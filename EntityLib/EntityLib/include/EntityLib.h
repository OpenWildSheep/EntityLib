#pragma once

#pragma warning(push, 0)
#include <vector>
#include <memory>
#include <map>
#include <array>

#include "../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#include "../external/filesystem.hpp"

#define nsvp_CONFIG_COMPARE_POINTERS 1
#include "../external/value_ptr.hpp"
#pragma warning(pop)

#include "Schema.h"

namespace Ent
{
    using nonstd::value_ptr;

    // ******************************** Implem details ********************************************

    struct Node;

    /// \cond PRIVATE

    /// Content of a Node which has type Ent::DataType::object
    using Object = std::map<std::string, value_ptr<Node>>;

    /// Content of a Node which has type Ent::DataType::array
    struct Array
    {
        std::vector<value_ptr<Node>> data; ///< List of items of the array
        DeleteCheck deleteCheck;

        bool hasOverride() const;
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
        std::string classNameField; ///< Name of the field containing the type under union
        std::string classDatafield; ///< Name of the field containing the data under union

        bool hasOverride() const; ///< Recursively check if there is an override inside.
        Node* getUnionData(); ///< return the underlying data (The type is given by getUnionType)
        Node const* getUnionData() const; ///< return the underlying data (The type is given by getUnionType)
        char const* getUnionType() const; ///< Get the type inside the union
        /// @brief Change the type inside the union
        /// @pre type match with a type declared inside the json "oneOf"
        Node* setUnionType(char const* _type);
    };

    struct EntityRef
    {
        /// @brief string representation of this entity ref, works like a file path, always relative.
        std::string entityPath;
    };

    template <typename V>
    struct Override
    {
        Override() = default;
        Override(V _defaultValue, tl::optional<V> _prefabValue, tl::optional<V> _overrideValue)
            : defaultValue(std::move(_defaultValue))
            , prefabValue(std::move(_prefabValue))
            , overrideValue(std::move(_overrideValue))
        {
        }
        Override(V _defaultVal, V _val)
            : defaultValue(_defaultVal)
            , value(_val)
        {
        }

        V const& get() const;

        void set(V _newVal);

        bool isSet() const;

        void unset();

        Override<V> detach() const;

        Override<V> makeInstanceOf() const;

        /// makeInstanceOf, then set a value
        Override<V> makeOverridedInstanceOf(tl::optional<V> _overrideValue) const
        {
            Override<V> result = makeInstanceOf();
            result.overrideValue = _overrideValue;
            return result;
        }

        /// True if no value was set in template or in instance
        bool isDefault() const
        {
            return !(prefabValue.has_value() || overrideValue.has_value());
        }

        // bool hasOverride() const;

    public:
        V defaultValue = V();
        tl::optional<V> prefabValue;
        tl::optional<V> overrideValue;
        DeleteCheck deleteCheck;
    };

    /// \endcond

    // *********************************** Scene/Entity/Component/Node ****************************

    struct Subschema;

    /// Property node. Can contains any type in Ent::DataType
    struct ENTLIB_DLLEXPORT Node
    {
        /// @cond PRIVATE
        using Value = mapbox::util::variant<
            Null,
            Override<std::string>,
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

        // Array
        Node* at(size_t _index); ///< @pre type==Ent::DataType::array. @brief Get the item at _index
        Node const* at(size_t _index) const; ///< @pre type==Ent::DataType::array. @brief Get the item at _index
        size_t size() const; ///< @pre type==Ent::DataType::array. @brief Get array size
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

        /// \cond PRIVATE
        /// Create a Node with the same value but which doesn't rely on prefab.
        Node detach() const;

        /// Create a Node which is an "instance of" this one. With no override.
        Node makeInstanceOf() const;
        /// \endcond

        bool hasDefaultValue() const; ///< false if something was set in instance or prefab

        bool isDefault() const; ///< true if the value was set in a template or in the instance

        float getDefaultFloat() const; ///< @pre number or integer. @brief Get the default value as float
        int64_t getDefaultInt() const; ///< @pre integer. @brief Get the default value as int
        char const* getDefaultString() const; ///< @pre DataType == string. @brief Get the default value as string
        bool getDefaultBool() const; ///< @pre DataType == bool. @brief Get the default value as bool

