#include <ComponentMerge.h>
#include <EntityLib.h>

#include <cassert>
#include <ciso646>
#include <fstream>
#include <set>
#include <map>
#include <optional>

#pragma warning(push, 0)
#include <iostream>
#include "../EntityLib/external/filesystem.hpp"
#include "external/Mustache/mustache.hpp"
#include "../EntityLib/external/json.hpp"
#pragma warning(pop)

using namespace kainjow::mustache;
using namespace nlohmann;

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
            result.set(k.c_str(), jsonToMustache(v));
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

std::map<std::string, Ent::Subschema const*> allDefs;
std::map<Ent::Subschema const*, std::string> schemaName;

static void addDef(std::string const& name, Ent::Subschema const* def, std::string const& scope)
{
    if (allDefs.count(name) == 0)
    {
        allDefs[name] = def;
        schemaName[def] = name;
    }
    else
    {
        std::string hint2 = scope + "_" + name;
        while (allDefs.count(hint2) != 0)
        {
            hint2 = '_' + hint2;
        }
        allDefs[hint2] = def;
        schemaName[def] = hint2;
    }
}

static std::set<std::string> cppKeywordTypes = {"float", "bool", "from", "in", "None"};

static std::string escapeName(std::string name)
{
    name = replaceAll(name, "::", "_");
    name = replaceAll(name, "<", "_");
    name = replaceAll(name, ">", "_");
    name = replaceAll(name, ",", "_");
    if (cppKeywordTypes.count(name) != 0)
    {
        return "_" + name;
    }
    return name;
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

static json getSchemaType(Ent::Subschema const& schema)
{
    json type = makeNewType();
    auto prim = [](char const* name) {
        json type = makeNewType();
        json ref;
        ref["name"] = (char)toupper(name[0]) + std::string((name + 1));
        type["ref"] = std::move(ref);
        return type;
    };

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
            json array;
            array["type"] = getSchemaRefType(*schema.singularItems);
            type["array"] = std::move(array);
            return type;
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
    case Ent::DataType::boolean: return prim("Bool");
    case Ent::DataType::integer: return prim("Int");
    case Ent::DataType::number: return prim("Float");
    case Ent::DataType::string: return prim("String");
    case Ent::DataType::entityRef: return prim("EntityRef");
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
    defData["array"] = false;
    defData["union_set"] = false;
    defData["object_set"] = false;
    defData["prim_set"] = false;
    defData["ref"] = false;
    defData["tuple"] = false;
    defData["union"] = false;
    defData["map"] = false;
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
                    Ent::Subschema const& unionSchema = **schema.singularItems;
                    defData["prim_set"] = getSchemaData(unionSchema);
                    defData["prim_set"]["items"] = getSchemaRefType(*schema.singularItems);
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
        json alias(json::value_t::object);
        alias["type"] = getSchemaType(schema);
        defData["alias"] = std::move(alias);
        break;
    }
    case Ent::DataType::object:
    {
        json object(json::value_t::object);
        json properties(json::value_t::array);
        for (auto& [propName, propRef] : schema.properties)
        {
            json prop(json::value_t::object);
            auto propData = getSchemaRefType(propRef);
            prop["prop_name"] = escapeName(propName);
            prop["type"] = std::move(propData);
            properties.push_back(prop);
        }
        object["properties"] = std::move(properties);
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
    Ent::Subschema const& ref, std::string const& hint, std::string const& hint2);

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

void gencpp()
{
    Ent::EntityLib entlib("X:/", true);

    for (auto& [defName, def] : entlib.schema.schema.allDefinitions)
    {
        addDef(getRefTypeName(defName), &def, "");
    }

    for (auto& [defName, def] : entlib.schema.schema.allDefinitions)
    {
        giveNameToAnonymousObject(def, getRefTypeName(defName), "");
    }

    json allDefinitions(json::value_t::array);
    for (auto& [defName, def] : allDefs)
    {
        auto shortTypeName = getRefTypeName(defName.c_str());
        json defData = getSchemaData(*def);
        defData["display_type"] = shortTypeName;
        json refSchema(json::value_t::object);
        refSchema["schema"] = std::move(defData);
        allDefinitions.push_back(refSchema);
    }

    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);
    rootData["tuple_type"] =
        partial([]() { return R"cpp(Ent::Gen::Tuple<{{#types}}{{>display_type}}{{/types}}>)cpp"; });
    rootData["prim_set_type"] = partial(
        []() { return R"cpp(Ent::Gen::PrimitiveSet<{{#type}}{{>display_type}}{{/type}}>)cpp"; });
    rootData["object_set_type"] =
        partial([]() { return R"cpp(Ent::Gen::ObjectSet<{{#type}}{{>display_type}}{{/type}}>)cpp"; });
    rootData["map_type"] = partial([]() {
        return R"cpp(Ent::Gen::Map<{{#key_type}}{{>display_type}}{{/key_type}}, {{#value_type}}{{>display_type}}{{/value_type}}>)cpp";
    });
    rootData["display_type"] = partial([]() {
        return R"cpp({{#object_set}}{{>object_set_type}}{{/object_set}}{{#prim_set}}{{>prim_set_type}}{{/prim_set}}{{#map}}{{>map_type}}{{/map}}{{#ref}}Ent::Gen::{{name}}{{/ref}}{{#array}}Array<{{#type}}{{>display_type}}{{/type}}>{{/array}}{{#union_set}}UnionSet<{{#type}}{{>display_type}}{{/type}}>{{/union_set}}{{#tuple}}{{>tuple_type}}{{/tuple}}{{#comma}}, {{/comma}})cpp";
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
        struct {{schema.display_type}}; // object_set{{/schema.object_set}}{{/all_definitions}}
        {{#all_definitions}}{{#schema.alias}}
        using {{schema.display_type}} = {{#type}}{{>display_type}}{{/type}};{{/schema.alias}}{{/all_definitions}}

        {{#all_definitions}}{{#schema.object}}
        struct {{schema.display_type}} : Base // Object
        {
	        {{schema.display_type}}(Ent::Node* _node): Base(_node) {}
        {{#properties}}    {{#type}}{{>display_type}}{{/type}} {{prop_name}}() const;
        {{/properties}}
        };{{/schema.object}}{{#schema.union}}
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

    std::ofstream output("cpp/EntGen.h");
    tmpl.render(rootData, output);
}

void genpy()
{
    Ent::EntityLib entlib("X:/", true);

    for (auto& [defName, def] : entlib.schema.schema.allDefinitions)
    {
        addDef(getRefTypeName(defName), &def, "");
    }

    for (auto& [defName, def] : entlib.schema.schema.allDefinitions)
    {
        giveNameToAnonymousObject(def, getRefTypeName(defName), "");
    }

    auto add_partials = [](data& root) {
        root["display_type"] = partial([]() {
            return R"({{#object_set}}ObjectSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/object_set}})"
                   R"({{#prim_set}}PrimitiveSet[{{#type}}{{>display_type_comma}}{{/type}}]{{/prim_set}})"
                   R"({{#map}}Map[{{#value_type}}{{>display_type_comma}}{{/value_type}}]{{/map}})"
                   R"({{#ref}}{{name}}{{/ref}})"
                   R"({{#array}}Array[{{#type}}{{>display_type_comma}}{{/type}}]{{/array}})"
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
                   R"({{#prim_set}}(lambda n: PrimitiveSet({{#type}}{{>type_ctor}}{{/type}}, n)){{/prim_set}})"
                   R"({{#map}}(lambda n: Map({{#value_type}}{{>type_ctor}}{{/value_type}}, n)){{/map}})"
                   R"({{#ref}}{{name}}{{/ref}})"
                   R"({{#array}}(lambda n: Array({{#type}}{{>type_ctor}}{{/type}}, n)){{/array}})"
                   R"({{#union_set}}(lambda n: UnionSet({{#type}}{{>type_ctor}}{{/type}}, n)){{/union_set}})"
                   R"({{#tuple}}TupleNode{{/tuple}})";
        });
        root["print_import"] = partial([]() {
            return R"({{#object_set}}{{#type}}{{>print_import}}{{/type}}{{/object_set}})"
                   R"({{#prim_set}}{{#type}}{{>print_import}}{{/type}}{{/prim_set}})"
                   R"({{#map}}{{#value_type}}{{>print_import}}{{/value_type}}{{/map}})"
                   R"({{#ref}}from entgen.{{name}} import *
{{/ref}})"
                   R"({{#array}}{{#type}}{{>print_import}}{{/type}}{{/array}})";
        });
    };

    json allDefinitions(json::value_t::array);
    for (auto& [defName, def] : allDefs)
    {
        auto shortTypeName = getRefTypeName(defName.c_str());
        json defData = getSchemaData(*def);
        defData["display_type"] = shortTypeName;
        json refSchema(json::value_t::object);
        refSchema["schema"] = std::move(defData);
        allDefinitions.push_back(refSchema);

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
{{/schema.object_set}}{{#schema.prim_set}}
class {{schema.display_type_comma}}(UnionSet):
    pass
{{/schema.prim_set}}{{/file_schema}}

{{#file_schema}}{{#schema.alias}}{{schema.display_type}} = {{#type}}{{>type_ctor}}{{/type}}
{{/schema.alias}}{{/file_schema}}


{{#file_schema}}{{#schema.object}}
{{#properties}}{{#type}}{{>print_import}}{{/type}}
{{/properties}}

class {{schema.display_type}}(Base):
{{#properties}}{{#type}}    @property
    def {{prop_name}}(self): return {{>type_ctor}}(self._node.at("{{prop_name}}"))
{{/type}}
{{/properties}}    pass


{{/schema.object}}{{#schema.union}}class {{schema.display_type}}(Union):
    pass


{{/schema.union}}{{#schema.tuple}}class {{schema.display_type}}(TupleNode[Tuple[{{#types}}Type[{{>display_type}}]{{#comma}}, {{/comma}}{{/types}}]]):
    def __init__(self, node : EntityLibPy.Node = None):
        super().__init__((Int, Int, Float, Float, Float), node)

{{#types}}    def get_{{index}}(self):  # type: () -> {{>display_type}}
        return {{>type_ctor}}(self._node.at({{index}}))
{{/types}}

{{/schema.tuple}}{{/file_schema}}

)py"};
        std::ofstream output("py/entgen/" + shortTypeName + ".py");
        tmpl.render(rootData, output);
    }

    {
        std::ofstream schemaOutput("schemaOutput.json");
        schemaOutput << allDefinitions.dump(4);
    }

    data rootData;
    rootData["all_definitions"] = jsonToMustache(allDefinitions);

    add_partials(rootData);

    mustache allInline{R"py(
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

{{#all_definitions}}{{#schema.union_set}}{{schema.display_type}} = UnionSet
{{/schema.union_set}}{{#schema.object_set}}
class {{schema.display_type_comma}}(UnionSet):
    pass
{{/schema.object_set}}{{#schema.prim_set}}
class {{schema.display_type_comma}}(UnionSet):
    pass
{{/schema.prim_set}}{{/all_definitions}}

{{#all_definitions}}{{#schema.alias}}{{schema.display_type}} = {{#type}}{{>type_ctor}}{{/type}}  # alias
{{/schema.alias}}{{/all_definitions}}


{{#all_definitions}}{{#schema.object}}class {{schema.display_type}}(Base):
{{#properties}}{{#type}}    @property
    def {{prop_name}}(self): return {{>type_ctor}}(self._node.at("{{prop_name}}"))
{{/type}}
{{/properties}}    pass


{{/schema.object}}{{#schema.union}}class {{schema.display_type}}(Union):
    pass


{{/schema.union}}{{#schema.tuple}}class {{schema.display_type}}(TupleNode[Tuple[{{#types}}Type[{{>display_type}}]{{#comma}}, {{/comma}}{{/types}}]]):
    def __init__(self, node : EntityLibPy.Node = None):
        super().__init__((Int, Int, Float, Float, Float), node)

{{#types}}    def get_{{index}}(self):  # type: () -> {{>display_type}}
        return {{>type_ctor}}(self._node.at({{index}}))
{{/types}}

{{/schema.tuple}}{{/all_definitions}}

Entity = Object

)py"};

    std::ofstream outputCommon("py/entgen/inline.py");
    allInline.render(rootData, outputCommon);

    mustache all{R"py(
### /!\ This code is GENERATED! Do not modify it.

{{#all_definitions}}{{#schema.object}}from .{{schema.display_type}} import {{schema.display_type}}{{/schema.object}}
{{/all_definitions}}

Entity = Object

)py"};

    std::ofstream outputAll("py/entgen/_all.py");
    all.render(rootData, outputAll);
}

int main()
try
{
    gencpp();
    allDefs.clear();
    schemaName.clear();
    genpy();
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
