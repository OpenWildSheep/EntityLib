#include <iostream>

#include <EntityLib.h>

namespace std
{
    using tl::nullopt;
    using tl::nullopt_t;
    using tl::optional;
} // namespace std

#define PYBIND11_HAS_OPTIONAL 1

#pragma warning(push, 0)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#pragma warning(pop)

/// @cond PRIVATE

namespace pybind11
{
    namespace detail
    {
        template <typename... Ts>
        struct type_caster<mapbox::util::variant<Ts...>>
            : variant_caster<mapbox::util::variant<Ts...>>
        {
        };

        // Specifies the function used to visit the variant -- `apply_visitor` instead of `visit`
        template <>
        struct visit_helper<mapbox::util::variant>
        {
            template <typename... Args>
            static auto call(Args&&... args) -> decltype(mapbox::util::apply_visitor(args...))
            {
                return mapbox::util::apply_visitor(args...);
            }
        };
    } // namespace detail
} // namespace pybind11

namespace py = pybind11;
using namespace Ent;

using Value = mapbox::util::variant<Null, std::string, float, int64_t, bool>;

Value getValue(Ent::Node& node)
{
    switch (node.getDataType())
    {
    case Ent::DataType::array: return node.getFloat();
    case Ent::DataType::freeobject: return node.getFloat();
    case Ent::DataType::object: return node.getFloat();
    case Ent::DataType::boolean: return node.getBool();
    case Ent::DataType::integer: return node.getInt();
    case Ent::DataType::null: return nullptr;
    case Ent::DataType::number: return node.getFloat();
    case Ent::DataType::string: return std::string(node.getString());
    }
    return Value();
}

void setValue(Ent::Node& node, Value const& val)
{
    switch (node.getDataType())
    {
    case Ent::DataType::array: node.setFloat(val.get<float>()); break;
    case Ent::DataType::freeobject: node.setFloat(val.get<float>()); break;
    case Ent::DataType::object: node.setFloat(val.get<float>()); break;
    case Ent::DataType::boolean: node.setBool(val.get<bool>()); break;
    case Ent::DataType::integer: node.setInt(val.get<int64_t>()); break;
    case Ent::DataType::null: break;
    case Ent::DataType::number: node.setFloat(val.get<float>()); break;
    case Ent::DataType::string: node.setString(val.get<std::string>().c_str()); break;
    }
}

using namespace pybind11::literals;

