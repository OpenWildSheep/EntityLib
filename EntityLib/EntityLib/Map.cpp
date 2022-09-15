#include "Map.h"

#include <ciso646>
#include <set>

#include "include/EntityLib.h"
#include "Tools.h"

using namespace nlohmann;

namespace Ent
{

    static void setChildKey(Subschema const* _arraySchema, Node* _child, Map::KeyType _key)
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(_arraySchema->meta);
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
            DataType const keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
            switch (keyType)
            {
            case DataType::string:
                _child->at(0llu)->setString(std::get<String>(_key).c_str());
                break;
            case DataType::entityRef:
                _child->at(0llu)->setEntityRef(EntityRef{std::get<String>(_key)});
                break;
            case DataType::integer: _child->at(0llu)->setInt(std::get<int64_t>(_key)); break;
            default:
                throw std::runtime_error(
                    "Can't use this type as key of a map : " + _arraySchema->name);
            }
        }
        break;
        case "set"_hash:
        {
            // It is a C++ set.
            // In json it is an array of primitive. string, double or integer or oneOf
            // meta.ordered means the items have to be sorted by the key
            DataType const keyType = _arraySchema->singularItems->get().type;
            switch (keyType)
            {
            // The key is the className string
            case DataType::oneOf: _child->setUnionType(std::get<String>(_key).c_str()); break;
            // The key is the item itself
            case DataType::string: _child->setString(std::get<String>(_key).c_str()); break;
            // The key is the item itself
            case DataType::entityRef:
                _child->setEntityRef(EntityRef{std::get<String>(_key)});
                break;
            // The key is the item itself
            case DataType::integer: _child->setInt(std::get<int64_t>(_key)); break;
            case DataType::object:
                if (meta.keyField.has_value())
                {
                    auto* const keyNode = _child->at(meta.keyField->c_str());
                    switch (keyNode->getDataType())
                    {
                    case DataType::string:
                        keyNode->setString(std::get<String>(_key).c_str());
                        break;
                    case DataType::entityRef:
                        keyNode->setEntityRef(EntityRef{std::get<String>(_key)});
                        break;
                    case DataType::integer: keyNode->setInt(std::get<int64_t>(_key)); break;
                    default:
                        throw ContextException(
                            "Can't use this type as key of a set : " + *meta.keyField);
                    }
                    break;
                }
                [[fallthrough]];
            default:
                throw std::runtime_error("Can't use this type in a set : " + _arraySchema->name);
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

    static DataType getKeyType(Subschema const* _arraySchema)
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(_arraySchema->meta);
        using namespace Ent;
        switch (hash(meta.overridePolicy))
        {
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
        case "map"_hash: return _arraySchema->singularItems->get().linearItems->at(0)->type; break;
        case "set"_hash:
        {
            auto& elementSchema = _arraySchema->singularItems->get();
            DataType const keyType = elementSchema.type;
            switch (keyType)
            {
            case DataType::oneOf: return DataType::string;
            case DataType::string: return DataType::string;
            case DataType::entityRef: return DataType::string;
            case DataType::integer: return DataType::integer;
            case DataType::object:
            {
                // If the element is an object, the map is actually a set of objects
                // So we expect to find a keyField. The key type is the type of the keyfield.
                if (meta.keyField.has_value())
                {
                    auto& keyFieldSchema = elementSchema.properties[*meta.keyField];
                    switch (keyFieldSchema->type)
                    {
                    case DataType::oneOf: return DataType::string;
                    case DataType::string: return DataType::string;
                    case DataType::entityRef: return DataType::string;
                    case DataType::integer: return DataType::integer;
                    default:
                        throw ContextException(
                            "Unknown key type in set %s/%s",
                            _arraySchema->name.c_str(),
                            meta.keyField->c_str());
                    }
                }
                throw ContextException("Object set without keyField in " + _arraySchema->name);
            }
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

    static Map::KeyType getChildKey(Subschema const* _arraySchema, Node const* _child)
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(_arraySchema->meta);
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
            DataType const keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
            Node const* keyNode = _child->at(0llu);
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
            switch (keyType)
            {
            case DataType::string: return String(keyNode->getString());
            case DataType::entityRef: return String(keyNode->getEntityRef().entityPath.c_str());
            case DataType::integer: return keyNode->getInt();
            default: throw std::runtime_error("Unknown key type in map " + _arraySchema->name);
            }
        }
        break;
        case "set"_hash:
        {
            // It is a C++ set.
            // In json it is an array of primitive. string, double or integer or oneOf
            // meta.ordered means the items have to be sorted by the key
            DataType const keyType = _arraySchema->singularItems->get().type;
            switch (keyType)
            {
            // The key is the className string
            case DataType::oneOf: return String(_child->getUnionType()); break;
            // The key is the item itself
            case DataType::string: return String(_child->getString());
            case DataType::entityRef: return _child->getEntityRef().entityPath;
            case DataType::integer: return _child->getInt();
            case DataType::object:
                if (meta.keyField.has_value())
                {
                    auto const* const keyNode = _child->at(meta.keyField->c_str());
                    switch (keyNode->getDataType())
                    {
                    case DataType::string: return keyNode->getString(); break;
                    case DataType::entityRef: return keyNode->getEntityRef().entityPath.c_str();
                    case DataType::integer: return keyNode->getInt(); break;
                    default:
                        throw ContextException(
                            "Can't use this type as key of a set : " + *meta.keyField);
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

    Map::Map(EntityLib const* _entlib, Subschema const* _schema)
        : m_entlib(_entlib)
        , m_schema(_schema)
    {
    }

    Map::Map(Map const& _other) = default;

    Map& Map::operator=(Map const& _other) = default;

    Map::KeyType Map::getChildKey(Subschema const* _schema, Node const* _child)
    {
        return Ent::getChildKey(_schema, _child);
    }

    DataType Map::getKeyType(Subschema const* _schema)
    {
        return Ent::getKeyType(_schema);
    }

    Map::Element::Element(Element const& _other)
        : node(_other.node->clone())
        , isPresent(_other.isPresent)
    {
    }
    Map::Element& Map::Element::operator=(Element const& _other)
    {
        if (this != &_other)
        {
            Element tmp(_other);
            std::swap(*this, tmp);
        }
        return *this;
    }

    bool Map::Element::hasOverride() const
    {
        if (isPresent.get())
        {
            return (not isPresent.getPrefab()) || node->hasOverride();
        }
        return isPresent.getPrefab();
    }

    bool Map::Element::hasPrefabValue() const
    {
        return isPresent.hasPrefabValue() or node->hasPrefabValue();
    }

    bool Map::Element::hasDefaultValue() const
    {
        return (not isPresent.hasPrefabValue() and not isPresent.hasOverride())
               and node->hasDefaultValue();
    }

    bool Map::hasOverride() const
    {
        return std::any_of(begin(m_items), end(m_items), std::mem_fn(&Element::hasOverride));
    }

    bool Map::hasPrefabValue() const
    {
        return std::any_of(begin(m_items), end(m_items), std::mem_fn(&Element::hasPrefabValue));
    }

    Node* Map::at(uint64_t _index)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Node*>(std::as_const(*this).at(_index));
    }

    Node const* Map::at(uint64_t _index) const
    {
        if (_index < m_items.size())
        {
            return m_items[_index].node.get();
        }
        return nullptr;
    }

    bool Map::erase(KeyType const& _key)
    {
        auto const iter = m_itemMap.find(_key);
        if (iter == m_itemMap.end())
        {
            return false;
        }
        size_t const index = iter->second;
        Element& element = m_items.at(index);
        if (element.isPresent.get())
        {
            element.isPresent.set(false);
            element.node->setAddedInInsance(false);
            checkInvariants();
            return true;
        }
        return false;
    }

    template <typename Elt> // Elt is Element or Element const
    static auto getEltValue(Subschema const* _schema, Elt& _element) -> decltype(_element.node.get())
    {
        if (not _element.isPresent.get())
        {
            return nullptr;
        }
        auto* node = _element.node.get();
        auto const& overridePolicy = std::get<Subschema::ArrayMeta>(_schema->meta).overridePolicy;
        if (overridePolicy == "map")
        {
            return node->at(1llu);
        }
        return _element.node.get();
    }

    Node const* Map::get(KeyType const& _key) const
    {
        auto const iter = m_itemMap.find(_key);
        if (iter == m_itemMap.end())
        {
            return nullptr;
        }
        size_t const index = iter->second;
        Element const& element = m_items.at(index);
        return getEltValue(m_schema, element);
    }

    Node* Map::get(KeyType const& _key)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Node*>(std::as_const(*this).get(_key));
    }

    Map::Element& Map::insertImpl(KeyType const& _key, NodeUniquePtr _newNode)
    {
        auto const iter = m_itemMap.find(_key);
        if (iter == m_itemMap.end())
        {
            SubschemaRef const* itemSchema = m_schema->singularItems.get();
            ENTLIB_ASSERT_MSG(itemSchema, "map/set expect a singularItems");
            if (_newNode == nullptr)
            {
                _newNode = m_entlib->loadNode(itemSchema->get(), json(), nullptr);
            }
            setChildKey(m_schema, _newNode.get(), _key);
            auto& elt = insertImpl(OverrideValueLocation::Override, _key, std::move(_newNode), true);
            getEltValue(m_schema, elt)->setAddedInInsance(true);
            elt.node->setAddedInInsance(true);
            elt.node->setParentNode(m_parentNode);
            return elt;
        }
        size_t const index = iter->second;
        Element& element = m_items.at(index);
        if (not element.isPresent.get())
        {
            element.isPresent.set(true);
            element.node->setAddedInInsance(true);
            if (not element.isPresent.getPrefab())
            {
                // This element was removed in the prefab and re-insert in the instance
                // So we will not get back the data from before the prefab.
                auto const key = getChildKey(m_schema, element.node.get());
                element.node = m_entlib->loadNode(*element.node->getSchema(), json{}, nullptr);
                setChildKey(m_schema, element.node.get(), key);
                // Can't change the type of a union which is inside a unionset,
                // so we move it in the parent after the "setChildKey".
                element.node->setParentNode(m_parentNode);
            }
            // If the element was present in the prefab and remove in the instance,
            // we have no way to express in the json that the element is reset,
            // so we will keep the prefab data.
        }
        checkInvariants();
        return element;
    }

    Node* Map::insert(KeyType const& _key)
    {
        return getEltValue(m_schema, insertImpl(_key));
    }

    void Map::insert(KeyType const& _key, NodeUniquePtr _newNode)
    {
        insertImpl(_key, std::move(_newNode));
    }

    Node* Map::rename(KeyType const& _key, KeyType const& _newkey)
    {
        auto const iter = m_itemMap.find(_key);
        if (iter != m_itemMap.end())
        {
            auto const idx = iter->second;
            if (m_items[idx].isPresent.get())
            {
                auto const& overridePolicy =
                    std::get<Subschema::ArrayMeta>(m_schema->meta).overridePolicy;
                auto const itemIsObject = m_schema->singularItems->get().type == DataType::object;
                if (itemIsObject and overridePolicy == "set"
                    and std::get<ObjectPtr>(m_items[idx].node->GetRawValue())->hasASuper)
                {
                    throw CantRename(
                        R"(Can't rename key because it override an item in prefab from parent entity)");
                }
                m_items[idx].isPresent.set(false);
                m_items[idx].node->setAddedInInsance(false);
                auto clone = m_items[idx].node->clone();
                setChildKey(m_schema, clone.get(), _newkey);
                Element& newNode =
                    insertImpl(OverrideValueLocation::Override, _newkey, std::move(clone), true);
                // Change the elements order to keep the position in the array
                std::swap(newNode, m_items[idx]); // swap the elements
                std::swap(m_itemMap[_key], m_itemMap[_newkey]); // swap the indexes
                return m_items[idx].node.get(); // The right elt is m_items[idx] since they have been swaped
            }
            throw CantRename("Can't rename key because it was removed");
        }
        throw CantRename("Can't rename key because it doesn't exist");
    }

    bool Map::isErased(KeyType const& _key) const
    {
        auto const iter = m_itemMap.find(_key);
        if (iter == m_itemMap.end())
        {
            return false;
        }
        return not m_items.at(iter->second).isPresent.get();
    }

    Map::Element& Map::insertImpl(
        OverrideValueLocation _loc, KeyType _key, NodeUniquePtr _node, bool _addedInInstance)
    {
        ENTLIB_ASSERT(get(_key) == nullptr);
        ENTLIB_ASSERT(m_itemMap.count(_key) == 0);
        checkInvariants();
        ENTLIB_ASSERT(&m_schema->singularItems->get() == _node->getSchema());
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

    Node* Map::insert(OverrideValueLocation _loc, KeyType _key, NodeUniquePtr _node, bool _addedInInstance)
    {
        return getEltValue(
            m_schema, insertImpl(_loc, std::move(_key), std::move(_node), _addedInInstance));
    }

    std::vector<Node const*> Map::getItemsWithRemoved() const
    {
        std::vector<Node const*> result;
        result.reserve(m_items.size());
        auto&& meta = std::get<Subschema::ArrayMeta>(m_schema->meta);
        auto notAGhostElement = [](Element const& elt)
        {
            // Don't care of elements which has never existed
            return elt.isPresent.get() or elt.isPresent.getPrefab();
        };
        if (meta.ordered)
        {
            for (auto const& key_index : m_itemMap)
            {
                auto const& elt = m_items[std::get<1>(key_index)];
                if (notAGhostElement(elt))
                {
                    result.push_back(elt.node.get());
                }
            }
        }
        else
        {
            for (auto&& elt : m_items)
            {
                if (notAGhostElement(elt))
                {
                    result.push_back(elt.node.get());
                }
            }
        }
        return result;
    }

    template <typename M>
    auto Map::getItemsImpl(M* self)
    {
        self->checkInvariants();
        auto result = []
        {
            if constexpr (std::is_const_v<M>)
            {
                return std::vector<Node const*>{};
            }
            else
            {
                return std::vector<Node*>{};
            }
        }();
        result.reserve(self->m_items.size());
        auto&& meta = std::get<Subschema::ArrayMeta>(self->m_schema->meta);
        if (meta.ordered)
        {
            for (auto const& key_index : self->m_itemMap)
            {
                auto index = std::get<1>(key_index);
                auto& elt = self->m_items[index];
                if (elt.isPresent.get())
                {
                    result.push_back(elt.node.get());
                }
            }
        }
        else
        {
            for (auto&& node : self->m_items)
            {
                auto key = Ent::getChildKey(self->m_schema, node.node.get());
                if (node.isPresent.get())
                {
                    result.push_back(node.node.get());
                }
            }
        }
        return result;
    }

    std::vector<Node*> Map::getItems()
    {
        return getItemsImpl(this);
    }

    std::vector<Node const*> Map::getItems() const
    {
        return getItemsImpl(this);
    }

    void Map::checkInvariants() const
    {
        ENTLIB_ASSERT(m_schema->singularItems != nullptr);
        auto const& overridePolicy = std::get<Subschema::ArrayMeta>(m_schema->meta).overridePolicy;
        ENTLIB_ASSERT(overridePolicy == "map" or overridePolicy == "set");
        auto* const singItem = &m_schema->singularItems->get();
        for (auto const& itm : m_items)
        {
            ENTLIB_ASSERT(singItem == itm.node->getSchema());
        }
        for (auto const& key_item : m_itemMap)
        {
            auto const* const itemSchema = m_items.at(std::get<1>(key_item)).node->getSchema();
            ENTLIB_ASSERT(singItem == itemSchema);
        }
    }

    bool Map::hasDefaultValue() const
    {
        return std::all_of(begin(m_items), end(m_items), std::mem_fn(&Element::hasDefaultValue));
    }

    void Map::clear()
    {
        for (auto&& elt : m_items)
        {
            elt.isPresent.set(false);
            elt.node->setAddedInInsance(false);
        }
        checkInvariants();
    }

    Map Map::detach() const
    {
        Map result{getEntityLib(), m_schema};
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

    Map Map::makeInstanceOf() const
    {
        checkInvariants();
        Map result{getEntityLib(), m_schema};
        for (auto const& elt : m_items)
        {
            auto key = Ent::getChildKey(m_schema, elt.node.get());
            result.m_items.push_back(elt.makeInstanceOf());
            result.m_itemMap[key] = result.m_items.size() - 1;
        }
        return result;
    }

    std::optional<size_t> Map::getRawSize(OverrideValueLocation _location) const
    {
        switch (_location)
        {
        case OverrideValueLocation::Default:
        {
            return getDefaultSize();
        }
        case OverrideValueLocation::Prefab:
        {
            auto const prefabSize = getPrefabSize();
            auto const defaultsize = getDefaultSize();
            return (prefabSize == defaultsize) ? std::optional<size_t>{} : prefabSize;
        }
        case OverrideValueLocation::Override:
        {
            auto const instanceSize = size();
            auto const prefabsize = getPrefabSize();
            return (instanceSize == prefabsize) ? std::optional<size_t>{} : instanceSize;
        }
        }
        ENTLIB_LOGIC_ERROR("Unknown OverrideValueLocation : %d", _location);
    }

    Map::Element Map::Element::makeInstanceOf() const
    {
        Element result;
        result.node = node->makeInstanceOf();
        result.isPresent = isPresent.makeInstanceOf();
        return result;
    }

    size_t Map::size() const
    {
        return static_cast<size_t>(std::count_if(
            begin(m_items), end(m_items), [](auto&& d) { return d.isPresent.get(); }));
    }

    size_t Map::getDefaultSize() const
    {
        return static_cast<size_t>(std::count_if(
            begin(m_items), end(m_items), [](Element const& d) { return d.isPresent.getDefault(); }));
    }

    size_t Map::getPrefabSize() const
    {
        return static_cast<size_t>(std::count_if(
            begin(m_items), end(m_items), [](Element const& d) { return d.isPresent.getPrefab(); }));
    }

    void Map::computeMemory(MemoryProfiler& _prof) const
    {
        _prof.addMem("Array::data", m_items.capacity() * sizeof(m_items.front()));
        for (auto&& item : m_items)
        {
            item.node->computeMemory(_prof);
            _prof.addMem("Array::data::value_ptr", sizeof(Node));
        }
        _prof.addMem("Array::itemMap", m_itemMap.size() * sizeof(*m_itemMap.begin()));
        _prof.addNodes(m_items.size());
    }

    void Map::unset()
    {
        for (auto& elt : m_items)
        {
            bool const presentBeforeUnset = elt.isPresent.get();
            elt.isPresent.unset();
            elt.node->setAddedInInsance(false);
            if (elt.node->getSchema()->oneOf.has_value())
            {
                // Avoid to change the key of the union, since it is the key of the item
                elt.node->getUnionData()->unset();
            }
            else
            {
                elt.node->unset();
            }
            if (presentBeforeUnset and not elt.isPresent.get())
            {
                elt.node->setAddedInInsance(true);
            }
            else
            {
                elt.node->setAddedInInsance(false);
            }
        }
    }

    void Map::applyAllValues(Map& _dest, CopyMode _copyMode) const
    {
        std::set<KeyType> removedDestKeys;
        for (auto const& destNode : _dest.getItems())
        {
            auto&& key = getChildKey(m_schema, destNode);
            removedDestKeys.insert(key);
        }

        for (auto const& sourceNode : getItems())
        {
            auto&& key = getChildKey(m_schema, sourceNode);
            Node* destNode2 = _dest.insertImpl(key).node.get(); // 'insert' only get if the item exist
            sourceNode->applyAllValues(*destNode2, _copyMode);
            removedDestKeys.erase(key);
        }

        for (auto const& removedDestKey : removedDestKeys)
        {
            _dest.erase(removedDestKey);
        }
    }

    void Map::setParentNode(Node* _parentNode)
    {
        m_parentNode = _parentNode;
        for (auto const& elt : m_items)
        {
            elt.node->setParentNode(_parentNode);
        }
    }

    void Map::checkParent(Node const* _parentNode) const
    {
        for (auto const& elt : m_items)
        {
            elt.node->checkParent(_parentNode);
        }
    }

    std::vector<String> Map::getKeysString(bool _forceSort) const
    {
        auto const keyType = getKeyType(m_schema);
        if (keyType != DataType::string and keyType != DataType::entityRef)
        {
            throw ContextException("Can't call 'getKeysString' if key is not string or entityRef");
        }
        std::vector<String> keys;
        keys.reserve(m_items.size());
        if (_forceSort)
        {
            for (auto const& [key, idx] : m_itemMap)
            {
                auto const& item = m_items[idx];
                if (item.isPresent.get())
                {
                    keys.push_back(std::get<String>(getChildKey(m_schema, item.node.get())));
                }
            }
        }
        else
        {
            for (auto const& elt : m_items)
            {
                if (elt.isPresent.get())
                {
                    keys.push_back(std::get<String>(getChildKey(m_schema, elt.node.get())));
                }
            }
        }
        return keys;
    }

    std::vector<int64_t> Map::getKeysInt(bool _forceSort) const
    {
        auto const keyType = getKeyType(m_schema);
        if (keyType != DataType::integer)
        {
            throw ContextException("Can't call 'getKeysInt' if key is not integer");
        }
        std::vector<int64_t> keys;
        keys.reserve(m_items.size());
        if (_forceSort)
        {
            for (auto const& [key, idx] : m_itemMap)
            {
                auto const& item = m_items[idx];
                if (item.isPresent.get())
                {
                    keys.push_back(std::get<int64_t>(getChildKey(m_schema, item.node.get())));
                }
            }
        }
        else
        {
            for (auto const& elt : m_items)
            {
                if (elt.isPresent.get())
                {
                    keys.push_back(std::get<int64_t>(getChildKey(m_schema, elt.node.get())));
                }
            }
        }
        return keys;
    }

    EntityLib const* Map::getEntityLib() const
    {
        return m_entlib;
    }

    std::vector<NodeUniquePtr> Map::releaseAllElements()
    {
        std::vector<NodeUniquePtr> releasedElts;
        SubschemaRef const* itemSchema = m_schema->singularItems.get();
        for (auto& elt : m_items)
        {
            if (elt.isPresent.get())
            {
                releasedElts.push_back(std::move(elt.node));
                elt.isPresent.set(false);
                elt.node = m_entlib->loadNode(itemSchema->get(), json(), nullptr);
                elt.node->setAddedInInsance(false);
            }
        }
        m_items.clear();
        m_itemMap.clear();
        return releasedElts;
    }

    struct KeyToString
    {
        NodeRef operator()(String const& key) const
        {
            return key.c_str();
        }

        NodeRef operator()(int64_t const& key) const
        {
            return format("lli", key);
        }
    };

    NodeRef Map::computeNodeRefToChild(Node const* _child) const
    {
        for (auto const& [key, idx] : m_itemMap)
        {
            auto const& item = m_items[idx];
            if (item.isPresent.get() and getEltValue(m_schema, item) == _child)
            {
                return std::visit(KeyToString{}, key);
            }
        }
        ENTLIB_LOGIC_ERROR("_child is not a child of this Map");
    }

} // namespace Ent
