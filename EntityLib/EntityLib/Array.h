#pragma once

#include <cstdint>
#include <map>
#include <algorithm>
#include <optional>

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include <variant>
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

        [[nodiscard]] bool hasOverride() const; ///< Recursively check if there is an override inside
        [[nodiscard]] bool hasPrefabValue() const; ///< Recursively check if value is set in a prefab
        [[nodiscard]] bool
        hasDefaultValue() const; ///< Recursively check if nothing is set in prefab and instance
        [[nodiscard]] bool hasKey() const; ///< The elements have keys if the overridePolicy is a map or a set
        [[nodiscard]] bool isTuple() const; ///< @return true if the schema has linearItems

        Node* at(uint64_t _index); ///< Get the item at _index
        [[nodiscard]] Node const* at(uint64_t _index) const; ///< Get the item at _index

        Node* arrayPush(); ///< @pre not hasKey()

        [[nodiscard]] bool canErase() const; ///< Erase is allowed if it is a map or a set of union

        /// @brief Erase the item with _key, or return false
        /// @pre canErase()
        bool mapErase(Map::KeyType const& _key);
        Node* mapGet(Map::KeyType const& _key); ///< @return the item with _key, or nullptr
        [[nodiscard]] Node const*
        mapGet(Map::KeyType const& _key) const; ///< @return the item with _key, or nullptr
        Node* mapInsert(Map::KeyType const& _key); ///< @pre hasKey(). @brief Insert a new item with _key
        void mapInsert(Map::KeyType const& _key, NodeUniquePtr _newNode);
        Node* mapRename(Map::KeyType const& _key, Map::KeyType const& _newKey);

        /// @return true if it is a map/set and the element with _key was removed
        [[nodiscard]] bool isErased(Map::KeyType const& _key) const;

        [[nodiscard]] std::vector<Node const*> getItems() const; ///< Get all not removed items
        std::vector<Node*> getItems(); ///< Get all not removed items
        [[nodiscard]] std::vector<Node const*>
        getItemsWithRemoved() const; ///< Get all items with the removed ones

        std::vector<NodeUniquePtr> releaseAllElements();

        void pop(); ///< @pre not hasKey() and not isTuple()

        void clear(); ///< @pre not isTuple()

        [[nodiscard]] bool empty() const;

        [[nodiscard]] Array detach() const;
        [[nodiscard]] Array makeInstanceOf() const;

        void arraySetSize(Override<size_t> _size);

        void computeMemory(MemoryProfiler& _prof) const;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] size_t getDefaultSize() const;

        [[nodiscard]] size_t getPrefabSize() const;

        [[nodiscard]] Subschema const* getSchema() const;

        [[nodiscard]] std::optional<size_t> getRawSize(OverrideValueLocation _location) const;

        Map::KeyType getChildKey(Node const* _child) const;

        [[nodiscard]] DataType getKeyType() const;

        void unset(); ///< Unset recursively all values overriden in instance (return to prefab values)

        // **************************** For array initialization **********************************
        Node* initAdd(
            OverrideValueLocation /*loc*/,
            NodeUniquePtr _node,
            bool _addedInInstance); ///< @pre This _node is not yet added
        /// @pre hasKey() and the key doesn't exist in map
        Node* mapInitInsert(
            OverrideValueLocation /*_loc*/,
            Map::KeyType _key,
            NodeUniquePtr _node,
            bool _addedInInstance);
        /// @pre not hasKey()
        Node* arrayInitPush(NodeUniquePtr _node, bool _addedInInstance);

        void applyAllValues(Array& _dest, CopyMode _copyMode) const;

        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;

        [[nodiscard]] std::vector<String> getKeysString(bool _forceSort) const;
        [[nodiscard]] std::vector<int64_t> getKeysInt(bool _forceSort) const;

        /// Get the child name, in the array/map logic
        /// @pre _child is a child field of this
        NodeRef computeNodeRefToChild(Node const* _child) const;

    private:
        void checkInvariants() const;

        Subschema const* m_schema = nullptr;

        using MapOrVector = std::variant<Vector, Map>;
        MapOrVector m_data;
    };
    using ArrayPtr = std::unique_ptr<Array>;

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

    inline std::optional<size_t> Array::getRawSize(OverrideValueLocation _location) const
    {
        return std::visit([_location](auto& a) { return a.getRawSize(_location); }, m_data);
    }

    inline void Array::unset()
    {
        std::visit([&](auto& a) { a.unset(); }, m_data);
    }

    inline void Array::setParentNode(Node* _parent)
    {
        std::visit([&](auto& a) { a.setParentNode(_parent); }, m_data);
    }

    inline void Array::checkParent(Node const* _parent) const
    {
        std::visit([&](auto& a) { a.checkParent(_parent); }, m_data);
    }

    inline std::vector<String> Array::getKeysString(bool _forceSort) const
    {
        ENTLIB_ASSERT_MSG(
            std::holds_alternative<Map>(m_data), "Can only getKeysString on map or set");
        return std::get<Map>(m_data).getKeysString(_forceSort);
    }

    inline std::vector<int64_t> Array::getKeysInt(bool _forceSort) const
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only getKeysInt on map or set");
        return std::get<Map>(m_data).getKeysInt(_forceSort);
    }

    inline std::vector<NodeUniquePtr> Array::releaseAllElements()
    {
        return std::visit([&](auto& a) { return a.releaseAllElements(); }, m_data);
    }

    inline NodeRef Array::computeNodeRefToChild(Node const* _child) const
    {
        return std::visit([_child](auto& a) { return a.computeNodeRefToChild(_child); }, m_data);
    }

} // namespace Ent
