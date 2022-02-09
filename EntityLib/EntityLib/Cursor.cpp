#include "include/EntityLib/Cursor.h"

#include <utility>

namespace Ent
{
    Cursor::Layer::Layer(
        EntityLib* _entityLib, Layer* _parent, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(_entityLib, _parent, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    Cursor::Layer::Layer(
        EntityLib* _entityLib,
        Layer* _parent,
        Ent::Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc)
    {
        _init(_entityLib, _parent, _schema, _filename, _doc);
    }

    Cursor::Layer::Layer(Cursor::Layer const& _other)
        : m_entityLib(_other.m_entityLib)
        , m_arraySize(_other.m_arraySize)
        , m_parent(_other.m_parent)
        , instance(_other.instance)
    {
        if (_other.prefab != nullptr)
        {
            prefab = std::make_unique<Layer>(*_other.prefab);
        }        
    }
    
    Cursor::Layer& Cursor::Layer::operator = (Cursor::Layer const& _other)
    {
        Layer copy(_other);
        std::swap(copy, *this);
        return *this;
    }

    void Cursor::Layer::_init(
        EntityLib* _entityLib, Layer* _parent, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(_entityLib, _parent, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    void Cursor::Layer::_init(
        EntityLib* _entityLib, Layer* _parent, Ent::Subschema const* _schema, char const* _filename, nlohmann::json* _doc)
    {
        ENTLIB_ASSERT(_schema != nullptr);
        m_entityLib = _entityLib;
        m_parent = _parent;

        setDefault(_schema, nullptr, &_schema->defaultValue);
        instance.init(_schema, _filename, _doc);
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        _loadInstanceOf();
    }

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
        m_arraySize = 0;
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

    bool Cursor::Layer::isSet() const
    {
        return instance.isSet();
    }

    template <typename V>
    V Cursor::Layer::get() const
    {
        auto& lastLayer = *this;
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

    double Cursor::Layer::getFloat() const
    {
        return get<double>();
    }

    int64_t Cursor::Layer::getInt() const
    {
        return get<int64_t>();
    }
    char const* Cursor::Layer::getString() const
    {
        return get<char const*>();
    }
    bool Cursor::Layer::getBool() const
    {
        return get<bool>();
    }
    EntityRef Cursor::Layer::getEntityRef() const
    {
        return get<EntityRef>();
    }

    bool Cursor::Layer::isDefault() const
    {
        if (instance.isSet())
        {
            return false;
        }
        if (prefab != nullptr)
        {
            return prefab->isDefault();
        }
        return true;        
    }

    bool Cursor::Layer::_loadInstanceOf()
    {
        auto* subschema = instance.getSchema();
        if ((subschema->type == DataType::object or subschema->type == DataType::oneOf)
             and instance.isSet())
        {
            auto* doc = instance.getRawJson();
            if (auto member = doc->find("InstanceOf"); member != doc->end())
            {
                if (auto const& prefabPath = member->get_ref<std::string const&>();
                    not prefabPath.empty())
                {
                    if (prefab == nullptr)
                    {
                        prefab = std::make_unique<Layer>(
                            m_entityLib, this, subschema, prefabPath.c_str());
                    }
                    else
                    {
                        prefab->_init(m_entityLib, this, subschema, prefabPath.c_str());
                    }
                }
                return true;
            }
        }
        return false;
    }

    Cursor::Layer Cursor::Layer::enterObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _checkInvariants();
        ENTLIB_DBG_ASSERT(instance.schema.base->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        ENTLIB_DBG_ASSERT(
            prefab == nullptr or prefab->getSchema()->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        ENTLIB_DBG_ASSERT(getDataType() == Ent::DataType::object);
        Layer newLayer;
        auto& lastLayer = *this;
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == Ent::DataType::object);
        newLayer.instance = lastLayer.instance.enterObjectField(_field, _fieldRef);
        newLayer.m_entityLib = m_entityLib;
        newLayer.m_parent = this;
        auto* subschema = newLayer.instance.getSchema();
        if (not newLayer._loadInstanceOf())
        {
            if (lastLayer.prefab != nullptr)
            {
                ENTLIB_ASSERT(lastLayer.prefab->m_entityLib != nullptr);
                ENTLIB_DBG_ASSERT(
                    prefab->getSchema()->deleteCheck.state_
                    == Ent::DeleteCheck::State::VALID);
                if (newLayer.prefab == nullptr)
                {
                    newLayer.prefab = std::make_unique<Layer>();
                }
                (*newLayer.prefab) = lastLayer.prefab->enterObjectField(_field, _fieldRef);
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
        return newLayer;
    }

    Cursor::Layer Cursor::Layer::enterUnionData(char const* _type)
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        if (_type == nullptr)
        {
            _type = getUnionType();
        }
        return _enterItem(
            [_type](auto&& _cur)
            {
                return _cur.enterUnionData(_type);
            });
    }

    Cursor::Layer Cursor::Layer::enterUnionSetItem(char const* _type, Subschema const* _dataSchema)
    {
        if (_dataSchema == nullptr)
        {
            auto& singularItems = getSchema()->singularItems;
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
                        getSchema()->name.c_str());
                }
            }
            else
            {
                throw Ent::BadType("Cursor::enterUnionSetItem : Not an UnionSet");
            }
        }
        return _enterItem(
            [_type, _dataSchema](auto&& _cur) { return _cur.enterUnionSetItem(_type, _dataSchema); });
    }

    template <typename E>
    Cursor::Layer Cursor::Layer::_enterItem(E&& _enter)
    {
        _checkInvariants();
        Layer newLayer;
        newLayer.m_entityLib = m_entityLib;
        auto& lastLayer = *this;
        newLayer.instance = _enter(lastLayer.instance);
        newLayer.m_parent = this;
        auto* subschema = newLayer.instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.defaultStorage = _enter(*defaultVal);
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
            if (not newLayer._loadInstanceOf())
            {
                if (lastLayer.prefab != nullptr)
                {
                    if (newLayer.prefab == nullptr)
                    {
                        newLayer.prefab = std::make_unique<Layer>();
                    }
                    (*newLayer.prefab) = _enter(*lastLayer.prefab);
                }
            }
        }
        ENTLIB_DBG_ASSERT(
            newLayer.getDefault() == nullptr
            or newLayer.getDefault()->getSchema()->type == newLayer.instance.getSchema()->type);
        return newLayer;
    }

    Cursor::Layer Cursor::Layer::enterObjectSetItem(char const* _key)
    {
        return _enterItem(
            [_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); });
    }

    Cursor::Layer Cursor::Layer::enterObjectSetItem(int64_t _key)
    {
        return _enterItem(
            [_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); });
    }

