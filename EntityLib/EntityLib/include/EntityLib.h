#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include "../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#include "../external/json.hpp"

namespace std
{
    using namespace experimental;
    using namespace tl;
    using namespace mapbox::util;
} // namespace std

#ifdef ENTLIB_NO_LINKAGE
#define ENTLIB_DLLEXPORT
#else
#ifdef ENTLIB_INSIDE
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
        BadType()
            : std::runtime_error("Bad node type")
        {
        }
    };

    enum class DataType
    {
        null,
        string,
        number,
        integer,
        object,
        array,
        boolean
    };

    // ******************************** Implem details ********************************************
    template <typename V>
    struct Override
    {
        Override() = default;
        Override(V val)
            : defaultValue()
            , value(val)
        {
        }

        V const& get() const;

        void set(V newVal);

        bool isSet() const;

        void unset();

    public:
        V defaultValue = V();
        std::optional<V> value;
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
    };

    using Value =
        std::variant<Null, Override<std::string>, Override<float>, Override<int64_t>, Object, Array, Override<bool>>;

    // *********************************** Scene/Entity/Component/Node ****************************

    // Each node can search in any version
    struct ENTLIB_DLLEXPORT Node
    {
        Node() = default;
        Node(Value val);
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

    private:
        Value value;
    };

    struct Component
    {
        Node root;
    };

    struct ENTLIB_DLLEXPORT Entity
    {
        Entity() = default;
        Entity(std::string _name, std::array<uint8_t, 4> _color, std::map<std::string, Component> _components)
            : name(std::move(_name))
            , color(_color)
            , components(std::move(_components))
        {
        }
        Entity(Entity const&) = delete;
        Entity& operator=(Entity const&) = delete;
        Entity(Entity&&) = default;
        Entity& operator=(Entity&&) = default;

        char const* getName() const;
        void setName(std::string name);
        std::array<uint8_t, 4> getColor() const;
        void setColor(std::array<uint8_t, 4> color);

        Component* addComponent(char const* type);
        Component const* getComponent(char const* type) const;
        Component* getComponent(char const* type);
        void removeComponent(char const* type);
        std::vector<char const*> getComponentTypes() const
        {
            std::vector<char const*> types;
            for (auto&& type_comp : components)
                types.push_back(type_comp.first.c_str());
            return types;
        }
        std::map<std::string, Component> const& getComponents() const
        {
            return components;
        }

    private:
        std::string name;
        std::array<uint8_t, 4> color;
        std::map<std::string, Component> components;
    };

    struct Scene
    {
        std::vector<Entity> objects;
    };

    // ------------------------------ Schema ------------------------------------------------------

    struct Definition;

    struct PropNull
    {
    };
    struct PropString
    {
        std::optional<std::string> defaultVal;
    };

    struct PropInteger
    {
        std::optional<int64_t> defaultVal;
    };

    struct PropNumber
    {
        std::optional<float> defaultVal;
    };

    struct Property;

    struct PropObject
    {
        std::map<std::string, Property*> properties;
    };

    struct PropArray
    {
        std::unique_ptr<Property> items;
    };

    struct PropBoolean
    {
        std::optional<bool> defaultVal;
    };

    using PropData =
        std::variant<PropNull, PropString, PropNumber, PropInteger, PropObject, PropArray, PropBoolean>;

    struct ENTLIB_DLLEXPORT Property
    {
        Property() = default;
        Property(Property const&) = delete;
        Property& operator=(Property const&) = delete;
        Property(Property&&) = default;
        Property& operator=(Property&&) = default;

        char const* getName() const;
        DataType getType() const;

        std::optional<float> getDefaultFloat() const;
        std::optional<int64_t> getDefaultInt() const;
        std::optional<char const*> getDefaultString() const;
        std::optional<bool> getDefaultBool() const;

        Property const* getArrayItemProperty() const;

        std::vector<char const*, Property const*> getObjectProperties() const;

        std::vector<char const*> getObjectPropertyNames() const;

        Property const* getObjectProperty(char const* _propName) const;

    private:
        std::string name;
        PropData value;
    };

    struct Definition
    {
        std::map<std::string, Property> properties;
    };

    struct Schema
    {
        std::map<std::string, Definition> definitions;
    };

    // ********************************** Static data *********************************************

    struct StaticData
    {
        Schema schema;
        std::map<std::string, std::vector<std::string>> componentDependencies;
    };

    ENTLIB_DLLEXPORT StaticData loadStaticData(); // Read schema and dependencies

    // ********************************** Load/Save ***********************************************

    ENTLIB_DLLEXPORT Entity loadEntity(std::filesystem::path const& entityPath);

    ENTLIB_DLLEXPORT Scene loadScene(std::filesystem::path const& scenePath);

    ENTLIB_DLLEXPORT void saveEntity(Entity const& entity, std::filesystem::path const& entityPath);

    ENTLIB_DLLEXPORT void saveScene(Scene const& scene, std::filesystem::path const& scenePath);

    // *************************** Implem details - method bodies *********************************

    template <typename V>
    V const& Override<V>::get() const
    {
        if (value.has_value())
        {
            return *value;
        }
        return defaultValue;
    }

    template <typename V>
    void Override<V>::set(V newVal)
    {
        return *value = newVal;
    }

    template <typename V>
    bool Override<V>::isSet() const
    {
        return value.has_value();
    }

    template <typename V>
    void Override<V>::unset()
    {
        value = std::nullopt;
    }

} // namespace Ent
