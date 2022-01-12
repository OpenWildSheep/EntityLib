#pragma once

#include <variant>
#include <ciso646>

#include "FileCursor.h"

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../EntityLib.h"
#include "../Tools.h"
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
            Ent::Subschema const* _schema, ///< Schema of the file to load
            char const* _filename,
            nlohmann::json* _doc);

        Cursor(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename);

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const;

        /// @brief The Node is default if no values are set inside
        bool isDefault() const;

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        Cursor& enterObjectField(
            char const* _field, ///< field to enter in
            SubschemaRef const* _fieldRef = nullptr ///< SubschemaRef of the field (For performance)
        );

        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        Cursor& enterUnionData(
            char const* _type = nullptr ///< type of the internal data of the union
        );

        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        Cursor& enterUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        );

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        Cursor& enterObjectSetItem(char const* _key ///< Key of the object
        );

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        Cursor& enterObjectSetItem(int64_t _key ///< Key of the object
        );

        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        Cursor& enterMapItem(char const* _key ///< Key of the value
        );

        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        Cursor& enterMapItem(int64_t _field ///< Key of the value
        );

        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        Cursor& enterArrayItem(size_t _index ///< index of the targeted element
        );

        /// @return The "InstanceOf" field. Or nullptr if there is no.
        /// @pre It is an Object
        char const* getInstanceOf();

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType();

        /// @return The index of the type of the Union
        /// @pre It is a Union
        size_t getUnionTypeIndex();

        /// Used after "enter..." function. From an item, get back to the parent container.
        Cursor& exit();

        DataType getDataType() const; ///< Get the DataType of a Node

        Subschema const* getSchema() const; ///< Get the Schema of the curent Node

        char const* getTypeName() const; ///< Get the Schema name of the curent Node

        DataType getMapKeyType() const; ///< @pre Map/Set @brief Get the key type curent Map/Set

        size_t size(); ///< @return the size the this Node whatever it is.
        bool contains(Key const& _key); ///< @pre map/set. @return true if it contains _key.
        size_t arraySize(); ///< @return size of a simple array
        bool empty(); ///< Check if size() == 0
        bool isNull() const; ///< @brief check if this Node is json null

        std::set<char const*, CmpStr> getMapKeysString(); ///< Get map keys as strings
        std::set<int64_t> getMapKeysInt(); ///< Get map keys as ints
        std::set<int64_t> getPrimSetKeysInt(); ///< Get set elements as ints
        std::set<char const*, CmpStr> getPrimSetKeysString(); ///< Get set elements as strings
        /// Get UnionSet keys as strings
        std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString();
        std::set<char const*, CmpStr> getObjectSetKeysString(); ///< Get keys of objects as strings
        std::set<int64_t> getObjectSetKeysInt(); ///< Get keys of objects as ints

        bool mapContains(char const* _key); ///< Check if the map contains this _key
        bool mapContains(int64_t _key); ///< Check if the map contains this _key
        bool primSetContains(char const* _key); ///< Check if the set contains this _key
        bool primSetContains(int64_t _key); ///< Check if the set contains this _key
        bool unionSetContains(char const* _key); ///< Check if the UnionSet contains this _key
        bool objectSetContains(char const* _key); ///< Check if the ObjectSet contains this _key
        bool objectSetContains(int64_t _key); ///< Check if the ObjectSet contains this _key

        bool isSet() const; ///< Check if the Node is set in the instance

        template <typename V>
        V get() const; ///< @pre Node is of type V. @brief Get the value in the given V type
        double getFloat() const; ///< @pre type==number. @brief Get the value as double
        int64_t getInt() const; ///< @pre type==integer. @brief Get the value as int
        char const* getString() const; ///< @pre type==string. @brief Get the value as string
        bool getBool() const; ///< @pre type==boolean. @brief Get the value as bool
        EntityRef getEntityRef() const; /// @pre type==entityRef. @brief Get the value as an Entity reference

        void setSize(size_t _size); ///< @pre type==array. @brief Set the size of the array.

        void setFloat(double _value); ///< @pre type==number. @brief Set _value in the instance
        void setInt(int64_t _value); ///< @pre type==integer. @brief Set _value in the instance
        void setString(char const* _value); ///< @pre type==string. @brief Set _value in the instance
        void setBool(bool _value); ///< @pre type==bool. @brief Set _value in the instance
        void setEntityRef(EntityRef const& _value); ///< @pre type==entityref. @brief Set _value in the instance
        void setUnionType(char const* _type); ///< @pre type==union. @brief Set _value in the instance

        void buildPath(); ///< Build json path but not set any value. Usefull for UnionSet items
        void insertPrimSetKey(char const* _key); ///< Insert _key in the set (or do nothing if already in)
        void insertPrimSetKey(int64_t _key); ///< Insert _key in the set (or do nothing if already in)

        nlohmann::json const* _getRawJson(); ///< Get the underlying json node of the instance

        Cursor* getPrefab(); ///< Get the Cursor of the prefab

    private:
        struct Layer
        {
            Cursor* prefab = nullptr;
            std::unique_ptr<Cursor> prefabsStorage;
            /// @brief offset of the defaultValue in m_layers
            /// @remark 0 = last, -1 = last - 1, 1 = undefined
            int defaultVal = 1;
            FileCursor defaultStorage;
            size_t arraySize = 0;
            void setDefault(
                Ent::Subschema const* _schema, char const* _filePath, nlohmann::json const* _document);
            void clear();
            FileCursor* getDefault();
            FileCursor const* getDefault() const;
        };
        bool _loadInstanceOf(Layer& _newLayer);
        void _comitNewLayer();
        void _validNewLayer();
        Layer& _allocLayer();
        Layer& _getLastLayer();
        Layer const& _getLastLayer() const;
        void _buildPath();
        template <typename K, typename E>
        bool _countPrimSetKeyImpl(K _key, E&& _isEqual);
        template <typename E>
        Cursor& _enterItem(E&& _enter);
        void _init(
            EntityLib* _entityLib,
            Ent::Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc);
        void _init(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename);
        void _checkInvariants() const;

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
