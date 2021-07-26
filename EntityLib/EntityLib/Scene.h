#pragma once

#pragma warning(push)
#pragma warning(disable : 4464)
#include "RemovableMap.h"
#include "Entity.h"
#pragma warning(pop)

#include "include/Schema.h"

namespace Ent
{
    struct Node;
    struct Entity;

    /// Contain all data of a scene. (A list of Entity)
    struct Scene
    {
        /// Construct an empty Scene
        Scene(EntityLib const* _entitylib);

        using EntityMap = RemovableMap<String, Entity>;
        /// Construct a scene taking the ownership of a list of \p _entities
        Scene(EntityMap _entities);

        /// @cond PRIVATE
        Scene(Scene const&) = delete;
        Scene& operator=(Scene const&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(Scene&&) = delete;

        DeleteCheck deleteCheck; // Just for debug
        /// @endcond

        /// Add a new entity in the scene and take its ownership
        Entity* addEntity(std::unique_ptr<Entity>&& _entity);

        Entity* addEntity(char const* name);

        /// Get all entities in the scene
        std::vector<Entity*> getObjects() const;

        /// Get the nth entity
        Entity const* getEntity(size_t index) const;

        /// Get the nth entity
        Entity* getEntity(size_t index);

        /// Get the entity named \b _name
        Entity const* getEntity(char const* _name) const;

        /// Get the entity named \b _name
        Entity* getEntity(char const* _name);

        /// Number of entity in the scene
        size_t entityCount() const;

        /// @brief Erase an Entity with the given \b _name
        /// @return true if the Entity was found
        void removeEntity(char const*);

        void renameEntity(char const* _currentName, char const* _newName);

        /// Abandons ownership of all entities and return them.
        std::vector<std::unique_ptr<Entity>> releaseAllEntities();

        /// @brief Resolve an EntityRef relative to this scene.
        /// Returns nullptr in case of failure.
        Entity* resolveEntityRef(const EntityRef& _entityRef);

        /// @brief Find an entity in the scene hierarchy given its path
        Entity* findEntityByPath(const std::string& _path);

        /// Create a new scene which if the "instance of" this one
        std::unique_ptr<Scene> makeInstanceOf() const;

        /// Clone this scene identically. (No instance of)
        std::unique_ptr<Scene> clone() const;

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const;

        /// @brief Get the entity owning this scene if it is embedded.
        Entity* getOwnerEntity() const;

        /// @brief Set the entity owning this scene if it is embedded.
        void setOwnerEntity(Entity* _entity);

        void computeMemory(MemoryProfiler& prof) const;

        /// @brief Take all values set in this and set them into \b _dest
        void applyAllValues(Scene& _dest, CopyMode _copyMode) const;

        nlohmann::json saveScene() const;

        static std::unique_ptr<Ent::Scene> loadScene(
            Ent::EntityLib const& _entLib, nlohmann::json const& _entities, Ent::Scene const* _super);

        EntityLib const* getEntityLib() const
        {
            return entlib;
        };

    private:
        void updateChildrenContext();
        EntityLib const* entlib = nullptr;
        Entity* ownerEntity = nullptr; ///< the entity owning this scene if it is embedded
        EntityMap objects;
    };

} // namespace Ent
