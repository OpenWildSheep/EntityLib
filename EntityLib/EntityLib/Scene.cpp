#include "Scene.h"

#include <ciso646>

#include "external/json.hpp"

#include "Entity.h"
#include "include/EntityLib.h"
#include "Tools.h"

using namespace nlohmann;

namespace Ent
{
    void Scene::computeMemory(MemoryProfiler& prof) const
    {
        objects.computeMemory(prof);
    }

    Scene::Scene(EntityLib const* _entitylib)
        : entlib(_entitylib)
    {
    }

    Scene::Scene(EntityMap _entities)
        : objects(std::move(_entities))
    {
        updateChildrenContext();
    }

    Entity* Scene::addEntity(std::unique_ptr<Entity>&& _entity)
    {
        _entity->setParentScene(this);
        auto name = _entity->getName();
        if (name == nullptr or strlen(name) == 0)
        {
            throw EmptyKey("Entity without name in Scene::addEntity!");
        }
        auto* ent = objects.emplace(name, std::move(_entity), OverrideValueLocation::Override);
        return ent;
    }

    std::vector<Entity*> Scene::getObjects() const
    {
        std::vector<Entity*> entities;
        for (auto&& name_ent : objects.map)
        {
            if (name_ent.second.isPresent.get())
            {
                entities.push_back(name_ent.second.value.get());
            }
        }
        return entities;
    }

    Entity const* Scene::getEntity(size_t _index) const
    {
        if (_index >= objects.size())
        {
            return nullptr;
        }
        size_t index = 0;
        for (auto&& key_val : objects.map)
        {
            if (key_val.second.isPresent.get())
            {
                if (index == _index)
                {
                    return key_val.second.value.get();
                }
                ++index;
            }
        }
        return nullptr;
    }

    Entity* Scene::addEntity(char const* name)
    {
        if (name == nullptr or strlen(name) == 0)
        {
            throw EmptyKey("Entity without name in Scene::addEntity!");
        }
        return addEntity(std::make_unique<Ent::Entity>(*entlib, name));
    }

