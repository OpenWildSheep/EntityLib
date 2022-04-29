#pragma once

#pragma warning(push)
#pragma warning(disable : 4464)
#include "Override.h"
#pragma warning(pop)

#include "include/Schema.h"

namespace Ent
{
    struct Node;

    struct ObjField
    {
        char const* name = nullptr;
        NodeUniquePtr node;
        uint32_t fieldIdx = 0;

        explicit ObjField(char const* _name = nullptr, NodeUniquePtr _node = {}, uint32_t _fieldIdx = 0)
            : name(_name)
            , node(std::move(_node))
            , fieldIdx(_fieldIdx)
        {
        }

        ObjField(ObjField const& _other);
        ObjField(ObjField&&) = default;
        ObjField& operator=(ObjField const& _other);
        ObjField& operator=(ObjField&&) = default;
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
        Object(
            Subschema const* _schema,
            std::vector<ObjField> _nodes,
            Override<String> _instanceOf = {},
            uint32_t _instanceOfFieldIndex = 0,
            bool _hasASuper = false)
            : schema(_schema)
            , nodes(std::move(_nodes))
            , instanceOf(std::move(_instanceOf))
            , instanceOfFieldIndex(_instanceOfFieldIndex)
            , hasASuper(_hasASuper)
        {
            ENTLIB_ASSERT(schema != nullptr);
            ENTLIB_ASSERT(nodes.size() == schema->properties.size());
        }

        Object(Object const& _other) = default;
        Object(Object&&) = default;
        Object& operator=(Object const& _other) = default;
        Object& operator=(Object&&) = default;

        Subschema const* schema{};
        std::vector<ObjField> nodes;
        Override<String> instanceOf;
        uint32_t instanceOfFieldIndex = 0;
        bool hasASuper = false;

        [[nodiscard]] size_t size() const
        {
            return nodes.size();
        }

        [[nodiscard]] auto& front() const
        {
            return nodes.front();
        }

        void unset() const;
        void resetInstanceOf(char const* _prefabNodePath);
        [[nodiscard]] Object makeInstanceOf() const;
        [[nodiscard]] Object detach() const;
        void applyAllValues(Object& _dest, CopyMode _copyMode) const;
        void applyAllValuesButPrefab(Object& _dest, CopyMode _copyMode) const;

        [[nodiscard]] Override<String> const& getInstanceOfValue() const
        {
            return instanceOf;
        }

        [[nodiscard]] bool hasDefaultValue() const;

        [[nodiscard]] bool hasOverride() const;
        [[nodiscard]] bool hasPrefabValue() const;

        void computeMemory(MemoryProfiler& prof) const;

        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;

        ObjField const& at(char const* key) const
        {
            if (key == nullptr)
            {
                throw NullPointerArgument("key", "");
            }
            auto const range =
                std::equal_range(begin(nodes), end(nodes), ObjField{key, nullptr, 0}, CompObject());
            if (range.first == range.second)
            {
                throw BadKey(key, "at", schema->name.c_str());
            }
            return *range.first;
        }

        ObjField& at(char const* key)
        {
            return const_cast<ObjField&>(std::as_const(*this).at(key));
        }

        /// Get the name of the field pointing to \b _child
        /// @pre \b _child is a child field of this
        NodeRef computeNodeRefToChild(Node const* _child) const;
    };
    using ObjectPtr = std::unique_ptr<Object>;

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
    void applyInstanceOfField(T const& _source, T& _dest, CopyMode _copyMode)
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
