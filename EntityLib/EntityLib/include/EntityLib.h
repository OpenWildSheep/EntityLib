#pragma once

#pragma warning(push, 0)
#include <vector>
#include <memory>
#include <map>
#include <array>
#include <filesystem>

#include "../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#pragma warning(pop)

#include "Schema.h"

namespace std
{
    using namespace experimental;
    using namespace mapbox::util;
} // namespace std

namespace Ent
{
    // ******************************** Global declarations ***************************************

    /// Exception thrown when calling a method of a Node which has not the apropriate Ent::DataType
    struct BadType : std::runtime_error
    {
        BadType();
    };

    // ******************************** Implem details ********************************************

    struct Node;

    /// \cond PRIVATE

    /// Content of a Node which has type Ent::DataType::object
    using Object = std::map<std::string, std::unique_ptr<Node>>;

    /// Content of a Node which has type Ent::DataType::array
    struct Array
    {
        std::vector<std::unique_ptr<Node>> data; ///< List of items of the array
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
        Override(V defaultVal, V val)
            : defaultValue(defaultVal)
            , value(val)
        {
        }

        V const& get() const;

        void set(V newVal);

        bool isSet() const;

        void unset();

        Override<V> detach() const;

        Override<V> makeInstanceOf() const;

    public:
        V defaultValue = V();
        tl::optional<V> prefabValue;
        tl::optional<V> overrideValue;
    };

    /// \endcond

    // *********************************** Scene/Entity/Component/Node ****************************

    struct Subschema;

    /// Property node. Can contains any type in Ent::DataType
    struct ENTLIB_DLLEXPORT Node
    {
        /// @cond PRIVATE
        using Value =
            std::variant<Null, Override<std::string>, Override<float>, Override<int64_t>, Object, Array, Override<bool>>;
        Node() = default;
        Node(Value val, Subschema const* schema);
        ~Node() = default;

        Node(Node const&) = delete;
        Node& operator=(Node const&) = delete;
        Node(Node&&) = default;
        Node& operator=(Node&&) = default;
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
        bool empty() const; ///< ///< @pre type==Ent::DataType::array. @brief return true if array is empty

        // Value
        float getFloat() const; ///< @pre number or integer. @brief Get the value as float
        int64_t getInt() const; ///< @pre number or integer. @brief Get the value as float
        char const* getString() const; ///< @pre Ent::DataType == string. @brief Get the value as string
        bool getBool() const; ///< @pre type==Ent::DataType::boolean. @brief Get the value as bool

        void setFloat(float val); ///< @pre type==Ent::DataType::number. @brief Set the float value
        void setInt(int64_t val); ///< @pre type==Ent::DataType::integer. @brief Set the int64_t value
        void setString(char const* val); ///< @pre type==Ent::DataType::string. @brief Set the string value
        void setBool(bool val); ///< @pre type==Ent::DataType::boolean. @brief Set the bool value

        /// @brief Fallback the the prefab or default value. The value will not be saved in json.
        /// @pre Ent::DataType is in {number, integer, boolean, string}
        void unset();

        /// Check if the value is set explicitly (it override the prefab or default value)
        bool isSet() const;

        /// \cond PRIVATE
        /// Create a Node with the same value but which doesn't rely on prefab.
        Node detach() const;

        /// Create a Node is an "instance of" this one. With no override.
        Node makeInstanceOf() const;

        /// @brief Recursively check if there is an override inside.
        ///
        /// If there is no override, there is no need to save it.
        bool hasOverride() const;
        /// \endcond

    private:
        Subschema const* schema = nullptr; ///< The Node schema. To avoid to pass it to each call
        Value value; ///< Contains one of the types accepted by a Node
    };

    /// The properties of a given component
    struct Component
    {
        std::string type; ///< Component type (ex : Transform, VisualGD, HeightObj ...)
        Node root; ///< Root node a the component. Always of type Ent::DataType::object
        size_t version; ///< @todo remove?
        size_t index; ///< Useful to keep the componants order in the json file. To make diffs easier.
    };

    struct Scene;

    /// @brief The properties of a component "SubScene"
    /// @remark "SubScene" need a special case because it contain some Scene, although a Node can't be a Scene.
    ///  There are other solutions to sove this problem like keep everything as a Node and make
    ///  Scene/Component only wrapper to Node. Let's see if the current solution is ok.
    struct SubSceneComponent
    {
        bool isEmbedded; ///< If true, data are in embedded, else data are in file
        std::string file; ///< Path to a .scene file, whene isEmbedded is false
        size_t index; ///< Useful to keep the componants order in the json file
        std::unique_ptr<Scene> embedded; ///< Embedded Scene, whene isEmbedded is true
    };