    Cursor::Layer Cursor::Layer::enterMapItem(char const* _key)
    {
        return _enterItem(
            [_key](auto&& _cur) { return _cur.enterMapItem(_key); });
    }

    Cursor::Layer Cursor::Layer::enterMapItem(int64_t _field)
    {
        return _enterItem(
            [_field](auto&& _cur) { return _cur.enterMapItem(_field); });
    }

    Cursor::Layer Cursor::Layer::enterArrayItem(size_t _index)
    {
        _checkInvariants();
        Layer newLayer;
        newLayer.m_entityLib = m_entityLib;
        auto& lastLayer = *this;
        ENTLIB_DBG_ASSERT(lastLayer.instance.getSchema()->type == Ent::DataType::array);
        newLayer.instance = lastLayer.instance.enterArrayItem(_index);
        newLayer.m_parent = this;
        auto* subschema = newLayer.instance.getSchema();
        if (not isDefault())
        {
            if (not newLayer._loadInstanceOf())
            {
                if (lastLayer.prefab != nullptr)
                {
                    if (newLayer.prefab == nullptr)
                    {
                        newLayer.prefab = std::make_unique<Layer>();
                    }
                    (*newLayer.prefab) = lastLayer.prefab->enterArrayItem(_index);
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
        return newLayer;
    }

    char const* Cursor::Layer::getInstanceOf()
    {
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Ent::Subschema schema;
        schema.type = Ent::DataType::string;
        Ent::SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        char const* result = nullptr;
        {
            auto field = enterObjectField("InstanceOf", &ref);
            if (not field.isSet())
            {
                return nullptr;
            }
            result = field.getString();
        }
        _checkInvariants();
        return result;
    }

    void Cursor::Layer::setInstanceOf(char const* _instanceOf)
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
        enterObjectField("InstanceOf", &ref).setString(_instanceOf);
        auto& lastLayer = *this;
        if (strlen(_instanceOf) != 0)
        {
            if (lastLayer.prefab == nullptr)
            {
                lastLayer.prefab =
                    std::make_unique<Layer>(m_entityLib, &lastLayer, getSchema(), _instanceOf);
            }
            else
            {
                lastLayer.prefab->_init(m_entityLib, &lastLayer, getSchema(), _instanceOf);
            }
        }
        else
        {
            lastLayer.prefab = nullptr;
        }
        _checkInvariants();
    }

    char const* Cursor::Layer::getUnionType()
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        auto& lastLayer = *this;
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

    size_t Cursor::Layer::getUnionTypeIndex()
    {
        auto type = getUnionType();
        return AT(getSchema()->unionTypeMap, type).index;
    }

    void Cursor::Layer::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(instance.schema.base != nullptr);
        ENTLIB_DBG_ASSERT(
            getDefault() == nullptr
            or getDefault()->getSchema()->type == instance.getSchema()->type);
        if (prefab != nullptr)
        {
            prefab->_checkInvariants();
            auto a = getSchema();
            auto b = prefab->getSchema();
            ENTLIB_ASSERT(a == b);
        }
#endif
    }

    DataType Cursor::Layer::getDataType() const
    {
        return instance.getSchema()->type;
    }

    Subschema const* Cursor::Layer::getSchema() const
    {
        return instance.getSchema();
    }

    char const* Cursor::Layer::getTypeName() const
    {
        return getSchema()->name.c_str();
    }

    DataType Cursor::Layer::getMapKeyType() const
    {
        return instance.getSchema()->singularItems->get().linearItems->at(0)->type;
    }

    DataType Cursor::Layer::getObjectSetKeyType() const
    {
        auto& schema = *instance.getSchema();
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

    size_t Cursor::Layer::arraySize()
    {
        auto& lastLayer = *this;
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

    size_t Cursor::Layer::size()
    {
        auto& jsonExplLayer = instance;
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

    bool Cursor::Layer::contains(Key const& _key)
    {
        auto& jsonExplLayer = instance;
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

    bool Cursor::Layer::empty()
    {
        return size() == 0;
    }

    std::set<char const*, CmpStr> Cursor::Layer::getMapKeysString()
    {
        auto& lastLayer = *this;
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
                auto pairLayer = enterArrayItem(i);
                auto keyLayer = pairLayer.enterArrayItem(0);
                auto key = keyLayer.getString();
                ENTLIB_DBG_ASSERT(node->is_array());
                auto valueLayer = pairLayer.enterArrayItem(1llu);
                if (valueLayer.isNull())
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
        _checkInvariants();
        return keys;
    }

    bool Cursor::Layer::isNull() const
    {
        auto& lastLayer = *this;
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

    std::set<int64_t> Cursor::Layer::getMapKeysInt()
    {
        auto& lastLayer = *this;
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
                auto pairLayer = enterArrayItem(i);
                auto key = pairLayer.enterArrayItem(0llu).getInt();
                if (pairLayer.enterArrayItem(1llu).isNull())
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

    std::set<int64_t> Cursor::Layer::getPrimSetKeysInt()
    {
        auto& lastLayer = *this;
        std::set<int64_t> keys;
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(enterArrayItem(i).getInt());
            }
        }
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getPrimSetKeysInt());
        }
        return keys;
    }

    std::set<char const*, CmpStr> Cursor::Layer::getPrimSetKeysString()
    {
        std::set<char const*, CmpStr> keys;
        if (instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto keyLayer = enterArrayItem(i);
                keys.insert(keyLayer.getString());
            }
        }
        auto& lastLayer = *this;
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getPrimSetKeysString());
        }
        return keys;
    }

