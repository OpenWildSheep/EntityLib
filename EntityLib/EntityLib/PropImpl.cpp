#include "PropImpl.h"
#include "include/EntityLib.h"

namespace Ent
{
    void PropImpl::setDefault(
        Subschema const* _schema, char const* _filePath, nlohmann::json const* _document)
    {
        // Loïc : To fix this aweful const_cast, FileProperty need a const version 'ConstFileCursor'.
        // This is a "not-so-easy" task just to remove a const_cast so it is not a priority I guess.
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        m_default = FileProperty{_schema, _filePath, const_cast<nlohmann::json*>(_document)};
    }

    FileProperty* PropImpl::getDefault()
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<FileProperty*>(std::as_const(*this).getDefault());
    }
    FileProperty const* PropImpl::getDefault() const
    {
        if (not m_default.has_value())
        {
            return nullptr;
        }
        return &(*m_default);
    }

    bool PropImpl::isSet() const
    {
        return m_instance.isSet();
    }

    template <typename V>
    V PropImpl::get() const
    {
        if (isSet())
        {
            return m_instance.get<V>();
        }
        else if (m_prefab != nullptr)
        {
            return m_prefab->get<V>();
        }
        else if (auto* defaultVal = getDefault(); defaultVal != nullptr and defaultVal->isSet())
        {
            return defaultVal->get<V>();
        }
        else if constexpr (std::is_same_v<char const*, V>)
        {
            if (not getSchema()->enumValues.empty())
            {
                return getSchema()->enumValues.front().c_str();
            }
            else
            {
                return "";
            }
        }
        else
        {
            return V();
        }
    }

    double PropImpl::getFloat() const
    {
        return get<double>();
    }
    int64_t PropImpl::getInt() const
    {
        return get<int64_t>();
    }
    char const* PropImpl::getString() const
    {
        return get<char const*>();
    }
    bool PropImpl::getBool() const
    {
        return get<bool>();
    }
    EntityRef PropImpl::getEntityRef() const
    {
        return get<EntityRef>();
    }

    PropImpl::PropImpl() = default;

    PropImpl::PropImpl(
        EntityLib* _entityLib,
        PropImplPtr _parent,
        Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc)
    {
        if (_doc == nullptr)
        {
            _doc = &_entityLib->readJsonFile(_filename);
        }
        ENTLIB_ASSERT(_schema != nullptr);
        m_entityLib = _entityLib;
        m_parent = std::move(_parent);

        setDefault(_schema, nullptr, &_schema->defaultValue);
        m_instance = FileProperty(_schema, _filename, _doc);
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        _loadInstanceOf();
    }

    PropImpl::PropImpl(
        EntityLib* _entityLib, PropImplPtr _parent, Subschema const* _schema, char const* _filename)
        : PropImpl(
            _entityLib, std::move(_parent), _schema, _filename, &_entityLib->readJsonFile(_filename))
    {
    }

    void PropImpl::save(char const* _filename) const
    {
        m_instance.save(_filename);
    }

    bool PropImpl::isDefault() const
    {
        auto& newLayer = *this;
        if (m_instance.isSet())
        {
            return false;
        }
        if (newLayer.m_prefab != nullptr)
        {
            return newLayer.m_prefab->isDefault();
        }
        return true;
    }

    bool PropImpl::_loadInstanceOf()
    {
        auto* subschema = m_instance.getSchema();
        if ((subschema->type == DataType::object or subschema->type == DataType::oneOf)
            and m_instance.isSet())
        {
            auto* doc = m_instance.getRawJson();
            if (auto member = doc->find("InstanceOf"); member != doc->end())
            {
                if (auto const& prefabPath = member->get_ref<std::string const&>();
                    not prefabPath.empty())
                {
                    m_prefab =
                        m_entityLib->newPropImpl(nullptr, subschema, prefabPath.c_str(), nullptr);
                }
                return true;
            }
        }
        return false;
    }

    PropImplPtr PropImpl::getObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _checkInvariants();
        ENTLIB_DBG_ASSERT(getDataType() == DataType::object);
        auto newLayer = m_entityLib->newPropImpl();
        ENTLIB_DBG_ASSERT(
            getDefault() == nullptr or getDefault()->getSchema()->type == DataType::object);
        newLayer->m_instance = m_instance.getObjectField(_field, _fieldRef);
        newLayer->m_entityLib = m_entityLib;
        newLayer->m_parent = shared_from_this();
        auto* subschema = newLayer->getSchema();
        if (not newLayer->_loadInstanceOf())
        {
            if (m_prefab != nullptr)
            {
                newLayer->m_prefab = m_prefab->getObjectField(_field, _fieldRef);
            }
        }
        bool defaultFound = false;
        auto* defaultVal = getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            auto const objectField = defaultVal->getObjectField(_field, _fieldRef);
            if (objectField.isSet())
            {
                defaultFound = true;
                newLayer->m_default = std::move(objectField);
            }
        }
        if (not defaultFound)
        {
            auto propDefVal = newLayer->m_instance.getPropertyDefaultValue();
            if (propDefVal != nullptr) // If there is property default, use them
            {
                newLayer->setDefault(subschema, nullptr, propDefVal);
            }
            else if (not subschema->defaultValue.is_null())
            {
                newLayer->setDefault(subschema, nullptr, &subschema->defaultValue);
            }
        }
        return newLayer;
    }

    PropImplPtr PropImpl::getUnionData(char const* _type)
    {
        ENTLIB_ASSERT(getSchema()->type == DataType::oneOf);
        if (_type == nullptr)
        {
            _type = getUnionType();
        }
        return _enterItem([_type](auto&& _cur) { return _cur.getUnionData(_type); });
    }

    PropImplPtr PropImpl::getUnionSetItem(char const* _type, Subschema const* _dataSchema)
    {
        if (_dataSchema == nullptr)
        {
            auto& singularItems = m_instance.getSchema()->singularItems;
            if (singularItems != nullptr)
            {
                Subschema const& unionSchema = singularItems->get();
                if (unionSchema.type != DataType::oneOf)
                {
                    throw BadType("PropImpl::enterUnionSetItem : Not an UnionSet");
                }
                auto& unionTypeMap = unionSchema.unionTypeMap;
                if (auto iter = unionTypeMap.find(_type); iter != unionTypeMap.end())
                {
                    _dataSchema = iter->second.dataSchema;
                }
                else
                {
                    throw BadKey(
                        _type, "PropImpl::enterUnionSetItem", m_instance.getSchema()->name.c_str());
                }
            }
            else
            {
                throw BadType("PropImpl::enterUnionSetItem : Not an UnionSet");
            }
        }
        return _enterItem([_type, _dataSchema](auto&& _cur)
                          { return _cur.getUnionSetItem(_type, _dataSchema); });
    }

    template <typename E>
    PropImplPtr PropImpl::_enterItem(E&& _enter)
    {
        _checkInvariants();
        auto newLayerPtr = m_entityLib->newPropImpl();
        PropImpl& newLayer = *newLayerPtr;
        newLayer.m_entityLib = m_entityLib;
        newLayer.m_instance = _enter(m_instance);
        newLayer.m_parent = shared_from_this();
        auto* subschema = newLayer.getSchema();
        auto* defaultVal = getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.m_default = _enter(*defaultVal);
        }
        else if (auto* propDefVal = newLayer.m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, propDefVal);
        }
        else // Use type default
        {
            newLayer.setDefault(subschema, nullptr, &subschema->defaultValue);
        }
        if (not isDefault())
        {
            if (not newLayer._loadInstanceOf())
            {
                if (m_prefab != nullptr)
                {
                    newLayer.m_prefab = _enter(*m_prefab);
                }
            }
        }
        return newLayerPtr;
    }

    PropImplPtr PropImpl::getObjectSetItem(char const* _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.getObjectSetItem(_key); });
    }

    PropImplPtr PropImpl::getObjectSetItem(int64_t _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.getObjectSetItem(_key); });
    }

    PropImplPtr PropImpl::getMapItem(char const* _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.getMapItem(_key); });
    }

    PropImplPtr PropImpl::getMapItem(int64_t _field)
    {
        return _enterItem([_field](auto&& _cur) { return _cur.getMapItem(_field); });
    }

    PropImplPtr PropImpl::getArrayItem(size_t _index)
    {
        _checkInvariants();
        auto newLayerPtr = m_entityLib->newPropImpl();
        PropImpl& newLayer = *newLayerPtr;
        newLayer.m_entityLib = m_entityLib;
        ENTLIB_DBG_ASSERT(m_instance.getSchema()->type == DataType::array);
        newLayer.m_instance = m_instance.getArrayItem(_index);
        newLayer.m_parent = shared_from_this();
        auto* subschema = newLayer.getSchema();
        if (not isDefault())
        {
            if (not newLayer._loadInstanceOf())
            {
                if (m_prefab != nullptr)
                {
                    newLayer.m_prefab = m_prefab->getArrayItem(_index);
                }
            }
        }
        auto* defaultVal = getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.m_default = defaultVal->getArrayItem(_index);
        }
        else if (newLayer.m_instance.getPropertyDefaultValue() != nullptr) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, newLayer.m_instance.getPropertyDefaultValue());
        }
        else // Use type default
        {
            newLayer.setDefault(subschema, nullptr, &subschema->defaultValue);
        }
        return newLayerPtr;
    }

    char const* PropImpl::getInstanceOf()
    {
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Subschema schema;
        schema.type = DataType::string;
        SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        auto field = getObjectField("InstanceOf", &ref);
        if (not field->isSet())
        {
            return nullptr;
        }
        char const* instanceOf = field->getString();
        return instanceOf;
    }

    void PropImpl::setInstanceOf(char const* _instanceOf)
    {
        if (_instanceOf == nullptr)
        {
            throw NullPointerArgument("_instanceOf", __func__);
        }
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Subschema schema;
        schema.type = DataType::string;
        SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        getObjectField("InstanceOf", &ref)->setString(_instanceOf);
        if (strlen(_instanceOf) != 0)
        {
            m_prefab = m_entityLib->newPropImpl(nullptr, getSchema(), _instanceOf, nullptr);
        }
        else
        {
            m_prefab = nullptr;
        }
    }

    char const* PropImpl::getUnionType()
    {
        ENTLIB_ASSERT(getSchema()->type == DataType::oneOf);
        if (char const* type = m_instance.getUnionType())
        {
            return type;
        }
        else if (m_prefab != nullptr)
        {
            if (char const* type2 = m_prefab->getUnionType())
            {
                return type2;
            }
        }
        else if (auto* defaultVal = getDefault())
        {
            if (char const* type3 = defaultVal->getUnionType())
            {
                return type3;
            }
        }
        return getSchema()->getUnionDefaultTypeName();
    }

    size_t PropImpl::getUnionTypeIndex()
    {
        auto type = getUnionType();
        return AT(getSchema()->unionTypeMap, type).index;
    }

    void PropImpl::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_instance.getSchema() != nullptr);
        ENTLIB_DBG_ASSERT(
            getDefault() == nullptr
            or getDefault()->getSchema()->type == m_instance.getSchema()->type);
        if (m_prefab != nullptr)
        {
            m_prefab->_checkInvariants();
        }
