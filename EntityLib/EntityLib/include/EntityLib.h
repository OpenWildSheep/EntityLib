#pragma once

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include "../Override.h"
#include <vector>
#include <memory>
#include <map>
#include <array>

#include "../../../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#include "../external/filesystem.hpp"

#include "../external/json.hpp" // TODO : Remove when the rawData in Component is no more useful
#pragma warning(pop)

#include "Schema.h"

namespace Ent
{
    // ******************************** Implem details ********************************************

    struct CompStr
    {
        bool operator()(char const* a, char const* b) const
        {
            return strcmp(a, b) < 0;
        }
    };

    struct MemoryProfiler
    {
        std::map<char const*, size_t, CompStr> mem;
        size_t total = 0;
        size_t nodeCount = 0;
        std::map<char const*, size_t, CompStr> nodeByComp;
        std::vector<char const*> currentComp;

        void addMem(char const* name, size_t value)
        {
            mem[name] += value;
            total += value;
        }

        void addNodes(size_t count)
        {
            nodeCount += count;
            nodeByComp[currentComp.back()] += count;
        }
    };

    struct Node;

    /// \cond PRIVATE

    /// Content of a Node which has type Ent::DataType::object
    struct Object
    {
        std::vector<std::pair<char const*, value_ptr<Node>>> nodes;
        Override<Ent::String> instanceOf;

        size_t size() const
        {
            return nodes.size();
        }

        auto front() const
        {
            return nodes.front();
        }
    };

    inline auto begin(Object const& obj)
    {
        return obj.nodes.begin();
    }

    inline auto end(Object const& obj)
    {
        return obj.nodes.end();
    }

    inline auto begin(Object& obj)
    {
        return obj.nodes.begin();
    }

    inline auto end(Object& obj)
    {
        return obj.nodes.end();
    }

    /// Content of a Node which has type Ent::DataType::array
    struct Array
    {
        Array();

        std::vector<value_ptr<Node>> data; ///< List of items of the array

        Override<uint64_t> arraySize; ///< Size of the array, to keep track on array size changes

        bool hasOverride() const;

        bool hasPrefabValue() const;
    };

    enum class ActivationLevel
    {
        Created,
        InWorld,
        Loading,
        Started
    };

    struct Union
    {
        Subschema const* schema = nullptr; ///< The schema of the object containing the oneOf field
        value_ptr<Node> wrapper; ///< Node containing the className/classData
        Ent::Subschema::UnionMeta const* metaData = nullptr;

        bool hasOverride() const; ///< Recursively check if there is an override inside.
        Node* getUnionData(); ///< return the underlying data (The type is given by getUnionType)
        Node const* getUnionData() const; ///< return the underlying data (The type is given by getUnionType)
        char const* getUnionType() const; ///< Get the type inside the union
        /// @brief Change the type inside the union
        /// @pre type match with a type declared inside the json "oneOf"
        Node* setUnionType(char const* _type);

        void computeMemory(MemoryProfiler& prof) const;
    };

    struct EntityRef
    {
        /// @brief string representation of this entity ref, works like a file path, always relative.
        String entityPath;
    };

    /// @brief The possible source of an Override value
    enum class OverrideValueSource
    {
        /// Value is set in this Override. Write the "InstanceOf" field.
        Override,
        /// Value is set in the Prefab or in this Override. Don't write the "InstanceOf" field.
        OverrideOrPrefab,
        /// Value can be any source: Override, Prefab or the default value. Don't write the "InstaneOf" field.
        Any,
    };

    void destroyAndFree(Node* ptr); ///< Internally used by the Node memory Pool
    Pool<Node>& getPool(Node const* ptr); ///< Internally used by the Node memory Pool

    /// \endcond

    // *********************************** Scene/Entity/Component/Node ****************************

    struct Subschema;
    class EntityLib;

    /// Property node. Can contains any type in Ent::DataType
    struct ENTLIB_DLLEXPORT Node
    {
        /// @cond PRIVATE
        using Value = mapbox::util::variant<
            Null,
            Override<String>,
            Override<float>,
            Override<int64_t>,
            Object,
            Array,
            Override<bool>,
            Override<EntityRef>,
            Union>;
        Node() = default;
        Node(Value _val, Subschema const* _schema);

