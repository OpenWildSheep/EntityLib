#include <ComponentMerge.h>
#include <EntityLib.h>

#include <cassert>
#include <ciso646>
#include <fstream>
#include <set>
#include <map>
#include <optional>
#include <regex>

#pragma warning(push, 0)
#include <iostream>
#include <mustache.hpp>
#include "../EntityLib/external/filesystem.hpp"
#include "../EntityLib/external/json.hpp"
#pragma warning(pop)

using namespace kainjow::mustache;
using namespace nlohmann;
using namespace std::filesystem;

std::map<std::string, Ent::Subschema const*> allDefs;
std::map<Ent::Subschema const*, std::string> schemaName;
json allDefinitions(json::value_t::array);

std::ofstream openOfstream(std::filesystem::path const& _filepath)
{
    std::ofstream file;
    file.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::goodbit);
    file.open(_filepath);
    if (not file.is_open())
    {
        throw FileSystemError("Trying to open file for write", std::filesystem::path(), _filepath);
    }
    return file;
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
    case json::value_t::boolean: return data(_input.get<bool>());
    case json::value_t::number_float: return data(std::to_string(_input.get<double>()));
    case json::value_t::number_integer: return data(std::to_string(_input.get<int64_t>()));
    case json::value_t::number_unsigned: return data(std::to_string(_input.get<uint64_t>()));
    case json::value_t::string: return data(_input.get<std::string>());
    }
    return data(false);
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
static std::string escapeName(std::string _name)
{
    static std::set<std::string> cppKeywordTypes = {
        "float", "bool", "from", "in", "None", "Type", "throw", "do", "default"};

    std::regex eastlNS(R"regex(eastl::(\w+))regex");
    _name = std::regex_replace(_name, eastlNS, "$1");
    std::regex vector(R"regex(vector\<(\w+)\>)regex");
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
    ENTLIB_ASSERT(_def->type != Ent::DataType::null);
    auto escapedName = escapeName(_name);
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
    static char const* definitionsStr = "#/definitions/";
    size_t pos = _link.find(definitionsStr);
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
    ref["name"] = (char)toupper(_name[0]) + std::string((_name + 1));
    if (_name == std::string("String"))
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

static std::set<Ent::DataType> primitiveTypes = {
    Ent::DataType::boolean,
    Ent::DataType::integer,
    Ent::DataType::number,
    Ent::DataType::string,
    Ent::DataType::entityRef};

/// @brief Get the name of a given primitive _type
char const* primitiveName(Ent::DataType _type)
{
    switch (_type)
    {
    case Ent::DataType::boolean: return "Bool";
    case Ent::DataType::integer: return "Int";
    case Ent::DataType::number: return "Float";
    case Ent::DataType::string: return "String";
    case Ent::DataType::entityRef: return "EntityRef";
    }
    ENTLIB_LOGIC_ERROR("Unexpected DataType");
}

/// @return true if it is an array of primitive type
static bool isPrimArray(Ent::Subschema const& _ref)
{
    if (auto singularItems = _ref.singularItems.get())
    {
        return primitiveTypes.count(singularItems->get().type) != 0;
    }
    else
    {
        return false;
    }
}

/// @brief Get a json describing the type of a given  _schema
static json getSchemaType(Ent::Subschema const& _schema)
{
    json type = makeNewType();

    switch (_schema.type)
    {
    case Ent::DataType::object:
    {
        std::string typeDispName = schemaName[&_schema];
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataType::array:
        if (_schema.singularItems != nullptr)
        {
            auto const& meta = _schema.meta.get<Ent::Subschema::ArrayMeta>();
            if (meta.overridePolicy == "set")
            {
                auto const singularType = (*_schema.singularItems)->type;
                if (singularType == Ent::DataType::oneOf)
                {
                    std::string typeDispName = schemaName.at(&_schema);
                    json ref;
                    ref["name"] = typeDispName;
                    type["ref"] = std::move(ref);
                    return type;
                }
                else if (singularType == Ent::DataType::object)
                {
                    json array;
                    array["type"] = getSchemaRefType(*_schema.singularItems);
                    auto keyFieldName = _schema.meta.get<Ent::Subschema::ArrayMeta>().keyField;
                    auto& keyField = _schema.singularItems->get().properties.at(*keyFieldName);
                    array["key_type"] = getSchemaRefType(keyField);
                    type["object_set"] = std::move(array);
                    return type;
                }
                else if (
                    singularType == Ent::DataType::boolean || singularType == Ent::DataType::entityRef
                    || singularType == Ent::DataType::integer || singularType == Ent::DataType::number
                    || singularType == Ent::DataType::string)
                {
                    json array;
                    array["type"] = getSchemaRefType(*_schema.singularItems);
                    type["prim_set"] = std::move(array);
                    return type;
                }
                else
                {
                    ENTLIB_LOGIC_ERROR("Unexpected singular type in set");
                }
            }
            else if (meta.overridePolicy == "map")
            {
                json array;
                auto& pair = *_schema.singularItems;
                array["key_type"] = getSchemaRefType(pair->linearItems->at(0));
                array["value_type"] = getSchemaRefType(pair->linearItems->at(1));
                type["map"] = std::move(array);
                return type;
            }
            else if (isPrimArray(_schema))
            {
                json array;
                array["type"] = getSchemaRefType(*_schema.singularItems);
                type["prim_array"] = std::move(array);
                return type;
            }
            else
            {
                json array;
                array["type"] = getSchemaRefType(*_schema.singularItems);
                type["array"] = std::move(array);
                return type;
            }
        }
        else
        {
            json tuple;
            json types(json::value_t::array);
            size_t index = 0;

            for (auto& itemRef : *_schema.linearItems)
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
    case Ent::DataType::oneOf:
    {
        std::string typeDispName = schemaName[&_schema];
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataType::boolean: [[fallthrough]];
    case Ent::DataType::integer: [[fallthrough]];
    case Ent::DataType::number: [[fallthrough]];
    case Ent::DataType::string: [[fallthrough]];
    case Ent::DataType::entityRef:
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
        else
        {
            return prim(primitiveName(_schema.type));
        }
    }
    return json{};
}

/// @brief Get a json describing the type of a given _ref
static json getSchemaRefType(Ent::SubschemaRef const& _ref)
{
    if (_ref.subSchemaOrRef.is<Ent::Subschema>())
    {
        return getSchemaType(*_ref);
    }
    else
    {
        std::string singItmRef = _ref.subSchemaOrRef.get<Ent::SubschemaRef::Ref>().ref;
        auto name = getRefTypeName(singItmRef);
        json typeref;
        typeref["name"] = name;
        typeref["settable"] = isPrimArray(*_ref) or primitiveTypes.count(_ref->type) != 0;
        json type = makeNewType();
        type["ref"] = std::move(typeref);
        return type;
    }
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

    switch (_schema.type)
    {
    case Ent::DataType::array:
        if (_schema.singularItems != nullptr)
        {
            auto const& meta = _schema.meta.get<Ent::Subschema::ArrayMeta>();
            if (meta.overridePolicy == "set")
            {
                auto const singularType = (*_schema.singularItems)->type;
                if (singularType == Ent::DataType::oneOf)
                {
                    Ent::Subschema const& unionSchema = **_schema.singularItems;
                    defData["union_set"] = getSchemaData(unionSchema);
                    defData["union_set"]["items"] = getSchemaRefType(*_schema.singularItems);
                    defData["includes"].emplace_back(getSchemaRefType(*_schema.singularItems));
                    break;
                }
                else if (singularType == Ent::DataType::object)
                {
                    Ent::Subschema const& unionSchema = **_schema.singularItems;
                    defData["object_set"] = getSchemaData(unionSchema);
                    defData["object_set"]["items"] = getSchemaRefType(*_schema.singularItems);
                    break;
                }
                else if (
                    singularType == Ent::DataType::boolean || singularType == Ent::DataType::entityRef
                    || singularType == Ent::DataType::integer || singularType == Ent::DataType::number
                    || singularType == Ent::DataType::string)
                {
                    // A primitive set is a native type so it is just an alias
                    json alias(json::value_t::object);
                    alias["type"] = getSchemaType(_schema);
                    defData["alias"] = std::move(alias);
                    defData["includes"].emplace_back(getSchemaType(_schema));
                    break;
                }
            }
            else if (meta.overridePolicy == "map")
            {
                Ent::Subschema const& unionSchema = **_schema.singularItems;
                defData["map"] = getSchemaData(unionSchema);
                defData["map"]["items"] = getSchemaRefType(*_schema.singularItems);
                break;
            }
            else
            {
                json alias(json::value_t::object);
                alias["type"] = getSchemaType(_schema);
                defData["alias"] = std::move(alias);
                defData["includes"].emplace_back(getSchemaType(_schema));
                break;
            }
        }
        else
        {
            json tuple;
            json types(json::value_t::array);
            size_t index = 0;
            std::set<json> includes;

            for (auto& itemRef : *_schema.linearItems)
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
        ENTLIB_LOGIC_ERROR("Unexpected fallthrough");
    case Ent::DataType::boolean: [[fallthrough]];
    case Ent::DataType::entityRef: [[fallthrough]];
    case Ent::DataType::integer: [[fallthrough]];
    case Ent::DataType::number: [[fallthrough]];
    case Ent::DataType::string:
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
                enumNode["values"].back()["escaped_name"] = escapeName(val);
                enumNode["values"].back()["name"] = val;
                enumNode["values"].back()["value"] = idx;
                ++idx;
            }
            defData["enum"] = std::move(enumNode);
            break;
        }
        json alias(json::value_t::object);
        auto primType = prim(primitiveName(_schema.type));
        alias["type"] = primType;
        defData["alias"] = std::move(alias);
        defData["includes"].emplace_back(primType);
        break;
    }
    case Ent::DataType::object:
    {
        json object(json::value_t::object);
        json properties(json::value_t::array);
        std::set<json> includes;
        for (auto& [propName, propRef] : _schema.properties)
        {
            json prop(json::value_t::object);
            auto propData = getSchemaRefType(propRef);
            prop["prop_name"] = escapeName(propName);
            prop["type"] = std::move(propData);
            properties.push_back(prop);
            includes.emplace(getSchemaRefType(propRef));
        }
        object["properties"] = std::move(properties);
        defData["object"] = std::move(object);
        defData["includes"] = includes;
        break;
    }
    case Ent::DataType::oneOf:
    {
        json union_(json::value_t::object);
        json types(json::value_t::array);
        auto const& unionData = _schema.meta.get<Ent::Subschema::UnionMeta>();
        for (Ent::SubschemaRef const& ref : *_schema.oneOf)
        {
            auto acceptedType =
                ref.get().properties.at(unionData.typeField)->constValue->get<std::string>();
            Ent::SubschemaRef const& subschema = ref.get().properties.at(unionData.dataField);
            json wrapper(json::value_t::object);
            wrapper["name"] = escapeName(acceptedType);
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
    if (_ref.subSchemaOrRef.is<Ent::Subschema>())
    {
        if (_ref->type == Ent::DataType::object)
        {
            addDef(_hint, &(*_ref), _hint2);
        }
        else if (_ref->type == Ent::DataType::oneOf)
        {
            addDef(_hint, &(*_ref), _hint2);
        }
        else if (_ref->type == Ent::DataType::array)
        {
            if (_ref->singularItems != nullptr)
            {
                auto const& meta = _ref->meta.get<Ent::Subschema::ArrayMeta>();
                if (meta.overridePolicy == "set")
                {
                    if ((*_ref->singularItems)->type == Ent::DataType::oneOf)
                    {
                        addDef(_hint, &(*_ref), _hint2);
                    }
                }
            }
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
    switch (_subschema.type)
    {
    case Ent::DataType::boolean:
    case Ent::DataType::entityRef:
    case Ent::DataType::integer:
    case Ent::DataType::number:
    case Ent::DataType::string: return;
    case Ent::DataType::array:
        if (_subschema.linearItems.has_value())
        {
            size_t index = 0;
            for (auto& subref : *_subschema.linearItems)
            {
                giveNameToAnonymousObjectRef(subref, _hint + "_" + char('A' + index), _morehint);
            }
            ++index;
        }
        if (_subschema.singularItems != nullptr)
        {
            giveNameToAnonymousObjectRef(*_subschema.singularItems, _hint + "Item", _morehint);
        }
        break;
    case Ent::DataType::oneOf:
    {
        auto const& unionData = _subschema.meta.get<Ent::Subschema::UnionMeta>();
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
    case Ent::DataType::object:
        for (auto& [propName, propRef] : _subschema.properties)
        {
            giveNameToAnonymousObjectRef(propRef, propName, _hint);
        }
        break;
    }
}

/// @brief Generate the cpp EntGen API
void gencpp(std::filesystem::path const& _resourcePath, std::filesystem::path const& _destinationPath)
{
    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);
    rootData["tuple_type"] =
        partial([]() { return R"cpp(Ent::Gen::Tuple<{{#types}}{{>display_type}}{{/types}}>)cpp"; });
    rootData["prim_set_type"] =
        partial([]() { return R"cpp(Ent::Gen::PrimitiveSet<{{type.ref.cpp_native}}>)cpp"; });
    rootData["object_set_type"] = partial([]() {
        return R"cpp(Ent::Gen::ObjectSet<{{key_type.ref.cpp_native}}, {{#type}}{{>display_type}}{{/type}}>)cpp";
    });
    rootData["map_type"] = partial([]() {
        return R"cpp(Ent::Gen::Map<{{key_type.ref.cpp_native}}, {{#value_type}}{{>display_type}}{{/value_type}}>)cpp";
    });
    rootData["display_type"] = partial([]() {
        return R"({{#object_set}}{{>object_set_type}}{{/object_set}})"
               R"({{#prim_set}}{{>prim_set_type}}{{/prim_set}})"
               R"({{#map}}{{>map_type}}{{/map}})"
               R"({{#ref}}Ent::Gen::{{name}}{{/ref}})"
               R"({{#array}}Array<{{#type}}{{>display_type}}{{/type}}>{{/array}})"
               R"({{#prim_array}}PrimArray<{{#type}}{{>display_type}}{{/type}}>{{/prim_array}})"
               R"({{#union_set}}UnionSet<{{#type}}{{>display_type}}{{/type}}>{{/union_set}})"
               R"({{#tuple}}{{>tuple_type}}{{/tuple}})"
               R"({{#comma}}, {{/comma}})";
    });

    mustache tmpl{R"cpp(
// /!\ This code is GENERATED! Do not modify it.

#pragma once

#include <EntityLib.h>
#include "EntGenHelpers.h"

namespace Ent
{
    namespace Gen
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
        struct {{schema.type_name}} : HelperObject // Object
        {
            {{schema.type_name}}(Ent::Node* _node): HelperObject(_node) {}
            {{#schema.schema_name}}
            static constexpr char schemaName[] = "{{.}}";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            {{/schema.schema_name}}
        {{#properties}}    {{#type}}{{>display_type}}{{/type}} {{prop_name}}() const;
        {{/properties}}
        };{{/schema.object}}{{#schema.enum}}
        struct {{schema.type_name}} : EnumPropHelper<{{schema.type_name}}, {{schema.type_name}}Enum> // Enum
        {
            using Enum = {{schema.type_name}}Enum;
            using PropHelper<{{schema.type_name}}, Enum>::operator=;
            {{schema.type_name}}(Ent::Node* _node): EnumPropHelper<{{schema.type_name}}, Enum>(_node) {}
            {{#schema.schema_name}}static constexpr char schemaName[] = "{{.}}";{{/schema.schema_name}}
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
            {{schema.type_name}}(Ent::Node* _node): Base(_node) {}
            {{#schema.schema_name}}static constexpr char schemaName[] = "{{.}}";{{/schema.schema_name}}
            char const* getType() const;{{#types}}
            std::optional<{{#type}}{{>display_type}}{{/type}}> {{name}}() const;
            {{#type}}{{>display_type}}{{/type}} set{{name}}() const;
        {{/types}}
        };{{/schema.union}}{{#schema.union_set}}{{#union}}
        struct {{schema.type_name}} : UnionSetBase<{{items.ref.name}}> // union_set
        {
            {{schema.type_name}}(Ent::Node* _node)
                : UnionSetBase<{{items.ref.name}}>(_node)
            {
            }
            {{#schema.schema_name}}static constexpr char schemaName[] = "{{.}}";{{/schema.schema_name}}
            char const* getType() const;{{#types}}
            std::optional<{{#type}}{{>display_type}}{{/type}}> {{name}}() const;
            {{#type}}{{>display_type}}{{/type}} add{{name}}() const;
        {{/types}}
        };{{/union}}{{/schema.union_set}}

{{/all_definitions}}

        {{#all_definitions}}{{#schema.object}}// {{schema.type_name}}
        {{#properties}}inline {{#type}}{{>display_type}}{{/type}} {{schema.type_name}}::{{prop_name}}() const
        {
            return {{#type}}{{>display_type}}{{/type}}(node->at("{{prop_name}}"));
        }
        {{/properties}}{{/schema.object}}{{#schema.union}}// {{schema.type_name}}
        inline char const* {{schema.type_name}}::getType() const
        {
            return node->getUnionType();
        }
        {{#types}}inline std::optional<{{#type}}{{>display_type}}{{/type}}> {{schema.type_name}}::{{name}}() const
        {
            return strcmp(node->getUnionType(), "{{name}}") != 0? std::optional<{{#type}}{{>display_type}}{{/type}}>{}: std::optional<{{#type}}{{>display_type}}{{/type}}>(node->getUnionData());
        }
        inline {{#type}}{{>display_type}}{{/type}} {{schema.type_name}}::set{{name}}() const
        {
            return {{#type}}{{>display_type}}{{/type}}(node->setUnionType("{{schema.type_name}}"));
        }
        {{/types}}
{{/schema.union}}{{#schema.union_set}}{{#union}}// {{schema.type_name}}
        inline char const* {{schema.type_name}}::getType() const
        {
            return node->getUnionType();
        }
        {{#types}}inline std::optional<{{#type}}{{>display_type}}{{/type}}> {{schema.type_name}}::{{name}}() const
        {
            auto sub = getSubNode("{{name}}");
            return sub == nullptr? std::optional<{{#type}}{{>display_type}}{{/type}}>{}: std::optional<{{#type}}{{>display_type}}{{/type}}>(getSubNode("{{name}}"));
        }
        inline {{#type}}{{>display_type}}{{/type}} {{schema.type_name}}::add{{name}}() const
        {
            return {{#type}}{{>display_type}}{{/type}}(addSubNode("{{name}}"));
        }
        {{/types}}
{{/union}}{{/schema.union_set}}
        {{/all_definitions}}
    } // Gen
} // Ent
)cpp"};

    create_directories(_destinationPath);
    std::ofstream output = openOfstream(_destinationPath / "EntGen.h");
    tmpl.render(rootData, output);
    copy_file(_resourcePath / "EntGenHelpers.h", _destinationPath / "EntGenHelpers.h");
}

/// @brief Generate the python EntGen API
void genpy(std::filesystem::path const& _resourcePath, std::filesystem::path const& _destinationPath)
{
    create_directories(_destinationPath / "entgen");

    auto add_partials = [](data& root) {
        root["display_type_hint"] = partial([]() {
            return R"({{#object_set}}ObjectSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/object_set}})"
                   R"({{#prim_set}}PrimitiveSet[{{type.ref.py_native}}]{{/prim_set}})"
                   R"({{#map}}Map[{{key_type.ref.py_native}}, {{#value_type}}{{>display_type_comma}}{{/value_type}}]{{/map}})"
                   R"({{#ref}}{{name}}{{/ref}})"
                   R"({{#array}}Array[{{#type}}{{>display_type_comma}}{{/type}}]{{/array}})"
                   R"({{#prim_array}}PrimArray[{{#type}}{{>display_type_comma}}{{/type}}]{{/prim_array}})"
                   R"({{#union_set}}UnionSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/union_set}})"
                   R"({{#tuple}}TupleNode[{{#types}}Type[{{>display_type_hint}}]{{#comma}}, {{/comma}}{{/types}}]{{/tuple}})";
        });

        root["display_type_comma"] = partial([]() {
            return R"({{>display_type_hint}})"
                   R"({{#comma}}, {{/comma}})";
        });
        root["type_ctor_comma"] = partial([]() {
            return R"({{>type_ctor}})"
                   R"({{#comma}}, {{/comma}})";
        });
        root["type_ctor"] = partial([]() {
            return R"({{#object_set}}(lambda n: ObjectSet({{#type}}{{>type_ctor}}{{/type}}, n)){{/object_set}})"
                   R"({{#prim_set}}(lambda n: PrimitiveSet({{type.ref.py_native}}, n)){{/prim_set}})"
                   R"({{#map}}(lambda n: Map({{key_type.ref.py_native}}, {{#value_type}}{{>type_ctor}}{{/value_type}}, n)){{/map}})"
                   R"({{#ref}}{{name}}{{/ref}})"
                   R"({{#array}}(lambda n: Array({{#type}}{{>type_ctor}}{{/type}}, n)){{/array}})"
                   R"({{#prim_array}}(lambda n: PrimArray({{#type}}{{>type_ctor}}{{/type}}, n)){{/prim_array}})"
                   R"({{#union_set}}(lambda n: UnionSet({{#items}}{{>type_ctor}}{{/items}}, n)){{/union_set}})"
                   R"({{#tuple}}TupleNode{{/tuple}})";
        });
        root["print_import"] = partial([]() {
            return R"({{#object_set}}{{#type}}{{>print_import}}{{/type}}{{/object_set}})"
                   R"({{#prim_set}}{{#type}}{{>print_import}}{{/type}}{{/prim_set}})"
                   R"({{#map}}{{#value_type}}{{>print_import}}{{/value_type}}{{#key_type}}{{>print_import}}{{/key_type}}{{/map}})"
                   R"({{#ref}}from entgen.{{name}} import *
{{/ref}})"
                   R"({{#array}}{{#type}}{{>print_import}}{{/type}}{{/array}})"
                   R"({{#prim_array}}{{#type}}{{>print_import}}{{/type}}{{/prim_array}})";
        });
        root["print_type_definition"] = partial([]() {
            return R"py(from EntityLibPy import Node
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
        return {{schema.type_name}}(entlib.load_node_file(sourcefile, entlib.get_schema({{schema.type_name}}.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->{{schema.type_name}}
        return {{schema.type_name}}(entlib.make_node({{schema.type_name}}.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
{{/schema.schema_name}}
{{#properties}}{{#type}}    @property
    def {{prop_name}}(self):  # type: ()->{{>display_type_comma}}
        return {{>type_ctor}}(self._node.at("{{prop_name}}")){{#prim_array}}
    @{{prop_name}}.setter
    def {{prop_name}}(self, val): self.{{prop_name}}.set(val)
{{/prim_array}}{{#ref.settable}}
    @{{prop_name}}.setter
    def {{prop_name}}(self, val): self.{{prop_name}}.set(val)
{{/ref.settable}}{{/type}}
{{/properties}}    pass


{{/object}}{{#union}}
class {{schema.type_name}}(Union):
    pass


{{/union}}{{#enum}}
class {{schema.type_name}}(Primitive[{{schema.type_name}}Enum]):  # Enum
    def __init__(self, node):
        super().__init__({{schema.type_name}}Enum, node)
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
        super().__init__((Int, Int, Float, Float, Float), node)
    {{#schema_name}}schema_name = "{{.}}"{{/schema_name}}

{{#types}}    def get_{{index}}(self):  # type: () -> {{>display_type_hint}}
        return {{>type_ctor}}(self._node.at({{index}}))
{{/types}}

{{/tuple}}{{/schema}})py";
        });
    };

    for (json const& refSchema : allDefinitions)
    {
        data rootData;
        rootData["file_schema"] = jsonToMustache(refSchema);

        add_partials(rootData);

        mustache tmpl{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

{{#file_schema}}
{{#schema}}{{#includes}}
{{>print_import}}
{{/includes}}{{/schema}}

{{>print_type_definition}}

{{/file_schema}}

)py"};
        auto shortTypeName = refSchema["schema"]["type_name"].get<std::string>();
        std::ofstream output = openOfstream(_destinationPath / "entgen" / (shortTypeName + ".py"));
        tmpl.render(rootData, output);
    }

    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);

    rootData["primitives"] = data::type::list;
    for (auto&& filename : {"Bool.py", "EntityRef.py", "Float.py", "Int.py", "String.py"})
    {
        std::ifstream primFile(_resourcePath / "entgen" / filename);
        std::string data;
        std::getline(primFile, data, char(0));
        rootData["primitives"].push_back(data);
    }

    add_partials(rootData);

    mustache allInline{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy
from enum import Enum

{{#primitives}}
{{.}}
{{/primitives}}

{{#all_definitions}}
{{>print_type_definition}}
{{/all_definitions}}

)py"};

    std::ofstream outputCommon = openOfstream(_destinationPath / "entgen/inline.py");
    allInline.render(rootData, outputCommon);

    mustache all{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *

{{#all_definitions}}{{#schema.object}}
from .{{schema.type_name}} import *{{/schema.object}}{{#schema.enum}}
from .{{schema.type_name}} import *{{/schema.enum}}
{{/all_definitions}}
from .Bool import *
from .EntityRef import *
from .Float import *
from .Int import *
from .String import *

)py"};

    std::ofstream outputAll = openOfstream(_destinationPath / "entgen/_all.py");
    all.render(rootData, outputAll);

    copy_file(_resourcePath / "entgen_helpers.py", _destinationPath / "entgen_helpers.py");
    std::ofstream init1(_destinationPath / "__init__.py");
    std::ofstream init2(_destinationPath / "entgen" / "__init__.py");
    for (auto&& file : {"Bool.py", "EntityRef.py", "Float.py", "Int.py", "String.py"})
    {
        copy_file(_resourcePath / "entgen" / file, _destinationPath / "entgen" / file);
    }
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

    void print_order()
    {
        for (auto const& ele : order)
        {
            std::cout << ele << " -> ";
        }
    }
};

int main(int argc, char* argv[])
try
{
    if (argc < 3)
    {
        fprintf(stderr, "Missing resourcesPath and destinationPath arguments");
        return EXIT_FAILURE;
    }
    auto resourcePath = std::filesystem::path(argv[1]);
    auto destinationPath = std::filesystem::path(argv[2]);

    Ent::EntityLib entlib("X:/", true);

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

    std::error_code er;
    std::filesystem::remove_all(destinationPath, er);
    std::filesystem::create_directories(destinationPath);

    auto getTypeID = [](json const& type) {
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
            for (auto& include : refSchema["schema"]["includes"])
            {
                if (include["ref"].is_object())
                {
                    auto ref = include["ref"]["name"].get<std::string>();
                    if (nameToSchema.count(ref) != 0)
                    {
                        g.addEdge(ref, type_name);
                    }
                }
                else if (include["array"].is_object())
                {
                    auto ref = include["array"]["type"]["ref"]["name"].get<std::string>();
                    if (nameToSchema.count(ref) != 0)
                    {
                        g.addEdge(ref, type_name);
                    }
                }
            }
        }
    }

    // topological sort schema types
    g.topological_dfs();

    // Transfert nameToSchema into allDefinitions
    for (auto& id : g.getOrder())
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
    {
        std::ofstream schemaOutput = openOfstream(destinationPath / "schemaOutput.json");
        schemaOutput << allDefinitions.dump(4);
    }

    gencpp(resourcePath / "cpp", destinationPath / "cpp");
    genpy(resourcePath / "py", destinationPath / "py");
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