PYBIND11_MODULE(EntityLibPy, ent)
{
    ent.doc() = "pybind11 for EntityLib";

    // ****************************** Schema ******************************************************

    py::enum_<DataType>(ent, "DataType")
        .value("null", DataType::null)
        .value("string", DataType::string)
        .value("number", DataType::number)
        .value("integer", DataType::integer)
        .value("object", DataType::object)
        .value("array", DataType::array)
        .value("boolean", DataType::boolean)
        .export_values();

    py::class_<std::filesystem::path>(ent, "path").def(py::init<std::string>());

    py::implicitly_convertible<std::string, std::filesystem::path>();

    py::class_<Subschema>(ent, "Subschema")
        .def_readonly("type", &Subschema::type)
        .def_readonly("name", &Subschema::name)
        .def_readonly("required", &Subschema::required)
        .def_readonly("properties", &Subschema::properties, py::return_value_policy::reference)
        .def_readonly("max_items", &Subschema::maxItems)
        .def_readonly("min_items", &Subschema::minItems)
        .def_readonly("one_of", &Subschema::oneOf, py::return_value_policy::reference)
        .def_readonly("default_value", &Subschema::defaultValue, py::return_value_policy::reference)
        .def(
            "get_default_value",
            [](Subschema& s) -> Ent::Subschema::DefaultValue& { return s.defaultValue; },
            py::return_value_policy::reference)
        .def_readonly("const_value", &Subschema::constValue, py::return_value_policy::reference)
        // .def("singular_items", &Subschema::singularItems, py::return_value_policy::reference)
        .def(
            "get_singular_items",
            [](Subschema const& s) -> SubschemaRef const* { return s.singularItems.get(); },
            py::return_value_policy::reference)
        .def("has_singular_items", [](Subschema const& s) { return s.singularItems != nullptr; })
        .def(
            "get_linear_items",
            [](Subschema const& s) -> std::vector<SubschemaRef> const& { return *s.linearItems; },
            py::return_value_policy::reference)
        // .def("linear_items", &Subschema::linearItems, py::return_value_policy::reference)
        .def("has_linear_items", [](Subschema const& s) { return s.linearItems.has_value(); })
        .def_readonly("enum_values", &Subschema::enumValues, py::return_value_policy::reference);

    py::class_<SubschemaRef>(ent, "SubschemaRef")
        .def(py::init<>())
        .def(
            "get",
            [](SubschemaRef const& s) -> Subschema const& { return s.get(); },
            py::return_value_policy::reference);

    py::class_<Schema>(ent, "Schema")
        .def_readonly("root", &Schema::root, py::return_value_policy::reference)
        .def_readonly("definitions", &Schema::allDefinitions, py::return_value_policy::reference);

    // ******************************************** EntityLib *************************************

    py::class_<Node>(ent, "Node")
        .def_property_readonly("datatype", [](Node const* node) { return node->getDataType(); })
        .def(
            "at",
            [](Node* node, char const* field) { return node->at(field); },
            py::return_value_policy::reference,
            "In an Object, get the property by name")
        .def("count", [](Node* node, char const* field) { return node->count(field); })
        .def("get_field_names", &Node::getFieldNames)
        .def(
            "at",
            [](Node* node, size_t i) { return node->at(i); },
            py::return_value_policy::reference,
            "In an Array, get the element by index")
        .def("size", [](Node* node) { return node->size(); })
        .def(
            "get_items",
            [](Node* node) { return node->getItems(); },
            py::return_value_policy::reference_internal)
        .def(
            "push", [](Node* node) { return node->push(); }, py::return_value_policy::reference)
        .def("pop", [](Node* node) { return node->pop(); })
        .def("clear", [](Node* node) { return node->clear(); })
        .def("empty", [](Node* node) { return node->empty(); })
        .def("get_float", [](Node* node) { return node->getFloat(); })
        .def("get_int", [](Node* node) { return node->getInt(); })
        .def("get_string", [](Node* node) { return node->getString(); })
        .def("get_bool", [](Node* node) { return node->getBool(); })
        .def("get_default_float", [](Node* node) { return node->getDefaultFloat(); })
        .def("get_default_int", [](Node* node) { return node->getDefaultInt(); })
        .def("get_default_string", [](Node* node) { return node->getDefaultString(); })
        .def("get_default_bool", [](Node* node) { return node->getDefaultBool(); })
        .def("is_default", [](Node* node) { return node->isDefault(); })
        .def("get_type_name", [](Node* node) { return node->getTypeName(); })
        .def_property("value", getValue, setValue)
        .def("set_float", [](Node* node, float val) { return node->setFloat(val); })
        .def("set_int", [](Node* node, int64_t val) { return node->setInt(val); })
        .def(
            "set_string", [](Node* node, char const* str) { return node->setString(std::move(str)); })
        .def("set_bool", [](Node* node, bool val) { return node->setBool(val); })
        .def("unset", [](Node* node) { return node->unset(); })
        .def("is_set", [](Node* node) { return node->isSet(); });

    py::class_<Component>(ent, "Component")
        .def_readonly("type", &Component::type)
        .def_readonly("root", &Component::root, py::return_value_policy::reference);

    py::class_<SubSceneComponent>(ent, "SubSceneComponent")
        .def_readonly("is_embedded", &SubSceneComponent::isEmbedded)
        .def_property(
            "file",
            [](SubSceneComponent const& sc) -> std::string { return sc.file.get(); },
            [](SubSceneComponent& sc, std::string f) { return sc.file.set(std::move(f)); })
        .def("make_embedded", &SubSceneComponent::makeEmbedded)
        .def_property_readonly(
            "embedded",
            [](SubSceneComponent* comp) -> Scene& { return *comp->embedded; },
            py::return_value_policy::reference);

    py::class_<Entity>(ent, "Entity")
        .def_property("name", &Entity::getName, &Entity::setName)
        .def_property_readonly("instance_of", &Entity::getInstanceOf)
        .def_property("thumbnail", &Entity::getThumbnail, &Entity::setThumbnail)
        .def_property("color", &Entity::getColor, &Entity::setColor)
        .def("add_component", &Entity::addComponent, py::return_value_policy::reference)
        .def(
            "get_component",
            [](Entity& e, char const* name) { return e.getComponent(name); },
            py::return_value_policy::reference)
        .def("remove_component", &Entity::removeComponent)
        .def("get_component_types", &Entity::getComponentTypes)
        .def("get_components", &Entity::getComponents, py::return_value_policy::reference)
        .def(
            "get_subscene_component",
            [](Entity& e) { return e.getSubSceneComponent(); },
            py::return_value_policy::reference)
        .def("add_subscene_component", &Entity::addSubSceneComponent, py::return_value_policy::reference)
        .def("detach_entity_from_prefab", &Entity::detachEntityFromPrefab);

    py::class_<Scene>(ent, "Scene")
        .def_readonly("entities", &Scene::objects, py::return_value_policy::reference_internal);

    py::class_<ComponentsSchema>(ent, "ComponentsSchema")
        .def_readonly("components", &ComponentsSchema::components, py::return_value_policy::reference)
        .def_readonly("schema", &ComponentsSchema::schema, py::return_value_policy::reference);

    py::class_<std::array<uint8_t, 4>>(ent, "Color")
        .def(py::init<>())
        .def(py::init<uint8_t, uint8_t, uint8_t, uint8_t>());

    py::class_<EntityLib>(ent, "EntityLib")
        .def(py::init<std::string>())
        .def_readonly("root_path", &EntityLib::rootPath)
        .def_readonly("rawdata_path", &EntityLib::rawdataPath)
        .def_readonly("tools_dir", &EntityLib::toolsDir)
        .def_readonly("schema", &EntityLib::schema, py::return_value_policy::reference)
        .def_readonly(
            "component_dependencies",
            &EntityLib::componentDependencies,
            py::return_value_policy::reference)
        .def(
            "load_entity",
            &EntityLib::loadEntity,
            py::return_value_policy::copy,
            "entityPath"_a,
            "super"_a = nullptr)
        .def("load_scene", &EntityLib::loadScene, py::return_value_policy::copy)
        .def("save_entity", &EntityLib::saveEntity, "entity"_a, "_entityPath"_a, "super"_a = nullptr)
        .def("save_scene", &EntityLib::saveScene)
        .def("make_instance_of", &EntityLib::makeInstanceOf, "instanceOf"_a);

    py::register_exception<Ent::JsonValidation>(ent, "JsonValidation");
}

/// @endcond
