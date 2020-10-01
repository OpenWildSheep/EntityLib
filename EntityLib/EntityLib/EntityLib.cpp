#include "include/EntityLib.h"

#include "Tools.h"
#include "SchemaLoader.h"
#include "include/ComponentMerge.h"

#pragma warning(push, 0)
#pragma warning(disable : 4702)
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <utility>

#include "external/json.hpp"
#include "ValidJson.h"
#pragma warning(pop)

/// \cond PRIVATE

using namespace nlohmann;

// char schemaPath[2048] = {};

static Ent::Node loadNode(Ent::Subschema const& nodeSchema, json const& data, Ent::Node const* super);
static std::unique_ptr<Ent::Scene> loadScene(
    Ent::EntityLib const& entLib,
    Ent::ComponentsSchema const& schema,
    json const& entities,
    Ent::Scene const* super);
static json saveScene(Ent::ComponentsSchema const& schema, Ent::Scene const& scene);

namespace Ent
{
    char const* colorSchemaName = "#/definitions/Color";
    static Ent::Node makeDefaultColorField(EntityLib const& entlib)
    {
        Ent::Override<float> zero{ 0.f, tl::nullopt, tl::nullopt };
        std::vector<nonstd::value_ptr<Ent::Node>> nodes{
            nonstd::make_value<Ent::Node>(zero, nullptr),
            nonstd::make_value<Ent::Node>(zero, nullptr),
            nonstd::make_value<Ent::Node>(zero, nullptr),
            nonstd::make_value<Ent::Node>(zero, nullptr),
        };
        Ent::Subschema const& colorSchema = entlib.schema.schema.allDefinitions.at(colorSchemaName);
        return Node{ Array{ nodes }, &colorSchema };
    }

    BadType::BadType()
        : std::runtime_error("Bad node type")
    {
    }

    EntityLib::EntityLib(std::filesystem::path _rootPath)
        : rootPath(std::move(_rootPath)) // Read schema and dependencies
    {
        rawdataPath = rootPath / "RawData";
        toolsDir = rootPath / "Tools";
        auto schemaPath = toolsDir / "WildPipeline/Schema";

        json schemaDocument = mergeComponents(toolsDir);

        SchemaLoader loader(schemaPath);

        loader.readSchema(&schema.schema, schemaDocument, schemaDocument);

        auto& compList = schema.schema.root->properties["Objects"]
                             ->singularItems
                             ->get() // get the Object
                             .properties["Components"]
                             ->singularItems
                             ->get() // get the Component
                             .oneOf;

        for (SubschemaRef& comp : *compList)
        {
            auto&& compName = comp->properties.at("Type")->constValue->get<std::string>();
            auto&& compSchema = *comp->properties.at("Data");
            compSchema.meta = comp->meta;
            schema.components.emplace(compName, &compSchema);
        }

        json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");
        for (json const& comp : dependencies["Dependencies"])
        {
            auto name = comp["className"].get<std::string>();
            std::vector<std::string> deps;
            for (json const& dep : comp["dependencies"])
            {
                if (not dep["Optional"].get<bool>())
                {
                    deps.push_back(dep["Name"].get<std::string>());
                }
            }
            componentDependencies.emplace(std::move(name), std::move(deps));
        }
    }

    EntityLib::~EntityLib() = default;

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
    {
    }

    DataType Node::getDataType() const
    {
        return (DataType)value.which();
    }

