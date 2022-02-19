#pragma once
#include "Cursor.h"
#include "../EntityLib.h"

namespace Ent
{
    struct ENTLIB_DLLEXPORT HandlerRW
    {
    public:
        using Key = std::variant<std::string, size_t>;

        HandlerRW() = default;
        HandlerRW(HandlerRW const&) = delete;
        HandlerRW& operator=(HandlerRW const&) = delete;
        HandlerRW(HandlerRW&&) = default;
        HandlerRW& operator=(HandlerRW&&) = default;
        HandlerRW(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
        {
            m_self = _entityLib->newLayer(nullptr, _schema, _filename, nullptr);
        }
        HandlerRW(
            EntityLib* _entityLib,
            Ent::Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc)
        {
            m_self = _entityLib->newLayer(nullptr, _schema, _filename, _doc);
        }

        void clear()
        {
            getLayer().clear();
        }

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr)
        {
            getLayer().save(_filename);
        }

        /// @brief The Node is default if no values are set inside
        bool isDefault()
        {
            return getLayer().isDefault();
        }

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        [[nodiscard]] HandlerRW enterObjectField(
            char const* _field, ///< field to enter in
            SubschemaRef const* _fieldRef = nullptr ///< SubschemaRef of the field (For performance)
        )
        {
            return HandlerRW(getLayer().enterObjectField(_field, _fieldRef));
        }
        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] HandlerRW enterUnionData(
            char const* _type = nullptr ///< type of the internal data of the union
        )
        {
            return HandlerRW{getLayer().enterUnionData(_type)};
        }
        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] HandlerRW enterUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        )
        {
            return HandlerRW{getLayer().enterUnionSetItem(_type, _dataSchema)};
        }
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] HandlerRW enterObjectSetItem(char const* _key ///< Key of the object
        )
        {
            return HandlerRW{getLayer().enterObjectSetItem(_key)};
        }
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] HandlerRW enterObjectSetItem(int64_t _key ///< Key of the object
        )
        {
            return HandlerRW{getLayer().enterObjectSetItem(_key)};
        }
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] HandlerRW enterMapItem(char const* _key ///< Key of the value
        )
        {
            return HandlerRW{getLayer().enterMapItem(_key)};
        }
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] HandlerRW enterMapItem(int64_t _field ///< Key of the value
        )
        {
            return HandlerRW{getLayer().enterMapItem(_field)};
        }
        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        [[nodiscard]] HandlerRW enterArrayItem(size_t _index ///< index of the targeted element
        )
        {
            return HandlerRW{getLayer().enterArrayItem(_index)};
        }
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        char const* getInstanceOf()
        {
            return getLayer().getInstanceOf();
        }

        /// @brief Set the InstanceOf field which point the prefab of the object
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void setInstanceOf(char const* _instanceOf)
        {
            return getLayer().setInstanceOf(_instanceOf);
        }

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType()
        {
            return getLayer().getUnionType();
        }
        /// @return The index of the type of the Union
        /// @pre It is a Union
        size_t getUnionTypeIndex()
        {
            return getLayer().getUnionTypeIndex();
        }
        DataType getDataType() const ///< Get the DataType of a Node
        {
            return getLayer().getDataType();
        }
        Subschema const* getSchema() const ///< Get the Schema of the curent Node
        {
            return getLayer().getSchema();
        }
        char const* getTypeName() const ///< Get the Schema name of the curent Node
        {
            return getLayer().getTypeName();
        }

        DataType getMapKeyType() const ///< @pre Map @brief Get the key type curent Map
        {
            return getLayer().getMapKeyType();
        }
        DataType getObjectSetKeyType() const ///< @pre ObjectSet @brief Get the key type curent ObjectSet
        {
            return getLayer().getObjectSetKeyType();
        }
        size_t size() ///< @return the size the this Node whatever it is.
        {
            return getLayer().size();
        }
        bool contains([[maybe_unused]] Key const& _key) ///< @pre map/set. @return true if it contains _key.
        {
            return getLayer().size();
        }
        size_t arraySize() ///< @return size of a simple array
        {
            return getLayer().arraySize();
        }
        bool empty() ///< Check if size() == 0
        {
            return getLayer().empty();
        }
        bool isNull() const ///< @brief check if this Node is json null
        {
            return getLayer().isNull();
        }

        std::set<char const*, CmpStr> getMapKeysString() ///< Get map keys as strings
        {
            return getLayer().getMapKeysString();
        }
        std::set<int64_t> getMapKeysInt() ///< Get map keys as ints
        {
            return getLayer().getMapKeysInt();
        }
        std::set<int64_t> getPrimSetKeysInt() ///< Get set elements as ints
        {
            return getLayer().getPrimSetKeysInt();
        }
        std::set<char const*, CmpStr> getPrimSetKeysString() ///< Get set elements as strings
        {
            return getLayer().getPrimSetKeysString();
        }
        /// Get UnionSet keys as strings
        std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString()
        {
            return getLayer().getUnionSetKeysString();
        }
        std::set<char const*, CmpStr> getObjectSetKeysString() ///< Get keys of objects as strings
        {
            return getLayer().getObjectSetKeysString();
        }
        std::set<int64_t> getObjectSetKeysInt() ///< Get keys of objects as ints
        {
            return getLayer().getObjectSetKeysInt();
        }

        bool mapContains(char const* _key) ///< Check if the map contains this _key
        {
            return getLayer().mapContains(_key);
        }
        bool mapContains(int64_t _key) ///< Check if the map contains this _key
        {
            return getLayer().mapContains(_key);
        }
        bool primSetContains(char const* _key) ///< Check if the set contains this _key
        {
            return getLayer().primSetContains(_key);
        }
        bool primSetContains(int64_t _key) ///< Check if the set contains this _key
        {
            return getLayer().primSetContains(_key);
        }
        bool unionSetContains(char const* _key) ///< Check if the UnionSet contains this _key
        {
            return getLayer().unionSetContains(_key);
        }
        bool objectSetContains(char const* _key) ///< Check if the ObjectSet contains this _key
        {
            return getLayer().objectSetContains(_key);
        }
        bool objectSetContains(int64_t _key) ///< Check if the ObjectSet contains this _key
        {
            return getLayer().objectSetContains(_key);
        }

        bool isSet() const ///< Check if the Node is set in the instance
        {
            return getLayer().isSet();
        }

        template <typename V>
        V get() const ///< @pre Node is of type V. @brief Get the value in the given V type
        {
            return getLayer().get();
        }
        double getFloat() const ///< @pre type==number. @brief Get the value as double
        {
            return getLayer().getFloat();
        }
        int64_t getInt() const ///< @pre type==integer. @brief Get the value as int
        {
            return getLayer().getInt();
        }
        char const* getString() const ///< @pre type==string. @brief Get the value as string
        {
            return getLayer().getString();
        }
        bool getBool() const ///< @pre type==boolean. @brief Get the value as bool
        {
            return getLayer().getBool();
        }
        EntityRef getEntityRef() const /// @pre type==entityRef. @brief Get the value as an Entity reference
        {
            return getLayer().getEntityRef();
        }

        void setSize(size_t _size) ///< @pre type==array. @brief Set the size of the array.
        {
            return getLayer().setSize(_size);
        }

        void setFloat(double _value) ///< @pre type==number. @brief Set _value in the instance
        {
            return getLayer().setFloat(_value);
        }
        void setInt(int64_t _value) ///< @pre type==integer. @brief Set _value in the instance
        {
            return getLayer().setInt(_value);
        }
        void setString(char const* _value) ///< @pre type==string. @brief Set _value in the instance
        {
            return getLayer().setString(_value);
        }
        void setBool(bool _value) ///< @pre type==bool. @brief Set _value in the instance
        {
            return getLayer().setBool(_value);
        }
        void setEntityRef(EntityRef const& _value) ///< @pre type==entityref. @brief Set _value in the instance
        {
            return getLayer().setEntityRef(_value);
        }
        void setUnionType(char const* _type) ///< @pre type==union. @brief Set _value in the instance
        {
            return getLayer().setUnionType(_type);
        }

        void buildPath() ///< Build json path but not set any value. Usefull for UnionSet items
        {
            return getLayer().buildPath();
        }
        void insertPrimSetKey(char const* _key) ///< Insert _key in the set (or do nothing if already in)
        {
            return getLayer().insertPrimSetKey(_key);
        }
        void insertPrimSetKey(int64_t _key) ///< Insert _key in the set (or do nothing if already in)
        {
            return getLayer().insertPrimSetKey(_key);
        }

        nlohmann::json const* _getRawJson() ///< Get the underlying json node of the instance
        {
            return getLayer()._getRawJson();
        }

        Layer* getPrefab() ///< Get the Cursor of the prefab
        {
            return getLayer().getPrefab();
        }

        Layer& getLayer()
        {
            return *m_self;
        }

        Layer const& getLayer() const
        {
            return *m_self;
        }

    private:
        HandlerRW(LayerSharedPtr _layer)
            : m_self(std::move(_layer))
        {
        }

        LayerSharedPtr m_self;
    };
} // namespace Ent