#endif
    }

    DataType PropImpl::getDataType() const
    {
        return m_instance.getSchema()->type;
    }

    Subschema const* PropImpl::getSchema() const
    {
        return m_instance.getSchema();
    }

    char const* PropImpl::getTypeName() const
    {
        return getSchema()->name.c_str();
    }

    DataType PropImpl::getMapKeyType() const
    {
        return m_instance.getSchema()->singularItems->get().linearItems->at(0)->type;
    }

    DataType PropImpl::getObjectSetKeyType() const
    {
        auto& schema = *m_instance.getSchema();
        if (auto arrayMeta = std::get_if<Subschema::ArrayMeta>(&schema.meta))
        {
            if (arrayMeta->keyField.has_value())
            {
                return schema.singularItems->get().properties.at(*arrayMeta->keyField)->type;
            }
        }
        throw BadType(staticFormat(
            "In PropImpl::getObjectSetKeyType : Expected ObjectSet. Got %s", schema.name.c_str()));
    }

    size_t PropImpl::arraySize()
    {
        auto& jsonExplLayer = m_instance;
        auto* schema = jsonExplLayer.getSchema();
        if (schema->linearItems.has_value())
        {
            return schema->linearItems->size();
        }
        else
        {
            if (isSet())
            {
                return jsonExplLayer.size();
            }
            else if (m_prefab != nullptr)
            {
                return m_prefab->arraySize();
            }
            else if (auto* defaultVal = getDefault(); defaultVal != nullptr and defaultVal->isSet())
            {
                return defaultVal->getRawJson()->size();
            }
            else
            {
                return schema->minItems;
            }
        }
    }

    size_t PropImpl::size()
    {
        auto& jsonExplLayer = m_instance;
        auto* schema = jsonExplLayer.getSchema();
        if (schema->linearItems.has_value())
        {
            return schema->linearItems->size();
        }
        switch (schema->type)
        {
        case DataType::object: return schema->properties.size();
        case DataType::oneOf: return 1;
        case DataType::array:
        {
            auto meta = std::get<Subschema::ArrayMeta>(schema->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                switch (getMapKeyType())
                {
                case DataType::string: return getMapKeysString().size();
                case DataType::integer: return getMapKeysInt().size();
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            case "set"_hash:
            {
                auto& itemType = schema->singularItems->get();
                switch (itemType.type)
                {
                case DataType::integer: return getPrimSetKeysInt().size();
                case DataType::string: return getPrimSetKeysString().size();
                case DataType::oneOf: return getUnionSetKeysString().size();
                case DataType::object:
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case DataType::string: return getObjectSetKeysString().size();
                    case DataType::integer: return getObjectSetKeysInt().size();
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    break;
                }
            }
            break;
            case ""_hash: return arraySize();
            default: ENTLIB_LOGIC_ERROR("override policy!");
            }
        }
        break;
        case DataType::null: return 0;
        case DataType::boolean: return 0;
        case DataType::integer: return 0;
        case DataType::number: return 0;
        case DataType::string: return 0;
        case DataType::entityRef: return 0;
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
        ENTLIB_LOGIC_ERROR("Unexpected DataType!");
    }

    bool PropImpl::contains(Key const& _key)
    {
        auto& jsonExplLayer = m_instance;
        auto* schema = jsonExplLayer.getSchema();
        if (schema->linearItems.has_value())
        {
            return false; // Not a map/set
        }
        switch (schema->type)
        {
        case DataType::object: return schema->properties.count(std::get<std::string>(_key)) != 0;
        case DataType::oneOf: return getUnionType() == std::get<std::string>(_key);
        case DataType::array:
        {
            auto meta = std::get<Subschema::ArrayMeta>(schema->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                switch (getMapKeyType())
                {
                case DataType::string: return mapContains(std::get<std::string>(_key).c_str());
                case DataType::integer: return mapContains(std::get<size_t>(_key));
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            case "set"_hash:
            {
                auto& itemType = schema->singularItems->get();
                switch (itemType.type)
                {
                case DataType::integer: return primSetContains(std::get<size_t>(_key));
                case DataType::string: return primSetContains(std::get<std::string>(_key).c_str());
                case DataType::oneOf: return unionSetContains(std::get<std::string>(_key).c_str());
                case DataType::object:
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case DataType::string:
                        return objectSetContains(std::get<std::string>(_key).c_str());
                    case DataType::integer: return objectSetContains(std::get<size_t>(_key));
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    break;
                }
            }
            break;
            case ""_hash: return false;
            default: ENTLIB_LOGIC_ERROR("override policy!");
            }
        }
        break;
        case DataType::null: return false;
        case DataType::boolean: return false;
        case DataType::integer: return false;
        case DataType::number: return false;
        case DataType::string: return false;
        case DataType::entityRef: return false;
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
        ENTLIB_LOGIC_ERROR("Unexpected DataType!");
    }

    bool PropImpl::empty()
    {
        return size() == 0;
    }

    std::set<char const*, CmpStr> PropImpl::getMapKeysString()
    {
        std::set<char const*, CmpStr> keys;
        if (m_prefab != nullptr)
        {
            keys = m_prefab->getMapKeysString();
        }
        else if (auto* defaultVal = getDefault();
                 defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            auto* node = defaultVal->getRawJson();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (auto const& k_v : *node)
            {
                ENTLIB_DBG_ASSERT(node->is_array());
                auto& key = k_v[0].get_ref<std::string const&>();
                ENTLIB_DBG_ASSERT(node->is_array());
                keys.insert(key.c_str());
                ENTLIB_DBG_ASSERT(node->is_array());
            }
        }
        if (m_instance.isSet())
        {
            auto* node = m_instance.getRawJson();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (size_t i = 0; i < node->size(); ++i)
            {
                ENTLIB_DBG_ASSERT(node->is_array());
                auto pairLayer = getArrayItem(i);
                auto key = pairLayer->getArrayItem(0)->getString();
                ENTLIB_DBG_ASSERT(node->is_array());
                if (pairLayer->getArrayItem(1llu)->isNull())
                {
                    keys.erase(key);
                }
                else
                {
                    keys.insert(key);
                }
                ENTLIB_DBG_ASSERT(node->is_array());
            }
        }
        return keys;
    }

    bool PropImpl::isNull() const
    {
        if (m_instance.isSetOrNull())
        {
            return m_instance.isNull();
        }
        else if (m_prefab != nullptr)
        {
            return m_prefab->isNull();
        }
        else
        {
            return false;
        }
    }
    std::set<int64_t> PropImpl::getMapKeysInt()
    {
        std::set<int64_t> keys;
        if (m_prefab != nullptr)
        {
            keys = m_prefab->getMapKeysInt();
        }
        if (m_instance.isSet())
        {
            auto const arraySize = m_instance.getRawJson()->size();
            for (size_t i = 0; i < arraySize; ++i)
            {
                auto pairLayer = getArrayItem(i);
                auto key = pairLayer->getArrayItem(0llu)->getInt();
                if (pairLayer->getArrayItem(1llu)->isNull())
                {
                    keys.erase(key);
                }
                else
                {
                    keys.insert(key);
                }
            }
        }
        return keys;
    }
    std::set<int64_t> PropImpl::getPrimSetKeysInt()
    {
        std::set<int64_t> keys;
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(getArrayItem(i)->getInt());
            }
        }
        if (m_prefab != nullptr)
        {
            keys.merge(m_prefab->getPrimSetKeysInt());
        }
        return keys;
    }
    std::set<char const*, CmpStr> PropImpl::getPrimSetKeysString()
    {
        std::set<char const*, CmpStr> keys;
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(getArrayItem(i)->getString());
            }
        }
        if (m_prefab != nullptr)
        {
            keys.merge(m_prefab->getPrimSetKeysString());
        }
        return keys;
    }

    std::map<char const*, Subschema const*, CmpStr> PropImpl::getUnionSetKeysString()
    {
        std::map<char const*, Subschema const*, CmpStr> keys;
        if (m_prefab != nullptr)
        {
            keys = m_prefab->getUnionSetKeysString();
        }
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto arrayItem = m_instance.getArrayItem(i);
                auto unionSchema = arrayItem.getUnionSchema();
                bool const isRemoved = (unionSchema == nullptr) or arrayItem.isUnionRemoved();
                if (isRemoved)
                {
                    keys.erase(arrayItem.getUnionType());
                }
                else
                {
                    keys.emplace(arrayItem.getUnionType(), unionSchema);
                }
            }
        }
        return keys;
    }

    std::set<char const*, CmpStr> PropImpl::getObjectSetKeysString()
    {
        auto const& meta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
        std::set<char const*, CmpStr> keys;
        if (m_prefab != nullptr)
        {
            keys = m_prefab->getObjectSetKeysString();
        }
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto objectLayer = getArrayItem(i);
                if (objectLayer->m_instance.isSet()
                    and objectLayer->m_instance.getRawJson()->count("__removed__") != 0)
                {
                    keys.erase(objectLayer->getObjectField(meta.keyField->c_str())->getString());
                }
                else
                {
                    keys.insert(objectLayer->getObjectField(meta.keyField->c_str())->getString());
                }
            }
        }
        return keys;
    }

    std::set<int64_t> PropImpl::getObjectSetKeysInt()
    {
        auto const& meta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
        std::set<int64_t> keys;
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto objLayer = getArrayItem(i);
                if (objLayer->m_instance.isSet()
                    and objLayer->m_instance.getRawJson()->count("__removed__") != 0)
                {
                    keys.erase(getObjectField(meta.keyField->c_str())->getInt());
                }
                else
                {
                    keys.insert(getObjectField(meta.keyField->c_str())->getInt());
                }
            }
        }
        if (m_prefab != nullptr)
        {
            keys.merge(m_prefab->getObjectSetKeysInt());
        }
        return keys;
    }

    bool PropImpl::mapContains(char const* _key)
    {
        return getMapKeysString().count(_key) != 0;
    }
    bool PropImpl::mapContains(int64_t _key)
    {
        return getMapKeysInt().count(_key) != 0;
    }
    bool PropImpl::primSetContains(char const* _key)
    {
        return _countPrimSetKeyImpl(
            _key,
            [this](PropImpl& primLayer, char const* _key)
            { return strcmp(primLayer.getString(), _key) == 0; });
    }
    bool PropImpl::primSetContains(int64_t _key)
    {
        return _countPrimSetKeyImpl(
            _key, [this](PropImpl& primLayer, int64_t _key) { return primLayer.getInt() == _key; });
    }
    bool PropImpl::unionSetContains(char const* _key)
    {
        return getUnionSetKeysString().count(_key) != 0;
    }
    bool PropImpl::objectSetContains(char const* _key)
    {
        return getObjectSetKeysString().count(_key) != 0;
    }
    bool PropImpl::objectSetContains(int64_t _key)
    {
        return getObjectSetKeysInt().count(_key) != 0;
    }

    void PropImpl::_buildPath()
    {
        _checkInvariants();
        std::vector<PropImpl*> allLayers;
        for (PropImpl* iter = this; iter != nullptr; iter = iter->m_parent.get())
        {
            allLayers.push_back(iter);
        }
        std::reverse(begin(allLayers), end(allLayers));
        auto firstNotSet = std::find_if(
            begin(allLayers),
            end(allLayers),
            [](PropImpl const* l) { return not l->m_instance.isSetOrNull(); });
        ENTLIB_ASSERT(firstNotSet != allLayers.begin());
        auto firstNotSetIdx = std::distance(begin(allLayers), firstNotSet);
        ENTLIB_ASSERT(firstNotSetIdx <= ptrdiff_t(allLayers.size()));
        auto lastSet = firstNotSet;
        --lastSet;
        auto endIter = allLayers.end();
        for (; firstNotSet != endIter; ++lastSet, ++firstNotSet, ++firstNotSetIdx)
        {
            size_t arraySize = allLayers[firstNotSetIdx - 1]->m_arraySize;
            auto* firstCursorNotSet = *firstNotSet;
            firstCursorNotSet->m_instance.setRawJson(FileProperty::createChildNode(
                (*lastSet)->m_instance,
                firstCursorNotSet->m_instance.getPathToken(),
                *firstCursorNotSet->m_instance.getSchema(),
                arraySize));
            ENTLIB_ASSERT(firstCursorNotSet->m_instance.isSetOrNull());
        }
        _checkInvariants();
    }
    void PropImpl::setSize(size_t _size)
    {
        _buildPath();
        m_instance.setSize(_size);
    }

    void PropImpl::setFloat(double _value)
    {
        _buildPath();
        m_instance.setFloat(_value);
    }
    void PropImpl::setInt(int64_t _value)
    {
        _buildPath();
        m_instance.setInt(_value);
    }
    void PropImpl::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        _buildPath();
        m_instance.setString(_value);
    }
    void PropImpl::setBool(bool _value)
    {
        _buildPath();
        m_instance.setBool(_value);
    }
    void PropImpl::setEntityRef(EntityRef const& _value)
    {
        _buildPath();
        m_instance.setEntityRef(_value);
    }
    void PropImpl::setUnionType(char const* _type)
    {
        _buildPath();
        m_instance.setUnionType(_type);
    }
    void PropImpl::buildPath()
    {
        _buildPath();
    }

    template <typename K, typename E>
    bool PropImpl::_countPrimSetKeyImpl(K _key, E&& _isEqual)
    {
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto item = getArrayItem(i);
                bool const equal = _isEqual(*item, _key);
                if (equal)
                {
                    return true;
                }
            }
        }
        if (m_prefab != nullptr)
        {
            return m_prefab->primSetContains(_key);
        }
        return false;
    }

    void PropImpl::insertPrimSetKey(char const* _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
        }
    }
    void PropImpl::insertPrimSetKey(int64_t _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
        }
    }

    nlohmann::json const* PropImpl::getRawJson()
    {
        return m_instance.getRawJson();
    }

    void decRef(PropImpl* self)
    {
        ENTLIB_ASSERT(self->m_refCount > 0);
        ENTLIB_ASSERT(self->m_deleteCheck.state_ == DeleteCheck::State::VALID);
        --self->m_refCount;
        if (self->m_refCount == 0)
        {
            auto& pool = self->m_entityLib->propertyPool;
            self->~PropImpl();
            pool.free(self);
            self = nullptr;
        }
    }

} // namespace Ent
