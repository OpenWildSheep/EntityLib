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
        // and can be string or integer
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
        case Ent::DataType::object:
            if (meta.keyField.has_value())
            {
                auto keyNode = _child->at(meta.keyField->c_str());
                switch (keyNode->getDataType())
                {
                case Ent::DataType::string:
                    keyNode->setString(_key.get<Ent::String>().c_str());
                    break;
                case Ent::DataType::integer: keyNode->setInt(_key.get<int64_t>()); break;
                default:
                    throw ContextException("Can't use this type as key of a set : " + *meta.keyField);
                }
                break;
            }
            [[fallthrough]];
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

static Ent::DataType getKeyType(Ent::Subschema const* _arraySchema)
{
    auto&& meta = _arraySchema->meta.get<Ent::Subschema::ArrayMeta>();
    using namespace Ent;
    switch (hash(meta.overridePolicy))
    {
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
    case "map"_hash: return _arraySchema->singularItems->get().linearItems->at(0)->type; break;
    case "set"_hash:
    {
        Ent::DataType const keyType = _arraySchema->singularItems->get().type;
        switch (keyType)
        {
        case Ent::DataType::oneOf: return Ent::DataType::string;
        case Ent::DataType::string: return Ent::DataType::string;
        case Ent::DataType::integer: return Ent::DataType::integer;
        default: throw ContextException("Unknown key type in set " + _arraySchema->name);
        }
#pragma warning(pop)
    }
    break;
    default:
        throw ContextException(
            "Unknown key type (%s) in schema of %s",
            meta.overridePolicy.c_str(),
            _arraySchema->name.c_str());
    }
}

static Ent::Map::KeyType getChildKey(Ent::Subschema const* _arraySchema, Ent::Node const* _child)
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
        Ent::DataType keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
        switch (keyType)
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(_child->at(0llu)->getString() != std::string());
            return String(_child->at(0llu)->getString());
        case Ent::DataType::entityRef:
            return String(_child->at(0llu)->getEntityRef().entityPath.c_str());
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
        case Ent::DataType::oneOf: return String(_child->getUnionType()); break;
        // The key is the item itself
        case Ent::DataType::string: return String(_child->getString());
        case Ent::DataType::integer: return _child->getInt();
        case Ent::DataType::object:
            if (meta.keyField.has_value())
            {
                auto keyNode = _child->at(meta.keyField->c_str());
                switch (keyNode->getDataType())
                {
                case Ent::DataType::string: return keyNode->getString(); break;
                case Ent::DataType::integer: return keyNode->getInt(); break;
                default:
                    throw ContextException("Can't use this type as key of a set : " + *meta.keyField);
                }
                break;
            }
            [[fallthrough]];
        default: throw ContextException("Unknown key type in set " + _arraySchema->name);
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

Ent::Map::Map(EntityLib const* _entlib, Subschema const* _schema)
    : m_entlib(_entlib)
    , m_schema(_schema)
{
}

Ent::Map::KeyType Ent::Map::getChildKey(Subschema const* _schema, Ent::Node const* _child)
{
    return ::getChildKey(_schema, _child);
}

Ent::DataType Ent::Map::getKeyType(Subschema const* _schema)
{
    return ::getKeyType(_schema);
}

bool Ent::Map::Element::hasOverride() const
{
    return isPresent.hasOverride() || node->hasOverride();
}

bool Ent::Map::Element::hasPrefabValue() const
{
    return isPresent.hasPrefabValue() or node->hasPrefabValue();
}

bool Ent::Map::Element::hasDefaultValue() const
{
    return (not isPresent.hasPrefabValue() and not isPresent.hasOverride())
           and node->hasDefaultValue();
}

bool Ent::Map::hasOverride() const
{
    return std::any_of(begin(m_items), end(m_items), std::mem_fn(&Element::hasOverride));
}

bool Ent::Map::hasPrefabValue() const
{
    return std::any_of(begin(m_items), end(m_items), std::mem_fn(&Element::hasPrefabValue));
}

Ent::Node* Ent::Map::at(uint64_t _index)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<Ent::Node*>(std::as_const(*this).at(_index));
}

Ent::Node const* Ent::Map::at(uint64_t _index) const
{
    if (_index < m_items.size())
    {
        return m_items[_index].node.get();
    }
    else
    {
        return nullptr;
    }
}

