#pragma once

#include <variant>
#include <ciso646>

#include "FileCursor.h"

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../EntityLib.h"
#include "../Tools.h"
#pragma push_macro("RAH_NAMESPACE")
#undef RAH_NAMESPACE
#define RAH_NAMESPACE entrah
#include "../external/rah.hpp"
#pragma pop_macro("RAH_NAMESPACE")
#pragma warning(pop)

namespace Ent
{
    struct ENTLIB_DLLEXPORT Cursor
    {
    public:
        using Key = std::variant<std::string, size_t>;

        Cursor();
        Cursor(Cursor const&) = delete;
        Cursor& operator=(Cursor const&) = delete;
        Cursor(Cursor&&) = delete;
        Cursor& operator=(Cursor&&) = delete;
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

        char const* getInstanceOf();

        char const* getUnionType();
        size_t getUnionTypeIndex();

        void checkInvariants() const;

        Cursor& exit();

        DataType getDataType() const;

        auto getFieldNames() const
        {
            return m_instance.getSchema()->properties
                   | entrah::view::transform([](auto&& field_schema)
                                             { return std::get<0>(field_schema).c_str(); });
        }

        Subschema const* getSchema() const;

        char const* getTypeName() const;

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

        bool mapContains(char const* _key);
        bool mapContains(int64_t _key);
        bool primSetContains(char const* _key);
        bool primSetContains(int64_t _key);
        bool unionSetContains(char const* _key);
        bool objectSetContains(char const* _key);
        bool objectSetContains(int64_t _key);

        bool isSet() const;

        template <typename V>
        V get() const;
        double getFloat() const;
        int64_t getInt() const; ///< @pre integer. @brief Get the value as int
        char const* getString() const; ///< @pre Ent::DataType == string. @brief Get the value as string
        bool getBool() const; ///< @pre type==Ent::DataType::boolean. @brief Get the value as bool
        /// @pre type==Ent::DataType::entityRef. @brief Get the value as an Entity reference
        EntityRef getEntityRef() const;

        void setSize(size_t _size);

        void setFloat(double _value);
        void setInt(int64_t _value);
        void setString(char const* _value);
        void setBool(bool _value);
        void setEntityRef(EntityRef const& _value);
        void setUnionType(char const* _type);
        // Build path but not set any value. Usefull for UnionSet items
        void buildPath();
        bool countPrimSetKey(char const* _key);
        bool countPrimSetKey(int64_t _key);
        void insertPrimSetKey(char const* _key);
        void insertPrimSetKey(int64_t _key);

        nlohmann::json* GetRawValue();

        Cursor* getPrefab();

    private:
        struct Layer
        {
            Cursor* prefab = nullptr;
            std::unique_ptr<Cursor> prefabsStorage;
            int defaultVal = 1; // 1 == undefined
            FileCursor defaultStorage;
            size_t arraySize = 0;
            bool isDefault = false; // Cache for isDefault()
            void setDefault(
                Ent::Subschema const* _schema, char const* _filePath, nlohmann::json const* _document);
            void clear();
            FileCursor* getDefault();
            FileCursor const* getDefault() const;
        };
        void _pushDefault(Layer& _newLayer) const;
        bool _loadInstanceOf(Layer& _newLayer);
        void _comitNewLayer(Layer& _newLayer);
        void _validNewLayer();
        Layer& _allocLayer();
        Layer& _getLastLayer();
        Layer const& _getLastLayer() const;
        void _buildPath();
        template <typename K, typename E>
        bool _countPrimSetKeyImpl(K _key, E&& _isEqual);
        template <typename E>
        Cursor& _enterItem(E&& _enter);

        EntityLib* m_entityLib = nullptr;
        FileCursor m_instance;
        std::vector<Layer> m_layers;
        size_t m_layerCount = 0;
    };

    inline Cursor* Cursor::getPrefab()
    {
        return _getLastLayer().prefab;
    }
} // namespace Ent
