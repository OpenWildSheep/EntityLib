#pragma once

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <array>
// #include <ciso646>

#include "../../../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#include "../external/filesystem.hpp"

#include "../external/json.hpp" // TODO : Remove when the rawData in Component is no more useful
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Override.h"
#include "../RemovableMap.h"
#include "../Array.h"
#include "../MemoryProfiler.h"
#include "../Union.h"
#include "../Object.h"
#include "../Node.h"
#pragma warning(pop)

#include "Schema.h"

namespace Ent
{
    // ******************************** Implem details ********************************************

    struct Node;

    enum class ActivationLevel
    {
        Created,
        InWorld,
        Loading,
        Started
    };

    // *********************************** Scene/Entity/Component ****************************

    /// The properties of a given component
    struct Component
    {
        nlohmann::json rawData;
        std::string type; ///< Component type (ex : Transform, VisualGD, HeightObj ...)
        Node root; ///< Root node of the component. Always of type Ent::DataType::object
        size_t version{}; ///< @todo remove?
        size_t index{}; ///< Useful to keep the componants order in the json file. To make diffs easier.
        DeleteCheck deleteCheck;
        bool hasPrefab{}; ///< True if it overrides an other component (not just default)

        Component(
            nlohmann::json _rawData,
            bool _hasPrefab,
            std::string _type,
            Node _root,
            size_t _version,
            size_t _index)
            : rawData(_rawData)
            , type(std::move(_type))
            , root(std::move(_root))
            , version(_version)
            , index(_index)
            , hasPrefab(_hasPrefab)
        {
        }

        /// \cond PRIVATE
        void computeMemory(MemoryProfiler& prof) const
        {
            prof.currentComp.push_back(type.c_str());
            prof.addMem("Component::type", type.size());
            root.computeMemory(prof);
            prof.currentComp.pop_back();
        }

        /// Create a Component which is an "instance of" this one. With no override.
        Component makeInstanceOf() const
        {
            return Component{rawData, true, type, root.makeInstanceOf(), version, index};
        }
        /// \endcond

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const
        {
            return root.hasOverride();
        }
        /// @brief Recursively check if values are at default value.
        bool hasDefaultValue() const
        {
            return root.hasDefaultValue();
        }
        /// Is this component used in runtime engine ?
        bool isUsedInRuntime() const
        {
            return root.getSchema() && root.getSchema()->IsUsedInRuntime();
        }
        /// Is this component used in editors ?
        bool isUsedInEditor() const
        {
            return root.getSchema() && root.getSchema()->IsEditorOnly();
        }

        /// @brief Take all values set in this and set them into \b _dest
        /// @pre \b _dest has the same component type than \b this
        void applyAllValues(Component& _dest, CopyMode _copyMode) const
        {
            ENTLIB_ASSERT(type == _dest.type);
            root.applyAllValues(_dest.root, _copyMode);
        }
    };

    struct Scene;

    /// @brief The properties of a component "SubScene"
    /// @remark "SubScene" need a special case because it contain some Scene, although a Node can't be a Scene.
    ///  There are other solutions to sove this problem like keep everything as a Node and make
    ///  Scene/Component only wrapper to Node. Let's see if the current solution is ok.
    /// @todo : Make all fields private since this struct has some invariants
    struct SubSceneComponent
    {
        size_t index = 0; ///< Useful to keep the components order in the json file
        std::unique_ptr<Scene> embedded; ///< Embedded Scene, when isEmbedded is true

        void computeMemory(MemoryProfiler& prof) const;

        /// @cond PRIVATE
        explicit SubSceneComponent(
            EntityLib const* _entlib, size_t _index = 0, std::unique_ptr<Scene> _embedded = {});
        SubSceneComponent(SubSceneComponent const&) = delete;
        SubSceneComponent(SubSceneComponent&&) noexcept = delete;
        SubSceneComponent& operator=(SubSceneComponent const&) = delete;
        SubSceneComponent& operator=(SubSceneComponent&&) noexcept = delete;
        DeleteCheck deleteCheck;
        /// @brief Create a SubSceneComponent which instanciate this one. (internal use only)
        std::unique_ptr<SubSceneComponent> makeInstanceOf() const;
        /// @endcond PRIVATE

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const;

