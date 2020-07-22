#pragma once

#pragma warning(push, 0)
#include <vector>
#include <memory>
#include <map>
#include <array>
#include <filesystem>

#include "../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#include "../external/json.hpp" // TODO : Try to remove this inclusion
#pragma warning(pop)

namespace std
{
    using namespace experimental;
    using namespace mapbox::util;
} // namespace std

#ifdef ENTLIB_STATIC
#define ENTLIB_DLLEXPORT
#else
#ifdef ENTLIB_DYNAMIC
#define ENTLIB_DLLEXPORT __declspec(dllexport)
#else
#define ENTLIB_DLLEXPORT __declspec(dllimport)
#endif
#endif

namespace Ent
{
    // ******************************** Global declarations ***************************************
    struct BadType : std::runtime_error
    {
        BadType();
    };

    enum class DataType
    {
        null,
        string,
        number,
        integer,
        object,
        array,
        boolean,
        freeobject, // Object without schema. Used in Subscene/Embedded
    };

    // ******************************** Implem details ********************************************

    // *** Entity part ***

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

    public:
        V defaultValue = V();
        tl::optional<V> prefabValue;
        tl::optional<V> overrideValue;
    };

    struct Null
    {
    };

    struct Node;

    using Object = std::map<std::string, std::unique_ptr<Node>>;

    struct Array
    {
        std::vector<std::unique_ptr<Node>> data;
        Override<int64_t> size;

        Array() = default;
        Array(Array const&) = delete;
        Array& operator=(Array const&) = delete;
        Array(Array&&) = default;
        Array& operator=(Array&&) = default;
    };

    using Value =
        std::variant<Null, Override<std::string>, Override<float>, Override<int64_t>, Object, Array, Override<bool>>;

    // *********************************** Scene/Entity/Component/Node ****************************

    struct Subschema;

    // Each node can search in any version
    struct ENTLIB_DLLEXPORT Node
    {
        Node() = default;
        Node(Value val, Subschema const* schema);
        ~Node() = default;

        Node(Node const&) = delete;
        Node& operator=(Node const&) = delete;
        Node(Node&&) = default;
        Node& operator=(Node&&) = default;

        DataType getDataType() const;

        // Object
        Node* at(char const* field);
        Node const* at(char const* field) const;
        bool count(char const* field) const;
        std::vector<char const*> getFieldNames() const;

        // Array
        Node* at(size_t index);
        Node const* at(size_t index) const;
        size_t size() const;
        std::vector<Node const*> getItems() const;
        Node* push();
        void pop();

        // Value
        float getFloat() const;
        int64_t getInt() const;
        char const* getString() const;
        bool getBool() const;

        void setNone();
        void setFloat(float val);
        void setInt(int64_t val);
        void setString(char const* val);
        void setBool(bool val);

        void unset();

        bool isSet() const;

        bool isArraySizeSet() const;

        Node detach() const;

    private:
        Subschema const* schema = nullptr;
        Value value;
    };

    struct Component
    {
        std::string type;
        Node root;
        size_t version;
        size_t index; ///< Useful to keep the componants order in the json file
    };

    struct Schema;
    struct EntityLib;

    struct ENTLIB_DLLEXPORT Entity
    {
        Entity() = default;
        Entity(
            std::string _name,
            std::array<uint8_t, 4> _color,
            std::map<std::string, Component> _components,
            tl::optional<std::string> _instanceOf = tl::nullopt);
        Entity(Entity const&) = delete;
        Entity& operator=(Entity const&) = delete;
        Entity(Entity&&) = default;
        Entity& operator=(Entity&&) = default;

        char const* getName() const;
        void setName(std::string name);
        char const* getInstanceOf() const;
        std::array<uint8_t, 4> getColor() const;
        void setColor(std::array<uint8_t, 4> color);

        Component* addComponent(EntityLib const& entlib, char const* type);
        Component const* getComponent(char const* type) const;
        Component* getComponent(char const* type);
        void removeComponent(char const* type);
        std::vector<char const*> getComponentTypes() const;
        std::map<std::string, Component> const& getComponents() const;

    private:
        tl::optional<std::string> instanceOf;
        std::string name;
        std::array<uint8_t, 4> color;
        std::map<std::string, Component> components;
    };

    struct Scene
    {
        std::vector<Entity> objects;
    };

    // ------------------------------ Schema ------------------------------------------------------

    struct ENTLIB_DLLEXPORT Subschema
    {
        DataType type = DataType::null;
        bool required = true;
        std::map<std::string, Subschema> properties;
        size_t maxItems = size_t(-1);
        size_t minItems = 0;
        nlohmann::json defaultValue;
        std::unique_ptr<Subschema> singularItems; // In valijson it is a SingularItems
        tl::optional<std::vector<Subschema>> linearItems;
        std::vector<std::string> enumValues;
    };

    struct Schema
    {
        std::map<std::string, Subschema> definitions;
    };

    // ********************************** Static data *********************************************

    struct ENTLIB_DLLEXPORT EntityLib
    {
        Schema schema;
        std::map<std::string, std::vector<std::string>> componentDependencies;

        EntityLib() = default;
        EntityLib(EntityLib const&) = delete;
        EntityLib& operator=(EntityLib const&) = delete;
        EntityLib(EntityLib&&) = default;
        EntityLib& operator=(EntityLib&&) = default;

        // ********************************** Load/Save ***********************************************

        Entity loadEntity(std::filesystem::path const& entityPath) const;

        Scene loadScene(std::filesystem::path const& scenePath) const;

        void saveEntity(Entity const& entity, std::filesystem::path const& entityPath) const;

        Entity detachEntityFromPrefab(Entity const& entity) const;

        void saveScene(Scene const& scene, std::filesystem::path const& scenePath) const;

        Component* addComponent(Entity& entity, char const* type) const;
    };

    ENTLIB_DLLEXPORT
    EntityLib loadStaticData(std::filesystem::path const& toolsDir); //!< Read schema and dependencies

    // *************************** Implem details - method bodies *********************************

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

    // *********************** Merge Runtime componants into Entity schema ************************

    void mergeComponants(std::filesystem::path const& toolsDir);
} // namespace Ent
