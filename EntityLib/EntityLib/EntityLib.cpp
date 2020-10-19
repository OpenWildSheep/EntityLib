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
#include <ciso646>

#include "external/json.hpp"
#include "ValidJson.h"
#pragma warning(pop)

/// \cond PRIVATE

using namespace nlohmann;

// char schemaPath[2048] = {};

static Ent::Node loadNode(Ent::Subschema const& _nodeSchema, json const& _data, Ent::Node const* _super);
static std::unique_ptr<Ent::Scene> loadScene(
    Ent::EntityLib const& _entLib,
    Ent::ComponentsSchema const& _schema,
    json const& _entities,
    Ent::Scene const* _super);
static json saveScene(Ent::ComponentsSchema const& _schema, Ent::Scene const& _scene);

namespace Ent
{
    char const* colorSchemaName = "file://RuntimeComponents.json#/definitions/Color";
    static Ent::Node makeDefaultColorField(EntityLib const& _entlib)
    {
        Ent::Subschema const& colorSchema = _entlib.schema.schema.allDefinitions.at(colorSchemaName);
        Ent::Subschema const* itemSchema = &colorSchema.singularItems->get();
        Ent::Override<float> one{ 255.f, tl::nullopt, tl::nullopt };
        std::vector<nonstd::value_ptr<Ent::Node>> nodes{
            nonstd::make_value<Ent::Node>(one, itemSchema),
            nonstd::make_value<Ent::Node>(one, itemSchema),
            nonstd::make_value<Ent::Node>(one, itemSchema),
            nonstd::make_value<Ent::Node>(one, itemSchema),
        };
        return Node{ Array{ nodes }, &colorSchema };
    }

