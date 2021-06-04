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

    struct Map
    {
        using KeyType = mapbox::util::variant<String, int64_t>;

        struct Element
        {
            value_ptr<Node> node;
            Override<bool> isPresent;

            bool hasOverride() const;
            bool hasPrefabValue() const;
            bool hasDefaultValue() const;
            Element makeInstanceOf() const;
        };

        EntityLib const* entlib = nullptr;
        Subschema const* schema = nullptr;
        std::vector<Element> items; ///< List of items of the array
        std::map<KeyType, size_t> itemMap;

        size_t size() const
        {
            return std::count_if(
                begin(items), end(items), [](auto&& d) { return d.isPresent.get(); });
        }

        size_t getDefaultSize() const
        {
            return std::count_if(
                begin(items), end(items), [](Element const& d) { return d.isPresent.defaultValue; });
        }

        size_t getPrefabSize() const
        {
            return std::count_if(
                begin(items), end(items), [](Element const& d) { return d.isPresent.getPrefab(); });
        }

        bool hasOverride() const;
        bool hasPrefabValue() const;
        bool hasDefaultValue() const;

        Node* at(uint64_t _index);
        Node const* at(uint64_t _index) const;

        bool erase(KeyType const& _key);
        Node const* get(KeyType const& _key) const;
        Ent::Node* insert(KeyType const& _key);
        bool isErased(KeyType const& _key) const;
        Ent::Node* insert(OverrideValueLocation loc, KeyType _key, Node _node);
        void checkInvariants() const;
        std::vector<Node const*> getItemsWithRemoved() const;
        std::vector<Node const*> getItems() const;
        void clear();
        void computeMemory(MemoryProfiler& prof) const;
        Map detach() const;
        Map makeInstanceOf() const;
        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;
        static KeyType getChildKey(Subschema const* _schema, Ent::Node const* _child);
    };

} // namespace Ent
