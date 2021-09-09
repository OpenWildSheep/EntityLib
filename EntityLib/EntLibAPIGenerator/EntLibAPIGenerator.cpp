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
#include "../EntityLib/external/filesystem.hpp"
#include "external/Mustache/mustache.hpp"
#include "../EntityLib/external/json.hpp"
#pragma warning(pop)

using namespace kainjow::mustache;
using namespace nlohmann;
using namespace std::filesystem;

constexpr auto overwrite = copy_options::overwrite_existing;

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

data jsonToMustache(json const& j)
{
    switch (j.type())
    {
    case json::value_t::array:
    {
        data result(data::type::list);
        for (auto&& elt : j)
        {
            result.push_back(jsonToMustache(elt));
        }
        return result;
    }
    case json::value_t::object:
    {
        data result(data::type::object);
        for (auto&& [k, v] : j.items())
        {
            result.set(k, jsonToMustache(v));
        }
        return result;
    }
    case json::value_t::boolean: return data(j.get<bool>());
    case json::value_t::number_float: return data(std::to_string(j.get<double>()));
    case json::value_t::number_integer: return data(std::to_string(j.get<int64_t>()));
    case json::value_t::number_unsigned: return data(std::to_string(j.get<uint64_t>()));
    case json::value_t::string: return data(j.get<std::string>());
    }
    return data(false);
}

static std::string replaceAll(std::string link, std::string const& before, std::string const& after)
{
    size_t pos = 0;
    while (pos != std::string::npos)
    {
        pos = link.find(before);
        if (pos != std::string::npos)
        {
            link = link.substr(0, pos) + after + link.substr(pos + before.size());
        }
    }
    return link;
}

static std::string escapeName(std::string _name)
{
    std::string name = _name;
    static std::set<std::string> cppKeywordTypes = {
        "float", "bool", "from", "in", "None", "Type", "throw", "do", "default"};

    std::regex eastlNS(R"regex(eastl::(\w+))regex");
    name = std::regex_replace(name, eastlNS, "$1");
    std::regex vector(R"regex(vector\<(\w+)\>)regex");
    std::string name2;
    while (name2 != name)
    {
        name2 = std::regex_replace(name, vector, "$1Vec");
        std::swap(name, name2);
    }
    name = replaceAll(name, "::", "_");
    name = replaceAll(name, "<", "_");
    name = replaceAll(name, ">", "_");
    name = replaceAll(name, ",", "_");
    if (cppKeywordTypes.count(name) != 0)
    {
        return name + '_';
    }
    return name;
}