    EntityLib::EntityLib(std::filesystem::path _rootPath)
        : rootPath(std::move(_rootPath)) // Read schema and dependencies
    {
        rawdataPath = rootPath / "RawData";
        toolsDir = rootPath / "Tools";
        auto schemaPath = toolsDir / "WildPipeline/Schema";

        json schemaDocument = mergeComponents(toolsDir);

        SchemaLoader loader(toolsDir, schemaPath);

        loader.readSchema(&schema.schema, "Scene-schema.json", schemaDocument, schemaDocument);

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

    // ************************************ Union *************************************************

    bool Ent::Union::hasOverride() const
    {
        return wrapper->hasOverride();
    }

    Node* Union::getUnionData()
    {
        return wrapper->at(classDatafield.c_str());
    }

    Node const* Union::getUnionData() const
    {
        return wrapper->at(classDatafield.c_str());
    }

    char const* Union::getUnionType() const
    {
        if (wrapper.has_value())
        {
            return wrapper->at(classNameField.c_str())->getString();
        }
        else
        {
            return nullptr;
        }
    }

    Node* Union::setUnionType(char const* _type)
    {
        if (getUnionType() != _type)
        {
            Subschema const* subTypeSchema = schema->getUnionTypeWrapper(_type);
            // TODO : Loïc - low prio - Find a way to get the super.
            //   It could be hard because we are no more in the loading phase, so the super is
            //   now delete.
            wrapper = loadNode(*subTypeSchema, json(), nullptr);
            wrapper->at(classNameField.c_str())->setString(_type);
        }
        return getUnionData();
    }

    // ************************************* Node *************************************************

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
    {
    }

    DataType Node::getDataType() const
    {
        return (DataType)value.which();
    }

    Node* Node::at(char const* _field)
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(_field).get();
        }
        throw BadType();
    }
    Node const* Node::at(char const* _field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(_field).get();
        }
        throw BadType();
    }
    bool Node::count(char const* _field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().count(_field) != 0;
        }
        throw BadType();
    }
    Node* Node::at(size_t _index)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data[_index].get();
        }
        throw BadType();
    }
    Node const* Node::at(size_t _index) const
    {
        if (value.is<Object>())
        {
            auto iter = value.get<Object>().begin();
            std::advance(iter, _index);
            return iter->second.get();
        }
        if (value.is<Array>())
        {
            return value.get<Array>().data[_index].get();
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

    Node const* Node::getUnionDataWrapper() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().wrapper.get();
        }
        throw BadType();
    }

    Node* Node::getUnionData()
    {
        if (value.is<Union>())
        {
            return value.get<Union>().getUnionData();
        }
        throw BadType();
    }
    Node const* Node::getUnionData() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().getUnionData();
        }
        throw BadType();
    }

    char const* Node::getUnionType() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().getUnionType();
        }
        throw BadType();
    }

    Node* Node::setUnionType(char const* _type)
    {
        if (value.is<Union>())
        {
            return value.get<Union>().setUnionType(_type);
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

    void Node::setFloat(float _val)
    {
        value.get<Override<float>>().set(_val);
    }
    void Node::setInt(int64_t _val)
    {
        value.get<Override<int64_t>>().set(_val);
    }
    void Node::setString(char const* _val)
    {
        value.get<Override<std::string>>().set(_val);
    }
    void Node::setBool(bool _val)
    {
        value.get<Override<bool>>().set(_val);
    }

    void Node::setEntityRef(EntityRef _entityRef)
    {
        value.get<Override<EntityRef>>().set(std::move(_entityRef));
    }

    struct UnSet
    {
        template <typename T>
        void operator()(Override<T>& _ov) const
        {
            _ov.unset();
        }

        template <typename U>
        void operator()(U& _notOverride) const
        {
            (void*)&_notOverride;
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
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.isSet();
        }

        template <typename U>
        bool operator()(U const& _notOverride) const
        {
            (void*)&_notOverride;
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
        bool operator()(Override<T> const& _ov) const
        {
            return (not _ov.prefabValue.has_value()) and (not _ov.overrideValue.has_value());
        }

        bool operator()(Null const&) const
        {
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            return std::all_of(begin(_arr.data), end(_arr.data), std::mem_fn(&Node::hasDefaultValue));
        }

        bool operator()(Object const& _obj) const
        {
            return std::all_of(begin(_obj), end(_obj), [](auto&& name_node) {
                return std::get<1>(name_node)->hasDefaultValue();
            });
        }

        bool operator()(Union const& _un) const
        {
            return _un.wrapper->hasDefaultValue();
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
        Node operator()(Override<T> const& _ov) const
        {
            return Node(_ov.detach(), schema);
        }

        Node operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return Node(Null{}, schema);
        }

        Node operator()(Array const& _arr) const
        {
            Array out;
            for (auto&& item : _arr.data)
            {
                out.data.emplace_back(nonstd::make_value<Node>(item->detach()));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& _obj) const
        {
            Object out;
            for (auto&& name_node : _obj)
            {
                out.emplace(
                    std::get<0>(name_node),
                    nonstd::make_value<Node>(std::get<1>(name_node)->detach()));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            detUnion.schema = _un.schema;
            detUnion.wrapper = _un.wrapper->detach();
            detUnion.classDatafield = _un.classDatafield;
            detUnion.classNameField = _un.classNameField;
            return Node(std::move(detUnion), schema);
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
        Node operator()(Override<T> const& _ov) const
        {
            return Node(_ov.makeInstanceOf(), schema);
        }

        Node operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return Node(Null{}, schema);
        }

        Node operator()(Array const& _arr) const
        {
            Array out;
            for (auto&& item : _arr.data)
            {
                out.data.emplace_back(nonstd::make_value<Node>(item->makeInstanceOf()));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& _obj) const
        {
            Object out;
            for (auto&& name_node : _obj)
            {
                out.emplace(
                    std::get<0>(name_node),
                    nonstd::make_value<Node>(std::get<1>(name_node)->makeInstanceOf()));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            detUnion.schema = _un.schema;
            detUnion.wrapper = _un.wrapper->makeInstanceOf();
            detUnion.classDatafield = _un.classDatafield;
            detUnion.classNameField = _un.classNameField;
            return Node(std::move(detUnion), schema);
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
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.isSet();
        }

        bool operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            return _arr.hasOverride();
        }

        bool operator()(Object const& _obj) const
        {
            for (auto&& name_node : _obj)
            {
                if (std::get<1>(name_node)->hasOverride())
                {
                    return true;
                }
            }
            return false;
        }

        bool operator()(Union const& _un) const
        {
            return _un.wrapper->hasOverride();
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
        bool operator()(Override<T> const& _ov) const
        {
            return not _ov.prefabValue.has_value() and not _ov.overrideValue.has_value();
        }

        bool operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            (void*)&_arr;
            return false;
        }

        bool operator()(Object const& _obj) const
        {
            (void*)&_obj;
            return false;
        }

        bool operator()(Union const&) const
        {
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
        bool _isEmbedded, Override<std::string> _file, size_t _index, std::unique_ptr<Scene> _embedded)
        : isEmbedded(_isEmbedded)
        , file(std::move(_file))
        , index(_index)
        , embedded(std::move(_embedded))
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
        , maxActivationLevel(Ent::ActivationLevel::Started, tl::nullopt, tl::nullopt)
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
        Override<Ent::ActivationLevel> _maxActivationLevel,
        bool _hasASuper)
        : entlib(&_entlib)
        , name(std::move(_name))
        , components(std::move(_components))
        , subSceneComponent(std::move(_subSceneComponent))
        , color(std::move(_color))
        , thumbnail(std::move(_thumbnail))
        , instanceOf(std::move(_instanceOf))
        , maxActivationLevel(std::move(_maxActivationLevel))
        , hasASuper(_hasASuper)
    {
        updateSubSceneOwner();
    }

    std::unique_ptr<Entity> Entity::clone() const
    {
        std::map<std::string, Component> instComponents;
        std::unique_ptr<SubSceneComponent> instSubSceneComponent;

        for (auto&& name_comp : components)
        {
            instComponents.emplace(name_comp.first, name_comp.second);
        }
        if (subSceneComponent != nullptr)
        {
            instSubSceneComponent = subSceneComponent->clone();
        }

        return std::make_unique<Entity>(
            *entlib,
            name,
            std::move(instComponents),
            std::move(instSubSceneComponent),
            color,
            thumbnail,
            instanceOf);
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
    void Entity::setCanBeRenamed(bool _can)
    {
        hasASuper = not _can;
    }

    char const* Entity::getInstanceOf() const
    {
        return instanceOf.isDefault() ? nullptr : instanceOf.get().c_str();
    }

    ActivationLevel Entity::getMaxActivationLevel() const
    {
        return maxActivationLevel.get();
    }

    void Entity::setMaxActivationLevel(ActivationLevel _level)
    {
        maxActivationLevel.set(_level);
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
    Component* Entity::addComponent(char const* _type)
    {
        if (entlib->schema.components.count(_type) == 0)
        {
            fprintf(stderr, "Error : Unknown Component type : %s\n", _type);
            return nullptr;
        }
        if (entlib->componentDependencies.count(_type) != 0) // Could be an editor componant
        {
            for (auto&& dep : entlib->componentDependencies.at(_type))
            {
                addComponent(dep.c_str());
            }
        }
        Ent::Subschema const& compSchema = *entlib->schema.components.at(_type);
        Ent::Component comp{
            false, _type, loadNode(compSchema, json(), nullptr), 1, components.size()
        };
        auto iter_bool = components.emplace(_type, std::move(comp));
        return &(iter_bool.first->second);
    }
    Component const* Entity::getComponent(char const* _type) const
    {
        auto iter = components.find(_type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    Component* Entity::getComponent(char const* _type)
    {
        auto iter = components.find(_type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    void Entity::removeComponent(char const* _type)
    {
        // TODO : Use dependencies
        components.erase(_type);
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
            instanceOf,
            maxActivationLevel.makeInstanceOf());
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

    void Entity::setParentScene(Scene* _scene)
    {
        parentScene = _scene;
    }

    Scene* Entity::getParentScene() const
    {
        return parentScene;
    }

    static std::tuple<std::vector<std::string>, Entity*, Scene*> getAbsolutePathReversed(Entity* _entity)
    {
        Entity* current = _entity;
        Entity* rootEntity = nullptr;
        Scene* rootScene = nullptr;
        std::vector<std::string> path;
        while (current != nullptr)
        {
            path.emplace_back(current->getName());
            rootEntity = current;
            rootScene = current->getParentScene();
            current = current->getParentScene() != nullptr ?
                          current->getParentScene()->getOwnerEntity() :
                          nullptr;
        }
        return { std::move(path), rootEntity, rootScene };
    }

    EntityRef Entity::makeEntityRef(Entity& _entity)
    {
        // get the two absolute path
        auto&& thisPathInfos = getAbsolutePathReversed(this);
        auto&& entityPathInfos = getAbsolutePathReversed(&_entity);

        Entity* thisRootEntity = std::get<1>(thisPathInfos);
        Entity* entityRootEntity = std::get<1>(entityPathInfos);
        Scene* thisRootScene = std::get<2>(thisPathInfos);
        Scene* entityRootScene = std::get<2>(entityPathInfos);

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

        std::string relativePath = computeRelativePath(thisPath, std::move(entityPath), false);

        return { std::move(relativePath) };
    }

    static Scene* getSubScene(Entity* _entity)
    {
        if (auto* subScene = _entity->getSubSceneComponent())
        {
            if (subScene->isEmbedded)
            {
                return subScene->embedded.get();
            }
            // TODO: major 2020-09-26 @Seb: else open non embedded subscene ?
        }
        return nullptr;
    }

    static Entity* findChild(Scene* _scene, const std::string& _name)
    {
        auto&& children = _scene->getObjects();
        const auto found = std::find_if(children.begin(), children.end(), [&_name](auto& childPtr) {
            return childPtr->getName() == _name;
        });
        return found == children.end() ? nullptr : found->get();
    }

    static Entity* resolveEntityRefRecursive(
        Entity* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path)
    {
        auto& head = _path.front();

        if (head == "..")
        {
            // go up in hierarchy
            if (_up == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = _up->getOwnerEntity();
            _down = _up;
            _up = _current == nullptr ? nullptr : _current->getParentScene();
        }
        else if (head != ".")
        {
            // go down in child hierarchy named "head"
            if (_down == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = findChild(_down, head);
            _up = _down;
            _down = _current == nullptr ? nullptr : getSubScene(_current);
        }
        _path.erase(_path.begin());
        if (_path.empty())
        {
            return _current;
        }
        return resolveEntityRefRecursive(_current, _up, _down, _path);
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

    Scene::Scene(std::vector<std::unique_ptr<Entity>> _entities)
        : objects(std::move(_entities))
    {
        updateChildrenContext();
    }

    void Scene::addEntity(std::unique_ptr<Entity>&& _entity)
    {
        _entity->setParentScene(this);
        objects.emplace_back(std::move(_entity));
    }

    std::vector<std::unique_ptr<Entity>> const& Scene::getObjects() const
    {
        return objects;
    }

    std::vector<std::unique_ptr<Entity>> Scene::releaseAllEntities()
    {
        std::vector<std::unique_ptr<Entity>> freeEntities;
        for (auto&& ent : objects)
        {
            ent->setParentScene(nullptr);
            freeEntities.emplace_back(std::move(ent));
        }
        objects.clear();
        return freeEntities;
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

    std::unique_ptr<Scene> Scene::clone() const
    {
        std::vector<std::unique_ptr<Entity>> instanceEntities;
        auto scene = std::make_unique<Scene>();
        for (auto const& ent : objects)
        {
            instanceEntities.emplace_back(ent->clone());
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
            {
                return true;
            }
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

static Ent::Node loadFreeObjectNode(json const& _data)
{
    Ent::Node result;
    switch (_data.type())
    {
    case nlohmann::detail::value_t::null: result = Ent::Node(Ent::Null{}, nullptr); break;
    case nlohmann::detail::value_t::string:
        result = Ent::Node(
            Ent::Override<std::string>(std::string(), tl::nullopt, _data.get<std::string>()),
            nullptr);
        break;
    case nlohmann::detail::value_t::boolean:
        result = Ent::Node(Ent::Override<bool>(bool{}, tl::nullopt, _data.get<bool>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
        result =
            Ent::Node(Ent::Override<int64_t>(int64_t{}, tl::nullopt, _data.get<int64_t>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_float:
        result = Ent::Node(Ent::Override<float>(float{}, tl::nullopt, _data.get<float>()), nullptr);
        break;
    case nlohmann::detail::value_t::object:
    {
        Ent::Object object;
        for (auto const& field : _data.items())
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
        for (auto const& item : _data)
        {
            Ent::Node tmpNode = loadFreeObjectNode(item);
            arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(arr), nullptr);
    }
    break;
    case nlohmann::detail::value_t::binary:
    case nlohmann::detail::value_t::discarded: break;
    }
    return result;
}

static Ent::Node const emptyNode(Ent::Null(), nullptr);

static Ent::Node loadNode(Ent::Subschema const& _nodeSchema, json const& _data, Ent::Node const* _super)
{
    Ent::Node result;

    switch (_nodeSchema.type)
    {
    case Ent::DataType::null: result = Ent::Node(Ent::Null{}, &_nodeSchema); break;
    case Ent::DataType::string:
    {
        if (_nodeSchema.constValue.has_value())
        {
            // _nodeSchema is const and the value can't be overriden
            std::string const def = _nodeSchema.constValue->get<std::string>();
            result = Ent::Node(Ent::Override<std::string>("", tl::nullopt, def), &_nodeSchema);
        }
        else
        {
            std::string const def = _nodeSchema.defaultValue.is<Ent::Null>() ?
                                        std::string() :
                                        _nodeSchema.defaultValue.get<std::string>();
            tl::optional<std::string> const supVal =
                (_super != nullptr and _super->isSet()) ?
                    tl::optional<std::string>(_super->getString()) :
                    tl::optional<std::string>(tl::nullopt);
            tl::optional<std::string> const val =
                _data.is_string() ? tl::optional<std::string>(_data.get<std::string>()) :
                                    tl::optional<std::string>(tl::nullopt);
            result = Ent::Node(Ent::Override<std::string>(def, supVal, val), &_nodeSchema);
        }
    }
    break;
    case Ent::DataType::boolean:
    {
        bool const def =
            _nodeSchema.defaultValue.is<Ent::Null>() ? bool{} : _nodeSchema.defaultValue.get<bool>();
        tl::optional<bool> const supVal = (_super != nullptr and _super->isSet()) ?
                                              tl::optional<bool>(_super->getBool()) :
                                              tl::optional<bool>(tl::nullopt);
        tl::optional<bool> const val = _data.is_boolean() ? tl::optional<bool>(_data.get<bool>()) :
                                                            tl::optional<bool>(tl::nullopt);
        result = Ent::Node(Ent::Override<bool>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::integer:
    {
        int64_t const def = _nodeSchema.defaultValue.is<Ent::Null>() ?
                                int64_t{} :
                                _nodeSchema.defaultValue.get<int64_t>();
        tl::optional<int64_t> const supVal = (_super != nullptr and _super->isSet()) ?
                                                 tl::optional<int64_t>(_super->getInt()) :
                                                 tl::optional<int64_t>(tl::nullopt);
        tl::optional<int64_t> const val = _data.is_number_integer() or _data.is_number_unsigned() ?
                                              tl::optional<int64_t>(_data.get<int64_t>()) :
                                              tl::optional<int64_t>(tl::nullopt);
        result = Ent::Node(Ent::Override<int64_t>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::number:
    {
        float const def = _nodeSchema.defaultValue.is<Ent::Null>() ?
                              float{} :
                              _nodeSchema.defaultValue.get<float>();
        tl::optional<float> const supVal = (_super != nullptr and _super->isSet()) ?
                                               tl::optional<float>(_super->getFloat()) :
                                               tl::optional<float>(tl::nullopt);
        tl::optional<float> const val =
            _data.is_number_float() or _data.is_number_integer() or _data.is_number_unsigned() ?
                tl::optional<float>(_data.get<float>()) :
                tl::optional<float>(tl::nullopt);
        result = Ent::Node(Ent::Override<float>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::object:
    {
        Ent::Object object;

        for (auto&& name_sub : _nodeSchema.properties)
        {
            std::string const& name = std::get<0>(name_sub);
            Ent::Node const* superProp = (_super != nullptr) ? _super->at(name.c_str()) : nullptr;
            static json const emptyJson;
            json const& prop = _data.count(name) != 0 ? _data.at(name) : emptyJson;
            Ent::Node tmpNode = loadNode(*std::get<1>(name_sub), prop, superProp);
            object.emplace(name, nonstd::make_value<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), &_nodeSchema);
    }
    break;
    case Ent::DataType::array:
    {
        Ent::Array arr;
        size_t index = 0;
        if (_nodeSchema.singularItems)
        {
            if (_data.is_null()) // No overrided
            {
                if (_super != nullptr)
                {
                    for (Ent::Node const* subSuper : _super->getItems())
                    {
                        Ent::Node tmpNode =
                            loadNode(_nodeSchema.singularItems->get(), json(), subSuper);
                        arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                        ++index;
                    }
                }
                // TODO : Create minItem items
            }
            else
            {
                for (auto const& item : _data)
                {
                    Ent::Node const* subSuper = (_super != nullptr and (_super->size() > index)) ?
                                                    _super->at(index) :
                                                    nullptr;
                    Ent::Node tmpNode = loadNode(_nodeSchema.singularItems->get(), item, subSuper);
                    arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                    ++index;
                }
            }
        }
        else
        {
            ENTLIB_ASSERT(_nodeSchema.linearItems.has_value());
            for (Ent::SubschemaRef const& sub : *_nodeSchema.linearItems)
            {
                Ent::Node const* subSuper =
                    (_super != nullptr and _super->size() > index) ? _super->at(index) : nullptr;
                static json const emptyJson;
                json const& prop = _data.size() > index ? _data.at(index) : emptyJson;
                Ent::Node tmpNode = loadNode(*sub, prop, subSuper);
                arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                ++index;
            }
        }
        result = Ent::Node(std::move(arr), &_nodeSchema);
    }
    break;
    case Ent::DataType::entityRef:
    {
        Ent::EntityRef const def;

        tl::optional<Ent::EntityRef> const supVal =
            (_super != nullptr and _super->isSet()) ?
                tl::optional<Ent::EntityRef>(_super->getEntityRef()) :
                tl::optional<Ent::EntityRef>(tl::nullopt);

        tl::optional<std::string> const refString =
            _data.is_string() ? _data.get<std::string>() : tl::optional<std::string>(tl::nullopt);

        tl::optional<Ent::EntityRef> const val =
            refString.has_value() ?
                tl::optional<Ent::EntityRef>(Ent::EntityRef{ refString.value() }) :
                tl::optional<Ent::EntityRef>(tl::nullopt);

        result = Ent::Node(Ent::Override<Ent::EntityRef>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::oneOf:
    {
        auto&& meta = _nodeSchema.meta.get<Ent::Subschema::UnionMeta>();
        std::string const& typeField = meta.typeField;
        std::string const& dataField = meta.dataField;
        std::string dataType;
        if (_data.count(typeField))
            dataType = _data.at(typeField).get<std::string>();
        else
        {
            // We are making a new node without input data
            // "back()" because the base type is at the end of the type list
            // TODO : Loïc - Add in metadata the name of the default type
            dataType =
                _nodeSchema.oneOf->back()->properties.at(typeField).get().constValue->get<std::string>();
        }
        bool typeFound = false;
        for (Ent::SubschemaRef const& schemaTocheck : *_nodeSchema.oneOf)
        {
            auto&& schemaType =
                schemaTocheck->properties.at(typeField).get().constValue->get<std::string>();
            if (schemaType == dataType)
            {
                Ent::Node dataNode = loadNode(
                    schemaTocheck.get(),
                    _data,
                    _super != nullptr ? _super->getUnionDataWrapper() : nullptr);
                Ent::Union un{};
                un.schema = &_nodeSchema;
                un.wrapper = nonstd::make_value<Ent::Node>(std::move(dataNode));
                un.classDatafield = dataField;
                un.classNameField = typeField;
                result = Ent::Node(std::move(un), &_nodeSchema);
                typeFound = true;
                break;
            }
        }
        if (not typeFound)
        {
            fprintf(
                stderr,
                "Can't find type %s in schema %s\n",
                dataType.c_str(),
                _nodeSchema.name.c_str());
            result = Ent::Node(Ent::Union{}, &_nodeSchema);
        }
    }
    break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("Invalid DataType"); break;
    }
    return result;
}

static json saveNode(Ent::Subschema const& _schema, Ent::Node const& _node)
{
    json data;
    switch (_schema.type)
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = _node.getString(); break;
    case Ent::DataType::boolean: data = _node.getBool(); break;
    case Ent::DataType::integer: data = _node.getInt(); break;
    case Ent::DataType::number: data = _node.getFloat(); break;
    case Ent::DataType::object:
    {
        data = json::object();
        for (auto const& name_sub : _schema.properties)
        {
            auto&& name = std::get<0>(name_sub);
            Ent::Node const* subNode = _node.at(name.c_str());
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
        for (Ent::Node const* item : _node.getItems())
        {
            if (item->hasOverride())
            {
                ENTLIB_ASSERT(item->getSchema() != nullptr);
                json tmpNode = saveNode(*item->getSchema(), *item);
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
        Ent::EntityRef ref = _node.getEntityRef();
        data = ref.entityPath;
    }
    break;
    case Ent::DataType::oneOf:
    {
        auto&& meta = _schema.meta.get<Ent::Subschema::UnionMeta>();
        Ent::Node const* dataInsideUnion = _node.getUnionData();
        char const* type = _node.getUnionType();
        data[meta.typeField] = type;
        data[meta.dataField] = saveNode(*dataInsideUnion->getSchema(), *dataInsideUnion);
    }
    break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("DataType is Invalid!!"); break;
    }
    return data;
}

namespace
{
    Ent::ActivationLevel parseActivationLevel(const std::string& _name)
    {
        if (_name == "Created")
        {
            return Ent::ActivationLevel::Created;
        }
        if (_name == "Started")
        {
            return Ent::ActivationLevel::Started;
        }
        if (_name == "Loading")
        {
            return Ent::ActivationLevel::Loading;
        }
        if (_name == "InWorld")
        {
            return Ent::ActivationLevel::InWorld;
        }
        return Ent::ActivationLevel::Started;
    }

    char const* getActivationLevelString(Ent::ActivationLevel _level)
    {
        if (_level == Ent::ActivationLevel::Created)
        {
            return "Created";
        }
        if (_level == Ent::ActivationLevel::Started)
        {
            return "Started";
        }
        if (_level == Ent::ActivationLevel::Loading)
        {
            return "Loading";
        }
        if (_level == Ent::ActivationLevel::InWorld)
        {
            return "InWorld";
        }
        return "Started";
    }
} // namespace

static std::unique_ptr<Ent::Entity> loadEntity(
    Ent::EntityLib const& _entlib,
    Ent::ComponentsSchema const& _schema,
    json const& _entNode,
    Ent::Entity const* _superEntityFromParentEntity)
{
    ENTLIB_ASSERT(
        _superEntityFromParentEntity == nullptr
        or _superEntityFromParentEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    tl::optional<std::string> instanceOf;
    auto superEntityOfThisEntity = std::make_unique<Ent::Entity>(_entlib);
    ENTLIB_ASSERT(superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    bool superIsInit = false;
    Ent::Entity const* superEntity = superEntityOfThisEntity.get();
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    if (_entNode.count("InstanceOf") != 0)
    {
        instanceOf = _entNode.at("InstanceOf").get<std::string>();
        superEntityOfThisEntity = _entlib.loadEntity(*instanceOf, _superEntityFromParentEntity);
        superEntity = superEntityOfThisEntity.get();
        ENTLIB_ASSERT(
            superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        std::filesystem::path instanceOfPath = *instanceOf;
        superIsInit = true;
    }
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    if (not superIsInit and _superEntityFromParentEntity != nullptr)
    {
        superEntity = _superEntityFromParentEntity;
        ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    }

    tl::optional<std::string> const thumbnail = _entNode.count("Thumbnail") != 0 ?
                                                    _entNode.at("Thumbnail").get<std::string>() :
                                                    tl::optional<std::string>();
    Ent::Override<std::string> superThumbnail = superEntity->getThumbnailValue();
    Ent::Override<std::string> ovThumbnail = superThumbnail.makeOverridedInstanceOf(thumbnail);

    tl::optional<std::string> const name = _entNode.count("Name") != 0 ?
                                               _entNode.at("Name").get<std::string>() :
                                               tl::optional<std::string>();

    Ent::Override<std::string> superName = superEntity->getNameValue();
    Ent::Override<std::string> ovName = superName.makeOverridedInstanceOf(name);

    Ent::Override<std::string> superInstanceOf = superEntity->getInstanceOfValue();
    Ent::Override<std::string> ovInstanceOf = superName.makeOverridedInstanceOf(instanceOf);

    tl::optional<Ent::ActivationLevel> maxActivationLevel;
    if (_entNode.count("MaxActivationLevel") != 0)
    {
        maxActivationLevel =
            parseActivationLevel(_entNode.at("MaxActivationLevel").get<std::string>());
    }
    Ent::Override<Ent::ActivationLevel> superActivationLevel =
        superEntity != nullptr ? superEntity->getMaxActivationLevelValue() :
                                 Ent::Override<Ent::ActivationLevel>{ Ent::ActivationLevel::Started,
                                                                      tl::nullopt,
                                                                      tl::nullopt };
    Ent::Override<Ent::ActivationLevel> ovMaxActivationLevel =
        superActivationLevel.makeOverridedInstanceOf(maxActivationLevel);

    Ent::Node ovColor = Ent::makeDefaultColorField(_entlib);
    if (_entNode.contains("Color"))
    {
        Ent::Subschema const& colorSchema =
            _entlib.schema.schema.allDefinitions.at(Ent::colorSchemaName);
        ovColor = loadNode(
            colorSchema,
            _entNode.at("Color"),
            _superEntityFromParentEntity != nullptr ? &_superEntityFromParentEntity->getColorValue() :
                                                      nullptr);
    }
    else
    {
        ovColor = superEntity->getColorValue().makeInstanceOf();
    }

    std::map<std::string, Ent::Component> components;
    std::unique_ptr<Ent::SubSceneComponent> subSceneComponent;
    size_t index = 0;
    if (_entNode.count("Components") != 0)
    {
        json const& componentsNode = _entNode.at("Components");
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
                        _entlib,
                        _schema,
                        data["Embedded"],
                        (superComp != nullptr ? superComp->embedded.get() : nullptr));
                }
                subSceneComponent = std::move(subSceneComp);
            }
            else
            {
                Ent::Component const* superComp = superEntity->getComponent(cmpType.c_str());
                auto const version =
                    compNode.count("Version") != 0u ? compNode.at("Version").get<size_t>() : 0;

                if (_schema.components.count(cmpType) == 0)
                {
                    fprintf(stderr, "Error : Unknown Component type : %s\n", cmpType.c_str());
                }
                else
                {
                    Ent::Subschema const& compSchema = *_schema.components.at(cmpType);

                    Ent::Component comp{
                        superComp != nullptr, // has a super component
                        cmpType,
                        loadNode(
                            compSchema, data, (superComp != nullptr ? &superComp->root : nullptr)),
                        version,
                        index
                    };

                    components.emplace(cmpType, std::move(comp));
                }
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
        _entlib,
        std::move(ovName),
        std::move(components),
        std::move(subSceneComponent),
        std::move(ovColor),
        std::move(ovThumbnail),
        std::move(ovInstanceOf),
        std::move(ovMaxActivationLevel));
}

std::unique_ptr<Ent::Entity>
Ent::EntityLib::loadEntity(std::filesystem::path const& _entityPath, Ent::Entity const* _super) const
{
    auto const absPath = getAbsolutePath(_entityPath);
    bool reload = false;
    auto timestamp = std::filesystem::last_write_time(absPath);
    auto iter = m_entityCache.find(absPath);
    if (iter == m_entityCache.end())
    {
        reload = true;
    }
    else
    {
        if (timestamp > iter->second.time)
        {
            reload = true;
        }
    }

    if (reload)
    {
        printf("loadEntity %ls\n", _entityPath.c_str());
        json document = loadJsonFile(absPath);

        if (validationEnabled)
        {
            try
            {
                validateEntity(schema.schema, toolsDir, document);
            }
            catch (...)
            {
                fprintf(stderr, "Error, loading entity : %ls\n", _entityPath.c_str());
                throw;
            }
        }

        std::unique_ptr<Ent::Entity> entity = ::loadEntity(*this, schema, document, _super);
        auto file = EntityFile{ entity->clone(), timestamp };
        auto iter_bool = m_entityCache.emplace(absPath, std::move(file));
        return entity;
    }
    else
    {
        return iter->second.entity->clone();
    }
}

static std::unique_ptr<Ent::Scene> loadScene(
    Ent::EntityLib const& _entLib,
    Ent::ComponentsSchema const& _schema,
    json const& _entities,
    Ent::Scene const* _super)
{
    auto scene = std::make_unique<Ent::Scene>();

    // Add all entities from super scene ...
    std::set<std::string> entFromSuper;
    if (_super != nullptr)
    {
        for (auto&& superEnt : _super->getObjects())
        {
            entFromSuper.insert(superEnt->getName());
            json const* instEntNode = nullptr;
            // ... and look if there is an override.
            for (json const& entNode : _entities)
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
                    ::loadEntity(_entLib, _schema, *instEntNode, superEnt.get());
            ent->setCanBeRenamed(false);
            scene->addEntity(std::move(ent));
        }
    }

    // Add new entities
    for (json const& entNode : _entities)
    {
        std::string const name = entNode.at("Name").get<std::string>();
        if (entFromSuper.count(name) != 0)
        {
            continue;
        }
        std::unique_ptr<Ent::Entity> ent = ::loadEntity(_entLib, _schema, entNode, nullptr);
        scene->addEntity(std::move(ent));
    }

    return scene;
}

std::unique_ptr<Ent::Scene> Ent::EntityLib::loadScene(std::filesystem::path const& _scenePath) const
{
    auto const absPath = getAbsolutePath(_scenePath);
    bool reload = false;
    auto timestamp = std::filesystem::last_write_time(absPath);
    auto iter = m_sceneCache.find(absPath);
    if (iter == m_sceneCache.end())
    {
        reload = true;
    }
    else
    {
        if (timestamp > iter->second.time)
        {
            reload = true;
        }
    }

    if (reload)
    {
        json document = loadJsonFile(absPath);

        if (validationEnabled)
        {
            try
            {
                validateScene(schema.schema, toolsDir, document);
            }
            catch (...)
            {
                fprintf(stderr, "Error, loading scene : %ls\n", _scenePath.c_str());
                throw;
            }
        }

        std::unique_ptr<Ent::Scene> scene =
            ::loadScene(*this, schema, document.at("Objects"), nullptr);
        auto file = SceneFile{ scene->clone(), timestamp };
        auto iter_bool = m_sceneCache.emplace(absPath, std::move(file));
        return scene;
    }
    else
    {
        return iter->second.scene->clone();
    }
}

static json saveEntity(Ent::ComponentsSchema const& _schema, Ent::Entity const& _entity)
{
    json entNode;

    // Always save Name since it is use for override
    entNode.emplace("Name", _entity.getNameValue().get());

    if (_entity.getInstanceOfValue().isSet())
    {
        entNode.emplace("InstanceOf", _entity.getInstanceOfValue().get());
    }

    Ent::Subschema const& colorSchema = _schema.schema.allDefinitions.at(Ent::colorSchemaName);
    if (_entity.getColorValue().hasOverride())
    {
        entNode.emplace("Color", saveNode(colorSchema, _entity.getColorValue()));
    }

    if (const char* thumbnail = _entity.getThumbnail())
    {
        entNode.emplace("Thumbnail", thumbnail);
    }

    if (not _entity.getMaxActivationLevelValue().isDefault())
    {
        entNode.emplace(
            "MaxActivationLevel", getActivationLevelString(_entity.getMaxActivationLevel()));
    }

    json& componentsNode = entNode["Components"] = json::array();
    std::vector<Ent::Component const*> sortedComp;
    for (auto&& type_comp : _entity.getComponents())
    {
        sortedComp.push_back(&std::get<1>(type_comp));
    }
    Ent::Component subscenePlaceholder{ true, "SubScene", Ent::Node(), 1, 0 };
    if (Ent::SubSceneComponent const* subscene = _entity.getSubSceneComponent())
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
            Ent::SubSceneComponent const* subscene = _entity.getSubSceneComponent();
            ENTLIB_ASSERT(subscene != nullptr);
            bool const subsceneHasOverride = subscene->hasOverride();
            bool const hasInstanceOf = _entity.getInstanceOf() != nullptr;
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
                    data.emplace("Embedded", saveScene(_schema, *subscene->embedded)["Objects"]);
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
            compNode.emplace("Data", saveNode(*_schema.components.at(comp->type), comp->root));

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
            for (std::unique_ptr<Ent::Entity> const& subEntity : subscene->embedded->getObjects())
            {
                detSubSceneComponent->embedded->addEntity(subEntity->detachEntityFromPrefab());
            }
        }
    }

    auto detachedColor = getColorValue().detach();
    auto detachedMaxActivationLevel = getMaxActivationLevelValue().detach();
    return std::make_unique<Ent::Entity>(
        *entlib,
        getNameValue().detach().makeOverridedInstanceOf(std::string(getName()) + "_detached"),
        std::move(detComponents),
        std::move(detSubSceneComponent),
        std::move(detachedColor),
        getThumbnailValue().detach(),
        Override<std::string>{},
        std::move(detachedMaxActivationLevel));
}

std::unique_ptr<Ent::Entity> Ent::EntityLib::makeInstanceOf(std::string _instanceOf) const
{
    std::unique_ptr<Ent::Entity> templ = loadEntity(_instanceOf, nullptr);
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
        templ->getInstanceOfValue().makeOverridedInstanceOf(_instanceOf),
        templ->getMaxActivationLevelValue().makeInstanceOf());
    return inst;
}

void Ent::EntityLib::saveEntity(Entity const& _entity, std::filesystem::path const& _entityPath) const
{
    std::ofstream file(_entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", _entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document = ::saveEntity(schema, _entity);
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
            fprintf(stderr, "Error, saving entity : %ls\n", _entityPath.c_str());
            throw;
        }
    }
}

std::filesystem::path Ent::EntityLib::getAbsolutePath(std::filesystem::path const& _path) const
{
    if (_path.is_absolute())
    {
        std::filesystem::path absPath = _path;
        absPath.make_preferred();
        return std::filesystem::canonical(absPath);
    }
    else
    {
        std::filesystem::path absPath = rawdataPath;
        absPath /= _path;
        absPath.make_preferred();
        return std::filesystem::canonical(absPath);
    }
}

static json saveScene(Ent::ComponentsSchema const& _schema, Ent::Scene const& _scene)
{
    json document;

    document.emplace("Version", 2);
    json& objects = document["Objects"];

    for (std::unique_ptr<Ent::Entity> const& ent : _scene.getObjects())
    {
        if (ent->hasOverride())
        {
            objects.emplace_back(::saveEntity(_schema, *ent));
        }
    }

    return document;
}

void Ent::EntityLib::saveScene(Scene const& _scene, std::filesystem::path const& _scenePath) const
{
    std::ofstream file(_scenePath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", _scenePath.c_str());
        throw std::runtime_error(message.data());
    }

    json document = ::saveScene(schema, _scene);

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
            fprintf(stderr, "Error, saving scene : %ls\n", _scenePath.c_str());
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

std::unique_ptr<Ent::SubSceneComponent> Ent::SubSceneComponent::clone() const
{
    std::unique_ptr<Scene> instEmbedded;
    if (embedded)
    {
        instEmbedded = embedded->clone();
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
