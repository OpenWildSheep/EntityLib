#pragma once

#include "EntityLib.h"
#include <variant>
#include <ciso646>
#include "../Tools.h"
#include "FileCursor.h"
#include "../external/rah.hpp"

namespace Ent
{
    struct ENTLIB_DLLEXPORT Cursor
    {
        using Key = std::variant<std::string, size_t>;
        using NodeRef = std::vector<Key>;
        EntityLib* m_entityLib = nullptr;
        FileCursor instance;
        struct Layer
        {
            Cursor* prefab = nullptr;
            std::unique_ptr<Cursor> prefabsStorage;
            FileCursor* defaultVal = nullptr;
            std::unique_ptr<FileCursor> defaultStorage;
            size_t arraySize = 0;
            bool isDefault = false;
        };
        std::vector<Layer> layers;

        Cursor(Cursor const&) = delete;
        Cursor& operator=(Cursor const&) = delete;

        Cursor() = default;

        Cursor(
            EntityLib* _entityLib,
            Ent::Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc)
            // : schema({_schema})
            : m_entityLib(_entityLib)
            , instance(_schema, _filename, _doc)
        {
            ENTLIB_ASSERT(_schema != nullptr);
            // layers.reserve(100);
            Layer newLayer;
            ///////////////////////////////////////////////////////////////////////////////////////
            // DO NOT COMIT THIS const_cast !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            ///////////////////////////////////////////////////////////////////////////////////////
            newLayer.defaultStorage = std::make_unique<FileCursor>(
                _schema, nullptr, const_cast<nlohmann::json*>(&_schema->defaultValue));
            newLayer.defaultVal = newLayer.defaultStorage.get();
            //[[maybe_unused]] auto type = _document->GetType();
            //ENTLIB_DBG_ASSERT(_document->is_object());
            auto doc = instance.back();
            if (auto member = doc->find("InstanceOf"); member != doc->end())
            {
                if (auto const& prefabPath = member->get_ref<std::string const&>();
                    prefabPath.size() > 0)
                {
                    newLayer.prefabsStorage =
                        std::make_unique<Cursor>(m_entityLib, _schema, prefabPath.c_str());
                    newLayer.prefab = newLayer.prefabsStorage.get();
                    ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                }
            }
            newLayer.isDefault = false;
            layers.emplace_back(std::move(newLayer));
            checkInvariants();
        }

