#include <EntityLib/ComponentMerge.h>
#include <EntityLib/EntityLib.h>

#include <cassert>
#include <ciso646>
#include <fstream>
#include <set>
#include <map>
#include <optional>
#include <regex>
#include <filesystem>

#include <iostream>
RAH2_WARNING_PUSH
RAH2_DISABLE_WARNING(RAH2_SIGNED_UNSIGNED_MISMATCH)
#include <mustache.hpp>
RAH2_WARNING_POP
#include <cxxopts.hpp>
#include <json.hpp>

using namespace kainjow::mustache;
using namespace nlohmann;
using namespace std::filesystem;

std::map<std::string, Ent::Subschema const*> allDefs;
std::map<Ent::Subschema const*, std::string> schemaName;
json allDefinitions(json::value_t::array);
std::vector<path> outputFiles;

std::ofstream openOfstream(path const& _filepath)
{
    std::ofstream file;
    file.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::goodbit);
    file.open(_filepath);
    if (not file.is_open())
    {
        throw Ent::FileSystemError("Trying to open file for write", path(), _filepath);
    }
    return file;
}

/// @brief Check if _file1 is identical to _file2
/// @return true if _file1 is identical to _file2
bool compareFiles(path const& _file1, path const& _file2)
{
    std::ifstream f1(_file1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(_file2, std::ifstream::binary | std::ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        return false; // size mismatch
    }

    // seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(
        std::istreambuf_iterator(f1.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator(f2.rdbuf()));
}

void moveIfDifferent(path const& _source, path const& _dest)
{
    outputFiles.push_back(_dest.lexically_normal());
    if (not compareFiles(_source, _dest))
    {
        rename(_source, _dest);
    }
}

void copyIfDifferent(path const& _source, path const& _dest)
{
    auto const sourceAbsolute = absolute(_source);
    auto const destAbsolute = absolute(_dest);
    outputFiles.push_back(destAbsolute.lexically_normal());
    if (not compareFiles(sourceAbsolute, destAbsolute))
    {
        copy_file(sourceAbsolute, destAbsolute, copy_options::overwrite_existing);
    }
}

/// @brief Create a file at the _destinationPath, using the _output function to fill it
/// @remark Will not change the destination file if the created file is identical
template <typename Output>
void createFile(
    path const& _destinationPath, ///< Path of the file to create
    Output&& _output ///< Function taking a std::ostream to fill the created file
)
{
    auto const destinationPathAbsolute = absolute(_destinationPath);
    if (destinationPathAbsolute.generic_u32string().size()
        < 255) // Can't write filename longer than 255 characters
    {
        create_directories(_destinationPath.parent_path());
        auto const tempPath = temp_directory_path() / "temp.py";
        auto const tempPathAbsolute = absolute(tempPath);
        if (tempPathAbsolute.generic_u32string().size()
            < 255) // Can't access filename longer than 255 characters
        {
            {
                std::ofstream output = openOfstream(tempPathAbsolute);
                _output(output);
            }
            moveIfDifferent(tempPathAbsolute, destinationPathAbsolute);
        }
    }
}

void renderToFile(mustache& tmpl, data const& rootData, path const& _destinationPath)
{
    createFile(_destinationPath, [&](std::ostream& _output) { tmpl.render(rootData, _output); });
}

/// @brief Convert a json to a mustache data
data jsonToMustache(json const& _input)
{
    switch (_input.type())
    {
    case json::value_t::array:
    {
        data result(data::type::list);
        for (auto&& elt : _input)
        {
            result.push_back(jsonToMustache(elt));
        }
        return result;
    }
    case json::value_t::object:
    {
        data result(data::type::object);
        for (auto&& [k, v] : _input.items())
        {
            result.set(k, jsonToMustache(v));
        }
        return result;
    }
    case json::value_t::boolean: return {_input.get<bool>()};
    case json::value_t::number_float: return data(std::to_string(_input.get<double>()));
    case json::value_t::number_integer: return data(std::to_string(_input.get<int64_t>()));
    case json::value_t::number_unsigned: return data(std::to_string(_input.get<uint64_t>()));
    case json::value_t::string: return data(_input.get<std::string>());
    case json::value_t::null: [[fallthrough]];
    case json::value_t::binary: [[fallthrough]];
    case json::value_t::discarded: break;
    }
    return {false};
}

/// @brief In _input, replace all occurences of _before by _after
static std::string replaceAll(std::string _input, std::string const& _before, std::string const& _after)
{
    size_t pos = 0;
    while (pos != std::string::npos)
    {
        pos = _input.find(_before);
        if (pos != std::string::npos)
        {
            _input = _input.substr(0, pos) + _after + _input.substr(pos + _before.size());
        }
    }
    return _input;
}

/// @brief Transform _name to ensure it doesn't conflict with C++ or python keywords
static std::string escapeName(std::string _name, std::string_view _toAvoid = {})
{
    if (_name == _toAvoid)
    {
        _name.push_back('_');
    }
    static std::set<std::string> cppKeywordTypes = {
        "float", "bool", "from", "in", "None", "Type", "throw", "do", "default", "class"};

    std::regex const eastlNS(R"regex(eastl::(\w+))regex");
    _name = std::regex_replace(_name, eastlNS, "$1");
    std::regex const vector(R"regex(vector\<(\w+)\>)regex");
    std::string name2;
    while (name2 != _name)
    {
        name2 = std::regex_replace(_name, vector, "$1Vec");
        std::swap(_name, name2);
    }
    _name = replaceAll(_name, "::", "_");
    _name = replaceAll(_name, "<", "_");
    _name = replaceAll(_name, ">", "_");
    _name = replaceAll(_name, ",", "_");
    _name = replaceAll(_name, " ", "_");
    if (_name.front() >= '0' and _name.front() <= '9')
    {
        _name = '_' + _name;
    }
    if (cppKeywordTypes.count(_name) != 0)
    {
        return _name + '_';
    }
    return _name;
}

/// @brief Add a definition into allDefs/schemaName
/// @remark Enum types are defined several times. "overwrite" is used to merge them is one
static void addDef(
    std::string const& _name,
    Ent::Subschema const* _def,
    std::string const& _scope,
    bool _overwrite = false)
{
    ENTLIB_ASSERT(_def->getDataKind() != Ent::DataKind::COUNT);
    // We already have a specific class for EntityRef so ignore the one from EditionComponents.json
    if (_name == "EntityRef")
    {
        return;
    }
    auto const escapedName = escapeName(_name);
    if (allDefs.count(escapedName) == 0)
    {
        allDefs[escapedName] = _def;
        schemaName[_def] = escapedName;
    }
    else if (_overwrite)
    {
        // Check if there is two enum with the same name
        if (_def->enumValues != allDefs.at(escapedName)->enumValues)
        {
            fprintf(stderr, "Two enums with the same name!! %s", _name.c_str());
        }
        schemaName[_def] = escapedName; // Several def for the same name
    }
    else
    {
        std::string hint2 = escapeName(_scope + "_" + _name);
        while (allDefs.count(hint2) != 0)
        {
            hint2 = '_' + hint2;
        }
        allDefs[hint2] = _def;
        schemaName[_def] = hint2;
    }
}

/// @brief Get a type name for a given _link
static std::string getRefTypeName(std::string _link)
{
    _link = escapeName(_link);

    // Force to create the definition (do nothing if already exist)
    static auto const* definitionsStr = "#/definitions/";
    size_t const pos = _link.find(definitionsStr);
    if (pos == std::string::npos)
    {
        return _link;
    }
    return _link.substr(pos + strlen(definitionsStr));
}

static json makeNewType()
{
    // To avoid infinite loop in mustache, it is better that all fields are defined or false
    json type;
    type["array"] = false;
    type["prim_array"] = false;
    type["union_set"] = false;
    type["object_set"] = false;
    type["prim_set"] = false;
    type["ref"] = false;
    type["tuple"] = false;
    type["union"] = false;
    type["map"] = false;
    return type;
}

static json getSchemaRefType(Ent::SubschemaRef const& _ref);

/// @brief Make the description of a primitive type
static json prim(char const* _name)
{
    json type = makeNewType();
    json ref;
    ref["name"] = static_cast<char>(toupper(_name[0])) + std::string((_name + 1));
    if (_name == std::string("String") or _name == std::string("EntityRef"))
    {
        ref["py_native"] = "str";
        ref["cpp_native"] = "char const*";
    }
    else if (_name == std::string("Int"))
    {
        ref["py_native"] = "int";
        ref["cpp_native"] = "int64_t";
    }
    ref["settable"] = true;
    type["ref"] = std::move(ref);
    return type;
}

static std::set primitiveTypes = {
    Ent::DataKind::boolean,
    Ent::DataKind::integer,
    Ent::DataKind::number,
    Ent::DataKind::string,
    Ent::DataKind::entityRef};

/// @brief Get the name of a given primitive _type
char const* primitiveName(Ent::DataKind _kind)
{
    switch (_kind)
    {
    case Ent::DataKind::boolean: return "Bool";
    case Ent::DataKind::integer: return "Int";
    case Ent::DataKind::number: return "Float";
    case Ent::DataKind::string: return "String";
    case Ent::DataKind::entityRef: return "EntityRef";
    }
    ENTLIB_LOGIC_ERROR("Unexpected DataKind");
}

/// @return true if it is an array of primitive type
static bool isPrimArray(Ent::Subschema const& _ref)
{
    if (auto* const singularItems = _ref.singularItems.get())
    {
        return primitiveTypes.count(singularItems->get().getDataKind()) != 0;
    }
    return false;
}

/// @brief Get a json describing the type of a given  _schema
static json getSchemaType(Ent::Subschema const& _schema)
{
    json type = makeNewType();

    switch (_schema.getDataKind())
    {
    case Ent::DataKind::object:
    {
        std::string typeDispName = schemaName[&_schema];
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataKind::array:
    {
        ENTLIB_ASSERT(_schema.singularItems != nullptr or _schema.linearItems.has_value());

        if (_schema.singularItems != nullptr)
        {
            if (isPrimArray(_schema))
            {
                json array;
                array["type"] = getSchemaRefType(*_schema.singularItems);
                type["prim_array"] = std::move(array);
                return type;
            }
            json array;
            array["type"] = getSchemaRefType(*_schema.singularItems);
            type["array"] = std::move(array);
            return type;
        }

        json tuple;
        json types(json::value_t::array);
        size_t index = 0;

        for (auto const& itemRef : *_schema.linearItems)
        {
            auto subtype = getSchemaRefType(itemRef);
            if (index != _schema.linearItems->size() - 1)
            {
                subtype["comma"] = true;
            }
            subtype["index"] = index;
            types.push_back(subtype);
            ++index;
        }
        tuple["types"] = std::move(types);
        type["tuple"] = std::move(tuple);
        return type;
    }
    case Ent::DataKind::unionSet:
    {
        std::string typeDispName = schemaName.at(&_schema);
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataKind::objectSet:
    {
        json array;
        array["type"] = getSchemaRefType(*_schema.singularItems);
        auto keyFieldName = std::get<Ent::Subschema::ArrayMeta>(_schema.meta).keyField;
        auto& keyField = _schema.singularItems->get().properties.at(*keyFieldName);
        array["key_type"] = getSchemaRefType(keyField);
        type["object_set"] = std::move(array);
        return type;
    }
    case Ent::DataKind::map:
    {
        json array;
        auto& pair = *_schema.singularItems;
        array["key_type"] = getSchemaRefType(pair->linearItems->at(0));
        array["value_type"] = getSchemaRefType(pair->linearItems->at(1));
        type["map"] = std::move(array);
        return type;
    }
    case Ent::DataKind::primitiveSet:
    {
        json array;
        array["type"] = getSchemaRefType(*_schema.singularItems);
        type["prim_set"] = std::move(array);
        return type;
    }
    case Ent::DataKind::union_:
    {
        std::string typeDispName = schemaName[&_schema];
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataKind::boolean: [[fallthrough]];
    case Ent::DataKind::integer: [[fallthrough]];
    case Ent::DataKind::number: [[fallthrough]];
    case Ent::DataKind::string: [[fallthrough]];
    case Ent::DataKind::entityRef:
    {
        if (auto iter = schemaName.find(&_schema); iter != schemaName.end())
        {
            std::string const& typeDispName = iter->second;
            json ref;
            ref["name"] = typeDispName;
            type["ref"] = std::move(ref);
            // It works because in the schema, Enums are always strings
            type["ref"]["py_native"] = _schema.name.empty() ? "str" : _schema.name + "Enum";
            type["ref"]["cpp_native"] = _schema.name.empty() ? "char const*" : _schema.name + "Enum";
            type["ref"]["settable"] = true;
            return type;
        }
        return prim(primitiveName(_schema.getDataKind()));
    }
    }
    return json{};
}

/// @brief Get a json describing the type of a given _ref
static json getSchemaRefType(Ent::SubschemaRef const& _ref)
{
    if (std::holds_alternative<Ent::Subschema>(_ref.subSchemaOrRef))
    {
        return getSchemaType(*_ref);
    }
    std::string const singItmRef = std::get<Ent::SubschemaRef::Ref>(_ref.subSchemaOrRef).ref;
    auto name = getRefTypeName(singItmRef);
    json typeref;
    typeref["name"] = name;
    typeref["settable"] = isPrimArray(*_ref) or primitiveTypes.count(_ref->getDataKind()) != 0;
    json type = makeNewType();
    type["ref"] = std::move(typeref);
    return type;
}

/// @brief Get a json describing the data of a given _schema
static json getSchemaData(Ent::Subschema const& _schema)
{
    json defData;
    defData["alias"] = false;
    defData["object"] = false;
    defData["union_set"] = false;
    defData["object_set"] = false;
    defData["tuple"] = false;
    defData["union"] = false;
    defData["map"] = false;
    defData["enum"] = false;
    if (not _schema.name.empty())
    {
        defData["schema_name"] = _schema.name;
    }
    else
    {
        defData["schema_name"] = false;
    }

    switch (_schema.getDataKind())
    {
    case Ent::DataKind::array:
    {
        ENTLIB_ASSERT(_schema.singularItems != nullptr or _schema.linearItems.has_value());

        if (_schema.singularItems != nullptr)
        {
            json alias(json::value_t::object);
            alias["type"] = getSchemaType(_schema);
            defData["alias"] = std::move(alias);
            defData["includes"].emplace_back(getSchemaType(_schema));
            break;
        }

        json tuple;
        json types(json::value_t::array);
        size_t index = 0;
        std::set<json> includes;

        for (auto const& itemRef : *_schema.linearItems)
        {
            auto subtype = getSchemaRefType(itemRef);
            if (index != _schema.linearItems->size() - 1)
            {
                subtype["comma"] = true;
            }
            subtype["index"] = index;
            types.push_back(subtype);
            includes.emplace(getSchemaRefType(itemRef));
            ++index;
        }
        tuple["types"] = std::move(types);
        defData["tuple"] = std::move(tuple);
        defData["includes"] = includes;
        break;
    }
    case Ent::DataKind::unionSet:
    {
        Ent::Subschema const& unionSchema = **_schema.singularItems;
        defData["union_set"] = getSchemaData(unionSchema);
        defData["union_set"]["items"] = getSchemaRefType(*_schema.singularItems);
        defData["includes"].emplace_back(getSchemaRefType(*_schema.singularItems));
        break;
    }
    case Ent::DataKind::objectSet:
    {
        Ent::Subschema const& unionSchema = **_schema.singularItems;
        defData["object_set"] = getSchemaData(unionSchema);
        defData["object_set"]["items"] = getSchemaRefType(*_schema.singularItems);
        break;
    }
    case Ent::DataKind::map:
    {
        Ent::Subschema const& unionSchema = **_schema.singularItems;
        defData["map"] = getSchemaData(unionSchema);
        defData["map"]["items"] = getSchemaRefType(*_schema.singularItems);
        break;
    }
    case Ent::DataKind::primitiveSet:
    {
        json alias(json::value_t::object);
        alias["type"] = getSchemaType(_schema);
        defData["alias"] = std::move(alias);
        defData["includes"].emplace_back(getSchemaType(_schema));
        break;
    }
    case Ent::DataKind::boolean: [[fallthrough]];
    case Ent::DataKind::entityRef: [[fallthrough]];
    case Ent::DataKind::integer: [[fallthrough]];
    case Ent::DataKind::number: [[fallthrough]];
    case Ent::DataKind::string:
    {
        if (not _schema.enumValues.empty())
        {
            json enumNode(json::value_t::object);
            enumNode["type"] = prim("String");
            enumNode["type"]["ref"]["cpp_native"] = _schema.name + "Enum";
            enumNode["type"]["ref"]["py_native"] = _schema.name + "Enum";
            size_t idx = 0;
            for (auto&& val : _schema.enumValues)
            {
                enumNode["values"].push_back(json::value_t::object);
                enumNode["values"].back()["escaped_name"] = escapeName(val, _schema.name);
                enumNode["values"].back()["name"] = val;
                enumNode["values"].back()["value"] = idx;
                ++idx;
            }
            defData["enum"] = std::move(enumNode);
            break;
        }
        json alias(json::value_t::object);
        auto primType = prim(primitiveName(_schema.getDataKind()));
        alias["type"] = primType;
        defData["alias"] = std::move(alias);
        defData["includes"].emplace_back(primType);
        break;
    }
    case Ent::DataKind::object:
    {
        json object(json::value_t::object);
        json properties(json::value_t::array);
        std::set<json> includes;
        for (auto const& [propName, propRef] : _schema.properties)
        {
            json prop(json::value_t::object);
            auto propData = getSchemaRefType(propRef);
            prop["prop_name"] = propName;
            prop["escaped_prop_name"] = escapeName(propName, _schema.name);
            prop["type"] = std::move(propData);
            properties.push_back(prop);
            includes.emplace(getSchemaRefType(propRef));
        }
        object["properties"] = std::move(properties);
        defData["object"] = std::move(object);
        defData["includes"] = includes;
        break;
    }
    case Ent::DataKind::union_:
    {
        json union_(json::value_t::object);
        json types(json::value_t::array);
        auto const& unionData = std::get<Ent::Subschema::UnionMeta>(_schema.meta);
        for (Ent::SubschemaRef const& ref : *_schema.oneOf)
        {
            auto acceptedType =
                ref.get().properties.at(unionData.typeField)->constValue->get<std::string>();
            Ent::SubschemaRef const& subschema = ref.get().properties.at(unionData.dataField);
            json wrapper(json::value_t::object);
            wrapper["escaped_name"] = escapeName(acceptedType);
            wrapper["name"] = acceptedType;
            wrapper["type"] = getSchemaRefType(subschema);
            types.push_back(wrapper);
        }
        union_["types"] = std::move(types);
        defData["union"] = std::move(union_);
        break;
    }
    }

    return defData;
}

static void giveNameToAnonymousObject(
    Ent::Subschema const& _subschema, std::string const& _hint, std::string const& _morehint);

/// @brief Add a named definition for an anonymous _ref
static void giveNameToAnonymousObjectRef(
    Ent::SubschemaRef const& _ref,
    std::string const& _hint, ///< A string that could be the name
    std::string const& _hint2 ///< A string that could be used to avoid conflict
)
{
    if (std::holds_alternative<Ent::Subschema>(_ref.subSchemaOrRef))
    {
        if (_ref->getDataKind() == Ent::DataKind::object)
        {
            addDef(_hint, &(*_ref), _hint2);
        }
        else if (_ref->getDataKind() == Ent::DataKind::union_)
        {
            addDef(_hint, &(*_ref), _hint2);
        }
        else if (_ref->getDataKind() == Ent::DataKind::unionSet)
        {
            addDef(_hint, &(*_ref), _hint2);
        }
        else if (not _ref->enumValues.empty())
        {
            if (not _ref->name.empty())
            {
                // The same enum can be descibe several time
                // TODO : Loïc : Fix the export of enums in Wild (Export each enum only one time, like classes)
                addDef(_ref->name, &(*_ref), "", true);
            }
            else
            {
                addDef(_hint, &(*_ref), _hint2);
            }
        }
        giveNameToAnonymousObject(*_ref, _hint, _hint2);
    }
}

/// @brief Add a named definition for an anonymous _subschema
static void giveNameToAnonymousObject(
    Ent::Subschema const& _subschema,
    std::string const& _hint, ///< A string that could be the name
    std::string const& _morehint ///< A string that could be used to avoid conflict
)
{
    switch (_subschema.getDataKind())
    {
    case Ent::DataKind::boolean:
    case Ent::DataKind::entityRef:
    case Ent::DataKind::integer:
    case Ent::DataKind::number:
    case Ent::DataKind::string: return;
    case Ent::DataKind::array: [[fallthrough]];
    case Ent::DataKind::unionSet: [[fallthrough]];
    case Ent::DataKind::objectSet: [[fallthrough]];
    case Ent::DataKind::map: [[fallthrough]];
    case Ent::DataKind::primitiveSet:
        if (_subschema.linearItems.has_value())
        {
            size_t index = 0;
            for (auto const& subref : *_subschema.linearItems)
            {
                giveNameToAnonymousObjectRef(
                    subref, _hint + "_" + static_cast<char>('A' + index), _morehint);
            }
            ++index;
        }
        if (_subschema.singularItems != nullptr)
        {
            giveNameToAnonymousObjectRef(*_subschema.singularItems, _hint + "Item", _morehint);
        }
        break;
    case Ent::DataKind::union_:
    {
        auto const& unionData = std::get<Ent::Subschema::UnionMeta>(_subschema.meta);
        for (Ent::SubschemaRef const& subref : *_subschema.oneOf)
        {
            auto typeField = unionData.typeField.empty() ? "Type" : unionData.typeField;
            auto dataField = unionData.dataField.empty() ? "Data" : unionData.dataField;
            auto acceptedType = subref.get().properties.at(typeField)->constValue->get<std::string>();
            Ent::SubschemaRef const& subschemaref = subref.get().properties.at(dataField);
            giveNameToAnonymousObjectRef(subschemaref, typeField, _hint);
        }
        break;
    }
    case Ent::DataKind::object:
        for (auto const& [propName, propRef] : _subschema.properties)
        {
            giveNameToAnonymousObjectRef(propRef, propName, _hint);
        }
        break;
    }
}

/// @brief Generate the cpp EntGen API
void gencppProp(path const& _resourcePath, path const& _destinationPath)
{
    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);
    rootData["tuple_type"] =
        partial([] { return R"cpp(Ent::Gen2::Tuple<{{#types}}{{>display_type}}{{/types}}>)cpp"; });
    rootData["prim_set_type"] =
        partial([] { return R"cpp(Ent::Gen2::PrimitiveSet<{{type.ref.cpp_native}}>)cpp"; });
    rootData["object_set_type"] = partial(
        []
        {
            return R"cpp(Ent::Gen2::ObjectSet<{{key_type.ref.cpp_native}}, {{#type}}{{>display_type}}{{/type}}>)cpp";
        });
    rootData["map_type"] = partial(
        []
        {
            return R"cpp(Ent::Gen2::Map<{{key_type.ref.cpp_native}}, {{#value_type}}{{>display_type}}{{/value_type}}>)cpp";
        });
    rootData["display_type"] = partial(
        []
        {
            return R"({{#object_set}}{{>object_set_type}}{{/object_set}})"
                   R"({{#prim_set}}{{>prim_set_type}}{{/prim_set}})"
                   R"({{#map}}{{>map_type}}{{/map}})"
                   R"({{#ref}}Ent::Gen2::{{name}}{{/ref}})"
                   R"({{#array}}Array<{{#type}}{{>display_type}}{{/type}}>{{/array}})"
                   R"({{#prim_array}}PrimArray<{{#type}}{{>display_type}}{{/type}}>{{/prim_array}})"
                   R"({{#union_set}}UnionSet<{{#type}}{{>display_type}}{{/type}}>{{/union_set}})"
                   R"({{#tuple}}{{>tuple_type}}{{/tuple}})"
                   R"({{#comma}}, {{/comma}})";
        });

    mustache tmpl{R"cpp(
// /!\ This code is GENERATED! Do not modify it.

#pragma once

#include <EntityLib/EntityLib.h>
#include "EntGenHelpers.h"

namespace Ent
{
    namespace Gen2
    {
        {{#all_definitions}}{{#schema.object}}
        struct {{schema.type_name}};{{/schema.object}}{{#schema.union}}
        struct {{schema.type_name}}; // Union{{/schema.union}}{{#schema.tuple}}
        using {{schema.type_name}} = {{>tuple_type}}; // Tuple{{/schema.tuple}}{{#schema.union_set}}
        struct {{schema.type_name}}; // union_set{{/schema.union_set}}{{#schema.object_set}}
        struct {{schema.type_name}}; // object_set{{/schema.object_set}}{{#schema.enum}}
        struct {{schema.type_name}}; // enum
        enum class {{schema.type_name}}Enum
        {
            {{#values}}{{escaped_name}},
            {{/values}}
        };{{/schema.enum}}{{/all_definitions}}
        {{#all_definitions}}{{#schema.alias}}
        using {{schema.type_name}} = {{#type}}{{>display_type}}{{/type}};{{/schema.alias}}{{/all_definitions}}

        {{#all_definitions}}{{#schema.object}}
        struct {{schema.type_name}} : HelperObject<{{schema.type_name}}> // Object
        {
            explicit {{schema.type_name}}(Ent::Property _node): HelperObject<{{schema.type_name}}>(std::move(_node)) {}
            {{#schema.schema_name}}
            static constexpr char schemaName[] = "{{{.}}}";
            static {{schema.type_name}} load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return {{schema.type_name}}(Ent::Property(&_entlib, _entlib.getSchema(schemaName), _sourceFile.string().c_str()));
            }
            static {{schema.type_name}} loadCopy(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return {{schema.type_name}}(_entlib.loadPropertyCopy(schemaName, _sourceFile.string().c_str()));
            }
            static {{schema.type_name}} create(Ent::EntityLib& _entlib)
            {
                return {{schema.type_name}}(_entlib.newProperty(_entlib.getSchema(schemaName)));
            }
            {{schema.type_name}} makeInstanceOf()
            {
                return {{schema.type_name}}(getProperty().makeInstanceOf());
            }
            {{/schema.schema_name}}
        {{#properties}}    {{#type}}{{>display_type}}{{/type}} {{escaped_prop_name}}() const;
        {{/properties}}
        };{{/schema.object}}{{#schema.enum}}
        struct {{schema.type_name}} : EnumPropHelper<{{schema.type_name}}, {{schema.type_name}}Enum> // Enum
        {
            using Enum = {{schema.type_name}}Enum;
            using PropHelper<{{schema.type_name}}, Enum>::operator=;
            explicit {{schema.type_name}}(Ent::Property _node): EnumPropHelper<{{schema.type_name}}, Enum>(std::move(_node)) {}
            {{#schema.schema_name}}static constexpr char schemaName[] = "{{{.}}}";{{/schema.schema_name}}
            static constexpr char const* enumToString[] = {
                {{#values}}"{{name}}",
                {{/values}}
            };
        };
        inline char const* toString({{schema.type_name}}Enum value)
        {
            if(size_t(value) >= std::size({{schema.type_name}}::enumToString))
                throw std::runtime_error("Wrong enum value");
            return {{schema.type_name}}::enumToString[size_t(value)];
        }
        inline char const* toInternal({{schema.type_name}}Enum value) { return toString(value); }
        template<> inline {{schema.type_name}}Enum strToEnum<{{schema.type_name}}Enum>(char const* value)
        {
            return static_cast<{{schema.type_name}}Enum>(details::indexInEnum(value, {{schema.type_name}}::enumToString));
        }
        {{/schema.enum}}{{#schema.union}}
        struct {{schema.type_name}} : Base // Union
        {
            explicit {{schema.type_name}}(Ent::Property _node): Base(std::move(_node)) {}
            {{#schema.schema_name}}static constexpr char schemaName[] = "{{{.}}}";{{/schema.schema_name}}
            char const* getType() const;{{#types}}
            std::optional<{{#type}}{{>display_type}}{{/type}}> {{escaped_name}}();
            {{#type}}{{>display_type}}{{/type}} set{{escaped_name}}();
        {{/types}}
        };{{/schema.union}}{{#schema.union_set}}{{#union}}
        struct {{schema.type_name}} : UnionSetBase<{{items.ref.name}}> // union_set
        {
            explicit {{schema.type_name}}(Ent::Property _node)
                : UnionSetBase<{{items.ref.name}}>(std::move(_node))
            {
            }
            {{#schema.schema_name}}static constexpr char schemaName[] = "{{{.}}}";{{/schema.schema_name}}
            char const* getType() const;{{#types}}
            std::optional<{{#type}}{{>display_type}}{{/type}}> {{name}}() const;
            {{#type}}{{>display_type}}{{/type}} add{{name}}() const;
            void remove{{name}}() const;
        {{/types}}
        };{{/union}}{{/schema.union_set}}

{{/all_definitions}}

        {{#all_definitions}}{{#schema.object}}// {{schema.type_name}}
        {{#properties}}inline {{#type}}{{>display_type}}{{/type}} {{schema.type_name}}::{{escaped_prop_name}}() const
        {
            return {{#type}}{{>display_type}}{{/type}}(getProperty().getObjectField("{{prop_name}}"));
        }
        {{/properties}}{{/schema.object}}{{#schema.union}}// {{schema.type_name}}
        inline char const* {{schema.type_name}}::getType() const
        {
            return getProperty().getUnionType();
        }
        {{#types}}inline std::optional<{{#type}}{{>display_type}}{{/type}}> {{schema.type_name}}::{{escaped_name}}()
        {
            return strcmp(
                getProperty().getUnionType(), "{{{name}}}") != 0?
                    std::optional<{{#type}}{{>display_type}}{{/type}}>{}:
                    std::optional<{{#type}}{{>display_type}}{{/type}}>(getProperty().getUnionData());
        }
        inline {{#type}}{{>display_type}}{{/type}} {{schema.type_name}}::set{{escaped_name}}()
        {
            return {{#type}}{{>display_type}}{{/type}}(getProperty().setUnionType("{{{name}}}"));
        }
        {{/types}}
{{/schema.union}}{{#schema.union_set}}{{#union}}// {{schema.type_name}}
        inline char const* {{schema.type_name}}::getType() const
        {
            return getProperty().getUnionType();
        }
        {{#types}}inline std::optional<{{#type}}{{>display_type}}{{/type}}> {{schema.type_name}}::{{name}}() const
        {
            return std::optional<{{#type}}{{>display_type}}{{/type}}>(getSubNode("{{name}}"));
        }
        inline {{#type}}{{>display_type}}{{/type}} {{schema.type_name}}::add{{name}}() const
        {
            return {{#type}}{{>display_type}}{{/type}}(addSubNode("{{name}}"));
        }
        inline void {{schema.type_name}}::remove{{name}}() const
        {
            getProperty().eraseUnionSetItem("{{name}}");
        }
        {{/types}}
{{/union}}{{/schema.union_set}}
        {{/all_definitions}}
    } // Gen2
} // Ent
)cpp"};

    renderToFile(tmpl, rootData, _destinationPath / "EntGen.h");
    copyIfDifferent(_resourcePath / "EntGenHelpers.h", _destinationPath / "EntGenHelpers.h");
}

/// @brief Generate the python EntGen API
void genpyProp(path const& _resourcePath, path const& _destinationPath)
{
    create_directories(_destinationPath / "entgen2");

    auto add_partials = [](data& root)
    {
        root["display_type_hint"] = partial(
            []()
            {
                return R"({{#object_set}}ObjectSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/object_set}})"
                       R"({{#prim_set}}PrimitiveSet[{{type.ref.py_native}}]{{/prim_set}})"
                       R"({{#map}}Map[{{key_type.ref.py_native}}, {{#value_type}}{{>display_type_comma}}{{/value_type}}]{{/map}})"
                       R"({{#ref}}{{name}}{{/ref}})"
                       R"({{#array}}Array[{{#type}}{{>display_type_comma}}{{/type}}]{{/array}})"
                       R"({{#prim_array}}PrimArray[{{#type}}{{>display_type_comma}}{{/type}}]{{/prim_array}})"
                       R"({{#union_set}}UnionSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/union_set}})"
                       R"({{#tuple}}TupleNode[{{#types}}Type[{{>display_type_hint}}]{{#comma}}, {{/comma}}{{/types}}]{{/tuple}})";
            });

        root["display_type_comma"] = partial(
            []()
            {
                return R"({{>display_type_hint}})"
                       R"({{#comma}}, {{/comma}})";
            });
        root["type_ctor_comma"] = partial(
            []()
            {
                return R"({{>type_ctor}})"
                       R"({{#comma}}, {{/comma}})";
            });
        root["type_ctor"] = partial(
            []()
            {
                return R"({{#object_set}}(lambda n: ObjectSet({{#type}}{{>type_ctor}}{{/type}}, n)){{/object_set}})"
                       R"({{#prim_set}}(lambda n: PrimitiveSet({{type.ref.py_native}}, n)){{/prim_set}})"
                       R"({{#map}}(lambda n: Map({{key_type.ref.py_native}}, {{#value_type}}{{>type_ctor}}{{/value_type}}, n)){{/map}})"
                       R"({{#ref}}{{name}}{{/ref}})"
                       R"({{#array}}(lambda n: Array({{#type}}{{>type_ctor}}{{/type}}, n)){{/array}})"
                       R"({{#prim_array}}(lambda n: PrimArray({{#type}}{{>type_ctor}}{{/type}}, n)){{/prim_array}})"
                       R"({{#union_set}}(lambda n: UnionSet({{#items}}{{>type_ctor}}{{/items}}, n)){{/union_set}})"
                       R"({{#tuple}}TupleNode{{/tuple}})";
            });
        root["print_import"] = partial(
            []()
            {
                return R"({{#object_set}}{{#type}}{{>print_import}}{{/type}}{{/object_set}})"
                       R"({{#prim_set}}{{#type}}{{>print_import}}{{/type}}{{/prim_set}})"
                       R"({{#map}}{{#value_type}}{{>print_import}}{{/value_type}}{{#key_type}}{{>print_import}}{{/key_type}}{{/map}})"
                       R"({{#ref}}from entgen.{{name}} import *
{{/ref}})"
                       R"({{#array}}{{#type}}{{>print_import}}{{/type}}{{/array}})"
                       R"({{#prim_array}}{{#type}}{{>print_import}}{{/type}}{{/prim_array}})";
            });
        root["print_type_definition"] = partial(
            []()
            {
                return R"py(from EntityLibPy import Property
{{#schema}}{{#union_set}}
{{schema.type_name}} = (lambda n: UnionSet({{#items}}{{>type_ctor}}{{/items}}, n))
{{/union_set}}{{#object_set}}
class {{schema.display_type_comma}}(ObjectSet):
    {{#schema.schema_name}}schema_name = "{{.}}"{{/schema.schema_name}}
    pass
{{/object_set}}{{#enum}}
class {{schema.type_name}}Enum(Enum):
    {{#values}}{{escaped_name}} = "{{name}}"
    {{/values}}


{{/enum}}{{#alias}}
{{schema.type_name}} = {{#type}}{{>type_ctor}}{{/type}}
{{/alias}}{{#object}}

class {{schema.type_name}}(HelperObject):
{{#schema.schema_name}}
    schema_name = "{{.}}"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->{{schema.type_name}}
        return {{schema.type_name}}(Property(entlib, entlib.get_schema({{schema.type_name}}.schema_name), sourcefile))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->{{schema.type_name}}
        return {{schema.type_name}}(Property.create(entlib, entlib.get_schema({{schema.type_name}}.schema_name)))
    def save(self, destfile):
        self.node.save(destfile)
{{/schema.schema_name}}
{{#properties}}{{#type}}    @property
    def {{escaped_prop_name}}(self):  # type: ()->{{>display_type_comma}}
        return {{>type_ctor}}(self._node.get_object_field("{{prop_name}}")){{#prim_array}}
    @{{escaped_prop_name}}.setter
    def {{escaped_prop_name}}(self, val): self.{{escaped_prop_name}}.set(val)
{{/prim_array}}{{#ref.settable}}
    @{{escaped_prop_name}}.setter
    def {{escaped_prop_name}}(self, val): self.{{escaped_prop_name}}.set(val)
{{/ref.settable}}{{/type}}
{{/properties}}    pass


{{/object}}{{#union}}
class {{schema.type_name}}(Union):
    pass


{{/union}}{{#enum}}
class {{schema.type_name}}(Primitive[{{schema.type_name}}Enum]):  # Enum
    def __init__(self, node):
        super({{schema.type_name}}, self).__init__({{schema.type_name}}Enum, node)
    {{#schema_name}}schema_name = "{{.}}"{{/schema_name}}
    def __call__(self, node):  # type: (EntityLibPy.Node) -> {{schema.type_name}}
        return {{schema.type_name}}(node)
    def set(self, val):  # type: ({{schema.type_name}}Enum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


{{/enum}}{{#tuple}}
class {{type_name}}(TupleNode[Tuple[{{#types}}Type[{{>display_type_hint}}]{{#comma}}, {{/comma}}{{/types}}]]):
    def __init__(self, node=None):  # type: (EntityLibPy.Node) -> None
        super({{type_name}}, self).__init__((Int, Int, Float, Float, Float), node)
    {{#schema_name}}schema_name = "{{.}}"{{/schema_name}}

{{#types}}    def get_{{index}}(self):  # type: () -> {{>display_type_hint}}
        return {{>type_ctor}}(self._node.at({{index}}))
{{/types}}

{{/tuple}}{{/schema}})py";
            });
    };

    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);

    rootData["primitives"] = data::type::list;
    for (auto&& filename : {"Bool.py", "EntityRef.py", "Float.py", "Int.py", "String.py"})
    {
        std::ifstream primFile(_resourcePath / "entgen2" / filename);
        std::string data;
        std::getline(primFile, data, char(0));
        rootData["primitives"].push_back(data);
    }

    add_partials(rootData);

    mustache allInline{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen2_helpers import *
import EntityLibPy
from enum import Enum

{{#primitives}}
{{{.}}}
{{/primitives}}

{{#all_definitions}}
{{>print_type_definition}}
{{/all_definitions}}

)py"};

    auto inlinePath = absolute(_destinationPath / "entgen2/inline.py").lexically_normal();
    std::ofstream outputCommon = openOfstream(inlinePath);
    outputFiles.push_back(inlinePath);
    allInline.render(rootData, outputCommon);

    copyIfDifferent(_resourcePath / "entgen2_helpers.py", _destinationPath / "entgen2_helpers.py");
    createFile(_destinationPath / "__init__.py", [](std::ostream&) {});
    createFile(_destinationPath / "entgen2" / "__init__.py", [](std::ostream&) {});
}

// Used to make a topological sort to the generated types
class Graph
{
    std::map<std::string, std::vector<std::string>> adjlist;
    std::map<std::string, bool> vis;
    std::vector<std::string> order;

public:
    std::vector<std::string> const& getOrder()
    {
        return order;
    }

    void addEdge(std::string const& u, std::string v)
    {
        adjlist[u].emplace_back(std::move(v));
    }

    void dfshelper(std::string const& u)
    {
        vis[u] = true;
        for (auto const& i : adjlist[u])
        {
            if (!vis[i])
            {
                dfshelper(i);
            }
        }
        order.push_back(u);
    }

    void topological_dfs()
    {
        for (auto&& [node, deps] : adjlist)
        {
            if (not vis[node])
            {
                dfshelper(node);
            }
        }
        std::reverse(begin(order), end(order));
    }

    void print_order() const
    {
        for (auto const& ele : order)
        {
            std::cout << ele << " -> ";
        }
    }
};

std::set<std::string> getDependencies(std::map<std::string, json> const& nameToSchema, json const& include)
{
    std::set<std::string> deps;
    if (include["ref"].is_object())
    {
        auto const ref = include["ref"]["name"].get<std::string>();
        if (nameToSchema.count(ref) != 0)
        {
            deps.insert(ref);
        }
    }
    else if (include["array"].is_object())
    {
        deps.merge(getDependencies(nameToSchema, include["array"]["type"]));
    }
    else if (include["object_set"].is_object())
    {
        deps.merge(getDependencies(nameToSchema, include["object_set"]["type"]));
        deps.merge(getDependencies(nameToSchema, include["object_set"]["key_type"]));
    }
    else if (include["map"].is_object())
    {
        deps.merge(getDependencies(nameToSchema, include["map"]["value_type"]));
        deps.merge(getDependencies(nameToSchema, include["map"]["key_type"]));
    }
    else if (include["prim_array"].is_object())
    {
        deps.merge(getDependencies(nameToSchema, include["prim_array"]["type"]));
    }
    else if (include["prim_set"].is_object())
    {
        deps.merge(getDependencies(nameToSchema, include["prim_set"]["type"]));
    }
    else if (include["tuple"].is_object())
    {
        for (auto&& type : include["tuple"]["types"])
        {
            deps.merge(getDependencies(nameToSchema, type));
        }
    }
    else if (include["union"].is_object())
    {
        for (auto&& type : include["union"]["types"])
        {
            deps.merge(getDependencies(nameToSchema, type["type"]));
        }
    }
    else if (include["union_set"].is_object())
    {
        deps.merge(getDependencies(nameToSchema, include["union_set"]["items"]));
    }
    return deps;
}

int main(int argc, char* argv[])
try
{
    cxxopts::Options options(
        "EntLibAPIGenerator", "Use schemas to generate strong typed API for C++ and python");
    // clang-format off
    options.add_options()
        ("r,resources","Path to the 'resources' directory", cxxopts::value<path>()->default_value("../EntLibAPIGenerator/resources"))
        ("d,destination","Directory to output c++ and python classes",cxxopts::value<path>()->default_value("EntGen"))
        ("s,schemas", "Directory containing the schemas", cxxopts::value<path>())
        ("h,help", "Print usage");
    // clang-format on

    path resourcePath, destinationPath, schemaPath;

    try
    {
        auto result = options.parse(argc, argv);
        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return EXIT_SUCCESS;
        }

        resourcePath = result["resources"].as<path>();
        destinationPath = result["destination"].as<path>();
        schemaPath = result["schemas"].as<path>();
    }
    catch (std::exception& ex)
    {
        std::cout << typeid(ex).name() << " - " << ex.what() << std::endl;
        std::cout << options.help() << std::endl;
        return EXIT_FAILURE;
    }

    Ent::EntityLib entlib(current_path(), schemaPath);

    // Add all first-level definitions in the dist
    for (auto& [defName, def] : entlib.schema.schema.allDefinitions)
    {
        addDef(getRefTypeName(defName), &def, "");
    }

    // Add in the dict some inlined schema which will need a name (Types inside array, tuple or property)
    for (auto& [defName, def] : entlib.schema.schema.allDefinitions)
    {
        giveNameToAnonymousObject(def, getRefTypeName(defName), "");
    }

    // Construct the full mustache json
    for (auto& [defName, def] : allDefs)
    {
        auto shortTypeName = getRefTypeName(defName);
        json defData = getSchemaData(*def);
        defData["type_name"] = shortTypeName;
        json refSchema(json::value_t::object);
        refSchema["schema"] = std::move(defData);
        allDefinitions.push_back(refSchema);
    }

    create_directories(destinationPath);
    std::vector<path> previousFiles;
    for (auto const& file : recursive_directory_iterator(destinationPath))
    {
        if (file.is_regular_file())
        {
            auto const filePathAbsolute = absolute(file.path());
            previousFiles.push_back(filePathAbsolute.lexically_normal()); // Ensure paths are comparable
        }
    }

    auto getTypeID = [](json const& type)
    {
        auto&& schema = type["schema"];
        if (schema.count("type_name") != 0)
        {
            return schema["type_name"].get<std::string>();
        }
        if (schema.count("schema_name") != 0)
        {
            return schema["schema_name"].get<std::string>();
        }
        return std::string("Anonymous");
    };

    // Transfert allDefinitions into nameToSchema
    std::map<std::string, json> nameToSchema;
    for (json& refSchema : allDefinitions)
    {
        nameToSchema.emplace(getTypeID(refSchema), std::move(refSchema));
    }
    allDefinitions.clear();

    // Enter schema into the topological sorter
    Graph g;
    for (auto const& [type_name, refSchema] : nameToSchema)
    {
        if (refSchema["schema"].count("includes") != 0)
        {
            std::set<std::string> deps;
            for (auto&& include : refSchema["schema"]["includes"])
            {
                deps.merge(getDependencies(nameToSchema, include));
            }
            for (auto&& ref : deps)
            {
                g.addEdge(ref, type_name);
            }
        }
    }

    // topological sort schema types
    g.topological_dfs();

    // Transfert nameToSchema into allDefinitions
    for (auto const& id : g.getOrder())
    {
        auto& schema = nameToSchema.at(id);
        allDefinitions.push_back(std::move(schema));
        nameToSchema.erase(id);
    }
    for (auto&& [id, schema] : nameToSchema)
    {
        allDefinitions.push_back(std::move(schema));
    }

    // Export the mustache json input (for debug purpose)
    createFile(
        destinationPath / "schemaOutput.json",
        [&](std::ostream& schemaOutput) { schemaOutput << allDefinitions.dump(4); });

    gencppProp(resourcePath / "cpp2", destinationPath / "cpp2");
    genpyProp(resourcePath / "py2", destinationPath / "py2");

    // Remove old files which was not re-created
    std::sort(begin(outputFiles), end(outputFiles));
    std::sort(begin(previousFiles), end(previousFiles));
    std::vector<path> toRemove;
    std::set_difference(
        begin(previousFiles),
        end(previousFiles),
        begin(outputFiles),
        end(outputFiles),
        std::back_inserter(toRemove));
    for (auto const& obsoleteFile : toRemove)
    {
        printf("Remove file : %ls\n", obsoleteFile.c_str());
        remove(obsoleteFile);
    }

    std::cout << "EntGen generation done" << std::endl;
    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    std::cerr << typeid(ex).name() << " : " << ex.what() << std::endl;
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "UNKOWN EXCEPTION" << std::endl;
    return EXIT_FAILURE;
}