        std::unique_ptr<SubSceneComponent> clone() const; ///< Clone this SubSceneComponent identically

        /// @brief detach the Scene from this sub scene components, leaving the embedded sub scene empty
        /// @pre this SubScene is embedded, i.e. isEmbedded is true
        std::unique_ptr<Scene> detachEmbedded();

        /// @brief Take all values set in this and set them into \b _dest
        void applyAllValues(SubSceneComponent& _dest, CopyMode _copyMode) const;
    };

    class EntityLib;

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

        void computeMemory(MemoryProfiler& prof) const
        {
            name.computeMemory(prof);
            for (auto&& name_comp : components)
            {
                prof.addMem("Entity::components::value", sizeof(name_comp));
                prof.addMem("Entity::components::key", sizeof(std::get<0>(name_comp).size()));
                std::get<1>(name_comp).computeMemory(prof);
            }
            if (subSceneComponent)
                subSceneComponent->computeMemory(prof);
            actorStates.computeMemory(prof);
            color.computeMemory(prof);
            thumbnail.computeMemory(prof);
            instanceOf.computeMemory(prof);
            maxActivationLevel.computeMemory(prof);
        }

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

        void computeMemory(MemoryProfiler& prof) const
        {
            objects.computeMemory(prof);
        }

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

    // ********************************** Static data *********************************************

    /// Definition of all components
    struct ComponentsSchema
    {
        ComponentsSchema() = default;
        ComponentsSchema(ComponentsSchema const&) = delete;
        ComponentsSchema& operator=(ComponentsSchema const&) = delete;
        std::map<std::string, Subschema*> components; ///< Schema of all possible Components
        std::map<std::string, Subschema*> actorstates; ///< Schema of all possible Actorstates
        Schema schema; ///< Schemas of everything (object, enum...)

        /// @cond PRIVATE
        DeleteCheck deleteCheck; // Just for debug
        /// @endcond
    };

    /// Entry point of the EntityLib. Used to load/save Scene/Entity and to parse the Schema
    class ENTLIB_DLLEXPORT EntityLib
    {
    public:
        Pool<Node> nodePool;
        /// @todo Make public attribute private?
        std::filesystem::path rootPath; ///< Path to the perforce root (X:/)
        std::filesystem::path rawdataPath; ///< Path to the RawData dir in the perforce root (X:/RawData)
        std::filesystem::path toolsDir; ///< Path to the Tools dir in in the perforce root (X:/Tools)
        ComponentsSchema schema; ///< Schema of all components
        bool validationEnabled = false; ///< validate all objects at load/save

        /// Component needed for each type of components
        std::map<std::string, std::vector<std::string>> componentDependencies;

        /// Load the EntityLib, given the path to the Tools directory
        explicit EntityLib(std::filesystem::path _rootPath, bool _doMergeComponents = false);
        ~EntityLib();
        /// @cond PRIVATE
        EntityLib(EntityLib const&) = delete;
        EntityLib& operator=(EntityLib const&) = delete;
        DeleteCheck deleteCheck;
        /// @endcond

        /// Load the Entity at path _entityPath then return a pointer to the cached data
        std::shared_ptr<Entity const> loadEntityReadOnly(
            std::filesystem::path const& _entityPath, Ent::Entity const* _super = nullptr) const;

        /// Load the Scene at path _scenePath then return a pointer to the cached data
        std::shared_ptr<Scene const> loadSceneReadOnly(std::filesystem::path const& _scenePath) const;

        /// Load the Scene in legacy format at path _scenePath then return a pointer to the cached data
        std::shared_ptr<Scene const>
        loadLegacySceneReadOnly(std::filesystem::path const& _scenePath) const;

