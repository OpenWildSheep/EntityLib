#pragma once

#include "../EntityLib.h"
#include <variant>
#include <ciso646>
#include "../Tools.h"
#include "FileCursor.h"

#pragma push_macro("RAH_NAMESPACE")
#undef RAH_NAMESPACE
#define RAH_NAMESPACE rah
#include "../external/rah.hpp"
#pragma pop_macro("RAH_NAMESPACE")

namespace Ent
{
    struct ENTLIB_DLLEXPORT Cursor
    {
    private:
        using Key = std::variant<std::string, size_t>;
        using NodeRef = std::vector<Key>;
        struct Layer
        {
            Cursor* prefab = nullptr;
            std::unique_ptr<Cursor> prefabsStorage;
            int defaultVal = 1; // 1 == undefined
            FileCursor defaultStorage;
            size_t arraySize = 0;
            bool isDefault = false; // Cache for isDefault()
            void setDefault(
                Ent::Subschema const* _schema, char const* filePath, nlohmann::json* _document);
            void clear();
            FileCursor* getDefault();
            FileCursor const* getDefault() const;
        };

    public:
        Cursor();
        Cursor(Cursor const&) = delete;
        Cursor& operator=(Cursor const&) = delete;
        Cursor(
            EntityLib* _entityLib,
            Ent::Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc);

        void init(
            EntityLib* _entityLib,
            Ent::Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc);

        void init(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename);

        Cursor(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename);

        void save(char const* _filename = nullptr) const;

        bool isDefaultImpl() const;

        bool isDefault() const;

        Cursor& enterObjectField(char const* _field, SubschemaRef const* _fieldRef = nullptr);

        Cursor& enterUnionData(char const* type = nullptr);

        Cursor& enterUnionSetItem(char const* _field, Subschema const* _dataSchema = nullptr);

        Cursor& enterObjectSetItem(char const* _field);

        Cursor& enterObjectSetItem(int64_t _field);

        Cursor& enterMapItem(char const* _field);

        Cursor& enterMapItem(int64_t _field);

        Cursor& enterArrayItem(size_t _index);

        char const* getUnionType();

        void checkInvariants() const;

        Cursor& exit();

        DataType getDataType() const;

        auto getFieldNames() const
        {
            return m_instance.getSchema()->properties | rah::view::transform([](auto&& field_schema) {
                       return std::get<0>(field_schema).c_str();
                   });
        }

        std::unordered_map<std::string, SubschemaRef> const& getFields() const;

        Subschema const* getSchema() const;

        DataType getMapKeyType() const;

        size_t size();
        bool contains(Key const& _key);
        size_t arraySize();
        bool empty();

        bool isNull() const;
        std::set<char const*, CmpStr> getMapKeysString();
        std::set<int64_t> getMapKeysInt();
        std::set<int64_t> getPrimSetKeysInt();
        std::set<char const*, CmpStr> getPrimSetKeysString();
        std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString();
        std::set<char const*, CmpStr> getObjectSetKeysString();
        std::set<int64_t> getObjectSetKeysInt();

        bool getMapContains(char const*);
        bool getMapContains(int64_t);
        bool getPrimSetContains(char const*);
        bool getPrimSetContains(int64_t);
        bool getUnionSetContains(char const*);
        bool getObjectSetContains(char const*);
        bool getObjectSetContains(int64_t);

        bool isSet() const;

        double getFloat() const;
        int64_t getInt() const; ///< @pre integer. @brief Get the value as int
        char const* getString() const; ///< @pre Ent::DataType == string. @brief Get the value as string
        bool getBool() const; ///< @pre type==Ent::DataType::boolean. @brief Get the value as bool
        /// @pre type==Ent::DataType::entityRef. @brief Get the value as an Entity reference
        EntityRef getEntityRef() const;

        void setSize(size_t size);

        void setFloat(double value);
        void setInt(int64_t value);
        void setString(char const* value);
        void setBool(bool value);
        void setEntityRef(EntityRef const& value);
        void setUnionType(char const* type);
        bool countPrimSetKey(char const* key);
        bool countPrimSetKey(int64_t key);
        void insertPrimSetKey(char const* key);
        void insertPrimSetKey(int64_t key);

    private:
        void _pushDefault(Layer& newLayer) const;
        bool _loadInstanceOf(Layer& newLayer);
        void _comitNewLayer(Layer& newLayer);
        void _validNewLayer();
        Layer& _allocLayer();
        Layer& _getLastLayer();
        Layer const& _getLastLayer() const;
        void _buildPath();

        EntityLib* m_entityLib = nullptr;
        FileCursor m_instance;
        std::vector<Layer> m_layers;
        size_t m_layerCount = 0;
    };
} // namespace Ent
