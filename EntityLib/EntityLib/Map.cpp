#include "Map.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "Tools.h"

using namespace nlohmann;

static void setChildKey(Ent::Subschema const* _arraySchema, Ent::Node* _child, Ent::Map::KeyType _key)
{
    auto&& meta = _arraySchema->meta.get<Ent::Subschema::ArrayMeta>();
    using namespace Ent;
    switch (hash(meta.overridePolicy))
    {
    case "map"_hash:
    {
        // It is a C++ map.
        // In json it is an array of "2 item array" where the 1st item is the key
        // and can be string, double or integer
        // meta.ordered means the items have to be sorted by the key
        ENTLIB_ASSERT(_child->getSchema()->linearItems.has_value());
        // ENTLIB_ASSERT(not _child->at(0llu)->hasDefaultValue); // Sometime there is a key in the default value
        Ent::DataType keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
        switch (keyType)
        {
        case Ent::DataType::string:
            _child->at(0llu)->setString(_key.get<Ent::String>().c_str());
            break;
        case Ent::DataType::entityRef:
            _child->at(0llu)->setEntityRef(Ent::EntityRef{_key.get<Ent::String>()});
            break;
        case Ent::DataType::integer: _child->at(0llu)->setInt(_key.get<int64_t>()); break;
        default:
            throw std::runtime_error("Can't use this type as key of a map : " + _arraySchema->name);
        }
    }
    break;
    case "set"_hash:
    {
        // It is a C++ set.
        // In json it is an array of primitive. string, double or integer or oneOf
        // meta.ordered means the items have to be sorted by the key
        Ent::DataType const keyType = _arraySchema->singularItems->get().type;
        switch (keyType)
        {
        // The key is the className string
        case Ent::DataType::oneOf: _child->setUnionType(_key.get<Ent::String>().c_str()); break;
        // The key is the item itself
        case Ent::DataType::string: _child->setString(_key.get<Ent::String>().c_str()); break;
        // The key is the item itself
        case Ent::DataType::integer: _child->setInt(_key.get<int64_t>()); break;
        default: throw std::runtime_error("Can't use this type in a set : " + _arraySchema->name);
        }
#pragma warning(pop)
    }
    break;
    default:
        throw std::runtime_error(format(
            "Unknown key type (%s) in schema of %s",
            meta.overridePolicy.c_str(),
            _arraySchema->name.c_str()));
    }
}

static Ent::Map::KeyType getChildKey(Ent::Subschema const* _arraySchema, Ent::Node const* _child)
{
    auto const& pol = _arraySchema->meta.get<Ent::Subschema::ArrayMeta>().overridePolicy;
    ENTLIB_ASSERT(pol == "map" or pol == "set");
    if (pol == "map")
    {
        ENTLIB_ASSERT(_child->size() == 2);
        ENTLIB_ASSERT(_child->at(0llu) != nullptr);
        ENTLIB_ASSERT(_child->at(1llu) != nullptr);
    }
    auto&& meta = _arraySchema->meta.get<Ent::Subschema::ArrayMeta>();
    using namespace Ent;
    switch (hash(meta.overridePolicy))
    {
    case "map"_hash:
    {
        // It is a C++ map.
        // In json it is an array of "2 item array" where the 1st item is the key
        // and can be string, double or integer
        // meta.ordered means the items have to be sorted by the key
        ENTLIB_ASSERT(_child->getSchema()->linearItems.has_value());
        Ent::DataType keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
        switch (keyType)
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(_child->at(0llu)->getString() != std::string());
            return _child->at(0llu)->getString();
        case Ent::DataType::entityRef: return _child->at(0llu)->getEntityRef().entityPath.c_str();
        case Ent::DataType::number: return _child->at(0llu)->getFloat();
        case Ent::DataType::integer: return _child->at(0llu)->getInt();
        default: throw std::runtime_error("Unknown key type in map " + _arraySchema->name);
        }
    }
    break;
    case "set"_hash:
    {
        // It is a C++ set.
        // In json it is an array of primitive. string, double or integer or oneOf
        // meta.ordered means the items have to be sorted by the key
        Ent::DataType const keyType = _arraySchema->singularItems->get().type;
        switch (keyType)
        {
        // The key is the className string
        case Ent::DataType::oneOf: return _child->getUnionType(); break;
        // The key is the item itself
        case Ent::DataType::string: return _child->getString();
        // The key is the item itself
        case Ent::DataType::number: return _child->getFloat();
        // The key is the item itself
        case Ent::DataType::integer: return _child->getInt();
        default: throw std::runtime_error("Unknown key type in set " + _arraySchema->name);
        }
#pragma warning(pop)
    }
    break;
    default:
        throw std::runtime_error(format(
            "Unknown key type (%s) in schema of %s",
            meta.overridePolicy.c_str(),
            _arraySchema->name.c_str()));
    }
}

