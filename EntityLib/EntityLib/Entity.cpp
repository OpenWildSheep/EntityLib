#include "Entity.h"

#include <ciso646>

#include "external/json.hpp"

#include "include/EntityLib.h"
#include "Tools.h"
#include "MemoryProfiler.h"
#include "SubSceneComponent.h"

using namespace nlohmann;

namespace Ent
{
    void Entity::computeMemory(MemoryProfiler& prof) const
    {
        name.computeMemory(prof);
        for (auto&& name_comp : components)
        {
            prof.addMem("Entity::components::value", sizeof(name_comp));
            prof.addMem("Entity::components::key", sizeof(std::get<0>(name_comp).size()));
            std::get<1>(name_comp).computeMemory(prof);
        }
        if (subSceneComponent)
        {
            subSceneComponent->computeMemory(prof);
        }
        actorStates.computeMemory(prof);
        color.computeMemory(prof);
        thumbnail.computeMemory(prof);
        instanceOf.computeMemory(prof);
        maxActivationLevel.computeMemory(prof);
    }

    void Ent::Entity::changeInstanceOf(char const* _newPrefab)
    {
        const auto cloned = clone();
        resetInstanceOf(_newPrefab);
        cloned->applyAllValuesButPrefab(*this, CopyMode::MinimalOverride);
    }

    extern char const* actorStatesSchemaName;
    extern char const* colorSchemaName;

    static Ent::Node makeDefaultActorStatesField(EntityLib const& _entlib)
    {
        Ent::Subschema const& actorStatesSchema =
            AT(_entlib.schema.schema.allDefinitions, actorStatesSchemaName);
        return Node{Array{&_entlib, &actorStatesSchema}, &actorStatesSchema};
    }

    Ent::Node makeDefaultColorField(EntityLib const& _entlib);

    Entity::Entity(EntityLib const& _entlib, char const* _name)
        : entlib(&_entlib)
        , name(std::string())
        , actorStates(Ent::makeDefaultActorStatesField(_entlib))
        , color(Ent::makeDefaultColorField(_entlib))
        , thumbnail(std::string())
        , instanceOf(std::string())
        , maxActivationLevel(Ent::ActivationLevel::Started)
    {
        if (_name != nullptr)
        {
            name.set(_name);
        }
    }

