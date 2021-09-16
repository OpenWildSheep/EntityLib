#include "Array.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "include/Schema.h"
#include "Tools.h"
#include "Map.h"

using namespace nlohmann;
using namespace mapbox::util;

Ent::Array::Array(EntityLib const* _entlib, Subschema const* _schema)
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

Ent::Map::KeyType Ent::Array::getChildKey(Ent::Node const* _child) const
{
    return Map::getChildKey(m_schema, _child);
}

Ent::DataType Ent::Array::getKeyType() const
{
    return Map::getKeyType(m_schema);
}

Ent::Node* Ent::Array::at(uint64_t _index)
{
    return apply_visitor([_index](auto& a) { return a.at(_index); }, m_data);
}

Ent::Node const* Ent::Array::at(uint64_t _index) const
{
    return apply_visitor([_index](auto const& a) { return a.at(_index); }, m_data);
}

bool Ent::Array::isErased(Map::KeyType const& _key) const
{
    ENTLIB_ASSERT(m_data.is<Map>());
    return m_data.get<Map>().isErased(_key);
}

bool Ent::Array::canErase() const
{
    auto&& meta = m_schema->meta.get<Ent::Subschema::ArrayMeta>();
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
    return getSchema()->singularItems->get().type == Ent::DataType::oneOf
           or meta.keyField.has_value();
}

bool Ent::Array::mapErase(Map::KeyType const& _key)
{
    ENTLIB_ASSERT_MSG(canErase(), "Can only erase in a map or a set of union");
    return m_data.get<Map>().erase(_key);
}

Ent::Node* Ent::Array::mapGet(Map::KeyType const& _key)
{
    ENTLIB_ASSERT_MSG(m_data.is<Map>(), "Can only mapGet on map or set");
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<Ent::Node*>(std::as_const(*this).m_data.get<Map>().get(_key));
}
Ent::Node const* Ent::Array::mapGet(Map::KeyType const& _key) const
{
    ENTLIB_ASSERT_MSG(m_data.is<Map>(), "Can only mapGet on map or set");
    return m_data.get<Map>().get(_key);
}
Ent::Node* Ent::Array::mapInsert(Map::KeyType const& _key)
{
    ENTLIB_ASSERT_MSG(m_data.is<Map>(), "Can only mapInsert on map or set");
    return m_data.get<Map>().insert(_key);
}

Ent::Node* Ent::Array::mapRename(Map::KeyType const& _key, Map::KeyType const& _newKey)
{
    ENTLIB_ASSERT_MSG(m_data.is<Map>(), "Can only mapRename on map or set");
    return m_data.get<Map>().rename(_key, _newKey);
}

bool Ent::Array::hasKey() const
{
    auto&& meta = m_schema->meta.get<Ent::Subschema::ArrayMeta>();
    return meta.overridePolicy == "map" || meta.overridePolicy == "set";
}

bool Ent::Array::isTuple() const
{
    if (not m_data.is<Vector>())
    {
        return false;
    }
    return m_data.get<Vector>().isTuple();
}

Ent::Node* Ent::Array::initAdd(OverrideValueLocation loc, Node _node, bool _addedInInstance)
{
    if (hasKey())
    {
        auto key = getChildKey(&_node);
        return m_data.get<Map>().insert(loc, key, std::move(_node), _addedInInstance);
    }
    else
    {
        return m_data.get<Vector>().initPush(std::move(_node), _addedInInstance);
    }
}

Ent::Node* Ent::Array::mapInitInsert(
    OverrideValueLocation _loc, Map::KeyType _key, Node _node, bool _addedInInstance)
{
    ENTLIB_ASSERT_MSG(m_data.is<Map>(), "Can only mapInsert on map or set");
    return m_data.get<Map>().insert(_loc, std::move(_key), std::move(_node), _addedInInstance);
}

std::vector<Ent::Node const*> Ent::Array::getItemsWithRemoved() const
{
    ENTLIB_ASSERT_MSG(m_data.is<Map>(), "Can only getItemsWithRemoved on map or set");
    return m_data.get<Map>().getItemsWithRemoved();
}

std::vector<Ent::Node const*> Ent::Array::getItems() const
{
    return apply_visitor(
        [](auto&& a) -> std::vector<Ent::Node const*> { return a.getItems(); }, m_data);
}

std::vector<Ent::Node*> Ent::Array::getItems()
{
    return apply_visitor([](auto& a) { return a.getItems(); }, m_data);
}

void Ent::Array::checkInvariants() const
{
    return apply_visitor([](auto& a) { return a.checkInvariants(); }, m_data);
}

bool Ent::Array::hasOverride() const
{
    return apply_visitor([](auto& a) { return a.hasOverride(); }, m_data);
}

bool Ent::Array::hasPrefabValue() const
{
    return apply_visitor([](auto& a) { return a.hasPrefabValue(); }, m_data);
}

bool Ent::Array::hasDefaultValue() const
{
    return apply_visitor([](auto& a) { return a.hasDefaultValue(); }, m_data);
}

void Ent::Array::pop()
{
    ENTLIB_ASSERT_MSG(m_data.is<Vector>(), "Can only 'pop' on simple array");
    m_data.get<Vector>().pop();
}

void Ent::Array::clear()
{
    apply_visitor([](auto& a) { return a.clear(); }, m_data);
}

bool Ent::Array::empty() const
{
    return size() == 0;
}

Ent::Array Ent::Array::detach() const
{
    Array result{nullptr, m_schema};
    result.m_data = apply_visitor([](auto& a) { return MapOrVector(a.detach()); }, m_data);
    result.checkInvariants();
    return result;
}

Ent::Array Ent::Array::makeInstanceOf() const
{
    Array result{nullptr, m_schema};
    result.m_data = apply_visitor([](auto& a) { return MapOrVector(a.makeInstanceOf()); }, m_data);
    return result;
}

void Ent::Array::arraySetSize(Override<size_t> _size)
{
    ENTLIB_ASSERT_MSG(m_data.is<Vector>(), "Can only 'arraySetSize' on simple array");
    m_data.get<Vector>().setSize(_size);
}

void Ent::Array::computeMemory(MemoryProfiler& _prof) const
{
    apply_visitor([&_prof](auto& a) { return a.computeMemory(_prof); }, m_data);
}

Ent::Node* Ent::Array::arrayInitPush(Node _node, bool _addedInInstance)
{
    ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
    return m_data.get<Vector>().initPush(std::move(_node), _addedInInstance);
}

void Ent::Array::applyAllValues(Array& _dest, CopyMode _copyMode) const
{
    apply_visitor(
        [pref = &_dest, _copyMode](auto&& a) {
            using PrefabType = std::remove_cv_t<std::remove_reference_t<decltype(a)>>;
            a.applyAllValues(pref->m_data.get<PrefabType>(), _copyMode);
        },
        m_data);
}

Ent::Node* Ent::Array::arrayPush()
{
    ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
    return m_data.get<Vector>().push();
}