bool Ent::Map::erase(KeyType const& _key)
{
    auto iter = m_itemMap.find(_key);
    if (iter == m_itemMap.end())
    {
        return false;
    }
    size_t index = iter->second;
    Element& element = m_items.at(index);
    if (element.isPresent.get())
    {
        element.isPresent.set(false);
        element.node->setAddedInInsance(false);
    }
    checkInvariants();
    return true;
}

template <typename Elt> // Elt is Element or Element const
static auto getEltValue(Ent::Subschema const* _schema, Elt& _element)
    -> decltype(_element.node.get())
{
    if (not _element.isPresent.get())
    {
        return nullptr;
    }
    auto* node = _element.node.get();
    auto const& overridePolicy = _schema->meta.get<Ent::Subschema::ArrayMeta>().overridePolicy;
    if (overridePolicy == "map")
    {
        return node->at(1llu);
    }
    else
    {
        return _element.node.get();
    }
}

Ent::Node const* Ent::Map::get(KeyType const& _key) const
{
    auto iter = m_itemMap.find(_key);
    if (iter == m_itemMap.end())
    {
        return nullptr;
    }
    size_t index = iter->second;
    Element const& element = m_items.at(index);
    return getEltValue(m_schema, element);
}

Ent::Node* Ent::Map::get(KeyType const& _key)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<Ent::Node*>(std::as_const(*this).get(_key));
}

Ent::Map::Element& Ent::Map::insertImpl(KeyType const& _key)
{
    auto iter = m_itemMap.find(_key);
    if (iter == m_itemMap.end())
    {
        SubschemaRef const* itemSchema = m_schema->singularItems.get();
        ENTLIB_ASSERT_MSG(itemSchema, "map/set expect a singularItems");
        auto newNode = m_entlib->loadNode(itemSchema->get(), json(), nullptr);
        setChildKey(m_schema, &newNode, _key);
        auto& elt = insertImpl(OverrideValueLocation::Override, _key, std::move(newNode), true);
        getEltValue(m_schema, elt)->setAddedInInsance(true);
        elt.node->setAddedInInsance(true);
        return elt;
    }
    size_t index = iter->second;
    Element& element = m_items.at(index);
    if (not element.isPresent.get())
    {
        element.isPresent.set(true);
        element.node->setAddedInInsance(true);
        if (not element.isPresent.getPrefab())
        {
            // This element was removed in the prefab and re-insert in the instance
            // So we will not get back the data from before the prefab.
            auto key = getChildKey(m_schema, element.node.get());
            (*element.node) = m_entlib->loadNode(*element.node->getSchema(), json{}, nullptr);
            setChildKey(m_schema, element.node.get(), key);
        }
        // If the element was present in the prefab and remove in the instance,
        // we have no way to express in the json that the element is reset,
        // so we will keep the prefab data.
    }
    checkInvariants();
    return element;
}

Ent::Node* Ent::Map::insert(KeyType const& _key)
{
    return insertImpl(_key).node.get();
}

Ent::Node* Ent::Map::rename(KeyType const& _key, KeyType const& _newkey)
{
    auto iter = m_itemMap.find(_key);
    if (iter != m_itemMap.end())
    {
        auto const idx = iter->second;
        if (m_items[idx].isPresent.get())
        {
            auto const& overridePolicy = m_schema->meta.get<Subschema::ArrayMeta>().overridePolicy;
            auto const itemIsObject = m_schema->singularItems->get().type == Ent::DataType::object;
            if (itemIsObject and overridePolicy == "set"
                and m_items[idx].node->GetRawValue().get<Object>().hasASuper)
            {
                throw CantRename(
                    R"(Can't rename key because it override an item in prefab from parent entity)");
            }
            else
            {
                m_items[idx].isPresent.set(false);
                m_items[idx].node->setAddedInInsance(false);
                auto clone = *m_items[idx].node;
                setChildKey(m_schema, &clone, _newkey);
                Element& newNode =
                    insertImpl(Ent::OverrideValueLocation::Override, _newkey, clone, true);
                // Change the elements order to keep the position in the array
                std::swap(newNode, m_items[idx]); // swap the elements
                std::swap(m_itemMap[_key], m_itemMap[_newkey]); // swap the indexes
                return m_items[idx].node.get(); // The right elt is m_items[idx] since they have been swaped
            }
        }
        else
        {
            throw CantRename("Can't rename key because it was removed");
        }
    }
    else
    {
        throw CantRename("Can't rename key because it doesn't exist");
    }
}

