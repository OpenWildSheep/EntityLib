#pragma once

#include <cstdint>
#include <map>
#include <algorithm>

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include "../external/optional.hpp"
#include "../../../external/mapbox/variant.hpp"
#pragma warning(pop)

#include "include/EntityLibCore.h"
#include "Override.h"
#include "Map.h"
#include "Vector.h"

namespace Ent
{
    struct Node;
    struct Subschema;
    class EntityLib;

    /// Content of a Node which has type Ent::DataType::array
    struct Array
    {
        Array(EntityLib const* _entlib, Subschema const* _schema);

        bool hasOverride() const; ///< Recursively check if there is an override inside
        bool hasPrefabValue() const; ///< Recursively check if value is set in a prefab
        bool hasDefaultValue() const; ///< Recursively check if nothing is set in prefab and instance
        bool hasKey() const; ///< The elements have keys if the overridePolicy is a map or a set
        bool isTuple() const; ///< @return true if the schema has linearItems

        Node* at(uint64_t _index); ///< Get the item at _index
        Node const* at(uint64_t _index) const; ///< Get the item at _index

        Node* arrayPush(); ///< @pre not hasKey()

        bool mapErase(Map::KeyType const& _key); ///< Erase the item with _key, or return false
        Node* mapGet(Map::KeyType const& _key); ///< @return the item with _key, or nullptr
        Node const* mapGet(Map::KeyType const& _key) const; ///< @return the item with _key, or nullptr
        Node* mapInsert(Map::KeyType const& _key); ///< @pre hasKey(). @brief Insert a new item with _key

        /// @return true if it is a map/set and the element with _key was removed
        bool isErased(Map::KeyType const& _key) const;

        std::vector<Node const*> getItems() const; ///< Get all not removed items
        std::vector<Node const*> getItemsWithRemoved() const; ///< Get all items with the removed ones

        void pop(); ///< @pre not hasKey() and not isTuple()

        void clear(); //< @pre not isTuple()

        bool empty() const;

        Array detach() const;
        Array makeInstanceOf() const;

        void arraySetSize(Override<size_t> _size);

        void computeMemory(MemoryProfiler& prof) const;

        size_t size() const
        {
            return mapbox::util::apply_visitor([](auto& a) { return a.size(); }, data);
        }

        size_t getDefaultSize() const
        {
            return mapbox::util::apply_visitor([](auto& a) { return a.getDefaultSize(); }, data);
        }

        size_t getPrefabSize() const
        {
            return mapbox::util::apply_visitor([](auto& a) { return a.getPrefabSize(); }, data);
        }

        Subschema const* getSchema() const
        {
            return schema;
        }

        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const
        {
            return mapbox::util::apply_visitor(
                [_location](auto& a) { return a.getRawSize(_location); }, data);
        }

        Ent::Map::KeyType getChildKey(Ent::Node const* _child) const;

        // **************************** For array initialization **********************************
        Node* initAdd(OverrideValueLocation, Node _node); ///< @pre This _node is not yet added
        /// @pre hasKey() and the key doesn't exist in map
        Node* mapInitInsert(OverrideValueLocation, Map::KeyType _key, Node _node);
        /// @pre not hasKey()
        Node* arrayInitPush(Node _node);

    private:
        void checkInvariants() const;

        Subschema const* schema = nullptr;

        using MapOrVector = mapbox::util::variant<Vector, Map>;
        MapOrVector data;
    };

} // namespace Ent
