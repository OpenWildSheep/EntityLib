#pragma once

//#include <cstdint>
#include <map>
#include <algorithm>

#pragma warning(push, 0)
#pragma warning(disable : 4996)
#include "../../../external/mapbox/variant.hpp"
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
        using KeyType = mapbox::util::variant<String, int64_t>;

        explicit Map(EntityLib const* _entlib = nullptr, Subschema const* _schema = nullptr);

        struct Element
        {
            value_ptr<Node> node;
            Override<bool> isPresent;

            bool hasOverride() const;
            bool hasPrefabValue() const;
            bool hasDefaultValue() const;
            Element makeInstanceOf() const;
        };

        size_t size() const;

        size_t getDefaultSize() const;

        size_t getPrefabSize() const;

        bool hasOverride() const;
        bool hasPrefabValue() const;
        bool hasDefaultValue() const;

        Node* at(uint64_t _index);
        Node const* at(uint64_t _index) const;

        bool erase(KeyType const& _key);
        Node const* get(KeyType const& _key) const;
        Node* get(KeyType const& _key);
        Ent::Node* insert(KeyType const& _key);
        bool isErased(KeyType const& _key) const;
        Ent::Node* insert(OverrideValueLocation _loc, KeyType _key, Node _node, bool _addedInInstance);
        Ent::Node* rename(KeyType const& _key, KeyType const& _newKey);
        void checkInvariants() const;
        std::vector<Node const*> getItemsWithRemoved() const;
        std::vector<Node const*> getItems() const;
        void clear();
        void computeMemory(MemoryProfiler& _prof) const;
        Map detach() const;
        Map makeInstanceOf() const;
        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;
        static KeyType getChildKey(Subschema const* _schema, Ent::Node const* _child);
        static DataType getKeyType(Subschema const* _schema);
        void unset();
        void applyAllValues(Map& _dest, CopyMode _copyMode) const;
        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;

        std::vector<String> getKeysString() const;
        std::vector<int64_t> getKeysInt() const;

    private:
        Element& insertImpl(KeyType const& _key);
        Element& insertImpl(OverrideValueLocation _loc, KeyType _key, Node _node, bool _addedInInstance);

        EntityLib const* m_entlib = nullptr;
        Subschema const* m_schema = nullptr;
        std::vector<Element> m_items; ///< List of items of the array
        std::map<KeyType, size_t> m_itemMap;
    };

} // namespace Ent
