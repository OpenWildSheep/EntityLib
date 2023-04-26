#include "PropImpl.h"
#include "include/EntityLib.h"

namespace Ent
{

    void PropImpl::_checkKind(DataKind _expectedKind, char const* _funcName)
    {
        if (auto kind = getDataKind(); kind != _expectedKind)
        {
            throw BadType(staticFormat(
                "In %s : Expected %s. Got %s (schema : %s)",
                _funcName,
                DataKindStr[static_cast<size_t>(_expectedKind)],
                DataKindStr[static_cast<size_t>(kind)],
                getSchema()->name.c_str()));
        }
    }

#define CHECK_TYPE(KIND) _checkKind(KIND, __func__)

    void PropImpl::_setDefault(
        Subschema const* _schema, char const* _filePath, nlohmann::json const* _document)
    {
        // Loïc : To fix this aweful const_cast, FileProperty need a const version 'ConstFileCursor'.
        // This is a "not-so-easy" task just to remove a const_cast so it is not a priority I guess.
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        m_default = FileProperty(
            *m_entityLib, _schema, _filePath, const_cast<nlohmann::json*>(_document), nullptr);
    }

    FileProperty const& PropImpl::_getDefault() const
    {
        return m_default;
    }

    bool PropImpl::isSet()
    {
        _reResolveIfNeeded();
        return m_instance.isSet();
    }

    template <typename V>
    V PropImpl::get()
    {
        _reResolveIfNeeded();
        if (isSet())
        {
            return m_instance.get<V>();
        }
        if (m_prefab != nullptr)
        {
            return m_prefab->get<V>();
        }
        if (_getDefault().isSet())
        {
            return _getDefault().get<V>();
        }
        if constexpr (std::is_same_v<char const*, V>)
        {
            if (not getSchema()->enumValues.empty())
            {
                return getSchema()->enumValues.front().c_str();
            }
            return "";
        }
        else
        {
            return V();
        }
    }