// Enum type are defined several times. "overwrite" is used to merge them is one
static void addDef(
    std::string const& _name,
    Ent::Subschema const* _def,
    std::string const& _scope,
    bool _overwrite = false)
{
    auto escapedName = escapeName(_name);
    if (allDefs.count(escapedName) == 0)
    {
        allDefs[escapedName] = _def;
        schemaName[_def] = escapedName;
    }
    else if (_overwrite)
    {
        // Check if there is two enum at with the same name
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

static std::string getRefTypeName(std::string link)
{
    link = escapeName(link);

    // Force to create the definition (do nothing if already exist)
    static char const* definitionsStr = "#/definitions/";
    size_t pos = link.find(definitionsStr);
    if (pos == std::string::npos)
    {
        return link;
    }
    return link.substr(pos + strlen(definitionsStr));
}

static json makeNewType()
{
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

static json getSchemaRefType(Ent::SubschemaRef const& ref);

auto prim = [](char const* name) {
    json type = makeNewType();
    json ref;
    ref["name"] = (char)toupper(name[0]) + std::string((name + 1));
    if (name == std::string("String"))
    {
        ref["py_native"] = "str";
        ref["cpp_native"] = "char const*";
    }
    else if (name == std::string("Int"))
    {
        ref["py_native"] = "int";
        ref["cpp_native"] = "int64_t";
    }
    ref["settable"] = true;
    type["ref"] = std::move(ref);
    return type;
};

static std::set<Ent::DataType> primitiveTypes = {
    Ent::DataType::boolean,
    Ent::DataType::integer,
    Ent::DataType::number,
    Ent::DataType::string,
    Ent::DataType::entityRef};

char const* primitiveName(Ent::DataType type)
{
    switch (type)
    {
    case Ent::DataType::boolean: return "Bool";
    case Ent::DataType::integer: return "Int";
    case Ent::DataType::number: return "Float";
    case Ent::DataType::string: return "String";
    case Ent::DataType::entityRef: return "EntityRef";
    }
    ENTLIB_LOGIC_ERROR("Unexpected DataType");
}

static bool isPrimArray(Ent::Subschema const& ref)
{
    if (auto singularItems = ref.singularItems.get())
    {
        return primitiveTypes.count(singularItems->get().type) != 0;
    }
    else
    {
        return false;
    }
}

static json getSchemaType(Ent::Subschema const& schema)
{
    json type = makeNewType();

    switch (schema.type)
    {
    case Ent::DataType::object:
    {
        std::string typeDispName = schemaName[&schema];
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataType::array:
        if (schema.singularItems != nullptr)
        {
            auto const& meta = schema.meta.get<Ent::Subschema::ArrayMeta>();
            if (meta.overridePolicy == "set")
            {
                auto const singularType = (*schema.singularItems)->type;
                if (singularType == Ent::DataType::oneOf)
                {
                    std::string typeDispName = schemaName.at(&schema);
                    json ref;
                    ref["name"] = typeDispName;
                    type["ref"] = std::move(ref);
                    return type;
                }
                else if (singularType == Ent::DataType::object)
                {
                    json array;
                    array["type"] = getSchemaRefType(*schema.singularItems);
                    auto keyFieldName = schema.meta.get<Ent::Subschema::ArrayMeta>().keyField;
                    auto& keyField = schema.singularItems->get().properties.at(*keyFieldName);
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
                    array["type"] = getSchemaRefType(*schema.singularItems);
                    type["prim_set"] = std::move(array);
                    return type;
                }
            }
            else if (meta.overridePolicy == "map")
            {
                json array;
                auto& pair = *schema.singularItems;
                array["key_type"] = getSchemaRefType(pair->linearItems->at(0));
                array["value_type"] = getSchemaRefType(pair->linearItems->at(1));
                type["map"] = std::move(array);
                return type;
            }
            else if (isPrimArray(schema))
            {
                json array;
                array["type"] = getSchemaRefType(*schema.singularItems);
                type["prim_array"] = std::move(array);
                return type;
            }
            else
            {
                json array;
                array["type"] = getSchemaRefType(*schema.singularItems);
                type["array"] = std::move(array);
                return type;
            }
        }
        else
        {
            json tuple;
            json types(json::value_t::array);
            size_t index = 0;

            for (auto& itemRef : *schema.linearItems)
            {
                auto subtype = getSchemaRefType(itemRef);
                if (index != schema.linearItems->size() - 1)
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
        std::string typeDispName = schemaName[&schema];
        json ref;
        ref["name"] = typeDispName;
        type["ref"] = std::move(ref);
        return type;
    }
    case Ent::DataType::boolean:
    case Ent::DataType::integer:
    case Ent::DataType::number:
    case Ent::DataType::string:
    case Ent::DataType::entityRef:
        if (auto iter = schemaName.find(&schema); iter != schemaName.end())
        {
            std::string const& typeDispName = iter->second;
            json ref;
            ref["name"] = typeDispName;
            type["ref"] = std::move(ref);
            // It works because in the schema, Enums are always strings
            type["ref"]["py_native"] = schema.name.empty() ? "str" : schema.name + "Enum";
            type["ref"]["cpp_native"] = schema.name.empty() ? "char const*" : schema.name + "Enum";
            type["ref"]["settable"] = true;
            return type;
        }
        else
        {
            return prim(primitiveName(schema.type));
        }
    }
    return json{};
}

static json getSchemaRefType(Ent::SubschemaRef const& ref)
{
    if (ref.subSchemaOrRef.is<Ent::Subschema>())
    {
        return getSchemaType(*ref);
    }
    else
    {
        std::string singItmRef = ref.subSchemaOrRef.get<Ent::SubschemaRef::Ref>().ref;
        auto name = getRefTypeName(singItmRef);
        json typeref;
        typeref["name"] = name;
        typeref["settable"] = isPrimArray(*ref) or primitiveTypes.count(ref->type) != 0;
        json type = makeNewType();
        type["ref"] = std::move(typeref);
        return type;
    }
}

static json getSchemaData(Ent::Subschema const& schema)
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
    // defData["array"] = false; // Always an alias
    // defData["prim_array"] = false; // Always an alias
    // defData["prim_set"] = false;  // Always an alias
    // defData["ref"] = false;   // A definition can't be a ref

    switch (schema.type)
    {
    case Ent::DataType::array:
        if (schema.singularItems != nullptr)
        {
            auto const& meta = schema.meta.get<Ent::Subschema::ArrayMeta>();
            if (meta.overridePolicy == "set")
            {
                auto const singularType = (*schema.singularItems)->type;
                if (singularType == Ent::DataType::oneOf)
                {
                    Ent::Subschema const& unionSchema = **schema.singularItems;
                    defData["union_set"] = getSchemaData(unionSchema);
                    defData["union_set"]["items"]["union_set"] =
                        getSchemaRefType(*schema.singularItems);
                    break;
                }
                else if (singularType == Ent::DataType::object)
                {
                    Ent::Subschema const& unionSchema = **schema.singularItems;
                    defData["object_set"] = getSchemaData(unionSchema);
                    defData["object_set"]["items"] = getSchemaRefType(*schema.singularItems);
                    break;
                }
                else if (
                    singularType == Ent::DataType::boolean || singularType == Ent::DataType::entityRef
                    || singularType == Ent::DataType::integer || singularType == Ent::DataType::number
                    || singularType == Ent::DataType::string)
                {
                    // A primitive set is a native type so it is just an alias
                    json alias(json::value_t::object);
                    alias["type"] = getSchemaType(schema);
                    defData["alias"] = std::move(alias);
                    break;
                }
            }
            else if (meta.overridePolicy == "map")
            {
                Ent::Subschema const& unionSchema = **schema.singularItems;
                defData["map"] = getSchemaData(unionSchema);
                defData["map"]["items"] = getSchemaRefType(*schema.singularItems);
                break;
            }
            else
            {
                json alias(json::value_t::object);
                alias["type"] = getSchemaType(schema);
                defData["alias"] = std::move(alias);
                break;
            }
        }
        else
        {
            json tuple;
            json types(json::value_t::array);
            size_t index = 0;

            for (auto& itemRef : *schema.linearItems)
            {
                auto subtype = getSchemaRefType(itemRef);
                if (index != schema.linearItems->size() - 1)
                {
                    subtype["comma"] = true;
                }
                subtype["index"] = index;
                types.push_back(subtype);
                ++index;
            }
            tuple["types"] = std::move(types);
            defData["tuple"] = std::move(tuple);
            break;
        }
    case Ent::DataType::boolean:
    case Ent::DataType::entityRef:
    case Ent::DataType::integer:
    case Ent::DataType::number:
    case Ent::DataType::string:
    {
        if (not schema.enumValues.empty())
        {
            json enumNode(json::value_t::object);
            enumNode["type"] = prim("String");
            enumNode["type"]["ref"]["cpp_native"] = schema.name + "Enum";
            enumNode["type"]["ref"]["py_native"] = schema.name + "Enum";
            size_t idx = 0;
            for (auto&& val : schema.enumValues)
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
        alias["type"] = prim(primitiveName(schema.type));
        defData["alias"] = std::move(alias);
        break;
    }
    case Ent::DataType::object:
    {
        json object(json::value_t::object);
        json properties(json::value_t::array);
        std::set<json> includes;
        for (auto& [propName, propRef] : schema.properties)
        {
            json prop(json::value_t::object);
            auto propData = getSchemaRefType(propRef);
            prop["prop_name"] = escapeName(propName);
            prop["type"] = std::move(propData);
            properties.push_back(prop);
            includes.emplace(getSchemaRefType(propRef));
        }
        object["properties"] = std::move(properties);
        object["includes"] = includes;
        defData["object"] = std::move(object);
        break;
    }
    case Ent::DataType::oneOf:
    {
        json union_(json::value_t::object);
        json types(json::value_t::array);
        auto const& unionData = schema.meta.get<Ent::Subschema::UnionMeta>();
        for (Ent::SubschemaRef const& ref : *schema.oneOf)
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

#pragma warning(disable : 4702)

static void giveNameToAnonymousObject(
    Ent::Subschema const& subschema, std::string const& hint, std::string const& morehint);

static void giveNameToAnonymousObjectRef(
    Ent::SubschemaRef const& ref, std::string const& hint, std::string const& hint2)
{
    if (ref.subSchemaOrRef.is<Ent::Subschema>())
    {
        if (ref->type == Ent::DataType::object)
        {
            addDef(hint, &(*ref), hint2);
        }
        else if (ref->type == Ent::DataType::oneOf)
        {
            addDef(hint, &(*ref), hint2);
        }
        else if (ref->type == Ent::DataType::array)
        {
            if (ref->singularItems != nullptr)
            {
                auto const& meta = ref->meta.get<Ent::Subschema::ArrayMeta>();
                if (meta.overridePolicy == "set")
                {
                    if ((*ref->singularItems)->type == Ent::DataType::oneOf)
                    {
                        addDef(hint, &(*ref), hint2);
                    }
                }
            }
        }
        else if (not ref->enumValues.empty())
        {
            if (not ref->name.empty())
            {
                // The same enum can be descibe several time
                // TODO : Loïc : Fix the export of enums in Wild (Export each enum only one time, like classes)
                addDef(ref->name, &(*ref), "", true);
            }
            else
            {
                addDef(hint, &(*ref), hint2);
            }
        }
        giveNameToAnonymousObject(*ref, hint, hint2);
    }
}

static void giveNameToAnonymousObject(
    Ent::Subschema const& subschema, std::string const& hint, std::string const& morehint)
{
    switch (subschema.type)
    {
    case Ent::DataType::boolean:
    case Ent::DataType::entityRef:
    case Ent::DataType::integer:
    case Ent::DataType::number:
    case Ent::DataType::string: return;
    case Ent::DataType::array:
        if (subschema.linearItems.has_value())
        {
            size_t index = 0;
            for (auto& subref : *subschema.linearItems)
            {
                giveNameToAnonymousObjectRef(subref, hint + "_" + char('A' + index), morehint);
            }
            ++index;
        }
        if (subschema.singularItems != nullptr)
        {
            giveNameToAnonymousObjectRef(*subschema.singularItems, hint + "Item", morehint);
        }
        break;
    case Ent::DataType::oneOf:
    {
        auto const& unionData = subschema.meta.get<Ent::Subschema::UnionMeta>();
        for (Ent::SubschemaRef const& subref : *subschema.oneOf)
        {
            auto typeField = unionData.typeField.empty() ? "Type" : unionData.typeField;
            auto dataField = unionData.dataField.empty() ? "Data" : unionData.dataField;
            auto acceptedType = subref.get().properties.at(typeField)->constValue->get<std::string>();
            Ent::SubschemaRef const& subschemaref = subref.get().properties.at(dataField);
            giveNameToAnonymousObjectRef(subschemaref, typeField, hint);
        }
        break;
    }
    case Ent::DataType::object:
        for (auto& [propName, propRef] : subschema.properties)
        {
            giveNameToAnonymousObjectRef(propRef, propName, hint);
        }
        break;
    }
}

void gencpp(std::filesystem::path const& resourcePath, std::filesystem::path const& destinationPath)
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
        struct {{schema.display_type}};{{/schema.object}}{{#schema.union}}
        struct {{schema.display_type}}; // Union{{/schema.union}}{{#schema.tuple}}
        using {{schema.display_type}} = {{>tuple_type}}; // Tuple{{/schema.tuple}}{{#schema.union_set}}
        struct {{schema.display_type}}; // union_set{{/schema.union_set}}{{#schema.object_set}}
        struct {{schema.display_type}}; // object_set{{/schema.object_set}}{{#schema.enum}}
        struct {{schema.display_type}}; // enum
        enum class {{schema.display_type}}Enum
        {
            {{#values}}{{escaped_name}},
            {{/values}}
        };{{/schema.enum}}{{/all_definitions}}
        {{#all_definitions}}{{#schema.alias}}
        using {{schema.display_type}} = {{#type}}{{>display_type}}{{/type}};{{/schema.alias}}{{/all_definitions}}

        {{#all_definitions}}{{#schema.object}}
        struct {{schema.display_type}} : Base // Object
        {
	        {{schema.display_type}}(Ent::Node* _node): Base(_node) {}
        {{#properties}}    {{#type}}{{>display_type}}{{/type}} {{prop_name}}() const;
        {{/properties}}
        };{{/schema.object}}{{#schema.enum}}
        struct {{schema.display_type}} : EnumPropHelper<{{schema.display_type}}, {{schema.display_type}}Enum> // Enum
        {
            using Enum = {{schema.display_type}}Enum;
            using PropHelper<{{schema.display_type}}, Enum>::operator=;
	        {{schema.display_type}}(Ent::Node* _node): EnumPropHelper<{{schema.display_type}}, Enum>(_node) {}
            static constexpr char* enumToString[] = {
                {{#values}}"{{name}}",
                {{/values}}
            };
        };
        char const* toInternal({{schema.display_type}}Enum value)
        {
            if(size_t(value) >= std::size({{schema.display_type}}::enumToString))
                throw std::runtime_error("Wrong enum value");
            return {{schema.display_type}}::enumToString[size_t(value)];
        }
        {{/schema.enum}}{{#schema.union}}
        struct {{schema.display_type}} : Base // Union
        {
	        {{schema.display_type}}(Ent::Node* _node): Base(_node) {}
            char const* getType() const;{{#types}}
            {{#type}}{{>display_type}}{{/type}} {{name}}() const;
            {{#type}}{{>display_type}}{{/type}} set{{name}}() const;
        {{/types}}
        };{{/schema.union}}{{#schema.union_set}}{{#union}}
        struct {{schema.display_type}} : UnionSetBase<{{schema.display_type}}> // union_set
        {
	        {{schema.display_type}}(Ent::Node* _node)
                : UnionSetBase<{{schema.display_type}}>(_node)
            {
            }
            char const* getType() const;{{#types}}
            {{#type}}{{>display_type}}{{/type}} {{name}}() const;
            {{#type}}{{>display_type}}{{/type}} add{{name}}() const;
        {{/types}}
        };{{/union}}{{/schema.union_set}}

{{/all_definitions}}

        {{#all_definitions}}{{#schema.object}}// {{schema.display_type}}
        {{#properties}}inline {{#type}}{{>display_type}}{{/type}} {{schema.display_type}}::{{prop_name}}() const
        {
	        return {{#type}}{{>display_type}}{{/type}}(node->at("{{prop_name}}"));
        }
        {{/properties}}{{/schema.object}}{{#schema.union}}// {{schema.display_type}}
        inline char const* {{schema.display_type}}::getType() const
        {
            return node->getUnionType();
        }
        {{#types}}inline {{#type}}{{>display_type}}{{/type}} {{schema.display_type}}::{{name}}() const
        {
	        return {{#type}}{{>display_type}}{{/type}}(node->getUnionData());
        }
        inline {{#type}}{{>display_type}}{{/type}} {{schema.display_type}}::set{{name}}() const
        {
	        return {{#type}}{{>display_type}}{{/type}}(node->setUnionType("{{schema.display_type}}"));
        }
        {{/types}}
{{/schema.union}}{{#schema.union_set}}{{#union}}// {{schema.display_type}}
        inline char const* {{schema.display_type}}::getType() const
        {
            return node->getUnionType();
        }
        {{#types}}inline {{#type}}{{>display_type}}{{/type}} {{schema.display_type}}::{{name}}() const
        {
	        return {{#type}}{{>display_type}}{{/type}}(get("{{name}}"));
        }
        inline {{#type}}{{>display_type}}{{/type}} {{schema.display_type}}::add{{name}}() const
        {
	        return {{#type}}{{>display_type}}{{/type}}(add("{{name}}"));
        }
        {{/types}}
{{/union}}{{/schema.union_set}}
        {{/all_definitions}}
    } // Gen
} // Ent
)cpp"};

    create_directories(destinationPath);
    std::ofstream output = openOfstream(destinationPath / "EntGen.h");
    tmpl.render(rootData, output);
    copy_file(resourcePath / "EntGenHelpers.h", destinationPath / "EntGenHelpers.h", overwrite);
}

void genpy(std::filesystem::path const& resourcePath, std::filesystem::path const& destinationPath)
{
    create_directories(destinationPath / "entgen");

    auto add_partials = [](data& root) {
        root["display_type"] = partial([]() {
            return R"({{#object_set}}ObjectSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/object_set}})"
                   R"({{#prim_set}}PrimitiveSet[{{type.ref.cpp_native}}]{{/prim_set}})"
                   R"({{#map}}Map[{{key_type.ref.py_native}}, {{#value_type}}{{>display_type_comma}}{{/value_type}}]{{/map}})"
                   R"({{#ref}}{{name}}{{/ref}})"
                   R"({{#array}}Array[{{#type}}{{>display_type_comma}}{{/type}}]{{/array}})"
                   R"({{#prim_array}}PrimArray[{{#type}}{{>display_type_comma}}{{/type}}]{{/prim_array}})"
                   R"({{#union_set}}UnionSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/union_set}})"
                   R"({{#tuple}}TupleNode[{{#types}}Type[{{>display_type}}]{{#comma}}, {{/comma}}{{/types}}]{{/tuple}})";
        });

        root["display_type_comma"] = partial([]() {
            return R"({{>display_type}})"
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
                   R"({{#union_set}}(lambda n: UnionSet({{#type}}{{>type_ctor}}{{/type}}, n)){{/union_set}})"
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

{{#file_schema}}{{#schema.union_set}}{{schema.display_type}} = UnionSet
{{/schema.union_set}}{{#schema.object_set}}
class {{schema.display_type_comma}}(UnionSet):
    pass
{{/schema.object_set}}{{#schema.enum}}
class {{schema.display_type}}Enum(Enum):
    {{#values}}{{escaped_name}} = "{{name}}"
    {{/values}}


{{/schema.enum}}{{/file_schema}}

{{#file_schema}}
{{#schema.alias}}
{{schema.display_type}} = {{#type}}{{>type_ctor}}{{/type}}{{/schema.alias}}{{/file_schema}}
{{#file_schema}}
{{#schema.object}}
{{#includes}}
{{>print_import}}
{{/includes}}

class {{schema.display_type}}(Base):
{{#properties}}{{#type}}    @property
    def {{prop_name}}(self): return {{>type_ctor}}(self._node.at("{{prop_name}}")){{#prim_array}}
    @{{prop_name}}.setter
    def {{prop_name}}(self, val): self.{{prop_name}}.set(val)
{{/prim_array}}{{#ref.settable}}
    @{{prop_name}}.setter
    def {{prop_name}}(self, val): self.{{prop_name}}.set(val)
{{/ref.settable}}{{/type}}
{{/properties}}    pass


{{/schema.object}}{{#schema.union}}class {{schema.display_type}}(Union):
    pass


{{/schema.union}}{{#schema.enum}}class {{schema.display_type}}(Primitive[{{schema.display_type}}Enum]):  # Enum
    def __init__(self, node):
        super().__init__({{schema.display_type}}Enum, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> {{schema.display_type}}
        return {{schema.display_type}}(node)
    def set(self, val):  # type: ({{schema.display_type}}Enum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


{{/schema.enum}}{{#schema.tuple}}class {{schema.display_type}}(TupleNode[Tuple[{{#types}}Type[{{>display_type}}]{{#comma}}, {{/comma}}{{/types}}]]):
    def __init__(self, node : EntityLibPy.Node = None):
        super().__init__((Int, Int, Float, Float, Float), node)

{{#types}}    def get_{{index}}(self):  # type: () -> {{>display_type}}
        return {{>type_ctor}}(self._node.at({{index}}))
{{/types}}

{{/schema.tuple}}{{/file_schema}}

)py"};
        auto shortTypeName = refSchema["schema"]["display_type"].get<std::string>();
        std::ofstream output = openOfstream(destinationPath / "entgen" / (shortTypeName + ".py"));
        tmpl.render(rootData, output);
    }

    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);

    add_partials(rootData);

    mustache allInline{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy
from enum import Enum

{{#all_definitions}}{{#schema.union_set}}{{schema.display_type}} = UnionSet
{{/schema.union_set}}{{#schema.object_set}}
class {{schema.display_type_comma}}(UnionSet):
    pass
{{/schema.object_set}}{{#schema.enum}}
class {{schema.display_type}}Enum(Enum):
    {{#values}}{{escaped_name}} = "{{name}}"
    {{/values}}


{{/schema.enum}}{{/all_definitions}}{{#all_definitions}}{{#schema.alias}}{{schema.display_type}} = {{#type}}{{>type_ctor}}{{/type}}  # alias
{{/schema.alias}}{{/all_definitions}}


{{#all_definitions}}{{#schema.object}}class {{schema.display_type}}(Base):
{{#properties}}{{#type}}    @property
    def {{prop_name}}(self): return {{>type_ctor}}(self._node.at("{{prop_name}}")){{#prim_array}}
    @{{prop_name}}.setter
    def {{prop_name}}(self, val): self.{{prop_name}}.set(val)
{{/prim_array}}{{#ref.settable}}
    @{{prop_name}}.setter
    def {{prop_name}}(self, val): self.{{prop_name}}.set(val)
{{/ref.settable}}{{/type}}
{{/properties}}    pass


{{/schema.object}}{{#schema.union}}class {{schema.display_type}}(Union):
    pass


{{/schema.union}}{{#schema.enum}}class {{schema.display_type}}(Primitive[{{schema.display_type}}Enum]):  # Enum
    def __init__(self, node):
        super().__init__({{schema.display_type}}Enum, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> {{schema.display_type}}
        return {{schema.display_type}}(node)
    def set(self, val):  # type: ({{schema.display_type}}Enum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


{{/schema.enum}}{{#schema.tuple}}class {{schema.display_type}}(TupleNode[Tuple[{{#types}}Type[{{>display_type}}]{{#comma}}, {{/comma}}{{/types}}]]):
    def __init__(self, node : EntityLibPy.Node = None):
        super().__init__((Int, Int, Float, Float, Float), node)

{{#types}}    def get_{{index}}(self):  # type: () -> {{>display_type}}
        return {{>type_ctor}}(self._node.at({{index}}))
{{/types}}

{{/schema.tuple}}{{/all_definitions}}

Entity = Object

)py"};

    std::ofstream outputCommon = openOfstream(destinationPath / "entgen/inline.py");
    allInline.render(rootData, outputCommon);

    mustache all{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *

{{#all_definitions}}{{#schema.object}}
from .{{schema.display_type}} import *{{/schema.object}}{{#schema.enum}}
from .{{schema.display_type}} import *{{/schema.enum}}
{{/all_definitions}}
from .Bool import *
from .EntityRef import *
from .Float import *
from .Int import *
from .String import *

Entity = Object

)py"};

    std::ofstream outputAll = openOfstream(destinationPath / "entgen/_all.py");
    all.render(rootData, outputAll);

    copy_file(resourcePath / "entgen_helpers.py", destinationPath / "entgen_helpers.py", overwrite);
    for (auto&& file : {"Bool.py", "EntityRef.py", "Float.py", "Int.py", "String.py"})
    {
        copy_file(resourcePath / "entgen" / file, destinationPath / "entgen" / file, overwrite);
    }
}

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
        defData["display_type"] = shortTypeName;
        json refSchema(json::value_t::object);
        refSchema["schema"] = std::move(defData);
        allDefinitions.push_back(refSchema);
    }

    // Export the mustache json input (for debug purpose)
    {
        std::ofstream schemaOutput = openOfstream(destinationPath / "schemaOutput.json");
        schemaOutput << allDefinitions.dump(4);
    }

    std::error_code er;
    std::filesystem::remove_all(destinationPath, er);
    std::filesystem::create_directories(destinationPath);
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
