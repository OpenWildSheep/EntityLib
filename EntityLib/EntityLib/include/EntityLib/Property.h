#pragma once
#include "../../PropImpl.h"
#include "../EntityLib.h"

namespace Ent
{
    struct ENTLIB_DLLEXPORT Property
    {
    public:
        using Key = std::variant<std::string, size_t>;

        Property() = default;
        Property(Property const& _other)
            : m_self(_other.m_self->sharedFromThis())
        {
        }
        Property& operator=(Property const& _other)
        {
            Property copy(_other);
            std::swap(copy, *this);
            return *this;
        }
        Property(Property&& _other) noexcept = default;
        Property& operator=(Property&& _other) noexcept = default;
        Property(EntityLib* _entityLib, Ent::Subschema const* _schema, char const* _filename)
            : m_self(_entityLib->newPropImpl(nullptr, _schema, _filename, nullptr))
        {
        }
        Property(
            EntityLib* _entityLib,
            Ent::Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc)
            : m_self(_entityLib->newPropImpl(nullptr, _schema, _filename, _doc))
        {
        }

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr)
        {
            getPimpl().save(_filename);
        }

        /// @brief The Node is default if no values are set inside
        bool isDefault()
        {
            return getPimpl().isDefault();
        }

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        [[nodiscard]] Property enterObjectField(
            char const* _field, ///< field to enter in
            SubschemaRef const* _fieldRef = nullptr ///< SubschemaRef of the field (For performance)
        )
        {
            return Property(getPimpl().enterObjectField(_field, _fieldRef));
        }
        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] Property enterUnionData(
            char const* _type = nullptr ///< type of the internal data of the union
        )
        {
            return Property{getPimpl().enterUnionData(_type)};
        }
        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] Property enterUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        )
        {
            return Property{getPimpl().enterUnionSetItem(_type, _dataSchema)};
        }
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] Property enterObjectSetItem(char const* _key ///< Key of the object
        )
        {
            return Property{getPimpl().enterObjectSetItem(_key)};
        }
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] Property enterObjectSetItem(int64_t _key ///< Key of the object
        )
        {
            return Property{getPimpl().enterObjectSetItem(_key)};
        }
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] Property enterMapItem(char const* _key ///< Key of the value
        )
        {
            return Property{getPimpl().enterMapItem(_key)};
        }
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] Property enterMapItem(int64_t _field ///< Key of the value
        )
        {
            return Property{getPimpl().enterMapItem(_field)};
        }
        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        [[nodiscard]] Property enterArrayItem(size_t _index ///< index of the targeted element
        )
        {
            return Property{getPimpl().enterArrayItem(_index)};
        }
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        char const* getInstanceOf()
        {
            return getPimpl().getInstanceOf();
        }

        /// @brief Set the InstanceOf field which point the prefab of the object
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void setInstanceOf(char const* _instanceOf)
        {
            return getPimpl().setInstanceOf(_instanceOf);
        }

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType()
        {
            return getPimpl().getUnionType();
        }
        /// @return The index of the type of the Union
        /// @pre It is a Union
        size_t getUnionTypeIndex()
        {
            return getPimpl().getUnionTypeIndex();
        }
        DataType getDataType() const ///< Get the DataType of a Node
        {
            return getPimpl().getDataType();
        }
        Subschema const* getSchema() const ///< Get the Schema of the curent Node
        {
            return getPimpl().getSchema();
        }
        char const* getTypeName() const ///< Get the Schema name of the curent Node
        {
            return getPimpl().getTypeName();
        }

        DataType getMapKeyType() const ///< @pre Map @brief Get the key type curent Map
        {
            return getPimpl().getMapKeyType();
        }
        DataType getObjectSetKeyType() const ///< @pre ObjectSet @brief Get the key type curent ObjectSet
        {
            return getPimpl().getObjectSetKeyType();
        }
        size_t size() ///< @return the size the this Node whatever it is.
        {
            return getPimpl().size();
        }
        bool contains(Key const& _key) ///< @pre map/set. @return true if it contains _key.
        {
            return getPimpl().contains(_key);
        }
        size_t arraySize() ///< @return size of a simple array
        {
            return getPimpl().arraySize();
        }
        bool empty() ///< Check if size() == 0
        {
            return getPimpl().empty();
        }
        bool isNull() const ///< @brief check if this Node is json null
        {
            return getPimpl().isNull();
        }

        std::set<char const*, CmpStr> getMapKeysString() ///< Get map keys as strings
        {
            return getPimpl().getMapKeysString();
        }
        std::set<int64_t> getMapKeysInt() ///< Get map keys as ints
        {
            return getPimpl().getMapKeysInt();
        }
        std::set<int64_t> getPrimSetKeysInt() ///< Get set elements as ints
        {
            return getPimpl().getPrimSetKeysInt();
        }
        std::set<char const*, CmpStr> getPrimSetKeysString() ///< Get set elements as strings
        {
            return getPimpl().getPrimSetKeysString();
        }
        /// Get UnionSet keys as strings
        std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString()
        {
            return getPimpl().getUnionSetKeysString();
        }
        std::set<char const*, CmpStr> getObjectSetKeysString() ///< Get keys of objects as strings
        {
            return getPimpl().getObjectSetKeysString();
        }
        std::set<int64_t> getObjectSetKeysInt() ///< Get keys of objects as ints
        {
            return getPimpl().getObjectSetKeysInt();
        }

        bool mapContains(char const* _key) ///< Check if the map contains this _key
        {
            return getPimpl().mapContains(_key);
        }
        bool mapContains(int64_t _key) ///< Check if the map contains this _key
        {
            return getPimpl().mapContains(_key);
        }
        bool primSetContains(char const* _key) ///< Check if the set contains this _key
        {
            return getPimpl().primSetContains(_key);
        }
        bool primSetContains(int64_t _key) ///< Check if the set contains this _key
        {
            return getPimpl().primSetContains(_key);
        }
        bool unionSetContains(char const* _key) ///< Check if the UnionSet contains this _key
        {
            return getPimpl().unionSetContains(_key);
        }
        bool objectSetContains(char const* _key) ///< Check if the ObjectSet contains this _key
        {
            return getPimpl().objectSetContains(_key);
        }
        bool objectSetContains(int64_t _key) ///< Check if the ObjectSet contains this _key
        {
            return getPimpl().objectSetContains(_key);
        }

        bool isSet() const ///< Check if the Node is set in the instance
        {
            return getPimpl().isSet();
        }

        template <typename V>
        V get() const ///< @pre Node is of type V. @brief Get the value in the given V type
        {
            return getPimpl().get();
        }
        double getFloat() const ///< @pre type==number. @brief Get the value as double
        {
            return getPimpl().getFloat();
        }
        int64_t getInt() const ///< @pre type==integer. @brief Get the value as int
        {
            return getPimpl().getInt();
        }
        char const* getString() const ///< @pre type==string. @brief Get the value as string
        {
            return getPimpl().getString();
        }
        bool getBool() const ///< @pre type==boolean. @brief Get the value as bool
        {
            return getPimpl().getBool();
        }
        EntityRef getEntityRef() const /// @pre type==entityRef. @brief Get the value as an Entity reference
        {
            return getPimpl().getEntityRef();
        }

        void setSize(size_t _size) ///< @pre type==array. @brief Set the size of the array.
        {
            return getPimpl().setSize(_size);
        }

        void setFloat(double _value) ///< @pre type==number. @brief Set _value in the instance
        {
            return getPimpl().setFloat(_value);
        }
        void setInt(int64_t _value) ///< @pre type==integer. @brief Set _value in the instance
        {
            return getPimpl().setInt(_value);
        }
        void setString(char const* _value) ///< @pre type==string. @brief Set _value in the instance
        {
            return getPimpl().setString(_value);
        }
        void setBool(bool _value) ///< @pre type==bool. @brief Set _value in the instance
        {
            return getPimpl().setBool(_value);
        }
        void setEntityRef(EntityRef const& _value) ///< @pre type==entityref. @brief Set _value in the instance
        {
            return getPimpl().setEntityRef(_value);
        }
        void setUnionType(char const* _type) ///< @pre type==union. @brief Set _value in the instance
        {
            return getPimpl().setUnionType(_type);
        }

        void buildPath() ///< Build json path but not set any value. Usefull for UnionSet items
        {
            return getPimpl().buildPath();
        }
        void insertPrimSetKey(char const* _key) ///< Insert _key in the set (or do nothing if already in)
        {
            return getPimpl().insertPrimSetKey(_key);
        }
        void insertPrimSetKey(int64_t _key) ///< Insert _key in the set (or do nothing if already in)
        {
            return getPimpl().insertPrimSetKey(_key);
        }

        nlohmann::json const* getRawJson() ///< Get the underlying json node of the instance
        {
            return getPimpl().getRawJson();
        }

        /// @brief Check if the Property is not nullptr inside (have to be true to call any method)
        bool hasValue() const
        {
            return m_self != nullptr;
        }

        /// @brief Check if the Property has a "InstanceOf" declared and not empty
        bool hasPrefab() const
        {
            return m_self->getPrefab() != nullptr;
        }

        Property getPrefab() const ///< Get the prefab of the Property
        {
            if (auto prefab = m_self->getPrefab())
            {
                return Property(prefab->sharedFromThis());
            }
            else
            {
                return Property();
            }
        }

        Property getParent() const ///< Get the Property which own this one
        {
            return m_self->getParent();
        }

    private:
        Property(PropImplPtr _prop)
            : m_self(std::move(_prop))
        {
        }

        PropImpl& getPimpl()
        {
            return *m_self;
        }
        PropImpl const& getPimpl() const
        {
            return *m_self;
        }

        PropImplPtr m_self{};
    };
} // namespace Ent