    Node* Node::at(char const* field)
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(field).get();
        }
        throw BadType();
    }
    Node const* Node::at(char const* field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(field).get();
        }
        throw BadType();
    }
    bool Node::count(char const* field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().count(field) != 0;
        }
        throw BadType();
    }
    Node* Node::at(size_t index)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data[index].get();
        }
        throw BadType();
    }
    Node const* Node::at(size_t index) const
    {
        if (value.is<Object>())
        {
            auto iter = value.get<Object>().begin();
            std::advance(iter, index);
            return iter->second.get();
        }
        if (value.is<Array>())
        {
            return value.get<Array>().data[index].get();
        }
        throw BadType();
    }
    size_t Node::size() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data.size();
        }
        throw BadType();
    }

    float Node::getFloat() const
    {
        if (value.is<Override<float>>())
        {
            return value.get<Override<float>>().get();
        }
        if (value.is<Override<int64_t>>())
        {
            return static_cast<float>(value.get<Override<int64_t>>().get());
        }
        throw BadType();
    }
    int64_t Node::getInt() const
    {
        if (value.is<Override<int64_t>>())
        {
            return value.get<Override<int64_t>>().get();
        }
        throw BadType();
    }
    char const* Node::getString() const
    {
        if (value.is<Override<std::string>>())
        {
            return value.get<Override<std::string>>().get().c_str();
        }
        throw BadType();
    }
    bool Node::getBool() const
    {
        if (value.is<Override<bool>>())
        {
            return value.get<Override<bool>>().get();
        }
        throw BadType();
    }

    EntityRef Node::getEntityRef() const
    {
        if (value.is<Override<EntityRef>>())
        {
            return value.get<Override<EntityRef>>().get();
        }
        throw BadType();
    }

    const Node::Value& Node::GetRawValue() const
    {
        return value;
    }

    void Node::setFloat(float val)
    {
        value.get<Override<float>>().set(val);
    }
    void Node::setInt(int64_t val)
    {
        value.get<Override<int64_t>>().set(val);
    }
    void Node::setString(char const* val)
    {
        value.get<Override<std::string>>().set(val);
    }
    void Node::setBool(bool val)
    {
        value.get<Override<bool>>().set(val);
    }

    void Node::setEntityRef(EntityRef entityRef)
    {
        value.get<Override<EntityRef>>().set(entityRef);
    }

    struct UnSet
    {
        template <typename T>
        void operator()(Override<T>& ov) const
        {
            ov.unset();
        }

        template <typename U>
        void operator()(U& notOverride) const
        {
            (void*)&notOverride;
            throw BadType();
        }
    };

    void Node::unset()
    {
        mapbox::util::apply_visitor(UnSet{}, value);
    }

    struct IsSet
    {
        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return ov.isSet();
        }

        template <typename U>
        bool operator()(U const& notOverride) const
        {
            (void*)&notOverride;
            // throw BadType();
            return true; // Object and Array are always considered as overrided
        }
    };

    bool Node::isSet() const
    {
        return mapbox::util::apply_visitor(IsSet{}, value);
    }

    struct HasDefaultValue
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return (not ov.prefabValue.has_value()) and (not ov.overrideValue.has_value());
        }

        bool operator()(Null const&) const
        {
            return false;
        }

        bool operator()(Array const& arr) const
        {
            return std::all_of(begin(arr.data), end(arr.data), std::mem_fn(&Node::hasDefaultValue));
        }

        bool operator()(Object const& obj) const
        {
            return std::all_of(begin(obj), end(obj), [](auto&& name_node) {
                return std::get<1>(name_node)->hasDefaultValue();
            });
        }
    };

    bool Node::hasDefaultValue() const
    {
        return mapbox::util::apply_visitor(HasDefaultValue{ schema }, value);
    }

    struct Detach
    {
        Subschema const* schema;

        template <typename T>
        Node operator()(Override<T> const& ov) const
        {
            return Node(ov.detach(), schema);
        }

        Node operator()(Null const& val) const
        {
            (void*)&val; // Null contains nothing so it is not needed
            return Node(Null{}, schema);
        }

        Node operator()(Array const& arr) const
        {
            Array out;
            for (auto&& item : arr.data)
            {
                out.data.emplace_back(nonstd::make_value<Node>(item->detach()));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& obj) const
        {
            Object out;
            for (auto&& name_node : obj)
            {
                out.emplace(
                    std::get<0>(name_node),
                    nonstd::make_value<Node>(std::get<1>(name_node)->detach()));
            }
            return Node(std::move(out), schema);
        }
    };

    Node Node::detach() const
    {
        return mapbox::util::apply_visitor(Detach{ schema }, value);
    }

    struct MakeInstanceOf
    {
        Subschema const* schema;

        template <typename T>
        Node operator()(Override<T> const& ov) const
        {
            return Node(ov.makeInstanceOf(), schema);
        }

        Node operator()(Null const& val) const
        {
            (void*)&val; // Null contains nothing so it is not needed
            return Node(Null{}, schema);
        }

        Node operator()(Array const& arr) const
        {
            Array out;
            for (auto&& item : arr.data)
            {
                out.data.emplace_back(nonstd::make_value<Node>(item->makeInstanceOf()));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& obj) const
        {
            Object out;
            for (auto&& name_node : obj)
            {
                out.emplace(
                    std::get<0>(name_node),
                    nonstd::make_value<Node>(std::get<1>(name_node)->makeInstanceOf()));
            }
            return Node(std::move(out), schema);
        }
    };

    Node Node::makeInstanceOf() const
    {
        return mapbox::util::apply_visitor(MakeInstanceOf{ schema }, value);
    }

    struct HasOverride
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return ov.isSet();
        }

        bool operator()(Null const& val) const
        {
            (void*)&val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& arr) const
        {
            return arr.hasOverride();
        }

        bool operator()(Object const& obj) const
        {
            for (auto&& name_node : obj)
            {
                if (std::get<1>(name_node)->hasOverride())
                {
                    return true;
                }
            }
            return false;
        }
    };

    bool Node::hasOverride() const
    {
        return mapbox::util::apply_visitor(HasOverride{ schema }, value);
    }

    std::vector<char const*> Node::getFieldNames() const
    {
        if (value.is<Object>())
        {
            std::vector<char const*> fields;
            for (auto&& f : value.get<Object>())
            {
                fields.push_back(f.first.c_str());
            }
            return fields;
        }
        throw BadType();
    }

    std::vector<Node const*> Node::getItems() const
    {
        if (value.is<Array>())
        {
            std::vector<Node const*> items;
            for (auto&& n : value.get<Array>().data)
            {
                items.push_back(n.get());
            }
            return items;
        }
        throw BadType();
    }

    Node* Node::push()
    {
        if (value.is<Array>())
        {
            if (SubschemaRef const* itemSchema = schema->singularItems.get())
            {
                value.get<Array>().data.emplace_back(
                    nonstd::make_value<Node>(loadNode(itemSchema->get(), json(), nullptr)));
                return value.get<Array>().data.back().get();
            }
        }
        throw BadType();
    }
    void Node::pop()
    {
        if (value.is<Array>())
        {
            if (schema->singularItems != nullptr)
            {
                value.get<Array>().data.pop_back();
                return;
            }
        }
        throw BadType();
    }

    void Node::clear()
    {
        if (value.is<Array>())
        {
            value.get<Array>().data.clear();
        }
        else
        {
            throw BadType();
        }
    }

    bool Node::empty() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data.empty();
        }
        throw BadType();
    }

    struct IsDefault
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return not ov.prefabValue.has_value() and not ov.overrideValue.has_value();
        }

        bool operator()(Null const& val) const
        {
            (void*)&val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& arr) const
        {
            (void*)&arr;
            return false;
        }

        bool operator()(Object const& obj) const
        {
            (void*)&obj;
            return false;
        }
    };

    bool Node::isDefault() const
    {
        return mapbox::util::apply_visitor(IsDefault{ schema }, value);
    }

    float Node::getDefaultFloat() const
    {
        if (value.is<Override<float>>())
        {
            return value.get<Override<float>>().defaultValue;
        }
        if (value.is<Override<int64_t>>())
        {
            return static_cast<float>(value.get<Override<int64_t>>().defaultValue);
        }
        throw BadType();
    }
    int64_t Node::getDefaultInt() const
    {
        if (value.is<Override<int64_t>>())
        {
            return value.get<Override<int64_t>>().defaultValue;
        }
        throw BadType();
    }
    char const* Node::getDefaultString() const
    {
        if (value.is<Override<std::string>>())
        {
            return value.get<Override<std::string>>().defaultValue.c_str();
        }
        throw BadType();
    }
    bool Node::getDefaultBool() const
    {
        if (value.is<Override<bool>>())
        {
            return value.get<Override<bool>>().defaultValue;
        }
        throw BadType();
    }

    char const* Node::getTypeName() const
    {
        if (schema == nullptr)
        {
            return nullptr;
        }
        return schema->name.c_str();
    }

    Subschema const* Node::getSchema() const
    {
        return schema;
    }

    // ********************************* SubSceneComponent ****************************************
    SubSceneComponent::SubSceneComponent(
        bool _isEmbedded, Override<std::string> _file, size_t _index, std::unique_ptr<Scene> embedded)
        : isEmbedded(_isEmbedded)
        , file(std::move(_file))
        , index(_index)
        , embedded(std::move(embedded))
    {
    }

    void SubSceneComponent::makeEmbedded(bool _embedded)
    {
        isEmbedded = _embedded;
        if (_embedded)
        {
            if (embedded == nullptr)
            {
                embedded = std::make_unique<Scene>();
            }
            file.set(std::string());
        }
        else
        {
            embedded.reset();
        }
    }

    // ********************************* Entity ***************************************************

    Entity::Entity(EntityLib const& _entlib)
        : entlib(&_entlib)
        , name(std::string(), tl::nullopt, tl::nullopt)
        , color(Ent::makeDefaultColorField(_entlib))
        , thumbnail(std::string(), tl::nullopt, tl::nullopt)
        , instanceOf(std::string(), tl::nullopt, tl::nullopt)
    {
    }

    Entity::Entity(
        EntityLib const& _entlib,
        Override<std::string> _name,
        std::map<std::string, Component> _components,
        std::unique_ptr<SubSceneComponent> _subSceneComponent,
        Node _color,
        Override<std::string> _thumbnail,
        Override<std::string> _instanceOf,
        bool _hasASuper)
        : entlib(&_entlib)
        , name(std::move(_name))
        , components(std::move(_components))
        , subSceneComponent(std::move(_subSceneComponent))
        , color(std::move(_color))
        , thumbnail(std::move(_thumbnail))
        , instanceOf(std::move(_instanceOf))
        , hasASuper(_hasASuper)
    {
        updateSubSceneOwner();
    }

    char const* Entity::getName() const
    {
        return name.get().c_str();
    }
    void Entity::setName(std::string _name)
    {
        ENTLIB_ASSERT_MSG(
            not hasASuper,
            "A SubEntity of an instance which override a SubEntity in a prefab can't be renamed. "
            "Check the canBeRenamed method.");
        name.set(std::move(_name));
    }
    bool Entity::canBeRenamed() const
    {
        return not hasASuper;
    }
    void Entity::setCanBeRenamed(bool can)
    {
        hasASuper = not can;
    }

    char const* Entity::getInstanceOf() const
    {
        return instanceOf.isDefault() ? nullptr : instanceOf.get().c_str();
    }
    char const* Entity::getThumbnail() const
    {
        return thumbnail.isDefault() ? nullptr : thumbnail.get().c_str();
    }
    void Entity::setThumbnail(std::string _thumbPath)
    {
        thumbnail.set(std::move(_thumbPath));
    }
    std::array<uint8_t, 4> Entity::getColor() const
    {
        std::array<uint8_t, 4> col{};
        for (size_t i = 0; i < 4; ++i)
        {
            col[i] = (uint8_t)color.at(i)->getFloat();
        }
        return col;
    }
    void Entity::setColor(std::array<uint8_t, 4> _color)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            color.at(i)->setFloat(_color[i]);
        }
    }
    Component* Entity::addComponent(char const* type)
    {
        if (entlib->componentDependencies.count(type) != 0) // Could be an editor componant
        {
            for (auto&& dep : entlib->componentDependencies.at(type))
            {
                addComponent(dep.c_str());
            }
        }
        Ent::Subschema const& compSchema = *entlib->schema.components.at(type);
        Ent::Component comp{ false, type, loadNode(compSchema, json(), nullptr), 1, components.size() };
        auto iter_bool = components.emplace(type, std::move(comp));
        return &(iter_bool.first->second);
    }
    Component const* Entity::getComponent(char const* type) const
    {
        auto iter = components.find(type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    Component* Entity::getComponent(char const* type)
    {
        auto iter = components.find(type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    void Entity::removeComponent(char const* type)
    {
        // TODO : Use dependencies
        components.erase(type);
    }

    std::vector<char const*> Entity::getComponentTypes() const
    {
        std::vector<char const*> types;
        for (auto&& type_comp : components)
        {
            types.push_back(type_comp.first.c_str());
        }
        return types;
    }

    std::map<std::string, Component> const& Entity::getComponents() const
    {
        return components;
    }

    SubSceneComponent const* Entity::getSubSceneComponent() const
    {
        if (subSceneComponent != nullptr)
        {
            return &(*subSceneComponent);
        }
        return nullptr;
    }

    SubSceneComponent* Entity::getSubSceneComponent()
    {
        if (subSceneComponent != nullptr)
        {
            return &(*subSceneComponent);
        }
        return nullptr;
    }

    SubSceneComponent* Entity::addSubSceneComponent()
    {
        if (subSceneComponent == nullptr)
        {
            subSceneComponent = std::make_unique<SubSceneComponent>();
        }
        return &(*subSceneComponent);
    }

    void Entity::removeSubSceneComponent()
    {
        if (subSceneComponent != nullptr)
        {
            subSceneComponent.reset();
        }
    }

    std::unique_ptr<Entity> Entity::makeInstanceOf() const
    {
        std::map<std::string, Component> instComponents;
        std::unique_ptr<SubSceneComponent> instSubSceneComponent;

        for (auto&& name_comp : components)
        {
            instComponents.emplace(name_comp.first, name_comp.second.makeInstanceOf());
        }
        if (subSceneComponent != nullptr)
        {
            instSubSceneComponent = subSceneComponent->makeInstanceOf();
        }

        return std::make_unique<Entity>(
            *entlib,
            name.makeInstanceOf(),
            std::move(instComponents),
            std::move(instSubSceneComponent),
            color.makeInstanceOf(),
            thumbnail.makeInstanceOf(),
            instanceOf);
    }

    bool Entity::hasOverride() const
    {
        if (name.isSet() or color.hasOverride() or thumbnail.isSet() or instanceOf.isSet())
        {
            return true;
        }
        for (auto&& name_comp : components)
        {
            if (name_comp.second.hasOverride())
            {
                return true;
            }
        }
        return subSceneComponent != nullptr and subSceneComponent->hasOverride();
    }

    void Entity::setParentScene(Scene* scene)
    {
        parentScene = scene;
    }

    Scene* Entity::getParentScene() const
    {
        return parentScene;
    }

    static std::tuple<std::vector<std::string>, Entity*, Scene*> getAbsolutePathReversed(Entity* entity)
    {
        Entity* current = entity;
        Entity* rootEntity = nullptr;
        Scene* rootScene = nullptr;
        std::vector<std::string> path;
        while (current != nullptr)
        {
            path.emplace_back(current->getName());
            rootEntity = current;
            rootScene = current->getParentScene();
            current =
                current->getParentScene() ? current->getParentScene()->getOwnerEntity() : nullptr;
        }
        return { std::move(path), rootEntity, rootScene };
    }

    EntityRef Entity::makeEntityRef(Entity& entity)
    {
        // get the two absolute path
        auto&& thisPathInfos = getAbsolutePathReversed(this);
        auto&& entityPathInfos = getAbsolutePathReversed(&entity);

        Entity *thisRootEntity = std::get<1>(thisPathInfos),
               *entityRootEntity = std::get<1>(entityPathInfos);
        Scene *thisRootScene = std::get<2>(thisPathInfos),
              *entityRootScene = std::get<2>(entityPathInfos);

        // entities should either share a common root scene
        // or a common root entity if they are in a .entity (i.e there is no root scene)
        if (thisRootScene != entityRootScene
            or thisRootEntity == nullptr and thisRootEntity != entityRootEntity)
        {
            // cannot reference unrelated entities
            return {};
        }

        auto&& thisPath = std::get<0>(thisPathInfos);
        auto&& entityPath = std::get<0>(entityPathInfos);

        std::string relativePath =
            computeRelativePath(std::move(thisPath), std::move(entityPath), false);

        return { std::move(relativePath) };
    }

    static Scene* getSubScene(Entity* entity)
    {
        if (auto* subScene = entity->getSubSceneComponent())
        {
            if (subScene->isEmbedded)
            {
                return subScene->embedded.get();
            }
            // TODO: major 2020-09-26 @Seb: else open non embedded subscene ?
        }
        return nullptr;
    }

    static Entity* findChild(Scene* scene, const std::string& name)
    {
        auto&& children = scene->objects;
        const auto found = std::find_if(children.begin(), children.end(), [&name](auto& childPtr) {
            return childPtr->getName() == name;
        });
        return found == children.end() ? nullptr : found->get();
    }

    static Entity* resolveEntityRefRecursive(
        Entity* current, Scene* up, Scene* down, std::vector<std::string>& path)
    {
        auto& head = path.front();

        if (head == "..")
        {
            // go up in hierarchy
            if (up == nullptr)
            {
                // broken ref
                return nullptr;
            }
            current = up->getOwnerEntity();
            down = up;
            up = current == nullptr ? nullptr : current->getParentScene();
        }
        else if (head != ".")
        {
            // go down in child hierarchy named "head"
            if (down == nullptr)
            {
                // broken ref
                return nullptr;
            }
            current = findChild(down, head);
            up = down;
            down = current == nullptr ? nullptr : getSubScene(current);
        }
        path.erase(path.begin());
        if (path.empty())
        {
            return current;
        }
        return resolveEntityRefRecursive(current, up, down, path);
    }

    Entity* Entity::resolveEntityRef(const EntityRef& _entityRef)
    {
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath, '/');

        Entity* current = this;
        Scene* down = getSubScene(current);
        Scene* up = current->getParentScene();

        return resolveEntityRefRecursive(current, up, down, parts);
    }

    void Entity::updateSubSceneOwner()
    {
        if (auto* subScene = getSubSceneComponent())
        {
            if (subScene->isEmbedded)
            {
                subScene->embedded->setOwnerEntity(this);
            }
        }
    }

    // ********************************* Scene ***************************************************

    Scene::Scene() = default;

    Scene::Scene(std::vector<std::unique_ptr<Entity>> entities)
        : objects(std::move(entities))
    {
        updateChildrenContext();
    }

    Entity* Scene::resolveEntityRef(const EntityRef& _entityRef)
    {
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath, '/');

        Entity* current = getOwnerEntity();
        Scene* down = this;
        Scene* up = current == nullptr ? nullptr : current->getParentScene();

        return resolveEntityRefRecursive(current, up, down, parts);
    }

    Entity* Scene::findEntityByPath(const std::string& _path)
    {
        return resolveEntityRef({ _path });
    }

    std::unique_ptr<Scene> Scene::makeInstanceOf() const
    {
        std::vector<std::unique_ptr<Entity>> instanceEntities;
        auto scene = std::make_unique<Scene>();
        for (auto const& ent : objects)
        {
            instanceEntities.emplace_back(ent->makeInstanceOf());
            instanceEntities.back()->setParentScene(scene.get());
        }
        scene->objects = std::move(instanceEntities);
        return scene;
    }

    bool Scene::hasOverride() const
    {
        for (std::unique_ptr<Entity> const& ent : objects)
        {
            if (ent->hasOverride())
                return true;
        }
        return false;
    }

    Entity* Scene::getOwnerEntity() const
    {
        return ownerEntity;
    }

    void Scene::setOwnerEntity(Entity* entity)
    {
        ownerEntity = entity;
    }

    void Scene::updateChildrenContext()
    {
        for (auto& childEntityPtr : objects)
        {
            childEntityPtr->setParentScene(this);
        }
    }

} // namespace Ent

// ********************************** Load/Save ***********************************************

static Ent::Node loadFreeObjectNode(json const& data)
{
    Ent::Node result;
    switch (data.type())
    {
    case nlohmann::detail::value_t::null: result = Ent::Node(Ent::Null{}, nullptr); break;
    case nlohmann::detail::value_t::string:
        result = Ent::Node(
            Ent::Override<std::string>(std::string(), tl::nullopt, data.get<std::string>()), nullptr);
        break;
    case nlohmann::detail::value_t::boolean:
        result = Ent::Node(Ent::Override<bool>(bool{}, tl::nullopt, data.get<bool>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
        result =
            Ent::Node(Ent::Override<int64_t>(int64_t{}, tl::nullopt, data.get<int64_t>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_float:
        result = Ent::Node(Ent::Override<float>(float{}, tl::nullopt, data.get<float>()), nullptr);
        break;
    case nlohmann::detail::value_t::object:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadFreeObjectNode(value);
            object.emplace(name, nonstd::make_value<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), nullptr);
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        Ent::Array arr;
        for (auto const& item : data)
        {
            Ent::Node tmpNode = loadFreeObjectNode(item);
            arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(arr), nullptr);
    }
    break;
    case nlohmann::detail::value_t::discarded: break;
    }
    return result;
}

static Ent::Node const emptyNode(Ent::Null(), nullptr);

static Ent::Node loadNode(Ent::Subschema const& nodeSchema, json const& data, Ent::Node const* super)
{
    Ent::Node result;

    switch (nodeSchema.type)
    {
    case Ent::DataType::null: result = Ent::Node(Ent::Null{}, &nodeSchema); break;
    case Ent::DataType::string:
    {
        std::string const def = nodeSchema.defaultValue.is<Ent::Null>() ?
                                    std::string() :
                                    nodeSchema.defaultValue.get<std::string>();
        tl::optional<std::string> const supVal = (super != nullptr and super->isSet()) ?
                                                     tl::optional<std::string>(super->getString()) :
                                                     tl::optional<std::string>(tl::nullopt);
        tl::optional<std::string> const val =
            data.is_string() ? tl::optional<std::string>(data.get<std::string>()) :
                               tl::optional<std::string>(tl::nullopt);
        result = Ent::Node(Ent::Override<std::string>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::boolean:
    {
        bool const def =
            nodeSchema.defaultValue.is<Ent::Null>() ? bool{} : nodeSchema.defaultValue.get<bool>();
        tl::optional<bool> const supVal = (super != nullptr and super->isSet()) ?
                                              tl::optional<bool>(super->getBool()) :
                                              tl::optional<bool>(tl::nullopt);
        tl::optional<bool> const val = data.is_boolean() ? tl::optional<bool>(data.get<bool>()) :
                                                           tl::optional<bool>(tl::nullopt);
        result = Ent::Node(Ent::Override<bool>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::integer:
    {
        int64_t const def = nodeSchema.defaultValue.is<Ent::Null>() ?
                                int64_t{} :
                                nodeSchema.defaultValue.get<int64_t>();
        tl::optional<int64_t> const supVal = (super != nullptr and super->isSet()) ?
                                                 tl::optional<int64_t>(super->getInt()) :
                                                 tl::optional<int64_t>(tl::nullopt);
        tl::optional<int64_t> const val = data.is_number_integer() or data.is_number_unsigned() ?
                                              tl::optional<int64_t>(data.get<int64_t>()) :
                                              tl::optional<int64_t>(tl::nullopt);
        result = Ent::Node(Ent::Override<int64_t>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::number:
    {
        float const def =
            nodeSchema.defaultValue.is<Ent::Null>() ? float{} : nodeSchema.defaultValue.get<float>();
        tl::optional<float> const supVal = (super != nullptr and super->isSet()) ?
                                               tl::optional<float>(super->getFloat()) :
                                               tl::optional<float>(tl::nullopt);
        tl::optional<float> const val =
            data.is_number_float() or data.is_number_integer() or data.is_number_unsigned() ?
                tl::optional<float>(data.get<float>()) :
                tl::optional<float>(tl::nullopt);
        result = Ent::Node(Ent::Override<float>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::object:
    {
        Ent::Object object;

        for (auto&& name_sub : nodeSchema.properties)
        {
            std::string const& name = std::get<0>(name_sub);
            Ent::Node const* superProp = (super != nullptr) ? super->at(name.c_str()) : nullptr;
            static json const emptyJson;
            json const& prop = data.count(name) != 0 ? data.at(name) : emptyJson;
            Ent::Node tmpNode = loadNode(*std::get<1>(name_sub), prop, superProp);
            object.emplace(name, nonstd::make_value<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), &nodeSchema);
    }
    break;
    case Ent::DataType::array:
    {
        Ent::Array arr;
        size_t index = 0;
        if (nodeSchema.singularItems)
        {
            if (data.is_null()) // No overrided
            {
                if (super != nullptr)
                {
                    for (Ent::Node const* subSuper : super->getItems())
                    {
                        Ent::Node tmpNode =
                            loadNode(nodeSchema.singularItems->get(), json(), subSuper);
                        arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                        ++index;
                    }
                }
            }
            else
            {
                for (auto const& item : data)
                {
                    Ent::Node const* subSuper =
                        (super != nullptr and (super->size() > index)) ? super->at(index) : nullptr;
                    Ent::Node tmpNode = loadNode(nodeSchema.singularItems->get(), item, subSuper);
                    arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                    ++index;
                }
            }
        }
        else
        {
            ENTLIB_ASSERT(nodeSchema.linearItems.has_value());
            for (Ent::SubschemaRef const& sub : *nodeSchema.linearItems)
            {
                Ent::Node const* subSuper =
                    (super != nullptr and super->size() > index) ? super->at(index) : nullptr;
                static json const emptyJson;
                json const& prop = data.size() > index ? data.at(index) : emptyJson;
                Ent::Node tmpNode = loadNode(*sub, prop, subSuper);
                arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                ++index;
            }
        }
        result = Ent::Node(std::move(arr), &nodeSchema);
    }
    break;
    case Ent::DataType::entityRef:
    {
        Ent::EntityRef const def;

        tl::optional<Ent::EntityRef> const supVal =
            (super != nullptr and super->isSet()) ?
                tl::optional<Ent::EntityRef>(super->getEntityRef()) :
                tl::optional<Ent::EntityRef>(tl::nullopt);

        tl::optional<std::string> const refString =
            data.is_string() ? data.get<std::string>() : tl::optional<std::string>(tl::nullopt);

        tl::optional<Ent::EntityRef> const val =
            refString.has_value() ?
                tl::optional<Ent::EntityRef>(Ent::EntityRef{ refString.value() }) :
                tl::optional<Ent::EntityRef>(tl::nullopt);

        result = Ent::Node(Ent::Override<Ent::EntityRef>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("Invalid DataType"); break;
    }
    return result;
}

static json saveNode(Ent::Subschema const& schema, Ent::Node const& node)
{
    json data;
    switch (schema.type)
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = node.getString(); break;
    case Ent::DataType::boolean: data = node.getBool(); break;
    case Ent::DataType::integer: data = node.getInt(); break;
    case Ent::DataType::number: data = node.getFloat(); break;
    case Ent::DataType::object:
    {
        data = json::object();
        for (auto const& name_sub : schema.properties)
        {
            auto&& name = std::get<0>(name_sub);
            Ent::Node const* subNode = node.at(name.c_str());
            if (subNode->hasOverride())
            {
                json subJson = saveNode(*std::get<1>(name_sub), *subNode);
                data[name] = std::move(subJson);
            }
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        for (Ent::Node const* item : node.getItems())
        {
            if (item->hasOverride())
            {
                json tmpNode = saveNode(schema.singularItems->get(), *item);
                data.emplace_back(std::move(tmpNode));
            }
            else
            {
                data.emplace_back(json());
            }
        }
    }
    break;
    case Ent::DataType::entityRef:
    {
        Ent::EntityRef ref = node.getEntityRef();
        data = ref.entityPath;
    }
    break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("DataType is Ent::DataType::COUNT"); break;
    }
    return data;
}

static std::unique_ptr<Ent::Entity> loadEntity(
    Ent::EntityLib const& entlib,
    Ent::ComponentsSchema const& schema,
    json const& entNode,
    Ent::Entity const* superEntityFromParentEntity)
{
    ENTLIB_ASSERT(
        superEntityFromParentEntity == nullptr
        or superEntityFromParentEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    tl::optional<std::string> instanceOf;
    auto superEntityOfThisEntity = std::make_unique<Ent::Entity>(entlib);
    ENTLIB_ASSERT(superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    bool superIsInit = false;
    Ent::Entity const* superEntity = superEntityOfThisEntity.get();
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    if (entNode.count("InstanceOf") != 0)
    {
        instanceOf = entNode.at("InstanceOf").get<std::string>();
        std::filesystem::path instanceOfPath = *instanceOf;
        if (instanceOfPath.is_absolute())
        {
            superEntityOfThisEntity = entlib.loadEntity(*instanceOf, superEntityFromParentEntity);
            superEntity = superEntityOfThisEntity.get();
            ENTLIB_ASSERT(
                superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
            ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        }
        else
        {
            instanceOfPath = entlib.rawdataPath / instanceOfPath;
            superEntityOfThisEntity = entlib.loadEntity(instanceOfPath, superEntityFromParentEntity);
            superEntity = superEntityOfThisEntity.get();
            ENTLIB_ASSERT(
                superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
            ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        }
        superIsInit = true;
    }
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    if (not superIsInit and superEntityFromParentEntity != nullptr)
    {
        superEntity = superEntityFromParentEntity;
        ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    }

    tl::optional<std::string> const thumbnail = entNode.count("Thumbnail") != 0 ?
                                                    entNode.at("Thumbnail").get<std::string>() :
                                                    tl::optional<std::string>();
    Ent::Override<std::string> superThumbnail = superEntity->getThumbnailValue();
    Ent::Override<std::string> ovThumbnail = superThumbnail.makeOverridedInstanceOf(thumbnail);

    tl::optional<std::string> const name = entNode.count("Name") != 0 ?
                                               entNode.at("Name").get<std::string>() :
                                               tl::optional<std::string>();

    Ent::Override<std::string> superName = superEntity->getNameValue();
    Ent::Override<std::string> ovName = superName.makeOverridedInstanceOf(name);

    Ent::Override<std::string> superInstanceOf = superEntity->getInstanceOfValue();
    Ent::Override<std::string> ovInstanceOf = superName.makeOverridedInstanceOf(instanceOf);

    Ent::Node ovColor = Ent::makeDefaultColorField(entlib);
    if (entNode.contains("Color"))
    {
        Ent::Subschema const& colorSchema =
            entlib.schema.schema.allDefinitions.at(Ent::colorSchemaName);
        ovColor = loadNode(
            colorSchema,
            entNode.at("Color"),
            superEntityFromParentEntity != nullptr ? &superEntityFromParentEntity->getColorValue() :
                                                     nullptr);
    }
    else
    {
        ovColor = superEntity->getColorValue().makeInstanceOf();
    }

    std::map<std::string, Ent::Component> components;
    std::unique_ptr<Ent::SubSceneComponent> subSceneComponent;
    size_t index = 0;
    if (entNode.count("Components") != 0)
    {
        json const& componentsNode = entNode.at("Components");
        for (json const& compNode : componentsNode)
        {
            auto const cmpType = compNode.at("Type").get<std::string>();
            json const& data = compNode.at("Data");
            if (cmpType == "SubScene")
            {
                Ent::SubSceneComponent const* superComp = superEntity->getSubSceneComponent();

                Ent::Override<std::string> file =
                    superComp != nullptr ?
                        superComp->file :
                        Ent::Override<std::string>(std::string(), tl::nullopt, tl::nullopt);

                auto fileInJson = (data.count("File") != 0) ?
                                      tl::optional<std::string>(data["File"].get<std::string>()) :
                                      tl::nullopt;
                file = file.makeOverridedInstanceOf(fileInJson);
                bool isEmbeddedInJson =
                    (data.count("isEmbedded") != 0) ? data["isEmbedded"].get<bool>() : false;
                auto subSceneComp =
                    std::make_unique<Ent::SubSceneComponent>(isEmbeddedInJson, file, index);
                if (subSceneComp->isEmbedded)
                {
                    subSceneComp->embedded = loadScene(
                        entlib,
                        schema,
                        data["Embedded"],
                        (superComp != nullptr ? superComp->embedded.get() : nullptr));
                }
                subSceneComponent = std::move(subSceneComp);
            }
            else
            {
                Ent::Component const* superComp = superEntity->getComponent(cmpType.c_str());
                auto const version =
                    compNode.count("Version") ? compNode.at("Version").get<size_t>() : 0;

                Ent::Subschema const& compSchema = *schema.components.at(cmpType);

                Ent::Component comp{
                    superComp != nullptr, // has a super component
                    cmpType,
                    loadNode(compSchema, data, (superComp != nullptr ? &superComp->root : nullptr)),
                    version,
                    index
                };

                components.emplace(cmpType, std::move(comp));
            }
            ++index;
        }
    }
    // Add undeclared componants to be able to get values inside (They are full reference to prefab)
    for (auto const& type_comp : superEntity->getComponents())
    {
        auto const& cmpType = std::get<0>(type_comp);
        auto const& superComp = std::get<1>(type_comp);
        if (components.count(cmpType) == 0)
        {
            Ent::Component comp{
                true, cmpType, superComp.root.makeInstanceOf(), superComp.version, superComp.index
            };

            components.emplace(cmpType, std::move(comp));
        }
        ++index;
    }
    {
        Ent::SubSceneComponent const* superComp = superEntity->getSubSceneComponent();
        if (superComp != nullptr and subSceneComponent == nullptr)
        {
            subSceneComponent = std::make_unique<Ent::SubSceneComponent>(
                superComp->isEmbedded,
                superComp->file,
                superComp->index,
                superComp->embedded->makeInstanceOf());
        }
    }
    return std::make_unique<Ent::Entity>(
        entlib,
        std::move(ovName),
        std::move(components),
        std::move(subSceneComponent),
        std::move(ovColor),
        std::move(ovThumbnail),
        std::move(ovInstanceOf));
}

std::unique_ptr<Ent::Entity>
Ent::EntityLib::loadEntity(std::filesystem::path const& entityPath, Ent::Entity const* super) const
{
    std::ifstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for read: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document;
    file >> document;

    if (validationEnabled)
    {
        try
        {
            validateEntity(schema.schema, toolsDir, document);
        }
        catch (...)
        {
            fprintf(stderr, "Error, loading entity : %ls\n", entityPath.c_str());
            throw;
        }
    }

    return ::loadEntity(*this, schema, document, super);
}

static std::unique_ptr<Ent::Scene> loadScene(
    Ent::EntityLib const& entLib,
    Ent::ComponentsSchema const& schema,
    json const& entities,
    Ent::Scene const* super)
{
    auto scene = std::make_unique<Ent::Scene>();

    // Add all entities from super scene ...
    std::set<std::string> entFromSuper;
    if (super != nullptr)
    {
        for (auto&& superEnt : super->objects)
        {
            entFromSuper.insert(superEnt->getName());
            json const* instEntNode = nullptr;
            // ... and look if there is an override.
            for (json const& entNode : entities)
            {
                std::string const instEntName = entNode.at("Name").get<std::string>();
                if (superEnt->getName() == instEntName)
                {
                    instEntNode = &entNode;
                    break;
                }
            }
            std::unique_ptr<Ent::Entity> ent =
                (instEntNode == nullptr) ?
                    superEnt->makeInstanceOf() :
                    ::loadEntity(entLib, schema, *instEntNode, superEnt.get());
            ent->setCanBeRenamed(false);
            ent->setParentScene(scene.get());
            scene->objects.emplace_back(std::move(ent));
        }
    }

    // Add new entities
    for (json const& entNode : entities)
    {
        std::string const name = entNode.at("Name").get<std::string>();
        if (entFromSuper.count(name) != 0)
        {
            continue;
        }
        std::unique_ptr<Ent::Entity> ent = ::loadEntity(entLib, schema, entNode, nullptr);
        ent->setParentScene(scene.get());
        scene->objects.emplace_back(std::move(ent));
    }

    return scene;
}

std::unique_ptr<Ent::Scene> Ent::EntityLib::loadScene(std::filesystem::path const& scenePath) const
{
    json document = loadJsonFile(scenePath);
    if (validationEnabled)
    {
        try
        {
            validateScene(schema.schema, toolsDir, document);
        }
        catch (...)
        {
            fprintf(stderr, "Error, loading scene : %ls\n", scenePath.c_str());
            throw;
        }
    }

    return ::loadScene(*this, schema, document.at("Objects"), nullptr);
}

static json saveEntity(Ent::ComponentsSchema const& schema, Ent::Entity const& entity)
{
    json entNode;

    // Always save Name since it is use for override
    entNode.emplace("Name", entity.getNameValue().get());

    if (entity.getInstanceOfValue().isSet())
    {
        entNode.emplace("InstanceOf", entity.getInstanceOfValue().get());
    }

    Ent::Subschema const& colorSchema = schema.schema.allDefinitions.at(Ent::colorSchemaName);
    if (entity.getColorValue().hasOverride())
    {
        entNode.emplace("Color", saveNode(colorSchema, entity.getColorValue()));
    }

    if (const char* thumbnail = entity.getThumbnail())
    {
        entNode.emplace("Thumbnail", thumbnail);
    }

    json& componentsNode = entNode["Components"] = json::array();
    std::vector<Ent::Component const*> sortedComp;
    for (auto&& type_comp : entity.getComponents())
    {
        sortedComp.push_back(&std::get<1>(type_comp));
    }
    Ent::Component subscenePlaceholder{ true, "SubScene", Ent::Node(), 1, 0 };
    if (Ent::SubSceneComponent const* subscene = entity.getSubSceneComponent())
    {
        subscenePlaceholder.index = subscene->index;
        sortedComp.push_back(&subscenePlaceholder);
    }
    std::sort(
        begin(sortedComp), end(sortedComp), [](Ent::Component const* cmp, Ent::Component const* cmp2) {
            return cmp->index < cmp2->index;
        });
    for (Ent::Component const* comp : sortedComp)
    {
        if (comp->type == "SubScene")
        {
            Ent::SubSceneComponent const* subscene = entity.getSubSceneComponent();
            ENTLIB_ASSERT(subscene != nullptr);
            bool const subsceneHasOverride = subscene->hasOverride();
            bool const hasInstanceOf = entity.getInstanceOf() != nullptr;
            if ((subsceneHasOverride and hasInstanceOf) or not hasInstanceOf)
            {
                json data;
                data.emplace("isEmbedded", subscene->isEmbedded);
                if (subscene->file.isSet())
                {
                    data.emplace("File", subscene->file.get());
                }
                if (subscene->isEmbedded)
                {
                    data.emplace("Embedded", saveScene(schema, *subscene->embedded)["Objects"]);
                }

                json compNode;
                compNode.emplace("Version", comp->version);
                compNode.emplace("Type", comp->type);
                compNode.emplace("Data", std::move(data));
                componentsNode.emplace_back(std::move(compNode));
            }
        }
        else if (not comp->hasTemplate or comp->root.hasOverride())
        {
            json compNode;
            compNode.emplace("Version", comp->version);
            compNode.emplace("Type", comp->type);
            compNode.emplace("Data", saveNode(*schema.components.at(comp->type), comp->root));

            componentsNode.emplace_back(std::move(compNode));
        }
    }
    return entNode;
}

std::unique_ptr<Ent::Entity> Ent::Entity::detachEntityFromPrefab() const
{
    std::map<std::string, Ent::Component> detComponents;
    size_t index = 0;
    for (auto const& type_comp : getComponents())
    {
        auto const& type = std::get<0>(type_comp);
        auto const& comp = std::get<1>(type_comp);

        Ent::Component detachedComp{ false, type, comp.root.detach(), 1, index };

        detComponents.emplace(type, std::move(detachedComp));
        ++index;
    }
    std::unique_ptr<SubSceneComponent> detSubSceneComponent;
    if (SubSceneComponent const* subscene = getSubSceneComponent())
    {
        detSubSceneComponent = std::make_unique<SubSceneComponent>();
        detSubSceneComponent->isEmbedded = subscene->isEmbedded;
        detSubSceneComponent->file = subscene->file;
        if (subscene->isEmbedded)
        {
            detSubSceneComponent->embedded = std::make_unique<Ent::Scene>();
            for (std::unique_ptr<Ent::Entity> const& subEntity : subscene->embedded->objects)
            {
                detSubSceneComponent->embedded->objects.push_back(subEntity->detachEntityFromPrefab());
                detSubSceneComponent->embedded->objects.back()->setParentScene(
                    detSubSceneComponent->embedded.get());
            }
        }
    }

    auto detachedColor = getColorValue().detach();

    return std::make_unique<Ent::Entity>(
        *entlib,
        getNameValue().detach().makeOverridedInstanceOf(std::string(getName()) + "_detached"),
        std::move(detComponents),
        std::move(detSubSceneComponent),
        std::move(detachedColor),
        getThumbnailValue().detach());
}

std::unique_ptr<Ent::Entity> Ent::EntityLib::makeInstanceOf(std::string _instanceOf) const
{
    std::filesystem::path instanceOfPath = _instanceOf;
    if (!instanceOfPath.is_absolute())
    {
        instanceOfPath = rawdataPath / _instanceOf;
    }

    std::unique_ptr<Ent::Entity> templ = loadEntity(instanceOfPath, nullptr);
    std::map<std::string, Ent::Component> components;
    for (auto const& type_comp : templ->getComponents())
    {
        auto const& cmpType = std::get<0>(type_comp);
        auto const& superComp = std::get<1>(type_comp);
        components.emplace(
            cmpType,
            Ent::Component{
                true,
                cmpType,
                superComp.root.makeInstanceOf(),
                superComp.version,
                superComp.index,
            });
    }
    auto inst = std::make_unique<Ent::Entity>(
        *this,
        templ->getNameValue().makeInstanceOf(),
        components,
        nullptr,
        templ->getColorValue().makeInstanceOf(),
        templ->getThumbnailValue().makeInstanceOf(),
        templ->getInstanceOfValue().makeOverridedInstanceOf(_instanceOf));
    return inst;
}

void Ent::EntityLib::saveEntity(Entity const& entity, std::filesystem::path const& entityPath) const
{
    std::ofstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document = ::saveEntity(schema, entity);
    file << document.dump(4);
    file.close();

    // Better to check after save because it is easiest to debug
    if (validationEnabled)
    {
        try
        {
            validateEntity(schema.schema, toolsDir, document);
        }
        catch (...)
        {
            fprintf(stderr, "Error, saving entity : %ls\n", entityPath.c_str());
            throw;
        }
    }
}

static json saveScene(Ent::ComponentsSchema const& schema, Ent::Scene const& scene)
{
    json document;

    document.emplace("Version", 2);
    json& objects = document["Objects"];

    for (std::unique_ptr<Ent::Entity> const& ent : scene.objects)
    {
        if (ent->hasOverride())
        {
            objects.emplace_back(::saveEntity(schema, *ent));
        }
    }

    return document;
}

void Ent::EntityLib::saveScene(Scene const& scene, std::filesystem::path const& scenePath) const
{
    std::ofstream file(scenePath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", scenePath.c_str());
        throw std::runtime_error(message.data());
    }

    json document = ::saveScene(schema, scene);

    file << document.dump(4);
    file.close();

    // Better to check after save because it is easiest to debug
    if (validationEnabled)
    {
        try
        {
            validateScene(schema.schema, toolsDir, document);
        }
        catch (...)
        {
            fprintf(stderr, "Error, saving scene : %ls\n", scenePath.c_str());
            throw;
        }
    }
}

std::unique_ptr<Ent::SubSceneComponent> Ent::SubSceneComponent::makeInstanceOf() const
{
    std::unique_ptr<Scene> instEmbedded;
    if (embedded)
    {
        instEmbedded = embedded->makeInstanceOf();
    }
    return std::make_unique<SubSceneComponent>(isEmbedded, file, index, std::move(instEmbedded));
}

bool Ent::SubSceneComponent::hasOverride() const
{
    //if (isEmbedded.isSet())
    //    return true;
    //if (file.isSet())
    //    return true;
    //if (index.isSet())
    //    return true;
    return embedded != nullptr && embedded->hasOverride();
}

bool Ent::Array::hasOverride() const
{
    return std::any_of(begin(data), end(data), std::mem_fn(&Ent::Node::hasOverride));
}

/// \endcond
