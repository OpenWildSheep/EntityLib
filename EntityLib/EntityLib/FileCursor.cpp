#include "include/EntityLib/FileCursor.h"

namespace Ent
{
    FileCursor::FileCursor() = default;

    FileCursor::FileCursor(Ent::Subschema const* _schema, char const* _filePath, nlohmann::json* _document)
    {
        m_filePath = _filePath;
        m_layers.reserve(30);
        auto& newLayer = m_layers.emplace_back();
        newLayer.schema = Schema{{_schema}};
        newLayer.values = _document;
    }

    void FileCursor::init(Ent::Subschema const* _schema, char const* _filePath, nlohmann::json* _document)
    {
        if (_filePath == nullptr)
        {
            m_filePath.clear();
        }
        else
        {
            m_filePath = _filePath;
        }
        m_rootDoc = nullptr;
        m_layers.clear();
        auto& newLayer = m_layers.emplace_back();
        newLayer.schema = Schema{{_schema}};
        newLayer.values = _document;
    }

    FileCursor::Layer* FileCursor::layerBegin()
    {
        return &m_layers.front();
    }

    FileCursor::Layer* FileCursor::layerEnd()
    {
        return (&m_layers.back()) + 1;
    }

    FileCursor::Layer const* FileCursor::layerBegin() const
    {
        return &m_layers.front();
    }

    FileCursor::Layer const* FileCursor::layerEnd() const
    {
        return (&m_layers.back()) + 1;
    }

    FileCursor::Layer& FileCursor::lastLayer()
    {
        return m_layers.back();
    }

    FileCursor::Layer const& FileCursor::lastLayer() const
    {
        return m_layers.back();
    }

    size_t FileCursor::layerCount() const
    {
        return m_layers.size();
    }

    void FileCursor::reset()
    {
        m_filePath.clear();
        m_rootDoc = nullptr;
        m_layers.clear();
    }

    FileCursor::FileCursor(Ent::Subschema const* _schema, char const* _filePath)
        : FileCursor(_schema, _filePath, &_schema->rootSchema->entityLib->readJsonFile(_filePath))
    {
    }

    void FileCursor::pushBack(char const* _key)
    {
        _getRawJson()->push_back(_key);
    }

    void FileCursor::pushBack(int64_t _key)
    {
        _getRawJson()->push_back(_key);
    }

    void FileCursor::save(char const* _filename) const
    {
        m_layers.front().schema.base->rootSchema->entityLib->saveJsonFile(
            m_layers.front().values, _filename != nullptr ? _filename : m_filePath.c_str());
    }

    nlohmann::json* FileCursor::_getRawJson()
    {
        return isSet() ? m_layers.back().values : nullptr;
    }

    nlohmann::json const* FileCursor::getRawJson() const
    {
        return isSet() ? m_layers.back().values : nullptr;
    }

    bool FileCursor::isSetOrNull() const
    {
        return m_layers.back().values != nullptr;
    }

    bool FileCursor::isSet() const
    {
        auto* val = m_layers.back().values;
        return val != nullptr and not val->is_null();
    }

    bool FileCursor::isNull() const
    {
        auto* val = m_layers.back().values;
        return val != nullptr and val->is_null();
    }

