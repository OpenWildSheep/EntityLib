#include "Object.h"

#include <ciso646>

#include "external/json.hpp"

#include "Tools.h"
#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{
    bool Object::hasDefaultValue() const
    {
        return std::all_of(nodes.begin(), nodes.end(), [](auto&& name_node) {
            return std::get<1>(name_node)->hasDefaultValue();
        });
    }

    // ************************************* Object ***********************************************

    void Ent::Object::unset()
    {
        for (auto&& name_node : nodes)
        {
            name_node.second->unset();
        }
    }

    void Ent::Object::applyAllValues(Object& _dest, CopyMode _copyMode) const
    {
        applyInstanceOfField(*this, _dest, _copyMode);
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            nodes[i].second->applyAllValues(*_dest.nodes[i].second, _copyMode);
        }
    }

    Ent::Object Ent::Object::makeInstanceOf() const
    {
        Object out(schema);
        out.instanceOf = instanceOf.makeInstanceOf();
        out.nodes.reserve(size());
        for (auto&& name_node : *this)
        {
            out.nodes.emplace_back(std::get<0>(name_node), std::get<1>(name_node)->makeInstanceOf());
        }
        std::sort(begin(out), end(out), CompObject());
        return out;
    }

    Object Ent::Object::detach() const
    {
        Object out(schema);
        out.nodes.reserve(size());
        for (auto&& name_node : *this)
        {
            out.nodes.emplace_back(std::get<0>(name_node), std::get<1>(name_node)->detach());
        }
        std::sort(begin(out), end(out), CompObject());
        return out;
    }

    void Ent::Object::resetInstanceOf(char const* _prefabNodePath)
    {
        auto const* entlib = schema->rootSchema->entityLib;
        if (_prefabNodePath == nullptr or strlen(_prefabNodePath) == 0)
        {
            Node prefabNode = entlib->loadNode(*schema, json{}, nullptr);
            (*this) = prefabNode.GetRawValue().get<Object>().makeInstanceOf();
            instanceOf.set("");
        }
        else
        {
            auto relPath = entlib->getRelativePath(_prefabNodePath).generic_u8string();
            json nodeData = loadJsonFile(entlib->rawdataPath, _prefabNodePath);
            Node prefabNode = entlib->loadNode(*schema, nodeData, nullptr);
            // Get the keyfield
            tl::optional<Node> keyField;
            for (auto&& name_field : nodes)
            {
                auto&& field = std::get<1>(name_field);
                if (field->getSchema()->isKeyField)
                {
                    if (keyField.has_value())
                    {
                        throw IllFormedSchema(
                            R"(An Object is used in two set with different keyField)");
                    }
                    keyField = *field;
                }
            }
            (*this) = prefabNode.GetRawValue().get<Object>().makeInstanceOf();
            // Set the keyField
            if (keyField.has_value())
            {
                for (auto&& name_field : nodes)
                {
                    auto&& field = std::get<1>(name_field);
                    if (field->getSchema()->isKeyField)
                    {
                        keyField->applyAllValues(*field, CopyMode::MinimalOverride);
                    }
                }
            }
            instanceOf.set(relPath);
        }
    }

    bool Object::hasOverride() const
    {
        if (instanceOf.hasOverride())
        {
            return true;
        }
        for (auto&& name_node : nodes)
        {
            if (std::get<1>(name_node)->hasOverride())
            {
                return true;
            }
        }
        return false;
    }

    bool Object::hasPrefabValue() const
    {
        if (instanceOf.hasPrefabValue())
        {
            return true;
        }
        for (auto&& name_node : nodes)
        {
            if (std::get<1>(name_node)->hasPrefabValue())
            {
                return true;
            }
        }
        return false;
    }

    void Ent::Object::setParentNode(Node* _parentNode)
    {
        for (auto&& [name, node] : nodes)
        {
            node->setParentNode(_parentNode);
        }
    }

    void Ent::Object::checkParent(Node const* _parentNode) const
    {
        for (auto&& [name, node] : nodes)
        {
            node->checkParent(_parentNode);
        }
    }

    void Object::computeMemory(MemoryProfiler& prof) const
    {
        prof.addMem("Object", nodes.capacity() * sizeof(front()));
        instanceOf.computeMemory(prof);
        for (auto&& name_node : nodes)
        {
            std::get<1>(name_node)->computeMemory(prof);
            prof.addMem("Object::value_ptr", sizeof(Ent::Node));
        }
        prof.addNodes(size());
    }

    size_t count(Object const& obj, char const* key)
    {
        auto range = std::equal_range(
            begin(obj), end(obj), std::pair<char const*, value_ptr<Node>>{key, nullptr}, CompObject());
        return (size_t)std::distance(range.first, range.second);
    }
    void emplace(Object& obj, std::pair<char const*, Node> const& value)
    {
        auto range = std::equal_range(begin(obj), end(obj), value, CompObject());
        if (range.first == range.second)
        {
            obj.nodes.insert(range.first, value);
        }
    }
    Node const& at(Object const& obj, char const* key)
    {
        auto range = std::equal_range(
            begin(obj), end(obj), std::pair<char const*, value_ptr<Node>>{key, nullptr}, CompObject());
        if (range.first == range.second)
        {
            throw std::logic_error(std::string("Bad key : ") + key);
        }
        else
        {
            return *range.first->second;
        }
    }
    Node& at(Object& obj, char const* key)
    {
        auto range = std::equal_range(
            begin(obj),
            end(obj),
            std::pair<char const*, value_ptr<Node>>{key, value_ptr<Node>()},
            CompObject());
        if (range.first == range.second)
        {
            throw std::logic_error(std::string("Bad key : ") + key);
        }
        else
        {
            return *range.first->second;
        }
    }
} // namespace Ent
