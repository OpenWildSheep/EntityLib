#include "include/EntityLib/Cursor.h"

namespace Ent
{
    void Cursor::Layer::setDefault(
        Ent::Subschema const* _schema, char const* _filePath, nlohmann::json const* _document)
    {
        // Loïc : To fix this aweful const_cast, FileCursor need a const version 'ConstFileCursor'.
        // This is a "not-so-easy" task just to remove a const_cast so it is not a priority I guess.
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        defaultStorage = FileCursor{_schema, _filePath, const_cast<nlohmann::json*>(_document)};
    }
    void Cursor::Layer::clear()
    {
        prefab = nullptr;
        defaultStorage.reset();
        arraySize = 0;
    }
    FileCursor* Cursor::Layer::getDefault()
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<FileCursor*>(std::as_const(*this).getDefault());
    }
    FileCursor const* Cursor::Layer::getDefault() const
    {
        if (not defaultStorage.has_value())
        {
            return nullptr;
        }
        else
        {
            return &(*defaultStorage);
        }
    }

    bool Cursor::isSet() const
    {
        return _getLastLayer().instance.isSet();
    }

    template <typename V>
    V Cursor::get() const
    {
        auto& lastLayer = _getLastLayer();
        if (isSet())
        {
            return lastLayer.instance.get<V>();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->get<V>();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
                 defaultVal != nullptr and defaultVal->isSet())
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

    double Cursor::getFloat() const
    {
        return get<double>();
    }
    int64_t Cursor::getInt() const
    {
        return get<int64_t>();
    }
    char const* Cursor::getString() const
    {
        return get<char const*>();
    }
    bool Cursor::getBool() const
    {
        return get<bool>();
    }
    EntityRef Cursor::getEntityRef() const
    {
        return get<EntityRef>();
    }

    Cursor::Layer& Cursor::_allocLayer()
    {
        if (m_layers.size() < m_layerCount + 1)
        {
            return m_layers.emplace_back();
        }
        Layer& newLayer = m_layers[m_layerCount];
        newLayer.clear();
        return newLayer;
    }

    void Cursor::_comitNewLayer()
    {
        ++m_layerCount;
        if (_getLastLayer().instance.getSchema()->type == Ent::DataType::array)
        {
            _getLastLayer().arraySize = arraySize();
        }
        _checkInvariants();
    }

    Cursor::Layer& Cursor::_getLastLayer()
    {
        return m_layers[m_layerCount - 1];
    }

    Cursor::Layer const& Cursor::_getLastLayer() const
    {
        return m_layers[m_layerCount - 1];
    }

    Cursor::Cursor() = default;

    Cursor::Cursor(
        EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename, nlohmann::json* _doc)
    {
        _init(_entityLib, _schema, _filename, _doc);
    }
    void Cursor::_init(
        EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename, nlohmann::json* _doc)
    {
        m_entityLib = _entityLib;

        ENTLIB_ASSERT(_schema != nullptr);
        m_layerCount = 0;
        Layer& newLayer = _allocLayer();
        newLayer.setDefault(_schema, nullptr, &_schema->defaultValue);
        newLayer.instance.init(_schema, _filename, _doc);
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        _loadInstanceOf(newLayer);
        _comitNewLayer();
    }

    void Cursor::_init(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(_entityLib, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    Cursor::Cursor(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(_entityLib, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    void Cursor::save(char const* _filename) const
    {
        _getLastLayer().instance.save(_filename);
    }

    bool Cursor::isDefault() const
    {
        auto& newLayer = _getLastLayer();
        if (newLayer.instance.isSet())
        {
            return false;
        }
        if (newLayer.prefab != nullptr)
        {
            return newLayer.prefab->isDefault();
        }
        return true;
    }

    bool Cursor::_loadInstanceOf(Layer& _newLayer)
    {
        auto* subschema = _newLayer.instance.getSchema();
        if ((subschema->type == DataType::object or subschema->type == DataType::oneOf)
             and _newLayer.instance.isSet())
        {
            auto* doc = _newLayer.instance.getRawJson();
            if (auto member = doc->find("InstanceOf"); member != doc->end())
            {
                if (auto const& prefabPath = member->get_ref<std::string const&>();
                    not prefabPath.empty())
                {
                    if (_newLayer.prefabsStorage == nullptr)
                    {
                        _newLayer.prefabsStorage =
                            std::make_unique<Cursor>(m_entityLib, subschema, prefabPath.c_str());
                    }
                    else
                    {
                        _newLayer.prefabsStorage->_init(m_entityLib, subschema, prefabPath.c_str());
                    }
                    _newLayer.prefab = _newLayer.prefabsStorage.get();
                }
                return true;
            }
        }
        return false;
    }

    Cursor& Cursor::enterObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _checkInvariants();
        ENTLIB_DBG_ASSERT(getDataType() == Ent::DataType::object);
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == Ent::DataType::object);
        newLayer.instance = lastLayer.instance.enterObjectField(_field, _fieldRef);
        auto* subschema = newLayer.instance.getSchema();
        if (not _loadInstanceOf(newLayer))
        {
            if (lastLayer.prefab != nullptr)
            {
                ENTLIB_ASSERT(lastLayer.prefab->m_entityLib != nullptr);
                lastLayer.prefab->enterObjectField(_field, _fieldRef);
                newLayer.prefab = lastLayer.prefab;
            }
        }
        bool defaultFound = false;
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            auto const objectField = defaultVal->enterObjectField(_field, _fieldRef);
            if (objectField.isSet())
            {
                defaultFound = true;
                newLayer.defaultStorage = std::move(objectField);
            }
        }
        if (not defaultFound)
        {
            auto propDefVal = newLayer.instance.getPropertyDefaultValue();
            if (propDefVal != nullptr) // If there is property default, use them
            {
                newLayer.setDefault(subschema, nullptr, propDefVal);
            }
            else if (not subschema->defaultValue.is_null())
            {
                newLayer.setDefault(subschema, nullptr, &subschema->defaultValue);
            }
        }
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterUnionData(char const* _type)
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        if (_type == nullptr)
        {
            _type = getUnionType();
        }
        return _enterItem(
            [_type](FileCursor& _cur)
            {
                return _cur.enterUnionData(_type);
            },
            [_type](Cursor& _cur) { _cur.enterUnionData(_type); });
    }

    Cursor& Cursor::enterUnionSetItem(char const* _type, Subschema const* _dataSchema)
    {
        if (_dataSchema == nullptr)
        {
            auto& singularItems = _getLastLayer().instance.getSchema()->singularItems;
            if (singularItems != nullptr)
            {
                Ent::Subschema const& unionSchema = singularItems->get();
                if (unionSchema.type != Ent::DataType::oneOf)
                {
                    throw Ent::BadType("Cursor::enterUnionSetItem : Not an UnionSet");
                }
                auto& unionTypeMap = unionSchema.unionTypeMap;
                if (auto iter = unionTypeMap.find(_type); iter != unionTypeMap.end())
                {
                    _dataSchema = iter->second.dataSchema;
                }
                else
                {
                    throw Ent::BadKey(
                        _type,
                        "Cursor::enterUnionSetItem",
                        _getLastLayer().instance.getSchema()->name.c_str());
                }
            }
            else
            {
                throw Ent::BadType("Cursor::enterUnionSetItem : Not an UnionSet");
            }
        }
        return _enterItem([_type, _dataSchema](auto&& _cur) { return _cur.enterUnionSetItem(_type, _dataSchema); },
            [_type, _dataSchema](auto&& _cur) { _cur.enterUnionSetItem(_type, _dataSchema); });
    }

    template <typename FC, typename C>
    Cursor& Cursor::_enterItem(FC&& _enterFileCursor, C&& _enterCursor)
    {
        _checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        newLayer.instance = _enterFileCursor(lastLayer.instance);
        auto* subschema = newLayer.instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.defaultStorage = _enterFileCursor(*defaultVal);
        }
        else if (auto* propDefVal = newLayer.instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, propDefVal);
        }
        else // Use type default
        {
            newLayer.setDefault(subschema, nullptr, &subschema->defaultValue);
        }
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    _enterCursor(*lastLayer.prefab);
                    newLayer.prefab = lastLayer.prefab;
                }
            }
        }
        ENTLIB_DBG_ASSERT(
            newLayer.getDefault() == nullptr
            or newLayer.getDefault()->getSchema()->type == newLayer.instance.getSchema()->type);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterObjectSetItem(char const* _key)
    {
        return _enterItem(
            [_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); },
            [_key](auto&& _cur) { _cur.enterObjectSetItem(_key); });
    }

    Cursor& Cursor::enterObjectSetItem(int64_t _key)
    {
        return _enterItem(
            [_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); },
            [_key](auto&& _cur) { _cur.enterObjectSetItem(_key); });
    }

    Cursor& Cursor::enterMapItem(char const* _key)
    {
        return _enterItem(
            [_key](auto&& _cur) { return _cur.enterMapItem(_key); },
            [_key](auto&& _cur) { _cur.enterMapItem(_key); });
    }

    Cursor& Cursor::enterMapItem(int64_t _field)
    {
        return _enterItem(
            [_field](auto&& _cur) { return _cur.enterMapItem(_field); },
            [_field](auto&& _cur) { _cur.enterMapItem(_field); });
    }

    Cursor& Cursor::enterArrayItem(size_t _index)
    {
        _checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(lastLayer.instance.getSchema()->type == Ent::DataType::array);
        newLayer.instance = lastLayer.instance.enterArrayItem(_index);
        auto* subschema = newLayer.instance.getSchema();
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterArrayItem(_index);
                    newLayer.prefab = lastLayer.prefab;
                }
            }
        }
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.defaultStorage = defaultVal->enterArrayItem(_index);
        }
        else if (newLayer.instance.getPropertyDefaultValue() != nullptr) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, newLayer.instance.getPropertyDefaultValue());
        }
        else // Use type default
        {
            newLayer.setDefault(subschema, nullptr, &subschema->defaultValue);
        }
        _comitNewLayer();
        return *this;
    }

    char const* Cursor::getInstanceOf()
    {
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Ent::Subschema schema;
        schema.type = Ent::DataType::string;
        Ent::SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        enterObjectField("InstanceOf", &ref);
        if (not isSet())
        {
            exit();
            return nullptr;
        }
        char const* instanceOf = getString();
        exit();
        return instanceOf;
    }

    void Cursor::setInstanceOf(char const* _instanceOf)
    {
        if (_instanceOf == nullptr)
        {
            throw Ent::NullPointerArgument("_instanceOf", __func__);
        }
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Ent::Subschema schema;
        schema.type = Ent::DataType::string;
        Ent::SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        enterObjectField("InstanceOf", &ref);
        setString(_instanceOf);
        exit();
        auto& lastLayer = _getLastLayer();
        if (lastLayer.prefab != nullptr)
        {
            lastLayer.prefab->exit();
        }
        if (strlen(_instanceOf) != 0)
        {
            if (lastLayer.prefabsStorage == nullptr)
            {
                lastLayer.prefabsStorage =
                    std::make_unique<Cursor>(m_entityLib, getSchema(), _instanceOf);
            }
            else
            {
                lastLayer.prefabsStorage->_init(m_entityLib, getSchema(), _instanceOf);
            }
            lastLayer.prefab = lastLayer.prefabsStorage.get();
        }
        else
        {
            lastLayer.prefab = nullptr;
        }
    }

    char const* Cursor::getUnionType()
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        auto& lastLayer = _getLastLayer();
        if (char const* type = lastLayer.instance.getUnionType())
        {
            return type;
        }
        else if (lastLayer.prefab != nullptr)
        {
            if (char const* type2 = lastLayer.prefab->getUnionType())
            {
                return type2;
            }
        }
        else if (auto* defaultVal = lastLayer.getDefault())
        {
            if (char const* type3 = defaultVal->getUnionType())
            {
                return type3;
            }
        }
        return getSchema()->getUnionDefaultTypeName();
    }

    size_t Cursor::getUnionTypeIndex()
    {
        auto type = getUnionType();
        return AT(getSchema()->unionTypeMap, type).index;
    }

    void Cursor::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_layerCount != 0);
        ENTLIB_DBG_ASSERT(_getLastLayer().instance.schema.base != nullptr);
        [[maybe_unused]] auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == lastLayer.instance.getSchema()->type);
        if (lastLayer.prefab != nullptr)
        {
            lastLayer.prefab->_checkInvariants();
        }
