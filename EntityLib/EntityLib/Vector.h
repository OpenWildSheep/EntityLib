#pragma once

//#include <cstdint>
#include <map>
#include <algorithm>

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include "../../../external/mapbox/variant.hpp"
#pragma warning(pop)

#include "include/EntityLibCore.h"
#include "Override.h"

namespace Ent
{
    struct Node;
    struct Subschema;
    class EntityLib;

    /// Storage of an Array which has no overridePolicy (simple array or tuple)
    struct Vector
    {
        explicit Vector(EntityLib const* _entlib = nullptr, Subschema const* _schema = nullptr);

        size_t size() const;

        size_t getDefaultSize() const;

        size_t getPrefabSize() const;

        bool hasOverride() const;
        bool hasPrefabValue() const;
        bool hasDefaultValue() const;
        Node* at(uint64_t _index);
        Node const* at(uint64_t _index) const;
        void checkInvariants() const;
        std::vector<Node const*> getItems() const;
        void pop();
        bool isTuple() const;
        void clear();
        void computeMemory(MemoryProfiler& prof) const;
        Node* push();
        Node* initPush(Node _node);
        Vector detach() const;
        Vector makeInstanceOf() const;
        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;
        void unset();
        void setSize(Override<size_t> _size);
        void applyAllValues(Vector& _dest, CopyMode _copyMode) const;
        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;

    private:
        EntityLib const* m_entlib = nullptr;
        Subschema const* m_schema = nullptr;
        std::vector<value_ptr<Node>> m_data; ///< List of items of the array
        Override<uint64_t> m_arraySize; ///< Size of the array, to keep track on array size changes
    };
} // namespace Ent