        /// @brief return the node containing the data and the type nodes (An element of the oneOf array)
        /// @pre type==Ent::DataType::oneOf
        /// @remark For internal use
        Node const* getUnionDataWrapper() const;
        /// @endcond

        DataType getDataType() const; ///< Type of this Node. @see Ent::DataType

        // Object
        Node* at(char const* _field); ///< @pre type==Ent::DataType::object @brief Get the _field
        Node const* at(char const* _field) const; ///< @pre type==Ent::DataType::object  @brief Get the _field
        bool count(char const* _field)
            const; ///< @pre type==Ent::DataType::object @brief true if a field with this name exist
        std::vector<char const*>
        getFieldNames() const; ///< @pre type==Ent::DataType::object @brief Get all field names
        char const* getInstanceOf() const; ///< @pre type==Ent::DataType::object @brief path to the tmpl Node

        // Array
        Node* at(size_t _index); ///< @pre type==Ent::DataType::array. @brief Get the item at _index
        Node const* at(size_t _index) const; ///< @pre type==Ent::DataType::array. @brief Get the item at _index
        size_t size() const; ///< @pre type==Ent::DataType::array. @brief Get array size
        /// @pre type==Ent::DataType::array. 
        /// @brief Get the raw Override value of the array size.
        /// @param _location the desired Override value location.
        /// @return the array size at the given Override value location.
        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;
        std::vector<Node const*> getItems() const; ///< @pre type==Ent::DataType::array. @brief Get all items
        Node* push(); ///< @pre type==Ent::DataType::array. @brief Add a new item at the end of array
        void pop(); ///< @pre type==Ent::DataType::array. @brief Remove an item at the end of array
        void clear(); ///< @pre type==Ent::DataType::array. @brief Remove all items in array
        bool empty() const; ///< @pre type==Ent::DataType::array. @brief return true if array is empty

        // Union
        Node* getUnionData(); ///< @pre type==Ent::DataType::oneOf. @brief return the underlying data
        Node const* getUnionData() const; ///< @pre type==Ent::DataType::oneOf. @brief return the underlying data
        /// @brief Get the type inside the union
        /// @pre type==Ent::DataType::oneOf
        char const* getUnionType() const;
        /// @brief Change the type inside the union
        /// @pre type==Ent::DataType::oneOf
        /// @pre type match with a type declared inside the json "oneOf"
        Node* setUnionType(char const* _type);

        // Value
        float getFloat() const; ///< @pre number or integer. @brief Get the value as float
        int64_t getInt() const; ///< @pre integer. @brief Get the value as int
        char const* getString() const; ///< @pre Ent::DataType == string. @brief Get the value as string
        bool getBool() const; ///< @pre type==Ent::DataType::boolean. @brief Get the value as bool
        EntityRef getEntityRef()
            const; ///< @pre type==Ent::DataType::entityRef. @brief Get the value as an Entity reference

        const Value& GetRawValue()
            const; ///< returns a reference to the raw Value (variant) stored at this node. Useful to write visitors.

        void setFloat(float _val); ///< @pre type==Ent::DataType::number. @brief Set the float value
        void setInt(int64_t _val); ///< @pre type==Ent::DataType::integer. @brief Set the int64_t value
        void setString(char const* _val); ///< @pre type==Ent::DataType::string. @brief Set the string value
        void setBool(bool _val); ///< @pre type==Ent::DataType::boolean. @brief Set the bool value
        void setEntityRef(EntityRef _entityRef); ///< @pre type==Ent::DataType::entityRef. @brief Set the Entity reference value

        /// @brief Fallback the the prefab or default value. The value will not be saved in json.
        /// @pre Ent::DataType is in {number, integer, boolean, string}
        void unset();

        /// Check if the value is set explicitly (it override the prefab or default value)
        /// @remark return true when object or array
        bool isSet() const;

        /// @brief Recursively check if there is an override inside.
        ///
        /// If there is no override, there is no need to save it.
        bool hasOverride() const;

        /// @brief Recursively check if value is set in a prefab (overriden or not by this Node)
        bool hasPrefabValue() const;