#endif
    }

    Cursor& Cursor::exit()
    {
#ifdef _DEBUG
        auto layersCount = m_layerCount;
        ENTLIB_DBG_ASSERT(m_layerCount > 0);
        auto& prevLayer = m_layers[m_layerCount - 2];
        auto& prevSchema = m_layers[m_layerCount - 2].instance.schema;
        ENTLIB_DBG_ASSERT((_getLastLayer().instance).schema.base != nullptr);
        ENTLIB_DBG_ASSERT(prevSchema.base != nullptr);
#endif
        _checkInvariants();
        auto& lastLayer = _getLastLayer();
        if (lastLayer.prefab != nullptr and not(lastLayer.prefab->m_layerCount < 2))
        {
            lastLayer.prefab->exit();
        }
        --m_layerCount;
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(layersCount == m_layerCount + 1);
        ENTLIB_DBG_ASSERT(
            prevLayer.getDefault() == nullptr
            or prevLayer.getDefault()->getSchema()->type == prevSchema.base->type);
#endif
        _checkInvariants();
        return *this;
    }

    DataType Cursor::getDataType() const
    {
        return _getLastLayer().instance.getSchema()->type;
    }

    Subschema const* Cursor::getSchema() const
    {
        return _getLastLayer().instance.getSchema();
    }

    char const* Cursor::getTypeName() const
    {
        return getSchema()->name.c_str();
    }

    DataType Cursor::getMapKeyType() const
    {
        return _getLastLayer().instance.getSchema()->singularItems->get().linearItems->at(0)->type;
    }

    DataType Cursor::getObjectSetKeyType() const
    {
        auto& schema = *_getLastLayer().instance.getSchema();
        if (auto arrayMeta = std::get_if<Subschema::ArrayMeta>(&schema.meta))
        {
            if (arrayMeta->keyField.has_value())
            {
                return schema.singularItems->get().properties.at(*arrayMeta->keyField)->type;
            }
        }
        throw Ent::BadType(Ent::staticFormat(
            "In Cursor::getObjectSetKeyType : Expected ObjectSet. Got %s", schema.name.c_str()));
    }

    size_t Cursor::arraySize()
    {
        auto& lastLayer = _getLastLayer();
        auto& jsonExplLayer = lastLayer.instance;
        auto* schema = jsonExplLayer.schema.base;
        if (schema->linearItems.has_value())
        {
            return schema->linearItems->size();
        }
        else
        {
            if (isSet())
            {
                return jsonExplLayer.values->size();
            }
            else if (lastLayer.prefab != nullptr)
            {
                return lastLayer.prefab->arraySize();
            }
            else if (auto* defaultVal = lastLayer.getDefault();
                     defaultVal != nullptr and defaultVal->isSet())
            {
                return defaultVal->getRawJson()->size();
            }
            else
            {
                return schema->minItems;
            }
        }
    }

    size_t Cursor::size()
    {
        auto& jsonExplLayer = _getLastLayer().instance;
        auto* schema = jsonExplLayer.schema.base;
        if (schema->linearItems.has_value())
        {
            return schema->linearItems->size();
        }
        switch (schema->type)
        {
        case Ent::DataType::object: return schema->properties.size();
        case Ent::DataType::oneOf: return 1;
        case Ent::DataType::array:
        {
            auto meta = std::get<Ent::Subschema::ArrayMeta>(schema->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                switch (getMapKeyType())
                {
                case Ent::DataType::string: return getMapKeysString().size();
                case Ent::DataType::integer: return getMapKeysInt().size();
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            case "set"_hash:
            {
                auto& itemType = schema->singularItems->get();
                switch (itemType.type)
                {
                case Ent::DataType::integer: return getPrimSetKeysInt().size();
                case Ent::DataType::string: return getPrimSetKeysString().size();
                case Ent::DataType::oneOf: return getUnionSetKeysString().size();
                case Ent::DataType::object:
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case Ent::DataType::string: return getObjectSetKeysString().size();
                    case Ent::DataType::integer: return getObjectSetKeysInt().size();
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
        case Ent::DataType::null: return 0;
        case Ent::DataType::boolean: return 0;
        case Ent::DataType::integer: return 0;
        case Ent::DataType::number: return 0;
        case Ent::DataType::string: return 0;
        case Ent::DataType::entityRef: return 0;
        case Ent::DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
        ENTLIB_LOGIC_ERROR("Unexpected DataType!");
    }

    bool Cursor::contains(Key const& _key)
    {
        auto& jsonExplLayer = _getLastLayer().instance;
        auto* schema = jsonExplLayer.schema.base;
        if (schema->linearItems.has_value())
        {
            return false; // Not a map/set
        }
        switch (schema->type)
        {
        case Ent::DataType::object:
            return schema->properties.count(std::get<std::string>(_key)) != 0;
        case Ent::DataType::oneOf: return getUnionType() == std::get<std::string>(_key);
        case Ent::DataType::array:
        {
            auto meta = std::get<Ent::Subschema::ArrayMeta>(schema->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                switch (getMapKeyType())
                {
                case Ent::DataType::string: return mapContains(std::get<std::string>(_key).c_str());
                case Ent::DataType::integer: return mapContains(std::get<size_t>(_key));
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            case "set"_hash:
            {
                auto& itemType = schema->singularItems->get();
                switch (itemType.type)
                {
                case Ent::DataType::integer: return primSetContains(std::get<size_t>(_key));
                case Ent::DataType::string:
                    return primSetContains(std::get<std::string>(_key).c_str());
                case Ent::DataType::oneOf:
                    return unionSetContains(std::get<std::string>(_key).c_str());
                case Ent::DataType::object:
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case Ent::DataType::string:
                        return objectSetContains(std::get<std::string>(_key).c_str());
                    case Ent::DataType::integer: return objectSetContains(std::get<size_t>(_key));
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
        case Ent::DataType::null: return false;
        case Ent::DataType::boolean: return false;
        case Ent::DataType::integer: return false;
        case Ent::DataType::number: return false;
        case Ent::DataType::string: return false;
        case Ent::DataType::entityRef: return false;
        case Ent::DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
        ENTLIB_LOGIC_ERROR("Unexpected DataType!");
    }

    bool Cursor::empty()
    {
        return size() == 0;
    }

    std::set<char const*, CmpStr> Cursor::getMapKeysString()
    {
        auto& lastLayer = _getLastLayer();
        std::set<char const*, CmpStr> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getMapKeysString();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
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
        if (lastLayer.instance.isSet())
        {
            auto* node = lastLayer.instance.getRawJson();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (size_t i = 0; i < node->size(); ++i)
            {
                ENTLIB_DBG_ASSERT(node->is_array());
                auto key = enterArrayItem(i).enterArrayItem(0llu).getString();
                exit();
                ENTLIB_DBG_ASSERT(node->is_array());
                if (enterArrayItem(1llu).isNull())
                {
                    keys.erase(key);
                }
                else
                {
                    keys.insert(key);
                }
                exit().exit();
                ENTLIB_DBG_ASSERT(node->is_array());
            }
        }
        return keys;
    }

    bool Cursor::isNull() const
    {
        auto& lastLayer = _getLastLayer();
        if (lastLayer.instance.isSetOrNull())
        {
            return lastLayer.instance.isNull();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->isNull();
        }
        else
        {
            return false;
        }
    }
    std::set<int64_t> Cursor::getMapKeysInt()
    {
        auto& lastLayer = _getLastLayer();
        std::set<int64_t> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getMapKeysInt();
        }
        if (lastLayer.instance.isSet())
        {
            auto const arraySize = lastLayer.instance.getRawJson()->size();
            for (size_t i = 0; i < arraySize; ++i)
            {
                auto key = enterArrayItem(i).enterArrayItem(0llu).getInt();
                if (exit().enterArrayItem(1llu).isNull())
                {
                    keys.erase(key);
                }
                else
                {
                    keys.insert(key);
                }
                exit().exit();
            }
        }
        return keys;
    }
    std::set<int64_t> Cursor::getPrimSetKeysInt()
    {
        auto& lastLayer = _getLastLayer();
        std::set<int64_t> keys;
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(enterArrayItem(i).getInt());
                exit();
            }
        }
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getPrimSetKeysInt());
        }
        return keys;
    }
    std::set<char const*, CmpStr> Cursor::getPrimSetKeysString()
    {
        std::set<char const*, CmpStr> keys;
        if (_getLastLayer().instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(enterArrayItem(i).getString());
                exit();
            }
        }
        auto& lastLayer = _getLastLayer();
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getPrimSetKeysString());
        }
        return keys;
    }

    std::map<char const*, Subschema const*, CmpStr> Cursor::getUnionSetKeysString()
    {
        auto& lastLayer = _getLastLayer();
        std::map<char const*, Subschema const*, CmpStr> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getUnionSetKeysString();
        }
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto arrayItem = lastLayer.instance.enterArrayItem(i);
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

    std::set<char const*, CmpStr> Cursor::getObjectSetKeysString()
    {
        auto& lastLayer = _getLastLayer();
        auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
        std::set<char const*, CmpStr> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getObjectSetKeysString();
        }
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                enterArrayItem(i);
                if (_getLastLayer().instance.isSet() and _getLastLayer().instance.getRawJson()->count("__removed__") != 0)
                {
                    keys.erase(enterObjectField(meta.keyField->c_str()).getString());
                    exit();
                }
                else
                {
                    keys.insert(enterObjectField(meta.keyField->c_str()).getString());
                    exit();
                }
                exit();
            }
        }
        return keys;
    }

    std::set<int64_t> Cursor::getObjectSetKeysInt()
    {
        auto& lastLayer = _getLastLayer();
        auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
        std::set<int64_t> keys;
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                enterArrayItem(i);
                if (_getLastLayer().instance.isSet() and _getLastLayer().instance.getRawJson()->count("__removed__") != 0)
                {
                    keys.erase(enterObjectField(meta.keyField->c_str()).getInt());
                    exit();
                }
                else
                {
                    keys.insert(enterObjectField(meta.keyField->c_str()).getInt());
                    exit();
                }
                exit();
            }
        }
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getObjectSetKeysInt());
        }
        return keys;
    }

    bool Cursor::mapContains(char const* _key)
    {
        return getMapKeysString().count(_key) != 0;
    }
    bool Cursor::mapContains(int64_t _key)
    {
        return getMapKeysInt().count(_key) != 0;
    }
    bool Cursor::primSetContains(char const* _key)
    {
        return _countPrimSetKeyImpl(
            _key, [this](char const* _key) { return strcmp(getString(), _key) == 0; });
    }
    bool Cursor::primSetContains(int64_t _key)
    {
        return _countPrimSetKeyImpl(_key, [this](int64_t _key) { return getInt() == _key; });
    }
    bool Cursor::unionSetContains(char const* _key)
    {
        return getUnionSetKeysString().count(_key) != 0;
    }
    bool Cursor::objectSetContains(char const* _key)
    {
        return getObjectSetKeysString().count(_key) != 0;
    }
    bool Cursor::objectSetContains(int64_t _key)
    {
        return getObjectSetKeysInt().count(_key) != 0;
    }

    void Cursor::_buildPath()
    {
        _checkInvariants();
        auto firstNotSet = std::find_if(
            &m_layers.front(),
            &_getLastLayer() + 1,
            [](Layer const& l) { return l.instance.values == nullptr; });
        ENTLIB_ASSERT(firstNotSet != &m_layers.front());
        auto firstNotSetIdx = std::distance(&m_layers.front(), firstNotSet);
        auto lastSet = firstNotSet;
        --lastSet;
        auto endIter = &_getLastLayer() + 1;
        for (; firstNotSet != endIter; ++lastSet, ++firstNotSet, ++firstNotSetIdx)
        {
            size_t arraySize = m_layers[firstNotSetIdx - 1].arraySize;
            firstNotSet->instance.values = FileCursor::createChildNode(
                lastSet->instance,
                firstNotSet->instance.additionalPath,
                *firstNotSet->instance.schema.base,
                arraySize);
            ENTLIB_ASSERT(firstNotSet->instance.values != nullptr);
        }
        ENTLIB_ASSERT(_getLastLayer().instance.values != nullptr);
        _checkInvariants();
    }
    void Cursor::setSize(size_t _size)
    {
        _buildPath();
        _getLastLayer().instance.setSize(_size);
    }

    void Cursor::setFloat(double _value)
    {
        _buildPath();
        _getLastLayer().instance.setFloat(_value);
    }
    void Cursor::setInt(int64_t _value)
    {
        _buildPath();
        _getLastLayer().instance.setInt(_value);
    }
    void Cursor::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        ENTLIB_ASSERT(getSchema()->type == DataType::string or getSchema()->type == DataType::entityRef);
        _buildPath();
        _getLastLayer().instance.setString(_value);
    }
    void Cursor::setBool(bool _value)
    {
        _buildPath();
        _getLastLayer().instance.setBool(_value);
    }
    void Cursor::setEntityRef(EntityRef const& _value)
    {
        _buildPath();
        _getLastLayer().instance.setEntityRef(_value);
    }
    void Cursor::setUnionType(char const* _type)
    {
        _buildPath();
        _getLastLayer().instance.setUnionType(_type);
    }
    void Cursor::buildPath()
    {
        _buildPath();
    }

    template <typename K, typename E>
    bool Cursor::_countPrimSetKeyImpl(K _key, E&& _isEqual)
    {
        if (_getLastLayer().instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                enterArrayItem(i);
                bool const equal = _isEqual(_key);
                exit();
                if (equal)
                {
                    return true;
                }
            }
        }
        auto& lastLayer = _getLastLayer();
        if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->primSetContains(_key);
        }
        return false;
    }

    void Cursor::insertPrimSetKey(char const* _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            _getLastLayer().instance.pushBack(_key);
        }
    }
    void Cursor::insertPrimSetKey(int64_t _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            _getLastLayer().instance.pushBack(_key);
        }
    }

    nlohmann::json const* Cursor::_getRawJson()
    {
        return _getLastLayer().instance.getRawJson();
    }

} // namespace Ent
