#include "include/EntityLib.h"

#include <iostream>
#include <fstream>

#include "external/json.hpp"
#include "external/optional.hpp"

using namespace nlohmann;

namespace Ent
{
    StaticData loadStaticData() // Read schema and dependencies
    {
        // char const* schemaPath = "E:/code/Wild/Bin/WildEngineStatic/WildEngine/x64/Release/"
        //                         "JsonSchemas.jsn";
        // TODO : Read schema
        // TODO : Read componentDependencies
        return StaticData{};
    }

    Node::Node(Value val)
        : value(std::move(val))
    {
    }

    DataType Node::getDataType() const
    {
        return (DataType)value.which();
    }

    Node* Node::at(char const* field)
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(field).get();
        }
        throw BadType();
    }
    Node const* Node::at(char const* field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(field).get();
        }
        throw BadType();
    }
    bool Node::count(char const* field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().count(field) != 0;
        }
        throw BadType();
    }
    Node* Node::at(size_t index)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data[index].get();
        }
        throw BadType();
    }
    Node const* Node::at(size_t index) const
    {
        if (value.is<Object>())
        {
            auto iter = value.get<Object>().begin();
            std::advance(iter, index);
            return iter->second.get();
        }
        if (value.is<Array>())
        {
            return value.get<Array>().data[index].get();
        }
        throw BadType();
    }
    size_t Node::size() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data.size();
        }
        throw BadType();
    }

    float Node::getFloat() const
    {
        if (value.is<Override<float>>())
        {
            return value.get<Override<float>>().get();
        }
        if (value.is<Override<int64_t>>())
        {
            return static_cast<float>(value.get<Override<int64_t>>().get());
        }
        throw BadType();
    }
    int64_t Node::getInt() const
    {
        if (value.is<Override<int64_t>>())
        {
            return value.get<Override<int64_t>>().get();
        }
        throw BadType();
    }
    char const* Node::getString() const
    {
        if (value.is<Override<std::string>>())
        {
            return value.get<Override<std::string>>().get().c_str();
        }
        throw BadType();
    }
    bool Node::getBool() const
    {
        if (value.is<Override<bool>>())
        {
            return value.get<Override<bool>>().get();
        }
        throw BadType();
    }

    void Node::setNone()
    {
        value = Null{};
    }
    void Node::setFloat(float val)
    {
        value = Override<float>{ val };
    }
    void Node::setInt(int64_t val)
    {
        value = Override<int64_t>{ val };
    }
    void Node::setString(char const* val)
    {
        value = Override<std::string>{ val };
    }
    void Node::setBool(bool val)
    {
        value = Override<bool>{ val };
    }

    struct UnSet
    {
        template <typename T>
        void operator()(Override<T>& ov) const
        {
            ov.unset();
        }

        template <typename U>
        void operator()(U& notOverride) const
        {
            (void*)&notOverride;
            throw BadType();
        }
    };

    void Node::unset()
    {
        std::apply_visitor(UnSet{}, value);
    }

    struct IsSet
    {
        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return ov.isSet();
        }

        template <typename U>
        bool operator()(U const& notOverride) const
        {
            (void*)&notOverride;
            throw BadType();
        }
    };

    bool Node::isSet() const
    {
        return std::apply_visitor(IsSet{}, value);
    }

    bool Node::isArraySizeSet() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().size.isSet();
        }
        throw BadType();
    }

    std::vector<char const*> Node::getFieldNames() const
    {
        if (value.is<Object>())
        {
            std::vector<char const*> fields;
            for (auto&& f : value.get<Object>())
            {
                fields.push_back(f.first.c_str());
            }
            return fields;
        }
        throw BadType();
    }

    std::vector<Node const*> Node::getItems() const
    {
        if (value.is<Array>())
        {
            std::vector<Node const*> items;
            for (auto&& n : value.get<Array>().data)
            {
                items.push_back(n.get());
            }
            return items;
        }
        throw BadType();
    }

    // ********************************* Entity ***************************************************

    char const* Entity::getName() const
    {
        return name.c_str();
    }
    void Entity::setName(std::string _name)
    {
        name = _name;
    }
    std::array<uint8_t, 4> Entity::getColor() const
    {
        return color;
    }
    void Entity::setColor(std::array<uint8_t, 4> _color)
    {
        color = _color;
    }
    Component* Entity::addComponent(char const*) // type
    {
        // TODO (check dependencies)
        return nullptr;
    }
    Component const* Entity::getComponent(char const* type) const
    {
        return &(components.at(type));
    }
    Component* Entity::getComponent(char const* type)
    {
        return &(components.at(type));
    }
    void Entity::removeComponent(char const*) // type
    {
        // TODO (check dependencies)
    }

} // namespace Ent