        /// @brief Check recursively if this node content match the given value source.
        bool matchValueSource(OverrideValueSource _source) const;

        /// \cond PRIVATE
        /// Create a Node with the same value but which doesn't rely on prefab.
        Node detach() const;

        /// Create a Node which is an "instance of" this one. With no override.
        Node makeInstanceOf() const;
        /// \endcond

        /// Reset the Node to be an instance of the given \b _template
        ///
        /// @warning All sub-nodes into \b _node will be invalidated
        /// @param _templateNodePath path to the template Node (relative to RawData)
        void setInstanceOf(char const* _templateNodePath);
        void resetInstanceOf();

        bool hasDefaultValue() const; ///< false if something was set in instance or prefab

        bool isDefault() const; ///< true if the value was set in a template or in the instance

        /// Dump this Node as a json value
        nlohmann::json toJson(
            OverrideValueSource _dumpedValueSource =
                OverrideValueSource::Override, ///< Dump only fields with given value source
            bool _superKeyIsTypeName =
                false, ///< Super sub-node are dumped using their type name for key instead of "Super"
            std::function<void(EntityRef&)> const& _entityRefPreProc = {}) const;

        /// Save as a Node prebab
        void saveNode(std::filesystem::path const& path) const;

        float getDefaultFloat() const; ///< @pre number or integer. @brief Get the default value as float
        int64_t getDefaultInt() const; ///< @pre integer. @brief Get the default value as int
        char const* getDefaultString() const; ///< @pre DataType == string. @brief Get the default value as string
        bool getDefaultBool() const; ///< @pre DataType == bool. @brief Get the default value as bool

        /// @pre number or integer. 
        /// @brief Get the raw Override value as float.
        /// @param _location the desired Override value location.
        /// @return the float value at the given Override value location.
        tl::optional<float> getRawFloat(OverrideValueLocation _location) const;
        /// @pre integer. 
        /// @brief Get the raw Override value as int.
        /// @param _location the desired Override value location.
        /// @return the int value at the given Override value location.
        tl::optional<int> getRawInt(OverrideValueLocation _location) const;
        /// @pre DataType == string. 
        /// @brief Get the raw Override value as string.
        /// @param _location the desired Override value location.
        /// @return the string value at the given Override value location.
        tl::optional<char const*> getRawString(OverrideValueLocation _location) const;
        /// @pre DataType == bool. 
        /// @brief Get the raw Override value as bool.
        /// @param _location the desired Override value location.
        /// @return the bool value at the given Override value location.
        tl::optional<bool> getRawBool(OverrideValueLocation _location) const;

        /// Get the absolute full link of the Subschema type, or nullptr if the is no
        /// Example : "./RuntimeComponents.json#/definitions/VoxelSimulationGD"
        char const* getTypeName() const;

        Subschema const* getSchema() const; ///< Get the Node schema.

        void computeMemory(MemoryProfiler& prof) const;

        EntityLib* getEntityLib() const;

    private:
        Subschema const* schema = nullptr; ///< The Node schema. To avoid to pass it to each call
        Value value; ///< Contains one of the types accepted by a Node

        friend EntityLib;
    };

    /// The properties of a given component
    struct Component
    {
        nlohmann::json rawData;
        std::string type; ///< Component type (ex : Transform, VisualGD, HeightObj ...)
        Node root; ///< Root node of the component. Always of type Ent::DataType::object
        size_t version{}; ///< @todo remove?
        size_t index{}; ///< Useful to keep the componants order in the json file. To make diffs easier.
        DeleteCheck deleteCheck;
        bool hasTemplate{}; ///< True if if override an other component (not just default)

        Component(
            nlohmann::json _rawData,
            bool _hasTemplate,
            std::string _type,
            Node _root,
            size_t _version,
            size_t _index)
            : rawData(_rawData)
            , type(std::move(_type))
            , root(std::move(_root))
            , version(_version)
            , index(_index)
            , hasTemplate(_hasTemplate)
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
    };

    struct Scene;

