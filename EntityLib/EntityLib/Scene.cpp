#include "Scene.h"

#include <ciso646>

#include "Entity.h"
#include "Tools.h"

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
        for (auto const& name_ent : objects.map)
        {
            instanceEntities.map.emplace(name_ent.first, name_ent.second.makeInstanceOf());
            instanceEntities.map[name_ent.first].value->setParentScene(scene.get());
        }
        scene->objects = std::move(instanceEntities);
        return scene;
    }

    std::unique_ptr<Scene> Scene::clone() const
    {
        EntityMap instanceEntities;
        auto scene = std::make_unique<Scene>(entlib);
        for (auto const& name_ent : objects.map)
        {
            instanceEntities.map.emplace(name_ent.first, name_ent.second.clone());
            instanceEntities.map[name_ent.first].value->setParentScene(scene.get());
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
        for (auto&& name_obj : _dest.objects.map)
        {
            if (name_obj.second.isPresent.get())
            {
                destMap.emplace(name_obj.first, name_obj.second.value.get());
            }
        }
        for (auto&& name_ent : objects.map)
        {
            if (name_ent.second.isPresent.get())
            {
                auto destIter = destMap.find(name_ent.first);
                auto&& ent = name_ent.second.value;
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
        for (auto&& name_ent : destMap)
        {
            _dest.removeEntity(name_ent.first.c_str());
        }
    }

    void Scene::updateChildrenContext()
    {
        for (auto& name_ent : objects.map)
        {
            name_ent.second.value->setParentScene(this);
        }
    }
} // namespace Ent
