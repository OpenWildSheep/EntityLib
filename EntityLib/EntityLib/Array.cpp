#include "Array.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "include/Schema.h"
#include "Tools.h"
#include "Map.h"

using namespace nlohmann;

Ent::Array::Array(EntityLib const* _entlib, Subschema const* _schema)
    : schema(_schema)
{
    if (hasKey())
    {
        data = Map{_entlib, _schema};
    }
    else
    {
        data = Vector{_entlib, _schema};
    }
    ENTLIB_ASSERT(schema != nullptr);
}

Ent::Map::KeyType Ent::Array::getChildKey(Ent::Node const* _child) const
{
    return Map::getChildKey(schema, _child);
}

Ent::Node* Ent::Array::at(uint64_t _index)
{
    return mapbox::util::apply_visitor([_index](auto& a) { return a.at(_index); }, data);
}

Ent::Node const* Ent::Array::at(uint64_t _index) const
{
    return mapbox::util::apply_visitor([_index](auto const& a) { return a.at(_index); }, data);
}

bool Ent::Array::isErased(Map::KeyType const& _key) const
{
    ENTLIB_ASSERT(data.is<Map>());
    return data.get<Map>().isErased(_key);
}

bool Ent::Array::mapErase(Map::KeyType const& _key)
{
    ENTLIB_ASSERT(data.is<Map>());
    return data.get<Map>().erase(_key);
}

Ent::Node* Ent::Array::mapGet(Map::KeyType const& _key)
{
    ENTLIB_ASSERT(data.is<Map>());
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<Ent::Node*>(std::as_const(*this).data.get<Map>().get(_key));
}
Ent::Node const* Ent::Array::mapGet(Map::KeyType const& _key) const
{
    return data.get<Map>().get(_key);
}
Ent::Node* Ent::Array::mapInsert(Map::KeyType const& _key)
{
    return data.get<Map>().insert(_key);
}

bool Ent::Array::hasKey() const
{
    auto&& meta = schema->meta.get<Ent::Subschema::ArrayMeta>();
    return meta.overridePolicy == "map" || meta.overridePolicy == "set";
}

bool Ent::Array::isTuple() const
{
    return data.get<Vector>().isTuple();
}

Ent::Node* Ent::Array::initAdd(OverrideValueLocation loc, Node _node)
{
    if (hasKey())
    {
        auto key = getChildKey(&_node);
        return data.get<Map>().insert(loc, key, std::move(_node));
    }
    else
    {
        return data.get<Vector>().initPush(std::move(_node));
    }
}

Ent::Node* Ent::Array::mapInitInsert(OverrideValueLocation _loc, Map::KeyType _key, Node _node)
{
    return data.get<Map>().insert(_loc, _key, _node);
}

std::vector<Ent::Node const*> Ent::Array::getItemsWithRemoved() const
{
    ENTLIB_ASSERT(data.is<Map>());
    return data.get<Map>().getItemsWithRemoved();
}

std::vector<Ent::Node const*> Ent::Array::getItems() const
{
    return mapbox::util::apply_visitor([](auto& a) { return a.getItems(); }, data);
}

void Ent::Array::checkInvariants() const
{
    return mapbox::util::apply_visitor([](auto& a) { return a.checkInvariants(); }, data);
}

bool Ent::Array::hasOverride() const
{
    return mapbox::util::apply_visitor([](auto& a) { return a.hasOverride(); }, data);
}

bool Ent::Array::hasPrefabValue() const
{
    return mapbox::util::apply_visitor([](auto& a) { return a.hasPrefabValue(); }, data);
}

bool Ent::Array::hasDefaultValue() const
{
    return mapbox::util::apply_visitor([](auto& a) { return a.hasDefaultValue(); }, data);
}

void Ent::Array::pop()
{
    ENTLIB_ASSERT(not hasKey());
    data.get<Vector>().pop();
}

void Ent::Array::clear()
{
    mapbox::util::apply_visitor([](auto& a) { return a.clear(); }, data);
}

bool Ent::Array::empty() const
{
    return size() == 0;
}

Ent::Array Ent::Array::detach() const
{
    Array result{nullptr, schema};
    result.data = mapbox::util::apply_visitor([](auto& a) { return MapOrVector(a.detach()); }, data);
    result.checkInvariants();
    return result;
}

Ent::Array Ent::Array::makeInstanceOf() const
{
    Array result{nullptr, schema};
    result.data =
        mapbox::util::apply_visitor([](auto& a) { return MapOrVector(a.makeInstanceOf()); }, data);
    return result;
}

void Ent::Array::arraySetSize(Override<size_t> _size)
{
    data.get<Vector>().arraySize = _size;
}

void Ent::Array::computeMemory(MemoryProfiler& prof) const
{
    mapbox::util::apply_visitor([&prof](auto& a) { return a.computeMemory(prof); }, data);
}

void Ent::Map::computeMemory(MemoryProfiler& prof) const
{
    prof.addMem("Array::data", items.capacity() * sizeof(items.front()));
    for (auto&& item : items)
    {
        item.node->computeMemory(prof);
        prof.addMem("Array::data::value_ptr", sizeof(Ent::Node));
    }
    prof.addMem("Array::itemMap", itemMap.size() * sizeof(*itemMap.begin()));
    prof.addNodes(items.size());
}

Ent::Node* Ent::Array::arrayInitPush(Node _node)
{
    ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
    return data.get<Vector>().initPush(_node);
}

Ent::Node* Ent::Array::arrayPush()
{
    ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
    return data.get<Vector>().push();
}
