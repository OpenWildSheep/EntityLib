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

    FileProperty const& PropImpl::getDefault() const
    {
        return m_default;
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
        if (m_prefab != nullptr)
        {
            return m_prefab->get<V>();
        }
        if (getDefault().isSet())
        {
            return getDefault().get<V>();
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
        const auto& newLayer = *this;
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
        const auto* subschema = m_instance.getSchema();
        if ((subschema->type == DataType::object or subschema->type == DataType::oneOf)
            and m_instance.isSet())
        {
            if (const auto* doc = m_instance.getRawJson())
            {
                if (auto const member = doc->find("InstanceOf"); member != doc->end())
                {
                    if (auto const& prefabPath = member->get_ref<std::string const&>();
                        not prefabPath.empty())
                    {
                        m_prefab = m_entityLib->newPropImpl(
                            nullptr, subschema, prefabPath.c_str(), nullptr);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    PropImplPtr PropImpl::getObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _checkInvariants();
        ENTLIB_DBG_ASSERT(getDataType() == DataType::object);
        auto newLayer = m_entityLib->newPropImpl();
        ENTLIB_DBG_ASSERT(getDefault().getSchema()->type == DataType::object);
        newLayer->m_instance = m_instance.getObjectField(_field, _fieldRef);
        newLayer->m_entityLib = m_entityLib;
        newLayer->m_parent = sharedFromThis();
        const auto* subschema = newLayer->getSchema();
        if (not newLayer->_loadInstanceOf())
        {
            if (not m_instance.isRemovedObject() and m_prefab != nullptr)
            {
                newLayer->m_prefab = m_prefab->getObjectField(_field, _fieldRef);
            }
        }
        bool defaultFound = false;
        const auto& defaultVal = getDefault();
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
            const auto* const propDefVal = newLayer->m_instance.getPropertyDefaultValue();
            if (propDefVal != nullptr) // If there is property default, use them
            {
                newLayer->setDefault(subschema, nullptr, propDefVal);
            }
            else if (not subschema->defaultValue.is_null())
            {
                newLayer->setDefault(subschema, nullptr, &subschema->defaultValue);
            }
            else
            {
                newLayer->setDefault(subschema, nullptr, nullptr);
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
            const auto& singularItems = m_instance.getSchema()->singularItems;
            if (singularItems != nullptr)
            {
                Subschema const& unionSchema = singularItems->get();
                if (unionSchema.type != DataType::oneOf)
                {
                    throw BadType("PropImpl::enterUnionSetItem : Not an UnionSet");
                }
                const auto& unionTypeMap = unionSchema.unionTypeMap;
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
        newLayer.m_parent = sharedFromThis();
        const auto* subschema = newLayer.getSchema();
        const auto& defaultVal = getDefault();
        if (defaultVal.isSet()) // If there is default, enter in
        {
            newLayer.m_default = _enter(defaultVal);
        }
        else if (const auto* propDefVal = newLayer.m_instance.getPropertyDefaultValue()) // If there is property default, use them
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
        if (newLayerPtr->getDefault().getSchema() == nullptr)
        {
            newLayerPtr->setDefault(subschema, nullptr, nullptr);
        }
        return newLayerPtr;
    }

    PropImplPtr PropImpl::getObjectSetItem(char const* _key)
    {
        ENTLIB_ASSERT(getDataKind() == DataKind::objectSet);
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
        newLayer.m_parent = sharedFromThis();
        const auto* subschema = newLayer.getSchema();
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
        const auto& defaultVal = getDefault();
        if (defaultVal.isSet()) // If there is default, enter in
        {
            newLayer.m_default = defaultVal.getArrayItem(_index);
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
        auto const field = getObjectField("InstanceOf", &ref);
        if (not field->isSet())
        {
            return nullptr;
        }
        char const* instanceOf = field->getString();
        return instanceOf;
    }

    void PropImpl::resetInstanceOf(char const* _instanceOf)
    {
        unset();
        changeInstanceOf(_instanceOf);
    }

    void PropImpl::changeInstanceOf(char const* _instanceOf)
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
        getObjectField("InstanceOf", &ref)
            ->setString(m_entityLib->getRelativePath(_instanceOf).generic_u8string().c_str());
        if (strlen(_instanceOf) != 0)
        {
            m_prefab = m_entityLib->newPropImpl(nullptr, getSchema(), _instanceOf, nullptr);
        }
        else
        {
            m_prefab = nullptr;
        }
    }

    PropImplPtr PropImpl::makeInstanceOf()
    {
        auto& jsonDoc = m_entityLib->createTempJsonFile();
        jsonDoc["InstanceOf"] = m_instance.getFilePath();
        auto instProp = m_entityLib->newPropImpl(nullptr, getSchema(), "", &jsonDoc);
        instProp->m_prefab = sharedFromThis();
        return instProp;
    }

    char const* PropImpl::getUnionType() const
    {
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
        else if (char const* type3 = getDefault().getUnionType())
        {
            return type3;
        }
        return getSchema()->getUnionDefaultTypeName();
    }

    size_t PropImpl::getUnionTypeIndex() const
    {
        const auto* const type = getUnionType();
        return AT(getSchema()->unionTypeMap, type).index;
    }

    void PropImpl::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_instance.getSchema() != nullptr);
        ENTLIB_DBG_ASSERT(getDefault().getSchema()->type == m_instance.getSchema()->type);
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
        return m_instance.getMapKeyType();
    }

    DataType PropImpl::getObjectSetKeyType() const
    {
        const auto& schema = *m_instance.getSchema();
        if (const auto* const arrayMeta = std::get_if<Subschema::ArrayMeta>(&schema.meta))
        {
            if (arrayMeta->keyField.has_value())
            {
                return schema.singularItems->get().properties.at(*arrayMeta->keyField)->type;
            }
        }
        throw BadType(staticFormat(
            "In PropImpl::getObjectSetKeyType : Expected ObjectSet. Got %s", schema.name.c_str()));
    }

    size_t PropImpl::arraySize() const
    {
        auto const& jsonExplLayer = m_instance;
        const auto* schema = jsonExplLayer.getSchema();
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
        if (getDefault().isSet())
        {
            return getDefault().getRawJson()->size();
        }
        return schema->minItems;
    }

    size_t PropImpl::size()
    {
        auto const& jsonExplLayer = m_instance;
        const auto* schema = jsonExplLayer.getSchema();
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
                    auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
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
        auto const& jsonExplLayer = m_instance;
        const auto* schema = jsonExplLayer.getSchema();
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
                    auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
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

    template <typename Container, typename F>
    Container PropImpl::getKeys(F const& getKeysInFile)
    {
        Container keys;
        if (m_prefab != nullptr) // If there is a prefab, get prefab's keys
        {
            keys = m_prefab->getKeys<Container, F>(getKeysInFile);
        }
        else // else, get the dfault keys
        {
            getKeysInFile(getDefault(), keys);
        }
        // Anyway, add or remove keys from instance
        getKeysInFile(m_instance, keys);
        return keys;
    }

    std::set<char const*, CmpStr> PropImpl::getMapKeysString()
    {
        return getKeys<std::set<char const*, CmpStr>>([](FileProperty const& _file, auto& _keys)
                                                      { _file.updateMapKeysString(_keys); });
    }

    bool PropImpl::isNull() const
    {
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
        return getKeys<std::set<int64_t>>([](FileProperty const& _file, auto& _keys)
                                          { _file.updateMapKeysInt(_keys); });
    }
    std::set<int64_t> PropImpl::getPrimSetKeysInt()
    {
        return getKeys<std::set<int64_t>>([](FileProperty const& _file, auto& _keys)
                                          { _file.updatePrimSetKeysInt(_keys); });
    }
    std::set<char const*, CmpStr> PropImpl::getPrimSetKeysString()
    {
        return getKeys<std::set<char const*, CmpStr>>([](FileProperty const& _file, auto& _keys)
                                                      { _file.updatePrimSetKeysString(_keys); });
    }

    std::map<char const*, Subschema const*, CmpStr> PropImpl::getUnionSetKeysString()
    {
        return getKeys<std::map<char const*, Subschema const*, CmpStr>>(
            [](FileProperty const& _file, auto& _keys) { _file.updateUnionSetKeysString(_keys); });
    }

    std::set<char const*, CmpStr> PropImpl::getObjectSetKeysString()
    {
        return getKeys<std::set<char const*, CmpStr>>([](FileProperty const& _file, auto& _keys)
                                                      { _file.updateObjectSetKeysString(_keys); });
    }

    std::set<int64_t> PropImpl::getObjectSetKeysInt()
    {
        return getKeys<std::set<int64_t>>([](FileProperty const& _file, auto& _keys)
                                          { _file.updateObjectSetKeysInt(_keys); });
    }

    std::set<char const*, CmpStr> PropImpl::getMapRemovedKeysString() const
    {
        return m_instance.getMapRemovedKeysString();
    }
    std::set<int64_t> PropImpl::getMapRemovedKeysInt() const
    {
        return m_instance.getMapRemovedKeysInt();
    }
    std::map<char const*, Subschema const*, CmpStr> PropImpl::getUnionSetRemovedKeysString() const
    {
        return m_instance.getUnionSetRemovedKeysString();
    }
    std::set<char const*, CmpStr> PropImpl::getObjectSetRemovedKeysString() const
    {
        return m_instance.getObjectSetRemovedKeysString();
    }
    std::set<int64_t> PropImpl::getObjectSetRemovedKeysInt() const
    {
        return m_instance.getObjectSetRemovedKeysInt();
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
        return _countPrimSetKeyImpl(_key);
    }
    bool PropImpl::primSetContains(int64_t _key)
    {
        return _countPrimSetKeyImpl(_key);
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
        for (auto* iter = this; iter != nullptr; iter = iter->m_parent.get())
        {
            allLayers.push_back(iter);
        }
        std::reverse(begin(allLayers), end(allLayers));
        auto firstNotSet = std::find_if(
            begin(allLayers),
            end(allLayers),
            [](PropImpl const* l) { return not l->m_instance.isSet(); });
        ENTLIB_ASSERT(firstNotSet != allLayers.begin());
        auto firstNotSetIdx = std::distance(begin(allLayers), firstNotSet);
        ENTLIB_ASSERT(firstNotSetIdx <= static_cast<ptrdiff_t>(allLayers.size()));
        auto lastSet = firstNotSet;
        --lastSet;
        auto const endIter = allLayers.end();
        for (; firstNotSet != endIter; ++lastSet, ++firstNotSet, ++firstNotSetIdx)
        {
            (*firstNotSet)->m_instance.createChildNode((*lastSet)->m_instance);
            ENTLIB_ASSERT((*firstNotSet)->m_instance.hasJsonPointer());
        }
        _checkInvariants();
    }
    void PropImpl::setSize(size_t _size)
    {
        _buildPath();
        m_instance.setSize(_size);
    }

    void PropImpl::clear()
    {
        setSize(0);
    }

    PropImplPtr PropImpl::push_back()
    {
        setSize(arraySize() + 1);
        return getArrayItem(arraySize() - 1);
    }

    void PropImpl::pop_back()
    {
        setSize(arraySize() - 1);
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
    PropImplPtr PropImpl::setUnionType(char const* _type)
    {
        if (getSchema()->unionTypeMap.count(_type) == 0)
        {
            throw BadUnionType(_type);
        }
        _buildPath();
        m_instance.setUnionType(_type);
        return getUnionData();
    }
    void PropImpl::buildPath()
    {
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

    PropImplPtr PropImpl::insertUnionSetItem(char const* _key)
    {
        auto newItem = getUnionSetItem(_key);
        newItem->buildPath();
        return newItem;
    }

    PropImplPtr PropImpl::insertMapItem(char const* _key)
    {
        auto newItem = getMapItem(_key);
        newItem->buildPath();
        return newItem;
    }

    PropImplPtr PropImpl::insertMapItem(int64_t _key)
    {
        auto newItem = getMapItem(_key);
        newItem->buildPath();
        return newItem;
    }

    PropImplPtr PropImpl::insertObjectSetItem(char const* _key)
    {
        auto newItem = getObjectSetItem(_key);
        newItem->buildPath();
        return newItem;
    }

    PropImplPtr PropImpl::insertInstanceObjectSetItem(char const* _prefabPath)
    {
        auto const prefab =
            m_entityLib->newPropImpl(nullptr, &getSchema()->singularItems->get(), _prefabPath);
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
        auto newItem = getObjectSetItem(_key);
        newItem->buildPath();
        return newItem;
    }

    bool PropImpl::erasePrimSetKey(char const* _key)
    {
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->primSetContains(_key);
        if (isInPrefab)
        {
            throw BadArrayType("Can't erase in a primitive set if the key is still in the prefab");
        }
        return m_instance.erasePrimSetKey(_key);
    }
    bool PropImpl::erasePrimSetKey(int64_t _key)
    {
        return m_instance.erasePrimSetKey(_key);
    }
    bool PropImpl::eraseObjectSetItem(char const* _key)
    {
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->objectSetContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        return m_instance.eraseObjectSetItem(_key, isInPrefab);
    }
    bool PropImpl::eraseObjectSetItem(int64_t _key)
    {
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->objectSetContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        return m_instance.eraseObjectSetItem(_key, isInPrefab);
    }
    bool PropImpl::eraseUnionSetItem(char const* _key)
    {
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->unionSetContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        return m_instance.eraseUnionSetItem(_key, isInPrefab);
    }
    bool PropImpl::eraseMapItem(char const* _key)
    {
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->mapContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        return m_instance.eraseMapItem(_key, isInPrefab);
    }
    bool PropImpl::eraseMapItem(int64_t _key)
    {
        bool const isInPrefab = (m_prefab == nullptr) ? false : m_prefab->mapContains(_key);
        if (isInPrefab)
        {
            buildPath();
        }
        return m_instance.eraseMapItem(_key, isInPrefab);
    }

    nlohmann::json const* PropImpl::getRawJson() const
    {
        return m_instance.getRawJson();
    }

    double PropImpl::getDefaultFloat() const
    {
        return m_default.getFloat();
    }
    int64_t PropImpl::getDefaultInt() const
    {
        return m_default.getInt();
    }
    char const* PropImpl::getDefaultString() const
    {
        return m_default.getString();
    }
    bool PropImpl::getDefaultBool() const
    {
        return m_default.getBool();
    }
    EntityRef PropImpl::getDefaultEntityRef() const
    {
        return m_default.getEntityRef();
    }

    size_t PropImpl::getDefaultSize() const
    {
        return m_default.size();
    }

    PropImplPtr PropImpl::getLastSetPrefab() const
    {
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

    bool PropImpl::hasPrefabValue() const
    {
        return getLastSetPrefab() != nullptr;
    }

    double PropImpl::getPrefabFloat() const
    {
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getFloat();
        }
        return getDefaultFloat();
    }
    int64_t PropImpl::getPrefabInt() const
    {
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getInt();
        }
        return getDefaultInt();
    }
    char const* PropImpl::getPrefabString() const
    {
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getString();
        }
        return getDefaultString();
    }
    bool PropImpl::getPrefabBool() const
    {
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getBool();
        }
        return getDefaultBool();
    }
    EntityRef PropImpl::getPrefabEntityRef() const
    {
        if (auto const lastSetPrefab = getLastSetPrefab())
        {
            return lastSetPrefab->getEntityRef();
        }
        return getDefaultEntityRef();
    }
    std::optional<int64_t> PropImpl::getPrefabSize() const
    {
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
        if (not isSet())
        {
            return;
        }
        _checkInvariants();
        std::vector<PropImpl*> allLayers;
        if (m_parent != nullptr)
        {
            const auto* const parentSchema = m_parent->getSchema();
            switch (parentSchema->getDataKind())
            {
            case DataKind::object: m_parent->m_instance.unsetObjectField(m_instance); break;
            case DataKind::union_:
                m_parent->m_instance.unsetUnionData();
                m_instance.setRawJson(nullptr);
                break;
            case DataKind::map: m_instance.setToDefault(parentSchema); break;
            case DataKind::objectSet: m_instance.setToDefault(parentSchema); break;
            case DataKind::unionSet: m_instance.setToDefault(parentSchema); break;
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

    std::vector<char const*> PropImpl::getFieldNames() const
    {
        std::vector<char const*> fields;
        for (auto&& [field, schema] : getSchema()->properties)
        {
            fields.push_back(field.c_str());
        }
        return fields;
    }
} // namespace Ent