    double PropImpl::getFloat()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::number);
        return get<double>();
    }
    int64_t PropImpl::getInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::integer);
        return get<int64_t>();
    }
    char const* PropImpl::getString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::string);
        return get<char const*>();
    }
    bool PropImpl::getBool()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::boolean);
        return get<bool>();
    }
    EntityRef PropImpl::getEntityRef()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::entityRef);
        return get<EntityRef>();
    }

    PropImpl::PropImpl(EntityLib* _entityLib)
        : m_entityLib(_entityLib)
        , m_default(*_entityLib)
        , m_instance(*_entityLib)
    {
    }

    PropImpl::PropImpl(
        EntityLib* _entityLib,
        PropImplPtr _parent,
        Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc,
        JsonMetaData* _metaData)
        : m_default(*_entityLib)
        , m_instance(*_entityLib)
    {
        if (_doc == nullptr)
        {
            auto& versionedDoc = _entityLib->readJsonFile(_filename);
            _doc = &versionedDoc.document;
            _metaData = &versionedDoc.metadata;
        }
        ENTLIB_ASSERT(_schema != nullptr);
        m_entityLib = _entityLib;
        m_parent = std::move(_parent);

        _setDefault(_schema, nullptr, &_schema->defaultValue);
        m_instance = FileProperty(*_entityLib, _schema, _filename, _doc, _metaData);
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        _loadInstanceOf();
    }

    PropImpl::PropImpl(
        EntityLib* _entityLib,
        PropImplPtr _parent,
        Subschema const* _schema,
        char const* _filename,
        VersionedJson& _document)
        : PropImpl(
            _entityLib, std::move(_parent), _schema, _filename, &_document.document, &_document.metadata)
    {
    }

    PropImpl::PropImpl(
        EntityLib* _entityLib, PropImplPtr _parent, Subschema const* _schema, char const* _filename)
        : PropImpl(
            _entityLib, std::move(_parent), _schema, _filename, _entityLib->readJsonFile(_filename))
    {
    }

    void PropImpl::save(char const* _filename)
    {
        _reResolveIfNeeded();
        m_instance.save(_filename);
    }

    bool PropImpl::isDefault()
    {
        _reResolveIfNeeded();
        auto const& newLayer = *this;
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
        auto const* subschema = m_instance.getSchema();
        if ((subschema->type == DataType::object or subschema->type == DataType::oneOf)
            and m_instance.isSet())
        {
            if (auto const* doc = m_instance.getJson())
            {
                if (auto const member = doc->find("InstanceOf"); member != doc->end())
                {
                    if (member->is_null()) // InstanceOf is null, there is no prefab
                    {
                        return false;
                    }
                    if (auto const& prefabPath = member->get_ref<std::string const&>();
                        not prefabPath.empty())
                    {
                        m_prefab = m_entityLib->newPropImpl(
                            nullptr, subschema, prefabPath.c_str(), nullptr, nullptr);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    PropImplPtr PropImpl::_getField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _reResolveIfNeeded();
        _checkInvariants();
        auto newLayer = m_entityLib->newPropImpl();
        newLayer->m_instance = m_instance.getObjectField(_field, _fieldRef);
        newLayer->m_entityLib = m_entityLib;
        newLayer->m_parent = sharedFromThis();
        auto const* subschema = newLayer->getSchema();
        if (not newLayer->_loadInstanceOf())
        {
            auto const parent = getParent();
            if (not m_instance.isRemovedObject(parent ? parent->getSchema() : nullptr)
                and m_prefab != nullptr)
            {
                newLayer->m_prefab = m_prefab->_getField(_field, _fieldRef);
            }
        }
        bool defaultFound = false;
        auto const& defaultVal = _getDefault();
        if (defaultVal.isSet()) // If there is default, enter in
        {
            auto objectField = defaultVal.getObjectField(_field, _fieldRef);
            if (objectField.isSet())
            {
                defaultFound = true;
                newLayer->m_default = std::move(objectField);
            }
        }
        if (not defaultFound)
        {
            auto const* const propDefVal = newLayer->m_instance.getPropertyDefaultValue();
            if (propDefVal != nullptr) // If there is property default, use them
            {
                newLayer->_setDefault(subschema, nullptr, propDefVal);
            }
            else if (not subschema->defaultValue.is_null())
            {
                newLayer->_setDefault(subschema, nullptr, &subschema->defaultValue);
            }
            else
            {
                newLayer->_setDefault(subschema, nullptr, nullptr);
            }
        }
        return newLayer;
    }

    PropImplPtr PropImpl::getObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        CHECK_TYPE(DataKind::object);
        ENTLIB_DBG_ASSERT(_getDefault().getSchema()->type == DataType::object);
        return _getField(_field, _fieldRef);
    }

    PropImplPtr PropImpl::getUnionData(char const* _type)
    {
        _reResolveIfNeeded();
        auto [data, exists] = forceGetUnionData(_type);
        if (exists)
        {
            return std::move(data);
        }
        return nullptr;
    }

    std::pair<PropImplPtr, bool> PropImpl::forceGetUnionData(char const* _type)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::union_);
        if (_type == nullptr)
        {
            _type = getUnionType();
        }
        bool const isDefaultUnionType = strcmp(getSchema()->getUnionDefaultTypeName(), _type) == 0;
        auto res = _enterItem(
            [_type](auto&& _cur) { return _cur.forceGetUnionData(_type); }, isDefaultUnionType);
        return res;
    }

    std::pair<PropImplPtr, bool>
    PropImpl::forceGetUnionSetItem(char const* _type, Subschema const* _dataSchema)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        if (_dataSchema == nullptr)
        {
            if (auto const& singularItems = m_instance.getSchema()->singularItems)
            {
                Subschema const& unionSchema = singularItems->get();
                if (unionSchema.type != DataType::oneOf)
                {
                    throw BadType("PropImpl::enterUnionSetItem : Not an UnionSet");
                }
                auto const& unionTypeMap = unionSchema.unionTypeMap;
                if (auto const iter = unionTypeMap.find(_type); iter != unionTypeMap.end())
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
                          { return _cur.forceGetUnionSetItem(_type, _dataSchema); });
    }

    PropImplPtr PropImpl::getUnionSetItem(char const* _type, Subschema const* _dataSchema)
    {
        _reResolveIfNeeded();
        if (auto [item, exist] = forceGetUnionSetItem(_type, _dataSchema); exist)
        {
            return std::move(item);
        }
        return nullptr;
    }

    PropImplPtr PropImpl::getObjectSetItem(char const* _key)
    {
        _reResolveIfNeeded();
        if (auto [item, exist] = forceGetObjectSetItem(_key); exist)
        {
            return std::move(item);
        }
        return nullptr;
    }
    PropImplPtr PropImpl::getObjectSetItem(int64_t _key)
    {
        _reResolveIfNeeded();
        if (auto [item, exist] = forceGetObjectSetItem(_key); exist)
        {
            return std::move(item);
        }
        return nullptr;
    }
    PropImplPtr PropImpl::getMapItem(char const* _key)
    {
        _reResolveIfNeeded();
        if (auto [item, exist] = forceGetMapItem(_key); exist)
        {
            return std::move(item);
        }
        return nullptr;
    }
    PropImplPtr PropImpl::getMapItem(int64_t _field)
    {
        _reResolveIfNeeded();
        if (auto [item, exist] = forceGetMapItem(_field); exist)
        {
            return std::move(item);
        }
        return nullptr;
    }

    template <typename E>
    std::pair<PropImplPtr, bool> PropImpl::_enterItem(
        E&& _enter,
        bool _isDefaultUnionType // = false
    )
    {
        _checkInvariants();
        auto newLayerPtr = m_entityLib->newPropImpl();
        PropImpl& newLayer = *newLayerPtr;
        newLayer.m_entityLib = m_entityLib;
        auto foundInInst = FileProperty::MapItemAction::None;
        auto foundInDefault = FileProperty::MapItemAction::None;
        bool found = false;
        std::tie(newLayer.m_instance, foundInInst) = _enter(m_instance);
        newLayer.m_parent = sharedFromThis();
        auto const* subschema = newLayer.getSchema();
        auto const& defaultVal = _getDefault();
        if (defaultVal.isSet()) // If there is default, enter in
        {
            std::tie(newLayer.m_default, foundInDefault) = _enter(defaultVal);
            found = foundInDefault == FileProperty::MapItemAction::Add;
        }
        else if (auto const* propDefVal = newLayer.m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer._setDefault(subschema, nullptr, propDefVal);
        }
        else // Use type default
        {
            newLayer._setDefault(subschema, nullptr, &subschema->defaultValue);
            if (_isDefaultUnionType)
            {
                found = true;
            }
        }
        if (not newLayer._loadInstanceOf())
        {
            if (m_prefab != nullptr)
            {
                std::tie(newLayer.m_prefab, found) = _enter(*m_prefab);
            }
        }
        if (newLayerPtr->_getDefault().getSchema() == nullptr)
        {
            newLayerPtr->_setDefault(subschema, nullptr, nullptr);
        }
        found = foundInInst == FileProperty::MapItemAction::Add    ? true :
                foundInInst == FileProperty::MapItemAction::Remove ? false :
                                                                     found;
        return std::pair{std::move(newLayerPtr), found};
    }

    std::pair<PropImplPtr, bool> PropImpl::forceGetObjectSetItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return _enterItem([_key](auto&& _cur) { return _cur.forceGetObjectSetItem(_key); });
    }

    std::pair<PropImplPtr, bool> PropImpl::forceGetObjectSetItem(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return _enterItem([_key](auto&& _cur) { return _cur.forceGetObjectSetItem(_key); });
    }

    std::pair<PropImplPtr, bool> PropImpl::forceGetMapItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return _enterItem([_key](auto&& _cur) { return _cur.forceGetMapItem(_key); });
    }

    std::pair<PropImplPtr, bool> PropImpl::forceGetMapItem(int64_t _field)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return _enterItem([_field](auto&& _cur) { return _cur.forceGetMapItem(_field); });
    }

    PropImplPtr PropImpl::getArrayItem(size_t _index)
    {
        _reResolveIfNeeded();
        _checkInvariants();
        auto newLayerPtr = m_entityLib->newPropImpl();
        PropImpl& newLayer = *newLayerPtr;
        newLayer.m_entityLib = m_entityLib;
        ENTLIB_DBG_ASSERT(m_instance.getSchema()->type == DataType::array);
        newLayer.m_instance = m_instance.getArrayItem(_index);
        newLayer.m_parent = sharedFromThis();
        auto const* subschema = newLayer.getSchema();
        if (not newLayer._loadInstanceOf())
        {
            if (m_prefab != nullptr)
            {
                newLayer.m_prefab = m_prefab->getArrayItem(_index);
            }
        }
        auto const& defaultVal = _getDefault();
        if (defaultVal.isSet()) // If there is default, enter in
        {
            newLayer.m_default = defaultVal.getArrayItem(_index);
        }
        else if (newLayer.m_instance.getPropertyDefaultValue() != nullptr) // If there is property default, use them
        {
            newLayer._setDefault(subschema, nullptr, newLayer.m_instance.getPropertyDefaultValue());
        }
        else // Use type default
        {
            newLayer._setDefault(subschema, nullptr, &subschema->defaultValue);
        }
        return newLayerPtr;
    }

    char const* PropImpl::getInstanceOf()
    {
        _reResolveIfNeeded();
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Subschema schema;
        schema.type = DataType::string;
        schema.setDataKind(DataKind::string);
        SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        auto const field = _getField("InstanceOf", &ref);
        if (not field->isSet())
        {
            return nullptr;
        }
        char const* instanceOf = field->getString();
        return instanceOf;
    }

    char const* PropImpl::getFirstInstanceOf()
    {
        auto prefab = this;
        while (prefab->getPrefab() != nullptr)
        {
            if (char const* prefabName = prefab->getInstanceOf())
            {
                return prefabName;
            }
            prefab = prefab->getPrefab();
        }
        return nullptr;
    }

    void PropImpl::resetInstanceOf(char const* _instanceOf)
    {
        _reResolveIfNeeded();
        unset();
        changeInstanceOf(_instanceOf);
    }

    void PropImpl::changeInstanceOf(char const* _instanceOf)
    {
        _reResolveIfNeeded();
        if (_instanceOf == nullptr)
        {
            throw NullPointerArgument("_instanceOf", __func__);
        }
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Subschema schema;
        schema.type = DataType::string;
        schema.setDataKind(DataKind::string);
        SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        getObjectField("InstanceOf", &ref)
            ->setString(m_entityLib->getRelativePath(_instanceOf).generic_u8string().c_str());
        if (strlen(_instanceOf) != 0)
        {
            m_prefab = m_entityLib->newPropImpl(nullptr, getSchema(), _instanceOf, nullptr, nullptr);
        }
        else
        {
            m_prefab = nullptr;
        }
    }

    PropImplPtr PropImpl::makeInstanceOf()
    {
        _reResolveIfNeeded();
        auto& jsonDoc = m_entityLib->createTempJsonFile(getSchema()->name.c_str());
        if (auto prefabPath = m_instance.getFilePath())
        {
            // If it has no FilePath, it isn't a root node, so we can't reference it in an InstanceOf path
            if (strlen(prefabPath) != 0)
            {
                jsonDoc.document["InstanceOf"] = prefabPath;
            }
        }
        auto instProp =
            m_entityLib->newPropImpl(nullptr, getSchema(), "", &jsonDoc.document, &jsonDoc.metadata);
        instProp->m_prefab = sharedFromThis();
        return instProp;
    }

    char const* PropImpl::getUnionType()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::union_);
        ENTLIB_ASSERT(getSchema()->type == DataType::oneOf);
        if (char const* type = m_instance.getUnionType())
        {
            return type;
        }
        if (m_prefab != nullptr)
        {
            if (char const* type2 = m_prefab->getUnionType())
            {
                return type2;
            }
        }
        else if (char const* type3 = _getDefault().getUnionType())
        {
            return type3;
        }
        return getSchema()->getUnionDefaultTypeName();
    }

    size_t PropImpl::getUnionTypeIndex()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::union_);
        auto const* const type = getUnionType();
        return AT(getSchema()->unionTypeMap, type).index;
    }

    void PropImpl::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_instance.getSchema() != nullptr);
        ENTLIB_DBG_ASSERT(_getDefault().getSchema()->type == m_instance.getSchema()->type);
        if (m_prefab != nullptr)
        {
            m_prefab->_checkInvariants();
        }
