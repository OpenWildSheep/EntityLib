#include <iostream>

#include <EntityLib.h>

namespace std
{
    using tl::nullopt;
    using tl::nullopt_t;
    using tl::optional;
} // namespace std

#define PYBIND11_HAS_OPTIONAL 1 // NOLINT

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

using Value = mapbox::util::variant<Null, std::string, float, int64_t, bool, EntityRef>;

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
struct Converter<int64_t, float>
{
    float operator()(int64_t const& val) const
    {
        return static_cast<float>(val);
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
    case Ent::DataType::boolean:
        node.setBool(mapbox::util::apply_visitor(GetValue<bool>{}, val));
        break;
    case Ent::DataType::integer:
        node.setInt(mapbox::util::apply_visitor(GetValue<int64_t>{}, val));
        break;
    case Ent::DataType::number:
        node.setFloat(mapbox::util::apply_visitor(GetValue<float>{}, val));
        break;
    case Ent::DataType::string:
        node.setString(mapbox::util::apply_visitor(GetValue<std::string>{}, val).c_str());
        break;
    case Ent::DataType::entityRef: node.setEntityRef({ val.get<EntityRef>() }); break;
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid Datatype");
    }
}

using namespace pybind11::literals;

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
    auto pyActivationLevel = py::enum_<ActivationLevel>(ent, "ActivationLevel");
    auto pyPath = py::class_<std::filesystem::path>(ent, "path");
    auto pySubschema = py::class_<Subschema>(ent, "Subschema");
    auto pySubschemaRef = py::class_<SubschemaRef>(ent, "SubschemaRef");
    auto pySchema = py::class_<Schema>(ent, "Schema");

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

    pyPath
        .def(py::init<std::string>())
        .def("__str__", [](std::filesystem::path* path) { return path->string(); })
        .def("__eq__", [](std::filesystem::path& a, std::filesystem::path& b) { return a == b; })
        .def("__hash__", [](std::filesystem::path& path) {
            return std::filesystem::hash_value(path);
        });

    py::implicitly_convertible<std::string, std::filesystem::path>();

    pySubschema
        .def_readonly("type", &Subschema::type)
        .def_readonly("name", &Subschema::name)
        .def_readonly("required", &Subschema::required)
        .def_readonly("properties", &Subschema::properties, py::return_value_policy::reference)
        .def_readonly("max_items", &Subschema::maxItems)
        .def_readonly("min_items", &Subschema::minItems)
        .def_readonly("one_of", &Subschema::oneOf, py::return_value_policy::reference)
        .def_readonly("default_value", &Subschema::defaultValue, py::return_value_policy::reference)
        .def("get_union_name_field", &Subschema::getUnionNameField, py::return_value_policy::reference)
        .def("get_union_data_field", &Subschema::getUnionDataField, py::return_value_policy::reference)
        .def(
            "get_default_value",
            [](Subschema& s) -> Ent::Subschema::DefaultValue& { return s.defaultValue; },
            py::return_value_policy::reference)
        .def_readonly("const_value", &Subschema::constValue, py::return_value_policy::reference)
        .def(
            "get_singular_items",
            [](Subschema const& s) -> SubschemaRef const* { return s.singularItems.get(); },
            py::return_value_policy::reference)
        .def("has_singular_items", [](Subschema const& s) { return s.singularItems != nullptr; })
        .def(
            "get_linear_items",
            [](Subschema const& s) -> std::vector<SubschemaRef> const& { return *s.linearItems; },
            py::return_value_policy::reference)
        .def(
            "get_union_types_dict",
            &Ent::Subschema::getUnionTypesMap,
            py::return_value_policy::reference_internal)
        // .def("linear_items", &Subschema::linearItems, py::return_value_policy::reference)
        .def("has_linear_items", [](Subschema const& s) { return s.linearItems.has_value(); })
        .def_readonly("enum_values", &Subschema::enumValues, py::return_value_policy::reference)
        .def_property_readonly("is_deprecated", [](Subschema const& s) { return s.IsDeprecated(); });

    pySubschemaRef
        .def(py::init<>())
        .def(
            "get",
            [](SubschemaRef const& s) -> Subschema const& { return s.get(); },
            py::return_value_policy::reference);

    pySchema
        .def_readonly("root", &Schema::root, py::return_value_policy::reference)
        .def_readonly("definitions", &Schema::allDefinitions, py::return_value_policy::reference);

    // ******************************************** EntityLib *************************************

    /*
     * "forward-declare" all bound classes to avoid naming issues that lead to bad typing information,
     * see https://github.com/sizmailov/pybind11/blob/7b9242c84826b36fa10e6dcedb6f97fe4429fa61/docs/advanced/misc.rst#avoiding-c-types-in-docstrings
     *
     * NOTE: it wasn't strictly to pre-declare ALL classes to fix the issues we currently had,
     * but it just seemed safer in case we add new methods with new dependencies.
     */
    auto pyNode = py::class_<Node>(ent, "Node");
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
    auto pySceneFile = py::class_<EntityLib::SceneFile>(ent, "SceneFile");

    pyNode
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
        .def("get_entityref", &Node::getEntityRef)
        .def("get_default_float", [](Node* node) { return node->getDefaultFloat(); })
        .def("get_default_int", [](Node* node) { return node->getDefaultInt(); })
        .def("get_default_string", [](Node* node) { return node->getDefaultString(); })
        .def("get_default_bool", [](Node* node) { return node->getDefaultBool(); })
        .def("is_default", [](Node* node) { return node->isDefault(); })
        .def("get_type_name", [](Node* node) { return node->getTypeName(); })
        .def_property("value", getValue, setValue)
        .def("set_float", [](Node* node, float val) { return node->setFloat(val); })
        .def("set_int", [](Node* node, int64_t val) { return node->setInt(val); })
        .def("set_string", [](Node* node, char const* str) { return node->setString(str); })
        .def("set_bool", [](Node* node, bool val) { return node->setBool(val); })
        .def("set_entityref", &Node::setEntityRef)
        .def(
            "get_union_data",
            [](Node* node) { return node->getUnionData(); },
            py::return_value_policy::reference)
        .def("get_union_type", &Node::getUnionType, py::return_value_policy::reference)
        .def("set_union_type", &Node::setUnionType, py::return_value_policy::reference)
        .def(
            "get_schema",
            [](Node* node) { return node->getSchema(); },
            py::return_value_policy::reference)
        .def("unset", [](Node* node) { return node->unset(); })
        .def("is_set", [](Node* node) { return node->isSet(); });

    pyComponent
        .def_readonly("type", &Component::type)
        .def_readonly("root", &Component::root, py::return_value_policy::reference)
        .def_property_readonly("raw_data", [](Component const& comp) { return comp.rawData.dump(4); })
        .def_property_readonly(
            "is_used_in_editor", [](Component const& comp) { return comp.isUsedInEditor(); })
        .def_property_readonly(
            "is_used_in_runtime", [](Component const& comp) { return comp.isUsedInRuntime(); });

    pySubSceneComponent
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

    pyEntity
        .def(py::init<EntityLib const&>())
        .def_property("name", &Entity::getName, &Entity::setName)
        .def_property_readonly("instance_of", &Entity::getInstanceOf)
        .def_property("thumbnail", &Entity::getThumbnail, &Entity::setThumbnail)
        .def_property(
            "max_activation_level", &Entity::getMaxActivationLevel, &Entity::setMaxActivationLevel)
        .def_property("color", &Entity::getColor, &Entity::setColor)
        .def("has_override", &Entity::hasOverride)
        .def("add_component", &Entity::addComponent, py::return_value_policy::reference)
        .def(
            "get_component",
            [](Entity& e, char const* name) { return e.getComponent(name); },
            py::return_value_policy::reference)
        .def("remove_component", &Entity::removeComponent)
        .def("get_component_types", &Entity::getComponentTypes)
        .def("get_components", &Entity::getComponents, py::return_value_policy::reference)
        .def("get_actorstates", &Entity::getActorStates, py::return_value_policy::reference)
        .def(
            "get_subscene_component",
            [](Entity& e) { return e.getSubSceneComponent(); },
            py::return_value_policy::reference)
        .def("add_subscene_component", &Entity::addSubSceneComponent, py::return_value_policy::reference)
        .def("make_entityref", &Entity::makeEntityRef)
        .def("resolve_entityref", &Entity::resolveEntityRef, py::return_value_policy::reference)
        .def("detach_entity_from_prefab", [](Entity* ent) {
            return ent->detachEntityFromPrefab().release();
        });

    pyScene
        .def(
            "add_entity",
            [](Scene* scene, Entity* ent) -> Entity*
            {
                scene->addEntity(ent->clone()); return scene->getObjects().back().get();
            }, py::return_value_policy::reference)
        .def("resolve_entityref", &Scene::resolveEntityRef, py::return_value_policy::reference)
        .def_property_readonly(
            "entities",
            [](Scene* scene) -> std::vector<Entity*> {
                std::vector<Entity*> entities;
                for (std::unique_ptr<Entity> const& ent : scene->getObjects())
                {
                    entities.push_back(ent.get());
                }
                return entities;
            },
            py::return_value_policy::reference_internal);

    pyComponentsSchema
        .def_readonly("components", &ComponentsSchema::components, py::return_value_policy::reference)
        .def_readonly("schema", &ComponentsSchema::schema, py::return_value_policy::reference);

    pyColor
        .def(py::init<>())
        .def(py::init<uint8_t, uint8_t, uint8_t, uint8_t>());

    pyEntityLib
        .def(py::init<std::string>())
        .def_readwrite("validation_enabled", &EntityLib::validationEnabled)
        .def_readonly("root_path", &EntityLib::rootPath)
        .def_readwrite("rawdata_path", &EntityLib::rawdataPath) // unit-test need to write it
        .def_readonly("tools_dir", &EntityLib::toolsDir)
        .def_readonly("schema", &EntityLib::schema, py::return_value_policy::reference)
        .def_readonly(
            "component_dependencies",
            &EntityLib::componentDependencies,
            py::return_value_policy::reference)
        .def(
            "load_entity",
            [](EntityLib* lib, std::string const& path) { return lib->loadEntity(path).release(); },
            "entityPath"_a)
        .def(
            "load_scene",
            [](EntityLib* lib, std::string const& path) { return lib->loadScene(path).release(); })
        .def(
            "load_entity_read_only",
            [](EntityLib* lib, std::string const& path) { return lib->loadEntityReadOnly(path); },
            py::return_value_policy::reference)
        .def(
            "load_scene_read_only",
            [](EntityLib* lib, std::string const& path) { return lib->loadSceneReadOnly(path); },
            py::return_value_policy::reference)
        .def("save_entity", &EntityLib::saveEntity, "entity"_a, "_entityPath"_a)
        .def("save_scene", &EntityLib::saveScene)
        .def("get_entity_cache", &EntityLib::getEntityCache, py::return_value_policy::reference)
        .def("get_scene_cache", &EntityLib::getSceneCache, py::return_value_policy::reference)
        .def("clear_cache", &EntityLib::clearCache)
        .def(
            "make_instance_of",
            [](EntityLib* lib, std::string const& path) {
                return lib->makeInstanceOf(path).release();
            },
            "instanceOf"_a);

    pyEntityRef
        .def(py::init<>())
        .def(py::init<std::string>())
        .def_readwrite("entity_path", &EntityRef::entityPath)
        .def("__str__", [](EntityRef* ref) { return ref->entityPath; });

    pyEntityFile
        .def_property_readonly(
            "data",
            [](EntityLib::EntityFile* entF) { return entF->data.get(); },
            py::return_value_policy::reference)
        .def_readonly("time", &EntityLib::EntityFile::time, py::return_value_policy::reference);

    pySceneFile
        .def_property_readonly(
            "data",
            [](EntityLib::SceneFile* sceneF) { return sceneF->data.get(); },
            py::return_value_policy::reference)
        .def_readonly("time", &EntityLib::SceneFile::time, py::return_value_policy::reference);

    py::register_exception<Ent::JsonValidation>(ent, "JsonValidation");
}

/// @endcond