    /// @brief The properties of a component "SubScene"
    /// @remark "SubScene" need a special case because it contain some Scene, although a Node can't be a Scene.
    ///  There are other solutions to sove this problem like keep everything as a Node and make
    ///  Scene/Component only wrapper to Node. Let's see if the current solution is ok.
    /// @todo : Make all fields private since this struct has some invariants
    struct SubSceneComponent
    {
        bool isEmbedded = false; ///< If true, data are in embedded, else data are in file
        Override<String> file; ///< Path to a .scene file, when isEmbedded is false
        size_t index = 0; ///< Useful to keep the components order in the json file
        std::unique_ptr<Scene> embedded; ///< Embedded Scene, when isEmbedded is true

        void computeMemory(MemoryProfiler& prof) const;

        /// @cond PRIVATE
        explicit SubSceneComponent(
            bool _isEmbedded = false,
            Override<String> _file = {},
            size_t _index = 0,
            std::unique_ptr<Scene> _embedded = {});
        SubSceneComponent(SubSceneComponent const&) = delete;
        SubSceneComponent(SubSceneComponent&&) noexcept = delete;
        SubSceneComponent& operator=(SubSceneComponent const&) = delete;
        SubSceneComponent& operator=(SubSceneComponent&&) noexcept = delete;
        DeleteCheck deleteCheck;
        /// @brief Create a SubSceneComponent which instanciate this one. (internal use only)
        std::unique_ptr<SubSceneComponent> makeInstanceOf() const;
        /// @endcond PRIVATE

        /// Switch SubSceneComponent to embedded mode or to external mode
        void makeEmbedded(bool _embedded ///< false to make extern (not embedded)
        );

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const;

        std::unique_ptr<SubSceneComponent> clone() const; ///< Clone this SubSceneComponent identically

        /// @brief detach the Scene from this sub scene components, leaving the embedded sub scene empty
        /// @pre this SubScene is embedded, i.e. isEmbedded is true
        std::unique_ptr<Scene> detachEmbedded();
    };

    class EntityLib;

    /// Contains all data of an Entity. (Name, Color, Conponent ...)
    struct ENTLIB_DLLEXPORT Entity
    {
        /// @cond PRIVATE
        Entity(EntityLib const& _entlib);
        Entity(
            EntityLib const& _entlib,
            Override<String> _name,
            std::map<std::string, Component> _components,
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
        /// @endcond

        char const* getName() const; ///< Get the name of the component
        void setName(Ent::String _name); ///< Set the name of the component
        bool canBeRenamed() const; ///< A SubEntity of an instance which override a SubEntity in a prefab can't be renamed
        char const* getInstanceOf() const; ///< Name of the inherited prefab if there is one, or nullptr.
        /// Get the initial max activation level of the entity at runtime.
        ActivationLevel getMaxActivationLevel() const;
        /// Set the initial max activation level of the entity at runtime.
        void setMaxActivationLevel(ActivationLevel _level);
        char const* getThumbnail() const; ///< Get the Thumbnail path, or nullptr.
        void setThumbnail(Ent::String _thumbPath); ///< Set the Thumbnail path
        std::array<float, 4> getColor() const; ///< Get the color of the is one, or nullptr.
        void setColor(std::array<float, 4> _color); ///< Set the color RGBA 8bit

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

        /// @brief Make the Entity independent from its prefab (instanceOf)
        ///
        /// All properties overrided in _entity OR in the prefeb become overrided in the Entity.
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

        /// Reset the Entity to be an instance of the given \b _template
        ///
        /// @warning All Nodes into the Entity will be invalidated
        void setInstanceOf(std::string _template);

    private:
        void updateSubSceneOwner();
        EntityLib const* entlib{}; ///< Reference the entity lib to find the schema when needed
        Override<String> name; ///< Entity name
        std::map<std::string, Component> components; ///< All components of this Entity
        std::unique_ptr<SubSceneComponent> subSceneComponent; ///< the optional SubScene Component
        Node actorStates; ///< All actorStates of this Entity
        Node color; ///< The optional Color of the Entity
        Override<String> thumbnail; ///< Path to the thumbnail mesh (.wthumb)
        Override<String> instanceOf; ///< Path to the prefab if this is the instanciation of an other entity
        Override<ActivationLevel> maxActivationLevel; ///< Maximum activation level of this entity in runtime
        bool hasASuper = false;
        Scene* parentScene = nullptr; ///< ptr the scene containing this entity.
    };

