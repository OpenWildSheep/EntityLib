#include "include/EntityLib/FileProperty.h"

#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{
    FileProperty::FileProperty() = default;

    FileProperty::FileProperty(Subschema const* _schema, char const* _filePath, json* _document)
    {
        if (_filePath != nullptr)
        {
            m_filePath = _filePath;
        }
        m_schema = Schema{{_schema}};
        m_values = _document;
    }

    FileProperty::FileProperty(Subschema const* _schema, char const* _filePath)
        : FileProperty(_schema, _filePath, &_schema->rootSchema->entityLib->readJsonFile(_filePath))
    {
    }

    void FileProperty::pushBack(char const* _key)
    {
        _getRawJson()->push_back(_key);
    }

    void FileProperty::pushBack(int64_t _key)
    {
        _getRawJson()->push_back(_key);
    }

    void FileProperty::save(char const* _filename) const
    {
        m_schema.base->rootSchema->entityLib->saveJsonFile(
            m_values, _filename != nullptr ? _filename : m_filePath.c_str());
    }

    json* FileProperty::_getRawJson()
    {
        return isSet() ? m_values : nullptr;
    }

    json const* FileProperty::getRawJson() const
    {
        return isSet() ? m_values : nullptr;
    }

    void FileProperty::setRawJson(json* _jsonNode)
    {
        m_values = _jsonNode;
    }

    bool FileProperty::isSetOrNull() const
    {
        return m_values != nullptr;
    }

    bool FileProperty::isSet() const
    {
        auto* val = m_values;
        return val != nullptr and not val->is_null();
    }

    bool FileProperty::isNull() const
    {
        auto* val = m_values;
        return val != nullptr and val->is_null();
    }

    FileProperty FileProperty::getObjectField(char const* _field, SubschemaRef const* _fieldRef)
    {
        bool const nodeIsSet = isSet();
        FileProperty newLayer;
        ENTLIB_DBG_ASSERT(m_schema.base->type == DataType::object);
        if (_fieldRef == nullptr)
        {
            auto& properties = m_schema.base->properties;
            if (auto propIter = properties.find(_field); propIter != properties.end())
            {
                _field = propIter->first.c_str(); // Convert _field to static string
                _fieldRef = &propIter->second;
            }
            else
            {
                throw BadKey(_field, __func__, m_schema.base->name.c_str());
            }
        }
        newLayer.m_key = _field;
        Subschema const* subschema = &(_fieldRef->get());
        newLayer.m_schema = Schema{subschema, _fieldRef->getRefDefaultValues()};
        if (nodeIsSet)
        {
            auto lastNode = m_values;
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            if (auto memiter = lastNode->find(_field); memiter != lastNode->end())
            {
                auto newValue = &(*memiter);
                if (newLayer.m_schema.base->type == DataType::string
                    or newLayer.m_schema.base->type == DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(newValue->is_string());
                }

                newLayer.m_values = newValue;
            }
        }
        ENTLIB_DBG_ASSERT(m_schema.base != nullptr);
        return newLayer;
    }

    FileProperty FileProperty::getUnionSetItem(char const* _field, Subschema const* _dataSchema)
    {
        FileProperty newLayer;
        auto& lastschema = *m_schema.base;
        if (lastschema.singularItems == nullptr)
        {
            throw BadArrayType(staticFormat(
                "In Property::enterUnionSetItem, expected UnionSet. Got %s.",
                lastschema.name.c_str()));
        }
        auto& unionSchema = lastschema.singularItems->get();
        if (_dataSchema == nullptr)
        {
            if (auto iter = unionSchema.unionTypeMap.find(_field);
                iter != unionSchema.unionTypeMap.end())
            {
                newLayer.m_schema = Schema{iter->second.dataSchema, nullptr};
                _field = iter->first.c_str(); // Convert _field to a long living memory
            }
            else
            {
                throw ContextException("Unknown Union type : %s", _field);
            }
        }
        else
        {
            newLayer.m_schema = Schema{_dataSchema, nullptr};
        }
        newLayer.m_key = _field;

        if (isSet())
        {
            auto typeField = unionSchema.getUnionNameField();
            auto dataField = unionSchema.getUnionDataField();
            auto lastNode = m_values;
            for (auto& item : *lastNode)
            {
                if (auto typeIter = item.find(typeField); typeIter != item.end())
                {
                    if (typeIter->get_ref<std::string const&>() == _field)
                    {
                        json* newValue = nullptr;
                        if (auto dataIter = item.find(dataField); dataIter != item.end())
                        {
                            newValue = &(*dataIter);
                        }
                        if (newLayer.m_schema.base->type == DataType::string
                            or newLayer.m_schema.base->type == DataType::entityRef)
                        {
                            ENTLIB_DBG_ASSERT(newValue == nullptr or newValue->is_string());
                        }

                        // Item found!
                        newLayer.m_values = newValue;
                        break;
                    }
                }
            }
        }
        ENTLIB_ASSERT(newLayer.m_schema.base != nullptr);
        return newLayer;
    }

    template <typename K, typename C>
    FileProperty FileProperty::_enterObjectSetItemImpl(K _field, C&& _equalKey)
    {
        FileProperty newLayer;
        auto& setSchema = *m_schema.base;
        auto& objectSchema = setSchema.singularItems->get();
        char const* keyFieldName = nullptr;
        if (auto meta = std::get_if<Subschema::ArrayMeta>(&setSchema.meta))
        {
            if (meta->keyField.has_value())
            {
                keyFieldName = meta->keyField->c_str();
            }
        }
        if (keyFieldName == nullptr)
        {
            throw BadArrayType(staticFormat(
                "In Property::enterObjectSet. Expected an ObjectSet. Got %s", setSchema.name.c_str()));
        }

        newLayer.m_schema = Schema{&objectSchema, nullptr};
        newLayer.m_key = _field;

        if (isSet())
        {
            auto lastNode = m_values;
            for (auto& item : *lastNode)
            {
                if (auto typeIter = item.find(keyFieldName); typeIter != item.end())
                {
                    if (_equalKey(*typeIter, _field))
                    {
                        auto newValue = &item;
                        if (newLayer.m_schema.base->type == DataType::string
                            or newLayer.m_schema.base->type == DataType::entityRef)
                        {
                            ENTLIB_DBG_ASSERT(newValue->is_string());
                        }

                        // Item found!
                        newLayer.m_values = newValue;
                        break;
                    }
                }
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.m_schema.base != nullptr);
        return newLayer;
    }

    FileProperty FileProperty::getObjectSetItem(char const* _field)
    {
        return _enterObjectSetItemImpl(
            _field,
            [](json const& _node, char const* _key)
            { return _node.get_ref<std::string const&>() == _key; });
    }

    FileProperty FileProperty::getObjectSetItem(int64_t _field)
    {
        return _enterObjectSetItemImpl(
            _field, [](json const& _node, int64_t _key) { return _node.get<int64_t>() == _key; });
    }

    template <typename K, typename E>
    FileProperty FileProperty::_enterMapItemImpl(K _field, E&& _isEqual)
    {
        FileProperty newLayer;

        auto& pairSchema = m_schema.base->singularItems->get();
        newLayer.m_schema = Schema{&pairSchema.linearItems->at(1).get(), nullptr};
        newLayer.m_key = _field;

        if (isSet())
        {
            auto lastNode = m_values;
            for (auto& item : *lastNode)
            {
                auto& key = item[0];
                if (_isEqual(key, _field))
                {
                    auto newValue = &item[1];
                    if (m_schema.base->type == DataType::string
                        or m_schema.base->type == DataType::entityRef)
                    {
                        ENTLIB_DBG_ASSERT(newValue->is_string());
                    }

                    // Item found!
                    newLayer.m_values = newValue;
                    break;
                }
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.m_schema.base != nullptr);
        return newLayer;
    }

    FileProperty FileProperty::getMapItem(char const* _field)
    {
        return _enterMapItemImpl(
            _field,
            [](json const& _node, char const* _field)
            { return _node.get_ref<std::string const&>() == _field; });
    }

    FileProperty FileProperty::getMapItem(int64_t _field)
    {
        return _enterMapItemImpl(
            _field, [](json const& _node, int64_t _field) { return _node.get<int64_t>() == _field; });
    }

    FileProperty FileProperty::getArrayItem(size_t _index)
    {
        FileProperty newLayer;
        ENTLIB_DBG_ASSERT(m_schema.base->type == DataType::array);
        if (auto item = m_schema.base->singularItems.get())
        {
            auto& subschema = item->get();
            newLayer.m_schema = Schema{&subschema, nullptr};
        }
        else
        {
            ENTLIB_DBG_ASSERT(m_schema.base->linearItems.has_value());
            if (_index >= m_schema.base->linearItems->size())
            {
                throw ContextException("Out of range in tuple");
            }
            auto& subschema = m_schema.base->linearItems->at(_index).get();
            newLayer.m_schema = Schema{&subschema, nullptr};
        }
        newLayer.m_key = _index;
        if (auto lastNode = _getRawJson())
        {
            if (lastNode->size() > _index)
            {
                auto newValue = &(*lastNode)[_index];
                if (newLayer.m_schema.base->type == DataType::string
                    or newLayer.m_schema.base->type == DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(newValue->is_string() or newValue->is_null());
                }
                newLayer.m_values = newValue;
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.m_schema.base != nullptr);
        return newLayer;
    }

    char const* FileProperty::getUnionType() const
    {
        if (isSet())
        {
            auto typeField = m_schema.base->getUnionNameField();
            auto lastNode = m_values;
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

    Subschema const* FileProperty::getUnionSchema() const
    {
        char const* unionType = getUnionType();
        try
        {
            return m_schema.base->getUnionType(unionType);
        }
        catch (BadUnionType&) // This unionType doesn't exist
        {
            return nullptr;
        }
    }

    bool FileProperty::isUnionRemoved() const
    {
        auto unionSchema = m_schema.base;
        if (isSet())
        {
            auto lastNode = m_values;
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            auto dataField = unionSchema->getUnionDataField();
            if (auto memiter = lastNode->find(dataField); memiter != lastNode->end())
            {
                auto unionValue = &(*memiter);
                if (unionSchema->type == DataType::string or unionSchema->type == DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(unionValue->is_string());
                }
                return unionValue->is_null();
            }
        }
        return false;
    }

    FileProperty FileProperty::getUnionData(char const* _unionType)
    {
        if (_unionType == nullptr)
        {
            _unionType = getUnionType();
        }
        FileProperty newLayer;
        auto dataSchema = m_schema.base->getUnionType(_unionType);
        auto unionSchema = m_schema.base;
        newLayer.m_key = _unionType;
        if (isSet())
        {
            auto unionType = getUnionType();
            if (unionType != nullptr and strcmp(_unionType, unionType) == 0)
            {
                auto lastNode = m_values;
                ENTLIB_DBG_ASSERT(lastNode->is_object());
                auto dataField = unionSchema->getUnionDataField();
                if (auto memiter = lastNode->find(dataField); memiter != lastNode->end())
                {
                    auto newValue = &(*memiter);
                    if (unionSchema->type == DataType::string
                        or unionSchema->type == DataType::entityRef)
                    {
                        ENTLIB_DBG_ASSERT(newValue->is_string());
                    }
                    newLayer.m_values = newValue;
                }
            }
        }
        newLayer.m_schema = Schema{dataSchema, nullptr};
        return newLayer;
    }

    Subschema const* FileProperty::getSchema() const
    {
        return m_schema.base;
    }

    json const* FileProperty::getPropertyDefaultValue() const
    {
        return m_schema.propDefVal;
    }

    json* FileProperty::createChildNode(
        FileProperty& _lastLayer,
        Key const& _childName,
        Subschema const& _newLayerSchema,
        size_t _arraySize)
    {
        ENTLIB_DBG_ASSERT(int(_lastLayer.m_values->type()) < int(json::value_t::discarded));
        json* newLayerJson = nullptr;
        switch (_lastLayer.m_schema.base->type)
        {
        case DataType::object:
        {
            if (_lastLayer.m_values->is_null())
            {
                (*_lastLayer.m_values) = json::object();
            }
            auto fieldName = std::get<char const*>(_childName);
            (*_lastLayer.m_values)[fieldName] = {};
            newLayerJson = &(*_lastLayer.m_values)[fieldName];
        }
        break;
        case DataType::oneOf:
        {
            if (_lastLayer.m_values->is_null())
            {
                (*_lastLayer.m_values) = json::object();
            }
            auto fieldName = std::get<char const*>(_childName);
            auto typeField = _lastLayer.m_schema.base->getUnionNameField();
            auto dataField = _lastLayer.m_schema.base->getUnionDataField();
            (*_lastLayer.m_values)[typeField] = fieldName;
            (*_lastLayer.m_values)[dataField] = {};
            newLayerJson = &(*_lastLayer.m_values)[dataField];
        }
        break;
        case DataType::array:
        {
            ENTLIB_DBG_ASSERT(_lastLayer.m_values->type() == json::value_t::array);
            auto meta = std::get<Subschema::ArrayMeta>(_lastLayer.m_schema.base->meta);
            auto& itemType = _lastLayer.m_schema.base->singularItems->get();
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                if (_lastLayer.m_values->is_null())
                {
                    (*_lastLayer.m_values) = json::array();
                }
                switch (itemType.linearItems->at(0)->type)
                {
                case DataType::string:
                {
                    auto key = std::get<char const*>(_childName);
                    auto pairNode = json::array();
                    pairNode.push_back(key);
                    pairNode.emplace_back();
                    _lastLayer.m_values->push_back(std::move(pairNode));
                    newLayerJson = &(*_lastLayer.m_values)[(*_lastLayer.m_values).size() - 1][1];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case DataType::integer:
                {
                    auto key = std::get<size_t>(_childName);
                    auto pairNode = json::array();
                    pairNode.push_back(key);
                    pairNode.emplace_back();
                    _lastLayer.m_values->push_back(std::move(pairNode));
                    newLayerJson = &(*_lastLayer.m_values)[(*_lastLayer.m_values).size() - 1][1];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            case "set"_hash:
            {
                if (_lastLayer.m_values->is_null())
                {
                    (*_lastLayer.m_values) = json::array();
                }
                switch (itemType.type)
                {
                case DataType::integer: // integer set
                {
                    auto key = std::get<size_t>(_childName);
                    _lastLayer.m_values->push_back(key);
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case DataType::string: // String set
                {
                    auto key = std::get<char const*>(_childName);
                    _lastLayer.m_values->push_back(key);
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case DataType::oneOf: // UnionSet
                {
                    auto wrapper = json::object();
                    auto fieldName = std::get<char const*>(_childName);
                    auto unionSchema = &_lastLayer.m_schema.base->singularItems->get();
                    auto typeField = unionSchema->getUnionNameField();
                    auto dataField = unionSchema->getUnionDataField();
                    wrapper[typeField] = fieldName;
                    wrapper[dataField] = {};
                    _lastLayer.m_values->push_back(std::move(wrapper));
                    newLayerJson =
                        &(*_lastLayer.m_values)[(*_lastLayer.m_values).size() - 1][dataField];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                case DataType::object: // Object Set
                    auto object = json::object();
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case DataType::string:
                    {
                        auto key = std::get<char const*>(_childName);
                        object[*meta.keyField] = key;
                        break;
                    }
                    case DataType::integer:
                    {
                        auto key = std::get<size_t>(_childName);
                        object[*meta.keyField] = key;
                        break;
                    }
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    ENTLIB_DBG_ASSERT(_lastLayer.m_values->type() == json::value_t::array);
                    _lastLayer.m_values->push_back(object);
                    newLayerJson = &(*_lastLayer.m_values)[(*_lastLayer.m_values).size() - 1];
                    ENTLIB_ASSERT(newLayerJson != nullptr);
                    break;
                }
                break;
            }
            case ""_hash:
            {
                if (_lastLayer.m_values->is_null())
                {
                    (*_lastLayer.m_values) = json::array();
                }
                while (_lastLayer.m_values->size() < _arraySize)
                {
                    _lastLayer.m_values->emplace_back();
                }
                while (_lastLayer.m_values->size() > _arraySize)
                {
                    _lastLayer.m_values->erase(_lastLayer.m_values->size() - 1);
                }
                auto index = std::get<size_t>(_childName);
                newLayerJson = &(*_lastLayer.m_values)[index];
                ENTLIB_ASSERT(newLayerJson != nullptr);
                break;
            }
            }
        }
        break;
        case DataType::null: [[fallthrough]];
        case DataType::string: [[fallthrough]];
        case DataType::number: [[fallthrough]];
        case DataType::integer: [[fallthrough]];
        case DataType::boolean: [[fallthrough]];
        case DataType::entityRef: [[fallthrough]];
        case DataType::COUNT: ENTLIB_LOGIC_ERROR("Unexpected DataType");
        }
        ENTLIB_ASSERT(newLayerJson != nullptr);
        if (newLayerJson->is_null())
        {
            if (_newLayerSchema.type == DataType::array)
            {
                *newLayerJson = json::array();
            }
            else if (_newLayerSchema.type == DataType::object)
            {
                *newLayerJson = json::object();
            }
        }
        return newLayerJson;
    }

    void FileProperty::setSize(size_t _size)
    {
        if (m_values->is_null())
        {
            (*m_values) = json::array();
        }
        while (_size > m_values->size())
        {
            m_values->emplace_back();
        }
        while (_size < m_values->size())
        {
            m_values->erase(m_values->size() - 1);
        }
    }
    template <typename T>
    void FileProperty::set(T&& _value)
    {
        if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, EntityRef>)
        {
            *m_values = _value.entityPath;
        }
        else
        {
            *m_values = std::forward<T>(_value);
        }
    }

    void FileProperty::setFloat(double _value)
    {
        set(_value);
    }
    void FileProperty::setInt(int64_t _value)
    {
        set(_value);
    }
    void FileProperty::setString(char const* _value)
    {
        ENTLIB_ASSERT(_value != nullptr);
        set(_value);
    }
    void FileProperty::setBool(bool _value)
    {
        set(_value);
    }
    void FileProperty::setEntityRef(EntityRef const& _value)
    {
        set(_value);
    }
    void FileProperty::setUnionType(char const* type)
    {
        auto& wrapper = (*m_values);
        auto dataFieldName = getSchema()->getUnionDataField();
        auto nameFieldName = getSchema()->getUnionNameField();
        wrapper[nameFieldName] = type;
        wrapper[dataFieldName] = json();
    }

    template <typename T>
    T FileProperty::get() const
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

    double FileProperty::getFloat() const
    {
        return get<double>();
    }
    int64_t FileProperty::getInt() const
    {
        return get<int64_t>();
    }
    char const* FileProperty::getString() const
    {
        return get<char const*>();
    }
    bool FileProperty::getBool() const
    {
        return get<bool>();
    }
    EntityRef FileProperty::getEntityRef() const
    {
        return get<EntityRef>();
    }
    size_t FileProperty::size() const
    {
        return m_values->size();
    }
    FileProperty::Key const& FileProperty::getPathToken() const
    {
        return m_key;
    }

} // namespace Ent
