#pragma once

#include <map>
#include <set>
#include "Override.h"
#include "Component.h"
#include "SubSceneComponent.h"
#include "include/EntityLibCore.h"

namespace Ent
{
    enum class ActivationLevel
    {
        Created,
        InWorld,
        Loading,
        Started
    };

    struct Scene;
    class EntityLib;
    struct SubSceneComponent;
    struct Node;

    /// Contains all data of an Entity. (Name, Color, Conponent ...)
    struct ENTLIB_DLLEXPORT Entity
    {
        /// @cond PRIVATE
        Entity(EntityLib const& _entlib, char const* name);
        Entity(
            EntityLib const& _entlib,
            Override<String> _name,
            std::map<std::string, Component> _components,
            std::set<std::string> _removedComponents,
            std::unique_ptr<SubSceneComponent> _subSceneComponent,
            Node _actorStates = {},
            Node _color = {},
            Override<String> _thumbnail = {},
            Override<String> _instanceOf = {},
            Override<ActivationLevel> _maxActivationLevel = {},
            bool _hasASuper = false);
        Entity(Entity const&) = delete;
        Entity& operator=(Entity const&) = delete;
        Entity(Entity&&) = delete;
        Entity& operator=(Entity&&) = delete;
        DeleteCheck deleteCheck;
        void setCanBeRenamed(bool _can); ///< If it has a super it can't be renamed

        Override<String> const& getNameValue() const
        {
            return name;
        }

        Node const& getColorValue() const
        {
            return color;
        }

        Override<String> const& getThumbnailValue() const
        {
            return thumbnail;
        }

        Override<String> const& getInstanceOfValue() const
        {
            return instanceOf;
        }

        Override<ActivationLevel> const& getMaxActivationLevelValue() const
        {
            return maxActivationLevel;
        }

        // Set name and do not inform the parent Scene. (Called by the parent Scene)
        void _setNameRaw(char const* _name);
        /// @endcond

        char const* getName() const; ///< Get the name of the component
        void setName(Ent::String _name); ///< Set the name of the component
        bool canBeRenamed() const; ///< A SubEntity of an instance which override a SubEntity in a prefab can't be renamed
        bool newInTheScene() const; ///< This entity is new in this scene (But it can have an "InstanceOf")
        char const* getInstanceOf() const; ///< Name of the inherited prefab if there is one, or nullptr.
        /// Get the initial max activation level of the entity at runtime.
        ActivationLevel getMaxActivationLevel() const;
        /// Set the initial max activation level of the entity at runtime.
        void setMaxActivationLevel(ActivationLevel _level);
        char const* getThumbnail() const; ///< Get the Thumbnail path, or nullptr.
        void setThumbnail(Ent::String _thumbPath); ///< Set the Thumbnail path
        std::array<double, 4> getColor() const; ///< Get the color of the is one, or nullptr.
        void setColor(std::array<double, 4> _color); ///< Set the color RGBA 8bit

        /// @brief Create a component of the given _type, with the default values
        /// @pre A component of this _type doesn't exist yet
        /// @pre _type match with a type of component described in the schema
        Component* addComponent(char const* _type);
        /// Get the component of the given _type, or nullptr
        Component const* getComponent(char const* _type) const;
        /// Get the component of the given _type, or nullptr
        Component* getComponent(char const* _type);
        /// @brief Remove the component of the given _type
        /// @pre A component of this _type exists
        void removeComponent(char const* _type);
        /// Get the list of all component types inside this Entity
        std::vector<char const*> getComponentTypes() const;
        /// Get an dictionary with all component where the key is the type, and the value a Component
        std::map<std::string, Component> const& getComponents() const;
        /// Get the special component SubScene or nullptr
        SubSceneComponent const* getSubSceneComponent() const;
        /// Get the special component SubScene or nullptr
        SubSceneComponent* getSubSceneComponent();
        /// Remove the special component SubScene
        void removeSubSceneComponent();

        /// Add the special component SubScene
        ///
        /// @remark Do nothing if already exist, and return the existing one
        SubSceneComponent* addSubSceneComponent();

        Node const& getActorStates() const
        {
            return actorStates;
        }
        Node& getActorStates()
        {
            return actorStates;
        }

        /// @brief Make the Entity independent from its prefab (instanceOf)
        ///
        /// All properties overrided in _entity OR in the prefab become overrided in the Entity.
        /// The prefab is no more referenced.
        /// The properties keep the sames values
        std::unique_ptr<Entity> detachEntityFromPrefab() const;

        /// @brief Create an Entity which instanciate this one.
        std::unique_ptr<Entity> makeInstanceOf() const;

        /// Clone this Entity identically. (No instance of)
        std::unique_ptr<Entity> clone() const;

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const;

        /// @brief Create a relative EntityRef to the given entity
        /// that will resolve to it from this entity.
        EntityRef makeEntityRef(Entity& _entity);

        /// @brief Resolve an EntityRef relative to this entity.
        /// Returns nullptr in case of failure.
        Entity* resolveEntityRef(const EntityRef& _entityRef);

        /// @brief Resolve an EntityRef relative to this entity.
        /// Returns nullptr in case of failure.
        Entity const* resolveEntityRef(const EntityRef& _entityRef) const;

        /// @brief Get the parent scene object containing this entity, if any.
        Scene* getParentScene() const;

        /// @brief Set the parent scene object containing this entity.
        void setParentScene(Scene* _scene);

        void computeMemory(MemoryProfiler& prof) const;

        /// @remark obsolete. Use resetInstanceOf
        void setInstanceOf(std::string const& _prefab);
        /// Reset the Entity to be an instance of the given \b _prefab
        ///
        /// @warning All Nodes into the Entity will be invalidated
        void resetInstanceOf(char const* _prefab);

        /// @brief Change this Entity to be an instance of the given \b _newPrefab, keeping
        /// all internal values the same.
        /// A detached version of the entity will be identical before and after a call to this method.
        /// @param _newPrefab the new prefab path
        void changeInstanceOf(char const* _newPrefab);

        nlohmann::json saveEntity() const;

        /// Take all values set in \b this, set them into the prefab entity, and save the prefab
        void applyToPrefab();

        /// @brief Take all values set in this and set them into \b _dest
        void applyAllValues(Entity& _dest, CopyMode _copyMode) const;

        /// @brief Take all values set in this and set them into \b _dest
        ///   BUT do not change the prefab of _dest
        void applyAllValuesButPrefab(Entity& _dest, CopyMode _copyMode) const;

    private:
        void updateSubSceneOwner();
        EntityLib const* entlib{}; ///< Reference the entity lib to find the schema when needed
        Override<String> name; ///< Entity name
        std::map<std::string, Component> components; ///< All components of this Entity
        std::set<std::string> removedComponents;
        std::unique_ptr<SubSceneComponent> subSceneComponent; ///< the optional SubScene Component
        Node actorStates; ///< All actorStates of this Entity
        Node color; ///< The optional Color of the Entity
        Override<String> thumbnail; ///< Path to the thumbnail mesh (.wthumb)
        Override<String> instanceOf; ///< Path to the prefab if this is the instanciation of an other entity
        Override<ActivationLevel> maxActivationLevel; ///< Maximum activation level of this entity in runtime
        bool hasASuper = false;
        Scene* parentScene = nullptr; ///< ptr the scene containing this entity.
        size_t index = 0; ///< Keep the order when saving
    };

    Entity* resolveEntityRefRecursive(
        Entity* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path);

    Entity const* resolveEntityRefRecursive(
        Entity const* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path);

} // namespace Ent