    Entity* Scene::getEntity(size_t index)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Entity*>(std::as_const(*this).getEntity(index));
    }

    Entity const* Scene::getEntity(char const* _name) const
    {
        return objects.at(_name);
    }

    Entity* Scene::getEntity(char const* _name)
    {
        return objects.at(_name);
    }

    size_t Scene::entityCount() const
    {
        return objects.size();
    }

    void Scene::removeEntity(char const* _name)
    {
        objects.erase(_name);
    }

    void Scene::renameEntity(char const* _currentName, char const* _newName)
    {
        auto iter = objects.map.find(_currentName);
        if (iter != objects.map.end())
        {
            if (not iter->second.value->canBeRenamed())
            {
                throw CantRename(staticFormat(
                    "Can't rename '%s' to '%s'. A SubEntity of an instance which override a "
                    "SubEntity in a prefab can't be renamed. Check the canBeRenamed method.",
                    _currentName,
                    _newName));
            }

            auto ent = iter->second.value->clone(); // Avoid to let the value to nullptr
            objects.erase(_currentName);
            ent->_setNameRaw(_newName);
            objects.emplace(_newName, std::move(ent), Ent::OverrideValueLocation::Override);
        }
        else
        {
            throw CantRename(staticFormat(
                "Can't rename %s to %s because it doesn't exist", _currentName, _newName));
        }
    }

    std::vector<std::unique_ptr<Entity>> Scene::releaseAllEntities()
    {
        std::vector<std::unique_ptr<Entity>> freeEntities;
        for (auto&& name_ent : objects.map)
        {
            if (name_ent.second.isPresent.get())
            {
                name_ent.second.value->setParentScene(nullptr);
                freeEntities.emplace_back(std::move(name_ent.second.value));
            }
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
        return resolveEntityRef({_path});
    }

    std::unique_ptr<Scene> Scene::makeInstanceOf() const
    {
        EntityMap instanceEntities;
        auto scene = std::make_unique<Scene>(entlib);
        for (auto const& [name, ent] : objects.map)
        {
            instanceEntities.map.emplace(name, ent.makeInstanceOf());
            instanceEntities.map[name].value->setParentScene(scene.get());
        }
        scene->objects = std::move(instanceEntities);
        return scene;
    }

    std::unique_ptr<Scene> Scene::clone() const
    {
        EntityMap instanceEntities;
        auto scene = std::make_unique<Scene>(entlib);
        for (auto const& [name, ent] : objects.map)
        {
            instanceEntities.map.emplace(name, ent.clone());
            instanceEntities.map[name].value->setParentScene(scene.get());
        }
        scene->objects = std::move(instanceEntities);
        return scene;
    }

    bool Scene::hasOverride() const
    {
        for (auto const& name_ent : objects.map)
        {
            auto const& ent = name_ent.second;
            if (ent.hasOverride() or ent.value->newInTheScene())
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

    void Scene::applyAllValues(Scene& _dest, CopyMode _copyMode) const
    {
        std::map<std::string, Entity*> destMap;
        for (auto&& [name, obj] : _dest.objects.map)
        {
            if (obj.isPresent.get())
            {
                destMap.emplace(name, obj.value.get());
            }
        }
        for (auto&& [name, rem] : objects.map)
        {
            if (rem.isPresent.get())
            {
                auto destIter = destMap.find(name);
                auto&& ent = rem.value;
                if (destIter != destMap.end()) // Preserved Entity
                {
                    ent->applyAllValues(*destIter->second, _copyMode);
                    destMap.erase(destIter);
                }
                else // Entity just added
                {
                    _dest.addEntity(ent->clone());
                }
            }
        }
        for (auto&& [name, ent] : destMap)
        {
            _dest.removeEntity(name.c_str());
        }
    }

    void Scene::updateChildrenContext()
    {
        for (auto& name_ent : objects.map)
        {
            name_ent.second.value->setParentScene(this);
        }
    }

    std::unique_ptr<Scene>
    Scene::loadScene(Ent::EntityLib const& _entLib, json const& _entities, Ent::Scene const* _super)
    {
        auto scene = std::make_unique<Ent::Scene>(&_entLib);

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
                    auto const instEntName = entNode.at("Name").get<std::string>();
                    if (superEnt->getName() == instEntName)
                    {
                        instEntNode = &entNode;
                        break;
                    }
                }
                bool const removed =
                    instEntNode != nullptr and instEntNode->count("__removed__") != 0;
                std::unique_ptr<Ent::Entity> ent =
                    (instEntNode == nullptr) ? superEnt->makeInstanceOf() :
                                               _entLib.loadEntityFromJson(*instEntNode, superEnt);
                auto entName = ent->getName();

                ent->setCanBeRenamed(false);
                scene->objects.emplace(entName, std::move(ent), OverrideValueLocation::Prefab);
                if (removed)
                {
                    scene->removeEntity(entName);
                }
            }
        }

        // Add new entities
        for (json const& entNode : _entities)
        {
            auto const name = entNode.at("Name").get<std::string>();
            if (entFromSuper.count(name) != 0)
            {
                continue;
            }
            if (entNode.count("__removed__") != 0) // Strange to remove a new entity. Let's ignore it.
            {
                continue;
            }
            std::unique_ptr<Ent::Entity> ent = _entLib.loadEntityFromJson(entNode, nullptr);
            ENTLIB_ASSERT(ent != nullptr);
            scene->addEntity(std::move(ent));
        }

        return scene;
    }

    json Ent::Scene::saveScene() const
    {
        json document;

        document.emplace("Version", 2);
        json& jsnObjects = document["Objects"];
        jsnObjects = json::array();

        std::vector<EntityMap::value_type const*> orderedEntities;
        orderedEntities.reserve(objects.map.size());
        for (auto& name_ent : objects.map)
        {
            orderedEntities.push_back(&name_ent);
        }
        std::stable_sort(
            begin(orderedEntities),
            end(orderedEntities),
            [](EntityMap::value_type const* a, EntityMap::value_type const* b) {
                return a->second.index < b->second.index; // Try to keep ordering
            });
        for (auto const* name_ent : orderedEntities)
        {
            if (name_ent->second.isPresent.get())
            {
                if (name_ent->second.hasOverride())
                {
                    jsnObjects.emplace_back(name_ent->second.value->saveEntity());
                }
            }
            else if (name_ent->second.isPresent.getPrefab())
            {
                // isPresent is false but it was true in the prefab
                json removedObj;
                removedObj["Name"] = name_ent->first;
                removedObj["__removed__"] = true;
                jsnObjects.emplace_back(std::move(removedObj));
            }
        }

        return document;
    }
} // namespace Ent