bool Ent::Map::isErased(KeyType const& _key) const
{
    auto iter = m_itemMap.find(_key);
    if (iter == m_itemMap.end())
    {
        return false;
    }
    return not m_items.at(iter->second).isPresent.get();
}

Ent::Map::Element&
Ent::Map::insertImpl(OverrideValueLocation _loc, KeyType _key, Node _node, bool _addedInInstance)
{
    ENTLIB_ASSERT(get(_key) == nullptr);
    ENTLIB_ASSERT(m_itemMap.count(_key) == 0);
    checkInvariants();
    ENTLIB_ASSERT(&m_schema->singularItems->get() == _node.getSchema());
    m_items.emplace_back(Element{std::move(_node)});
    auto& elt = m_items.back();
    switch (_loc)
    {
    case OverrideValueLocation::Default:
    {
        elt.isPresent.setDefault(true);
        break;
    }
    case OverrideValueLocation::Prefab: elt.isPresent.setPrefab(true); break;
    case OverrideValueLocation::Override: elt.isPresent.set(true); break;
    }
    elt.node->setAddedInInsance(_addedInInstance);
    getEltValue(m_schema, elt)->setAddedInInsance(_addedInInstance);
    m_itemMap.emplace(std::move(_key), m_items.size() - 1);
    checkInvariants();
    return elt;
}

Ent::Node* Ent::Map::insert(OverrideValueLocation _loc, KeyType _key, Node _node, bool _addedInInstance)
{
    return insertImpl(_loc, std::move(_key), std::move(_node), _addedInInstance).node.get();
}

std::vector<Ent::Node const*> Ent::Map::getItemsWithRemoved() const
{
    std::vector<Node const*> result;
    result.reserve(m_items.size());
    auto&& meta = m_schema->meta.get<Ent::Subschema::ArrayMeta>();
    if (meta.ordered)
    {
        for (auto const& key_index : m_itemMap)
        {
            auto& elt = m_items[std::get<1>(key_index)];
            result.push_back(elt.node.get());
        }
    }
    else
    {
        for (auto&& elt : m_items)
        {
            result.push_back(elt.node.get());
        }
    }
    return result;
}

std::vector<Ent::Node const*> Ent::Map::getItems() const
{
    checkInvariants();
    std::vector<Node const*> result;
    result.reserve(m_items.size());
    auto&& meta = m_schema->meta.get<Ent::Subschema::ArrayMeta>();
    if (meta.ordered)
    {
        for (auto const& key_index : m_itemMap)
        {
            auto index = std::get<1>(key_index);
            auto& elt = m_items[index];
            if (elt.isPresent.get())
            {
                result.push_back(elt.node.get());
            }
        }
    }
    else
    {
        for (auto const& node : m_items)
        {
            auto key = ::getChildKey(m_schema, node.node.get());
            if (node.isPresent.get())
            {
                result.push_back(node.node.get());
            }
        }
    }
    return result;
}

void Ent::Map::checkInvariants() const
{
    ENTLIB_ASSERT(m_schema->singularItems != nullptr);
    auto const& overridePolicy = m_schema->meta.get<Subschema::ArrayMeta>().overridePolicy;
    ENTLIB_ASSERT(overridePolicy == "map" or overridePolicy == "set");
    auto singItem = &m_schema->singularItems->get();
    for (auto& itm : m_items)
    {
        ENTLIB_ASSERT(singItem == itm.node->getSchema());
    }
    for (auto& key_item : m_itemMap)
    {
        auto itemSchema = m_items.at(std::get<1>(key_item)).node->getSchema();
        ENTLIB_ASSERT(singItem == itemSchema);
    }
}

bool Ent::Map::hasDefaultValue() const
{
    return std::all_of(begin(m_items), end(m_items), std::mem_fn(&Element::hasDefaultValue));
}

void Ent::Map::clear()
{
    for (auto&& elt : m_items)
    {
        elt.isPresent.set(false);
        elt.node->setAddedInInsance(false);
    }
    checkInvariants();
}

Ent::Map Ent::Map::detach() const
{
    Map result{nullptr, m_schema};
    for (auto const& elt : m_items)
    {
        if (elt.isPresent.get())
        {
            Element detachedElt;
            detachedElt.node = elt.node->detach();
            detachedElt.isPresent = elt.isPresent.detach();
            auto key = getChildKey(m_schema, detachedElt.node.get());
            result.m_items.emplace_back(std::move(detachedElt));
            result.m_itemMap.emplace(key, result.m_items.size() - 1);
        }
    }
    result.checkInvariants();
    return result;
}

