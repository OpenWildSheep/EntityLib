#include "PropImpl.h"
#include "include/EntityLib.h"

#include <utility>

namespace Ent
{
    void Cursor::setDefault(
        Ent::Subschema const* _schema, char const* _filePath, nlohmann::json const* _document)
    {
        // Loïc : To fix this aweful const_cast, FileCursor need a const version 'ConstFileCursor'.
        // This is a "not-so-easy" task just to remove a const_cast so it is not a priority I guess.
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        defaultStorage = FileCursor{_schema, _filePath, const_cast<nlohmann::json*>(_document)};
    }
    void Cursor::clear()
    {
        prefab.reset();
        m_parent.reset();
        defaultStorage.reset();
        m_arraySize = 0;
    }
    FileCursor* Cursor::getDefault()
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<FileCursor*>(std::as_const(*this).getDefault());
    }
    FileCursor const* Cursor::getDefault() const
    {
        if (not defaultStorage.has_value())
        {
            return nullptr;
        }
        return &(*defaultStorage);
    }

    bool Cursor::isSet() const
    {
        return m_instance.isSet();
    }

    template <typename V>
    V Cursor::get() const
    {
        auto& lastLayer = *this;
        if (isSet())
        {
            return m_instance.get<V>();
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

    Cursor::Cursor(
        EntityLib* _entityLib,
        PropImplPtr _parent,
        Ent::Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc)
    {
        _init(_entityLib, std::move(_parent), _schema, _filename, _doc);
    }

    Cursor::~Cursor()
    {
        ENTLIB_ASSERT_NOTHROW(m_deleteCheck.state_ == DeleteCheck::State::VALID);
        prefab.reset();
        m_parent.reset();
    }

    void Cursor::_init(
        EntityLib* _entityLib,
        PropImplPtr _parent,
        Ent::Subschema const* _schema,
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
        m_instance = FileCursor(_schema, _filename, _doc);
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        _loadInstanceOf();
    }

    void Cursor::_init(
        EntityLib* _entityLib, PropImplPtr _parent, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(
            _entityLib, std::move(_parent), _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    Cursor::Cursor(
        EntityLib* _entityLib, PropImplPtr _parent, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(
            _entityLib, std::move(_parent), _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    void Cursor::save(char const* _filename) const
    {
        m_instance.save(_filename);
    }

    bool Cursor::isDefault() const
    {
        auto& newLayer = *this;
        if (m_instance.isSet())
        {
            return false;
        }
        if (newLayer.prefab != nullptr)
        {
            return newLayer.prefab->isDefault();
        }
        return true;
    }

    bool Cursor::_loadInstanceOf()
    {
        auto* subschema = getSchema();
        if ((subschema->type == DataType::object or subschema->type == DataType::oneOf)
            and m_instance.isSet())
        {
            auto* doc = m_instance.getRawJson();
            if (auto member = doc->find("InstanceOf"); member != doc->end())
            {
                if (auto const& prefabPath = member->get_ref<std::string const&>();
                    not prefabPath.empty())
                {
                    prefab =
                        m_entityLib->newPropImpl(nullptr, subschema, prefabPath.c_str(), nullptr);
                }
                return true;
            }
        }
        return false;
    }

    PropImplPtr Cursor::enterObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _checkInvariants();
        ENTLIB_DBG_ASSERT(getDataType() == Ent::DataType::object);
        auto newLayer = m_entityLib->newPropImpl();
        auto& lastLayer = *this;
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == Ent::DataType::object);
        newLayer->m_instance = lastLayer.m_instance.enterObjectField(_field, _fieldRef);
        newLayer->m_entityLib = m_entityLib;
        newLayer->m_parent = shared_from_this();
        auto* subschema = newLayer->getSchema();
        if (not newLayer->_loadInstanceOf())
        {
            if (lastLayer.prefab != nullptr)
            {
                newLayer->prefab = lastLayer.prefab->enterObjectField(_field, _fieldRef);
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
                newLayer->defaultStorage = std::move(objectField);
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

    PropImplPtr Cursor::enterUnionData(char const* _type)
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        if (_type == nullptr)
        {
            _type = getUnionType();
        }
        return _enterItem([_type](auto&& _cur) { return _cur.enterUnionData(_type); });
    }

    PropImplPtr Cursor::enterUnionSetItem(char const* _type, Subschema const* _dataSchema)
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
                        _type, "Cursor::enterUnionSetItem", m_instance.getSchema()->name.c_str());
                }
            }
            else
            {
                throw Ent::BadType("Cursor::enterUnionSetItem : Not an UnionSet");
            }
        }
        return _enterItem([_type, _dataSchema](auto&& _cur)
                          { return _cur.enterUnionSetItem(_type, _dataSchema); });
    }

    template <typename E>
    PropImplPtr Cursor::_enterItem(E&& _enter)
    {
        _checkInvariants();
        auto newLayerPtr = m_entityLib->newPropImpl();
        Cursor& newLayer = *newLayerPtr;
        auto& lastLayer = *this;
        newLayer.m_entityLib = m_entityLib;
        newLayer.m_instance = _enter(lastLayer.m_instance);
        newLayer.m_parent = shared_from_this();
        auto* subschema = newLayer.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.defaultStorage = _enter(*defaultVal);
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
                if (lastLayer.prefab != nullptr)
                {
                    newLayer.prefab = _enter(*lastLayer.prefab);
                }
            }
        }
        return newLayerPtr;
    }

    PropImplPtr Cursor::enterObjectSetItem(char const* _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); });
    }

    PropImplPtr Cursor::enterObjectSetItem(int64_t _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); });
    }

    PropImplPtr Cursor::enterMapItem(char const* _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.enterMapItem(_key); });
    }

    PropImplPtr Cursor::enterMapItem(int64_t _field)
    {
        return _enterItem([_field](auto&& _cur) { return _cur.enterMapItem(_field); });
    }

    PropImplPtr Cursor::enterArrayItem(size_t _index)
    {
        _checkInvariants();
        auto newLayerPtr = m_entityLib->newPropImpl();
        Cursor& newLayer = *newLayerPtr;
        newLayer.m_entityLib = m_entityLib;
        auto& lastLayer = *this;
        ENTLIB_DBG_ASSERT(lastLayer.m_instance.getSchema()->type == Ent::DataType::array);
        newLayer.m_instance = lastLayer.m_instance.enterArrayItem(_index);
        newLayer.m_parent = shared_from_this();
        auto* subschema = newLayer.getSchema();
        if (not isDefault())
        {
            if (not newLayer._loadInstanceOf())
            {
                if (lastLayer.prefab != nullptr)
                {
                    newLayer.prefab = lastLayer.prefab->enterArrayItem(_index);
                }
            }
        }
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            newLayer.defaultStorage = defaultVal->enterArrayItem(_index);
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

    char const* Cursor::getInstanceOf()
    {
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Ent::Subschema schema;
        schema.type = Ent::DataType::string;
        Ent::SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        auto field = enterObjectField("InstanceOf", &ref);
        if (not field->isSet())
        {
            return nullptr;
        }
        char const* result = field->getString();
        _checkInvariants();
        return result;
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
        enterObjectField("InstanceOf", &ref)->setString(_instanceOf);
        auto& lastLayer = *this;
        if (strlen(_instanceOf) != 0)
        {
            lastLayer.prefab = m_entityLib->newPropImpl(nullptr, getSchema(), _instanceOf, nullptr);
        }
        else
        {
            lastLayer.prefab = nullptr;
        }
    }

    char const* Cursor::getUnionType()
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        auto& lastLayer = *this;
        if (char const* type = lastLayer.m_instance.getUnionType())
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
        ENTLIB_DBG_ASSERT(m_instance.getSchema() != nullptr);
        ENTLIB_DBG_ASSERT(
            getDefault() == nullptr
            or getDefault()->getSchema()->type == m_instance.getSchema()->type);
        if (prefab != nullptr)
        {
            prefab->_checkInvariants();
        }
#endif
    }

    DataType Cursor::getDataType() const
    {
        return getSchema()->type;
    }

    char const* Cursor::getTypeName() const
    {
        return getSchema()->name.c_str();
    }

    DataType Cursor::getMapKeyType() const
    {
        return getSchema()->singularItems->get().linearItems->at(0)->type;
    }

    DataType Cursor::getObjectSetKeyType() const
    {
        auto& schema = *getSchema();
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
        auto& lastLayer = *this;
        auto& jsonExplLayer = lastLayer.m_instance;
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
        auto& jsonExplLayer = m_instance;
        auto* schema = jsonExplLayer.getSchema();
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
        auto& jsonExplLayer = m_instance;
        auto* schema = jsonExplLayer.getSchema();
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
        if (lastLayer.m_instance.isSet())
        {
            auto* node = lastLayer.m_instance.getRawJson();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (size_t i = 0; i < node->size(); ++i)
            {
                ENTLIB_DBG_ASSERT(node->is_array());
                auto pairLayer = enterArrayItem(i);
                auto key = pairLayer->enterArrayItem(0)->getString();
                ENTLIB_DBG_ASSERT(node->is_array());
                if (pairLayer->enterArrayItem(1llu)->isNull())
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

    bool Cursor::isNull() const
    {
        auto& lastLayer = *this;
        if (lastLayer.m_instance.isSetOrNull())
        {
            return lastLayer.m_instance.isNull();
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
        auto& lastLayer = *this;
        std::set<int64_t> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getMapKeysInt();
        }
        if (lastLayer.m_instance.isSet())
        {
            auto const arraySize = lastLayer.m_instance.getRawJson()->size();
            for (size_t i = 0; i < arraySize; ++i)
            {
                auto pairLayer = enterArrayItem(i);
                auto key = pairLayer->enterArrayItem(0llu)->getInt();
                if (pairLayer->enterArrayItem(1llu)->isNull())
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
    std::set<int64_t> Cursor::getPrimSetKeysInt()
    {
        auto& lastLayer = *this;
        std::set<int64_t> keys;
        if (lastLayer.m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(enterArrayItem(i)->getInt());
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
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                keys.insert(enterArrayItem(i)->getString());
            }
        }
        auto& lastLayer = *this;
        if (lastLayer.prefab != nullptr)
        {
            keys.merge(lastLayer.prefab->getPrimSetKeysString());
        }
        return keys;
    }

    std::map<char const*, Subschema const*, CmpStr> Cursor::getUnionSetKeysString()
    {
        auto& lastLayer = *this;
        std::map<char const*, Subschema const*, CmpStr> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getUnionSetKeysString();
        }
        if (lastLayer.m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto arrayItem = lastLayer.m_instance.enterArrayItem(i);
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
        auto& lastLayer = *this;
        auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
        std::set<char const*, CmpStr> keys;
        if (lastLayer.prefab != nullptr)
        {
            keys = lastLayer.prefab->getObjectSetKeysString();
        }
        if (lastLayer.m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto objectLayer = enterArrayItem(i);
                if (objectLayer->m_instance.isSet()
                    and objectLayer->m_instance.getRawJson()->count("__removed__") != 0)
                {
                    keys.erase(objectLayer->enterObjectField(meta.keyField->c_str())->getString());
                }
                else
                {
                    keys.insert(objectLayer->enterObjectField(meta.keyField->c_str())->getString());
                }
            }
        }
        return keys;
    }

    std::set<int64_t> Cursor::getObjectSetKeysInt()
    {
        auto& lastLayer = *this;
        auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
        std::set<int64_t> keys;
        if (lastLayer.m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto objLayer = enterArrayItem(i);
                if (objLayer->m_instance.isSet()
                    and objLayer->m_instance.getRawJson()->count("__removed__") != 0)
                {
                    keys.erase(enterObjectField(meta.keyField->c_str())->getInt());
                }
                else
                {
                    keys.insert(enterObjectField(meta.keyField->c_str())->getInt());
                }
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
            _key,
            [this](Cursor& primLayer, char const* _key)
            { return strcmp(primLayer.getString(), _key) == 0; });
    }
    bool Cursor::primSetContains(int64_t _key)
    {
        return _countPrimSetKeyImpl(
            _key, [this](Cursor& primLayer, int64_t _key) { return primLayer.getInt() == _key; });
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
        std::vector<Cursor*> allLayers;
        for (Cursor* iter = this; iter != nullptr; iter = iter->m_parent.get())
        {
            allLayers.push_back(iter);
        }
        std::reverse(begin(allLayers), end(allLayers));
        auto firstNotSet = std::find_if(
            begin(allLayers),
            end(allLayers),
            [](Cursor const* l) { return not l->m_instance.isSetOrNull(); });
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
            firstCursorNotSet->m_instance.setRawJson(FileCursor::createChildNode(
                (*lastSet)->m_instance,
                firstCursorNotSet->m_instance.getPathToken(),
                *firstCursorNotSet->m_instance.getSchema(),
                arraySize));
            ENTLIB_ASSERT(firstCursorNotSet->m_instance.isSetOrNull());
        }
        _checkInvariants();
    }
    void Cursor::setSize(size_t _size)
    {
        _buildPath();
        m_instance.setSize(_size);
    }

    void Cursor::setFloat(double _value)
    {
        _buildPath();
        m_instance.setFloat(_value);
    }
    void Cursor::setInt(int64_t _value)
    {
        _buildPath();
        m_instance.setInt(_value);
    }
    void Cursor::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        _buildPath();
        m_instance.setString(_value);
    }
    void Cursor::setBool(bool _value)
    {
        _buildPath();
        m_instance.setBool(_value);
    }
    void Cursor::setEntityRef(EntityRef const& _value)
    {
        _buildPath();
        m_instance.setEntityRef(_value);
    }
    void Cursor::setUnionType(char const* _type)
    {
        _buildPath();
        m_instance.setUnionType(_type);
    }
    void Cursor::buildPath()
    {
        _buildPath();
    }

    template <typename K, typename E>
    bool Cursor::_countPrimSetKeyImpl(K _key, E&& _isEqual)
    {
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                auto item = enterArrayItem(i);
                bool const equal = _isEqual(*item, _key);
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

    void Cursor::insertPrimSetKey(char const* _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
        }
    }
    void Cursor::insertPrimSetKey(int64_t _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
        }
    }

    nlohmann::json const* Cursor::getRawJson()
    {
        return m_instance.getRawJson();
    }

    Subschema const* Cursor::getSchema() const
    {
        return m_instance.getSchema();
    }

    void decRef(Cursor* self)
    {
        ENTLIB_ASSERT(self->m_refCount > 0);
        ENTLIB_ASSERT(self->m_deleteCheck.state_ == DeleteCheck::State::VALID);
        --self->m_refCount;
        if (self->m_refCount == 0)
        {
            auto& pool = self->m_entityLib->propertyPool;
            self->~Cursor();
            pool.free(self);
            self = nullptr;
        }
    }

} // namespace Ent