        Cursor(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
            : Cursor(_entityLib, _schema, _filename, &_entityLib->readJsonFile(_filename))
        {
        }

        void save(char const* _filename = nullptr) const
        {
            instance.save(_filename);
        }

        bool isDefaultImpl() const
        {
            auto& newLayer = layers.back();
            if (instance.isSet())
            {
                return false;
            }
            if (newLayer.prefab != nullptr)
            {
                return newLayer.prefab->isDefaultImpl();
            }
            return true;
        }

        void pushDefault(Layer& newLayer) const
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

        bool isDefault() const
        {
            return layers.back().isDefault;
        }

        bool loadInstanceOf(Layer& newLayer)
        {
            auto* subschema = instance.getSchema();
            if (instance.isSet() and subschema->type == Ent::DataType::object)
            {
                if (auto member = instance.back()->find("InstanceOf");
                    member != instance.back()->end())
                {
                    if (auto const& prefabPath = member->get_ref<std::string const&>();
                        prefabPath.size() > 0)
                    {
                        newLayer.prefabsStorage =
                            std::make_unique<Cursor>(m_entityLib, subschema, prefabPath.c_str());
                        newLayer.prefab = newLayer.prefabsStorage.get();
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                    return true;
                }
            }
            return false;
        }

        Cursor& enterObjectField(char const* _field, SubschemaRef const* _fieldRef = nullptr)
        {
            checkInvariants();
            auto const layersCount = layers.size();
            ENTLIB_DBG_ASSERT(getDataType() == Ent::DataType::object);
            Layer newLayer;
            auto& lastLayer = layers.back();
            ENTLIB_DBG_ASSERT(
                lastLayer.defaultVal == nullptr
                or lastLayer.defaultVal->getSchema()->type == Ent::DataType::object);
            instance.enterObjectField(_field, _fieldRef);
            auto* subschema = instance.getSchema();
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
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
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterObjectField(_field, _fieldRef);
                if (lastLayer.defaultVal->isSet())
                {
                    defaultFound = true;
                    newLayer.defaultVal = lastLayer.defaultVal;
                }
                else
                {
                    lastLayer.defaultVal->exit();
                }
            }
            if (not defaultFound)
            {
                auto propDefVal = instance.getPropertyDefaultValue();
                if (propDefVal) // If there is property default, use them
                {
                    newLayer.defaultStorage = std::make_unique<FileCursor>(
                        subschema, nullptr, (nlohmann::json*)propDefVal);
                    newLayer.defaultVal = newLayer.defaultStorage.get();
                }
                else if (not subschema->defaultValue.is_null())
                {
                    newLayer.defaultStorage = std::make_unique<FileCursor>(
                        subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                    newLayer.defaultVal = newLayer.defaultStorage.get();
                }
            }
            comitNewLayer(std::move(newLayer));
            ENTLIB_DBG_ASSERT(layersCount == layers.size() - 1);
            return *this;
        }

        Cursor& enterUnionData(char const* type = nullptr)
        {
            checkInvariants();
            if (type == nullptr)
                type = getUnionType();
            Layer newLayer;
            auto& lastLayer = layers.back();
            instance.enterUnionData(type);
            auto* subschema = instance.getSchema();
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterUnionData(type);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterUnionData(type);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        Cursor& enterUnionSetItem(char const* _field, Subschema const* _dataSchema = nullptr)
        {
            checkInvariants();
            Layer newLayer;
            auto& lastLayer = layers.back();
            instance.enterUnionSetItem(_field, _dataSchema);
            auto* subschema = instance.getSchema();
            ENTLIB_DBG_ASSERT(_dataSchema == nullptr or subschema == _dataSchema);
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterUnionSetItem(_field, subschema);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterUnionSetItem(_field, subschema);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else if (instance.getPropertyDefaultValue()) // If there is property default, use them
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)instance.getPropertyDefaultValue());
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        Cursor& enterObjectSetItem(char const* _field)
        {
            checkInvariants();
            Layer newLayer;
            auto& lastLayer = layers.back();
            instance.enterObjectSetItem(_field);
            auto* subschema = instance.getSchema();
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterObjectSetItem(_field);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else if (instance.getPropertyDefaultValue()) // If there is property default, use them
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)instance.getPropertyDefaultValue());
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterObjectSetItem(_field);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        Cursor& enterObjectSetItem(int64_t _field)
        {
            checkInvariants();
            Layer newLayer;
            auto& lastLayer = layers.back();
            instance.enterObjectSetItem(_field);
            auto* subschema = instance.getSchema();
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterObjectSetItem(_field);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else if (instance.getPropertyDefaultValue()) // If there is property default, use them
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)instance.getPropertyDefaultValue());
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterObjectSetItem(_field);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        Cursor& enterMapItem(char const* _field)
        {
            checkInvariants();
            Layer newLayer;
            auto& lastLayer = layers.back();
            instance.enterMapItem(_field);
            auto* subschema = instance.getSchema();
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterMapItem(_field);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else if (instance.getPropertyDefaultValue()) // If there is property default, use them
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)instance.getPropertyDefaultValue());
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterMapItem(_field);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        Cursor& enterMapItem(int64_t _field)
        {
            checkInvariants();
            Layer newLayer;
            auto& lastLayer = layers.back();
            instance.enterMapItem(_field);
            auto* subschema = instance.getSchema();
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterMapItem(_field);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else if (instance.getPropertyDefaultValue()) // If there is property default, use them
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)instance.getPropertyDefaultValue());
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterMapItem(_field);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        void comitNewLayer(Layer newLayer)
        {
            pushDefault(newLayer);
            layers.emplace_back(std::move(newLayer));
            if (instance.getSchema()->type == Ent::DataType::array)
                layers.back().arraySize = size();
            checkInvariants();
        }

        Cursor& enterArrayItem(size_t _index)
        {
            checkInvariants();
            Layer newLayer;
            auto& lastLayer = layers.back();
            ENTLIB_DBG_ASSERT(instance.getSchema()->type == Ent::DataType::array);
            instance.enterArrayItem(_index);
            auto* subschema = instance.getSchema();
            if (not isDefault())
            {
                if (not loadInstanceOf(newLayer))
                {
                    if (lastLayer.prefab != nullptr)
                    {
                        lastLayer.prefab->enterArrayItem(_index);
                        newLayer.prefab = lastLayer.prefab;
                        ENTLIB_ASSERT(newLayer.prefab != (void*)0xdddddddddddddddd);
                    }
                }
            }
            if (lastLayer.defaultVal != nullptr
                and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                lastLayer.defaultVal->enterArrayItem(_index);
                newLayer.defaultVal = lastLayer.defaultVal;
            }
            else if (instance.getPropertyDefaultValue()) // If there is property default, use them
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)instance.getPropertyDefaultValue());
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            else // Une type default
            {
                newLayer.defaultStorage = std::make_unique<FileCursor>(
                    subschema, nullptr, (nlohmann::json*)&subschema->defaultValue);
                newLayer.defaultVal = newLayer.defaultStorage.get();
            }
            comitNewLayer(std::move(newLayer));
            return *this;
        }

        char const* getUnionType()
        {
            auto& lastLayer = layers.back();
            if (char const* type = instance.getUnionType())
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
            else if (lastLayer.defaultVal != nullptr)
            {
                if (char const* type3 = lastLayer.defaultVal->getUnionType())
                {
                    return type3;
                }
            }
            return getSchema()->getUnionDefaultTypeName();
        }

        void checkInvariants() const
        {
#ifdef _DEBUG
            ENTLIB_DBG_ASSERT(not layers.empty());
            ENTLIB_DBG_ASSERT(instance.layers.back().schema.base != nullptr);
            //ENTLIB_DBG_ASSERT(
            //    (layers.empty() and instance.additionalPath.empty())
            //    or layers.size() == (instance.additionalPath.size() + 1));
            ENTLIB_DBG_ASSERT(layers.size() == instance.layers.size());
            [[maybe_unused]] auto& lastLayer = layers.back();
            ENTLIB_DBG_ASSERT(
                lastLayer.defaultVal == nullptr
                or lastLayer.defaultVal->getSchema()->type == instance.getSchema()->type);
            if (layers.back().prefab != nullptr)
            {
                ENTLIB_DBG_ASSERT(layers.back().prefab != (void*)0xdddddddddddddddd);
                layers.back().prefab->checkInvariants();
            }
#endif
        }

        Cursor& exit()
        {
#ifdef _DEBUG
            auto layersCount = layers.size();
            ENTLIB_DBG_ASSERT(layers.size() > 0);
            auto& prevLayer = layers[layers.size() - 2];
            auto& prevSchema = instance.layers[instance.layers.size() - 2].schema;
#endif
            checkInvariants();
            auto& lastLayer = layers.back();
            //ENTLIB_DBG_ASSERT(
            //    prevLayer.default == nullptr
            //    or prevLayer.default->schema.back().base->type == prevSchema.base->type);
            instance.exit();
            if (lastLayer.prefab != nullptr and not(lastLayer.prefab->layers.size() < 2))
            {
                lastLayer.prefab->exit();
            }
            if (lastLayer.defaultVal != nullptr and not lastLayer.defaultVal->layers.empty())
            {
                lastLayer.defaultVal->exit();
            }
            layers.pop_back();
#ifdef _DEBUG
            ENTLIB_DBG_ASSERT(layersCount == layers.size() + 1);
            ENTLIB_DBG_ASSERT(
                prevLayer.defaultVal == nullptr
                or prevLayer.defaultVal->getSchema()->type == prevSchema.base->type);
#endif
            checkInvariants();
            return *this;
        }

        DataType getDataType() const
        {
            return instance.getSchema()->type;
        }

        auto getFieldNames() const
        {
            return instance.getSchema()->properties | rah::view::transform([](auto&& field_schema) {
                       return std::get<0>(field_schema).c_str();
                   });
        }

        auto const& getFields() const
        {
            return instance.getSchema()->properties;
        }

        Subschema const* getSchema() const
        {
            return instance.getSchema();
        }

        DataType getMapKeyType() const
        {
            return instance.getSchema()->singularItems->get().linearItems->at(0)->type;
        }

        size_t size() const
        {
            auto& lastLayer = layers.back();
            auto& jsonExplLayer = instance.layers.back();
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
                    return lastLayer.prefab->size();
                }
                else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet())
                {
                    return lastLayer.defaultVal->back()->size();
                }
                else
                {
                    return schema->minItems;
                }
            }
        }

        std::set<char const*, CmpStr> getMapKeysString()
        {
            auto& lastLayer = layers.back();
            std::set<char const*, CmpStr> keys;
            if (lastLayer.prefab != nullptr)
            {
                keys = lastLayer.prefab->getMapKeysString();
            }
            else if (lastLayer.defaultVal != nullptr and lastLayer.defaultVal->isSet()) // If there is default, enter in
            {
                auto* node = lastLayer.defaultVal->back();
                ENTLIB_DBG_ASSERT(node->is_array());
                for (size_t i = 0; i < node->size(); ++i)
                {
                    ENTLIB_DBG_ASSERT(node->is_array());
                    auto key = enterArrayItem(i).enterArrayItem(0llu).getString();
                    exit().exit();
                    ENTLIB_DBG_ASSERT(node->is_array());
                    if (enterArrayItem(i).enterArrayItem(1llu).isNull())
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
            if (instance.isSet())
            {
                auto* node = instance.back();
                ENTLIB_DBG_ASSERT(node->is_array());
                for (size_t i = 0; i < node->size(); ++i)
                {
                    ENTLIB_DBG_ASSERT(node->is_array());
                    auto key = enterArrayItem(i).enterArrayItem(0llu).getString();
                    exit().exit();
                    ENTLIB_DBG_ASSERT(node->is_array());
                    if (enterArrayItem(i).enterArrayItem(1llu).isNull())
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
        bool isNull() const
        {
            auto& lastLayer = layers.back();
            if (instance.isSetInternal())
            {
                return instance.isNull();
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
        std::set<int64_t> getMapKeysInt()
        {
            auto& lastLayer = layers.back();
            std::set<int64_t> keys;
            if (lastLayer.prefab != nullptr)
            {
                keys = lastLayer.prefab->getMapKeysInt();
            }
            if (instance.isSet())
            {
                for (size_t i = 0; i < instance.back()->size(); ++i)
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
        std::set<int64_t> getPrimSetKeysInt()
        {
            auto& lastLayer = layers.back();
            std::set<int64_t> keys;
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
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
        std::set<char const*, CmpStr> getPrimSetKeysString()
        {
            std::set<char const*, CmpStr> keys;
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
                {
                    keys.insert(enterArrayItem(i).getString());
                    exit();
                }
            }
            auto& lastLayer = layers.back();
            if (lastLayer.prefab != nullptr)
            {
                ENTLIB_ASSERT(lastLayer.prefab != (void*)0xdddddddddddddddd);
                keys.merge(lastLayer.prefab->getPrimSetKeysString());
            }
            return keys;
        }

        std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString()
        {
            auto& lastLayer = layers.back();
            std::map<char const*, Subschema const*, CmpStr> keys;
            if (lastLayer.prefab != nullptr)
            {
                keys = lastLayer.prefab->getUnionSetKeysString();
            }
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
                {
                    auto instanceSize = instance.back();
                    auto [unionSchema, unionValue] = instance.enterArrayItem(i).getUnionData();
                    bool const isNull = unionValue != nullptr ? unionValue->is_null() : false;
                    // bool const isNull = instance.enterArrayItem(i).enterUnionData().isNull();
                    // Subschema const* unionSchema = instance.getSchema();
                    // instance.exit();
                    if (isNull)
                    {
                        keys.erase(instance.getUnionType());
                    }
                    else
                    {
                        keys.emplace(instance.getUnionType(), unionSchema);
                    }
                    instance.exit();
                    ENTLIB_ASSERT(instanceSize == instance.back());
                }
            }
            return keys;
        }

        std::set<char const*, CmpStr> getObjectSetKeysString()
        {
            auto& lastLayer = layers.back();
            auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
            std::set<char const*, CmpStr> keys;
            if (lastLayer.prefab != nullptr)
            {
                keys = lastLayer.prefab->getObjectSetKeysString();
            }
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
                {
                    enterArrayItem(i);
                    if (instance.isSet() and instance.back()->count("__removed__"))
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

        std::set<int64_t> getObjectSetKeysInt()
        {
            auto& lastLayer = layers.back();
            auto const& meta = std::get<Ent::Subschema::ArrayMeta>(getSchema()->meta);
            std::set<int64_t> keys;
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
                {
                    enterArrayItem(i);
                    if (instance.isSet() and instance.back()->count("__removed__"))
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

        bool isSet() const;

        double getFloat() const;
        int64_t getInt() const; ///< @pre integer. @brief Get the value as int
        char const* getString() const; ///< @pre Ent::DataType == string. @brief Get the value as string
        bool getBool() const; ///< @pre type==Ent::DataType::boolean. @brief Get the value as bool
        EntityRef getEntityRef()
            const; ///< @pre type==Ent::DataType::entityRef. @brief Get the value as an Entity reference

        void buildPath()
        {
            auto firstNotSet = std::find_if(
                begin(instance.layers), end(instance.layers), [](FileCursor::Layer const& l) {
                    return l.values == nullptr;
                });
            ENTLIB_ASSERT(firstNotSet != begin(instance.layers));
            auto firstNotSetIdx = std::distance(begin(instance.layers), firstNotSet);
            auto lastSet = firstNotSet;
            --lastSet;
            auto endIter = end(instance.layers);
            for (; firstNotSet != endIter; ++lastSet, ++firstNotSet, ++firstNotSetIdx)
            {
                size_t arraySize = layers[firstNotSetIdx - 1].arraySize;
                instance.setLayer(*lastSet, *firstNotSet, arraySize);
                ENTLIB_ASSERT(firstNotSet->values != nullptr);
            }
            // ENTLIB_ASSERT(instance.back() != nullptr);
        }
        void setSize(size_t size)
        {
            buildPath();
            instance.setSize(size);
        }

        void setFloat(double value)
        {
            buildPath();
            instance.setFloat(value);
        }
        void setInt(int64_t value)
        {
            buildPath();
            instance.setInt(value);
        }
        void setString(char const* value)
        {
            ENTLIB_ASSERT(value != nullptr);
            buildPath();
            instance.setString(value);
        }
        void setBool(bool value)
        {
            buildPath();
            instance.setBool(value);
        }
        void setEntityRef(EntityRef const& value)
        {
            buildPath();
            instance.setEntityRef(value);
        }
        void setUnionType(char const* type)
        {
            buildPath();
            instance.setUnionType(type);
        }
        bool countPrimSetKey(char const* key)
        {
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
                {
                    bool const equal = strcmp(enterArrayItem(i).getString(), key) == 0;
                    exit();
                    if (equal)
                    {
                        return true;
                    }
                }
            }
            auto& lastLayer = layers.back();
            if (lastLayer.prefab != nullptr)
            {
                return lastLayer.prefab->countPrimSetKey(key);
            }
            return false;
        }
        bool countPrimSetKey(int64_t key)
        {
            if (instance.isSet())
            {
                for (size_t i = 0; i < size(); ++i)
                {
                    bool const equal = enterArrayItem(i).getInt() == key;
                    exit();
                    if (equal)
                    {
                        return true;
                    }
                }
            }
            auto& lastLayer = layers.back();
            if (lastLayer.prefab != nullptr)
            {
                return lastLayer.prefab->countPrimSetKey(key);
            }
            return false;
        }
        void insertPrimSetKey(char const* key)
        {
            if (not countPrimSetKey(key))
            {
                buildPath();
                instance.pushBack(key);
            }
        }
        void insertPrimSetKey(int64_t key)
        {
            if (not countPrimSetKey(key))
            {
                buildPath();
                instance.pushBack(key);
            }
        }
    };
} // namespace Ent
