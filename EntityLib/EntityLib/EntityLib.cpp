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
    char const* actorStatesSchemaName = "file://Scene-schema.json#/definitions/ActorStates";
    char const* colorSchemaName = "file://RuntimeComponents.json#/definitions/Color";
    static Ent::Node makeDefaultColorField(EntityLib const& _entlib)
    {
        Ent::Subschema const& colorSchema = _entlib.schema.schema.allDefinitions.at(colorSchemaName);
        Ent::Subschema const* itemSchema = &colorSchema.singularItems->get();
        Ent::Override<float> one{ 255.f };
        std::vector<nonstd::value_ptr<Ent::Node>> nodes{
            nonstd::make_value<Ent::Node>(one, itemSchema),
            nonstd::make_value<Ent::Node>(one, itemSchema),
            nonstd::make_value<Ent::Node>(one, itemSchema),
            nonstd::make_value<Ent::Node>(one, itemSchema),
        };
        return Node{ Array{ nodes }, &colorSchema };
    }

    EntityLib::EntityLib(std::filesystem::path _rootPath, bool _doMergeComponents)
        : rootPath(std::move(_rootPath)) // Read schema and dependencies
    {
        rawdataPath = getAbsolutePath(rootPath / "RawData");
        toolsDir = getAbsolutePath(rootPath / "Tools");
        auto schemaPath = toolsDir / "WildPipeline/Schema";

        SchemaLoader loader(toolsDir, schemaPath);

        if (_doMergeComponents)
        {
            // mergeComponents create the content of the "MergedComponents.json" file
            json mergedComps = mergeComponents(toolsDir);
            loader.addInCache("MergedComponents.json", std::move(mergedComps));
        }

        json schemaDocument = loadJsonFile(toolsDir / "WildPipeline/Schema/Scene-schema.json");

        loader.readSchema(&schema.schema, "Scene-schema.json", schemaDocument, schemaDocument);

        auto&& compList =
            schema.schema.allDefinitions["file://MergedComponents.json#/definitions/Component"].oneOf;

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
        return wrapper->at(metaData->dataField.c_str());
    }

    Node const* Union::getUnionData() const
    {
        return wrapper->at(metaData->dataField.c_str());
    }

    char const* Union::getUnionType() const
    {
        if (wrapper.has_value())
        {
            return wrapper->at(metaData->typeField.c_str())->getString();
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
            wrapper->at(metaData->typeField.c_str())->setString(_type);
        }
        return getUnionData();
    }

    void Union::computeMemory(MemoryProfiler& prof) const
    {
        if (wrapper)
        {
            wrapper->computeMemory(prof);
            prof.add("Union::wrapper", sizeof(Node));
        }
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
            return &value.get<Object>().at(_field);
        }
        throw BadType();
    }
    Node const* Node::at(char const* _field) const
    {
        if (value.is<Object>())
        {
            return &value.get<Object>().at(_field);
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
            return &iter->second;
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
        if (value.is<Override<String>>())
        {
            return value.get<Override<String>>().get().c_str();
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
        value.get<Override<String>>().set(_val);
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
            return (not _ov.hasPrefab) and (not _ov.hasOverride);
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
                return std::get<1>(name_node).hasDefaultValue();
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
                out.emplace(std::get<0>(name_node), std::get<1>(name_node).detach());
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            detUnion.schema = _un.schema;
            detUnion.wrapper = _un.wrapper->detach();
            detUnion.metaData = _un.metaData;
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
                out.emplace(std::get<0>(name_node), std::get<1>(name_node).makeInstanceOf());
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            detUnion.schema = _un.schema;
            detUnion.wrapper = _un.wrapper->makeInstanceOf();
            detUnion.metaData = _un.metaData;
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
                if (std::get<1>(name_node).hasOverride())
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
                fields.push_back(f.first);
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
            return not _ov.hasPrefab and not _ov.hasOverride;
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
            return value.get<Override<float>>().getDefaltValue();
        }
        if (value.is<Override<int64_t>>())
        {
            return static_cast<float>(value.get<Override<int64_t>>().getDefaltValue());
        }
        throw BadType();
    }
    int64_t Node::getDefaultInt() const
    {
        if (value.is<Override<int64_t>>())
        {
            return value.get<Override<int64_t>>().getDefaltValue();
        }
        throw BadType();
    }
    char const* Node::getDefaultString() const
    {
        if (value.is<Override<String>>())
        {
            return value.get<Override<String>>().getDefaltValue().c_str();
        }
        throw BadType();
    }
    bool Node::getDefaultBool() const
    {
        if (value.is<Override<bool>>())
        {
            return value.get<Override<bool>>().getDefaltValue();
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

    struct ComputeMem
    {
        MemoryProfiler& prof;
        template <typename T>
        void operator()(Override<T> const& _ov) const
        {
            return _ov.computeMemory(prof);
        }

        void operator()(Null const&) const
        {
        }

        void operator()(Array const& _arr) const
        {
            prof.add("Array::data", _arr.data.capacity() * sizeof(_arr.data.front()));
            for (auto&& item : _arr.data)
            {
                item->computeMemory(prof);
                prof.add("Array::data::value_ptr", sizeof(Ent::Node));
            }
            prof.nodeCount += _arr.data.size();
            prof.nodeByComp[prof.currentComp.front()] += _arr.data.size();
        }

        void operator()(Object const& _obj) const
        {
            for (auto&& name_node : _obj)
            {
                prof.add("Object::name_node", sizeof(name_node));
                std::get<1>(name_node).computeMemory(prof);
            }
            prof.nodeCount += _obj.size();
            prof.nodeByComp[prof.currentComp.front()] += _obj.size();
        }

        void operator()(Union const& _un) const
        {
            _un.computeMemory(prof);
        }
    };

    void Node::computeMemory(MemoryProfiler& prof) const
    {
        mapbox::util::apply_visitor(ComputeMem{ prof }, value);
    }

    // ********************************* SubSceneComponent ****************************************
    SubSceneComponent::SubSceneComponent(
        bool _isEmbedded, Override<String> _file, size_t _index, std::unique_ptr<Scene> _embedded)
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

    static Ent::Node makeDefaultActorStatesField(EntityLib const& _entlib)
    {
        Ent::Subschema const& actorStatesSchema =
            _entlib.schema.schema.allDefinitions.at(actorStatesSchemaName);
        return Node{ Array{}, &actorStatesSchema };
    }

    Entity::Entity(EntityLib const& _entlib)
        : entlib(&_entlib)
        , name(std::string())
        , actorStates(Ent::makeDefaultActorStatesField(_entlib))
        , color(Ent::makeDefaultColorField(_entlib))
        , thumbnail(std::string())
        , instanceOf(std::string())
        , maxActivationLevel(Ent::ActivationLevel::Started)
    {
    }

    Entity::Entity(
        EntityLib const& _entlib,
        Override<String> _name,
        std::map<std::string, Component> _components,
        std::unique_ptr<SubSceneComponent> _subSceneComponent,
        Node _actorStates,
        Node _color,
        Override<String> _thumbnail,
        Override<String> _instanceOf,
        Override<Ent::ActivationLevel> _maxActivationLevel,
        bool _hasASuper)
        : entlib(&_entlib)
        , name(std::move(_name))
        , components(std::move(_components))
        , subSceneComponent(std::move(_subSceneComponent))
        , actorStates(std::move(_actorStates))
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

        std::unique_ptr<Entity> ent = std::make_unique<Entity>(
            *entlib,
            name,
            std::move(instComponents),
            std::move(instSubSceneComponent),
            actorStates,
            color,
            thumbnail,
            instanceOf,
            maxActivationLevel);
        ent->hasASuper = hasASuper;
        return ent;
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
            actorStates.makeInstanceOf(),
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
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

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
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

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

using Ent::String;

struct MergeMapOverride
{
    Ent::Subschema const& _nodeSchema;
    json const& _data;
    Ent::Node const* _super;

    // Merge the instance array/map/set with the template array/map/set and return the resulting Ent::Array
    template <typename GetKeyJson, typename GetKeyNode>
    Ent::Array operator()(
        GetKeyJson&& getKeyJson, ///< Function to get the key in the json (instance)
        GetKeyNode&& getKeyNode ///< Function to get the key in the Node (template)
    )
    {
        using namespace Ent;

        auto&& meta = _nodeSchema.meta.get<Ent::Subschema::ArrayMeta>();
        bool const ordered = meta.ordered;

        // Make a map key=>item of the instance array
        using KeyType = std::remove_reference_t<decltype(getKeyJson(json()))>;
        std::map<KeyType, json const*> instancePropMap;
        for (auto const& item : _data)
        {
            instancePropMap.emplace(getKeyJson(item), &item);
        }
        std::vector<std::pair<KeyType, Node>> result;
        if (_super != nullptr)
        {
            // Load all Nodes from the _super (overriden or not)
            for (Ent::Node const* subSuper : _super->getItems())
            {
                KeyType key = getKeyNode(subSuper);
                if (instancePropMap.count(key)) // Overriden in instance
                {
                    Ent::Node tmpNode =
                        loadNode(_nodeSchema.singularItems->get(), *instancePropMap[key], subSuper);
                    result.emplace_back(key, std::move(tmpNode));
                    instancePropMap.erase(key); // Later we need to know which item are NOT in the template
                }
                else // Not overriden
                {
                    Ent::Node tmpNode = loadNode(_nodeSchema.singularItems->get(), json(), subSuper);
                    ENTLIB_ASSERT(tmpNode.hasOverride() == false);
                    result.emplace_back(key, std::move(tmpNode));
                }
            }
        }
        // Load items from instance which are not in template (they are new)
        // Use _data (and not instancePropMap) to keep the order of items inside _data
        for (auto const& item : _data)
        {
            auto key = getKeyJson(item);
            if (instancePropMap.count(key))
            {
                result.emplace_back(key, loadNode(_nodeSchema.singularItems->get(), item, nullptr));
            }
        }
        if (ordered)
        {
            std::sort(begin(result), end(result), [](auto&& a, auto&& b) {
                return std::get<0>(a) < std::get<0>(b);
            });
        }
        Ent::Array arr;
        for (auto const& key_node : result)
        {
            arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(std::get<1>(key_node))));
        }
        return arr;
    }
};

static Ent::Node loadNode(Ent::Subschema const& _nodeSchema, json const& _data, Ent::Node const* _super)
{
    ENTLIB_ASSERT(_super == nullptr or &_nodeSchema == _super->getSchema());

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
            // We don't want to "override" this value to avoid to write every oneOf
            if (_super != nullptr) // If there is a template, the value is not overriden
            {
                result = Ent::Node(Ent::Override<String>("", def, tl::nullopt), &_nodeSchema);
            }
            else // If there is no template, it is overriden to be sure the node "hasOverride" and be saved
            {
                result = Ent::Node(Ent::Override<String>("", tl::nullopt, def), &_nodeSchema);
            }
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
            result = Ent::Node(Ent::Override<String>(def, supVal, val), &_nodeSchema);
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
            object.emplace(name.c_str(), std::move(tmpNode));
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
            else // If it is a singularItems and there is _data, we have to use the overridePolicy
            {
                auto&& meta = _nodeSchema.meta.get<Ent::Subschema::ArrayMeta>();
                using namespace Ent;
                MergeMapOverride mergeMapOverride{ _nodeSchema, _data, _super };
                switch (hash(meta.overridePolicy))
                {
                case "map"_hash:
                {
                    // It is a C++ map.
                    // In json it is an array of "2 item array" where the 1st item is the key
                    // and can be string, float or integer
                    // meta.ordered means the items have to be sorted by the key
                    Ent::DataType keyType = _nodeSchema.singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
                    switch (keyType)
                    {
                    case Ent::DataType::string:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<std::string>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getString(); });
                        break;
                    case Ent::DataType::number:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<float>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getFloat(); });
                        break;
                    case Ent::DataType::integer:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getInt(); });
                        break;
                    default:
                        throw std::runtime_error("Unknown key type in map " + _nodeSchema.name);
                    }
                }
                break;
                case "set"_hash:
                {
                    // It is a C++ set.
                    // In json it is an array of primitive. string, float or integer or oneOf
                    // meta.ordered means the items have to be sorted by the key
                    Ent::DataType const keyType = _nodeSchema.singularItems->get().type;
                    switch (keyType)
                    {
                    case Ent::DataType::oneOf: // The key is the className string
                    {
                        auto const& unionMeta =
                            _nodeSchema.singularItems->get().meta.get<Ent::Subschema::UnionMeta>();
                        arr = mergeMapOverride(
                            [&unionMeta](json const& item) {
                                return item[unionMeta.typeField].get<std::string>();
                            },
                            [](Node const* subSuper) { return subSuper->getUnionType(); });
                    }
                    break;
                    case Ent::DataType::string: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<std::string>(); },
                            [](Node const* tmplItem) { return tmplItem->getString(); });
                        break;
                    case Ent::DataType::number: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<float>(); },
                            [](Node const* tmplItem) { return tmplItem->getFloat(); });
                        break;
                    case Ent::DataType::integer: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->getInt(); });
                        break;
                    default:
                        throw std::runtime_error("Unknown key type in set " + _nodeSchema.name);
                    }
