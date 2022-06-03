#include "Array.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "include/Schema.h"
#include "Tools.h"
#include "Map.h"

using namespace nlohmann;

namespace Ent
{

    Array::Array(EntityLib const* _entlib, Subschema const* _schema)
        : m_schema(_schema)
    {
        if (hasKey())
        {
            m_data = Map{_entlib, _schema};
        }
        else
        {
            m_data = Vector{_entlib, _schema};
        }
        ENTLIB_ASSERT(m_schema != nullptr);
    }

    Map::KeyType Array::getChildKey(Node const* _child) const
    {
        return Map::getChildKey(m_schema, _child);
    }

    DataType Array::getKeyType() const
    {
        return Map::getKeyType(m_schema);
    }

    Node* Array::at(uint64_t _index)
    {
        return std::visit([_index](auto& a) { return a.at(_index); }, m_data);
    }

    Node const* Array::at(uint64_t _index) const
    {
        return std::visit([_index](auto const& a) { return a.at(_index); }, m_data);
    }

    bool Array::isErased(Map::KeyType const& _key) const
    {
        ENTLIB_ASSERT(std::holds_alternative<Map>(m_data));
        return std::get<Map>(m_data).isErased(_key);
    }

    bool Array::canErase() const
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(m_schema->meta);
        if (meta.overridePolicy == "map")
        {
            return true;
        }
        if (meta.overridePolicy != "set")
        {
            return false;
        }
        // If it is a set, it has a singularItems.
        // Can erase only if item is a oneOf or an Object with a keyField.
        return getSchema()->singularItems->get().type == DataType::oneOf or meta.keyField.has_value();
    }

    bool Array::mapErase(Map::KeyType const& _key)
    {
        ENTLIB_ASSERT_MSG(canErase(), "Can only erase in a map or a set of union");
        return std::get<Map>(m_data).erase(_key);
    }

    Node* Array::mapGet(Map::KeyType const& _key)
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only mapGet on map or set");
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Node*>(std::get<Map>(std::as_const(*this).m_data).get(_key));
    }
    Node const* Array::mapGet(Map::KeyType const& _key) const
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only mapGet on map or set");
        return std::get<Map>(m_data).get(_key);
    }
    Node* Array::mapInsert(Map::KeyType const& _key)
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only mapInsert on map or set");
        return std::get<Map>(m_data).insert(_key);
    }

    void Array::mapInsert(Map::KeyType const& _key, NodeUniquePtr _newNode)
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only mapInsert on map or set");
        std::get<Map>(m_data).insert(_key, std::move(_newNode));
    }

    Node* Array::mapRename(Map::KeyType const& _key, Map::KeyType const& _newKey)
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only mapRename on map or set");
        return std::get<Map>(m_data).rename(_key, _newKey);
    }

    bool Array::hasKey() const
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(m_schema->meta);
        return meta.overridePolicy == "map" || meta.overridePolicy == "set";
    }

    bool Array::isTuple() const
    {
        if (not std::holds_alternative<Vector>(m_data))
        {
            return false;
        }
        return std::get<Vector>(m_data).isTuple();
    }

    Node* Array::initAdd(OverrideValueLocation _loc, NodeUniquePtr _node, bool _addedInInstance)
    {
        if (hasKey())
        {
            auto const key = getChildKey(_node.get());
            return std::get<Map>(m_data).insert(_loc, key, std::move(_node), _addedInInstance);
        }
        return std::get<Vector>(m_data).initPush(std::move(_node), _addedInInstance);
    }

    Node* Array::mapInitInsert(
        OverrideValueLocation _loc, Map::KeyType _key, NodeUniquePtr _node, bool _addedInInstance)
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Map>(m_data), "Can only mapInsert on map or set");
        return std::get<Map>(m_data).insert(
            _loc, std::move(_key), std::move(_node), _addedInInstance);
    }

    std::vector<Node const*> Array::getItemsWithRemoved() const
    {
        ENTLIB_ASSERT_MSG(
            std::holds_alternative<Map>(m_data), "Can only getItemsWithRemoved on map or set");
        return std::get<Map>(m_data).getItemsWithRemoved();
    }

    std::vector<Node const*> Array::getItems() const
    {
        return std::visit([](auto&& a) -> std::vector<Node const*> { return a.getItems(); }, m_data);
    }

    std::vector<Node*> Array::getItems()
    {
        return std::visit([](auto& a) { return a.getItems(); }, m_data);
    }

    void Array::checkInvariants() const
    {
        return std::visit([](auto& a) { return a.checkInvariants(); }, m_data);
    }

    bool Array::hasOverride() const
    {
        return std::visit([](auto& a) { return a.hasOverride(); }, m_data);
    }

    bool Array::hasPrefabValue() const
    {
        return std::visit([](auto& a) { return a.hasPrefabValue(); }, m_data);
    }

    bool Array::hasDefaultValue() const
    {
        return std::visit([](auto& a) { return a.hasDefaultValue(); }, m_data);
    }

    void Array::pop()
    {
        ENTLIB_ASSERT_MSG(std::holds_alternative<Vector>(m_data), "Can only 'pop' on simple array");
        std::get<Vector>(m_data).pop();
    }

    void Array::clear()
    {
        std::visit([](auto& a) { return a.clear(); }, m_data);
    }

    bool Array::empty() const
    {
        return size() == 0;
    }

    Array Array::detach() const
    {
        auto const* const entitylib = std::visit([](auto& a) { return a.getEntityLib(); }, m_data);
        Array result{entitylib, m_schema};
        result.m_data = std::visit([](auto& a) { return MapOrVector(a.detach()); }, m_data);
        result.checkInvariants();
        return result;
    }

    Array Array::makeInstanceOf() const
    {
        auto const* const entitylib = std::visit([](auto& a) { return a.getEntityLib(); }, m_data);
        Array result{entitylib, m_schema};
        result.m_data = std::visit([](auto& a) { return MapOrVector(a.makeInstanceOf()); }, m_data);
        return result;
    }

    void Array::arraySetSize(Override<size_t> _size)
    {
        ENTLIB_ASSERT_MSG(
            std::holds_alternative<Vector>(m_data), "Can only 'arraySetSize' on simple array");
        std::get<Vector>(m_data).setSize(_size);
    }

    void Array::computeMemory(MemoryProfiler& _prof) const
    {
        std::visit([&_prof](auto& a) { return a.computeMemory(_prof); }, m_data);
    }

    Node* Array::arrayInitPush(NodeUniquePtr _node, bool _addedInInstance)
    {
        ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
        return std::get<Vector>(m_data).initPush(std::move(_node), _addedInInstance);
    }

    void Array::applyAllValues(Array& _dest, CopyMode _copyMode) const
    {
        std::visit(
            [pref = &_dest, _copyMode](auto&& a)
            {
                using PrefabType = std::remove_cv_t<std::remove_reference_t<decltype(a)>>;
                a.applyAllValues(std::get<PrefabType>(pref->m_data), _copyMode);
            },
            m_data);
    }

    Node* Array::arrayPush()
    {
        ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
        return std::get<Vector>(m_data).push();
    }

} // namespace Ent
