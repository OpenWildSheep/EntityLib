#include "include/EntityLib/FileProperty.h"

#include <ciso646>
#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{
    FileProperty::FileProperty(EntityLib& _entitylib, JsonMetaData* _docMetaData)
        : m_entityLib(&_entitylib)
        , m_docMetaData(_docMetaData)
        , m_lastAccessVersion(_docMetaData == nullptr ? 0 : _docMetaData->version)
        , m_lastAccessGlobalVersion(_entitylib.getGlobalDocumentsVersion())
    {
    }

    FileProperty::FileProperty(
        EntityLib& _entitylib,
        Subschema const* _schema,
        char const* _filePath,
        json* _document,
        JsonMetaData* _docMetaData)
        : m_entityLib(&_entitylib)
        , m_docMetaData(_docMetaData)
        , m_lastAccessVersion(_docMetaData == nullptr ? 0 : _docMetaData->version)
        , m_lastAccessGlobalVersion(_entitylib.getGlobalDocumentsVersion())
    {
        if (_filePath != nullptr)
        {
            m_filePath = _filePath;
        }
        m_schema = Schema{{_schema}};
        _setRawJson(_document);
    }

    FileProperty::FileProperty(
        EntityLib& _entitylib, Subschema const* _schema, char const* _filePath, VersionedJson& _document)
        : FileProperty(_entitylib, _schema, _filePath, &_document.document, &_document.metadata)
    {
    }

    FileProperty::FileProperty(EntityLib& _entitylib, Subschema const* _schema, char const* _filePath)
        : FileProperty(
            _entitylib, _schema, _filePath, _schema->rootSchema->entityLib->readJsonFile(_filePath))
    {
    }

    void FileProperty::pushBack(char const* _key)
    {
        _getJson()->push_back(_key);
        _increaseVersion();
    }

    void FileProperty::pushBack(int64_t _key)
    {
        _getJson()->push_back(_key);
        _increaseVersion();
    }

    void FileProperty::save(char const* _filename) const
    {
        if (not _getRawJson()->is_object())
        {
            throw BadType(staticFormat(
                "Can't save %s. Can only save object or union.", getSchema()->name.c_str()));
        }
        m_schema.base->rootSchema->entityLib->saveJsonFile(
            _getRawJson(),
            _filename != nullptr ? _filename : m_filePath.c_str(),
            m_schema.base->name.c_str());
    }

    json* FileProperty::_getJson() const
    {
        return isSet() ? _getRawJsonMutable() : nullptr;
    }

    json const* FileProperty::getJson() const
    {
        return isSet() ? _getRawJson() : nullptr;
    }

    void FileProperty::_setRawJson(json* _jsonNode)
    {
        m_values = _jsonNode;
    }

    bool FileProperty::hasJsonPointer() const
    {
        return _getRawJson() != nullptr;
    }

    bool FileProperty::isSet() const
    {
        return _getRawJson() != nullptr and not _getRawJson()->is_null() and not isRemovedObject(nullptr);
    }

    bool FileProperty::isNull() const
    {
        auto* val = _getRawJson();
        return val != nullptr and val->is_null();
    }

    FileProperty FileProperty::getObjectField(char const* _field, SubschemaRef const* _fieldRef) const
    {
        FileProperty newLayer(*m_entityLib, m_docMetaData);
        ENTLIB_DBG_ASSERT(m_schema.base->type == DataType::object);
        if (_fieldRef == nullptr)
        {
            auto const& properties = m_schema.base->properties;
            if (auto const propIter = properties.find(_field); propIter != properties.end())
            {
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
        if (hasJsonPointer() and not _getRawJson()->is_null())
        {
            auto* const lastNode = _getRawJsonMutable();
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            if (auto const memiter = lastNode->find(_field); memiter != lastNode->end())
            {
                newLayer._setRawJson(&(*memiter));
            }
        }
        ENTLIB_DBG_ASSERT(m_schema.base != nullptr);
        return newLayer;
    }

    std::pair<FileProperty, FileProperty::MapItemAction>
    FileProperty::forceGetUnionSetItem(char const* _key, Subschema const* _dataSchema) const
    {
        FileProperty newLayer(*m_entityLib, m_docMetaData);
        auto const& lastschema = *m_schema.base;
        if (lastschema.singularItems == nullptr)
        {
            throw BadArrayType(staticFormat(
                "In Property::enterUnionSetItem, expected UnionSet. Got %s.",
                lastschema.name.c_str()));
        }
        auto& unionSchema = lastschema.singularItems->get();
        if (_dataSchema == nullptr)
        {
            if (auto const iter = unionSchema.unionTypeMap.find(_key);
                iter != unionSchema.unionTypeMap.end())
            {
                newLayer.m_schema = Schema{iter->second.dataSchema, nullptr};
            }
            else
            {
                throw ContextException("Unknown Union type : %s", _key);
            }
        }
        else
        {
            newLayer.m_schema = Schema{_dataSchema, nullptr};
        }
        newLayer.m_key = _key;

        MapItemAction subItemIsSet = MapItemAction::None;
        if (isSet())
        {
            auto const* dataField = unionSchema.getUnionDataField();

            if (auto const jsonIter = _findUnionSetItem(_key, true);
                jsonIter != _getRawJsonMutable()->end())
            {
                newLayer.m_wrapper = &(*jsonIter);
                if (auto const dataIter = jsonIter->find(dataField); dataIter != jsonIter->end())
                {
                    if (not dataIter->is_null()) // In UnionSet, null dataField mean remove
                    { // Item found!
                        newLayer._setRawJson(&(*dataIter));
                        subItemIsSet = MapItemAction::Add;
                    }
                    else // Item is marked for remove
                    {
                        subItemIsSet = MapItemAction::Remove;
                    }
                }
                else
                {
                    subItemIsSet = MapItemAction::Add;
                }
            }
        }
        ENTLIB_ASSERT(newLayer.m_schema.base != nullptr);
        return {newLayer, subItemIsSet};
    }

    static bool objectIsRemoved(json const& _object)
    {
        return _object.is_object() and _object.value("__removed__", false);
    }

    template <typename K>
    std::pair<FileProperty, FileProperty::MapItemAction> FileProperty::_enterObjectSetItemImpl(K _key) const
    {
        FileProperty newLayer(*m_entityLib, m_docMetaData);
        auto const& setSchema = *m_schema.base;
        ENTLIB_ASSERT(setSchema.type == DataType::array);
        auto const& objectSchema = setSchema.singularItems->get();
        char const* keyFieldName = nullptr;
        MapItemAction itemAction = MapItemAction::None;
        if (auto const* const meta = std::get_if<Subschema::ArrayMeta>(&setSchema.meta))
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
        auto& keySchema = objectSchema.properties.at(keyFieldName).get();
        if constexpr (std::is_same_v<char const*, K>)
        {
            if (not keySchema.isValidEnumString(_key))
            {
                throw BreakSchemaRules(staticFormat(
                    "The value '%s' is not accepted in enum type '%s'", _key, keySchema.name.c_str()));
            }
        }

        newLayer.m_schema = Schema{&objectSchema, nullptr};
        newLayer.m_key = _key;

        if (isSet())
        {
            if (auto jsonIter = _findObjectSetItem(_key, true);
                jsonIter != _getRawJsonMutable()->end())
            {
                newLayer._setRawJson(&(*jsonIter));
                if (objectIsRemoved(*jsonIter))
                {
                    itemAction = MapItemAction::Remove;
                }
                else
                {
                    itemAction = MapItemAction::Add;
                }
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.m_schema.base != nullptr);
        return {newLayer, itemAction};
    }

    std::pair<FileProperty, FileProperty::MapItemAction>
    FileProperty::forceGetObjectSetItem(char const* _key) const
    {
        return _enterObjectSetItemImpl(_key);
    }

    std::pair<FileProperty, FileProperty::MapItemAction>
    FileProperty::forceGetObjectSetItem(int64_t _key) const
    {
        return _enterObjectSetItemImpl(_key);
    }

    static bool mapRemoved(json const& _pair)
    {
        return _pair[1].is_null();
    }

    template <typename K>
    std::pair<FileProperty, FileProperty::MapItemAction> FileProperty::_enterMapItemImpl(K _key) const
    {
        FileProperty newLayer(*m_entityLib, m_docMetaData);

        auto& pairSchema = m_schema.base->singularItems->get();
        newLayer.m_schema = Schema{&pairSchema.linearItems->at(1).get(), nullptr};
        newLayer.m_key = _key;

        auto keySchema = &pairSchema.linearItems->at(0).get();
        if constexpr (std::is_same_v<char const*, K>)
        {
            if (not keySchema->isValidEnumString(_key))
            {
                throw BreakSchemaRules(staticFormat(
                    "The value '%s' is not accepted in enum type '%s'", _key, keySchema->name.c_str()));
            }
        }

        MapItemAction itemAction = MapItemAction::None;
        if (isSet())
        {
            if (auto jsonIter = _findMapItem(_key, true); jsonIter != _getRawJsonMutable()->end())
            {
                newLayer._setRawJson(&(*jsonIter)[1]); // Take this node even if it is a "null" node
                if (not mapRemoved(*jsonIter))
                {   // Item found
                    itemAction = MapItemAction::Add;
                }
                else
                {   // Item found but marked as removed
                    itemAction = MapItemAction::Remove;
                }
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.m_schema.base != nullptr);
        return {newLayer, itemAction};
    }

    std::pair<FileProperty, FileProperty::MapItemAction>
    FileProperty::forceGetMapItem(char const* _key) const
    {
        return _enterMapItemImpl(_key);
    }

    std::pair<FileProperty, FileProperty::MapItemAction> FileProperty::forceGetMapItem(int64_t _key) const
    {
        return _enterMapItemImpl(_key);
    }

    FileProperty FileProperty::getArrayItem(size_t _index) const
    {
        FileProperty newLayer(*m_entityLib, m_docMetaData);
        ENTLIB_DBG_ASSERT(m_schema.base->type == DataType::array);
        if (auto* const item = m_schema.base->singularItems.get())
        {
            auto const& subschema = item->get();
            newLayer.m_schema = Schema{&subschema, nullptr};
        }
        else
        {
            ENTLIB_DBG_ASSERT(m_schema.base->linearItems.has_value());
            if (_index >= m_schema.base->linearItems->size())
            {
                throw ContextException("Out of range in tuple");
            }
            auto const& subschema = m_schema.base->linearItems->at(_index).get();
            newLayer.m_schema = Schema{&subschema, nullptr};
        }
        newLayer.m_key = static_cast<int64_t>(_index);
        if (auto* const lastNode = _getJson())
        {
            if (lastNode->size() > _index)
            {
                auto* const newValue = &(*lastNode)[_index];
                if (newLayer.m_schema.base->type == DataType::string
                    or newLayer.m_schema.base->type == DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(newValue->is_string() or newValue->is_null());
                }
                newLayer._setRawJson(newValue);
            }
        }
        ENTLIB_DBG_ASSERT(newLayer.m_schema.base != nullptr);
        return newLayer;
    }

    char const* FileProperty::getUnionType() const
    {
        if (isSet())
        {
            auto const* typeField = m_schema.base->getUnionNameField();
            auto* const lastNode = _getRawJson();
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            if (auto const memiter = lastNode->find(typeField); memiter != lastNode->end())
            {
                return memiter->get_ref<std::string const&>().c_str();
            }
        }
        return nullptr;
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
        auto const* const unionSchema = m_schema.base;
        if (isSet())
        {
            auto* const lastNode = _getRawJson();
            ENTLIB_DBG_ASSERT(lastNode->is_object());
            auto const* dataField = unionSchema->getUnionDataField();
            if (auto const memiter = lastNode->find(dataField); memiter != lastNode->end())
            {
                auto const* const unionValue = &(*memiter);
                if (unionSchema->type == DataType::string or unionSchema->type == DataType::entityRef)
                {
                    ENTLIB_DBG_ASSERT(unionValue->is_string());
                }
                return unionValue->is_null();
            }
        }
        return false;
    }

    std::pair<FileProperty, FileProperty::MapItemAction>
    FileProperty::forceGetUnionData(char const* _unionType) const
    {
        if (_unionType == nullptr)
        {
            _unionType = getUnionType();
        }
        FileProperty newLayer(*m_entityLib, m_docMetaData);
        auto const* const dataSchema = m_schema.base->getUnionType(_unionType);
        auto const* const unionSchema = m_schema.base;
        newLayer.m_key = _unionType;
        MapItemAction itemAction = MapItemAction::None;
        if (isSet())
        {
            auto const* const unionType = getUnionType();
            if (unionType != nullptr)
            {
                if (strcmp(_unionType, unionType) == 0)
                {
                    itemAction = MapItemAction::Add;
                    auto* const lastNode = _getRawJsonMutable();
                    ENTLIB_DBG_ASSERT(lastNode->is_object());
                    auto const* dataField = unionSchema->getUnionDataField();
                    if (auto const memiter = lastNode->find(dataField); memiter != lastNode->end())
                    {
                        auto* const newValue = &(*memiter);
                        if (unionSchema->type == DataType::string
                            or unionSchema->type == DataType::entityRef)
                        {
                            ENTLIB_DBG_ASSERT(newValue->is_string());
                        }
                        newLayer._setRawJson(newValue);
                    }
                }
                else
                {
                    itemAction = MapItemAction::Remove;
                }
            }
        }
        newLayer.m_schema = Schema{dataSchema, nullptr};
        return {newLayer, itemAction};
    }

    Subschema const* FileProperty::getSchema() const
    {
        return m_schema.base;
    }

    json const* FileProperty::getPropertyDefaultValue() const
    {
        return m_schema.propDefVal;
    }

    void FileProperty::createChildNode(FileProperty& _parent)
    {
        if (isRemovedObject(_parent.getSchema()))
        {
            unRemoveObject(_parent.getSchema());
            return;
        }

        if (m_wrapper != nullptr)
        { // It is a Union in a UnionSet and the Union object is still declared in json
            auto&& unionSchema = _parent.getSchema()->singularItems->get();
            auto const* dataField = unionSchema.getUnionDataField();
            // TODO : Change to default value according to type
            _setRawJson(&((*m_wrapper)[dataField] = json::object()));
            return;
        }

        auto&& childName = getPathToken();

        ENTLIB_ASSERT(not hasJsonPointer());
        ENTLIB_DBG_ASSERT(
            static_cast<int>(_parent._getRawJson()->type())
            < static_cast<int>(json::value_t::discarded));
        json* newLayerJson = nullptr;
        auto& parentSchema = *_parent.m_schema.base;
        switch (parentSchema.getDataKind())
        {
        case DataKind::object:
        {
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::object();
            }
            auto const& fieldName = std::get<std::string>(childName);
            (*_parent._getRawJsonMutable())[fieldName] = {};
            newLayerJson = &(*_parent._getRawJsonMutable())[fieldName];
        }
        break;
        case DataKind::union_:
        {
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::object();
            }
            auto const& fieldName = std::get<std::string>(childName);
            auto const* typeField = parentSchema.getUnionNameField();
            auto const* dataField = parentSchema.getUnionDataField();
            (*_parent._getRawJsonMutable())[typeField] = fieldName;
            (*_parent._getRawJsonMutable())[dataField] = {};
            newLayerJson = &(*_parent._getRawJsonMutable())[dataField];
        }
        break;
        case DataKind::map:
        {
            auto& itemType = parentSchema.singularItems->get();
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::array();
            }
            auto& keyType = itemType.linearItems->at(0).get();
            switch (keyType.type)
            {
            case DataType::entityRef: [[fallthrough]];
            case DataType::string:
            {
                auto const& key = std::get<std::string>(childName);
                ENTLIB_ASSERT(keyType.enumValues.empty() or keyType.isValidEnumString(key));
                auto pairNode = json::array();
                pairNode.push_back(key);
                pairNode.emplace_back();
                _parent._getRawJsonMutable()->push_back(std::move(pairNode));
                newLayerJson =
                    &(*_parent._getRawJsonMutable())[(*_parent._getRawJson()).size() - 1][1];
                ENTLIB_ASSERT(newLayerJson != nullptr);
                break;
            }
            case DataType::integer:
            {
                auto key = std::get<int64_t>(childName);
                auto pairNode = json::array();
                pairNode.push_back(key);
                pairNode.emplace_back();
                _parent._getRawJsonMutable()->push_back(std::move(pairNode));
                newLayerJson =
                    &(*_parent._getRawJsonMutable())[(*_parent._getRawJson()).size() - 1][1];
                ENTLIB_ASSERT(newLayerJson != nullptr);
                break;
            }
            default: ENTLIB_LOGIC_ERROR("Unexpected key type");
            }
            break;
        }
        case DataKind::primitiveSet:
        {
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::array();
            }
            auto& itemType = parentSchema.singularItems->get();
            switch (itemType.type)
            {
            case DataType::integer: // integer set
            {
                auto key = std::get<int64_t>(childName);
                _parent._getRawJsonMutable()->push_back(key);
                ENTLIB_ASSERT(newLayerJson != nullptr);
                break;
            }
            case DataType::entityRef: [[fallthrough]]; // entityRef set
            case DataType::string: // String set
            {
                auto const& key = std::get<std::string>(childName);
                _parent._getRawJsonMutable()->push_back(key);
                ENTLIB_ASSERT(newLayerJson != nullptr);
                break;
            }
            }
            break;
        }
        case DataKind::unionSet:
        {
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::array();
            }
            auto wrapper = json::object();
            auto const& fieldName = std::get<std::string>(childName);
            auto* unionSchema = &parentSchema.singularItems->get();
            auto const* typeField = unionSchema->getUnionNameField();
            auto const* dataField = unionSchema->getUnionDataField();
            wrapper[dataField] = json::object(); // TODO : Change to default value according to type
            wrapper[typeField] = fieldName;
            _parent._getRawJsonMutable()->push_back(std::move(wrapper));
            newLayerJson =
                &(*_parent._getRawJsonMutable())[(*_parent._getRawJson()).size() - 1][dataField];
            ENTLIB_ASSERT(newLayerJson != nullptr);
            break;
        }
        case DataKind::objectSet:
        {
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::array();
            }
            auto meta = std::get<Subschema::ArrayMeta>(parentSchema.meta);
            auto& itemType = parentSchema.singularItems->get();
            auto object = json::object();
            auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
            switch (keyFieldSchema.type)
            {
            case DataType::entityRef: [[fallthrough]];
            case DataType::string:
            {
                auto const& key = std::get<std::string>(childName);
                object[*meta.keyField] = key;
                break;
            }
            case DataType::integer:
            {
                auto key = std::get<int64_t>(childName);
                object[*meta.keyField] = key;
                break;
            }
            default: ENTLIB_LOGIC_ERROR("Unexpected key type");
            }
            ENTLIB_DBG_ASSERT(_parent.getJson()->type() == json::value_t::array);
            _parent._getRawJsonMutable()->push_back(object);
            newLayerJson = &(*_parent._getRawJsonMutable())[(*_parent._getRawJson()).size() - 1];
            ENTLIB_ASSERT(newLayerJson != nullptr);
            break;
        }
        case DataKind::array:
        {
            ENTLIB_DBG_ASSERT(_parent.getJson()->type() == json::value_t::array);
            if (_parent._getRawJson()->is_null())
            {
                (*_parent._getRawJsonMutable()) = json::array();
            }
            auto const index = std::get<int64_t>(childName);
            auto const minSize = std::max(static_cast<int64_t>(parentSchema.minItems - 1), index);
            while (static_cast<int64_t>(_parent._getRawJson()->size()) <= minSize)
            {
                _parent._getRawJsonMutable()->emplace_back();
            }
            newLayerJson = &(*_parent._getRawJsonMutable())[index];
            ENTLIB_ASSERT(_parent._getRawJson()->size() <= parentSchema.maxItems);
            ENTLIB_ASSERT(newLayerJson != nullptr);
            break;
        }
        case DataKind::string: [[fallthrough]];
        case DataKind::number: [[fallthrough]];
        case DataKind::integer: [[fallthrough]];
        case DataKind::boolean: [[fallthrough]];
        case DataKind::entityRef: [[fallthrough]];
        case DataKind::COUNT: ENTLIB_LOGIC_ERROR("Unexpected DataType");
        }
        ENTLIB_ASSERT(newLayerJson != nullptr);
        _setRawJson(newLayerJson);
        if (_getRawJson()->is_null())
        {
            if (getSchema()->type == DataType::array) // Replace "null" by [] for readability
            {
                *_getRawJsonMutable() = json::array();
            }
            else if (getSchema()->type == DataType::object) // Replace "null" by [] for readability
            {
                *_getRawJsonMutable() = json::object();
            }
            else if (_parent.getSchema()->getDataKind() == DataKind::map)
            {   // In map replace "null" by default value because "null" is a reserved value
                setToDefault(_parent.getSchema(), true);
            }
        }
        _increaseVersion();
    }

    void FileProperty::setSize(size_t _size)
    {
        bool changed = false;
        if (_getRawJson()->is_null())
        {
            (*_getRawJsonMutable()) = json::array();
            changed = true;
        }
        while (_size > _getRawJson()->size())
        {
            _getRawJsonMutable()->emplace_back();
            changed = true;
        }
        while (_size < _getRawJson()->size())
        {
            _getRawJsonMutable()->erase(_getRawJson()->size() - 1);
            changed = true;
        }
        if (changed)
        {
            _increaseVersion();
        }
    }
    template <typename T>
    void FileProperty::set(T&& _value)
    {
        if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, EntityRef>)
        {
            *_getRawJsonMutable() = _value.entityPath;
        }
        else if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, double>)
        {
            *_getRawJsonMutable() = truncFloat(static_cast<float>(_value));
        }
        else
        {
            *_getRawJsonMutable() = std::forward<T>(_value);
        }
        _increaseVersion();
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
        auto& wrapper = (*_getRawJsonMutable());
        auto const* const dataFieldName = getSchema()->getUnionDataField();
        auto const* const nameFieldName = getSchema()->getUnionNameField();
        wrapper[nameFieldName] = type;
        wrapper.erase(dataFieldName);
        _increaseVersion();
    }

    template <typename T>
    T FileProperty::get() const
    {
        if constexpr (std::is_same_v<T, char const*>)
        {
            return getJson()->get_ref<std::string const&>().c_str();
        }
        else if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, EntityRef>)
        {
            return EntityRef{getString()};
        }
        else
        {
            return getJson()->get<T>();
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
        return _getRawJson()->size();
    }
    FileProperty::Key const& FileProperty::getPathToken() const
    {
        return m_key;
    }

    template <typename K>
    json::iterator FileProperty::_findPrimSetKey(K _key)
    {
        if (not isSet())
        {
            return _getRawJsonMutable()->end();
        }
        auto find = [this](auto&& _isEqual)
        {
            return std::find_if(_getRawJsonMutable()->begin(), _getRawJsonMutable()->end(), _isEqual);
        };
        if constexpr (std::is_same_v<K, char const*>)
        {
            return find([this, _key](json const& primLayer)
                        { return primLayer.get_ref<std::string const&>() == _key; });
        }
        else
        {
            return find([this, _key](json const& primLayer)
                        { return primLayer.get<int64_t>() == _key; });
        }
    }

    template <typename V>
    static bool compareJson(json const& _node, V _value)
    {
        if constexpr (std::is_same_v<V, char const*>)
        {
            return _node.get_ref<std::string const&>() == _value;
        }
        else
        {
            return _node.get<V>() == _value;
        }
    }

    template <typename K, typename GetKey, typename IsRemoved>
    json::iterator FileProperty::_findArrayItem(
        bool _withRemoved, K _key, GetKey&& _getKey, IsRemoved&& _isRemoved) const
    {
        ENTLIB_DBG_ASSERT(isSet());
        if (_withRemoved)
        {
            return std::find_if(
                _getRawJsonMutable()->begin(),
                _getRawJsonMutable()->end(),
                [_getKey, _key](json const& _pair) { return compareJson(_getKey(_pair), _key); });
        }
        return std::find_if(
            _getRawJsonMutable()->begin(),
            _getRawJsonMutable()->end(),
            [_getKey, _isRemoved, _key](json const& _pair)
            { return compareJson(_getKey(_pair), _key) and not _isRemoved(_pair); });
    }

    json::iterator FileProperty::_findUnionSetItem(char const* _key, bool _withRemoved) const
    {
        auto const* dataField = getSchema()->singularItems->get().getUnionDataField();
        auto const* typeField = getSchema()->singularItems->get().getUnionNameField();
        return _findArrayItem(
            _withRemoved,
            _key,
            [typeField](json const& _union) { return _union[typeField]; },
            [dataField](json const& _union) { return _union[dataField].is_null(); });
    }

    template <typename K>
    json::iterator FileProperty::_findMapItem(K _key, bool _withRemoved) const
    {
        return _findArrayItem(
            _withRemoved, _key, [](json const& _pair) { return _pair[0]; }, mapRemoved);
    }

    template <typename K>
    json::iterator FileProperty::_findObjectSetItem(K _key, bool _withRemoved) const
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
        ENTLIB_ASSERT(meta.keyField.has_value());
        auto const* keyFieldName = meta.keyField->c_str();
        return _findArrayItem(
            _withRemoved,
            _key,
            [keyFieldName](json const& _object) { return _object[keyFieldName]; },
            objectIsRemoved);
    }

    template <typename K>
    bool FileProperty::_countPrimSetKeyImpl(K _key)
    {
        if (not isSet())
        {
            return false;
        }
        auto iter = _findPrimSetKey(_key);
        return iter != _getRawJsonMutable()->end();
    }

    bool FileProperty::countPrimSetKey(char const* _key)
    {
        return _countPrimSetKeyImpl(_key);
    }
    bool FileProperty::countPrimSetKey(int64_t _key)
    {
        return _countPrimSetKeyImpl(_key);
    }

    void FileProperty::updateMapKeysString(std::set<char const*, CmpStr>& _keys, bool onlyRemoved) const
    {
        if (isSet())
        {
            auto const* node = getJson();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (auto const& pair : *node)
            {
                auto const* key = pair[0].get_ref<std::string const&>().c_str();
                bool const removed = mapRemoved(pair);
                if (removed and not onlyRemoved)
                {
                    _keys.erase(key);
                }
                if (removed == onlyRemoved)
                {
                    _keys.insert(key);
                }
            }
        }
    }

    void FileProperty::updateMapKeysInt(std::set<int64_t>& _keys, bool onlyRemoved) const
    {
        if (isSet())
        {
            auto const* node = getJson();
            ENTLIB_DBG_ASSERT(node->is_array());
            for (auto const& pair : *node)
            {
                auto key = pair[0].get<int64_t>();
                bool const removed = mapRemoved(pair);
                if (removed and not onlyRemoved)
                {
                    _keys.erase(key);
                }
                if (removed == onlyRemoved)
                {
                    _keys.insert(key);
                }
            }
        }
    }

    void FileProperty::updatePrimSetKeysString(std::set<char const*, CmpStr>& _keys) const
    {
        if (isSet())
        {
            for (auto const& prim : *getJson())
            {
                _keys.insert(prim.get_ref<std::string const&>().c_str());
            }
        }
    }
    void FileProperty::updatePrimSetKeysInt(std::set<int64_t>& _keys) const
    {
        if (isSet())
        {
            for (auto const& prim : *getJson())
            {
                _keys.insert(prim.get<int64_t>());
            }
        }
    }

    void FileProperty::updateUnionSetKeysString(
        std::map<char const*, Subschema const*, CmpStr>& _keys, bool onlyRemoved) const
    {
        if (isSet())
        {
            auto const* node = getJson();
            for (size_t i = 0; i < node->size(); ++i)
            {
                auto arrayItem = getArrayItem(i);
                auto const* unionSchema = arrayItem.getUnionSchema();
                bool const removed = (unionSchema == nullptr) or arrayItem.isUnionRemoved();
                if (removed and not onlyRemoved)
                {
                    _keys.erase(arrayItem.getUnionType());
                }
                else if (removed == onlyRemoved)
                {
                    _keys.emplace(arrayItem.getUnionType(), unionSchema);
                }
            }
        }
    }

    void FileProperty::updateObjectSetKeysString(
        std::set<char const*, CmpStr>& _keys, bool onlyRemoved) const
    {
        if (isSet())
        {
            auto const& meta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
            for (auto const& object : *getJson())
            {
                auto const& key = object.at(*meta.keyField).get_ref<std::string const&>();
                auto const removed = objectIsRemoved(object);
                if (removed and not onlyRemoved)
                {
                    _keys.erase(key.c_str());
                }
                else if (removed == onlyRemoved)
                {
                    _keys.insert(key.c_str());
                }
            }
        }
    }

    void FileProperty::updateObjectSetKeysInt(std::set<int64_t>& _keys, bool onlyRemoved) const
    {
        if (isSet())
        {
            auto const& meta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
            for (auto const& object : *getJson())
            {
                auto key = object.at(*meta.keyField).get<int64_t>();
                auto const removed = objectIsRemoved(object);
                if (removed and not onlyRemoved)
                {
                    _keys.erase(key);
                }
                else if (removed == onlyRemoved)
                {
                    _keys.insert(key);
                }
            }
        }
    }

    std::set<char const*, CmpStr> FileProperty::getMapRemovedKeysString() const
    {
        std::set<char const*, CmpStr> removed;
        updateMapKeysString(removed, true);
        return removed;
    }
    std::set<int64_t> FileProperty::getMapRemovedKeysInt() const
    {
        std::set<int64_t> removed;
        updateMapKeysInt(removed, true);
        return removed;
    }
    std::map<char const*, Subschema const*, CmpStr> FileProperty::getUnionSetRemovedKeysString() const
    {
        std::map<char const*, Subschema const*, CmpStr> removed;
        updateUnionSetKeysString(removed, true);
        return removed;
    }
    std::set<char const*, CmpStr> FileProperty::getObjectSetRemovedKeysString() const
    {
        std::set<char const*, CmpStr> removed;
        updateObjectSetKeysString(removed, true);
        return removed;
    }
    std::set<int64_t> FileProperty::getObjectSetRemovedKeysInt() const
    {
        std::set<int64_t> removed;
        updateObjectSetKeysInt(removed, true);
        return removed;
    }

    template <typename K>
    bool FileProperty::_erasePrimSetKeyImpl(K _key)
    {
        if (auto iter = _findPrimSetKey(_key); iter != _getRawJsonMutable()->end())
        {
            _getRawJsonMutable()->erase(iter);
            _increaseVersion();
            return true;
        }
        return false;
    }

    bool FileProperty::erasePrimSetKey(char const* _key)
    {
        return _erasePrimSetKeyImpl(_key);
    }
    bool FileProperty::erasePrimSetKey(int64_t _key)
    {
        return _erasePrimSetKeyImpl(_key);
    }

    template <typename K, typename FindItem, typename IsRemoved, typename MaskRemoved, typename PushBack>
    bool FileProperty::_eraseImpl(
        K _key,
        bool _isInPrefab,
        FindItem&& _findItem,
        IsRemoved&& _isRemoved,
        MaskRemoved&& _markRemove,
        PushBack&& _pushBack)
    {
        if (not _isInPrefab)
        {
            if (not isSet())
            {
                return false;
            }
            if (auto iter = _findItem(this, _key, _isInPrefab); iter != _getRawJsonMutable()->end())
            {
                auto const wasAlreadyRemoved = _isRemoved(*iter);
                _getRawJsonMutable()->erase(iter);
                _increaseVersion();
                return not wasAlreadyRemoved;
            }
            return false;
        }
        if (auto iter = _findItem(this, _key, _isInPrefab); iter != _getRawJsonMutable()->end())
        {
            if (_isRemoved(*iter))
            {
                return false;
            }
            _markRemove(*iter);
            _increaseVersion();
        }
        else
        {
            _pushBack(_key);
            _increaseVersion();
        }
        return true;
    }

    template <typename K>
    bool FileProperty::_eraseObjectSetItemImpl(K _key, bool _isInPrefab)
    {
        auto&& meta = std::get<Subschema::ArrayMeta>(getSchema()->meta);
        auto const* keyFieldName = meta.keyField->c_str();
        return _eraseImpl(
            _key,
            _isInPrefab,
            std::mem_fn(&FileProperty::_findObjectSetItem<K>),
            objectIsRemoved,
            [](auto& node) { return node["__removed__"] = true; },
            [this, keyFieldName](K _key) {
                _getRawJsonMutable()->push_back(
                    json::object({{keyFieldName, _key}, {"__removed__", true}}));
            });
    }

    bool FileProperty::eraseObjectSetItem(char const* _key, bool _isInPrefab)
    {
        return _eraseObjectSetItemImpl(_key, _isInPrefab);
    }
    bool FileProperty::eraseObjectSetItem(int64_t _key, bool _isInPrefab)
    {
        return _eraseObjectSetItemImpl(_key, _isInPrefab);
    }

    bool FileProperty::eraseUnionSetItem(char const* _key, bool _isInPrefab)
    {
        auto const* dataField = getSchema()->singularItems->get().getUnionDataField();
        auto const* typeField = getSchema()->singularItems->get().getUnionNameField();
        auto isRemoved = [dataField](auto& node)
        {
            if (auto iter = node.find(dataField); iter != node.end())
            {
                return iter->is_null();
            }
            return false;
        };
        auto pushBack = [this, typeField, dataField](char const* _key)
        {
            auto& newUnion = _getRawJsonMutable()->emplace_back(json::object());
            newUnion[typeField] = _key;
            newUnion[dataField] = json();
        };

        return _eraseImpl(
            _key,
            _isInPrefab,
            std::mem_fn(&FileProperty::_findUnionSetItem),
            isRemoved,
            [dataField](auto& node) { return node[dataField] = json(); },
            pushBack);
    }

    template <typename K>
    bool FileProperty::_eraseMapItemImpl(K _key, bool _isInPrefab)
    {
        auto pushBack = [this](K _key)
        {
            _getRawJsonMutable()->push_back(json::array({_key, json()}));
        };

        return _eraseImpl(
            _key,
            _isInPrefab,
            std::mem_fn(&FileProperty::_findMapItem<K>),
            mapRemoved,
            [](auto& node) { node[1] = json(); },
            pushBack);
    }

    bool FileProperty::eraseMapItem(char const* _key, bool _isInPrefab)
    {
        return _eraseMapItemImpl(_key, _isInPrefab);
    }
    bool FileProperty::eraseMapItem(int64_t _key, bool _isInPrefab)
    {
        return _eraseMapItemImpl(_key, _isInPrefab);
    }

    void FileProperty::unsetObjectField(FileProperty& _field)
    {
        if (not isSet())
        {
            return;
        }
        for (auto&& [key, data] : _getRawJson()->items())
        {
            if (_field._getRawJson() == &data)
            {
                _getRawJsonMutable()->erase(key);
                _increaseVersion();
                break;
            }
        }
        _field._setRawJson(nullptr);
    }

    void FileProperty::unsetUnionData()
    {
        if (not isSet())
        {
            return;
        }
        auto const* const dataFieldName = getSchema()->getUnionDataField();
        _getRawJsonMutable()->erase(dataFieldName);
        _increaseVersion();
    }

    void FileProperty::unsetMapItem(FileProperty& _data)
    {
        if (not isSet())
        {
            return;
        }
        bool found = false;
        auto map = _getRawJson();
        for (size_t i = 0; i < map->size(); ++i)
        {
            auto const& pair = (*map)[i];
            if (_data._getRawJson() == &pair[1])
            {
                _getRawJsonMutable()->erase(i);
                _increaseVersion();
                found = true;
                break;
            }
        }
        ENTLIB_ASSERT(found);
        _data._setRawJson(nullptr);
    }

    void FileProperty::unsetObjectSetItem(FileProperty& _object)
    {
        if (not isSet())
        {
            return;
        }
        bool found = false;
        auto unionset = _getRawJson();
        for (size_t i = 0; i < unionset->size(); ++i)
        {
            if (_object._getRawJson() == &(*unionset)[i])
            {
                _getRawJsonMutable()->erase(i);
                _increaseVersion();
                found = true;
                break;
            }
        }
        ENTLIB_ASSERT(found);
        _object._setRawJson(nullptr);
    }

    void FileProperty::unsetUnionSetItem(FileProperty& _data)
    {
        if (not isSet())
        {
            return;
        }
        bool found = false;
        auto const* unionDataFieldName = getSchema()->singularItems->get().getUnionDataField();
        auto unionset = _getRawJson();
        for (size_t i = 0; i < unionset->size(); ++i)
        {
            auto const& union_ = (*unionset)[i];
            if (auto dataIter = union_.find(unionDataFieldName); dataIter != union_.end())
            {
                if (_data._getRawJson() == &(*dataIter))
                {
                    _getRawJsonMutable()->erase(i);
                    _increaseVersion();
                    found = true;
                    break;
                }
            }
        }
        ENTLIB_ASSERT(found);
        _data._setRawJson(nullptr);
    }

    void FileProperty::setToDefault(Subschema const* _parentSchema, bool _force)
    {
        if (not _force and not isSet())
        {
            return;
        }
        switch (getSchema()->type)
        {
        case DataType::string: *_getRawJsonMutable() = std::string(); break;
        case DataType::object:
        {
            json newObj = json::object();
            if (auto const* const arrayMeta = std::get_if<Subschema::ArrayMeta>(&_parentSchema->meta))
            {
                if (auto const keyField = arrayMeta->keyField)
                {
                    auto const* keyFieldName = keyField->c_str();
                    auto key = _getRawJsonMutable()->at(keyFieldName);
                    *_getRawJsonMutable() = json::object({{keyFieldName, key}});
                    break;
                }
            }
            *_getRawJsonMutable() = json::object();
            break;
        }
        case DataType::entityRef: *_getRawJsonMutable() = std::string(); break;
        case DataType::array: *_getRawJsonMutable() = json::array(); break;
        case DataType::boolean: *_getRawJsonMutable() = false; break;
        case DataType::integer: *_getRawJsonMutable() = 0; break;
        case DataType::null: *_getRawJsonMutable() = json(); break;
        case DataType::number: *_getRawJsonMutable() = 0.; break;
        case DataType::oneOf: *_getRawJsonMutable() = json::object(); break;
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected schema type");
        }
        _increaseVersion();
    }

    void FileProperty::setToNull()
    {
        if (not isSet())
        {
            return;
        }
        *_getRawJsonMutable() = json();
        _increaseVersion();
    }

    bool FileProperty::isRemovedObject(Subschema const* _parentSchema) const
    {
        if (_parentSchema != nullptr  and _parentSchema->getDataKind() == DataKind::map and isNull())
        {   // Take care of the case of null in a map item (mean marked for remove)
            return true;
        }
        return _getRawJson() != nullptr and objectIsRemoved(*_getRawJson());
    }

    void FileProperty::unRemoveObject(Subschema const* _parentSchema)
    {
        if (_parentSchema != nullptr and _parentSchema->getDataKind() == DataKind::map and isNull())
        {   // Take care of the case of null in a map item (mean marked for remove)
            setToDefault(_parentSchema, true);
        }
        else
        {
            _getRawJsonMutable()->erase("__removed__");
        }
        _increaseVersion();
        ENTLIB_ASSERT(not isRemovedObject(_parentSchema));
    }

    char const* FileProperty::getFilePath() const
    {
        return m_filePath.c_str();
    }

    json const* FileProperty::_getRawJson() const
    {
        return m_values;
    }

    json* FileProperty::_getRawJsonMutable() const
    {
        return m_values;
    }

    void FileProperty::_increaseVersion()
    {
        if (m_docMetaData != nullptr)
        {
            ++m_docMetaData->version;
            m_lastAccessVersion = m_docMetaData->version;
            m_entityLib->incrementGlobalDocumentsVersion();
            m_lastAccessGlobalVersion = m_entityLib->getGlobalDocumentsVersion();
        }
    }

    bool FileProperty::needRebuild() const
    {
        if (m_docMetaData == nullptr)
        {
            return false;
        }
        return m_docMetaData->version != m_lastAccessVersion;
    }

    bool FileProperty::needRebuildGlobal() const
    {
        return m_entityLib->getGlobalDocumentsVersion() != m_lastAccessGlobalVersion;
    }

    void FileProperty::updateToResolved()
    {
        if (m_docMetaData != nullptr)
        {
            m_lastAccessVersion = m_docMetaData->version;
        }
    }

} // namespace Ent
