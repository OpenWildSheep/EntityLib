#include <iostream>

#include <EntityLib.h>
#include <EntityLib/Property.h>

#pragma warning(push, 0)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "EntityLib/DumpProperty.h"
#include "external/pybind11_json.hpp"
#pragma warning(pop)

/// @cond PRIVATE

namespace py = pybind11;
using namespace Ent;

using Value = std::variant<Null, std::string, double, int64_t, bool, EntityRef>;

Value getValue(Node& node)
{
    switch (node.getDataType())
    {
    case DataType::array:
    case DataType::object:
    case DataType::oneOf:
    case DataType::null: return nullptr;
    case DataType::boolean: return node.getBool();
    case DataType::integer: return node.getInt();
    case DataType::number: return node.getFloat();
    case DataType::string: return std::string(node.getString());
    case DataType::entityRef: return node.getEntityRef();
    case DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
    return {};
}

Value getPropValue(Property const& _prop)
{
    switch (_prop.getDataType())
    {
    case DataType::array:
    case DataType::object:
    case DataType::oneOf:
    case DataType::null: return nullptr;
    case DataType::boolean: return _prop.getBool();
    case DataType::integer: return _prop.getInt();
    case DataType::number: return _prop.getFloat();
    case DataType::string: return std::string(_prop.getString());
    case DataType::entityRef: return _prop.getEntityRef();
    case DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
    return {};
}

Value getDefaultValue(Node& node)
{
    switch (node.getDataType())
    {
    case DataType::array:
    case DataType::object:
    case DataType::oneOf:
    case DataType::null: return nullptr;
    case DataType::boolean: return node.getDefaultBool();
    case DataType::integer: return node.getDefaultInt();
    case DataType::number: return node.getDefaultFloat();
    case DataType::string: return std::string(node.getDefaultString());
    case DataType::entityRef: return node.getDefaultEntityRef();
    case DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
    return {};
}

template <typename I, typename O>
struct Converter
{
    O operator()([[maybe_unused]] I const& _input) const
    {
        throw std::runtime_error(
            std::string("Can't convert") + typeid(I).name() + " to " + typeid(O).name());
    }
};

template <typename IO>
struct Converter<IO, IO>
{
    IO const& operator()(IO const& val) const
    {
        return val;
    }
};

template <>
struct Converter<int64_t, double>
{
    double operator()(int64_t const& val) const
    {
        return static_cast<double>(val);
    }
};

template <>
struct Converter<int64_t, bool>
{
    bool operator()(int64_t const& val) const
    {
        return val != 0;
    }
};

template <typename O>
struct GetValue
{
    template <typename I>
    O operator()(I const& val) const
    {
        return Converter<I, O>{}(val);
    }
};

void setValue(Node& node, Value const& val)
{
    switch (node.getDataType())
    {
    case DataType::array:
    case DataType::object:
    case DataType::oneOf:
    case DataType::null: break;
    case DataType::boolean: node.setBool(std::visit(GetValue<bool>{}, val)); break;
    case DataType::integer: node.setInt(std::visit(GetValue<int64_t>{}, val)); break;
    case DataType::number: node.setFloat(std::visit(GetValue<double>{}, val)); break;
    case DataType::string: node.setString(std::visit(GetValue<std::string>{}, val).c_str()); break;
    case DataType::entityRef: node.setEntityRef({std::get<EntityRef>(val)}); break;
    case DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
}

void setPropValue(Property& node, Value const& val)
{
    switch (node.getDataType())
    {
    case DataType::array:
    case DataType::object:
    case DataType::oneOf:
    case DataType::null: break;
    case DataType::boolean: node.setBool(std::visit(GetValue<bool>{}, val)); break;
    case DataType::integer: node.setInt(std::visit(GetValue<int64_t>{}, val)); break;
    case DataType::number: node.setFloat(std::visit(GetValue<double>{}, val)); break;
    case DataType::string: node.setString(std::visit(GetValue<std::string>{}, val).c_str()); break;
    case DataType::entityRef: node.setEntityRef({std::get<EntityRef>(val)}); break;
    case DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
}

static py::list nodeGetKey(Node* _node)
{
    auto const type = _node->getKeyType();
    py::list arr;
    if (type == DataType::string || type == DataType::entityRef)
    {
        for (auto const& key : _node->getKeysString())
        {
            arr.append(py::str(key.c_str()));
        }
    }
    else if (type == DataType::integer)
    {
        for (auto key : _node->getKeysInt())
        {
            arr.append(key);
        }
    }
    else
    {
        throw std::runtime_error("Unexpected key type");
    }
    return arr;
}

static py::list propMapGetKeys(Property& _prop)
{
    auto const type = _prop.getMapKeyType();
    py::list arr;
    if (type == DataType::string || type == DataType::entityRef)
    {
        for (auto const& key : _prop.getMapKeysString())
        {
            arr.append(py::str(key));
        }
    }
    else if (type == DataType::integer)
    {
        for (auto key : _prop.getMapKeysInt())
        {
            arr.append(key);
        }
    }
    else
    {
        throw std::runtime_error("Unexpected key type");
    }
    return arr;
}

static py::list propMapGetItems(Property& _prop)
{
    auto const type = _prop.getMapKeyType();
    py::list arr;
    if (type == DataType::string || type == DataType::entityRef)
    {
        for (auto&& [key, value] : _prop.getMapStringItems())
        {
            arr.append(make_tuple(py::str(key), py::cast(value)));
        }
    }
    else if (type == DataType::integer)
    {
        for (auto&& [key, value] : _prop.getMapIntItems())
        {
            arr.append(make_tuple(key, py::cast(value)));
        }
    }
    else
    {
        throw std::runtime_error("Unexpected key type");
    }
    return arr;
}

static py::list propPrimSetGetKeys(Property& _prop)
{
    auto const& type = _prop.getSchema()->singularItems->get().type;
    py::list arr;
    if (type == DataType::string || type == DataType::entityRef)
    {
        for (auto const& key : _prop.getPrimSetKeysString())
        {
            arr.append(py::str(key));
        }
    }
    else if (type == DataType::integer)
    {
        for (auto key : _prop.getPrimSetKeysInt())
        {
            arr.append(key);
        }
    }
    else
    {
        throw std::runtime_error("Unexpected key type");
    }
    return arr;
}

static py::list propObjSetGetKeys(Property& _prop)
{
    auto& itemType = _prop.getSchema()->singularItems->get();
    auto const meta = std::get<Subschema::ArrayMeta>(_prop.getSchema()->meta);
    auto const type = itemType.properties.at(*meta.keyField).get().type;
    py::list arr;
    if (type == DataType::string || type == DataType::entityRef)
    {
        for (auto const& key : _prop.getObjectSetKeysString())
        {
            arr.append(py::str(key));
        }
    }
    else if (type == DataType::integer)
    {
        for (auto key : _prop.getObjectSetKeysInt())
        {
            arr.append(key);
        }
    }
    else
    {
        throw std::runtime_error("Unexpected key type");
    }
    return arr;
}

nlohmann::json dumpProperty(Property _prop, bool _superKeyIsTypeName = false)
{
    nlohmann::json result;
    DumpProperty dumper(result, _superKeyIsTypeName);
    visitRecursive(_prop, dumper);
    return result;
}

using namespace pybind11::literals;

// clang-format off

PYBIND11_MODULE(EntityLibPy, ent)
{
    ent.doc() = "pybind11 for EntityLib";

    // ****************************** Schema ******************************************************

    /*
     * "forward-declare" all bound classes to avoid naming issues that lead to bad typing information,
     * see https://github.com/sizmailov/pybind11/blob/7b9242c84826b36fa10e6dcedb6f97fe4429fa61/docs/advanced/misc.rst#avoiding-c-types-in-docstrings
     *
     * NOTE: it wasn't strictly to pre-declare ALL classes to fix the issues we currently had,
     * but it just seemed safer in case we add new methods with new dependencies.
     */
    auto pyDataType = py::enum_<DataType>(ent, "DataType");
    auto pyDataKind = py::enum_<DataKind>(ent, "DataKind");
    auto pyLogicErrorPolicy = py::enum_<LogicErrorPolicy>(ent, "LogicErrorPolicy");
    auto pyOverrideValueSource = py::enum_<OverrideValueSource>(ent, "OverrideValueSource");
    auto pyOverrideValueLocation = py::enum_<OverrideValueLocation>(ent, "OverrideValueLocation");
    auto pyCopyMode = py::enum_<CopyMode>(ent, "CopyMode");
    auto pyPath = py::class_<std::filesystem::path>(ent, "path");
    auto pyEntString = py::class_<String>(ent, "String");
    auto pySubschema = py::class_<Subschema>(ent, "Subschema");
    auto pySubschemaRef = py::class_<SubschemaRef>(ent, "SubschemaRef");
    auto pySchema = py::class_<Schema>(ent, "Schema");
    auto pySubschemaBaseMeta = py::class_<Subschema::BaseMeta>(ent, "Subschema_BaseMeta");
    auto pySubschemaArrayMeta = py::class_<Subschema::ArrayMeta>(ent, "Subschema_ArrayMeta");
    auto pySubschemaGenericMeta = py::class_<Subschema::GenericMeta>(ent, "Subschema_GenericMeta");
    auto pySubschemaNumberMeta = py::class_<Subschema::NumberMeta>(ent, "Subschema_NumberMeta");
    auto pySubschemaUnionMeta = py::class_<Subschema::UnionMeta>(ent, "Subschema_UnionMeta");
    auto pySubschemaUnionSubTypeInfo = py::class_<Subschema::UnionSubTypeInfo>(ent, "Subschema_UnionSubTypeInfo");

    pyLogicErrorPolicy
        .value("Terminate", LogicErrorPolicy::Terminate)
        .value("Throw", LogicErrorPolicy::Throw)
        .export_values();

    pyDataType
        .value("null", DataType::null)
        .value("string", DataType::string)
        .value("number", DataType::number)
        .value("integer", DataType::integer)
        .value("object", DataType::object)
        .value("array", DataType::array)
        .value("boolean", DataType::boolean)
        .value("entityRef", DataType::entityRef)
        .value("union", DataType::oneOf)
        .export_values();

    pyDataKind
        .value("string", DataKind::string)
        .value("number", DataKind::number)
        .value("integer", DataKind::integer)
        .value("object", DataKind::object)
        .value("array", DataKind::array)
        .value("boolean", DataKind::boolean)
        .value("union", DataKind::union_)
        .value("unionSet", DataKind::unionSet)
        .value("map", DataKind::map)
        .value("objectSet", DataKind::objectSet)
        .value("primitiveSet", DataKind::primitiveSet)
        .export_values();

    pyOverrideValueSource
        .value("Override", OverrideValueSource::Override)
        .value("OverrideOrPrefab", OverrideValueSource::OverrideOrPrefab)
        .value("Any", OverrideValueSource::Any)
        .export_values();

    pyOverrideValueLocation
        .value("Default", OverrideValueLocation::Default)
        .value("Prefab", OverrideValueLocation::Prefab)
        .value("Override", OverrideValueLocation::Override)
        .export_values();

    pyCopyMode
        .value("CopyOverride", CopyMode::CopyOverride)
        .value("MinimalOverride", CopyMode::MinimalOverride)
        .export_values();

    pyPath
        .def(py::init<std::string>())
        .def("__str__", [](std::filesystem::path* path) { return path->string(); })
        .def("__eq__", [](std::filesystem::path& a, std::filesystem::path& b) { return a == b; })
        .def("__hash__", [](std::filesystem::path& path) {
            return hash_value(path);
        });

    pyEntString
        .def(py::init<std::string>())
        .def("__str__", [](String* str) { return static_cast<std::string>(*str); })
        .def("__eq__", [](String& a, String& b) { return a == b; });

    py::implicitly_convertible<std::string, std::filesystem::path>();
    py::implicitly_convertible<std::string, String>();

    pySubschemaBaseMeta
        .def_readonly("used_in_editor", &Subschema::BaseMeta::usedInEditor)
        .def_readonly("used_in_runtime", &Subschema::BaseMeta::usedInRuntime)
        .def_readonly("deprecated", &Subschema::BaseMeta::deprecated);
    pySubschemaArrayMeta
        .def_readonly("override_policy", &Subschema::ArrayMeta::overridePolicy)
        .def_readonly("ordered", &Subschema::ArrayMeta::ordered);
    pySubschemaNumberMeta
        .def_readonly("bit_depth", &Subschema::NumberMeta::bitDepth)
        .def_readonly("is_signed", &Subschema::NumberMeta::isSigned);
    pySubschemaUnionMeta
        .def_readonly("data_field", &Subschema::UnionMeta::dataField)
        .def_readonly("type_field", &Subschema::UnionMeta::typeField)
        .def_readonly("index_field", &Subschema::UnionMeta::indexField);
    pySubschemaUnionSubTypeInfo
        .def_readonly("data_schema", &Subschema::UnionSubTypeInfo::dataSchema)
        .def_readonly("wrapper_schema", &Subschema::UnionSubTypeInfo::wrapperSchema)
        .def_readonly("index", &Subschema::UnionSubTypeInfo::index);

    pySubschema
        .def_readonly("type", &Subschema::type)
        .def_readonly("name", &Subschema::name)
        .def_readonly("title", &Subschema::title)
        .def_readonly("description", &Subschema::description)
        .def_readonly("required", &Subschema::required)
        .def_readonly("properties", &Subschema::properties, py::return_value_policy::reference_internal)
        .def_readonly("max_items", &Subschema::maxItems)
        .def_readonly("min_items", &Subschema::minItems)
        .def_readonly("union_type_map", &Subschema::unionTypeMap)
        .def_property_readonly("is_used_in_editor", &Subschema::IsUsedInEditor)
        .def_property_readonly("is_used_in_runtime", &Subschema::IsUsedInRuntime)
        .def_readonly("one_of", &Subschema::oneOf, py::return_value_policy::reference_internal)
        .def_readonly("default_value", &Subschema::defaultValue, py::return_value_policy::reference_internal)
        .def_readonly("meta", &Subschema::meta, py::return_value_policy::reference_internal)
        .def_readonly("user_meta", &Subschema::userMeta, py::return_value_policy::reference_internal)
        .def("get_union_name_field", &Subschema::getUnionNameField, py::return_value_policy::reference_internal)
        .def("get_union_data_field", &Subschema::getUnionDataField, py::return_value_policy::reference_internal)
        .def(
            "get_default_value",
            [](Subschema& s) -> Subschema::DefaultValue& { return s.defaultValue; },
            py::return_value_policy::reference_internal)
        .def_readonly("const_value", &Subschema::constValue, py::return_value_policy::reference_internal)
        .def(
            "get_singular_items",
            [](Subschema const& s) -> SubschemaRef const* { return s.singularItems.get(); },
            py::return_value_policy::reference_internal)
        .def_property_readonly(
            "singular_items",
            [](Subschema const& s) -> SubschemaRef const* { return s.singularItems.get(); },
            py::return_value_policy::reference_internal)
        .def("has_singular_items", [](Subschema const& s) { return s.singularItems != nullptr; })
        .def(
            "get_linear_items",
            [](Subschema const& s) -> std::vector<SubschemaRef> const& { return *s.linearItems; },
            py::return_value_policy::reference_internal)
        .def_property_readonly("linear_items",
            [](Subschema const& s) -> std::vector<SubschemaRef> const& { return *s.linearItems; },
            py::return_value_policy::reference_internal)
        .def(
            "get_union_types_dict",
            &Subschema::getUnionTypesMap,
            py::return_value_policy::reference_internal)
        // .def("linear_items", &Subschema::linearItems, py::return_value_policy::reference_internal)
        .def("has_linear_items", [](Subschema const& s) { return s.linearItems.has_value(); })
        .def_readonly("enum_values", &Subschema::enumValues, py::return_value_policy::reference_internal)
        .def_property_readonly("is_deprecated", [](Subschema const& s) { return s.IsDeprecated(); })
        .def_property_readonly("data_kind", &Subschema::getDataKind)
    ;

    pySubschemaRef
        .def(py::init<>())
        .def_property_readonly("sub_schema", [](SubschemaRef const& s) -> Subschema const& { return s.get(); },
            py::return_value_policy::reference_internal)
        .def(
            "get",
            [](SubschemaRef const& s) -> Subschema const& { return s.get(); },
            py::return_value_policy::reference_internal);

    pySchema
        .def_readonly("definitions", &Schema::allDefinitions, py::return_value_policy::reference_internal);

    // ******************************************** EntityLib *************************************

    /*
     * "forward-declare" all bound classes to avoid naming issues that lead to bad typing information,
     * see https://github.com/sizmailov/pybind11/blob/7b9242c84826b36fa10e6dcedb6f97fe4429fa61/docs/advanced/misc.rst#avoiding-c-types-in-docstrings
     *
     * NOTE: it wasn't strictly to pre-declare ALL classes to fix the issues we currently had,
     * but it just seemed safer in case we add new methods with new dependencies.
     */
    auto pyNode = py::class_<Node, NodeUniquePtr>(ent, "Node");
    // Make python internally use shared_ptr for Entity and Scene
    auto pyComponentsSchema = py::class_<ComponentsSchema>(ent, "ComponentsSchema");
    auto pyColor = py::class_<std::array<uint8_t, 4>>(ent, "Color");
    auto pyEntityLib = py::class_<EntityLib>(ent, "EntityLib");
    auto pyEntityRef = py::class_<EntityRef>(ent, "EntityRef");
    auto pyNodeFile = py::class_<EntityLib::NodeFile>(ent, "NodeFile");
    auto pyPrefabInfo = py::class_<Node::PrefabInfo>(ent, "Node_PrefabInfo");
    auto pyPropPrefabInfo = py::class_<PrefabInfo>(ent, "Prop_PrefabInfo");
    auto pyProperty = py::class_<Property>(ent, "Property");

    pyPrefabInfo
        .def_readonly("node", &Node::PrefabInfo::node)
        .def_readonly("noderef", &Node::PrefabInfo::nodeRef)
        .def_readonly("prefab_path", &Node::PrefabInfo::prefabPath)
        ;

    pyPropPrefabInfo
        .def_readonly("node", &PrefabInfo::prop)
        .def_readonly("noderef", &PrefabInfo::nodeRef)
        .def_readonly("prefab_path", &PrefabInfo::prefabPath)
        ;

    pyNode
        // this is for exchanging pointers between different wrappers (eg C++ vs Python), only works in the same process, use at your own risk
        .def("get_ptr", [](Node* self) {return (intptr_t)self;})
        .def_static("from_ptr", [](intptr_t _ptr) {return (Node*)_ptr;}, py::return_value_policy::reference_internal)
        .def("has_override", &Node::hasOverride)
        .def("has_prefab_value", &Node::hasPrefabValue)
        .def("has_default_value", &Node::hasDefaultValue)
        .def("get_entitylib", &Node::getEntityLib)
        .def_property_readonly("datatype", [](Node const* node) { return node->getDataType(); })
        .def(
            "at",
            [](Node* node, char const* field) { return node->at(field); },
            py::return_value_policy::reference_internal,
            "In an Object, get the property by name")
        .def("count", [](Node* node, char const* field) { return node->count(field); })
        .def("get_field_names", &Node::getFieldNames)
        .def_property_readonly("fields",
            &Node::getFields,
            py::return_value_policy::reference_internal)
        .def(
            "at",
            [](Node* node, size_t i) { return node->at(i); },
            py::return_value_policy::reference_internal,
            "In an Array, get the element by index")
        .def(
            "__getitem__",
            [](Node* node, size_t i) { return node->at(i); },
            py::return_value_policy::reference_internal)
        .def("size", [](Node* node) { return node->size(); })
        .def("__len__", [](Node* node) { return node->size(); })
        .def("get_raw_size", &Node::getRawSize)
        .def(
            "get_items",
            [](Node* node) { return node->getItems(); },
            py::return_value_policy::reference_internal)
        .def_property_readonly(
            "items",
            [](Node* node) { return node->getItems(); },
            py::return_value_policy::reference_internal)
        .def(
            "push", [](Node* node) { return node->push(); }, py::return_value_policy::reference_internal)
        .def("pop", [](Node* node) { node->pop(); })
        .def("clear", [](Node* node) { return node->clear(); })
        .def("empty", [](Node* node) { return node->empty(); })
        .def_property_readonly("instance_of", [](Node* node) { return node->getInstanceOf(); })
        .def("get_instance_of", [](Node* node) { return node->getInstanceOf(); })
        .def("set_instance_of", [](Node* node, char const* _path){ node->resetInstanceOf(_path);})
        .def("change_instance_of", [](Node* node, char const* _path){ node->changeInstanceOf(_path);})
        .def("reset_instance_of", [](Node* node, char const* _path){ node->resetInstanceOf(_path);})
        .def("get_float", [](Node* node) { return node->getFloat(); })
        .def("get_int", [](Node* node) { return node->getInt(); })
        .def("get_string", [](Node* node) { return node->getString(); })
        .def("get_bool", [](Node* node) { return node->getBool(); })
        .def("get_entityref", &Node::getEntityRef)
        .def("get_raw_float", &Node::getRawFloat)
        .def("get_raw_int", &Node::getRawInt)
        .def("get_raw_string", &Node::getRawString)
        .def("get_raw_bool", &Node::getRawBool)
        .def("get_default_float", [](Node* node) { return node->getDefaultFloat(); })
        .def("get_default_int", [](Node* node) { return node->getDefaultInt(); })
        .def("get_default_string", [](Node* node) { return node->getDefaultString(); })
        .def("get_default_bool", [](Node* node) { return node->getDefaultBool(); })
        .def("is_default", [](Node* node) { return node->isDefault(); })
        .def("get_type_name", [](Node* node) { return node->getTypeName(); })
        // properties are reference_internal by default, but "value" is a fake property since
        // the Node doesn't own the returned variant.
        .def_property("value", getValue, setValue, py::return_value_policy::copy)
        .def_property_readonly("default_value", getDefaultValue)
        .def("set_float", [](Node* node, double val) { return node->setFloat(val); })
        .def("set_int", [](Node* node, int64_t val) { return node->setInt(val); })
        .def("set_string", [](Node* node, char const* str) { return node->setString(str); })
        .def("set_bool", [](Node* node, bool val) { return node->setBool(val); })
        .def("set_entityref", &Node::setEntityRef)
        .def(
            "get_union_data",
            [](Node* node) { return node->getUnionData(); },
            py::return_value_policy::reference_internal)
        .def_property_readonly("union_data", [](Node* node) { return node->getUnionData(); }, py::return_value_policy::reference_internal)
        .def("get_union_type", &Node::getUnionType, py::return_value_policy::reference_internal)
        .def_property_readonly("union_type", &Node::getUnionType, py::return_value_policy::reference_internal)
        .def("set_union_type", &Node::setUnionType, py::return_value_policy::reference_internal)
        .def(
            "get_schema",
            [](Node* node) { return node->getSchema(); },
            py::return_value_policy::reference_internal)
        .def_property_readonly(
            "schema",
            [](Node* node) { return node->getSchema(); },
            py::return_value_policy::reference_internal)
        .def("unset", [](Node* node) { return node->unset(); })
        .def("is_set", [](Node* node) { return node->isSet(); })
        .def("dumps", [](Node* node, OverrideValueSource source, bool superKeyIsType)
             {
                 return node->toJson(source, superKeyIsType).dump(4);
             },
             "source"_a = OverrideValueSource::Override, "superKeyIsType"_a = false)
        .def("map_erase", static_cast<bool(Node::*)(char const*) const>(&Node::mapErase))
        .def("map_erase", [](Node* _node, String const& _key){ return _node->mapErase(_key.c_str()); })
        .def("map_erase", static_cast<bool(Node::*)(int64_t) const>(&Node::mapErase))
        .def("map_rename", static_cast<Node*(Node::*)(char const*, char const*)>(&Node::mapRename), py::return_value_policy::reference_internal)
        .def("map_rename", [](Node* _node, String const& _from, String const& _to)
            {
                return _node->mapRename(_from.c_str(), _to.c_str());
            }, py::return_value_policy::reference_internal)
        .def("map_rename", static_cast<Node*(Node::*)(int64_t, int64_t) const>(&Node::mapRename), py::return_value_policy::reference_internal)
        .def("map_get", static_cast<Node*(Node::*)(char const*)>(&Node::mapGet), py::return_value_policy::reference_internal)
        .def("map_get", [](Node* node, String const& str){return node->mapGet(str.c_str());}, py::return_value_policy::reference_internal)
        .def("map_get", static_cast<Node*(Node::*)(int64_t)>(&Node::mapGet), py::return_value_policy::reference_internal)
        .def("map_insert", static_cast<Node*(Node::*)(char const*) const>(&Node::mapInsert), py::return_value_policy::reference_internal)
        .def("map_insert", [](Node* _node, String const& _key){ return _node->mapInsert(_key.c_str()); }, py::return_value_policy::reference_internal)
        .def("map_insert", static_cast<Node*(Node::*)(int64_t)>(&Node::mapInsert), py::return_value_policy::reference_internal)
        .def("map_insert_instanceof", &Node::mapInsertInstanceOf, py::return_value_policy::reference_internal)
        .def("map_insert_instanceof", (Node* (Node::*)(int64_t))&Node::mapInsertInstanceOf, py::return_value_policy::reference_internal)
        .def("is_map_or_set", &Node::isMapOrSet)
        .def("get_key_type", &Node::getKeyType)
        .def("get_keys", nodeGetKey)
        .def("save_node", &Node::saveNode)
        .def("detach", &Node::detach)
        .def("make_instance_of", &Node::makeInstanceOf)
        .def_property_readonly("parent_node", static_cast<Node*(Node::*)()>(&Node::getParentNode), py::return_value_policy::reference_internal)
        .def("apply_all_values", [](Node& self, Node& dest, CopyMode copyMode) {
            self.applyAllValues(dest, copyMode);
        })
        .def_property_readonly("root_node", &Node::getRootNode, py::return_value_policy::reference_internal)
        .def("make_noderef", &Node::makeNodeRef)
        .def("resolve_noderef", static_cast<Node*(Node::*)(char const* _nodeRef)>(&Node::resolveNodeRef), py::return_value_policy::reference_internal)
        .def_property_readonly("absolute_noderef", &Node::makeAbsoluteNodeRef)
        .def("get_prefab_history", &Node::getPrefabHistory)
        .def("apply_to_prefab", &Node::applyToPrefab)
        ;

    pyComponentsSchema
        .def_readonly("components", &ComponentsSchema::components, py::return_value_policy::reference_internal)
        .def_readonly("actorstates", &ComponentsSchema::actorstates, py::return_value_policy::reference_internal)
        .def_readonly("schema", &ComponentsSchema::schema, py::return_value_policy::reference_internal);

    pyColor
        .def(py::init<>())
        .def(py::init<uint8_t, uint8_t, uint8_t, uint8_t>());

    pyEntityLib
        .def(py::init<std::string>())
        // this is for exchanging pointers between different wrappers (eg C++ vs Python), only works in the same process, use at your own risk
        .def("get_ptr", [](EntityLib* self) {return (intptr_t)self;})
        .def_static("from_ptr", [](intptr_t _ptr) {return (EntityLib*)_ptr;}, py::return_value_policy::reference_internal)
        .def_readwrite("validation_enabled", &EntityLib::validationEnabled)
        .def_readonly("root_path", &EntityLib::rootPath)
        .def_readwrite("rawdata_path", &EntityLib::rawdataPath) // unit-test need to write it
        .def_readonly("tools_dir", &EntityLib::toolsDir)
        .def_readonly("schema", &EntityLib::schema, py::return_value_policy::reference_internal)
        .def("make_entityref", static_cast<EntityRef(EntityLib::*)(Node const&, Node const&) const>(&EntityLib::makeEntityRef))
        .def("make_entityref", static_cast<EntityRef(EntityLib::*)(Property const&, Property const&) const>(&EntityLib::makeEntityRef))
        .def("resolve_entityref",
            static_cast<Node*(EntityLib::*)(Node*, EntityRef const&) const>(&EntityLib::resolveEntityRef),
            py::return_value_policy::reference_internal)
        .def("resolve_entityref",
            static_cast<std::optional<Property>(EntityLib::*)(Property const&, EntityRef const&) const>(&EntityLib::resolveEntityRef),
            py::keep_alive<0, 1>())
        .def_readonly(
            "component_dependencies",
            &EntityLib::componentDependencies,
            py::return_value_policy::reference_internal)
        .def(
            "load_node_read_only",
            [](EntityLib* entlib, Subschema const* schema, char const* name){ return entlib->loadNodeReadOnly(*schema, name).get();},
            py::return_value_policy::reference_internal
        )
        .def(
            "load_node_entity_read_only",
            [](EntityLib* entlib, char const* name){ return entlib->loadNodeEntityReadOnly(name).get();},
            py::return_value_policy::reference_internal
        )
        .def("get_node_cache", &EntityLib::getNodeCache, py::return_value_policy::reference_internal)
        .def("clear_cache", &EntityLib::clearCache)
        .def("load_node_file",
            [](EntityLib* lib, std::filesystem::path const& _path, Subschema const& _schema)
            {
                return lib->loadFileAsNode(_path, _schema);
            }, py::keep_alive<0, 1>())
        .def("load_node_file",
            [](EntityLib* lib, char const* _path)
            {
                return lib->loadFileAsNode(_path);
            }, py::keep_alive<0, 1>())
        .def("load_node_entity", &EntityLib::loadEntityAsNode, py::keep_alive<0, 1>())
        .def_property(
            "logic_error_policy",
            [](EntityLib* lib){return lib->getLogicErrorPolicy();},
            [](EntityLib* lib, LogicErrorPolicy err){lib->setLogicErrorPolicy(err);})
        .def("load_node_scene", &EntityLib::loadSceneAsNode, py::keep_alive<0, 1>()) // py::keep_alive<0, 1> => Do not destroy EntityLib before Node
        .def("make_node_instanceof", &EntityLib::makeNodeInstanceOf, py::keep_alive<0, 1>())
        .def("make_entity_node_instanceof", &EntityLib::makeEntityNodeInstanceOf, py::keep_alive<0, 1>())
        .def("make_node", &EntityLib::makeNode, py::keep_alive<0, 1>())
        .def("make_entity_node", &EntityLib::makeEntityNode, py::keep_alive<0, 1>())
        .def("save_node_as_entity", &EntityLib::saveNodeAsEntity)
        .def("save_node_as_scene", &EntityLib::saveNodeAsScene)
        .def("get_parent_entity", static_cast<Node*(EntityLib::*)(Node*) const>(&EntityLib::getParentEntity), py::return_value_policy::reference_internal)
        .def("get_parent_entity", static_cast<std::optional<Property>(EntityLib::*)(Property const&) const>(&EntityLib::getParentEntity), py::return_value_policy::reference_internal)
        .def("get_schema", &EntityLib::getSchema, py::return_value_policy::reference_internal)
        .def("load_property", &EntityLib::loadProperty)
        .def("load_property_copy", &EntityLib::loadPropertyCopy)
        .def("set_dep_file_callback", &EntityLib::setNewDepFileCallBack)
    ;

    pyEntityRef
        .def(py::init<>())
        .def(py::init<std::string>())
        .def(py::init<EntityRef const&>())
        .def_readwrite("entity_path", &EntityRef::entityPath)
        .def("__str__", [](EntityRef* ref) { return static_cast<std::string>(ref->entityPath); })
        .def("__eq__", [](EntityRef const& _lhs, EntityRef const& _rhs){ return _lhs.entityPath == _rhs.entityPath; })
        .def("__lt__", [](EntityRef const& _lhs, EntityRef const& _rhs){ return _lhs.entityPath < _rhs.entityPath; });

    pyNodeFile
        .def_property_readonly(
            "data",
            [](EntityLib::NodeFile* entF) { return entF->data.get(); },
            py::return_value_policy::reference_internal)
        .def_readonly("time", &EntityLib::NodeFile::time, py::return_value_policy::reference_internal);

    pyProperty
        .def(py::init<EntityLib*, Subschema const*, char const*>(), py::keep_alive<1, 2>())
        .def(py::init<EntityLib*, Subschema const*, char const*, nlohmann::json*>(), py::keep_alive<1, 2>())
        .def_static("create", [](EntityLib* _lib, Subschema const* _schema, char const* _path)
        {
            return Property(_lib, _schema, _path, &_lib->createTempJsonFile());
        }, py::arg("entlib"), py::arg("schema"), py::arg("path") = "", py::keep_alive<1, 2>())
        .def("save", &Property::save)
        .def_property_readonly("is_default", &Property::isDefault)
        .def("get_object_field", &Property::getObjectField, py::arg("field"), py::arg("field_schema") = nullptr, py::keep_alive<0, 1>())
        .def("get_union_data", [](Property& _self, char const* _type){ return _self.getUnionData(_type);}, py::keep_alive<0, 1>())
        .def("get_union_data", [](Property& _self){ return _self.getUnionData();}, py::keep_alive<0, 1>())
        .def("get_unionset_item", &Property::getUnionSetItem, py::arg("type"), py::arg("schema") = nullptr, py::keep_alive<0, 1>())
        .def("get_objectset_item", [](Property& _self, char const* _key){return _self.getObjectSetItem(_key);}, py::keep_alive<0, 1>())
        .def("get_objectset_item", [](Property& _self, int64_t _key){return _self.getObjectSetItem(_key);}, py::keep_alive<0, 1>())
        .def("get_map_item", [](Property& _self, char const* _key){return _self.getMapItem(_key);}, py::keep_alive<0, 1>())
        .def("get_map_item", [](Property& _self, int64_t _key){return _self.getMapItem(_key);}, py::keep_alive<0, 1>())
        .def("get_array_item", &Property::getArrayItem, py::keep_alive<0, 1>())
        .def("get_instance_of", &Property::getInstanceOf)
        .def_property("instance_of", &Property::getInstanceOf, &Property::changeInstanceOf)
        .def_property_readonly("union_type", &Property::getUnionType) // or read/write ?
        .def_property_readonly("data_type", &Property::getDataType)
        .def_property_readonly("schema", &Property::getSchema, py::return_value_policy::reference_internal)
        .def_property_readonly("type_name", &Property::getTypeName)
        .def_property_readonly("map_key_type", &Property::getMapKeyType)
        .def_property_readonly("objectset_key_type", &Property::getObjectSetKeyType)
        .def_property_readonly("primset_key_type", &Property::getPrimSetKeyType)
        .def_property("size", &Property::size, &Property::setSize)
        .def("contains", &Property::contains)
        .def_property_readonly("array_size", &Property::arraySize)
        .def_property_readonly("empty", &Property::empty)
        .def_property_readonly("is_null", &Property::isNull)
        .def_property_readonly("map_keys", &propMapGetKeys)
        .def_property_readonly("primset_keys", &propPrimSetGetKeys)
        .def_property_readonly("unionset_keys", &Property::getUnionSetKeysString)
        .def_property_readonly("objectset_keys", &propObjSetGetKeys)
        .def_property_readonly("map_items", &propMapGetItems)
        .def_property_readonly("objectset_items", &Property::getObjectSetItems)
        .def_property_readonly("unionset_items", &Property::getUnionSetItems)    
        .def("map_contains", [](Property& _self, char const* _key){return _self.mapContains(_key);})
        .def("map_contains", [](Property& _self, int64_t _key){return _self.mapContains(_key);})
        .def("primset_contains", [](Property& _self, char const* _key){return _self.primSetContains(_key);})
        .def("primset_contains", [](Property& _self, int64_t _key){return _self.primSetContains(_key);})
        .def("unionset_contains", [](Property& _self, char const* _key){return _self.unionSetContains(_key);})
        .def("objectset_contains", [](Property& _self, char const* _key){return _self.objectSetContains(_key);})
        .def("objectset_contains", [](Property& _self, int64_t _key){return _self.objectSetContains(_key);})
        .def_property_readonly("is_set", &Property::isSet)
        .def_property("value", getPropValue, setPropValue, py::return_value_policy::copy)
        .def("get_float", &Property::getFloat)
        .def("get_int", &Property::getInt)
        .def("get_string", &Property::getString)
        .def("get_bool", &Property::getBool)
        .def("get_entityref", &Property::getEntityRef)
        .def("set_float", &Property::setFloat)
        .def("set_int", &Property::setInt)
        .def("set_string", &Property::setString)
        .def("set_bool", &Property::setBool)
        .def("set_entityref", &Property::setEntityRef)
        .def("set_union_type", &Property::setUnionType, py::keep_alive<0, 1>())
        .def("build_path", &Property::buildPath)
        .def("insert_primset_item", [](Property const& _self, char const* _key){return _self.insertPrimSetKey(_key);})
        .def("insert_primset_item", [](Property const& _self, int64_t _key){return _self.insertPrimSetKey(_key);})
        .def("insert_unionset_item", &Property::insertUnionSetItem, py::keep_alive<0, 1>())
        .def("insert_instance_objectset_item", &Property::insertInstanceObjectSetItem, py::keep_alive<0, 1>())
        .def("insert_map_item", [](Property const& _self, char const* _key){return _self.insertMapItem(_key);}, py::keep_alive<0, 1>())
        .def("insert_map_item", [](Property const& _self, int64_t _key){return _self.insertMapItem(_key);}, py::keep_alive<0, 1>())
        .def("insert_objectset_item", [](Property const& _self, char const* _key){return _self.insertObjectSetItem(_key);}, py::keep_alive<0, 1>())
        .def("insert_objectset_item", [](Property const& _self, int64_t _key){return _self.insertObjectSetItem(_key);}, py::keep_alive<0, 1>())
        .def("resolve_noderef", &Property::resolveNodeRef, py::keep_alive<0, 1>())
        .def_property_readonly("raw_json", &Property::getRawJson)
        .def_property_readonly("has_value", &Property::hasValue)
        .def_property_readonly("has_prefab", &Property::hasPrefab)
        .def_property_readonly("prefab", &Property::getPrefab, py::keep_alive<0, 1>())
        .def_property_readonly("parent", &Property::getParent, py::keep_alive<0, 1>())
        .def_property_readonly("file_path", &Property::getFilePath)
        .def_property_readonly("root_node", &Property::getRootNode, py::keep_alive<0, 1>())
        .def_property_readonly("noderef", &Property::makeNodeRef)
        .def_property_readonly("absolute_noderef", &Property::makeAbsoluteNodeRef)
        .def_property_readonly("path_token", &Property::getPathToken)
        .def_property_readonly("get_prefab_history", &getPrefabHistory, py::keep_alive<0, 1>())
        .def("detach", &Property::detach, py::keep_alive<0, 1>())
        .def("clear", &Property::clear)
        .def("dumps", &dumpProperty, py::arg("superKeyIsTypeName") = false)
        .def("erase_primset_key", [](Property& _self, char const* _key){return _self.erasePrimSetKey(_key);})
        .def("erase_primset_key", [](Property& _self, int64_t _key){return _self.erasePrimSetKey(_key);})
        .def("erase_objectset_item", [](Property& _self, char const* _key){return _self.eraseObjectSetItem(_key);})
        .def("erase_objectset_item", [](Property& _self, int64_t _key){return _self.eraseObjectSetItem(_key);})
        .def("erase_map_item", [](Property& _self, char const* _key){return _self.eraseMapItem(_key);})
        .def("erase_map_item", [](Property& _self, int64_t _key){return _self.eraseMapItem(_key);})
        .def("erase_unionset_item", &Property::eraseUnionSetItem)
        .def("copy_into", &Property::copyInto)
        .def("unset", [](Property& _self) { return _self.unset(); })
        .def("has_override", &Property::hasOverride)
        ;

    py::register_exception<JsonValidation>(ent, "JsonValidation");
}

// clang-format on

/// @endcond
