#include <iostream>

#include <EntityLib.h>

#pragma warning(push, 0)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "external/pybind11_json.hpp"
#pragma warning(pop)

/// @cond PRIVATE

namespace pybind11::detail
{
    // Use tj::optional like a std::optional
    template <typename T>
    struct type_caster<tl::optional<T>> : public optional_caster<tl::optional<T>>
    {
    };
} // namespace pybind11::detail

namespace py = pybind11;
using namespace Ent;

using Value = std::variant<Null, std::string, double, int64_t, bool, EntityRef>;

Value getValue(Ent::Node& node)
{
    switch (node.getDataType())
    {
    case Ent::DataType::array:
    case Ent::DataType::object:
    case Ent::DataType::oneOf:
    case Ent::DataType::null: return nullptr;
    case Ent::DataType::boolean: return node.getBool();
    case Ent::DataType::integer: return node.getInt();
    case Ent::DataType::number: return node.getFloat();
    case Ent::DataType::string: return std::string(node.getString());
    case Ent::DataType::entityRef: return node.getEntityRef();
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
    return Value();
}

Value getDefaultValue(Ent::Node& node)
{
    switch (node.getDataType())
    {
    case Ent::DataType::array:
    case Ent::DataType::object:
    case Ent::DataType::oneOf:
    case Ent::DataType::null: return nullptr;
    case Ent::DataType::boolean: return node.getDefaultBool();
    case Ent::DataType::integer: return node.getDefaultInt();
    case Ent::DataType::number: return node.getDefaultFloat();
    case Ent::DataType::string: return std::string(node.getDefaultString());
    case Ent::DataType::entityRef: return node.getDefaultEntityRef();
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
    return Value();
}

template <typename I, typename O>
struct Converter
{
    O operator()(I const&) const
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

void setValue(Ent::Node& node, Value const& val)
{
    switch (node.getDataType())
    {
    case Ent::DataType::array:
    case Ent::DataType::object:
    case Ent::DataType::oneOf:
    case Ent::DataType::null: break;
    case Ent::DataType::boolean: node.setBool(std::visit(GetValue<bool>{}, val)); break;
    case Ent::DataType::integer: node.setInt(std::visit(GetValue<int64_t>{}, val)); break;
    case Ent::DataType::number: node.setFloat(std::visit(GetValue<double>{}, val)); break;
    case Ent::DataType::string:
        node.setString(std::visit(GetValue<std::string>{}, val).c_str());
        break;
    case Ent::DataType::entityRef: node.setEntityRef({std::get<EntityRef>(val)}); break;
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
}

std::map<std::string, Component*> getComponents(Entity const& e)
{
    std::map<std::string, Component*> components;
    for (auto&& [name, compPtr] : e.getComponents())
    {
        components.emplace(name, compPtr.get());
    }
    return components;
}

static py::list nodeGetKey(Node* _node)
{
    auto const type = _node->getKeyType();
    py::list arr;
    if (type == Ent::DataType::string || type == Ent::DataType::entityRef)
    {
        for (auto const& key : _node->getKeysString())
        {
            arr.append(py::str(key.c_str()));
        }
    }
    else if (type == Ent::DataType::integer)
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

using namespace pybind11::literals;

// clang-format off

static Entity* anonymEntityCtor(EntityLib* _entlib)
{
    static std::atomic<size_t> count = 0;
    auto val = ++count;
    char buff[128];
    sprintf_s(buff, "Anonymous%llu", val);
    return new Entity(*_entlib, buff); // NOLINT(cppcoreguidelines-owning-memory)
}

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
    auto pyLogicErrorPolicy = py::enum_<LogicErrorPolicy>(ent, "LogicErrorPolicy");
    auto pyActivationLevel = py::enum_<ActivationLevel>(ent, "ActivationLevel");
    auto pyOverrideValueSource = py::enum_<OverrideValueSource>(ent, "OverrideValueSource");
    auto pyOverrideValueLocation = py::enum_<OverrideValueLocation>(ent, "OverrideValueLocation");
    auto pyCopyMode = py::enum_<CopyMode>(ent, "CopyMode");
    auto pyPath = py::class_<std::filesystem::path>(ent, "path");
    auto pyEntString = py::class_<Ent::String>(ent, "String");
    auto pySubschema = py::class_<Subschema>(ent, "Subschema");
    auto pySubschemaRef = py::class_<SubschemaRef>(ent, "SubschemaRef");
    auto pySchema = py::class_<Schema>(ent, "Schema");
    auto pySubschemaBaseMeta = py::class_<Subschema::BaseMeta>(ent, "Subschema_BaseMeta");
    auto pySubschemaArrayMeta = py::class_<Subschema::ArrayMeta>(ent, "Subschema_ArrayMeta");
    auto pySubschemaGenericMeta = py::class_<Subschema::GenericMeta>(ent, "Subschema_GenericMeta");
    auto pySubschemaNumberMeta = py::class_<Subschema::NumberMeta>(ent, "Subschema_NumberMeta");
    auto pySubschemaUnionMeta = py::class_<Subschema::UnionMeta>(ent, "Subschema_UnionMeta");

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

    pyActivationLevel
        .value("Created", ActivationLevel::Created)
        .value("Started", ActivationLevel::Started)
        .value("Loading", ActivationLevel::Loading)
        .value("InWorld", ActivationLevel::InWorld)
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
            return std::filesystem::hash_value(path);
        });

    pyEntString
        .def(py::init<std::string>())
        .def("__str__", [](Ent::String* str) { return (std::string)*str; })
        .def("__eq__", [](Ent::String& a, Ent::String& b) { return a == b; });

    py::implicitly_convertible<std::string, std::filesystem::path>();
    py::implicitly_convertible<std::string, Ent::String>();

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

    pySubschema
        .def_readonly("type", &Subschema::type)
        .def_readonly("name", &Subschema::name)
        .def_readonly("title", &Subschema::title)
        .def_readonly("description", &Subschema::description)
        .def_readonly("required", &Subschema::required)
        .def_readonly("properties", &Subschema::properties, py::return_value_policy::reference_internal)
        .def_readonly("max_items", &Subschema::maxItems)
        .def_readonly("min_items", &Subschema::minItems)
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
            [](Subschema& s) -> Ent::Subschema::DefaultValue& { return s.defaultValue; },
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
            &Ent::Subschema::getUnionTypesMap,
            py::return_value_policy::reference_internal)
        // .def("linear_items", &Subschema::linearItems, py::return_value_policy::reference_internal)
        .def("has_linear_items", [](Subschema const& s) { return s.linearItems.has_value(); })
        .def_readonly("enum_values", &Subschema::enumValues, py::return_value_policy::reference_internal)
        .def_property_readonly("is_deprecated", [](Subschema const& s) { return s.IsDeprecated(); });

    pySubschemaRef
        .def(py::init<>())
        .def_property_readonly("sub_schema", [](SubschemaRef const& s) -> Subschema const& { return s.get(); },
            py::return_value_policy::reference_internal)
        .def(
            "get",
            [](SubschemaRef const& s) -> Subschema const& { return s.get(); },
            py::return_value_policy::reference_internal);

    pySchema
        .def_readonly("root", &Schema::root, py::return_value_policy::reference_internal)
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
    auto pyComponent = py::class_<Component>(ent, "Component");
    auto pySubSceneComponent = py::class_<SubSceneComponent>(ent, "SubSceneComponent");
    // Make python internally use shared_ptr for Entity and Scene
    auto pyEntity = py::class_<Entity, std::shared_ptr<Entity>>(ent, "Entity");
    auto pyScene = py::class_<Scene, std::shared_ptr<Scene>>(ent, "Scene");
    auto pyComponentsSchema = py::class_<ComponentsSchema>(ent, "ComponentsSchema");
    auto pyColor = py::class_<std::array<uint8_t, 4>>(ent, "Color");
    auto pyEntityLib = py::class_<EntityLib>(ent, "EntityLib");
    auto pyEntityRef = py::class_<EntityRef>(ent, "EntityRef");
    auto pyEntityFile = py::class_<EntityLib::EntityFile>(ent, "EntityFile");
    auto pyNodeFile = py::class_<EntityLib::NodeFile>(ent, "NodeFile");
    auto pySceneFile = py::class_<EntityLib::SceneFile>(ent, "SceneFile");

    pyNode
        // this is for exchanging pointers between different wrappers (eg C++ vs Python), only works in the same process, use at your own risk
        .def("get_ptr", [](Node* self) {return (intptr_t)self;})
        .def_static("from_ptr", [](intptr_t _ptr) {return (Node*)_ptr;})
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
        .def("map_erase", (bool (Node::*)(char const*))&Node::mapErase)
        .def("map_erase", [](Node* _node, Ent::String const& _key){ return _node->mapErase(_key.c_str()); })
        .def("map_erase", (bool (Node::*)(int64_t))&Node::mapErase)
        .def("map_rename", (Node* (Node::*)(char const*, char const*))&Node::mapRename, py::return_value_policy::reference_internal)
        .def("map_rename", [](Node* _node, Ent::String const& _from, Ent::String const& _to)
            {
                return _node->mapRename(_from.c_str(), _to.c_str());
            }, py::return_value_policy::reference_internal)
        .def("map_rename", (Node* (Node::*)(int64_t, int64_t))&Node::mapRename, py::return_value_policy::reference_internal)
        .def("map_get", (Node* (Node::*)(char const*))&Node::mapGet, py::return_value_policy::reference_internal)
        .def("map_get", [](Node* node, Ent::String const& str){return node->mapGet(str.c_str());}, py::return_value_policy::reference_internal)
        .def("map_get", (Node* (Node::*)(int64_t))&Node::mapGet, py::return_value_policy::reference_internal)
        .def("map_insert", (Node* (Node::*)(char const* _key))&Node::mapInsert, py::return_value_policy::reference_internal)
        .def("map_insert", [](Node* _node, Ent::String const& _key){ return _node->mapInsert(_key.c_str()); }, py::return_value_policy::reference_internal)
        .def("map_insert", (Node* (Node::*)(int64_t _key))&Node::mapInsert, py::return_value_policy::reference_internal)
        .def("map_insert_instanceof", (Node* (Node::*)(char const* _key))&Node::mapInsertInstanceOf, py::return_value_policy::reference_internal)
        .def("map_insert_instanceof", (Node* (Node::*)(int64_t _key))&Node::mapInsertInstanceOf, py::return_value_policy::reference_internal)
        .def("is_map_or_set", &Node::isMapOrSet)
        .def("get_key_type", &Node::getKeyType)
        .def("get_keys", nodeGetKey)
        .def("save_node", &Node::saveNode)
        .def("detach", &Node::detach)
        .def("make_instance_of", &Node::makeInstanceOf)
        .def_property_readonly("parent_node", (Node* (Node::*)())&Node::getParentNode, py::return_value_policy::reference_internal)
        .def("apply_all_values", [](Node& self, Node& dest, CopyMode copyMode) {
            self.applyAllValues(dest, copyMode);
        })
        ;

    pyComponent
        .def_readonly("type", &Component::type)
        .def_property_readonly("root", [](Component const& comp){ return comp.root.get();}, py::return_value_policy::reference_internal)
        .def_property_readonly(
            "is_used_in_editor", [](Component const& comp) { return comp.isUsedInEditor(); })
        .def_property_readonly(
            "is_used_in_runtime", [](Component const& comp) { return comp.isUsedInRuntime(); });

    pySubSceneComponent
        .def_property_readonly(
            "embedded",
            [](SubSceneComponent* comp) -> Scene& { return *comp->embedded; },
            py::return_value_policy::reference_internal)
        // detachEmbedded is hard to bind in python because it change the way the entities inside
        // are managed by python.
        // They were reference_internal and become managed by python.
        // Since this function is used nowhere is seems acceptable to not bind it now.
        // .def("detach_embedded",
        //     [](SubSceneComponent* comp) -> Scene* { return comp->detachEmbedded().release(); })
        ;

    pyEntity
        // 1 = this = constructed object.   2 = 1st arg = entlib.  (https://pybind11.readthedocs.io/en/stable/advanced/functions.html#keep-alive)
        .def(py::init<EntityLib const&, char const*>(), py::keep_alive<1, 2>())
        .def(py::init(&anonymEntityCtor), py::keep_alive<1, 2>())
        // this is for exchanging pointers between different wrappers (eg C++ vs Python), only works in the same process, use at your own risk
        .def("get_ptr", [](Entity* self) {return (intptr_t)self;})
        .def_static("from_ptr", [](intptr_t _ptr) {return (Entity*)_ptr;}, py::return_value_policy::reference_internal)
        .def_property("name", &Entity::getName, &Entity::setName)
        .def_property_readonly("instance_of", &Entity::getInstanceOf)
        .def_property("thumbnail", &Entity::getThumbnail, &Entity::setThumbnail)
        .def_property_readonly("parent_scene", &Entity::getParentScene)
        .def_property(
            "max_activation_level", &Entity::getMaxActivationLevel, &Entity::setMaxActivationLevel)
        .def_property("color", &Entity::getColor, &Entity::setColor)
        .def("has_override", &Entity::hasOverride)
        .def("add_component", &Entity::addComponent, py::return_value_policy::reference_internal)
        .def(
            "get_component",
            [](Entity& e, char const* name) { return e.getComponent(name); },
            py::return_value_policy::reference_internal)
        .def("remove_component", &Entity::removeComponent)
        .def("remove_subscene_component", &Entity::removeSubSceneComponent)
        .def("get_component_types", &Entity::getComponentTypes)
        .def("get_components", &getComponents, py::return_value_policy::reference_internal)
        .def_property_readonly("components",
            &getComponents,
            py::return_value_policy::reference_internal)
        .def("get_actorstates", [](Entity* ent) { return &ent->getActorStates(); }, py::return_value_policy::reference_internal)
        .def_property_readonly("actorstates", [](Entity* ent) { return &ent->getActorStates(); }, py::return_value_policy::reference_internal)
        .def(
            "get_subscene_component",
            [](Entity& e) { return e.getSubSceneComponent(); },
            py::return_value_policy::reference_internal)
        .def("add_subscene_component", &Entity::addSubSceneComponent, py::return_value_policy::reference_internal)
        .def_property_readonly("sub_scene_component",
            [](Entity& e) { return e.getSubSceneComponent(); },
            py::return_value_policy::reference_internal)
        .def("make_entityref", &Entity::makeEntityRef)
        .def("set_instance_of", &Entity::resetInstanceOf)
        .def("reset_instance_of", &Entity::resetInstanceOf)
        .def("change_instance_of", &Entity::changeInstanceOf)
        .def("resolve_entityref", (Entity* (Entity::*)(const EntityRef&))&Entity::resolveEntityRef, py::return_value_policy::reference_internal)
        .def("detach_entity_from_prefab", [](Entity* ent) {
            return ent->detachEntityFromPrefab().release();
        })
        .def("clone", [](Entity* ent) {
            return ent->clone().release();
        })
        .def("apply_to_prefab", [](Entity& ent) {
            ent.applyToPrefab();
        })
        .def("apply_all_values", [](Entity& ent, Entity& dest, CopyMode copyMode) {
            ent.applyAllValues(dest, copyMode);
        })
        .def("apply_all_values_but_prefab", [](Entity& ent, Entity& dest, CopyMode copyMode) {
            ent.applyAllValuesButPrefab(dest, copyMode);
        })
        .def("dumps", [](Entity* entity)
             {
                 return entity->saveEntity().dump(4);
             });

    pyScene
        // this is for exchanging pointers between different wrappers (eg C++ vs Python), only works in the same process, use at your own risk
        .def("get_ptr", [](Scene* self) {return (intptr_t)self;})
        .def_static("from_ptr", [](intptr_t _ptr) {return (Scene*)_ptr;})
        .def(
            "add_entity",
            [](Scene* scene, Entity* ent) -> Entity*
            {
                return scene->addEntity(ent->clone());
            }, py::return_value_policy::reference_internal)
        .def(
            "add_entity",
            [](Scene* scene, char const* name) -> Entity*
            {
                return scene->addEntity(name);
            }, py::return_value_policy::reference_internal)
        .def(
            "get_entity",
            [](Scene* scene, char const* name) -> Entity*
            {
                return scene->getEntity(name);
            }, py::return_value_policy::reference_internal)
        .def(
            "remove_entity",
            [](Scene* scene, char const* name)
            {
                scene->removeEntity(name);
            }, py::return_value_policy::reference_internal)
        .def(
            "rename_entity",
            [](Scene* scene, char const* name, char const* newName)
            {
                scene->renameEntity(name, newName);
            }, py::return_value_policy::reference_internal)
        .def("resolve_entityref", &Scene::resolveEntityRef, py::return_value_policy::reference_internal)
        .def_property_readonly("owner_entity", &Scene::getOwnerEntity)
        .def("get_entity",
            static_cast<Entity*(Scene::*)(size_t)>(&Scene::getEntity),
            py::return_value_policy::reference_internal)
        .def_property_readonly("entity_count", &Scene::entityCount)
        .def_property_readonly("entities", &Scene::getObjects);

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
        .def("make_entityref", &EntityLib::makeEntityRef)
        .def("resolve_entityref",
            (Node* (EntityLib::*)(Node*, const EntityRef&) const)&EntityLib::resolveEntityRef,
            py::return_value_policy::reference_internal)
        .def_readonly(
            "component_dependencies",
            &EntityLib::componentDependencies,
            py::return_value_policy::reference_internal)
        .def(
            "load_entity",
            [](EntityLib* lib, std::string const& path) { return lib->loadEntity(path).release(); },
            py::keep_alive<0, 1>(), // py::keep_alive<0, 1> => Do not destroy EntityLib before Entity
            "entityPath"_a)
        .def(
            "load_scene",
            [](EntityLib* lib, std::string const& path) { return lib->loadScene(path).release(); },
            py::keep_alive<0, 1>())
        .def(
            "load_legacy_scene",
            [](EntityLib* lib, std::string const& path) { return lib->loadLegacyScene(path).release(); },
            py::keep_alive<0, 1>())
        .def(
            "load_entity_read_only",
            [](EntityLib* lib, std::string const& path) {
                return lib->loadEntityReadOnly(path);},
            py::keep_alive<0, 1>())
        .def(
            "load_scene_read_only",
            [](EntityLib* lib, std::string const& path) { return lib->loadSceneReadOnly(path); },
            py::keep_alive<0, 1>())
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
        .def(
            "load_legacy_scene_read_only",
            [](EntityLib* lib, std::string const& path) { return lib->loadLegacySceneReadOnly(path); },
            py::keep_alive<0, 1>())
        .def("save_entity", &EntityLib::saveEntity, "entity"_a, "_entityPath"_a)
        .def("save_scene", &EntityLib::saveScene)
        .def("get_entity_cache", &EntityLib::getEntityCache, py::return_value_policy::reference_internal)
        .def("get_scene_cache", &EntityLib::getSceneCache, py::return_value_policy::reference_internal)
        .def("get_node_cache", &EntityLib::getNodeCache, py::return_value_policy::reference_internal)
        .def("clear_cache", &EntityLib::clearCache)
        .def("load_node_file",
            [](EntityLib* lib, std::filesystem::path const& _path, Ent::Subschema const& _schema)
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
        .def("get_parent_entity", (Node*(EntityLib::*)(Node*))&EntityLib::getParentEntity, py::return_value_policy::reference_internal)
        .def("get_schema", &EntityLib::getSchema, py::return_value_policy::reference_internal)
        .def(
            "make_instance_of",
            [](EntityLib* lib, std::string const& path) {
                return lib->makeInstanceOf(path).release();
            },
            py::keep_alive<0, 1>(), // py::keep_alive<0, 1> => Do not destroy EntityLib before Entity
            "instanceOf"_a);

    pyEntityRef
        .def(py::init<>())
        .def(py::init<std::string>())
        .def(py::init<EntityRef const&>())
        .def_readwrite("entity_path", &EntityRef::entityPath)
        .def("__str__", [](EntityRef* ref) { return (std::string)ref->entityPath; })
        .def("__eq__", [](EntityRef const& _lhs, EntityRef const& _rhs){ return _lhs.entityPath == _rhs.entityPath; })
        .def("__lt__", [](EntityRef const& _lhs, EntityRef const& _rhs){ return _lhs.entityPath < _rhs.entityPath; });

    pyEntityFile
        .def_property_readonly(
            "data",
            [](EntityLib::EntityFile* entF) { return entF->data.get(); },
            py::return_value_policy::reference_internal)
        .def_readonly("time", &EntityLib::EntityFile::time, py::return_value_policy::reference_internal);

    pySceneFile
        .def_property_readonly(
            "data",
            [](EntityLib::SceneFile* sceneF) { return sceneF->data.get(); },
            py::return_value_policy::reference_internal)
        .def_readonly("time", &EntityLib::SceneFile::time, py::return_value_policy::reference_internal);

    pyNodeFile
        .def_property_readonly(
            "data",
            [](EntityLib::NodeFile* entF) { return entF->data.get(); },
            py::return_value_policy::reference_internal)
        .def_readonly("time", &EntityLib::NodeFile::time, py::return_value_policy::reference_internal);

    py::register_exception<Ent::JsonValidation>(ent, "JsonValidation");
}

// clang-format on

/// @endcond