Ent::Map::KeyType Ent::Map::getChildKey(Subschema const* _schema, Ent::Node const* _child)
{
    return ::getChildKey(_schema, _child);
}

bool Ent::Map::Element::hasOverride() const
{
    return isPresent.hasOverride || node->hasOverride();
}

bool Ent::Map::Element::hasPrefabValue() const
{
    return isPresent.hasPrefab or node->hasPrefabValue();
}

bool Ent::Map::Element::hasDefaultValue() const
{
    return (not isPresent.hasPrefab and not isPresent.hasOverride) and node->hasDefaultValue();
}

bool Ent::Map::hasOverride() const
{
    return std::any_of(begin(items), end(items), std::mem_fn(&Element::hasOverride));
}

bool Ent::Map::hasPrefabValue() const
{
    return std::any_of(begin(items), end(items), std::mem_fn(&Element::hasPrefabValue));
}

Ent::Node* Ent::Map::at(uint64_t _index)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<Ent::Node*>(std::as_const(*this).at(_index));
}

Ent::Node const* Ent::Map::at(uint64_t _index) const
{
    if (_index < items.size())
    {
        return items[_index].node.get();
    }
    else
    {
        return nullptr;
    }
}

bool Ent::Map::erase(KeyType const& _key)
{
    auto iter = itemMap.find(_key);
    if (iter == itemMap.end())
    {
        return false;
    }
    size_t index = iter->second;
    Element& element = items.at(index);
    if (element.isPresent.get())
    {
        element.isPresent.set(false);
    }
    checkInvariants();
    return true;
}

Ent::Node const* Ent::Map::get(KeyType const& _key) const
{
    auto iter = itemMap.find(_key);
    if (iter == itemMap.end())
    {
        return nullptr;
    }
    size_t index = iter->second;
    Element const& element = items.at(index);
    if (not element.isPresent.get())
    {
        return nullptr;
    }
    return element.node.get();
}

Ent::Node* Ent::Map::insert(KeyType const& _key)
{
    auto iter = itemMap.find(_key);
    if (iter == itemMap.end())
    {
        SubschemaRef const* itemSchema = schema->singularItems.get();
        ENTLIB_ASSERT_MSG(itemSchema, "map/set expect a singularItems");
        auto newNode = entlib->loadNode(itemSchema->get(), json(), nullptr);
        setChildKey(schema, &newNode, _key);
        return insert(OverrideValueLocation::Override, _key, std::move(newNode));
    }
    size_t index = iter->second;
    Element& element = items.at(index);
    if (not element.isPresent.get())
    {
        element.isPresent.set(true);
    }
    checkInvariants();
    return element.node.get();
}

bool Ent::Map::isErased(KeyType const& _key) const
{
    auto iter = itemMap.find(_key);
    if (iter == itemMap.end())
    {
        return false;
    }
    return not items.at(iter->second).isPresent.get();
}