#pragma warning(pop)
                }
                break;
                case ""_hash: // The default "overridePolicy" is for simple array
                {
                    for (auto const& item : _data)
                    {
                        Ent::Node const* subSuper =
                            (_super != nullptr and (_super->size() > index)) ? _super->at(index) :
                                                                               nullptr;
                        Ent::Node tmpNode =
                            loadNode(_nodeSchema.singularItems->get(), item, subSuper);
                        arr.data.emplace_back(nonstd::make_value<Ent::Node>(std::move(tmpNode)));
                        ++index;
                    }
                }
                break;
                default:
                    throw std::runtime_error(format(
                        "Unknown key type (%s) in schema of %s",
                        meta.overridePolicy.c_str(),
                        _nodeSchema.name.c_str()));
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
        std::string dataType;
        if (_data.count(typeField) != 0)
        {
            dataType = _data.at(typeField).get<std::string>();
            if (_super != nullptr and dataType != _super->getUnionType())
            {
                _super = nullptr; // The datatype has changed. No more use the data from _super
            }
        }
        else // No uniontype
        {
            if (_super != nullptr) // If no uniontype, use the one the template
            {
                dataType = _super->getUnionType();
            }
            else
            {
                // We are making a new node without input data
                // "back()" because the base type is at the end of the type list
                // TODO : Loïc - Add in metadata the name of the default type
                dataType =
                    _nodeSchema.oneOf->back()->properties.at(typeField).get().constValue->get<std::string>();
            }
        }
        bool typeFound = false;
        for (Ent::SubschemaRef const& schemaTocheck : *_nodeSchema.oneOf)
        {
            auto&& schemaType =
                schemaTocheck->properties.at(typeField).get().constValue->get<std::string>();
            if (schemaType == dataType)
            {
                Ent::Node const* superUnionDataWrapper =
                    _super != nullptr ? _super->getUnionDataWrapper() : nullptr;
                ENTLIB_ASSERT(
                    superUnionDataWrapper == nullptr
                    or &schemaTocheck.get() == superUnionDataWrapper->getSchema());
                Ent::Node dataNode = loadNode(schemaTocheck.get(), _data, superUnionDataWrapper);
                Ent::Union un{};
                un.schema = &_nodeSchema;
                un.wrapper = nonstd::make_value<Ent::Node>(std::move(dataNode));
                un.metaData = &meta;
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
        auto&& meta = _schema.meta.get<Ent::Subschema::ArrayMeta>();
        for (Ent::Node const* item : _node.getItems())
        {
            if (item->hasOverride())
            {
                ENTLIB_ASSERT(item->getSchema() != nullptr);
                json tmpNode = saveNode(*item->getSchema(), *item);
                data.emplace_back(std::move(tmpNode));
            }
            else if (meta.overridePolicy.empty())
            {
                data.emplace_back(json());
            }
        }
    }
    break;
    case Ent::DataType::entityRef:
    {
        Ent::EntityRef ref = _node.getEntityRef();
        data = ref.entityPath.c_str();
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
        superEntity = _entlib.loadEntityReadOnly(*instanceOf, _superEntityFromParentEntity);
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
    Ent::Override<String> superThumbnail = superEntity->getThumbnailValue();
    Ent::Override<String> ovThumbnail = superThumbnail.makeOverridedInstanceOf(thumbnail);

    tl::optional<std::string> const name = _entNode.count("Name") != 0 ?
                                               _entNode.at("Name").get<std::string>() :
                                               tl::optional<std::string>();

    Ent::Override<String> superName = superEntity->getNameValue();
    Ent::Override<String> ovName = superName.makeOverridedInstanceOf(name);

    Ent::Override<String> superInstanceOf = superEntity->getInstanceOfValue();
    Ent::Override<String> ovInstanceOf = superName.makeOverridedInstanceOf(instanceOf);

    tl::optional<Ent::ActivationLevel> maxActivationLevel;
    if (_entNode.count("MaxActivationLevel") != 0)
    {
        maxActivationLevel =
            parseActivationLevel(_entNode.at("MaxActivationLevel").get<std::string>());
    }
    Ent::Override<Ent::ActivationLevel> superActivationLevel =
        superEntity != nullptr ?
            superEntity->getMaxActivationLevelValue() :
            Ent::Override<Ent::ActivationLevel>{ Ent::ActivationLevel::Started };
    Ent::Override<Ent::ActivationLevel> ovMaxActivationLevel =
        superActivationLevel.makeOverridedInstanceOf(maxActivationLevel);

    // Color
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

    // ActorStates
    Ent::Subschema const& actorStatesSchema =
        _entlib.schema.schema.allDefinitions.at(Ent::actorStatesSchemaName);
    Ent::Node ovActorStates(Ent::Array{}, &actorStatesSchema);
    if (_entNode.contains("ActorStates"))
    {
        ovActorStates =
            loadNode(actorStatesSchema, _entNode.at("ActorStates"), &superEntity->getActorStates());
    }
    else
    {
        ovActorStates = superEntity->getActorStates().makeInstanceOf();
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

                Ent::Override<String> file =
                    superComp != nullptr ? superComp->file : Ent::Override<String>(std::string());

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
        std::move(ovActorStates),
        std::move(ovColor),
        std::move(ovThumbnail),
        std::move(ovInstanceOf),
        std::move(ovMaxActivationLevel));
}

template <typename Type, typename Cache, typename ValidateFunc, typename LoadFunc>
Type const* Ent::EntityLib::loadEntityOrScene(
    std::filesystem::path const& _path,
    Cache& cache,
    ValidateFunc&& validate,
    LoadFunc&& load,
    Type const* _super) const
{
    auto const absPath = getAbsolutePath(_path);
    std::filesystem::path relPath = absPath.c_str() + rawdataPath.native().size() + 1;
    bool reload = false;
    auto error = std::error_code{};
    auto timestamp = std::filesystem::last_write_time(absPath, error);
    if (error)
    {
        const auto msg = not std::filesystem::exists(absPath) ?
                             format("file doesn't exist: %ls", absPath.c_str()) :
                             format(
                                 "last_write_time(p): invalid argument: %ls (%s)",
                                 absPath.c_str(),
                                 error.message().c_str());
        throw std::filesystem::filesystem_error(msg);
    }
    auto iter = cache.find(relPath);
    if (iter == cache.end())
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
                validate(schema.schema, toolsDir, document);
            }
            catch (...)
            {
                fprintf(stderr, "Error, validating : %ls\n", absPath.c_str());
                throw;
            }
        }

        std::unique_ptr<Type> entity = load(*this, schema, document, _super);
        auto file = typename Cache::mapped_type{ std::move(entity), timestamp };
        auto iter_bool = cache.insert_or_assign(relPath, std::move(file));
        return std::get<0>(iter_bool)->second.data.get();
    }
    else
    {
        return iter->second.data.get();
    }
}

