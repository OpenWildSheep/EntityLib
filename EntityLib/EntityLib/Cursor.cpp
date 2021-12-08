#include "include/EntityLib/Cursor.h"

namespace Ent
{
    void Cursor::Layer::setDefault(
        Ent::Subschema const* _schema, char const* filePath, nlohmann::json* _document)
    {
        defaultStorage.init(_schema, filePath, _document);
        defaultVal = 0;
    }
    void Cursor::Layer::clear()
    {
        prefab = nullptr;
        defaultVal = 1; // 1 == undefined
        defaultStorage.clear();
        arraySize = 0;
        isDefault = false;
    }
    FileCursor* Cursor::Layer::getDefault()
    {
        if (defaultVal == 1)
        {
            return nullptr;
        }
        else
        {
            return &(this + defaultVal)->defaultStorage;
        }
    }
    FileCursor const* Cursor::Layer::getDefault() const
    {
        if (defaultVal == 1)
        {
            return nullptr;
        }
        else
        {
            return &(this + defaultVal)->defaultStorage;
        }
    }

    bool Cursor::isSet() const
    {
        return m_instance.isSet();
    }

    // Identical to isDefault
    //bool Cursor::hasDefaultValue() const
    //{
    //    return not m_instance.isSet() and (m_layers.back().prefab == nullptr
    //           or m_layers.back().prefab->isSet());
    //}