    /// Contain all data of a scene. (A list of Entity)
    struct Scene
    {
        /// Construct an empty Scene
        Scene();
        /// Construct a scene taking the ownership of a list of \p _entities
        Scene(std::vector<std::unique_ptr<Entity>> _entities);

        /// @cond PRIVATE
        Scene(Scene const&) = delete;
        Scene& operator=(Scene const&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(Scene&&) = delete;

        DeleteCheck deleteCheck; // Just for debug
        /// @endcond

        /// Add a new entity in the scene and take its ownership
        void addEntity(std::unique_ptr<Entity>&& _entity);

        /// Get all entities in the scene
        std::vector<std::unique_ptr<Entity>> const& getObjects() const;

        /// Get the nth entity
        Entity const* getEntity(size_t index) const;

        /// Get the nth entity
        Entity* getEntity(size_t index);

        /// Number of entity in the scene
        size_t entityCount() const;

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
            prof.addMem("Scene::objects", objects.capacity() * sizeof(objects.front()));
            for (auto&& entityPtr : objects)
                entityPtr->computeMemory(prof);
        }

    private:
        Entity* ownerEntity = nullptr; ///< the entity owning this scene if it is embedded
        void updateChildrenContext();
        std::vector<std::unique_ptr<Entity>> objects; ///< All Ent::Entity of this Scene
    };

    // ********************************** Static data *********************************************

    /// Definition of all components
    struct ComponentsSchema
    {
        ComponentsSchema() = default;
        ComponentsSchema(ComponentsSchema const&) = delete;
        ComponentsSchema& operator=(ComponentsSchema const&) = delete;
        std::map<std::string, Subschema*> components; ///< Schema of all possible Component s
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

        /// Load the Entity at path _entityPath
        std::unique_ptr<Entity> loadEntity(
            std::filesystem::path const& _entityPath, Ent::Entity const* _super = nullptr) const;

        /// Load the Scene at path _scenePath
        std::unique_ptr<Scene> loadScene(std::filesystem::path const& _scenePath) const;

        /// Load the Scene in legacy format at path _scenePath
        std::unique_ptr<Scene> loadLegacyScene(std::filesystem::path const& _scenePath) const;

        /// Save the Entity at path _entityPath
        void saveEntity(Entity const& _entity, std::filesystem::path const& _entityPath) const;

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
            std::function<void(EntityRef&)> const& _entityRefPreProc = {});

        /// @brief Create an Entity which instanciate an other.
        ///
        /// This allow to override some properties without change the prefab properties.
        std::unique_ptr<Entity> makeInstanceOf(std::string _instanceOf ///< Path to the prefab Entity
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
    template <typename V>
    V const& Override<V>::get() const
    {
        if (hasOverride)
        {
            return overrideValue;
        }
        if (hasPrefab)
        {
            return prefabValue;
        }
        return defaultValue;
    }

    template <typename V>
    void Override<V>::set(V _newVal)
    {
        overrideValue = std::move(_newVal);
        hasOverride = true;
    }

    template <typename V>
    bool Override<V>::isSet() const
    {
        return hasOverride;
    }

    template <typename V>
    void Override<V>::unset()
    {
        hasOverride = false;
        overrideValue = {};
    }

    template <typename V>
    Override<V> Override<V>::detach() const
    {
        if (hasOverride)
            return Override<V>(defaultValue, V{}, overrideValue, false, hasOverride);
        else
            return Override<V>(defaultValue, V{}, prefabValue, false, hasPrefab);
    }

    template <typename V>
    Override<V> Override<V>::makeInstanceOf() const
    {
        if (hasOverride)
            return Override<V>(defaultValue, overrideValue, V{}, hasOverride, false);
        else
            return Override<V>(defaultValue, prefabValue, V{}, hasPrefab, false);
    }

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
        compute(defaultValue);
        if (hasPrefab)
            compute(prefabValue);
        if (hasOverride)
            compute(overrideValue);
    }

    size_t count(Object const& obj, char const* key);
    void emplace(Object& obj, std::pair<char const*, Node> const& value);
    Node const& at(Object const& obj, char const* key);
    Node& at(Object& obj, char const* key);

    /// \endcond

} // namespace Ent
