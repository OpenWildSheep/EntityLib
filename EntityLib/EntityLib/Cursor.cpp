#include "include/EntityLib/Cursor.h"
#include "include/EntityLib.h"

#include <utility>

namespace Ent
{
    void Layer::setDefault(
        Ent::Subschema const* _schema, char const* _filePath, nlohmann::json const* _document)
    {
        // Loïc : To fix this aweful const_cast, FileCursor need a const version 'ConstFileCursor'.
        // This is a "not-so-easy" task just to remove a const_cast so it is not a priority I guess.
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        defaultStorage = FileCursor{_schema, _filePath, const_cast<nlohmann::json*>(_document)};
    }
    void Layer::clear()
    {
        prefab = nullptr;
        defaultStorage.reset();
        m_arraySize = 0;
    }
    FileCursor* Layer::getDefault()
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<FileCursor*>(std::as_const(*this).getDefault());
    }
    FileCursor const* Layer::getDefault() const
    {
        if (not defaultStorage.has_value())
        {
            return nullptr;
        }
        return &(*defaultStorage);
    }

    bool Layer::isSet() const
    {
        return m_instance.isSet();
    }

    template <typename V>
    V Layer::get() const
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

    double Layer::getFloat() const
    {
        return get<double>();
    }
    int64_t Layer::getInt() const
    {
        return get<int64_t>();
    }
    char const* Layer::getString() const
    {
        return get<char const*>();
    }
    bool Layer::getBool() const
    {
        return get<bool>();
    }
    EntityRef Layer::getEntityRef() const
    {
        return get<EntityRef>();
    }

    Layer::Layer(Layer const& _other)
        : m_entityLib(_other.m_entityLib)
        , m_arraySize(_other.m_arraySize)
        , m_instance(_other.m_instance)
        , m_parent(_other.m_parent)
    {
        if (_other.prefab != nullptr)
        {
            prefab = m_entityLib->newLayer(*_other.prefab);
        }
    }

    Layer& Layer::operator=(Layer const& _other)
    {
        Layer copy(_other);
        std::swap(copy, *this);
        return *this;
    }

    Layer::Layer(
        EntityLib* _entityLib,
        Layer* _parent,
        Ent::Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc)
    {
        _init(_entityLib, _parent, _schema, _filename, _doc);
    }

    void Layer::_init(
        EntityLib* _entityLib,
        Layer* _parent,
        Ent::Subschema const* _schema,
        char const* _filename,
        nlohmann::json* _doc)
    {
        if (_doc == nullptr)
            _doc = &_entityLib->readJsonFile(_filename);
        ENTLIB_ASSERT(_schema != nullptr);
        m_entityLib = _entityLib;
        m_parent = _parent;

        setDefault(_schema, nullptr, &_schema->defaultValue);
        m_instance.init(_schema, _filename, _doc);
        ENTLIB_ASSERT(_doc != nullptr);
        ENTLIB_ASSERT(_doc->is_object());
        _loadInstanceOf();
    }

    void Layer::_init(
        EntityLib* _entityLib, Layer* _parent, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(_entityLib, _parent, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    Layer::Layer(
        EntityLib* _entityLib, Layer* _parent, Ent::Subschema const* _schema, char const* _filename)
    {
        _init(_entityLib, _parent, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    void Layer::save(char const* _filename) const
    {
        m_instance.save(_filename);
    }

    bool Layer::isDefault() const
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

    bool Layer::_loadInstanceOf()
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
                    if (prefab == nullptr)
                    {
                        prefab =
                            m_entityLib->newLayer(this, subschema, prefabPath.c_str(), nullptr);
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

    LayerSharedPtr Layer::enterObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        _checkInvariants();
        ENTLIB_DBG_ASSERT(getDataType() == Ent::DataType::object);
        LayerSharedPtr newLayer = m_entityLib->newLayer();
        auto& lastLayer = *this;
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == Ent::DataType::object);
        newLayer->m_instance = lastLayer.m_instance.enterObjectField(_field, _fieldRef);
        newLayer->m_entityLib = m_entityLib;
        newLayer->m_parent = this;
        auto* subschema = newLayer->getSchema();
        if (not newLayer->_loadInstanceOf())
        {
            if (lastLayer.prefab != nullptr)
            {
                ENTLIB_ASSERT(lastLayer.prefab->m_entityLib != nullptr);
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

    LayerSharedPtr Layer::enterUnionData(char const* _type)
    {
        ENTLIB_ASSERT(getSchema()->type == Ent::DataType::oneOf);
        if (_type == nullptr)
        {
            _type = getUnionType();
        }
        return _enterItem([_type](auto&& _cur) { return _cur.enterUnionData(_type); });
    }

    LayerSharedPtr Layer::enterUnionSetItem(char const* _type, Subschema const* _dataSchema)
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
    LayerSharedPtr Layer::_enterItem(E&& _enter)
    {
        _checkInvariants();
        LayerSharedPtr newLayerPtr = m_entityLib->newLayer();
        Layer& newLayer = *newLayerPtr;
        auto& lastLayer = *this;
        newLayer.m_entityLib = m_entityLib;
        newLayer.m_instance = _enter(lastLayer.m_instance);
        newLayer.m_parent = this;
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
        ENTLIB_DBG_ASSERT(
            newLayer.getDefault() == nullptr
            or newLayer.getDefault()->getSchema()->type == newLayer.m_instance.getSchema()->type);
        return newLayerPtr;
    }

    LayerSharedPtr Layer::enterObjectSetItem(char const* _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); });
    }

    LayerSharedPtr Layer::enterObjectSetItem(int64_t _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.enterObjectSetItem(_key); });
    }

    LayerSharedPtr Layer::enterMapItem(char const* _key)
    {
        return _enterItem([_key](auto&& _cur) { return _cur.enterMapItem(_key); });
    }

    LayerSharedPtr Layer::enterMapItem(int64_t _field)
    {
        return _enterItem([_field](auto&& _cur) { return _cur.enterMapItem(_field); });
    }

    LayerSharedPtr Layer::enterArrayItem(size_t _index)
    {
        _checkInvariants();
        LayerSharedPtr newLayerPtr = m_entityLib->newLayer();
        Layer& newLayer = *newLayerPtr;
        newLayer.m_entityLib = m_entityLib;
        auto& lastLayer = *this;
        ENTLIB_DBG_ASSERT(lastLayer.m_instance.getSchema()->type == Ent::DataType::array);
        newLayer.m_instance = lastLayer.m_instance.enterArrayItem(_index);
        newLayer.m_parent = this;
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

    char const* Layer::getInstanceOf()
    {
        // The field InstanceOf is not a field of objects, so we have to fake it.
        Ent::Subschema schema;
        schema.type = Ent::DataType::string;
        Ent::SubschemaRef ref;
        ref.subSchemaOrRef = std::move(schema);
        char const* result = nullptr;
        {
            auto field = enterObjectField("InstanceOf", &ref);
            if (not field->isSet())
            {
                return nullptr;
            }
            result = field->getString();
        }
        _checkInvariants();
        return result;
    }

    void Layer::setInstanceOf(char const* _instanceOf)
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
            if (lastLayer.prefab == nullptr)
            {
                lastLayer.prefab = m_entityLib->newLayer();
                *lastLayer.prefab = Layer(m_entityLib, &lastLayer, getSchema(), _instanceOf);
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
    }

    char const* Layer::getUnionType()
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

    size_t Layer::getUnionTypeIndex()
    {
        auto type = getUnionType();
        return AT(getSchema()->unionTypeMap, type).index;
    }

    void Layer::_checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_instance.schema.base != nullptr);
        ENTLIB_DBG_ASSERT(
            getDefault() == nullptr
            or getDefault()->getSchema()->type == m_instance.getSchema()->type);
        if (prefab != nullptr)
        {
            prefab->_checkInvariants();
        }
#endif
    }

    DataType Layer::getDataType() const
    {
        return getSchema()->type;
    }

    char const* Layer::getTypeName() const
    {
        return getSchema()->name.c_str();
    }

    DataType Layer::getMapKeyType() const
    {
        return getSchema()->singularItems->get().linearItems->at(0)->type;
    }

    DataType Layer::getObjectSetKeyType() const
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

    size_t Layer::arraySize()
    {
        auto& lastLayer = *this;
        auto& jsonExplLayer = lastLayer.m_instance;
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

    size_t Layer::size()
    {
        auto& jsonExplLayer = m_instance;
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

    bool Layer::contains(Key const& _key)
    {
        auto& jsonExplLayer = m_instance;
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

    bool Layer::empty()
    {
        return size() == 0;
    }

    std::set<char const*, CmpStr> Layer::getMapKeysString()
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

    bool Layer::isNull() const
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
    std::set<int64_t> Layer::getMapKeysInt()
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
    std::set<int64_t> Layer::getPrimSetKeysInt()
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
    std::set<char const*, CmpStr> Layer::getPrimSetKeysString()
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

    std::map<char const*, Subschema const*, CmpStr> Layer::getUnionSetKeysString()
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

    std::set<char const*, CmpStr> Layer::getObjectSetKeysString()
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

    std::set<int64_t> Layer::getObjectSetKeysInt()
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

    bool Layer::mapContains(char const* _key)
    {
        return getMapKeysString().count(_key) != 0;
    }
    bool Layer::mapContains(int64_t _key)
    {
        return getMapKeysInt().count(_key) != 0;
    }
    bool Layer::primSetContains(char const* _key)
    {
        return _countPrimSetKeyImpl(
            _key,
            [this](Layer& primLayer, char const* _key)
            { return strcmp(primLayer.getString(), _key) == 0; });
    }
    bool Layer::primSetContains(int64_t _key)
    {
        return _countPrimSetKeyImpl(
            _key, [this](Layer& primLayer, int64_t _key) { return primLayer.getInt() == _key; });
    }
    bool Layer::unionSetContains(char const* _key)
    {
        return getUnionSetKeysString().count(_key) != 0;
    }
    bool Layer::objectSetContains(char const* _key)
    {
        return getObjectSetKeysString().count(_key) != 0;
    }
    bool Layer::objectSetContains(int64_t _key)
    {
        return getObjectSetKeysInt().count(_key) != 0;
    }

    void Layer::_buildPath()
    {
        _checkInvariants();
        std::vector<Layer*> allLayers;
        for (Layer* iter = this; iter != nullptr; iter = iter->m_parent)
        {
            ENTLIB_ASSERT(iter != (Layer*)DeletedLayer);
            allLayers.push_back(iter);
        }
        std::reverse(begin(allLayers), end(allLayers));
        auto firstNotSetIter = std::find_if(
            begin(allLayers),
            end(allLayers),
            [](Layer const* l) { return l->m_instance.values == nullptr; });
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
            firstNotSet->m_instance.values = FileCursor::createChildNode(
                (*lastSet)->m_instance,
                firstNotSet->m_instance.additionalPath,
                *firstNotSet->m_instance.schema.base,
                arraySize);
            ENTLIB_ASSERT(firstNotSet->m_instance.values != nullptr);
        }
        ENTLIB_ASSERT(allLayers.back()->m_instance.values != nullptr);
        _checkInvariants();
    }
    void Layer::setSize(size_t _size)
    {
        _buildPath();
        m_instance.setSize(_size);
    }

    void Layer::setFloat(double _value)
    {
        _buildPath();
        m_instance.setFloat(_value);
    }
    void Layer::setInt(int64_t _value)
    {
        _buildPath();
        m_instance.setInt(_value);
    }
    void Layer::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        _buildPath();
        m_instance.setString(_value);
    }
    void Layer::setBool(bool _value)
    {
        _buildPath();
        m_instance.setBool(_value);
    }
    void Layer::setEntityRef(EntityRef const& _value)
    {
        _buildPath();
        m_instance.setEntityRef(_value);
    }
    void Layer::setUnionType(char const* _type)
    {
        _buildPath();
        m_instance.setUnionType(_type);
    }
    void Layer::buildPath()
    {
        _buildPath();
    }

    template <typename K, typename E>
    bool Layer::_countPrimSetKeyImpl(K _key, E&& _isEqual)
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

    void Layer::insertPrimSetKey(char const* _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
        }
    }
    void Layer::insertPrimSetKey(int64_t _key)
    {
        if (not primSetContains(_key))
        {
            _buildPath();
            m_instance.pushBack(_key);
        }
    }

    nlohmann::json const* Layer::_getRawJson()
    {
        return m_instance.getRawJson();
    }

    Subschema const* Layer::getSchema() const
    {
        return m_instance.getSchema();
    }

    void destroyAndFree(Layer* ptr)
    {
        auto& pool = ptr->m_entityLib->layerPool;
        ptr->~Layer();
        pool.free(ptr);
    }
} // namespace Ent