// ********************************** Load/Save ***********************************************

static Ent::Node loadNode(json const& data)
{
    Ent::Node result;
    switch (data.type())
    {
    case nlohmann::detail::value_t::null: result = Ent::Node(Ent::Null{}); break;
    case nlohmann::detail::value_t::string:
        result = Ent::Node(Ent::Override<std::string>(data.get<std::string>()));
        break;
    case nlohmann::detail::value_t::boolean:
        result = Ent::Node(Ent::Override<bool>(data.get<bool>()));
        break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
        result = Ent::Node(Ent::Override<int64_t>(data.get<int64_t>()));
        break;
    case nlohmann::detail::value_t::number_float:
        result = Ent::Node(Ent::Override<float>(data.get<float>()));
        break;
    case nlohmann::detail::value_t::object:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadNode(value);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object));
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        Ent::Array arr;
        for (auto const& item : data)
        {
            Ent::Node tmpNode = loadNode(item);
            arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        arr.size = data.size();
        result = Ent::Node(std::move(arr));
    }
    break;
    case nlohmann::detail::value_t::discarded: break;
    }
    return result;
}

static Ent::Entity loadEntity(json const& entNode)
{
    // TODO override, types and default values

    auto name = entNode.at("Name").get<std::string>();

    std::array<uint8_t, 4> color;
    if (entNode.contains("Color"))
    {
        json const& colorNode = entNode.at("Color");
        colorNode[0].get_to(color[0]);
        colorNode[1].get_to(color[1]);
        colorNode[2].get_to(color[2]);
        colorNode[3].get_to(color[3]);
    }
    else
    {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        color[3] = 0;
    }

    std::map<std::string, Ent::Component> components;
    json const& componentsNode = entNode.at("Components");
    for (json const& compNode : componentsNode)
    {
        auto cmpType = compNode.at("Type").get<std::string>();
        json const& data = compNode.at("Data");
        Ent::Component comp{ loadNode(data) };

        components.emplace(cmpType, std::move(comp));
    }
    return Ent::Entity{ std::move(name), color, std::move(components) };
}

Ent::Entity Ent::loadEntity(std::filesystem::path const& entityPath)
{
    std::ifstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for read: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document;
    file >> document;

    Ent::Entity ent = ::loadEntity(document);
    return ent;
}

Ent::Scene Ent::loadScene(std::filesystem::path const& scenePath)
{
    std::ifstream file(scenePath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for read: %ls", scenePath.c_str());
        throw std::runtime_error(message.data());
    }
    json document;
    file >> document;

    Scene scene;

    for (json const& entNode : document.at("Objects"))
    {
        Ent::Entity ent = ::loadEntity(entNode);
        scene.objects.emplace_back(std::move(ent));
    }

    return scene;
}

void Ent::saveEntity(
    Entity const&, // entity
    std::filesystem::path const& // entityPath
)
{
    // TODO
}

void Ent::saveScene(
    Scene const&, // scene
    std::filesystem::path const& // scenePath
)
{
    // TODO
}
