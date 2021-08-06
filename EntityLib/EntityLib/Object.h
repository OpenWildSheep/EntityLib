#pragma once

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Override.h"
#pragma warning(pop)

#include "include/Schema.h"

namespace Ent
{
    struct Node;

    struct ObjField
    {
        char const* name = nullptr;
        value_ptr<Node> node;
        uint32_t fieldIdx = 0;
    };

    struct CompObject
    {
        bool operator()(ObjField const& a, ObjField const& b) const
        {
            return strcmp(a.name, b.name) < 0;
        }
    };

    /// Content of a Node which has type Ent::DataType::object
    struct Object
    {
        Object(Subschema const* _schema)
            : schema(_schema)
        {
        }

        Subschema const* schema{};
        std::vector<ObjField> nodes;
        Override<Ent::String> instanceOf;
        uint32_t instanceOfFieldIndex = 0;
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

        ObjField const& at(char const* key) const
        {
            auto range =
                std::equal_range(begin(nodes), end(nodes), ObjField{key, nullptr, 0}, CompObject());
            if (range.first == range.second)
            {
                throw std::logic_error(std::string("Bad key : ") + key);
            }
            else
            {
                return *range.first;
            }
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