        /// Get the absolute full link of the Subschema type, or nullptr if the is no
        /// Example : "file://RuntimeComponents.json#/definitions/VoxelSimulationGD"
        char const* getTypeName() const;

        Subschema const* getSchema() const; ///< Get the Node schema.

    private:
        Subschema const* schema = nullptr; ///< The Node schema. To avoid to pass it to each call
        Value value; ///< Contains one of the types accepted by a Node
        DeleteCheck deleteCheck;
    };

    /// The properties of a given component
    struct Component
    {
        bool hasTemplate; ///< True if if override an other component (not just default)
        std::string type; ///< Component type (ex : Transform, VisualGD, HeightObj ...)
        Node root; ///< Root node of the component. Always of type Ent::DataType::object
        size_t version; ///< @todo remove?
        size_t index; ///< Useful to keep the componants order in the json file. To make diffs easier.

        /// \cond PRIVATE
        DeleteCheck deleteCheck;

        /// Create a Component which is an "instance of" this one. With no override.
        Component makeInstanceOf() const
        {
            return Component{ true, type, root.makeInstanceOf(), version, index };
        }
        /// \endcond

        /// @brief Recursively check if there is an override inside.
        bool hasOverride() const
        {
            return root.hasOverride();
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
        Override<std::string> file; ///< Path to a .scene file, whene isEmbedded is false
        size_t index = 0; ///< Useful to keep the componants order in the json file
        std::unique_ptr<Scene> embedded; ///< Embedded Scene, whene isEmbedded is true

        /// @cond PRIVATE
        explicit SubSceneComponent(
            bool _isEmbedded = false,
            Override<std::string> _file = {},
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
    };

    class EntityLib;

    /// Contains all data of an Entity. (Name, Color, Conponent ...)
    struct ENTLIB_DLLEXPORT Entity
    {
        /// @cond PRIVATE
        Entity(EntityLib const& _entlib);
        Entity(
            EntityLib const& _entlib,
            Override<std::string> _name,
            std::map<std::string, Component> _components,
            std::unique_ptr<SubSceneComponent> _subSceneComponent,
            Node _color = {},
            Override<std::string> _thumbnail = {},
            Override<std::string> _instanceOf = {},
            Override<ActivationLevel> _maxActivationLevel = {},
            bool _hasASuper = false);
        Entity(Entity const&) = delete;
        Entity& operator=(Entity const&) = delete;
        Entity(Entity&&) = delete;
        Entity& operator=(Entity&&) = delete;
        DeleteCheck deleteCheck;
        void setCanBeRenamed(bool _can); ///< If it has a super it can't be renamed

        Override<std::string> const& getNameValue() const
        {
            return name;
        }

        Node const& getColorValue() const
        {
            return color;
        }

        Override<std::string> const& getThumbnailValue() const
        {
            return thumbnail;
        }

        Override<std::string> const& getInstanceOfValue() const
        {
            return instanceOf;
        }

        Override<ActivationLevel> const& getMaxActivationLevelValue() const
        {
            return maxActivationLevel;
        }
        /// @endcond

        char const* getName() const; ///< Get the name of the component
        void setName(std::string _name); ///< Set the name of the component
        bool canBeRenamed() const; ///< A SubEntity of an instance which override a SubEntity in a prefab can't be renamed
        char const* getInstanceOf() const; ///< Name of the inherited prefab if there is one, or nullptr.
        /// Get the initial max activation level of the entity at runtime.
        ActivationLevel getMaxActivationLevel() const;
        /// Set the initial max activation level of the entity at runtime.
        void setMaxActivationLevel(ActivationLevel _level);
        char const* getThumbnail() const; ///< Get the Thumbnail path, or nullptr.
        void setThumbnail(std::string _thumbPath); ///< Set the Thumbnail path
        std::array<uint8_t, 4> getColor() const; ///< Get the color of the is one, or nullptr.
        void setColor(std::array<uint8_t, 4> _color); ///< Set the color RGBA 8bit

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

        /// @brief Get the parent scene object containing this entity, if any.
        Scene* getParentScene() const;

        /// @brief Set the parent scene object containing this entity.
        void setParentScene(Scene* _scene);

    private:
        void updateSubSceneOwner();
        EntityLib const* entlib{}; ///< Reference the entity lib to find the schema when needed
        Override<std::string> name; ///< Entity name
        std::map<std::string, Component> components; ///< All components of this Entity
        std::unique_ptr<SubSceneComponent> subSceneComponent; ///< the optional SubScene Component
        Node color; ///< The optional Color of the Entity
        Override<std::string> thumbnail; ///< Path to the thumbnail mesh (.wthumb)
        Override<std::string> instanceOf; ///< Path to the prefab if this is the instanciation of an other entity
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
        /// @todo Make public attribute private?
        std::filesystem::path rootPath; ///< Path to the perforce root (X:/)
        std::filesystem::path rawdataPath; ///< Path to the RawData dir in the perforce root (X:/RawData)
        std::filesystem::path toolsDir; ///< Path to the Tools dir in in the perforce root (X:/Tools)
        ComponentsSchema schema; ///< Schema of all components
        bool validationEnabled = false; ///< validate all objects at load/save

        /// Component needed for each type of components
        std::map<std::string, std::vector<std::string>> componentDependencies;

        /// Load the EntityLib, given the path to the Tools directory
        explicit EntityLib(std::filesystem::path _rootPath);
        ~EntityLib();
        /// @cond PRIVATE
        EntityLib(EntityLib const&) = delete;
        EntityLib& operator=(EntityLib const&) = delete;
        DeleteCheck deleteCheck;
        /// @endcond

        /// Load the Entity at path _entityPath
        std::unique_ptr<Entity> loadEntity(
            std::filesystem::path const& _entityPath, Ent::Entity const* _super = nullptr) const;

        /// Load the Scene at path _scenePath
        std::unique_ptr<Scene> loadScene(std::filesystem::path const& _scenePath) const;

        /// Save the Entity at path _entityPath
        void saveEntity(Entity const& _entity, std::filesystem::path const& _entityPath) const;

        /// Save the Scene at path _scenePath
        void saveScene(Scene const& _scene, std::filesystem::path const& _scenePath) const;

        /// @brief Create an Entity which instanciate an other.
        ///
        /// This allow to override some properties without change the prefab properties.
        std::unique_ptr<Entity> makeInstanceOf(std::string _instanceOf ///< Path to the prefab Entity
        ) const;

        struct EntityFile
        {
            std::unique_ptr<Entity> data;
            std::filesystem::file_time_type time;
        };
        struct SceneFile
        {
            std::unique_ptr<Scene> data;
            std::filesystem::file_time_type time;
        };
        std::map<std::filesystem::path, EntityFile> const& getEntityCache() const;
        std::map<std::filesystem::path, SceneFile> const& getSceneCache() const;

        void clearCache();

    private:
        std::filesystem::path getAbsolutePath(std::filesystem::path const& _path) const;

        /// Load an Entity or a Scene, using the given cache
        template <typename Type, typename Cache, typename ValidateFunc, typename LoadFunc>
        std::unique_ptr<Type> loadEntityOrScene(
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
        if (overrideValue.has_value())
        {
            return *overrideValue;
        }
        if (prefabValue.has_value())
        {
            return *prefabValue;
        }
        return defaultValue;
    }

    template <typename V>
    void Override<V>::set(V _newVal)
    {
        overrideValue.emplace(std::move(_newVal));
    }

    template <typename V>
    bool Override<V>::isSet() const
    {
        return overrideValue.has_value();
    }

    template <typename V>
    void Override<V>::unset()
    {
        overrideValue = tl::nullopt;
    }

    template <typename V>
    Override<V> Override<V>::detach() const
    {
        if (overrideValue.has_value())
            return Override<V>(defaultValue, tl::nullopt, overrideValue);
        else
            return Override<V>(defaultValue, tl::nullopt, prefabValue);
    }

    template <typename V>
    Override<V> Override<V>::makeInstanceOf() const
    {
        if (overrideValue.has_value())
            return Override<V>(defaultValue, overrideValue, tl::nullopt);
        else
            return Override<V>(defaultValue, prefabValue, tl::nullopt);
    }
    /// \endcond

} // namespace Ent