Ent::Map Ent::Map::makeInstanceOf() const
{
    checkInvariants();
    Map result{nullptr, m_schema};
    for (auto const& elt : m_items)
    {
        auto key = ::getChildKey(m_schema, elt.node.get());
        result.m_items.push_back(elt.makeInstanceOf());
        result.m_itemMap[key] = result.m_items.size() - 1;
    }
    return result;
}

tl::optional<size_t> Ent::Map::getRawSize(OverrideValueLocation _location) const
{
    switch (_location)
    {
    case OverrideValueLocation::Default:
    {
        return getDefaultSize();
    }
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
}

Ent::Map::Element Ent::Map::Element::makeInstanceOf() const
{
    Element result;
    result.node = node->makeInstanceOf();
    result.isPresent = isPresent.makeInstanceOf();
    return result;
}

size_t Ent::Map::size() const
{
    return (size_t)std::count_if(
        begin(m_items), end(m_items), [](auto&& d) { return d.isPresent.get(); });
}

size_t Ent::Map::getDefaultSize() const
{
    return (size_t)std::count_if(
        begin(m_items), end(m_items), [](Element const& d) { return d.isPresent.getDefault(); });
}

size_t Ent::Map::getPrefabSize() const
{
    return (size_t)std::count_if(
        begin(m_items), end(m_items), [](Element const& d) { return d.isPresent.getPrefab(); });
}

void Ent::Map::computeMemory(MemoryProfiler& _prof) const
{
    _prof.addMem("Array::data", m_items.capacity() * sizeof(m_items.front()));
    for (auto&& item : m_items)
    {
        item.node->computeMemory(_prof);
        _prof.addMem("Array::data::value_ptr", sizeof(Ent::Node));
    }
    _prof.addMem("Array::itemMap", m_itemMap.size() * sizeof(*m_itemMap.begin()));
    _prof.addNodes(m_items.size());
}

void Ent::Map::unset()
{
    for (auto& elt : m_items)
    {
        elt.isPresent.unset();
        elt.node->unset();
        elt.node->setAddedInInsance(false);
        if (elt.isPresent.get() and elt.isPresent.hasDefaultValue())
        {
            elt.node->setAddedInInsance(true);
        }
        else
        {
            elt.node->setAddedInInsance(false);
        }
    }
}

void Ent::Map::applyAllValues(Map& _dest, CopyMode _copyMode) const
{
    std::set<KeyType> removedDestKeys;
    for (auto& destNode : _dest.getItems())
    {
        auto&& key = getChildKey(m_schema, destNode);
        removedDestKeys.insert(key);
    }

    for (auto& sourceNode : getItems())
    {
        auto&& key = getChildKey(m_schema, sourceNode);
        Node* destNode2 = _dest.insert(key); // 'insert' only get if the item exist
        sourceNode->applyAllValues(*destNode2, _copyMode);
        removedDestKeys.erase(key);
    }

    for (auto const& removedDestKey : removedDestKeys)
    {
        _dest.erase(removedDestKey);
    }
}

void Ent::Map::setParentNode(Node* _parentNode)
{
    for (auto& elt : m_items)
    {
        elt.node->setParentNode(_parentNode);
    }
}

void Ent::Map::checkParent(Node const* _parentNode) const
{
    for (auto& elt : m_items)
    {
        elt.node->checkParent(_parentNode);
    }
}

std::vector<Ent::String> Ent::Map::getKeysString() const
{
    auto const keyType = getKeyType(m_schema);
    if (keyType != Ent::DataType::string and keyType != Ent::DataType::entityRef)
    {
        throw ContextException("Can't call 'getKeysString' if key is not string or entityRef");
    }
    std::vector<String> keys;
    keys.reserve(m_items.size());
    for (auto& elt : m_items)
    {
        if (elt.isPresent.get())
            keys.push_back(getChildKey(m_schema, elt.node.get()).get<Ent::String>());
    }
    return keys;
}

std::vector<int64_t> Ent::Map::getKeysInt() const
{
    auto const keyType = getKeyType(m_schema);
    if (keyType != Ent::DataType::integer)
    {
        throw ContextException("Can't call 'getKeysInt' if key is not integer");
    }
    std::vector<int64_t> keys;
    keys.reserve(m_items.size());
    for (auto& elt : m_items)
    {
        if (elt.isPresent.get())
            keys.push_back(getChildKey(m_schema, elt.node.get()).get<int64_t>());
    }
    return keys;
}