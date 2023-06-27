#include <iostream>

#include <EntityLib.h>
#include <EntityLib/Property.h>
#include <EntityLib/SearchProperty.h>

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

Value getPropValue(Property const& _prop)
{
    switch (_prop.getDataKind())
    {
    case DataKind::array: [[fallthrough]];
    case DataKind::unionSet: [[fallthrough]];
    case DataKind::map: [[fallthrough]];
    case DataKind::objectSet: [[fallthrough]];
    case DataKind::object: [[fallthrough]];
    case DataKind::primitiveSet: [[fallthrough]];
    case DataKind::union_: return nullptr;
    case DataKind::boolean: return _prop.getBool();
    case DataKind::integer: return _prop.getInt();
    case DataKind::number: return _prop.getFloat();
    case DataKind::string: return std::string(_prop.getString());
    case DataKind::entityRef: return _prop.getEntityRef();
    case DataKind::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
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

void setPropValue(Property& node, Value const& val)
{
    switch (node.getDataKind())
    {
    case DataKind::array:
    case DataKind::object:
    case DataKind::union_:
    case DataKind::boolean: node.setBool(std::visit(GetValue<bool>{}, val)); break;
    case DataKind::integer: node.setInt(std::visit(GetValue<int64_t>{}, val)); break;
    case DataKind::number: node.setFloat(std::visit(GetValue<double>{}, val)); break;
    case DataKind::string: node.setString(std::visit(GetValue<std::string>{}, val).c_str()); break;
    case DataKind::entityRef: node.setEntityRef({std::get<EntityRef>(val)}); break;
    case DataKind::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
}

static py::list propMapGetKeys(Property& _prop)
{
    auto const kind = _prop.getMapKeyKind();
    py::list arr;
    if (kind == DataKind::string || kind == DataKind::entityRef)
    {
        for (auto const& key : _prop.getMapKeysString())
        {
            arr.append(py::str(key));
        }
    }
    else if (kind == DataKind::integer)
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
    auto const kind = _prop.getMapKeyKind();
    py::list arr;
    if (kind == DataKind::string || kind == DataKind::entityRef)
    {
        for (auto&& [key, value] : _prop.getMapStringItems())
        {
            arr.append(make_tuple(py::str(key), py::cast(value)));
        }
    }
    else if (kind == DataKind::integer)
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
    if (_prop.getSchema()->singularItems == nullptr)
    {
        throw std::runtime_error("Not an primitiveSet in 'primset_keys'");
    }
    auto const& kind = _prop.getSchema()->singularItems->get().getDataKind();
    py::list arr;
    if (kind == DataKind::string || kind == DataKind::entityRef)
    {
        for (auto const& key : _prop.getPrimSetKeysString())
        {
            arr.append(py::str(key));
        }
    }
    else if (kind == DataKind::integer)
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
    if (_prop.getSchema()->singularItems == nullptr)
    {
        throw std::runtime_error("Not an objectSet in 'objectset_keys'");
    }
    auto& itemType = _prop.getSchema()->singularItems->get();
    auto const meta = std::get<Subschema::ArrayMeta>(_prop.getSchema()->meta);
    auto const type = itemType.properties.at(*meta.keyField).get().getDataKind();
    py::list arr;
    if (type == DataKind::string || type == DataKind::entityRef)
    {
        for (auto const& key : _prop.getObjectSetKeysString())
        {
            arr.append(py::str(key));
        }
    }
    else if (type == DataKind::integer)
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

nlohmann::json dumpProperty(Property _prop, bool _superKeyIsTypeName = false, bool _saveUnionIndex = false)
{
    nlohmann::json result;
    DumpProperty dumper(
        result,
        Ent::OverrideValueSource::Any,
        _superKeyIsTypeName,
        [](Ent::EntityRef&) {},
        _saveUnionIndex);
    visitRecursive(_prop, dumper);
    return result;
}

std::vector<Property> searchChild(Property _prop, char const* _pattern)
{
    if (std::string_view(_pattern).empty())
    {
        return {};
    }
    SearchProperty searcher(_pattern);
    visitRecursive(_prop, searcher);
    return searcher.getMatchingProperties();
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
    auto pyJsonType = py::enum_<JsonType>(ent, "JsonType");
    auto pyDataKind = py::enum_<DataKind>(ent, "DataKind");
    auto pyLogicErrorPolicy = py::enum_<LogicErrorPolicy>(ent, "LogicErrorPolicy");
    auto pyOverrideValueSource = py::enum_<OverrideValueSource>(ent, "OverrideValueSource");
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
    auto pyJsonMetaData = py::class_<JsonMetaData>(ent, "JsonMetaData");

    pyLogicErrorPolicy
        .value("Terminate", LogicErrorPolicy::Terminate)
        .value("Throw", LogicErrorPolicy::Throw)
        .export_values();

    pyJsonType
        .value("null", JsonType::null)
        .value("string", JsonType::string)
        .value("number", JsonType::number)
        .value("integer", JsonType::integer)
        .value("object", JsonType::object)
        .value("array", JsonType::array)
        .value("boolean", JsonType::boolean)
        .value("entityRef", JsonType::entityRef)
        .value("union", JsonType::oneOf)
        .export_values();

    pyDataKind
        .value("string", DataKind::string)
        .value("number", DataKind::number)
        .value("integer", DataKind::integer)
        .value("entityRef", DataKind::entityRef)
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
        .def_readonly("json_type", &Subschema::jsonType)
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
        .def_readonly("minimum", &Subschema::minimum, py::return_value_policy::reference_internal)
        .def_readonly("maximum", &Subschema::maximum, py::return_value_policy::reference_internal)
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
    // Make python internally use shared_ptr for Entity and Scene
    auto pyComponentsSchema = py::class_<ComponentsSchema>(ent, "ComponentsSchema");
    auto pyColor = py::class_<std::array<uint8_t, 4>>(ent, "Color");
    auto pyEntityLib = py::class_<EntityLib>(ent, "EntityLib");
    auto pyEntityRef = py::class_<EntityRef>(ent, "EntityRef");
    auto pyPropPrefabInfo = py::class_<PrefabInfo>(ent, "Prop_PrefabInfo");
    auto pyProperty = py::class_<Property>(ent, "Property");

    pyPropPrefabInfo
        .def_readonly("node", &PrefabInfo::prop)
        .def_readonly("noderef", &PrefabInfo::nodeRef)
        .def_readonly("prefab_path", &PrefabInfo::prefabPath)
        ;

    pyComponentsSchema
        .def_readonly("schema", &ComponentsSchema::schema, py::return_value_policy::reference_internal);

    pyColor
        .def(py::init<>())
        .def(py::init<uint8_t, uint8_t, uint8_t, uint8_t>());

    pyEntityLib
        .def(py::init<std::string, std::string>(), "rawdata_path"_a, "schemas_path"_a)
        // this is for exchanging pointers between different wrappers (eg C++ vs Python), only works in the same process, use at your own risk
        .def("get_ptr", [](EntityLib* self) {return (intptr_t)self;})
        .def_static("from_ptr", [](intptr_t _ptr) {return (EntityLib*)_ptr;}, py::return_value_policy::reference_internal)
        .def_readwrite("validation_enabled", &EntityLib::validationEnabled)
        .def_readonly("root_path", &EntityLib::rootPath)
        .def_readwrite("rawdata_path", &EntityLib::rawdataPath) // unit-test need to write it
        .def_readonly("schema", &EntityLib::schema, py::return_value_policy::reference_internal)
        .def_property_readonly("schema_path", &EntityLib::getSchemaPath)
        .def("make_entityref", &EntityLib::makeEntityRef)
        .def("resolve_entityref", &EntityLib::resolveEntityRef, py::keep_alive<0, 1>())
        .def_readonly(
            "component_dependencies",
            &EntityLib::componentDependencies,
            py::return_value_policy::reference_internal)
        .def_readonly(
            "component_incompatibilities",
            &EntityLib::componentIncompatibilities,
            py::return_value_policy::reference_internal)
        .def("get_json_database", [](EntityLib const& _entlib)
        {
            std::map<std::string, nlohmann::json*> allFiles;
            for (auto const& [path, doc]: _entlib.getJsonDatabase())

            {
                allFiles.emplace(path.generic_string(), &doc->document);
            }
            return allFiles;
        })
        .def_property(
            "logic_error_policy",
            [](EntityLib* lib){return lib->getLogicErrorPolicy();},
            [](EntityLib* lib, LogicErrorPolicy err){lib->setLogicErrorPolicy(err);})
        .def("get_parent_entity", &EntityLib::getParentEntity, py::return_value_policy::reference_internal)
        .def("get_schema", &EntityLib::getSchema, py::return_value_policy::reference_internal)
        .def("load_property", (Property (EntityLib::*)(char const*, char const*))&EntityLib::loadProperty, "schema_name"_a, "file_path"_a)
        .def("load_property", (Property (EntityLib::*)(char const*))&EntityLib::loadProperty, "file_path"_a)
        .def("load_property_copy", (Property (EntityLib::*)(char const*, char const*))&EntityLib::loadPropertyCopy, "schema_name"_a, "file_path"_a)
        .def("load_property_copy", (Property (EntityLib::*)(char const*))&EntityLib::loadPropertyCopy, "file_path"_a)
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

    pyProperty
        .def(py::init<EntityLib*, Subschema const*, char const*>(), py::keep_alive<1, 2>())
        .def(py::init<EntityLib*, Subschema const*, char const*, nlohmann::json*, JsonMetaData*>(), py::keep_alive<1, 2>())
        .def_static("create", [](EntityLib* _lib, Subschema const* _schema, char const* _path, nlohmann::json* _data)
        {
            auto& newFile = _lib->createTempJsonFile(_schema->name.c_str());
            if (_data != nullptr && !_data->is_null()) // Python convert None to json::null, so _data is never nullptr
            {
                newFile.document = *_data;
            }
            return Property(_lib, _schema, _path, newFile);
        }, py::arg("entlib"), py::arg("schema"), py::arg("path") = "", py::arg("data") = nullptr, py::keep_alive<1, 2>())
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
        .def("reset_instance_of", &Property::resetInstanceOf)
        .def_property("instance_of", &Property::getInstanceOf, &Property::changeInstanceOf)
        .def_property_readonly("first_instance_of", &Property::getFirstInstanceOf)
        .def_property_readonly("entitylib", &Property::getEntityLib)
        .def_property_readonly("union_type", &Property::getUnionType) // or read/write ?
        .def_property_readonly("data_kind", &Property::getDataKind)
        .def_property_readonly("schema", &Property::getSchema, py::return_value_policy::reference_internal)
        .def_property_readonly("type_name", &Property::getTypeName)
        .def_property_readonly("map_key_kind", &Property::getMapKeyKind)
        .def_property_readonly("objectset_key_kind", &Property::getObjectSetKeyKind)
        .def_property_readonly("primset_key_kind", &Property::getPrimSetKeyKind)
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
        .def("dumps", &dumpProperty, py::arg("superKeyIsTypeName") = false, py::arg("saveUnionIndex") = false)
        .def("erase_primset_key", [](Property& _self, char const* _key){return _self.erasePrimSetKey(_key);})
        .def("erase_primset_key", [](Property& _self, int64_t _key){return _self.erasePrimSetKey(_key);})
        .def("erase_objectset_item", [](Property& _self, char const* _key){return _self.eraseObjectSetItem(_key);})
        .def("erase_objectset_item", [](Property& _self, int64_t _key){return _self.eraseObjectSetItem(_key);})
        .def("erase_map_item", [](Property& _self, char const* _key){return _self.eraseMapItem(_key);})
        .def("erase_map_item", [](Property& _self, int64_t _key){return _self.eraseMapItem(_key);})
        .def("erase_unionset_item", &Property::eraseUnionSetItem)
        .def("copy_into", &Property::copyInto, py::arg("dest"), py::arg("copy_mode"), py::arg("override_value_source") = OverrideValueSource::OverrideOrPrefab)
        .def("unset", [](Property& _self) { return _self.unset(); })
        .def("push_back", &Property::pushBack)
        .def("pop_back", &Property::popBack)
        .def("apply_to_prefab", &Property::applyToPrefab)
        .def_property_readonly("debug_string", &Property::getDebugString)
        .def("search_child", &searchChild)
        .def_static("from_ptr", [](intptr_t _ptr) {return (Property*)_ptr;}, py::return_value_policy::reference_internal)
        ;
    // clang-format on

    py::register_exception<JsonValidation>(ent, "JsonValidation");
    py::register_exception_translator(
        [](std::exception_ptr _ptr)
        {
            try
            {
                if (_ptr)
                    std::rethrow_exception(_ptr);
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                PyErr_SetString(PyExc_IOError, Ent::convertANSIToUTF8(e.what()).c_str());
            }
        });
}

/// @endcond
