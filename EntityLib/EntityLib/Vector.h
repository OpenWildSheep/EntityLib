#pragma once

//#include <cstdint>
#include <map>
#include <algorithm>

#pragma warning(push, 0)
#pragma warning(disable : 4996)
// #include "../external/optional.hpp"
#include "../../../external/mapbox/variant.hpp"
#pragma warning(pop)

#include "include/EntityLibCore.h"
#include "Override.h"

namespace Ent
{
    struct Node;
    struct Subschema;
    class EntityLib;

    struct Vector
    {
        EntityLib const* entlib = nullptr;
        Subschema const* schema = nullptr;
        std::vector<value_ptr<Node>> data; ///< List of items of the array
        Override<uint64_t> arraySize; ///< Size of the array, to keep track on array size changes

        size_t size() const
        {
            return arraySize.get();
        }

        size_t getDefaultSize() const
        {
            return arraySize.defaultValue;
        }

        size_t getPrefabSize() const
        {
            return arraySize.getPrefab();
        }

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
        void addRemovedDefault(OverrideValueLocation _removedIn);
        // Node* push(OverrideValueLocation loc);
        void computeMemory(MemoryProfiler& prof) const;
        Node* push();
        Node* initPush(Node _node);
        Vector detach() const;
        Vector makeInstanceOf() const;
        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;
    };
} // namespace Ent