    double Cursor::getFloat() const
    {
        auto& lastLayer = _getLastLayer();
        if (isSet())
        {
            return m_instance.getFloat();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getFloat();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
                 defaultVal != nullptr and defaultVal->isSet())
        {
            return defaultVal->getFloat();
        }
        else
        {
            return 0.;
        }
    }
    int64_t Cursor::getInt() const
    {
        auto& lastLayer = _getLastLayer();
        if (isSet())
        {
            return m_instance.getInt();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getInt();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
                 defaultVal != nullptr and defaultVal->isSet())
        {
            return defaultVal->getInt();
        }
        else
        {
            return 0;
        }
    }
    char const* Cursor::getString() const
    {
        auto& lastLayer = _getLastLayer();
        if (isSet())
        {
            return m_instance.getString();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getString();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
                 defaultVal != nullptr and defaultVal->isSet())
        {
            return defaultVal->getString();
        }
        else if (not getSchema()->enumValues.empty())
        {
            return getSchema()->enumValues.front().c_str();
        }
        else
        {
            return "";
        }
    }
    bool Cursor::getBool() const
    {
        auto& lastLayer = _getLastLayer();
        if (isSet())
        {
            return m_instance.getBool();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getBool();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
                 defaultVal != nullptr and defaultVal->isSet())
        {
            return defaultVal->getBool();
        }
        else
        {
            return false;
        }
    }
    EntityRef Cursor::getEntityRef() const
    {
        auto& lastLayer = _getLastLayer();
        if (isSet())
        {
            return m_instance.getEntityRef();
        }
        else if (lastLayer.prefab != nullptr)
        {
            return lastLayer.prefab->getEntityRef();
        }
        else if (auto* defaultVal = lastLayer.getDefault();
                 defaultVal != nullptr and defaultVal->isSet())
        {
            return defaultVal->getEntityRef();
        }
        else
        {
            return {};
        }
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

    void Cursor::_validNewLayer()
    {
        ++m_layerCount;
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
        init(_entityLib, _schema, _filename, _doc);
    }
    void Cursor::init(
        EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename, nlohmann::json* _doc)
    {
        m_entityLib = _entityLib;
        m_instance.init(_schema, _filename, _doc);

        ENTLIB_ASSERT(_schema != nullptr);
        // m_layers.resize(10);
        m_layerCount = 0;
        Layer& newLayer = _allocLayer();
        ///////////////////////////////////////////////////////////////////////////////////////
        // DO NOT COMIT THIS const_cast !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ///////////////////////////////////////////////////////////////////////////////////////
        newLayer.setDefault(_schema, nullptr, const_cast<nlohmann::json*>(&_schema->defaultValue));
        //[[maybe_unused]] auto type = _document->GetType();
        //ENTLIB_DBG_ASSERT(_document->is_object());
        auto* doc = m_instance.back();
        if (auto member = doc->find("InstanceOf"); member != doc->end())
        {
            if (auto const& prefabPath = member->get_ref<std::string const&>();
                not prefabPath.empty())
            {
                if (newLayer.prefabsStorage == nullptr)
                {
                    newLayer.prefabsStorage =
                        std::make_unique<Cursor>(m_entityLib, _schema, prefabPath.c_str());
                }
                else
                {
                    newLayer.prefabsStorage->init(m_entityLib, _schema, prefabPath.c_str());
                }
                newLayer.prefab = newLayer.prefabsStorage.get();
                ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
            }
        }
        newLayer.isDefault = false;
        _validNewLayer();
        checkInvariants();
    }

    void Cursor::init(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
    {
        init(_entityLib, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    Cursor::Cursor(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
    {
        init(_entityLib, _schema, _filename, &_entityLib->readJsonFile(_filename));
    }

    void Cursor::save(char const* _filename) const
    {
        m_instance.save(_filename);
    }

    bool Cursor::isDefaultImpl() const
    {
        auto& newLayer = _getLastLayer();
        if (m_instance.isSet())
        {
            return false;
        }
        if (newLayer.prefab != nullptr)
        {
            return newLayer.prefab->isDefaultImpl();
        }
        return true;
    }

    void Cursor::_pushDefault(Layer& newLayer) const
    {
        if (newLayer.isDefault)
        {
            newLayer.isDefault = true;
        }
        else
        {
            newLayer.isDefault = isDefaultImpl();
        }
    }

    bool Cursor::isDefault() const
    {
        return _getLastLayer().isDefault;
    }

    bool Cursor::_loadInstanceOf(Layer& newLayer)
    {
        auto* subschema = m_instance.getSchema();
        if (subschema->type == Ent::DataType::object and m_instance.isSet())
        {
            auto* doc = m_instance.back();
            if (auto member = doc->find("InstanceOf"); member != doc->end())
            {
                if (auto const& prefabPath = member->get_ref<std::string const&>();
                    not prefabPath.empty())
                {
                    if (newLayer.prefabsStorage == nullptr)
                    {
                        newLayer.prefabsStorage =
                            std::make_unique<Cursor>(m_entityLib, subschema, prefabPath.c_str());
                    }
                    else
                    {
                        newLayer.prefabsStorage->init(m_entityLib, subschema, prefabPath.c_str());
                    }
                    newLayer.prefab = newLayer.prefabsStorage.get();
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
                return true;
            }
        }
        return false;
    }

    Cursor& Cursor::enterObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        checkInvariants();
        ENTLIB_DBG_ASSERT(getDataType() == Ent::DataType::object);
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == Ent::DataType::object);
        m_instance.enterObjectField(_field, _fieldRef);
        auto* subschema = m_instance.getSchema();
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterObjectField(_field, _fieldRef);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        bool defaultFound = false;
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterObjectField(_field, _fieldRef);
            if (defaultVal->isSet())
            {
                defaultFound = true;
                newLayer.defaultVal = lastLayer.defaultVal - 1;
            }
            else
            {
                defaultVal->exit();
            }
        }
        if (not defaultFound)
        {
            auto propDefVal = m_instance.getPropertyDefaultValue();
            if (propDefVal != nullptr) // If there is property default, use them
            {
                newLayer.setDefault(subschema, nullptr, (nlohmann::json*)propDefVal);
            }
            else if (not subschema->defaultValue.is_null())
            {
                newLayer.setDefault(subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
            }
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    Cursor& Cursor::enterUnionData(char const* type)
    {
        checkInvariants();
        if (type == nullptr)
        {
            type = getUnionType();
        }
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        m_instance.enterUnionData(type);
        auto* subschema = m_instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterUnionData(type);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else // Une type default
        {
            newLayer.setDefault(subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
        }
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterUnionData(type);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    Cursor& Cursor::enterUnionSetItem(char const* _field, Subschema const* _dataSchema)
    {
        checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        m_instance.enterUnionSetItem(_field, _dataSchema);
        auto* subschema = m_instance.getSchema();
        ENTLIB_DBG_ASSERT(_dataSchema == nullptr or subschema == _dataSchema);
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterUnionSetItem(_field, subschema);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterUnionSetItem(_field, subschema);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else if (auto* propDefVal = m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, const_cast<nlohmann::json*>(propDefVal));
        }
        else // Une type default
        {
            newLayer.setDefault(
                subschema, nullptr, const_cast<nlohmann::json*>(&subschema->defaultValue));
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    Cursor& Cursor::enterObjectSetItem(char const* _field)
    {
        checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        m_instance.enterObjectSetItem(_field);
        auto* subschema = m_instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterObjectSetItem(_field);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else if (auto* propDefVal = m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, const_cast<nlohmann::json*>(propDefVal));
        }
        else // Une type default
        {
            newLayer.setDefault(
                subschema, nullptr, const_cast<nlohmann::json*>(&subschema->defaultValue));
        }
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterObjectSetItem(_field);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    Cursor& Cursor::enterObjectSetItem(int64_t _field)
    {
        checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        m_instance.enterObjectSetItem(_field);
        auto* subschema = m_instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterObjectSetItem(_field);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else if (auto* propDefVal = m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, const_cast<nlohmann::json*>(propDefVal));
        }
        else // Une type default
        {
            newLayer.setDefault(
                subschema, nullptr, const_cast<nlohmann::json*>(&subschema->defaultValue));
        }
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterObjectSetItem(_field);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    Cursor& Cursor::enterMapItem(char const* _field)
    {
        checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        m_instance.enterMapItem(_field);
        auto* subschema = m_instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterMapItem(_field);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else if (auto* propDefVal = m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, (nlohmann::json*)propDefVal);
        }
        else // Une type default
        {
            newLayer.setDefault(subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
        }
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterMapItem(_field);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    Cursor& Cursor::enterMapItem(int64_t _field)
    {
        checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        m_instance.enterMapItem(_field);
        auto* subschema = m_instance.getSchema();
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterMapItem(_field);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else if (auto* propDefVal = m_instance.getPropertyDefaultValue()) // If there is property default, use them
        {
            newLayer.setDefault(subschema, nullptr, (nlohmann::json*)propDefVal);
        }
        else // Une type default
        {
            newLayer.setDefault(subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
        }
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterMapItem(_field);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    void Cursor::_comitNewLayer(Layer& newLayer)
    {
        _pushDefault(newLayer);
        _validNewLayer();
        if (m_instance.getSchema()->type == Ent::DataType::array)
        {
            _getLastLayer().arraySize = arraySize();
        }
        checkInvariants();
    }

    Cursor& Cursor::enterArrayItem(size_t _index)
    {
        checkInvariants();
        Layer& newLayer = _allocLayer();
        auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(m_instance.getSchema()->type == Ent::DataType::array);
        m_instance.enterArrayItem(_index);
        auto* subschema = m_instance.getSchema();
        if (not isDefault())
        {
            if (not _loadInstanceOf(newLayer))
            {
                if (lastLayer.prefab != nullptr)
                {
                    lastLayer.prefab->enterArrayItem(_index);
                    newLayer.prefab = lastLayer.prefab;
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
        }
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->isSet()) // If there is default, enter in
        {
            defaultVal->enterArrayItem(_index);
            newLayer.defaultVal = lastLayer.defaultVal - 1;
        }
        else if (m_instance.getPropertyDefaultValue() != nullptr) // If there is property default, use them
        {
            newLayer.setDefault(
                subschema, nullptr, (nlohmann::json*)m_instance.getPropertyDefaultValue());
        }
        else // Une type default
        {
            newLayer.setDefault(subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
        }
        _comitNewLayer(newLayer);
        return *this;
    }

    char const* Cursor::getUnionType()
    {
        auto& lastLayer = _getLastLayer();
        if (char const* type = m_instance.getUnionType())
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

    void Cursor::checkInvariants() const
    {
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(m_layerCount != 0);
        ENTLIB_DBG_ASSERT(m_instance.lastLayer().schema.base != nullptr);
        //ENTLIB_DBG_ASSERT(
        //    (layers.empty() and m_instance.additionalPath.empty())
        //    or layers.size() == (m_instance.additionalPath.size() + 1));
        ENTLIB_DBG_ASSERT(m_layerCount == m_instance.layerCount());
        [[maybe_unused]] auto& lastLayer = _getLastLayer();
        ENTLIB_DBG_ASSERT(
            lastLayer.getDefault() == nullptr
            or lastLayer.getDefault()->getSchema()->type == m_instance.getSchema()->type);
        if (_getLastLayer().prefab != nullptr)
        {
            ENTLIB_DBG_ASSERT(_getLastLayer().prefab != (void*)0xdddddddddddddddd);
            _getLastLayer().prefab->checkInvariants();
        }
#endif
    }

    Cursor& Cursor::exit()
    {
#ifdef _DEBUG
        auto layersCount = m_layerCount;
        ENTLIB_DBG_ASSERT(m_layerCount > 0);
        auto& prevLayer = m_layers[m_layerCount - 2];
        auto& prevSchema = (m_instance.layerEnd() - 2)->schema;
#endif
        checkInvariants();
        auto& lastLayer = _getLastLayer();
        //ENTLIB_DBG_ASSERT(
        //    prevLayer.default == nullptr
        //    or prevLayer.default->schema.back().base->type == prevSchema.base->type);
        m_instance.exit();
        if (lastLayer.prefab != nullptr and not(lastLayer.prefab->m_layerCount < 2))
        {
            lastLayer.prefab->exit();
        }
        auto* defaultVal = lastLayer.getDefault();
        if (defaultVal != nullptr and defaultVal->layerCount() != 0)
        {
            defaultVal->exit();
        }
        --m_layerCount; // leuers.pop_back()
#ifdef _DEBUG
        ENTLIB_DBG_ASSERT(layersCount == m_layerCount + 1);
        ENTLIB_DBG_ASSERT(
            prevLayer.getDefault() == nullptr
            or prevLayer.getDefault()->getSchema()->type == prevSchema.base->type);
#endif
        checkInvariants();
        return *this;
    }

    DataType Cursor::getDataType() const
    {
        return m_instance.getSchema()->type;
    }

    Subschema const* Cursor::getSchema() const
    {
        return m_instance.getSchema();
    }

    DataType Cursor::getMapKeyType() const
    {
        return m_instance.getSchema()->singularItems->get().linearItems->at(0)->type;
    }

    size_t Cursor::arraySize()
    {
        auto& lastLayer = _getLastLayer();
        auto& jsonExplLayer = m_instance.lastLayer();
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
                return defaultVal->back()->size();
            }
            else
            {
                return schema->minItems;
            }
        }
    }

    size_t Cursor::size()
    {
        auto& jsonExplLayer = m_instance.lastLayer();
        auto* schema = jsonExplLayer.schema.base;
        if (schema->linearItems.has_value())
        {
            return schema->linearItems->size();
        }
        else
        {
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
                    auto& itemType = schema->singularItems.get()->get();
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
        }
        ENTLIB_LOGIC_ERROR("Unexpected DataType!");
    }

    bool Cursor::contains(Key const& _key)
    {
        auto& jsonExplLayer = m_instance.lastLayer();
        auto* schema = jsonExplLayer.schema.base;
        if (schema->linearItems.has_value())
        {
            return false; // Not a map/set
        }
        else
        {
            switch (schema->type)
            {
            case Ent::DataType::object:
                return schema->properties.count(std::get<std::string>(_key));
            case Ent::DataType::oneOf: return getUnionType() == std::get<std::string>(_key);
            case Ent::DataType::array:
            {
                auto meta = std::get<Ent::Subschema::ArrayMeta>(schema->meta);
                switch (hash(meta.overridePolicy))
                {
                case "map"_hash:
                    switch (getMapKeyType())
                    {
                    case Ent::DataType::string: return getMapContains(std::get<std::string>(_key).c_str());
                    case Ent::DataType::integer: return getMapContains(std::get<size_t>(_key));
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    break;
                case "set"_hash:
                {
                    auto& itemType = schema->singularItems.get()->get();
                    switch (itemType.type)
                    {
                    case Ent::DataType::integer: return getPrimSetContains(std::get<size_t>(_key));
                    case Ent::DataType::string:
                        return getPrimSetContains(std::get<std::string>(_key).c_str());
                    case Ent::DataType::oneOf:
                        return getUnionSetContains(std::get<std::string>(_key).c_str());
                    case Ent::DataType::object:
                        auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                        switch (keyFieldSchema.type)
                        {
                        case Ent::DataType::string:
                            return getObjectSetContains(std::get<std::string>(_key).c_str());
                        case Ent::DataType::integer:
                            return getObjectSetContains(std::get<size_t>(_key));
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
            auto* node = defaultVal->back();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (auto const& k_v : *node)
            {
                ENTLIB_DBG_ASSERT(node->is_array());
                auto& key = k_v[0llu].get_ref<std::string const&>();
                ENTLIB_DBG_ASSERT(node->is_array());
                keys.insert(key.c_str());
                ENTLIB_DBG_ASSERT(node->is_array());
            }
        }
        if (m_instance.isSet())
        {
            auto* node = m_instance.back();
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
        if (m_instance.isSetInternal())
        {
            return m_instance.isNull();
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
        if (m_instance.isSet())
        {
            auto const arraySize = m_instance.back()->size();
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
        if (m_instance.isSet())
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
        if (m_instance.isSet())
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
            ENTLIB_ASSERT(lastLayer.prefab != (void*)0xdddddddddddddddd);
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
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
#ifdef _DEBUG
                auto* instanceSize = m_instance.back();
#endif
                auto [unionSchema, unionValue] = m_instance.enterArrayItem(i).getUnionData();
                bool const isNull = unionValue != nullptr ? unionValue->is_null() : false;
                // bool const isNull = m_instance.enterArrayItem(i).enterUnionData().isNull();
                // Subschema const* unionSchema = m_instance.getSchema();
                // m_instance.exit();
                if (isNull)
                {
                    keys.erase(m_instance.getUnionType());
                }
                else
                {
                    keys.emplace(m_instance.getUnionType(), unionSchema);
                }
                m_instance.exit();
                ENTLIB_DBG_ASSERT(instanceSize == m_instance.back());
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
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                enterArrayItem(i);
                if (m_instance.isSet() and m_instance.back()->count("__removed__") != 0)
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
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                enterArrayItem(i);
                if (m_instance.isSet() and m_instance.back()->count("__removed__") != 0)
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

    bool Cursor::getMapContains(char const* _key)
    {
        return getMapKeysString().count(_key);
    }
    bool Cursor::getMapContains(int64_t _key)
    {
        return getMapKeysInt().count(_key);
    }
    bool Cursor::getPrimSetContains(char const* _key)
    {
        return getPrimSetKeysString().count(_key) != 0;
    }
    bool Cursor::getPrimSetContains(int64_t _key)
    {
        return getPrimSetKeysInt().count(_key) != 0;
    }
    bool Cursor::getUnionSetContains(char const* _key)
    {
        return getUnionSetKeysString().count(_key) != 0;
    }
    bool Cursor::getObjectSetContains(char const* _key)
    {
        return getObjectSetKeysString().count(_key) != 0;
    }
    bool Cursor::getObjectSetContains(int64_t _key)
    {
        return getObjectSetKeysInt().count(_key) != 0;
    }


    void Cursor::_buildPath()
    {
        auto firstNotSet = std::find_if(
            m_instance.layerBegin(), m_instance.layerEnd(), [](FileCursor::Layer const& l) {
                return l.values == nullptr;
            });
        ENTLIB_ASSERT(firstNotSet != m_instance.layerBegin());
        auto firstNotSetIdx = std::distance(m_instance.layerBegin(), firstNotSet);
        auto lastSet = firstNotSet;
        --lastSet;
        auto endIter = m_instance.layerEnd();
        for (; firstNotSet != endIter; ++lastSet, ++firstNotSet, ++firstNotSetIdx)
        {
            size_t arraySize = m_layers[firstNotSetIdx - 1].arraySize;
            FileCursor::setLayer(*lastSet, *firstNotSet, arraySize);
            ENTLIB_ASSERT(firstNotSet->values != nullptr);
        }
        // ENTLIB_ASSERT(m_instance.back() != nullptr);
    }
    void Cursor::setSize(size_t size)
    {
        _buildPath();
        m_instance.setSize(size);
    }

    void Cursor::setFloat(double value)
    {
        _buildPath();
        m_instance.setFloat(value);
    }
    void Cursor::setInt(int64_t value)
    {
        _buildPath();
        m_instance.setInt(value);
    }
    void Cursor::setString(char const* value)
    {
        ENTLIB_ASSERT(value != nullptr);
        _buildPath();
        m_instance.setString(value);
    }
    void Cursor::setBool(bool value)
    {
        _buildPath();
        m_instance.setBool(value);
    }
    void Cursor::setEntityRef(EntityRef const& value)
    {
        _buildPath();
        m_instance.setEntityRef(value);
    }
    void Cursor::setUnionType(char const* type)
    {
        _buildPath();
        m_instance.setUnionType(type);
    }
    bool Cursor::countPrimSetKey(char const* key)
    {
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                bool const equal = strcmp(enterArrayItem(i).getString(), key) == 0;
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
            return lastLayer.prefab->countPrimSetKey(key);
        }
        return false;
    }
    bool Cursor::countPrimSetKey(int64_t key)
    {
        if (m_instance.isSet())
        {
            for (size_t i = 0; i < arraySize(); ++i)
            {
                bool const equal = enterArrayItem(i).getInt() == key;
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
            return lastLayer.prefab->countPrimSetKey(key);
        }
        return false;
    }
    void Cursor::insertPrimSetKey(char const* key)
    {
        if (not countPrimSetKey(key))
        {
            _buildPath();
            m_instance.pushBack(key);
        }
    }
    void Cursor::insertPrimSetKey(int64_t key)
    {
        if (not countPrimSetKey(key))
        {
            _buildPath();
            m_instance.pushBack(key);
        }
    }
} // namespace Ent