    struct EntityLib;

    /// Contains all data of an Entity. (Name, Color, Conponent ...)
    struct ENTLIB_DLLEXPORT Entity
    {
        /// @cond PRIVATE
        Entity() = default;
        Entity(
            EntityLib const& _entlib,
            std::string _name,
            std::map<std::string, Component> _components,
            tl::optional<SubSceneComponent> _subSceneComponent,
            tl::optional<std::array<uint8_t, 4>> color = tl::nullopt,
            tl::optional<std::string> _thumbnail = tl::nullopt,
            tl::optional<std::string> _instanceOf = tl::nullopt);
        Entity(Entity const&) = delete;
        Entity& operator=(Entity const&) = delete;
        Entity(Entity&&) = default;
        Entity& operator=(Entity&&) = default;
        /// @endcond

        char const* getName() const; ///< Get the name of the component
        void setName(std::string name); ///< Set the name of the component
        char const* getInstanceOf() const; ///< Name of the inherited prefab if there is one, or nullptr.
        char const* getThumbnail() const; ///< Get the Thumbnail path, or nullptr.
        std::array<uint8_t, 4> const* getColor() const; ///< Get the color of the is one, or nullptr.
        void setColor(std::array<uint8_t, 4> color); ///< Set the color RGBA 8bit

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

        /// @brief Make the Entity independent from its prefab (instanceOf)
        ///
        /// All properties overrided in _entity OR in the prefeb become overrided in the Entity.
        /// The prefab is no more referenced.
        /// The properties keep the sames values
        Entity detachEntityFromPrefab() const;

    private:
        EntityLib const* entlib{}; ///< Reference the entity lib to find the schema when needed
        std::string name; ///< Entity name
        std::map<std::string, Component> components; ///< All components of this Entity
        tl::optional<SubSceneComponent> subSceneComponent; ///< the optional SubScene Component
        tl::optional<std::array<uint8_t, 4>> color; ///< The optional Color of the Entity
        tl::optional<std::string> thumbnail; ///< Path to the thumbnail mesh (.wthumb)
        tl::optional<std::string> instanceOf; ///< Path to the prefab if this is the instanciation of an other entity
    };

    /// Contain all data of a scene. (A list of Entity)
    struct Scene
    {
        std::vector<Entity> objects; ///< All Ent::Entity of this Scene
    };

    // ********************************** Static data *********************************************

    /// Entry point of the EntityLib. Used to load/save Scene/Entity and to parse the Schema
    struct ENTLIB_DLLEXPORT EntityLib
    {
        /// @todo Make public attribute private?
        std::filesystem::path toolsDir; ///< Path to the Tools dir in in the perforce root (X:/Tools)
        Schema schema; ///< Schema of all components

        /// Component needed for each type of components
        std::map<std::string, std::vector<std::string>> componentDependencies;

        /// Load the EntityLib, given the path to the Tools directory
        explicit EntityLib(std::filesystem::path const& _toolsDir);
        ~EntityLib();
        /// @cond PRIVATE
        EntityLib(EntityLib const&) = delete;
        EntityLib& operator=(EntityLib const&) = delete;
        EntityLib(EntityLib&&) = default;
        EntityLib& operator=(EntityLib&&) = default;
        /// @endcond

        /// Load the Entity at path _entityPath
        Entity loadEntity(std::filesystem::path const& entityPath) const;

        /// Load the Scene at path _scenePath
        Scene loadScene(std::filesystem::path const& _scenePath) const;

        /// Save the Entity at path _entityPath
        void saveEntity(Entity const& entity, std::filesystem::path const& _entityPath) const;

        /// Save the Scene at path _scenePath
        void saveScene(Scene const& scene, std::filesystem::path const& _scenePath) const;

        /// @brief Create an Entity which instanciate an other.
        ///
        /// This allow to override some properties without change the prefab properties.
        Entity makeInstanceOf(
            std::string _name, ///< Name of the new Entity
            std::string _instanceOf, ///< Path to the prefab Entity
            tl::optional<std::array<uint8_t, 4>> color = tl::nullopt ///< Optional color of the new Entity
        ) const;
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
    void Override<V>::set(V newVal)
    {
        overrideValue.emplace(std::move(newVal));
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