        /// Load an entity file into a Node
        Node loadEntityAsNode(std::filesystem::path const& _entityPath) const;

        /// Load any entitylib file into a Node, giving a schema
        Node loadFileAsNode(std::filesystem::path const& _path, Ent::Subschema const& _schema) const;

        /// Load the Entity at path _entityPath
        std::unique_ptr<Entity> loadEntity(
            std::filesystem::path const& _entityPath, Ent::Entity const* _super = nullptr) const;

        /// Load the Scene at path _scenePath
        std::unique_ptr<Scene> loadScene(std::filesystem::path const& _scenePath) const;

        /// Load the Scene in legacy format at path _scenePath
        std::unique_ptr<Scene> loadLegacyScene(std::filesystem::path const& _scenePath) const;

        /// Save the Entity at path _entityPath
        void saveEntity(Entity const& _entity, std::filesystem::path const& _relEntityPath) const;

        /// Save the Scene at path _scenePath
        void saveScene(Scene const& _scene, std::filesystem::path const& _scenePath) const;

        /// Dump the given Node with the given schema in json format
        static nlohmann::json dumpNode(
            Subschema const& _schema, ///< Schema for the Node
            Node const& _node, ///< the Node to dump
            OverrideValueSource _dumpedValueSource =
                OverrideValueSource::Override, ///< Dump only fields with given value source
            bool _superKeyIsTypeName =
                false, ///< Super sub-node are dumped using their type name for key instead of "Super"
            std::function<void(EntityRef&)> const& _entityRefPreProc = {},
            bool _saveUnionIndex = false);

        /// @brief Create an Entity which instanciate an other.
        ///
        /// This allow to override some properties without change the prefab properties.
        std::unique_ptr<Entity> makeInstanceOf(std::string const& _instanceOf ///< Path to the prefab Entity
        ) const;

        struct EntityFile
        {
            std::shared_ptr<Entity> data;
            std::filesystem::file_time_type time;
        };
        struct SceneFile
        {
            std::shared_ptr<Scene> data;
            std::filesystem::file_time_type time;
        };
        std::map<std::filesystem::path, EntityFile> const& getEntityCache() const;
        std::map<std::filesystem::path, SceneFile> const& getSceneCache() const;

        void clearCache();

        std::filesystem::path getAbsolutePath(std::filesystem::path const& _path) const;
        /// @param _path : A file path absolute or relative but inside the rawdata path
        std::filesystem::path getRelativePath(std::filesystem::path const& _path) const;

        Ent::Node loadNode(
            Ent::Subschema const& _nodeSchema,
            nlohmann::json const& _data,
            Ent::Node const* _super,
            nlohmann::json const* _default = nullptr) const;

    private:
        /// Load an Entity or a Scene, using the given cache
        template <typename Type, typename Cache, typename ValidateFunc, typename LoadFunc>
        std::shared_ptr<Type const> loadEntityOrScene(
            std::filesystem::path const& _path,
            Cache& cache,
            ValidateFunc&& validate,
            LoadFunc&& load,
            Type const* _super) const;

        mutable std::map<std::filesystem::path, EntityFile> m_entityCache;
        mutable std::map<std::filesystem::path, SceneFile> m_sceneCache;
    };

    // *************************** Implem details - method bodies *********************************

    /// \cond PRIVATE
    struct Memory
    {
        MemoryProfiler* prof;

        template <typename T>
        void operator()(T) const
        {
        }

        void operator()(std::string const& str) const
        {
            prof->addMem("Override<string>", str.capacity());
        }
    };

    template <typename V>
    void Override<V>::computeMemory(MemoryProfiler& prof) const
    {
        Memory compute{&prof};
        compute(m_defaultValue);
        if (hasPrefabValue())
            compute(m_prefabValue);
        if (hasOverride())
            compute(m_overrideValue);
    }

    /// \endcond

} // namespace Ent