    Entity::Entity(
        EntityLib const& _entlib,
        Override<String> _name,
        std::map<std::string, Component> _components,
        std::set<std::string> _removedComponents,
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
        , removedComponents(std::move(_removedComponents))
        , subSceneComponent(std::move(_subSceneComponent))
        , actorStates(std::move(_actorStates))
        , color(std::move(_color))
        , thumbnail(std::move(_thumbnail))
        , instanceOf(std::move(_instanceOf))
        , maxActivationLevel(_maxActivationLevel)
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
            removedComponents,
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
    void Entity::setName(Ent::String _name)
    {
        if (name.get() == _name)
        {
            return;
        }
        if (hasASuper)
        {
            throw ContextException(
                "Setting name : %s. A SubEntity of an instance which override a SubEntity in a "
                "prefab can't be renamed. Check the canBeRenamed method.",
                _name.c_str());
        }
        if (parentScene != nullptr)
        {
            parentScene->renameEntity(name.get().c_str(), _name.c_str());
        }
        else
        {
            name.set(std::move(_name));
        }
    }

    void Entity::_setNameRaw(char const* _name)
    {
        if (strcmp(name.get().c_str(), _name) == 0)
        {
            return;
        }
        name.set(_name);
    }

    bool Entity::canBeRenamed() const
    {
        return not hasASuper;
    }
    bool Entity::newInTheScene() const
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
    void Entity::setThumbnail(Ent::String _thumbPath)
    {
        thumbnail.set(std::move(_thumbPath));
    }
    std::array<double, 4> Entity::getColor() const
    {
        std::array<double, 4> col{};
        for (size_t i = 0; i < 4; ++i)
        {
            col[i] = color.at(i)->getFloat();
        }
        return col;
    }
    void Entity::setColor(std::array<double, 4> _color)
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
            ENTLIB_LOG_ERROR("Unknown Component type : %s", _type);
            return nullptr;
        }
        if (entlib->componentDependencies.count(_type) != 0) // Could be an editor componant
        {
            for (auto&& dep : AT(entlib->componentDependencies, _type))
            {
                addComponent(dep.c_str());
            }
        }
        Ent::Subschema const& compSchema = *AT(entlib->schema.components, _type);
        Ent::Component comp{
            false, _type, entlib->loadNode(compSchema, json(), nullptr), 1, components.size()};
        removedComponents.erase(_type);
        auto&& [iter, inserted] = components.emplace(_type, std::move(comp));
        if (inserted)
        {
            iter->second.root.setAddedInInsance(true);
        }
        return &(iter->second);
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
        auto iter = components.find(_type);
        if (iter != end(components))
        {
            Component const& comp = iter->second;
            if (comp.hasPrefab)
            {
                removedComponents.insert(_type);
            }
            components.erase(iter);
        }
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
            subSceneComponent = std::make_unique<SubSceneComponent>(entlib);
            removedComponents.erase("SubScene");
            subSceneComponent->embedded->setOwnerEntity(this);
        }
        return &(*subSceneComponent);
    }

    void Entity::removeSubSceneComponent()
    {
        if (subSceneComponent != nullptr)
        {
            subSceneComponent.reset();
            removedComponents.insert("SubScene");
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
            std::set<std::string>{},
            std::move(instSubSceneComponent),
            actorStates.makeInstanceOf(),
            color.makeInstanceOf(),
            thumbnail.makeInstanceOf(),
            instanceOf.makeInstanceOf(),
            maxActivationLevel.makeInstanceOf(),
            true // It is an instance so it is not a new entity in the scene
        );
    }

    bool Entity::hasOverride() const
    {
        //    If "InstanceOf" is set, this entity "hasOverride"
        if (name.isSet() or color.hasOverride() or thumbnail.isSet() or actorStates.hasOverride()
            or instanceOf.hasOverride())
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

    void Entity::setInstanceOf(std::string const& _prefab)
    {
        resetInstanceOf(_prefab.c_str());
    }

    void Entity::resetInstanceOf(char const* _prefab)
    {
        std::shared_ptr<Ent::Entity const> templ;
        std::string prefab;
        if (_prefab == nullptr or strlen(_prefab) == 0)
        {
            templ = std::make_shared<Ent::Entity const>(*entlib, nullptr);
        }
        else
        {
            prefab = entlib->getRelativePath(_prefab).generic_u8string();
            templ = entlib->loadEntityReadOnly(prefab.c_str(), nullptr);
        }
        components.clear();
        removedComponents.clear();
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
        auto prevName = name;
        name = templ->getNameValue().makeInstanceOf();
        if (not canBeRenamed()) // Name is the key to override entities, so it can't be changed
        {
            name.set(prevName.get());
        }
        subSceneComponent = templ->getSubSceneComponent() != nullptr ?
                                templ->getSubSceneComponent()->makeInstanceOf() :
                                nullptr;
        actorStates = templ->getActorStates().makeInstanceOf();
        color = templ->getColorValue().makeInstanceOf();
        thumbnail = templ->getThumbnailValue().makeInstanceOf();
        instanceOf = templ->getInstanceOfValue().makeOverridedInstanceOf(prefab.c_str());
        maxActivationLevel = templ->getMaxActivationLevelValue().makeInstanceOf();

        updateSubSceneOwner();
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
        return {std::move(path), rootEntity, rootScene};
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

        return {relativePath};
    }

    /// @tparam E is Entity or Entity const.
    template <typename E>
    static auto getSubScene(E* _entity) -> decltype(_entity->getSubSceneComponent()->embedded.get())
    {
        if (auto* subScene = _entity->getSubSceneComponent())
        {
            return subScene->embedded.get();
        }
        return nullptr;
    }

    /// @tparam E is Entity or Entity const.
    template <typename E>
    static E*
    resolveEntityRefRecursive(E* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path)
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
            _current = _down->getEntity(head.c_str());
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

    Entity* resolveEntityRefRecursive(
        Entity* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path)
    {
        return resolveEntityRefRecursive<>(_current, _up, _down, _path);
    }

    Entity const* resolveEntityRefRecursive(
        Entity const* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path)
    {
        return resolveEntityRefRecursive<>(_current, _up, _down, _path);
    }

    /// @tparam E is Entity or Entity const.
    template <typename E>
    E* resolveEntityRefImpl(E* _current, const EntityRef& _entityRef)
    {
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

        Scene* down = getSubScene(_current);
        Scene* up = _current->getParentScene();

        return resolveEntityRefRecursive(_current, up, down, parts);
    }

    Entity* Entity::resolveEntityRef(const EntityRef& _entityRef)
    {
        return resolveEntityRefImpl(this, _entityRef);
    }

    Entity const* Entity::resolveEntityRef(const EntityRef& _entityRef) const
    {
        return resolveEntityRefImpl(this, _entityRef);
    }

    void Entity::updateSubSceneOwner()
    {
        if (auto* subScene = getSubSceneComponent())
        {
            subScene->embedded->setOwnerEntity(this);
        }
    }

    static char const* getActivationLevelString(Ent::ActivationLevel _level)
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

    nlohmann::json Ent::Entity::saveEntity() const
    {
        ComponentsSchema const& _schema = entlib->schema;
        json entNode;

        // Always save Name since it is use for override
        entNode.emplace("Name", getNameValue().get().c_str());

        if (getInstanceOfValue().isSet())
        {
            entNode.emplace("InstanceOf", getInstanceOfValue().get().c_str());
        }

        Subschema const& colorSchema = AT(_schema.schema.allDefinitions, colorSchemaName);
        if (getColorValue().hasOverride())
        {
            entNode.emplace("Color", EntityLib::dumpNode(colorSchema, getColorValue()));
        }

        if (getThumbnailValue().isSet())
        {
            entNode.emplace("Thumbnail", getThumbnail());
        }

        if (getMaxActivationLevelValue().isSet())
        {
            entNode.emplace("MaxActivationLevel", getActivationLevelString(getMaxActivationLevel()));
        }

        json& componentsNode = entNode["Components"] = json::array();
        std::vector<Component const*> sortedComp;
        for (auto&& type_comp : getComponents())
        {
            sortedComp.push_back(&std::get<1>(type_comp));
        }
        Component subscenePlaceholder{true, "SubScene", Node(), 1, 0};
        if (SubSceneComponent const* subscene = getSubSceneComponent())
        {
            subscenePlaceholder.index = subscene->index;
            sortedComp.push_back(&subscenePlaceholder);
        }
        std::sort(begin(sortedComp), end(sortedComp), [](Component const* cmp, Component const* cmp2) {
            return cmp->index < cmp2->index;
        });
        for (Component const* comp : sortedComp)
        {
            if (comp->type == "SubScene")
            {
                SubSceneComponent const* subscene = getSubSceneComponent();
                ENTLIB_ASSERT(subscene != nullptr);
                bool const subsceneHasOverride = subscene->hasOverride();
                bool const hasInstanceOf = getInstanceOf() != nullptr;
                if ((subsceneHasOverride and hasInstanceOf) or not hasInstanceOf)
                {
                    json data;
                    data.emplace("Embedded", subscene->embedded->saveScene()["Objects"]);

                    json compNode;
                    compNode.emplace("Version", comp->version);
                    compNode.emplace("Type", comp->type);
                    compNode.emplace("Data", std::move(data));
                    componentsNode.emplace_back(std::move(compNode));
                }
            }
            else if (not comp->hasPrefab or comp->root.hasOverride())
            {
                json compNode;
                compNode.emplace("Version", comp->version);
                compNode.emplace("Type", comp->type);
                compNode.emplace(
                    "Data", EntityLib::dumpNode(*AT(_schema.components, comp->type), comp->root));

                componentsNode.emplace_back(std::move(compNode));
            }
        }
        for (auto const& type : removedComponents)
        {
            json compNode;
            compNode.emplace("Type", type);
            compNode.emplace("Data", json{});
            componentsNode.emplace_back(std::move(compNode));
        }
        Subschema const& actorStatesSchema = AT(_schema.schema.allDefinitions, actorStatesSchemaName);
        if (getActorStates().hasOverride())
        {
            entNode.emplace("ActorStates", EntityLib::dumpNode(actorStatesSchema, getActorStates()));
        }
        return entNode;
    }

    void Ent::Entity::applyToPrefab()
    {
        if (getInstanceOf() == nullptr)
        {
            throw ContextException("This entity has no prefab");
        }
        std::string prefabPath = getInstanceOf();
        auto prefab = entlib->loadEntity(prefabPath);
        auto prefabName = prefab->name;
        auto instanceName = name;

        // When the value is overridden is the source, we want to make it overridden in the dest => CopyOverride
        applyAllValuesButPrefab(*prefab, CopyMode::CopyOverride);
        // Asked by the maxscript team because they don't want to change the name this way
        prefab->name = prefabName;
        // Need to save the prefab before "resetInstanceOf"
        // because "resetInstanceOf" will use the new prefab
        entlib->saveEntity(*prefab, prefabPath.c_str());
        resetInstanceOf(prefabPath.c_str()); // Reset 'this' to a vanilla instance of prefab
        name = instanceName;
    }

    void Ent::Entity::applyAllValues(Entity& _dest, CopyMode _copyMode) const
    {
        applyInstanceOfField(*this, _dest, _copyMode);
        applyAllValuesButPrefab(_dest, _copyMode);
    }

    void Ent::Entity::applyAllValuesButPrefab(Entity& _dest, CopyMode _copyMode) const
    {
        name.applyAllValues(_dest.name, _copyMode);
        thumbnail.applyAllValues(_dest.thumbnail, _copyMode);
        maxActivationLevel.applyAllValues(_dest.maxActivationLevel, _copyMode);
        actorStates.applyAllValues(_dest.actorStates, _copyMode);
        color.applyAllValues(_dest.color, _copyMode);

        for (auto&& name_comp : getComponents())
        {
            auto&& cmpName = name_comp.first;
            auto&& comp = name_comp.second;
            // addComponent has no effect if the component exist
            comp.applyAllValues(*_dest.addComponent(cmpName.c_str()), _copyMode);
        }
        std::vector<char const*> compToRemove;
        for (auto&& name_comp : _dest.getComponents())
        {
            auto&& cmpName = name_comp.first;
            if (getComponent(cmpName.c_str()) == nullptr) // Removed component
            {
                compToRemove.push_back(cmpName.c_str());
            }
        }
        if (auto subScene = getSubSceneComponent())
        {
            // addSubSceneComponent has no effect if the component exist
            subScene->applyAllValues(*_dest.addSubSceneComponent(), _copyMode);
        }
        else if (auto destSubScene = _dest.getSubSceneComponent()) // Removed component
        {
            compToRemove.push_back("SubScene");
        }
        for (auto&& cmpName : compToRemove)
        {
            _dest.removeComponent(cmpName);
        }
    }

    std::unique_ptr<Ent::Entity> Ent::Entity::detachEntityFromPrefab() const
    {
        std::map<std::string, Ent::Component> detComponents;
        size_t cmpIndex = 0;
        for (auto const& type_comp : getComponents())
        {
            auto const& type = std::get<0>(type_comp);
            auto const& comp = std::get<1>(type_comp);

            Ent::Component detachedComp{false, type, comp.root.detach(), 1, cmpIndex};

            detComponents.emplace(type, std::move(detachedComp));
            ++cmpIndex;
        }
        std::unique_ptr<SubSceneComponent> detSubSceneComponent;
        if (SubSceneComponent const* subscene = getSubSceneComponent())
        {
            detSubSceneComponent = std::make_unique<SubSceneComponent>(entlib);
            detSubSceneComponent->embedded = std::make_unique<Ent::Scene>(entlib);
            for (auto const& subEntity : subscene->embedded->getObjects())
            {
                detSubSceneComponent->embedded->addEntity(subEntity->detachEntityFromPrefab());
            }
        }

        auto detachedColor = getColorValue().detach();
        auto detachedMaxActivationLevel = getMaxActivationLevelValue().detach();
        return std::make_unique<Ent::Entity>(
            *entlib,
            getNameValue().detach().makeOverridedInstanceOf(std::string(getName()) + "_detached"),
            std::move(detComponents),
            std::set<std::string>{}, // removedComponents
            std::move(detSubSceneComponent),
            actorStates.detach(),
            std::move(detachedColor),
            getThumbnailValue().detach(),
            Override<String>{},
            detachedMaxActivationLevel);
    }
} // namespace Ent