    FileCursor& FileCursor::enterObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        bool const nodeIsSet = isSet();
        Layer& newLayer = m_layers.emplace_back();
        auto& lastLayer = *(m_layers.end() - 2);
        ENTLIB_DBG_ASSERT(lastLayer.schema.base->type == Ent::DataType::object);
        if (_fieldRef == nullptr)
        {
            auto& properties = lastLayer.schema.base->properties;
            if (auto propIter = properties.find(_field); propIter != properties.end())
            {
                _field = propIter->first.c_str(); // Convert _field to static string
                _fieldRef = &propIter->second;
            }
            else
            {
                throw Ent::BadKey(_field, __func__, lastLayer.schema.base->name.c_str());
            }
        }
        newLayer.additionalPath = _field;
        Subschema const* subschema = &(_fieldRef->get());
        newLayer.schema = Schema{subschema, _fieldRef->getRefDefaultValues()};
        if (nodeIsSet)
        {
            auto lastNode = lastLayer.values;
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            if (auto memiter = lastNode->find(_field); memiter != lastNode->end())
            {
                auto newValue = &(*memiter);
                if (newLayer.schema.base->type == Ent::DataType::string
                    or newLayer.schema.base->type == Ent::DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(newValue->is_string());
                }

                newLayer.values = newValue;
            }
        }
        ENTLIB_DBG_ASSERT(lastLayer.schema.base != nullptr);
        return *this;
    }

    FileCursor& FileCursor::enterUnionSetItem(char const* _field, Subschema const* _dataSchema)
    {
        Layer newLayer;
        auto& lastLayer = m_layers.back();
        auto& unionSchema = lastLayer.schema.base->singularItems->get();
        if (_dataSchema == nullptr)
        {
            if (auto iter = unionSchema.unionTypeMap.find(_field);
                iter != unionSchema.unionTypeMap.end())
            {
                newLayer.schema = Schema{iter->second.dataSchema, nullptr};
                _field = iter->first.c_str(); // Convert _field to a long living memory
            }
            else
            {
                throw ContextException("Unknown Union type : %s", _field);
            }
        }
        else
        {
            newLayer.schema = Schema{_dataSchema, nullptr};
        }
        newLayer.additionalPath = _field;

        if (isSet())
        {
            auto typeField = unionSchema.getUnionNameField();
            auto dataField = unionSchema.getUnionDataField();
            auto lastNode = lastLayer.values;
            for (auto& item : *lastNode)
            {
                if (auto typeIter = item.find(typeField); typeIter != item.end())
                {
                    if (typeIter->get_ref<std::string const&>() == _field)
                    {
                        nlohmann::json* newValue = nullptr;
                        if (auto dataIter = item.find(dataField); dataIter != item.end())
                        {
                            newValue = &(*dataIter);
                        }
                        if (newLayer.schema.base->type == Ent::DataType::string
                            or newLayer.schema.base->type == Ent::DataType::entityRef)
                        {
                            ENTLIB_DBG_ASSERT(newValue == nullptr or newValue->is_string());
                        }

                        // Item found!
                        newLayer.values = newValue;
                        break;
                    }
                }
            }
        }
        ENTLIB_ASSERT(newLayer.schema.base != nullptr);
        m_layers.push_back(newLayer);
        return *this;
    }

    template <typename K, typename C>
    FileCursor& FileCursor::_enterObjectSetItemImpl(K _field, C&& _equalKey)
    {
        Layer newLayer;
        auto& lastLayer = m_layers.back();
        auto& objectSchema = lastLayer.schema.base->singularItems->get();
        auto keyFieldName =
            std::get<Subschema::ArrayMeta>(lastLayer.schema.base->meta).keyField->c_str();
        newLayer.schema = Schema{&objectSchema, nullptr};
        newLayer.additionalPath = _field;

        if (isSet())
        {
            auto lastNode = lastLayer.values;
            for (auto& item : *lastNode)
            {
                if (auto typeIter = item.find(keyFieldName); typeIter != item.end())
                {
                    if (_equalKey(*typeIter, _field))
                    {
                        auto newValue = &item;
                        if (newLayer.schema.base->type == Ent::DataType::string
                            or newLayer.schema.base->type == Ent::DataType::entityRef)
                        {
                            ENTLIB_DBG_ASSERT(newValue->is_string());
                        }

                        // Item found!
                        newLayer.values = newValue;
                        break;
                    }
                }
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.schema.base != nullptr);
        m_layers.push_back(newLayer);
        return *this;
    }

    FileCursor& FileCursor::enterObjectSetItem(char const* _field)
    {
        return _enterObjectSetItemImpl(
            _field,
            [](nlohmann::json const& _node, char const* _key)
            { return _node.get_ref<std::string const&>() == _key; });
    }

    FileCursor& FileCursor::enterObjectSetItem(int64_t _field)
    {
        return _enterObjectSetItemImpl(
            _field,
            [](nlohmann::json const& _node, int64_t _key) { return _node.get<int64_t>() == _key; });
    }

    template <typename K, typename E>
    FileCursor& FileCursor::_enterMapItemImpl(K _field, E&& _isEqual)
    {
        Layer newLayer;
        auto& lastLayer = m_layers.back();

        auto& pairSchema = lastLayer.schema.base->singularItems->get();
        newLayer.schema = Schema{&pairSchema.linearItems->at(1).get(), nullptr};
        newLayer.additionalPath = _field;

        if (isSet())
        {
            auto lastNode = lastLayer.values;
            for (auto& item : *lastNode)
            {
                auto& key = item[0];
                if (_isEqual(key, _field))
                {
                    auto newValue = &item[1];
                    if (lastLayer.schema.base->type == Ent::DataType::string
                        or lastLayer.schema.base->type == Ent::DataType::entityRef)
                    {
                        ENTLIB_DBG_ASSERT(newValue->is_string());
                    }

                    // Item found!
                    newLayer.values = newValue;
                    break;
                }
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.schema.base != nullptr);
        m_layers.push_back(newLayer);
        return *this;
    }

    FileCursor& FileCursor::enterMapItem(char const* _field)
    {
        return _enterMapItemImpl(
            _field,
            [](nlohmann::json const& _node, char const* _field)
            { return _node.get_ref<std::string const&>() == _field; });
    }

    FileCursor& FileCursor::enterMapItem(int64_t _field)
    {
        return _enterMapItemImpl(
            _field,
            [](nlohmann::json const& _node, int64_t _field)
            { return _node.get<int64_t>() == _field; });
    }

    FileCursor& FileCursor::enterArrayItem(size_t _index)
    {
        Layer newLayer;
        auto& lastLayer = m_layers.back();
        ENTLIB_DBG_ASSERT(lastLayer.schema.base->type == Ent::DataType::array);
        if (auto item = lastLayer.schema.base->singularItems.get())
        {
            auto& subschema = item->get();
            newLayer.schema = Schema{&subschema, nullptr};
        }
        else
        {
            ENTLIB_DBG_ASSERT(lastLayer.schema.base->linearItems.has_value());
            if (_index >= lastLayer.schema.base->linearItems->size())
            {
                throw ContextException("Out of range in tuple");
            }
            auto& subschema = lastLayer.schema.base->linearItems->at(_index).get();
            newLayer.schema = Schema{&subschema, nullptr};
        }
        newLayer.additionalPath = _index;
        if (auto lastNode = _getRawJson())
        {
            if (lastNode->size() > _index)
            {
                auto newValue = &(*lastNode)[_index];
                if (newLayer.schema.base->type == Ent::DataType::string
                    or newLayer.schema.base->type == Ent::DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(newValue->is_string() or newValue->is_null());
                }
                newLayer.values = newValue;
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.schema.base != nullptr);
        m_layers.push_back(newLayer);
        return *this;
    }

    char const* FileCursor::getUnionType() const
    {
        auto& lastLayer = m_layers.back();
        if (isSet())
        {
            auto typeField = lastLayer.schema.base->getUnionNameField();
            auto lastNode = lastLayer.values;
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            if (auto memiter = lastNode->find(typeField); memiter != lastNode->end())
            {
                return memiter->get_ref<std::string const&>().c_str();
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

    Ent::Subschema const* FileCursor::getUnionSchema() const
    {
        char const* unionType = getUnionType();
        auto& lastLayer = m_layers.back();
        try
        {
            return lastLayer.schema.base->getUnionType(unionType);
        }
        catch (BadUnionType&) // This unionType doesn't exist
        {
            return nullptr;
        }
    }

    bool FileCursor::isUnionRemoved() const
    {
        auto& lastLayer = m_layers.back();
        auto unionSchema = lastLayer.schema.base;
        if (isSet())
        {
            auto lastNode = lastLayer.values;
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            auto dataField = unionSchema->getUnionDataField();
            if (auto memiter = lastNode->find(dataField); memiter != lastNode->end())
            {
                auto unionValue = &(*memiter);
                if (unionSchema->type == Ent::DataType::string
                    or unionSchema->type == Ent::DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(unionValue->is_string());
                }
                return unionValue->is_null();
            }
        }
        return false;
    }

    FileCursor& FileCursor::enterUnionData(char const* _unionType)
    {
        if (_unionType == nullptr)
        {
            _unionType = getUnionType();
        }
        Layer newLayer;
        auto& lastLayer = m_layers.back();
        auto dataSchema = lastLayer.schema.base->getUnionType(_unionType);
        auto unionSchema = lastLayer.schema.base;
        newLayer.additionalPath = _unionType;
        if (isSet())
        {
            auto unionType = getUnionType();
            if (unionType != nullptr and strcmp(_unionType, unionType) == 0)
            {
                auto lastNode = lastLayer.values;
                ENTLIB_DBG_ASSERT(lastNode->is_object());
                auto dataField = unionSchema->getUnionDataField();
                if (auto memiter = lastNode->find(dataField); memiter != lastNode->end())
                {
                    auto newValue = &(*memiter);
                    if (unionSchema->type == Ent::DataType::string
                        or unionSchema->type == Ent::DataType::entityRef)
                    {
                        ENTLIB_DBG_ASSERT(newValue->is_string());
                    }
                    newLayer.values = newValue;
                }
            }
        }
        newLayer.schema = Schema{dataSchema, nullptr};
        m_layers.push_back(newLayer);
        return *this;
    }

    FileCursor& FileCursor::exit()
    {
        m_layers.pop_back();
        return *this;
    }

    Subschema const* FileCursor::getSchema() const
    {
        return m_layers.back().schema.base;
    }

    nlohmann::json const* FileCursor::getPropertyDefaultValue() const
    {
        return m_layers.back().schema.propDefVal;
    }

    nlohmann::json* FileCursor::createChildNode(
        Layer& _lastLayer,
        Ent::FileCursor::Key const& _childName,
        Ent::Subschema const& _newLayerSchema,
        size_t _arraySize)
    {
        ENTLIB_DBG_ASSERT(int(_lastLayer.values->type()) < int(nlohmann::json::value_t::discarded));
        nlohmann::json* newLayerJson = nullptr;
        switch (_lastLayer.schema.base->type)
        {
        case Ent::DataType::object:
        {
            if (_lastLayer.values->is_null())
            {
                (*_lastLayer.values) = nlohmann::json::object();
            }
            auto fieldName = std::get<char const*>(_childName);
            (*_lastLayer.values)[fieldName] = {};
            newLayerJson = &(*_lastLayer.values)[fieldName];
        }
        break;
        case Ent::DataType::oneOf:
        {
            if (_lastLayer.values->is_null())
            {
                (*_lastLayer.values) = nlohmann::json::object();
            }
            auto fieldName = std::get<char const*>(_childName);
            auto typeField = _lastLayer.schema.base->getUnionNameField();
            auto dataField = _lastLayer.schema.base->getUnionDataField();
            (*_lastLayer.values)[typeField] = fieldName;
            (*_lastLayer.values)[dataField] = {};
            newLayerJson = &(*_lastLayer.values)[dataField];
        }
        break;
        case Ent::DataType::array:
        {
            ENTLIB_DBG_ASSERT(_lastLayer.values->type() == nlohmann::json::value_t::array);
            auto meta = std::get<Ent::Subschema::ArrayMeta>(_lastLayer.schema.base->meta);
            auto& itemType = _lastLayer.schema.base->singularItems->get();
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                if (_lastLayer.values->is_null())
                {
                    (*_lastLayer.values) = nlohmann::json::array();
                }
                switch (itemType.linearItems->at(0)->type)
                {
                case Ent::DataType::string:
                {
                    auto key = std::get<char const*>(_childName);
                    auto pairNode = nlohmann::json::array();
                    pairNode.push_back(key);
                    pairNode.emplace_back();
                    _lastLayer.values->push_back(std::move(pairNode));
                    newLayerJson = &(*_lastLayer.values)[(*_lastLayer.values).size() - 1][1];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case Ent::DataType::integer:
                {
                    auto key = std::get<size_t>(_childName);
                    auto pairNode = nlohmann::json::array();
                    pairNode.push_back(key);
                    pairNode.emplace_back();
                    _lastLayer.values->push_back(std::move(pairNode));
                    newLayerJson = &(*_lastLayer.values)[(*_lastLayer.values).size() - 1][1];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            case "set"_hash:
            {
                if (_lastLayer.values->is_null())
                {
                    (*_lastLayer.values) = nlohmann::json::array();
                }
                switch (itemType.type)
                {
                case Ent::DataType::integer: // integer set
                {
                    auto key = std::get<size_t>(_childName);
                    _lastLayer.values->push_back(key);
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case Ent::DataType::string: // String set
                {
                    auto key = std::get<char const*>(_childName);
                    _lastLayer.values->push_back(key);
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case Ent::DataType::oneOf: // UnionSet
                {
                    auto wrapper = nlohmann::json::object();
                    auto fieldName = std::get<char const*>(_childName);
                    auto unionSchema = &_lastLayer.schema.base->singularItems->get();
                    auto typeField = unionSchema->getUnionNameField();
                    auto dataField = unionSchema->getUnionDataField();
                    wrapper[typeField] = fieldName;
                    wrapper[dataField] = {};
                    _lastLayer.values->push_back(std::move(wrapper));
                    newLayerJson = &(*_lastLayer.values)[(*_lastLayer.values).size() - 1][dataField];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case Ent::DataType::object: // Object Set
                    auto object = nlohmann::json::object();
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case Ent::DataType::string:
                    {
                        auto key = std::get<char const*>(_childName);
                        object[*meta.keyField] = key;
                        break;
                    }
                    case Ent::DataType::integer:
                    {
                        auto key = std::get<size_t>(_childName);
                        object[*meta.keyField] = key;
                        break;
                    }
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    ENTLIB_DBG_ASSERT(_lastLayer.values->type() == nlohmann::json::value_t::array);
                    _lastLayer.values->push_back(object);
                    newLayerJson = &(*_lastLayer.values)[(*_lastLayer.values).size() - 1];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                break;
            }
            case ""_hash:
            {
                if (_lastLayer.values->is_null())
                {
                    (*_lastLayer.values) = nlohmann::json::array();
                }
                while (_lastLayer.values->size() < _arraySize)
                {
                    _lastLayer.values->emplace_back();
                }
                while (_lastLayer.values->size() > _arraySize)
                {
                    _lastLayer.values->erase(_lastLayer.values->size() - 1);
                }
                auto index = std::get<size_t>(_childName);
                newLayerJson = &(*_lastLayer.values)[index];
                ENTLIB_ASSERT(newLayerJson != nullptr);
                break;
            }
            }
        }
        break;
        case Ent::DataType::null: [[fallthrough]];
        case Ent::DataType::string: [[fallthrough]];
        case Ent::DataType::number: [[fallthrough]];
        case Ent::DataType::integer: [[fallthrough]];
        case Ent::DataType::boolean: [[fallthrough]];
        case Ent::DataType::entityRef: [[fallthrough]];
        case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Unexpected DataType");
        }
        ENTLIB_ASSERT(newLayerJson != nullptr);
        if (newLayerJson->is_null())
        {
            if (_newLayerSchema.type == Ent::DataType::array)
            {
                *newLayerJson = nlohmann::json::array();
            }
            else if (_newLayerSchema.type == Ent::DataType::object)
            {
                *newLayerJson = nlohmann::json::object();
            }
        }
        return newLayerJson;
    }

    void FileCursor::setSize(size_t _size)
    {
        if (lastLayer().values->is_null())
        {
            (*lastLayer().values) = nlohmann::json::array();
        }
        while (_size > lastLayer().values->size())
        {
            lastLayer().values->emplace_back();
        }
        while (_size < lastLayer().values->size())
        {
            lastLayer().values->erase(lastLayer().values->size() - 1);
        }
    }
    template <typename T>
    void FileCursor::set(T&& _value)
    {
        if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, EntityRef>)
        {
            *lastLayer().values = _value.entityPath;
        }
        else
        {
            *lastLayer().values = std::forward<T>(_value);
        }
    }

    void FileCursor::setFloat(double _value)
    {
        set(_value);
    }
    void FileCursor::setInt(int64_t _value)
    {
        set(_value);
    }
    void FileCursor::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        set(_value);
    }
    void FileCursor::setBool(bool _value)
    {
        set(_value);
    }
    void FileCursor::setEntityRef(EntityRef const& _value)
    {
        set(_value);
    }
    void FileCursor::setUnionType(char const* type)
    {
        auto& wrapper = (*lastLayer().values);
        auto dataFieldName = getSchema()->getUnionDataField();
        auto nameFieldName = getSchema()->getUnionNameField();
        wrapper[nameFieldName] = type;
        wrapper[dataFieldName] = nlohmann::json();
    }

    template <typename T>
    T FileCursor::get() const
    {
        if constexpr (std::is_same_v<T, const char*>)
        {
            return getRawJson()->get_ref<std::string const&>().c_str();
        }
        else if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, EntityRef>)
        {
            return EntityRef{getString()};
        }
        else
        {
            return getRawJson()->get<T>();
        }
    }

    double FileCursor::getFloat() const
    {
        return get<double>();
    }
    int64_t FileCursor::getInt() const
    {
        return get<int64_t>();
    }
    char const* FileCursor::getString() const
    {
        return get<char const*>();
    }
    bool FileCursor::getBool() const
    {
        return get<bool>();
    }
    EntityRef FileCursor::getEntityRef() const
    {
        return get<EntityRef>();
    }
} // namespace Ent