#endif
    }

    DataType PropImpl::getDataType()
    {
        _reResolveIfNeeded();
        return m_instance.getSchema()->type;
    }

    Subschema const* PropImpl::getSchema()
    {
        _reResolveIfNeeded();
        return m_instance.getSchema();
    }

    char const* PropImpl::getTypeName()
    {
        _reResolveIfNeeded();
        return getSchema()->name.c_str();
    }

    DataType PropImpl::getMapKeyType()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return m_instance.getMapKeyType();
    }

    DataType PropImpl::getObjectSetKeyType()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        auto const& schema = *m_instance.getSchema();
        if (auto const* const arrayMeta = std::get_if<Subschema::ArrayMeta>(&schema.meta))
        {
            if (arrayMeta->keyField.has_value())
            {
                return schema.singularItems->get().properties.at(*arrayMeta->keyField)->type;
            }
        }
        throw BadType(staticFormat(
            "In PropImpl::getObjectSetKeyType : Expected ObjectSet. Got %s", schema.name.c_str()));
    }

    DataType PropImpl::getPrimSetKeyType()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        _checkInvariants();
        auto const& schema = *m_instance.getSchema();
        return schema.singularItems->get().type;
    }

    size_t PropImpl::arraySize()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::array);
        auto const& jsonExplLayer = m_instance;
        auto const* schema = jsonExplLayer.getSchema();
        if (schema->linearItems.has_value())
        {
            return schema->linearItems->size();
        }
        if (isSet())
        {
            return jsonExplLayer.size();
        }
        if (m_prefab != nullptr)
        {
            return m_prefab->arraySize();
        }
        if (_getDefault().isSet())
        {
            return _getDefault().getJson()->size();
        }
        return schema->minItems;
    }

    size_t PropImpl::size()
    {
        _reResolveIfNeeded();
        auto const& jsonExplLayer = m_instance;
        auto const* schema = jsonExplLayer.getSchema();
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
                case DataType::entityRef: [[fallthrough]];
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
                case DataType::entityRef: [[fallthrough]];
                case DataType::string: return getPrimSetKeysString().size();
                case DataType::oneOf: return getUnionSetKeysString().size();
                case DataType::object:
                    auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case DataType::entityRef: [[fallthrough]];
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
        _reResolveIfNeeded();
        auto const& jsonExplLayer = m_instance;
        auto const* schema = jsonExplLayer.getSchema();
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
                case DataType::entityRef: [[fallthrough]];
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
                case DataType::entityRef: [[fallthrough]];
                case DataType::string: return primSetContains(std::get<std::string>(_key).c_str());
                case DataType::oneOf: return unionSetContains(std::get<std::string>(_key).c_str());
                case DataType::object:
                    auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case DataType::entityRef: [[fallthrough]];
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
        _reResolveIfNeeded();
        return size() == 0;
    }

    template <typename Container, typename F>
    Container PropImpl::_getKeys(F const& getKeysInFile)
    {
        Container keys;
        if (m_prefab != nullptr) // If there is a prefab, get prefab's keys
        {
            keys = m_prefab->_getKeys<Container, F>(getKeysInFile);
        }
        else // else, get the dfault keys
        {
            getKeysInFile(_getDefault(), keys);
        }
        // Anyway, add or remove keys from instance
        getKeysInFile(m_instance, keys);
        return keys;
    }

    std::set<char const*, CmpStr> PropImpl::getMapKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return _getKeys<std::set<char const*, CmpStr>>([](FileProperty const& _file, auto& _keys)
                                                       { _file.updateMapKeysString(_keys); });
    }

    bool PropImpl::isNull()
    {
        _reResolveIfNeeded();
        if (m_instance.hasJsonPointer())
        {
            return m_instance.isNull();
        }
        if (m_prefab != nullptr)
        {
            return m_prefab->isNull();
        }
        return false;
    }
    std::set<int64_t> PropImpl::getMapKeysInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return _getKeys<std::set<int64_t>>([](FileProperty const& _file, auto& _keys)
                                           { _file.updateMapKeysInt(_keys); });
    }
    std::set<int64_t> PropImpl::getPrimSetKeysInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        return _getKeys<std::set<int64_t>>([](FileProperty const& _file, auto& _keys)
                                           { _file.updatePrimSetKeysInt(_keys); });
    }
    std::set<char const*, CmpStr> PropImpl::getPrimSetKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        return _getKeys<std::set<char const*, CmpStr>>([](FileProperty const& _file, auto& _keys)
                                                       { _file.updatePrimSetKeysString(_keys); });
    }

    std::map<char const*, Subschema const*, CmpStr> PropImpl::getUnionSetKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        return _getKeys<std::map<char const*, Subschema const*, CmpStr>>(
            [](FileProperty const& _file, auto& _keys) { _file.updateUnionSetKeysString(_keys); });
    }

    std::set<char const*, CmpStr> PropImpl::getObjectSetKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return _getKeys<std::set<char const*, CmpStr>>([](FileProperty const& _file, auto& _keys)
                                                       { _file.updateObjectSetKeysString(_keys); });
    }

    std::set<int64_t> PropImpl::getObjectSetKeysInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return _getKeys<std::set<int64_t>>([](FileProperty const& _file, auto& _keys)
                                           { _file.updateObjectSetKeysInt(_keys); });
    }

    std::set<char const*, CmpStr> PropImpl::getMapRemovedKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return m_instance.getMapRemovedKeysString();
    }
    std::set<int64_t> PropImpl::getMapRemovedKeysInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return m_instance.getMapRemovedKeysInt();
    }
    std::map<char const*, Subschema const*, CmpStr> PropImpl::getUnionSetRemovedKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        return m_instance.getUnionSetRemovedKeysString();
    }
    std::set<char const*, CmpStr> PropImpl::getObjectSetRemovedKeysString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return m_instance.getObjectSetRemovedKeysString();
    }
    std::set<int64_t> PropImpl::getObjectSetRemovedKeysInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return m_instance.getObjectSetRemovedKeysInt();
    }

    bool PropImpl::mapContains(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return getMapKeysString().count(_key) != 0;
    }
    bool PropImpl::mapContains(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        return getMapKeysInt().count(_key) != 0;
    }
    bool PropImpl::primSetContains(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        return _countPrimSetKeyImpl(_key);
    }
    bool PropImpl::primSetContains(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        return _countPrimSetKeyImpl(_key);
    }
    bool PropImpl::unionSetContains(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        return getUnionSetKeysString().count(_key) != 0;
    }
    bool PropImpl::objectSetContains(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return getObjectSetKeysString().count(_key) != 0;
    }
    bool PropImpl::objectSetContains(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        return getObjectSetKeysInt().count(_key) != 0;
    }

    void PropImpl::_buildPath()
    {
        _checkInvariants();
        std::vector<PropImpl*> allLayers;
        for (auto* iter = this; iter != nullptr; iter = iter->m_parent.get())
        {
            allLayers.push_back(iter);
        }
        auto needToCreateOrRestoreNode = [](PropImpl* _prop)
        {
            auto const parent = _prop->getParent();
            return not _prop->m_instance.hasJsonPointer()
                   or _prop->m_instance.isRemovedObject(parent ? parent->getSchema() : nullptr);
        };
        std::reverse(begin(allLayers), end(allLayers));
        auto firstNotSet = std::find_if(begin(allLayers), end(allLayers), needToCreateOrRestoreNode);
        ENTLIB_ASSERT(firstNotSet != allLayers.begin());
        auto firstNotSetIdx = std::distance(begin(allLayers), firstNotSet);
        ENTLIB_ASSERT(firstNotSetIdx <= static_cast<ptrdiff_t>(allLayers.size()));
        auto lastSet = firstNotSet;
        --lastSet;
        auto const endIter = allLayers.end();
        for (; firstNotSet != endIter; ++lastSet, ++firstNotSet, ++firstNotSetIdx)
        {
            size_t _prefabSize = 0;
            if (auto prefab = (*firstNotSet)->getPrefab())
            {
                if (prefab->getDataKind() == DataKind::array)
                {
                    _prefabSize = prefab->arraySize();
                }
            }
            (*firstNotSet)->m_instance.createChildNode((*lastSet)->m_instance, _prefabSize);
            ENTLIB_ASSERT(not needToCreateOrRestoreNode(*firstNotSet));
        }
        _checkInvariants();
        _updateParentToResolved();
    }
    void PropImpl::setSize(size_t _size)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::array);
        _buildPath();
        m_instance.setSize(_size);
        _updateParentToResolved();
    }

    void PropImpl::clearArray()
    {
        _reResolveIfNeeded();
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        setSize(getSchema()->minItems);
        for (size_t i = 0; i < getSchema()->minItems; ++i)
        {
            getArrayItem(i)->clear();
        }
    }

    void PropImpl::clearMap()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        switch (getMapKeyType()) // NOLINT(clang-diagnostic-switch-enum)
        {
        case DataType::integer:
            for (auto const key : getMapKeysInt())
            {
                eraseMapItem(key);
            }
            break;
        case DataType::string:
        case DataType::entityRef:
            for (auto const key : getMapKeysString())
            {
                eraseMapItem(key);
            }
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected map key type");
        }
    }

    void PropImpl::clearPrimSet()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        switch (getPrimSetKeyType()) // NOLINT(clang-diagnostic-switch-enum)
        {
        case DataType::integer:
            for (auto const key : getPrimSetKeysInt())
            {
                erasePrimSetKey(key);
            }
            break;
        case DataType::string:
        case DataType::entityRef:
            for (auto const key : getPrimSetKeysString())
            {
                erasePrimSetKey(key);
            }
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected primitiveSet key type");
        }
    }

    void PropImpl::clearObjectSet()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        switch (getObjectSetKeyType()) // NOLINT(clang-diagnostic-switch-enum)
        {
        case DataType::integer:
            for (auto const key : getObjectSetKeysInt())
            {
                eraseObjectSetItem(key);
            }
            break;
        case DataType::string:
        case DataType::entityRef:
            for (auto const key : getObjectSetKeysString())
            {
                eraseObjectSetItem(key);
            }
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected objectSet key type");
        }
    }

    void PropImpl::clearUnionSet()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        for (auto const [key, schema] : getUnionSetKeysString())
        {
            eraseUnionSetItem(key);
        }
    }

    void PropImpl::clearObject()
    {
        _reResolveIfNeeded();
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        for (auto&& [name, prop] : getSchema()->properties)
        {
            getObjectField(name.c_str())->clear();
        }
    }

    void PropImpl::clearUnion()
    {
        _reResolveIfNeeded();
        if (not hasPrefabValue())
        {
            unset();
            return;
        }
        setUnionType(getDefaultUnionType())->clear();
    }

    void PropImpl::clear()
    {
        _reResolveIfNeeded();
        auto clearPrim = [this](auto&& setDefault)
        {
            if (not hasPrefabValue())
            {
                unset();
                return;
            }
            if (hasPrefabValue())
            {
                setDefault();
            }
            else
            {
                unset();
            }
        };

        auto const kind = getDataKind();
        switch (kind)
        {
        case DataKind::array: clearArray(); break;
        case DataKind::map: clearMap(); break;
        case DataKind::unionSet: clearUnionSet(); break;
        case DataKind::objectSet: clearObjectSet(); break;
        case DataKind::primitiveSet: clearPrimSet(); break;
        case DataKind::entityRef: clearPrim([this] { setEntityRef(getDefaultEntityRef()); }); break;
        case DataKind::boolean: clearPrim([this] { setBool(getDefaultBool()); }); break;
        case DataKind::number: clearPrim([this] { setFloat(getDefaultFloat()); }); break;
        case DataKind::integer: clearPrim([this] { setInt(getDefaultInt()); }); break;
        case DataKind::string: clearPrim([this] { setString(getDefaultString()); }); break;
        case DataKind::object: clearObject(); break;
        case DataKind::union_: clearUnion(); break;
        default:
            throw BadType(staticFormat(
                "In %s : Expected Array, Map or Set. Got %s (schema : %s)",
                "clear",
                DataKindStr[static_cast<size_t>(kind)],
                getSchema()->name.c_str()));
        }
    }

    PropImplPtr PropImpl::pushBack()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::array);
        if (arraySize() + 1 > getSchema()->maxItems)
        {
            throw BreakSchemaRules(
                staticFormat("In pushBack : Can't push more than %d items", getSchema()->maxItems));
        }
        setSize(arraySize() + 1);
        return getArrayItem(arraySize() - 1);
    }

    void PropImpl::popBack()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::array);
        if (arraySize() - 1 < getSchema()->minItems)
        {
            throw BreakSchemaRules(
                staticFormat("In popBack : Can't pop less than %d items", getSchema()->minItems));
        }
        setSize(arraySize() - 1);
    }

    template <typename K>
    auto PropImpl::_checkCanRename(K _newName)
    {
        if (getSchema()->isKeyField)
        {
            if (m_parent != nullptr and m_parent->getSchema()->type == DataType::object)
            {
                auto& map = m_parent->m_parent;
                if (map != nullptr and map->getSchema()->getDataKind() == DataKind::objectSet)
                {
                    // If the renaming doesn't change the NodePath of this Property,
                    // it is not really a renaming
                    using KeyType = std::remove_const_t<std::remove_reference_t<K>>;
                    if constexpr (std::is_same_v<KeyType, char const*>)
                    {
                        if (std::get<std::string>(m_parent->getPathToken()) == _newName)
                        {
                            return;
                        }
                    }
                    else if constexpr (std::is_same_v<KeyType, EntityRef>)
                    {
                        if (std::get<std::string>(m_parent->getPathToken())
                            == _newName.entityPath.c_str())
                        {
                            return;
                        }
                    }
                    else if constexpr (std::is_same_v<KeyType, int64_t>)
                    {
                        if (std::get<int64_t>(m_parent->getPathToken()) == _newName)
                        {
                            return;
                        }
                    }

                    throw CantRename("Can't rename on object in an ObjectSet");
                }
            }
        }
    }

    void PropImpl::setFloat(double _value)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::number);
        _checkCanRename(_value);
        _buildPath();
        m_instance.setFloat(_value);
        _updateParentToResolved();
    }
    void PropImpl::setInt(int64_t _value)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::integer);
        _checkCanRename(_value);
        _buildPath();
        m_instance.setInt(_value);
        _updateParentToResolved();
    }
    void PropImpl::setString(char const* _value)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::string);
        ENTLIB_ASSERT(_value != nullptr);
        _checkCanRename(_value);
        _buildPath();
        m_instance.setString(_value);
        _updateParentToResolved();
    }
    void PropImpl::setBool(bool _value)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::boolean);
        _checkCanRename(_value);
        _buildPath();
        m_instance.setBool(_value);
        _updateParentToResolved();
    }
    void PropImpl::setEntityRef(EntityRef const& _value)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::entityRef);
        _checkCanRename(_value);
        _buildPath();
        m_instance.setEntityRef(_value);
        _updateParentToResolved();
    }
    PropImplPtr PropImpl::setUnionType(char const* _type)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::union_);
        if (getSchema()->unionTypeMap.count(_type) == 0)
        {
            throw BadUnionType(_type);
        }
        _buildPath();
        m_instance.setUnionType(_type);
        _updateParentToResolved();
        return getUnionData();
    }
    void PropImpl::buildPath()
    {
        _reResolveIfNeeded();
        _buildPath();
    }

    template <typename K>
    bool PropImpl::_countPrimSetKeyImpl(K _key)
    {
        if (m_instance.countPrimSetKey(_key))
        {
            return true;
        }
        if (m_prefab != nullptr)
        {
            return m_prefab->primSetContains(_key);
        }
        return false;
    }

    void PropImpl::insertPrimSetKey(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        auto& keySchema = getSchema()->singularItems->get();
        if (not keySchema.isValidEnumString(_key))
        {
            throw BreakSchemaRules(staticFormat(
                "The value '%s' is not accepted in enum type '%s'", _key, keySchema.name.c_str()));
        }
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
            _updateParentToResolved();
        }
    }
    void PropImpl::insertPrimSetKey(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
            _updateParentToResolved();
        }
    }

    PropImplPtr PropImpl::insertUnionSetItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        auto [newItem, exists] = forceGetUnionSetItem(_key);
        newItem->buildPath();
        return std::move(newItem);
    }

    PropImplPtr PropImpl::insertMapItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        auto [newItem, found] = forceGetMapItem(_key);
        newItem->buildPath();
        return std::move(newItem);
    }

    PropImplPtr PropImpl::insertMapItem(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        auto [newItem, found] = forceGetMapItem(_key);
        newItem->buildPath();
        return std::move(newItem);
    }

    PropImplPtr PropImpl::insertObjectSetItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        auto [newItem, found] = forceGetObjectSetItem(_key);
        newItem->buildPath();
        return std::move(newItem);
    }

    PropImplPtr PropImpl::insertInstanceObjectSetItem(char const* _prefabPath)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        auto const prefab = m_entityLib->newPropImpl(
            nullptr, &getSchema()->singularItems->get(), _prefabPath, nullptr, nullptr);
        auto const& arrayMeta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
        auto const key = prefab->getObjectField(arrayMeta.keyField->c_str());
        PropImplPtr newObj;
        if (key->getDataType() == DataType::integer)
        {
            newObj = insertObjectSetItem(key->getInt());
        }
        else
        {
            newObj = insertObjectSetItem(key->getString());
        }
        newObj->changeInstanceOf(_prefabPath);
        return newObj;
    }

    PropImplPtr PropImpl::insertObjectSetItem(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        auto [newItem, found] = forceGetObjectSetItem(_key);
        newItem->buildPath();
        return std::move(newItem);
    }

    bool PropImpl::erasePrimSetKey(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->primSetContains(_key);
        if (isInPrefab)
        {
            throw BadArrayType("Can't erase in a primitive set if the key is still in the prefab");
        }
        auto erased = m_instance.erasePrimSetKey(_key);
        _updateParentToResolved();
        return erased;
    }
    bool PropImpl::erasePrimSetKey(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::primitiveSet);
        auto erased = m_instance.erasePrimSetKey(_key);
        _updateParentToResolved();
        return erased;
    }
    bool PropImpl::eraseObjectSetItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->objectSetContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        auto erased = m_instance.eraseObjectSetItem(_key, isInPrefab);
        _updateParentToResolved();
        return erased;
    }
    bool PropImpl::eraseObjectSetItem(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::objectSet);
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->objectSetContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        auto erased = m_instance.eraseObjectSetItem(_key, isInPrefab);
        _updateParentToResolved();
        return erased;
    }
    bool PropImpl::eraseUnionSetItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::unionSet);
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->unionSetContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        auto erased = m_instance.eraseUnionSetItem(_key, isInPrefab);
        _updateParentToResolved();
        return erased;
    }
    bool PropImpl::eraseMapItem(char const* _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->mapContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        auto erased = m_instance.eraseMapItem(_key, isInPrefab);
        _updateParentToResolved();
        return erased;
    }
    bool PropImpl::eraseMapItem(int64_t _key)
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::map);
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->mapContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        auto erased = m_instance.eraseMapItem(_key, isInPrefab);
        _updateParentToResolved();
        return erased;
    }

    nlohmann::json const* PropImpl::getRawJson()
    {
        _reResolveIfNeeded();
        return m_instance.getJson();
    }

    double PropImpl::getDefaultFloat()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::number);
        return m_default.getFloat();
    }
    int64_t PropImpl::getDefaultInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::integer);
        return m_default.getInt();
    }
    char const* PropImpl::getDefaultString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::string);
        return m_default.getString();
    }
    bool PropImpl::getDefaultBool()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::boolean);
        return m_default.getBool();
    }
    EntityRef PropImpl::getDefaultEntityRef()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::entityRef);
        return m_default.getEntityRef();
    }

    char const* PropImpl::getDefaultUnionType()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::union_);
        return m_default.getUnionType();
    }

    size_t PropImpl::getDefaultSize()
    {
        _reResolveIfNeeded();
        return m_default.size();
    }

    PropImplPtr PropImpl::getLastSetPrefab()
    {
        _reResolveIfNeeded();
        if (m_prefab == nullptr)
        {
            return nullptr;
        }
        if (m_prefab->isSet())
        {
            return m_prefab->sharedFromThis();
        }
        return m_prefab->getLastSetPrefab();
    }

    bool PropImpl::hasPrefabValue()
    {
        _reResolveIfNeeded();
        return getLastSetPrefab() != nullptr;
    }

    double PropImpl::getPrefabFloat()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::number);
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getFloat();
        }
        return getDefaultFloat();
    }
    int64_t PropImpl::getPrefabInt()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::integer);
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getInt();
        }
        return getDefaultInt();
    }
    char const* PropImpl::getPrefabString()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::string);
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getString();
        }
        return getDefaultString();
    }
    bool PropImpl::getPrefabBool()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::boolean);
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getBool();
        }
        return getDefaultBool();
    }
    EntityRef PropImpl::getPrefabEntityRef()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::entityRef);
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getEntityRef();
        }
        return getDefaultEntityRef();
    }
    std::optional<int64_t> PropImpl::getPrefabSize()
    {
        _reResolveIfNeeded();
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->m_instance.size();
        }
        return std::nullopt;
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

    void PropImpl::unset()
    {
        _reResolveIfNeeded();
        if (not isSet())
        {
            return;
        }
        _checkInvariants();
        std::vector<PropImpl*> allLayers;
        if (m_parent != nullptr)
        {
            auto const* const parentSchema = m_parent->getSchema();
            switch (parentSchema->getDataKind())
            {
            case DataKind::object: m_parent->m_instance.unsetObjectField(m_instance); break;
            case DataKind::union_: m_parent->m_instance.unsetUnionData(); break;
            case DataKind::map:
            {
                // Check if the item is present in in the parent's prefab
                bool isPresentInPrefab = false;
                if (m_parent->getPrefab() != nullptr)
                {
                    if (m_parent->getPrefab()->getMapKeyType() == DataType::string)
                    {
                        isPresentInPrefab = m_parent->getPrefab()->mapContains(
                            std::get<std::string>(m_instance.getPathToken()).c_str());
                    }
                    else
                    {
                        isPresentInPrefab = m_parent->getPrefab()->mapContains(
                            std::get<int64_t>(m_instance.getPathToken()));
                    }
                }
                if (isPresentInPrefab)
                {
                    // If it is present in the parent's prefab, we can erase the json node in the instance
                    m_parent->m_instance.unsetMapItem(m_instance);
                }
                else
                {
                    // If not, we have to keep it to ensure to ADD.
                    // It is not possible to ADD and to be unset...
                    m_instance.setToDefault(parentSchema);
                }
                break;
            }
            case DataKind::objectSet:
            {
                bool isPresentInPrefab = false;
                if (m_parent->getPrefab() != nullptr)
                {
                    if (m_parent->getPrefab()->getObjectSetKeyType() == DataType::string)
                    {
                        isPresentInPrefab = m_parent->getPrefab()->objectSetContains(
                            std::get<std::string>(m_instance.getPathToken()).c_str());
                    }
                    else
                    {
                        isPresentInPrefab = m_parent->getPrefab()->objectSetContains(
                            std::get<int64_t>(m_instance.getPathToken()));
                    }
                }
                if (isPresentInPrefab)
                {
                    m_parent->m_instance.unsetObjectSetItem(m_instance);
                }
                else
                {
                    m_instance.setToDefault(parentSchema);
                }
                break;
            }
            case DataKind::unionSet:
            {
                bool isPresentInPrefab = false;
                if (m_parent->getPrefab() != nullptr)
                {
                    isPresentInPrefab = m_parent->getPrefab()->unionSetContains(
                        std::get<std::string>(m_instance.getPathToken()).c_str());
                }
                if (isPresentInPrefab)
                {
                    m_parent->m_instance.unsetUnionSetItem(m_instance);
                }
                else
                {
                    m_instance.setToDefault(parentSchema);
                }
                break;
            }
            case DataKind::primitiveSet:
                ENTLIB_LOGIC_ERROR("Unexpected unset on a pripitive in a set !");
            case DataKind::array: m_instance.setToNull(); break;
            case DataKind::boolean: [[fallthrough]];
            case DataKind::integer: [[fallthrough]];
            case DataKind::number: [[fallthrough]];
            case DataKind::string: [[fallthrough]];
            case DataKind::entityRef: [[fallthrough]];
            case DataKind::COUNT: [[fallthrough]];
            default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
            }
        }
        else
        {
            m_instance.setToDefault(getSchema());
        }
        _checkInvariants();
    }

    std::vector<char const*> PropImpl::getFieldNames()
    {
        _reResolveIfNeeded();
        CHECK_TYPE(DataKind::object);
        std::vector<char const*> fields;
        for (auto&& [field, schema] : getSchema()->properties)
        {
            fields.push_back(field.c_str());
        }
        return fields;
    }

    PropImplPtr PropImpl::resolveNodeRef(char const* _nodeRef)
    {
        _reResolveIfNeeded();
        if (_nodeRef == nullptr)
        {
            throw NullPointerArgument("resolveNodeRef", "nodeRef");
        }
        auto const* tokenStart = _nodeRef;
        auto const* const nodeRefEnd = _nodeRef + strlen(_nodeRef);

        auto const* tokenStop = strchr(tokenStart, '/');
        if (tokenStop == nullptr)
        {
            tokenStop = nodeRefEnd;
        }
        auto current = sharedFromThis();

        auto nextToken = [&tokenStart, &tokenStop, nodeRefEnd]
        {
            if (tokenStop == nodeRefEnd)
            {
                tokenStart = nodeRefEnd;
            }
            else
            {
                tokenStart = tokenStop + 1;
                tokenStop = strchr(tokenStart, '/');
                if (tokenStop == nullptr)
                {
                    tokenStop = nodeRefEnd;
                }
            }
        };

        // For each token in _nodeRef
        std::string token;
        for (; tokenStart != nodeRefEnd; nextToken())
        {
            // Get the child, using the token and the DataType
            token.assign(tokenStart, tokenStop - tokenStart);
            if (token == ".")
            {
                continue;
            }
            ENTLIB_ASSERT(not token.empty());
            switch (auto kind = current->getDataKind(); kind)
            {
            case DataKind::object:
            {
                current = current->getObjectField(token.c_str());
                break;
            }
            case DataKind::union_:
            {
                if (token != current->getUnionType())
                {
                    throw WrongPath("Wrong union type. Path doesn't exist.");
                }
                current = current->getUnionData();
                break;
            }
            case DataKind::unionSet:
            {
                current = current->getUnionSetItem(token.c_str());
                break;
            }
            case DataKind::objectSet:
            {
                current = current->getObjectSetItem(token.c_str());
                break;
            }
            case DataKind::map:
            {
                if (current->getMapKeyType() == DataType::integer)
                {
                    // current is any other map/set kind, with an integer key
                    auto const key = atoi(token.c_str());
                    current = current->getMapItem(key);
                }
                else
                {
                    // current is any other map/set kind, with a string, or EntityRef key
                    current = current->getMapItem(token.c_str());
                }
                break;
            }
            case DataKind::array:
            {
                // current is an array
                auto const index = atoi(token.c_str());
                current = current->getArrayItem(index);
                break;
            }
            case DataKind::primitiveSet: [[fallthrough]];
            case DataKind::boolean: [[fallthrough]];
            case DataKind::entityRef: [[fallthrough]];
            case DataKind::integer: [[fallthrough]];
            case DataKind::number: [[fallthrough]];
            case DataKind::string: [[fallthrough]];
            case DataKind::COUNT:
            default:
                ENTLIB_LOGIC_ERROR("Unexpected DataKind in PropImpl::resolveNodeRef : %d", kind);
            }
            if (current == nullptr)
            {
                return current;
            }
        }
        return current;
    }

    PropImplPtr PropImpl::getRootNode() const
    {
        auto rootParent = this;
        while (rootParent->m_parent != nullptr)
        {
            rootParent = rootParent->m_parent.get();
        }
        return rootParent->sharedFromThis();
    }

    static [[nodiscard]] std::string keyToString(FileProperty::Key _key)
    {
        return std::visit(
            [](auto const& _key)
            {
                using KeyType = std::remove_const_t<std::remove_reference_t<decltype(_key)>>;
                if constexpr (std::is_same_v<KeyType, std::string>)
                {
                    return _key;
                }
                else if constexpr (std::is_same_v<KeyType, int64_t>)
                {
                    char buff[64];
                    _ltoa_s(static_cast<long>(_key), buff, 10);
                    return std::string(buff);
                }
                else
                {
                    static_assert(false, "Unknown type in FileProperty::Key");
                }
            },
            _key);
    }

    // Get the path from _root to _child, but reversed.
    static [[nodiscard]] std::vector<std::string>
    makeNodeRefReversed(PropImpl const* _root, PropImpl const& _child)
    {
        PropImplPtr propPtr = _child.sharedFromThis();
        std::vector<std::string> tokens;
        while (propPtr.get() != _root and propPtr->getParent() != nullptr)
        {
            tokens.push_back(keyToString(propPtr->getPathToken()));
            propPtr = propPtr->getParent();
        }
        return tokens;
    }

    NodeRef PropImpl::makeNodeRef(PropImpl const& _target) const
    {
        auto const thisRoot = getRootNode();
        auto const targetRoot = _target.getRootNode();
        if (thisRoot != targetRoot)
        {
            throw UnrelatedNodes();
        }
        // get the two absolute path
        auto thisPath = makeNodeRefReversed(thisRoot.get(), *this);
        auto targetPath = makeNodeRefReversed(targetRoot.get(), _target);

        // Get path from this to target
        std::string relativePath =
            computeRelativePath(std::move(thisPath), std::move(targetPath), false);

        return relativePath;
    }

    NodeRef PropImpl::makeAbsoluteNodeRef() const
    {
        return getRootNode()->makeNodeRef(*this);
    }

    bool PropImpl::sameValue(PropImpl& _other)
    {
        _reResolveIfNeeded();
        switch (getSchema()->getDataKind())
        {
        case DataKind::boolean: return getBool() == _other.getBool();
        case DataKind::integer: return getInt() == _other.getInt();
        case DataKind::number: return getFloat() == _other.getFloat();
        case DataKind::string: return strcmp(getString(), _other.getString()) == 0;
        case DataKind::entityRef: return getEntityRef() == _other.getEntityRef();
        case DataKind::object: [[fallthrough]];
        case DataKind::union_: [[fallthrough]];
        case DataKind::map: [[fallthrough]];
        case DataKind::objectSet: [[fallthrough]];
        case DataKind::unionSet: [[fallthrough]];
        case DataKind::primitiveSet: [[fallthrough]];
        case DataKind::array: throw BadType("Called 'sameValue' on a none primitive type");
        case DataKind::COUNT: [[fallthrough]];
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
    }

    void PropImpl::_reResolveFromRoot()
    {
        if (m_parent != nullptr)
        {
            m_parent->_reResolveFromRoot();
            auto key = m_parent->makeNodeRef(*this);
            auto newThis = m_parent->resolveNodeRef(key.c_str());
            if (newThis == nullptr)
            {
                auto prevRefCount = m_refCount;
                *this = PropImpl(m_entityLib);
                m_refCount = prevRefCount; // Reapply the previous m_refCount (lost in move)
                return;
            }
            auto prevRefCount = m_refCount;
            auto prevNewRefCount = newThis->m_refCount;
            *this = std::move(*newThis);
            m_refCount = prevRefCount; // Reapply the previous m_refCount (lost in move)
            newThis->m_refCount = prevNewRefCount;
        }
    }

    bool PropImpl::_doNeedReResolve() const
    {
        return m_instance.needRebuild();
    }

    bool PropImpl::_reResolveIfNeeded()
    {
        if (not m_entityLib->getRebuildPropertyEnabled())
        {
            return false;
        }
        if (not m_instance.needRebuildGlobal())
        { // If nothing has changed since last access, no need to check prefabs
            return false;
        }
        bool prefabChanged = false;
        if (m_prefab)
        {
            prefabChanged = m_prefab->_reResolveIfNeeded();
        }
        if (prefabChanged or _doNeedReResolve())
        {
            _reResolveFromRoot();
            return true;
        }
        return false;
    }

    void PropImpl::_updateParentToResolved()
    {
        m_instance.updateToResolved();
        if (auto parent = getParent())
        {
            parent->_updateParentToResolved();
        }
    }

} // namespace Ent