Ent::Entity const* Ent::EntityLib::loadEntityReadOnly(
    std::filesystem::path const& _entityPath, Ent::Entity const* _super) const
{
    return loadEntityOrScene<Ent::Entity>(
        _entityPath, m_entityCache, &validateEntity, &::loadEntity, _super);
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

Ent::Scene const* Ent::EntityLib::loadSceneReadOnly(std::filesystem::path const& _scenePath) const
{
    auto loadFunc = [](Ent::EntityLib const& _entLib,
                       Ent::ComponentsSchema const& _schema,
                       json const& _document,
                       Ent::Scene const* _super) {
        return ::loadScene(_entLib, _schema, _document.at("Objects"), _super);
    };

    return loadEntityOrScene<Ent::Scene>(_scenePath, m_sceneCache, &validateScene, loadFunc, nullptr);
}

std::unique_ptr<Ent::Entity>
Ent::EntityLib::loadEntity(std::filesystem::path const& _entityPath, Ent::Entity const* _super) const
{
    return loadEntityReadOnly(_entityPath, _super)->clone();
}

std::unique_ptr<Ent::Scene> Ent::EntityLib::loadScene(std::filesystem::path const& _scenePath) const
{
    return loadSceneReadOnly(_scenePath)->clone();
}

static json saveEntity(Ent::ComponentsSchema const& _schema, Ent::Entity const& _entity)
{
    json entNode;

    // Always save Name since it is use for override
    entNode.emplace("Name", _entity.getNameValue().get().c_str());

    if (_entity.getInstanceOfValue().isSet())
    {
        entNode.emplace("InstanceOf", _entity.getInstanceOfValue().get().c_str());
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
                    data.emplace("File", subscene->file.get().c_str());
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
    Ent::Subschema const& actorStatesSchema =
        _schema.schema.allDefinitions.at(Ent::actorStatesSchemaName);
    if (_entity.getActorStates().hasOverride())
    {
        entNode.emplace("ActorStates", saveNode(actorStatesSchema, _entity.getActorStates()));
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
        actorStates.detach(),
        std::move(detachedColor),
        getThumbnailValue().detach(),
        Override<String>{},
        std::move(detachedMaxActivationLevel));
}

std::unique_ptr<Ent::Entity> Ent::EntityLib::makeInstanceOf(std::string _instanceOf) const
{
    Ent::Entity const* templ = loadEntityReadOnly(_instanceOf, nullptr);
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
        templ->getSubSceneComponent() != nullptr ? templ->getSubSceneComponent()->makeInstanceOf() :
                                                   nullptr,
        templ->getActorStates().makeInstanceOf(),
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

std::map<std::filesystem::path, Ent::EntityLib::EntityFile> const& Ent::EntityLib::getEntityCache() const
{
    return m_entityCache;
}
std::map<std::filesystem::path, Ent::EntityLib::SceneFile> const& Ent::EntityLib::getSceneCache() const
{
    return m_sceneCache;
}

void Ent::EntityLib::clearCache()
{
    m_entityCache.clear();
    m_sceneCache.clear();
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

void Ent::SubSceneComponent::computeMemory(MemoryProfiler& prof) const
{
    file.computeMemory(prof);
    if (embedded)
        embedded->computeMemory(prof);
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