Ent::Node* Ent::Map::insert(OverrideValueLocation loc, KeyType _key, Node _node)
{
    ENTLIB_ASSERT(get(_key) == nullptr);
    ENTLIB_ASSERT(itemMap.count(_key) == 0);
    checkInvariants();
    ENTLIB_ASSERT(&schema->singularItems->get() == _node.getSchema());
    items.emplace_back(Element{std::move(_node)});
    auto& elt = items.back();
    switch (loc)
    {
    case OverrideValueLocation::Default: elt.isPresent.defaultValue = true; break;
    case OverrideValueLocation::Prefab:
        elt.isPresent.prefabValue = true;
        elt.isPresent.hasPrefab = true;
        break;
    case OverrideValueLocation::Override:
        elt.isPresent.overrideValue = true;
        elt.isPresent.hasOverride = true;
        break;
    }
    itemMap.emplace(std::move(_key), items.size() - 1);
    checkInvariants();
    return elt.node.get();
}

std::vector<Ent::Node const*> Ent::Map::getItemsWithRemoved() const
{
    std::vector<Node const*> result;
    result.reserve(items.size());
    for (auto&& elt : items)
    {
        result.emplace_back(elt.node.get());
    }
    return result;
}

std::vector<Ent::Node const*> Ent::Map::getItems() const
{
    checkInvariants();
    std::vector<Node const*> result;
    result.reserve(items.size());
    for (auto&& node : items)
    {
        auto key = ::getChildKey(schema, node.node.get());
        if (node.isPresent.get())
        {
            result.emplace_back(node.node.get());
        }
    }
    return result;
}

void Ent::Map::checkInvariants() const
{
    ENTLIB_ASSERT(schema->singularItems != nullptr);
    auto const& overridePolicy = schema->meta.get<Subschema::ArrayMeta>().overridePolicy;
    ENTLIB_ASSERT(overridePolicy == "map" or overridePolicy == "set");
    auto singItem = &schema->singularItems->get();
    for (auto& itm : items)
    {
        ENTLIB_ASSERT(singItem == itm.node->getSchema());
    }
    for (auto& key_item : itemMap)
    {
        auto schem = items.at(std::get<1>(key_item)).node->getSchema();
        ENTLIB_ASSERT(singItem == schem);
    }
}

bool Ent::Map::hasDefaultValue() const
{
    return std::all_of(begin(items), end(items), std::mem_fn(&Element::hasDefaultValue));
}

void Ent::Map::clear()
{
    for (auto&& elt : items)
    {
        elt.isPresent.set(false);
    }
    checkInvariants();
}

Ent::Map Ent::Map::detach() const
{
    Map result{nullptr, schema};
    for (auto const elt : items)
    {
        if (elt.isPresent.get())
        {
            Node detachedNode(elt.node->detach());
            auto key = ::getChildKey(schema, &detachedNode);
            result.insert(OverrideValueLocation::Override, key, std::move(detachedNode));
        }
    }
    result.checkInvariants();
    return result;
}

Ent::Map Ent::Map::makeInstanceOf() const
{
    checkInvariants();
    Map result{nullptr, schema};
    for (auto const& elt : items)
    {
        auto key = ::getChildKey(schema, elt.node.get());
        result.items.push_back(elt.makeInstanceOf());
        result.itemMap[key] = result.items.size() - 1;
    }
    return result;
}

tl::optional<size_t> Ent::Map::getRawSize(OverrideValueLocation _location) const
{
    switch (_location)
    {
    case OverrideValueLocation::Default: return getDefaultSize();
    case OverrideValueLocation::Prefab:
    {
        auto prefabSize = getPrefabSize();
        auto defaultsize = getDefaultSize();
        return (prefabSize == defaultsize) ? tl::optional<size_t>{} : prefabSize;
    }
    case OverrideValueLocation::Override:
    {
        auto instanceSize = size();
        auto prefabsize = getPrefabSize();
        return (instanceSize == prefabsize) ? tl::optional<size_t>{} : instanceSize;
    }
    }
    ENTLIB_LOGIC_ERROR("Unknown OverrideValueLocation : %d", _location);
    return {};
}

Ent::Map::Element Ent::Map::Element::makeInstanceOf() const
{
    Element result;
    result.node = node->makeInstanceOf();
    result.isPresent = isPresent.makeInstanceOf();
    return result;
}
