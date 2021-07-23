#pragma once

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Override.h"
#pragma warning(pop)

#include "include/Schema.h"

namespace Ent
{
    struct Node;

    /// Content of a Node which has type Ent::DataType::object
    struct Object
    {
        Object(Subschema const* _schema)
            : schema(_schema)
        {
        }

        Subschema const* schema{};
        std::vector<std::pair<char const*, value_ptr<Node>>> nodes;
        Override<Ent::String> instanceOf;
        bool hasASuper = false;

        size_t size() const
        {
            return nodes.size();
        }

        auto& front() const
        {
            return nodes.front();
        }

        void unset();
        void resetInstanceOf(char const* _prefabNodePath);
        Object makeInstanceOf() const;
        Object detach() const;
        void applyAllValues(Object& _dest, CopyMode _copyMode) const;
        Override<String> const& getInstanceOfValue() const
        {
            return instanceOf;
        }

        bool hasDefaultValue() const;

        bool hasOverride() const;
        bool hasPrefabValue() const;

        void computeMemory(MemoryProfiler& prof) const;

        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;
    };

    struct CompObject
    {
        bool operator()(
            std::pair<char const*, value_ptr<Node>> const& a,
            std::pair<char const*, value_ptr<Node>> const& b) const
        {
            return strcmp(a.first, b.first) < 0;
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

    // For Entity and Object. Decide to resetInstanceOf or not depending on \b _copyMode
    template <typename T>
    void applyInstanceOfField(T const& _source, T& _dest, Ent::CopyMode _copyMode)
    {
        auto sourcePrefabPath = _source.getInstanceOfValue().get().c_str();
        if (_source.getInstanceOfValue().get() != _dest.getInstanceOfValue().get())
        {
            _dest.resetInstanceOf(sourcePrefabPath == nullptr ? "" : sourcePrefabPath);
        }
        else if (_copyMode == CopyMode::CopyOverride)
        {
            if (_source.getInstanceOfValue().isSet() && !_dest.getInstanceOfValue().isSet())
            {
                _dest.resetInstanceOf(sourcePrefabPath == nullptr ? "" : sourcePrefabPath);
            }
        }
    }

    size_t count(Object const& obj, char const* key);
    void emplace(Object& obj, std::pair<char const*, Node> const& value);
    Node const& at(Object const& obj, char const* key);
    Node& at(Object& obj, char const* key);

} // namespace Ent
