#pragma once

//#include <cstdint>
#include <map>
#include <algorithm>

#pragma warning(push, 0)
#include <variant>
#pragma warning(pop)

#include "include/EntityLibCore.h"
#include "include/Schema.h"
#include "Override.h"

namespace Ent
{
    struct Node;
    struct Subschema;
    class EntityLib;

    /// Storage of an Array which has the overridePolicy map or set
    struct Map
    {
        using KeyType = std::variant<String, int64_t>;

        explicit Map(EntityLib const* _entlib = nullptr, Subschema const* _schema = nullptr);
        Map(Map const& _other);
        Map(Map&&) noexcept = default;
        Map& operator=(Map const& _other);
        Map& operator=(Map&&) = default;

        struct Element
        {
            NodeUniquePtr node;
            Override<bool> isPresent;

            explicit Element(NodeUniquePtr _node = {})
                : node(std::move(_node))
            {
            }
            Element(Element const& _other);
            Element(Element&&) = default;
            Element& operator=(Element const& _other);
            Element& operator=(Element&&) = default;

            [[nodiscard]] bool hasOverride() const;
            [[nodiscard]] bool hasPrefabValue() const;
            [[nodiscard]] bool hasDefaultValue() const;
            [[nodiscard]] Element makeInstanceOf() const;
        };

        [[nodiscard]] size_t size() const;

        [[nodiscard]] size_t getDefaultSize() const;

        [[nodiscard]] size_t getPrefabSize() const;

        [[nodiscard]] bool hasOverride() const;
        [[nodiscard]] bool hasPrefabValue() const;
        [[nodiscard]] bool hasDefaultValue() const;

        Node* at(uint64_t _index);
        [[nodiscard]] Node const* at(uint64_t _index) const;

        bool erase(KeyType const& _key);
        [[nodiscard]] Node const* get(KeyType const& _key) const;
        Node* get(KeyType const& _key);
        Node* insert(KeyType const& _key);
        void insert(KeyType const& _key, NodeUniquePtr _newNode);
        [[nodiscard]] bool isErased(KeyType const& _key) const;
        Node*
        insert(OverrideValueLocation _loc, KeyType _key, NodeUniquePtr _node, bool _addedInInstance);
        Node* rename(KeyType const& _key, KeyType const& _newKey);
        void checkInvariants() const;
        [[nodiscard]] std::vector<Node const*> getItemsWithRemoved() const;
        [[nodiscard]] std::vector<Node const*> getItems() const;
        std::vector<Node*> getItems();
        void clear();
        void computeMemory(MemoryProfiler& _prof) const;
        [[nodiscard]] Map detach() const;
        [[nodiscard]] Map makeInstanceOf() const;
        [[nodiscard]] std::optional<size_t> getRawSize(OverrideValueLocation _location) const;
        static KeyType getChildKey(Subschema const* _schema, Node const* _child);
        static DataType getKeyType(Subschema const* _schema);
        void unset();
        void applyAllValues(Map& _dest, CopyMode _copyMode) const;
        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;
        std::vector<NodeUniquePtr> releaseAllElements();

        [[nodiscard]] std::vector<String> getKeysString(bool _forceSort) const;
        [[nodiscard]] std::vector<int64_t> getKeysInt(bool _forceSort) const;
        [[nodiscard]] EntityLib const* getEntityLib() const;

        /// Get the key containing this \b _child node
        /// @pre \b _child is a child field of this map
        NodeRef computeNodeRefToChild(Node const* _child) const;

    private:
        Element& insertImpl(KeyType const& _key, NodeUniquePtr _newNode = {});
        Element& insertImpl(
            OverrideValueLocation _loc, KeyType _key, NodeUniquePtr _node, bool _addedInInstance);
        template <typename M>
        static auto getItemsImpl(M* self);

        EntityLib const* m_entlib = nullptr;
        Subschema const* m_schema = nullptr;
        std::vector<Element> m_items; ///< List of items of the array
        std::map<KeyType, size_t> m_itemMap;
        Node* m_parentNode = nullptr;
    };

} // namespace Ent
