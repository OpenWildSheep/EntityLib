#include "include/EntityLib.h"

#include "Tools.h"
#include "SchemaLoader.h"

#pragma warning(push, 0)
#include <iostream>
#include <fstream>
#include <set>

#include "external/json.hpp"
// TODO Add valid check
//#include <valijson/adapters/nlohmann_json_adapter.hpp>
//#include <valijson/utils/nlohmann_json_utils.hpp>
//#include <valijson/schema.hpp>
//#include <valijson/schema_parser.hpp>
#pragma warning(pop)

using namespace nlohmann;

// char schemaPath[2048] = {};

static Ent::Node loadNode(Ent::Subschema const& nodeSchema, json const& data, Ent::Node const* super);

namespace Ent
{
    BadType::BadType()
        : std::runtime_error("Bad node type")
    {
    }

    EntityLib::EntityLib(std::filesystem::path const& toolsDir) // Read schema and dependencies
    {
        auto schemaPath = toolsDir / "WildPipeline/Schema";

        json schemaDocument = loadJsonFile(toolsDir / "WildPipeline/Schema/Scene-schema.json");

        json const& definition = schemaDocument.at("definitions");
        json const& compList = definition.at("Component").at("oneOf");

        SchemaLoader loader(schemaPath);

        for (json const& comp : compList)
        {
            json const& properties = comp.at("properties");
            auto compName = properties.at("Type").at("const").get<std::string>();

            json const& data = properties["Data"];
            Ent::Subschema sub = loader.readSchema(schemaDocument, data, compName);

            schema.definitions.emplace(compName, std::move(sub));
        }

        json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");
        for (json const& comp : dependencies["Dependencies"])
        {
            auto name = comp["className"].get<std::string>();
            std::vector<std::string> deps;
            for (json const& dep : comp["dependencies"])
            {
                if (dep["Optional"].get<bool>() == false)
                {
                    deps.push_back(dep["Name"].get<std::string>());
                }
            }
            componentDependencies.emplace(std::move(name), std::move(deps));
        }
    }

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
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
        value.get<Override<float>>().set(val);
    }
    void Node::setInt(int64_t val)
    {
        value.get<Override<int64_t>>().set(val);
    }
    void Node::setString(char const* val)
    {
        value.get<Override<std::string>>().set(val);
    }
    void Node::setBool(bool val)
    {
        value.get<Override<bool>>().set(val);
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
            // throw BadType();
            return true; // Object and Array are always considered as overrided
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

    struct Detach
    {
        Subschema const* schema;

        template <typename T>
        Node operator()(Override<T> const& ov) const
        {
            return Node(ov.detach(), schema);
        }

        Node operator()(Null const&) const
        {
            return Node(Null{}, schema);
        }

        Node operator()(Array const& arr) const
        {
            Array out;
            for (auto&& item : arr.data)
                out.data.emplace_back(std::make_unique<Node>(item->detach()));
            out.size = arr.size.detach();
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& obj) const
        {
            Object out;
            for (auto&& name_node : obj)
                out.emplace(
                    std::get<0>(name_node), std::make_unique<Node>(std::get<1>(name_node)->detach()));
            return Node(std::move(out), schema);
        }
    };

    Node Node::detach() const
    {
        return std::apply_visitor(Detach{ schema }, value);
    }

    struct MakeInstanceOf
    {
        Subschema const* schema;

        template <typename T>
        Node operator()(Override<T> const& ov) const
        {
            return Node(ov.makeInstanceOf(), schema);
        }

        Node operator()(Null const&) const
        {
            return Node(Null{}, schema);
        }

        Node operator()(Array const& arr) const
        {
            Array out;
            for (auto&& item : arr.data)
                out.data.emplace_back(std::make_unique<Node>(item->makeInstanceOf()));
            out.size = arr.size.detach();
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& obj) const
        {
            Object out;
            for (auto&& name_node : obj)
                out.emplace(
                    std::get<0>(name_node),
                    std::make_unique<Node>(std::get<1>(name_node)->makeInstanceOf()));
            return Node(std::move(out), schema);
        }
    };

    Node Node::makeInstanceOf() const
    {
        return std::apply_visitor(MakeInstanceOf{ schema }, value);
    }

    struct HasOverride
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return ov.isSet();
        }

        bool operator()(Null const&) const
        {
            return false;
        }

        bool operator()(Array const& arr) const
        {
            return std::any_of(begin(arr.data), end(arr.data), std::mem_fn(&Ent::Node::hasOverride));
        }

        bool operator()(Object const& obj) const
        {
            for (auto&& name_node : obj)
            {
                if (std::get<1>(name_node)->hasOverride())
                {
                    return true;
                }
            }
            return false;
        }
    };

    bool Node::hasOverride() const
    {
        return std::apply_visitor(HasOverride{ schema }, value);
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

    Node* Node::push()
    {
        if (value.is<Array>())
        {
            if (auto itemSchema = schema->singularItems.get())
            {
                value.get<Array>().data.emplace_back(
                    std::make_unique<Node>(loadNode(*itemSchema, json(), nullptr)));
                return value.get<Array>().data.back().get();
            }
        }
        throw BadType();
    }
    void Node::pop()
    {
        if (value.is<Array>())
        {
            value.get<Array>().data.pop_back();
        }
        throw BadType();
    }

    // ********************************* Entity ***************************************************

    Entity::Entity(
        std::string _name,
        std::map<std::string, Component> _components,
        tl::optional<std::array<uint8_t, 4>> _color,
        tl::optional<std::string> _thumbnail,
        tl::optional<std::string> _instanceOf)
        : name(std::move(_name))
        , components(std::move(_components))
        , color(_color)
        , thumbnail(std::move(_thumbnail))
        , instanceOf(std::move(_instanceOf))
    {
    }

    char const* Entity::getName() const
    {
        return name.c_str();
    }
    void Entity::setName(std::string _name)
    {
        name = _name;
    }
    char const* Entity::getInstanceOf() const
    {
        return instanceOf.has_value() ? instanceOf->c_str() : nullptr;
    }
    char const* Entity::getThumbnail() const
    {
        return thumbnail.has_value() ? thumbnail->c_str() : nullptr;
    }
    std::array<uint8_t, 4> const* Entity::getColor() const
    {
        return color.has_value() ? &(*color) : nullptr;
    }
    void Entity::setColor(std::array<uint8_t, 4> _color)
    {
        color = _color;
    }
    Component* Entity::addComponent(EntityLib const& entlib, char const* type)
    {
        if (entlib.componentDependencies.count(type)) // Could be an editor componant
        {
            for (auto&& dep : entlib.componentDependencies.at(type))
            {
                addComponent(entlib, dep.c_str());
            }
        }
        Ent::Subschema const& compSchema = entlib.schema.definitions.at(type);
        Ent::Component comp{ type, loadNode(compSchema, json(), nullptr), 1, components.size() };
        auto iter_bool = components.emplace(type, std::move(comp));
        return &(iter_bool.first->second);
    }
    Component const* Entity::getComponent(char const* type) const
    {
        auto iter = components.find(type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    Component* Entity::getComponent(char const* type)
    {
        auto iter = components.find(type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    void Entity::removeComponent(char const* type)
    {
        // TODO : Use dependencies
        components.erase(type);
    }

    std::vector<char const*> Entity::getComponentTypes() const
    {
        std::vector<char const*> types;
        for (auto&& type_comp : components)
            types.push_back(type_comp.first.c_str());
        return types;
    }

    std::map<std::string, Component> const& Entity::getComponents() const
    {
        return components;
    }

} // namespace Ent

// ********************************** Load/Save ***********************************************

static Ent::Node loadFreeObjectNode(json const& data)
{
    Ent::Node result;
    switch (data.type())
    {
    case nlohmann::detail::value_t::null: result = Ent::Node(Ent::Null{}, nullptr); break;
    case nlohmann::detail::value_t::string:
        result = Ent::Node(
            Ent::Override<std::string>(std::string(), tl::nullopt, data.get<std::string>()), nullptr);
        break;
    case nlohmann::detail::value_t::boolean:
        result = Ent::Node(Ent::Override<bool>(bool{}, tl::nullopt, data.get<bool>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
        result =
            Ent::Node(Ent::Override<int64_t>(int64_t{}, tl::nullopt, data.get<int64_t>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_float:
        result = Ent::Node(Ent::Override<float>(float{}, tl::nullopt, data.get<float>()), nullptr);
        break;
    case nlohmann::detail::value_t::object:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadFreeObjectNode(value);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), nullptr);
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        Ent::Array arr;
        for (auto const& item : data)
        {
            Ent::Node tmpNode = loadFreeObjectNode(item);
            arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        arr.size = Ent::Override<int64_t>(int64_t{}, tl::nullopt, static_cast<int64_t>(data.size()));
        result = Ent::Node(std::move(arr), nullptr);
    }
    break;
    case nlohmann::detail::value_t::discarded: break;
    }
    return result;
}

static Ent::Node const emptyNode(Ent::Null(), nullptr);

static Ent::Node loadNode(Ent::Subschema const& nodeSchema, json const& data, Ent::Node const* super)
{
    Ent::Node result;

    switch (nodeSchema.type)
    {
    case Ent::DataType::null: result = Ent::Node(Ent::Null{}, &nodeSchema); break;
    case Ent::DataType::string:
    {
        std::string const def = nodeSchema.defaultValue.is_null() ?
                                    std::string() :
                                    nodeSchema.defaultValue.get<std::string>();
        tl::optional<std::string> const supVal = super and super->isSet() ?
                                                     tl::optional<std::string>(super->getString()) :
                                                     tl::optional<std::string>(tl::nullopt);
        tl::optional<std::string> const val =
            data.is_string() ? tl::optional<std::string>(data.get<std::string>()) :
                               tl::optional<std::string>(tl::nullopt);
        result = Ent::Node(Ent::Override<std::string>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::boolean:
    {
        bool const def =
            nodeSchema.defaultValue.is_null() ? bool{} : nodeSchema.defaultValue.get<bool>();
        tl::optional<bool> const supVal = super and super->isSet() ?
                                              tl::optional<bool>(super->getBool()) :
                                              tl::optional<bool>(tl::nullopt);
        tl::optional<bool> const val = data.is_boolean() ? tl::optional<bool>(data.get<bool>()) :
                                                           tl::optional<bool>(tl::nullopt);
        result = Ent::Node(Ent::Override<bool>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::integer:
    {
        int64_t const def =
            nodeSchema.defaultValue.is_null() ? int64_t{} : nodeSchema.defaultValue.get<int64_t>();
        tl::optional<int64_t> const supVal = super and super->isSet() ?
                                                 tl::optional<int64_t>(super->getInt()) :
                                                 tl::optional<int64_t>(tl::nullopt);
        tl::optional<int64_t> const val = data.is_number_integer() or data.is_number_unsigned() ?
                                              tl::optional<int64_t>(data.get<int64_t>()) :
                                              tl::optional<int64_t>(tl::nullopt);
        result = Ent::Node(Ent::Override<int64_t>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::number:
    {
        float const def =
            nodeSchema.defaultValue.is_null() ? float{} : nodeSchema.defaultValue.get<float>();
        tl::optional<float> const supVal = super and super->isSet() ?
                                               tl::optional<float>(super->getFloat()) :
                                               tl::optional<float>(tl::nullopt);
        tl::optional<float> const val = data.is_number_float() ?
                                            tl::optional<float>(data.get<float>()) :
                                            tl::optional<float>(tl::nullopt);
        result = Ent::Node(Ent::Override<float>(def, supVal, val), &nodeSchema);
    }
    break;
    case Ent::DataType::object:
    {
        Ent::Object object;

        for (auto&& name_sub : nodeSchema.properties)
        {
            std::string const& name = std::get<0>(name_sub);
            Ent::Node const* superProp = super ? super->at(name.c_str()) : nullptr;
            static json const emptyJson;
            json const& prop = data.count(name) ? data.at(name) : emptyJson;
            Ent::Node tmpNode = loadNode(std::get<1>(name_sub), prop, superProp);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), &nodeSchema);
    }
    break;
    case Ent::DataType::array:
    {
        Ent::Array arr;
        size_t index = 0;
        if (nodeSchema.singularItems)
        {
            if (data.is_null()) // No overrided
            {
                if (super != nullptr)
                {
                    for (Ent::Node const* subSuper : super->getItems())
                    {
                        Ent::Node tmpNode = loadNode(*nodeSchema.singularItems, json(), subSuper);
                        arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
                        ++index;
                    }
                    arr.size = Ent::Override<int64_t>(
                        int64_t{}, tl::nullopt, static_cast<int64_t>(super->size()));
                }
                else
                    arr.size = Ent::Override<int64_t>(int64_t{}, tl::nullopt, 0);
            }
            else
            {
                for (auto const& item : data)
                {
                    Ent::Node const* subSuper =
                        (super and (super->size() > index)) ? super->at(index) : nullptr;
                    Ent::Node tmpNode = loadNode(*nodeSchema.singularItems, item, subSuper);
                    arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
                    ++index;
                }
                arr.size = Ent::Override<int64_t>(
                    int64_t{}, tl::nullopt, static_cast<int64_t>(data.size()));
            }
        }
        else
        {
            ENTLIB_ASSERT(nodeSchema.linearItems.has_value());
            for (Ent::Subschema const& sub : *nodeSchema.linearItems)
            {
                Ent::Node const* subSuper =
                    (super and super->size() > index) ? super->at(index) : nullptr;
                static json const emptyJson;
                json const& prop = data.size() > index ? data.at(index) : emptyJson;
                Ent::Node tmpNode = loadNode(sub, prop, subSuper);
                arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
                ++index;
            }
            arr.size = Ent::Override<int64_t>(
                int64_t{}, tl::nullopt, static_cast<int64_t>(nodeSchema.linearItems->size()));
        }
        result = Ent::Node(std::move(arr), &nodeSchema);
    }
    break;
    case Ent::DataType::freeobject:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadFreeObjectNode(value);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), &nodeSchema);
    }
    break;
    }
    return result;
}

static json saveFreeObjectNode(Ent::Node const& node)
{
    json data;
    switch (node.getDataType())
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = node.getString(); break;
    case Ent::DataType::boolean: data = node.getBool(); break;
    case Ent::DataType::integer: data = node.getInt(); break;
    case Ent::DataType::number: data = node.getFloat(); break;
    case Ent::DataType::object:
    case Ent::DataType::freeobject:
    {
        data = json::object();
        for (auto const& name : node.getFieldNames())
        {
            Ent::Node const* subNode = node.at(name);
            json subJson = saveFreeObjectNode(*subNode);
            data[name] = std::move(subJson);
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        for (Ent::Node const* item : node.getItems())
        {
            json tmpNode = saveFreeObjectNode(*item);
            data.emplace_back(std::move(tmpNode));
        }
    }
    break;
    }
    return data;
}

static json saveNode(Ent::Subschema const& schema, Ent::Node const& node)
{
    json data;
    switch (schema.type)
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = node.getString(); break;
    case Ent::DataType::boolean: data = node.getBool(); break;
    case Ent::DataType::integer: data = node.getInt(); break;
    case Ent::DataType::number: data = node.getFloat(); break;
    case Ent::DataType::object:
    {
        data = json::object();
        for (auto const& name_sub : schema.properties)
        {
            auto&& name = std::get<0>(name_sub);
            Ent::Node const* subNode = node.at(name.c_str());
            if (subNode->hasOverride())
            {
                json subJson = saveNode(std::get<1>(name_sub), *subNode);
                data[name] = std::move(subJson);
            }
        }
    }
    break;
    case Ent::DataType::freeobject:
    {
        data = json::object();
        for (auto const& name : node.getFieldNames())
        {
            Ent::Node const* subNode = node.at(name);
            json subJson = saveFreeObjectNode(*subNode);
            data[name] = std::move(subJson);
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        for (Ent::Node const* item : node.getItems())
        {
            if (item->hasOverride())
            {
                json tmpNode = saveNode(*schema.singularItems, *item);
                data.emplace_back(std::move(tmpNode));
            }
            else
            {
                data.emplace_back(json());
            }
        }
    }
    break;
    }
    return data;
}

static Ent::Entity loadEntity(Ent::EntityLib const& entlib, Ent::Schema const& schema, json const& entNode)
{
    tl::optional<std::string> instanceOf;
    Ent::Entity superEntity;
    if (entNode.count("InstanceOf"))
    {
        instanceOf = entNode.at("InstanceOf").get<std::string>();
        superEntity = entlib.loadEntity(*instanceOf);
    }

    tl::optional<std::string> const thumbnail = entNode.count("Thumbnail") ?
                                                    entNode.at("Thumbnail").get<std::string>() :
                                                    tl::optional<std::string>();

    auto name = entNode.at("Name").get<std::string>();

    tl::optional<std::array<uint8_t, 4>> color;
    if (entNode.contains("Color"))
    {
        color.emplace();
        json const& colorNode = entNode.at("Color");
        colorNode[0].get_to(color->at(0));
        colorNode[1].get_to(color->at(1));
        colorNode[2].get_to(color->at(2));
        colorNode[3].get_to(color->at(3));
    }

    std::map<std::string, Ent::Component> components;
    json const& componentsNode = entNode.at("Components");
    size_t index = 0;
    for (json const& compNode : componentsNode)
    {
        auto const cmpType = compNode.at("Type").get<std::string>();
        Ent::Component* superComp = superEntity.getComponent(cmpType.c_str());
        auto const version = compNode.at("Version").get<size_t>();
        json const& data = compNode.at("Data");

        Ent::Subschema const& compSchema = schema.definitions.at(cmpType);

        Ent::Component comp{ cmpType,
                             loadNode(compSchema, data, (superComp ? &superComp->root : nullptr)),
                             version,
                             index };

        components.emplace(cmpType, std::move(comp));
        ++index;
    }
    // Add undeclared componants to be able to get values inside (They are full reference to prefab)
    for (auto const& type_comp : superEntity.getComponents())
    {
        auto const& cmpType = std::get<0>(type_comp);
        auto const& superComp = std::get<1>(type_comp);
        if (not components.count(cmpType))
        {
            Ent::Component comp{
                cmpType, superComp.root.makeInstanceOf(), superComp.version, superComp.index
            };

            components.emplace(cmpType, std::move(comp));
        }
        ++index;
    }
    return Ent::Entity(std::move(name), std::move(components), color, thumbnail, instanceOf);
}

Ent::Entity Ent::EntityLib::loadEntity(std::filesystem::path const& entityPath) const
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

    Ent::Entity ent = ::loadEntity(*this, schema, document);
    return ent;
}

Ent::Scene Ent::EntityLib::loadScene(std::filesystem::path const& scenePath) const
{
    json document;
    {
        std::ifstream file(scenePath);
        if (not file.is_open())
        {
            constexpr size_t MessSize = 1024;
            std::array<char, MessSize> message = {};
            sprintf_s(message.data(), MessSize, "Can't open file for read: %ls", scenePath.c_str());
            throw std::runtime_error(message.data());
        }
        file >> document;
    }

    // Reformat input to make diff easier
    /*{
        std::ofstream file(scenePath);
        file << document.dump(4);
    }*/

    Scene scene;

    for (json const& entNode : document.at("Objects"))
    {
        Ent::Entity ent = ::loadEntity(*this, schema, entNode);
        scene.objects.emplace_back(std::move(ent));
    }

    return scene;
}

static json saveEntity(Ent::Schema const& schema, Ent::Entity const& entity)
{
    // TODO override, types and default values
    json entNode;

    entNode.emplace("Name", entity.getName());

    if (char const* instanceOf = entity.getInstanceOf())
    {
        entNode.emplace("InstanceOf", instanceOf);
    }

    if (std::array<uint8_t, 4> const* color = entity.getColor())
    {
        entNode.emplace("Color", *color);
    }

    if (const char* thumbnail = entity.getThumbnail())
    {
        entNode.emplace("Thumbnail", thumbnail);
    }

    json& componentsNode = entNode["Components"] = json::array();
    std::vector<Ent::Component const*> sortedComp;
    for (auto&& type_comp : entity.getComponents())
    {
        sortedComp.push_back(&std::get<1>(type_comp));
    }
    std::sort(
        begin(sortedComp), end(sortedComp), [](Ent::Component const* cmp, Ent::Component const* cmp2) {
            return cmp->index < cmp2->index;
        });
    for (Ent::Component const* comp : sortedComp)
    {
        if (comp->root.hasOverride())
        {
            json compNode;
            compNode.emplace("Version", comp->version);
            compNode.emplace("Type", comp->type);
            compNode.emplace("Data", saveNode(schema.definitions.at(comp->type), comp->root));

            componentsNode.emplace_back(std::move(compNode));
        }
    }
    return entNode;
}

Ent::Entity Ent::EntityLib::detachEntityFromPrefab(Entity const& entity) const
{
    std::map<std::string, Ent::Component> components;
    size_t index = 0;
    for (auto const& type_comp : entity.getComponents())
    {
        auto const& type = std::get<0>(type_comp);
        auto const& comp = std::get<1>(type_comp);

        Ent::Component detachedComp{ type, comp.root.detach(), 1, index };

        components.emplace(type, std::move(detachedComp));
        ++index;
    }
    return Ent::Entity(
        std::move(entity.getName()),
        std::move(components),
        entity.getColor() ? *entity.getColor() : tl::optional<std::array<uint8_t, 4>>(),
        entity.getThumbnail() ? entity.getThumbnail() : tl::optional<std::string>());
}

Ent::Entity Ent::EntityLib::makeInstanceOf(
    std::string name, std::string _instanceOf, tl::optional<std::array<uint8_t, 4>> color)
{
    return Ent::Entity(
        std::move(name),
        std::map<std::string, Ent::Component>(),
        color,
        tl::nullopt,
        std::move(_instanceOf));
}

void Ent::EntityLib::saveEntity(Entity const& entity, std::filesystem::path const& entityPath) const
{
    std::ofstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document = ::saveEntity(schema, entity);

    file << document.dump(4);
}

void Ent::EntityLib::saveScene(Scene const& scene, std::filesystem::path const& scenePath) const
{
    std::ofstream file(scenePath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", scenePath.c_str());
        throw std::runtime_error(message.data());
    }
    json document;

    document.emplace("Version", 2);
    json& objects = document["Objects"];

    for (Ent::Entity const& ent : scene.objects)
    {
        objects.emplace_back(::saveEntity(schema, ent));
    }

    file << document.dump(4);
}

Ent::Component* Ent::EntityLib::addComponent(Entity& entity, char const* type) const
{
    return entity.addComponent(*this, type);
}

void Ent::mergeComponants(std::filesystem::path const& toolsDir)
{
    json runtimeCompSch = loadJsonFile(toolsDir / "WildPipeline/Schema/RuntimeComponants.json");
    json editionCompSch = loadJsonFile(toolsDir / "WildPipeline/Schema/EditionComponents.json");
    auto sceneSchemaPath = toolsDir / "WildPipeline/Schema/Scene-schema.json";
    json sceneSch = loadJsonFile(sceneSchemaPath);
    json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");

    runtimeCompSch = runtimeCompSch["definitions"];
    editionCompSch = editionCompSch["definitions"];

    auto&& compList = sceneSch["definitions"]["Component"]["oneOf"];
    compList = json();

    // Looking for components with same name and merge them
    std::map<std::string, json const*> editionCompMap;
    std::set<std::string> alreadyInsertedComponents;
    for (auto&& name_comp : editionCompSch.items())
    {
        editionCompMap.emplace(name_comp.key(), &(name_comp.value()));
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        auto iter = editionCompMap.find(name);
        if (iter != editionCompMap.end())
        {
            json merged = dep.value("properties", json());
            merged.update(*iter->second);

            json newComp;
            auto&& prop = newComp["properties"];
            prop["Type"]["const"] = name;
            prop["Data"] = std::move(merged);

            compList.push_back(std::move(newComp));
            alreadyInsertedComponents.insert(name);
        }
    }

    // Add other components
    auto addComponent = [&](std::string const& name, char const* filename) {
        if (alreadyInsertedComponents.count(name))
            return;
        json newComp;
        auto&& prop = newComp["properties"];
        prop["Type"]["const"] = name;
        prop["Data"]["$ref"] = "file://" + (filename + ("#/definitions/" + name));

        compList.push_back(std::move(newComp));
    };
    for (auto&& name_comp : editionCompSch.items())
    {
        addComponent(name_comp.key(), "EditionComponents.json");
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        addComponent(name, "RuntimeComponants.json");
    }

    std::ofstream file(sceneSchemaPath);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for write: " + sceneSchemaPath.u8string());
    }
    file << sceneSch.dump(4);
}