    std::map<char const*, Subschema const*, CmpStr> Cursor::Layer::getUnionSetKeysString()
    {
        auto& lastLayer = *this;
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

    std::set<char const*, CmpStr> Cursor::Layer::getObjectSetKeysString()
    {
        _checkInvariants();
        auto& lastLayer = *this;
        auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
        std::set<char const*, CmpStr> keys;
        if (lastLayer.prefab != nullptr)
        {
            ENTLIB_ASSERT(
                std::holds_alternative<Subschema::ArrayMeta>(lastLayer.prefab->getSchema()->meta));
            keys = lastLayer.prefab->getObjectSetKeysString();
        }
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto objectLayer = enterArrayItem(i);
                if (objectLayer.instance.isSet()
                    and objectLayer.instance.getRawJson()->count("__removed__") != 0)
                {
                    auto fieldLayer = objectLayer.enterObjectField(meta.keyField->c_str());
                    keys.erase(fieldLayer.getString());
                }
                else
                {
                    auto fieldLayer = objectLayer.enterObjectField(meta.keyField->c_str());
                    keys.insert(fieldLayer.getString());
                }
            }
        }
        return keys;
    }

    std::set<int64_t> Cursor::Layer::getObjectSetKeysInt()
    {
        auto& lastLayer = *this;
        auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
        std::set<int64_t> keys;
        if (lastLayer.instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto objLayer = enterArrayItem(i);
                if (objLayer.instance.isSet()
                    and objLayer.instance.getRawJson()->count("__removed__") != 0)
                {
                    auto field = enterObjectField(meta.keyField->c_str());
                    keys.erase(field.getInt());
                }
                else
                {
                    auto field = enterObjectField(meta.keyField->c_str());
                    keys.insert(field.getInt());
                }
            }
        }
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getObjectSetKeysInt());
        }
        return keys;
    }

    bool Cursor::Layer::mapContains(char const* _key)
    {
        return getMapKeysString().count(_key) != 0;
    }

    bool Cursor::Layer::mapContains(int64_t _key)
    {
        return getMapKeysInt().count(_key) != 0;
    }

    bool Cursor::Layer::primSetContains(char const* _key)
    {
        return _countPrimSetKeyImpl(
            _key,
            [this](Layer& primLayer, char const* _key)
            { return strcmp(primLayer.getString(), _key) == 0; });
    }

    bool Cursor::Layer::primSetContains(int64_t _key)
    {
        return _countPrimSetKeyImpl(
            _key, [this](Layer& primLayer, int64_t _key) { return primLayer.getInt() == _key; });
    }

    bool Cursor::Layer::unionSetContains(char const* _key)
    {
        return getUnionSetKeysString().count(_key) != 0;
    }

    bool Cursor::Layer::objectSetContains(char const* _key)
    {
        return getObjectSetKeysString().count(_key) != 0;
    }
    bool Cursor::Layer::objectSetContains(int64_t _key)
    {
        return getObjectSetKeysInt().count(_key) != 0;
    }

    void Cursor::Layer::_buildPath()
    {
        _checkInvariants();
        std::vector<Layer*> allLayers;
        for (Layer* iter = this; iter != nullptr; iter = iter->m_parent)
        {
            allLayers.push_back(iter);
        }
        std::reverse(begin(allLayers), end(allLayers));
        auto firstNotSetIter = std::find_if(
            begin(allLayers),
            end(allLayers),
            [](Layer const* l) { return l->instance.values == nullptr; });
        ENTLIB_ASSERT(firstNotSetIter != allLayers.begin());
        auto firstNotSetIdx = std::distance(begin(allLayers), firstNotSetIter);
        ENTLIB_ASSERT(firstNotSetIdx <= ptrdiff_t(allLayers.size()));
        auto lastSet = firstNotSetIter;
        --lastSet;
        auto endIter = allLayers.end();
        for (; firstNotSetIter != endIter; ++lastSet, ++firstNotSetIter, ++firstNotSetIdx)
        {
            size_t arraySize = allLayers[firstNotSetIdx - 1]->m_arraySize;
            auto firstNotSet = *firstNotSetIter;
            firstNotSet->instance.values = FileCursor::createChildNode(
                (*lastSet)->instance,
                firstNotSet->instance.additionalPath,
                *firstNotSet->instance.schema.base,
                arraySize);
            ENTLIB_ASSERT(firstNotSet->instance.values != nullptr);
        }
        ENTLIB_ASSERT(allLayers.back()->instance.values != nullptr);
        _checkInvariants();
    }

    void Cursor::Layer::setSize(size_t _size)
    {
        _buildPath();
        instance.setSize(_size);
    }

    void Cursor::Layer::setFloat(double _value)
    {
        _buildPath();
        instance.setFloat(_value);
    }

    void Cursor::Layer::setInt(int64_t _value)
    {
        _buildPath();
        instance.setInt(_value);
    }

    void Cursor::Layer::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        ENTLIB_ASSERT(getSchema()->type == DataType::string or getSchema()->type == DataType::entityRef);
        _buildPath();
        instance.setString(_value);
    }

    void Cursor::Layer::setBool(bool _value)
    {
        _buildPath();
        instance.setBool(_value);
    }

    void Cursor::Layer::setEntityRef(EntityRef const& _value)
    {
        _buildPath();
        instance.setEntityRef(_value);
    }

    void Cursor::Layer::setUnionType(char const* _type)
    {
        _buildPath();
        instance.setUnionType(_type);
    }

    void Cursor::Layer::buildPath()
    {
        _buildPath();
    }

    template <typename K, typename E>
    bool Cursor::Layer::_countPrimSetKeyImpl(K _key, E&& _isEqual)
    {
        if (instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto item = enterArrayItem(i);
                bool const equal = _isEqual(item, _key);
                if (equal)
                {
                    return true;
                }
            }
        }
        auto& lastLayer = *this;
        if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->primSetContains(_key);
        }
        return false;
    }

    void Cursor::Layer::insertPrimSetKey(char const* _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            instance.pushBack(_key);
        }
    }

    void Cursor::Layer::insertPrimSetKey(int64_t _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            instance.pushBack(_key);
        }
    }

    nlohmann::json const* Cursor::Layer::_getRawJson()
    {
        return instance.getRawJson();
    }

    // ***************************************** Cursor *******************************************

    bool Cursor::isSet() const
    {
        return _getLastLayer().isSet();
    }

    template <typename V>
    V Cursor::get() const
    {
        return _getLastLayer().get<V>();
    }
    double Cursor::getFloat() const
    {
        return _getLastLayer().getFloat();
    }
    int64_t Cursor::getInt() const
    {
        return _getLastLayer().getInt();
    }
    char const* Cursor::getString() const
    {
        return _getLastLayer().getString();
    }
    bool Cursor::getBool() const
    {
        return _getLastLayer().getBool();
    }
    EntityRef Cursor::getEntityRef() const
    {
        return _getLastLayer().getEntityRef();
    }

    Cursor::Layer& Cursor::_allocLayer()
    {
        if (m_layers.size() < m_layerCount + 1)
        {
            return m_layers.emplace_back();
        }
        return m_layers[m_layerCount];
    }

    void Cursor::_comitNewLayer()
    {
        ++m_layerCount;
        if (_getLastLayer().instance.getSchema()->type == Ent::DataType::array)
        {
            _getLastLayer().m_arraySize = arraySize();
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
        newLayer.m_entityLib = m_entityLib;
        newLayer.setDefault(_schema, nullptr, &_schema->defaultValue);
        newLayer.instance.init(_schema, _filename, _doc);
        newLayer.m_parent = nullptr;
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        newLayer._loadInstanceOf();
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
        return _getLastLayer().isDefault();
    }

    Cursor& Cursor::enterUnionData(char const* _type)
    {
        auto& newLayer = _allocLayer();
        newLayer = _getLastLayer().enterUnionData(_type);
        _comitNewLayer();
        return *this;
    }
    Cursor& Cursor::enterUnionSetItem(char const* _type, Subschema const* _dataSchema)
    {
        auto& newLayer = _allocLayer();
        newLayer = _getLastLayer().enterUnionSetItem(_type, _dataSchema);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterObjectField(char const* _key, struct Ent::SubschemaRef const* _schema)
    {
        _checkInvariants();
        auto& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(lastLayer.getSchema()->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        ENTLIB_DBG_ASSERT(
            lastLayer.prefab == nullptr
            or lastLayer.prefab->getSchema()->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        newLayer = lastLayer.enterObjectField(_key, _schema);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterObjectSetItem(char const* _key)
    {
        auto& newAlloc = _allocLayer();
        newAlloc = _getLastLayer().enterObjectSetItem(_key);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterObjectSetItem(int64_t _key)
    {
        auto& newAlloc = _allocLayer();
        newAlloc = _getLastLayer().enterObjectSetItem(_key);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterMapItem(char const* _key)
    {
        auto& newAlloc = _allocLayer();
        newAlloc = _getLastLayer().enterMapItem(_key);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterMapItem(int64_t _field)
    {
        auto& newAlloc = _allocLayer();
        newAlloc = _getLastLayer().enterMapItem(_field);
        _comitNewLayer();
        return *this;
    }

    Cursor& Cursor::enterArrayItem(size_t _index)
    {
        auto& newAlloc = _allocLayer();
        newAlloc = _getLastLayer().enterArrayItem(_index);
        _comitNewLayer();
        return *this;
    }

    char const* Cursor::getInstanceOf()
    {
        char const* result = nullptr;
        result = _getLastLayer().getInstanceOf();
        _checkInvariants();
        return result;
    }

    char const* Cursor::getUnionType()
    {
        return _getLastLayer().getUnionType();
    }

    size_t Cursor::getUnionTypeIndex()
    {
        return _getLastLayer().getUnionTypeIndex();
    }

    void Cursor::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_layerCount != 0);
        ENTLIB_DBG_ASSERT(_getLastLayer().instance.schema.base != nullptr);
        [[maybe_unused]] auto& lastLayer = _getLastLayer();
        lastLayer._checkInvariants();
        ENTLIB_DBG_ASSERT(lastLayer.getSchema()->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        ENTLIB_DBG_ASSERT(
            lastLayer.prefab == nullptr
            or lastLayer.prefab->getSchema()->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
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
        return _getLastLayer().getDataType();
    }

    Subschema const* Cursor::getSchema() const
    {
        return _getLastLayer().getSchema();
    }

    char const* Cursor::getTypeName() const
    {
        return _getLastLayer().getTypeName();
    }

    DataType Cursor::getMapKeyType() const
    {
        return _getLastLayer().getMapKeyType();
    }

    DataType Cursor::getObjectSetKeyType() const
    {
        return _getLastLayer().getObjectSetKeyType();
    }

    size_t Cursor::arraySize()
    {
        return _getLastLayer().arraySize();
    }

    size_t Cursor::size()
    {
        return _getLastLayer().size();
    }

    bool Cursor::contains(Key const& _key)
    {
        return _getLastLayer().contains(_key);
    }

    bool Cursor::empty()
    {
        return _getLastLayer().empty();
    }

    std::set<char const*, CmpStr> Cursor::getMapKeysString()
    {
        return _getLastLayer().getMapKeysString();
    }

    bool Cursor::isNull() const
    {
        return _getLastLayer().isNull();
    }

    std::set<int64_t> Cursor::getMapKeysInt()
    {
        return _getLastLayer().getMapKeysInt();
    }

    std::set<int64_t> Cursor::getPrimSetKeysInt()
    {
        return _getLastLayer().getPrimSetKeysInt();
    }

    std::set<char const*, CmpStr> Cursor::getPrimSetKeysString()
    {
        return _getLastLayer().getPrimSetKeysString();
    }

    std::map<char const*, Subschema const*, CmpStr> Cursor::getUnionSetKeysString()
    {
        return _getLastLayer().getUnionSetKeysString();
    }

    std::set<char const*, CmpStr> Cursor::getObjectSetKeysString()
    {
        return _getLastLayer().getObjectSetKeysString();
    }

    std::set<int64_t> Cursor::getObjectSetKeysInt()
    {
        return _getLastLayer().getObjectSetKeysInt();
    }

    bool Cursor::mapContains(char const* _key)
    {
        return _getLastLayer().mapContains(_key);
    }

    bool Cursor::mapContains(int64_t _key)
    {
        return _getLastLayer().mapContains(_key);
    }

    bool Cursor::primSetContains(char const* _key)
    {
        return _getLastLayer().primSetContains(_key);
    }

    bool Cursor::primSetContains(int64_t _key)
    {
        return _getLastLayer().primSetContains(_key);
    }

    bool Cursor::unionSetContains(char const* _key)
    {
        return _getLastLayer().unionSetContains(_key);
    }

    bool Cursor::objectSetContains(char const* _key)
    {
        return _getLastLayer().objectSetContains(_key);
    }
    bool Cursor::objectSetContains(int64_t _key)
    {
        return _getLastLayer().objectSetContains(_key);
    }

    void Cursor::setInstanceOf(char const* _instanceOf)
    {
        return getLastRung().setInstanceOf(_instanceOf);
    }

    void Cursor::setSize(size_t _size)
    {
        getLastRung().setSize(_size);
    }

    void Cursor::setFloat(double _value)
    {
        _getLastLayer().setFloat(_value);
    }

    void Cursor::setInt(int64_t _value)
    {
        _getLastLayer().setInt(_value);
    }

    void Cursor::setString(char const* _value)
    {
        _getLastLayer().setString(_value);
    }

    void Cursor::setBool(bool _value)
    {
        _getLastLayer().setBool(_value);
    }

    void Cursor::setEntityRef(EntityRef const& _value)
    {
        _getLastLayer().setEntityRef(_value);
    }

    void Cursor::setUnionType(char const* _type)
    {
        _getLastLayer().setUnionType(_type);
    }

    void Cursor::buildPath()
    {
        getLastRung().buildPath();
    }

    void Cursor::insertPrimSetKey(char const* _key)
    {
        return getLastRung().insertPrimSetKey(_key);
    }

    void Cursor::insertPrimSetKey(int64_t _key)
    {
        return getLastRung().insertPrimSetKey(_key);
    }

} // namespace Ent
