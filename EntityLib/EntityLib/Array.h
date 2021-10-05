#pragma once

#include <cstdint>
#include <map>
#include <algorithm>

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include <variant>
#include "../external/optional.hpp"
#pragma warning(pop)

#include "include/EntityLibCore.h"
#include "Override.h"
#include "Map.h"
#include "Vector.h"
#include "include/Schema.h"

namespace Ent
{
    struct Node;
    struct Subschema;
    class EntityLib;

    /// Content of a Node which has type Ent::DataType::array
    struct Array
    {
        Array(EntityLib const* _entlib, Subschema const* _schema);
        Array(Array const& _other) = default;
        Array(Array&&) = default;
        Array& operator=(Array const&) = default;
        Array& operator=(Array&&) = default;

        bool hasOverride() const; ///< Recursively check if there is an override inside
        bool hasPrefabValue() const; ///< Recursively check if value is set in a prefab
        bool hasDefaultValue() const; ///< Recursively check if nothing is set in prefab and instance
        bool hasKey() const; ///< The elements have keys if the overridePolicy is a map or a set
        bool isTuple() const; ///< @return true if the schema has linearItems

        Node* at(uint64_t _index); ///< Get the item at _index
        Node const* at(uint64_t _index) const; ///< Get the item at _index

        Node* arrayPush(); ///< @pre not hasKey()

        bool canErase() const; ///< Erase is allowed if it is a map or a set of union

        /// @brief Erase the item with _key, or return false
        /// @pre canErase()
        bool mapErase(Map::KeyType const& _key);
        Node* mapGet(Map::KeyType const& _key); ///< @return the item with _key, or nullptr
        Node const* mapGet(Map::KeyType const& _key) const; ///< @return the item with _key, or nullptr
        Node* mapInsert(Map::KeyType const& _key); ///< @pre hasKey(). @brief Insert a new item with _key
        Node* mapRename(Map::KeyType const& _key, Map::KeyType const& _newKey);

        /// @return true if it is a map/set and the element with _key was removed
        bool isErased(Map::KeyType const& _key) const;

        std::vector<Node const*> getItems() const; ///< Get all not removed items
        std::vector<Node*> getItems(); ///< Get all not removed items
        std::vector<Node const*> getItemsWithRemoved() const; ///< Get all items with the removed ones

        void pop(); ///< @pre not hasKey() and not isTuple()

        void clear(); ///< @pre not isTuple()

        bool empty() const;

        Array detach() const;
        Array makeInstanceOf() const;

        void arraySetSize(Override<size_t> _size);

        void computeMemory(MemoryProfiler& _prof) const;

        size_t size() const;

        size_t getDefaultSize() const;

        size_t getPrefabSize() const;

        Subschema const* getSchema() const;

        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;

        Ent::Map::KeyType getChildKey(Ent::Node const* _child) const;

        Ent::DataType getKeyType() const;

        void unset(); ///< Unset recursively all values overriden in instance (return to prefab values)

        // **************************** For array initialization **********************************
        Node* initAdd(
            OverrideValueLocation,
            std::unique_ptr<Node> _node,
            bool _addedInInstance); ///< @pre This _node is not yet added
        /// @pre hasKey() and the key doesn't exist in map
        Node* mapInitInsert(
            OverrideValueLocation,
            Map::KeyType _key,
            std::unique_ptr<Node> _node,
            bool _addedInInstance);
        /// @pre not hasKey()
        Node* arrayInitPush(std::unique_ptr<Node> _node, bool _addedInInstance);

        void applyAllValues(Array& _dest, CopyMode _copyMode) const;

        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;

        std::vector<String> getKeysString() const;
        std::vector<int64_t> getKeysInt() const;

    private:
        void checkInvariants() const;

        Subschema const* m_schema = nullptr;

        using MapOrVector = std::variant<Vector, Map>;
        MapOrVector m_data;
    };

    inline size_t Array::size() const
    {
        return std::visit([](auto& a) { return a.size(); }, m_data);
    }

    inline size_t Array::getDefaultSize() const
    {
        return std::visit([](auto& a) { return a.getDefaultSize(); }, m_data);
    }

    inline size_t Array::getPrefabSize() const
    {
        return std::visit([](auto& a) { return a.getPrefabSize(); }, m_data);
    }

    inline Subschema const* Array::getSchema() const
    {
        return m_schema;
    }

    inline tl::optional<size_t> Array::getRawSize(OverrideValueLocation _location) const
    {
        return std::visit([_location](auto& a) { return a.getRawSize(_location); }, m_data);
    }

    inline void Ent::Array::unset()
    {
        std::visit([&](auto& a) { a.unset(); }, m_data);
    }

    inline void Ent::Array::setParentNode(Node* _parent)
    {
        std::visit([&](auto& a) { a.setParentNode(_parent); }, m_data);
    }

    inline void Ent::Array::checkParent(Node const* _parent) const
    {
        std::visit([&](auto& a) { a.checkParent(_parent); }, m_data);
    }

    inline std::vector<String> Ent::Array::getKeysString() const
    {
        ENTLIB_ASSERT_MSG(
            std::holds_alternative<Map>(m_data), "Can only getKeysString on map or set");
        return std::get<Map>(m_data).getKeysString();
    }

    inline std::vector<int64_t> Ent::Array::getKeysInt() const
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only getKeysInt on map or set");
        return std::get<Map>(m_data).getKeysInt();
    }

} // namespace Ent
