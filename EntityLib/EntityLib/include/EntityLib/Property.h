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
        Property(PropImplPtr _prop)
            : m_self(std::move(_prop))
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
        Property(EntityLib* _entityLib, Subschema const* _schema, char const* _filename)
            : m_self(_entityLib->newPropImpl(nullptr, _schema, _filename, nullptr))
        {
        }
        Property(
            EntityLib* _entityLib, Subschema const* _schema, char const* _filename, nlohmann::json* _doc)
            : m_self(_entityLib->newPropImpl(nullptr, _schema, _filename, _doc))
        {
        }

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const
        {
            getPimpl().save(_filename);
        }

        /// @brief The Node is default if no values are set inside
        bool isDefault() const
        {
            return getPimpl().isDefault();
        }

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        [[nodiscard]] Property getObjectField(
            char const* _field, ///< field to enter in
            SubschemaRef const* _fieldRef = nullptr ///< SubschemaRef of the field (For performance)
        ) const
        {
            return Property(getPimpl().getObjectField(_field, _fieldRef));
        }
        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] Property getUnionData(
            char const* _type = nullptr ///< type of the internal data of the union
        ) const
        {
            return Property{getPimpl().getUnionData(_type)};
        }
        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] Property getUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        ) const
        {
            return Property{getPimpl().getUnionSetItem(_type, _dataSchema)};
        }
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] Property getObjectSetItem(char const* _key ///< Key of the object
        ) const
        {
            return Property{getPimpl().getObjectSetItem(_key)};
        }
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] Property getObjectSetItem(int64_t _key ///< Key of the object
        ) const
        {
            return Property{getPimpl().getObjectSetItem(_key)};
        }
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] Property getMapItem(char const* _key ///< Key of the value
        ) const
        {
            return Property{getPimpl().getMapItem(_key)};
        }
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] Property getMapItem(int64_t _field ///< Key of the value
        ) const
        {
            return Property{getPimpl().getMapItem(_field)};
        }
        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        [[nodiscard]] Property getArrayItem(size_t _index ///< index of the targeted element
        ) const
        {
            return Property{getPimpl().getArrayItem(_index)};
        }
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        char const* getInstanceOf() const
        {
            return getPimpl().getInstanceOf();
        }

        /// @brief Set the prefab (and reset all overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void resetInstanceOf(char const* _instanceOf) const
        {
            return getPimpl().resetInstanceOf(_instanceOf);
        }

        /// @brief Set the prefab (and reset keep overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void changeInstanceOf(char const* _instanceOf) const
        {
            return getPimpl().changeInstanceOf(_instanceOf);
        }

        Property makeInstanceOf() const
        {
            return Property{getPimpl().makeInstanceOf()};
        }

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType() const
        {
            return getPimpl().getUnionType();
        }
        /// @return The index of the type of the Union
        /// @pre It is a Union
        size_t getUnionTypeIndex() const
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
        size_t size() const ///< @return the size the this Node whatever it is.
        {
            return getPimpl().size();
        }
        Property push_back() const
        {
            return getPimpl().push_back();
        }
        bool contains(Key const& _key) const ///< @pre map/set. @return true if it contains _key.
        {
            return getPimpl().contains(_key);
        }
        size_t arraySize() const ///< @return size of a simple array
        {
            return getPimpl().arraySize();
        }
        bool empty() const ///< Check if size() == 0
        {
            return getPimpl().empty();
        }
        void clear() const
        {
            getPimpl().clear();
        }
        bool isNull() const ///< @brief check if this Node is json null
        {
            return getPimpl().isNull();
        }

        std::set<char const*, CmpStr> getMapKeysString() const ///< Get map keys as strings
        {
            return getPimpl().getMapKeysString();
        }
        std::set<int64_t> getMapKeysInt() const ///< Get map keys as ints
        {
            return getPimpl().getMapKeysInt();
        }
        std::set<int64_t> getPrimSetKeysInt() const ///< Get set elements as ints
        {
            return getPimpl().getPrimSetKeysInt();
        }
        std::set<char const*, CmpStr> getPrimSetKeysString() const ///< Get set elements as strings
        {
            return getPimpl().getPrimSetKeysString();
        }
        /// Get UnionSet keys as strings
        std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString() const
        {
            return getPimpl().getUnionSetKeysString();
        }
        std::set<char const*, CmpStr> getObjectSetKeysString() const ///< Get keys of objects as strings
        {
            return getPimpl().getObjectSetKeysString();
        }
        std::set<int64_t> getObjectSetKeysInt() const ///< Get keys of objects as ints
        {
            return getPimpl().getObjectSetKeysInt();
        }

        std::set<char const*, CmpStr> getMapRemovedKeysString()
        {
            return getPimpl().getMapRemovedKeysString();
        }
        std::set<int64_t> getMapRemovedKeysInt()
        {
            return getPimpl().getMapRemovedKeysInt();
        }
        std::map<char const*, Subschema const*, CmpStr> getUnionSetRemovedKeysString()
        {
            return getPimpl().getUnionSetRemovedKeysString();
        }
        std::set<char const*, CmpStr> getObjectSetRemovedKeysString()
        {
            return getPimpl().getObjectSetRemovedKeysString();
        }
        std::set<int64_t> getObjectSetRemovedKeysInt()
        {
            return getPimpl().getObjectSetRemovedKeysInt();
        }

        Property mapRename(char const* _current, char const* _new);
        Property mapRename(int64_t _current, int64_t _new);
        Property unionSetRename(char const* _current, char const* _new);
        Property objectSetRename(char const* _current, char const* _new);
        Property objectSetRename(int64_t _current, int64_t _new);

        bool mapContains(char const* _key) const ///< Check if the map contains this _key
        {
            return getPimpl().mapContains(_key);
        }
        bool mapContains(int64_t _key) const ///< Check if the map contains this _key
        {
            return getPimpl().mapContains(_key);
        }
        bool primSetContains(char const* _key) const ///< Check if the set contains this _key
        {
            return getPimpl().primSetContains(_key);
        }
        bool primSetContains(int64_t _key) const ///< Check if the set contains this _key
        {
            return getPimpl().primSetContains(_key);
        }
        bool unionSetContains(char const* _key) const ///< Check if the UnionSet contains this _key
        {
            return getPimpl().unionSetContains(_key);
        }
        bool objectSetContains(char const* _key) const ///< Check if the ObjectSet contains this _key
        {
            return getPimpl().objectSetContains(_key);
        }
        bool objectSetContains(int64_t _key) const ///< Check if the ObjectSet contains this _key
        {
            return getPimpl().objectSetContains(_key);
        }

        bool isSet() const ///< Check if the Node is set in the instance
        {
            return getPimpl().isSet();
        }
        bool hasOverride() const ///< Check if the Node is set in the instance
        {
            return getPimpl().isSet();
        }
        void unset() const
        {
            return getPimpl().unset();
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

        void setSize(size_t _size) const ///< @pre type==array. @brief Set the size of the array.
        {
            return getPimpl().setSize(_size);
        }

        void setFloat(double _value) const ///< @pre type==number. @brief Set _value in the instance
        {
            return getPimpl().setFloat(_value);
        }
        void setInt(int64_t _value) const ///< @pre type==integer. @brief Set _value in the instance
        {
            return getPimpl().setInt(_value);
        }
        void setString(char const* _value) const ///< @pre type==string. @brief Set _value in the instance
        {
            return getPimpl().setString(_value);
        }
        void setBool(bool _value) const ///< @pre type==bool. @brief Set _value in the instance
        {
            return getPimpl().setBool(_value);
        }
        void setEntityRef(EntityRef const& _value) const ///< @pre type==entityref. @brief Set _value in the instance
        {
            return getPimpl().setEntityRef(_value);
        }
        Property setUnionType(char const* _type) const ///< @pre type==union. @brief Set _value in the instance
        {
            return getPimpl().setUnionType(_type);
        }

        void buildPath() const ///< Build json path but not set any value. Usefull for UnionSet items
        {
            return getPimpl().buildPath();
        }
        void insertPrimSetKey(char const* _key) const ///< Insert _key in the set (or do nothing if already in)
        {
            return getPimpl().insertPrimSetKey(_key);
        }
        void insertPrimSetKey(int64_t _key) const ///< Insert _key in the set (or do nothing if already in)
        {
            return getPimpl().insertPrimSetKey(_key);
        }
        Property insertUnionSetItem(char const* _key) const
        {
            return getPimpl().insertUnionSetItem(_key);
        }
        Property insertObjectSetItem(char const* _key) const
        {
            return getPimpl().insertObjectSetItem(_key);
        }
        Property insertObjectSetItem(int64_t _key) const
        {
            return getPimpl().insertObjectSetItem(_key);
        }
        Property insertInstanceObjectSetItem(char const* _prefabPath) const
        {
            return getPimpl().insertInstanceObjectSetItem(_prefabPath);
        }
        Property insertMapItem(char const* _key) const
        {
            return getPimpl().insertMapItem(_key);
        }
        Property insertMapItem(int64_t _key) const
        {
            return getPimpl().insertMapItem(_key);
        }

        bool erasePrimSetKey(char const* _key) const
        {
            return getPimpl().erasePrimSetKey(_key);
        }
        bool erasePrimSetKey(int64_t _key) const
        {
            return getPimpl().erasePrimSetKey(_key);
        }
        bool eraseObjectSetItem(char const* _key) const
        {
            return getPimpl().eraseObjectSetItem(_key);
        }
        bool eraseObjectSetItem(int64_t _key) const
        {
            return getPimpl().eraseObjectSetItem(_key);
        }
        bool eraseMapItem(char const* _key) const
        {
            return getPimpl().eraseMapItem(_key);
        }
        bool eraseMapItem(int64_t _key) const
        {
            return getPimpl().eraseMapItem(_key);
        }
        bool eraseUnionSetItem(char const* _key) const
        {
            return getPimpl().eraseUnionSetItem(_key);
        }
        double getDefaultFloat() const
        {
            return getPimpl().getDefaultFloat();
        }
        int64_t getDefaultInt() const
        {
            return getPimpl().getDefaultInt();
        }
        char const* getDefaultString() const
        {
            return getPimpl().getDefaultString();
        }
        bool getDefaultBool() const
        {
            return getPimpl().getDefaultBool();
        }
        EntityRef getDefaultEntityRef() const
        {
            return getPimpl().getDefaultEntityRef();
        }
        size_t getDefaultSize() const
        {
            return getPimpl().getDefaultSize();
        }

        PropImplPtr getLastSetPrefab() const
        {
            return getPimpl().getLastSetPrefab();
        }
        bool hasPrefabValue() const
        {
            return getPimpl().hasPrefabValue();
        }
        double getPrefabFloat() const
        {
            return getPimpl().getPrefabFloat();
        }
        int64_t getPrefabInt() const
        {
            return getPimpl().getPrefabInt();
        }
        char const* getPrefabString() const
        {
            return getPimpl().getPrefabString();
        }
        bool getPrefabBool() const
        {
            return getPimpl().getPrefabBool();
        }
        EntityRef getPrefabEntityRef() const
        {
            return getPimpl().getPrefabEntityRef();
        }
        std::optional<size_t> getPrefabSize() const
        {
            return getPimpl().getPrefabSize();
        }

        nlohmann::json const* getRawJson() const ///< Get the underlying json node of the instance
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

        std::vector<char const*>
        getFieldNames() const ///< @pre type==Ent::DataType::object @brief Get all field names
        {
            return m_self->getFieldNames();
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

        EntityLib* getEntityLib() const
        {
            return m_self->getEntityLib();
        }

        char const* getFilePath() const
        {
            return m_self->getFilePath();
        }

        DataKind getDataKind() const
        {
            return m_self->getDataKind();
        }

        bool isMapOrSet() const
        {
            auto const kind = getDataKind();
            return kind == DataKind::map || kind == DataKind::objectSet
                   || kind == DataKind::unionSet || kind == DataKind::primitiveSet;
        }

        void copyInto(Property& _dest, CopyMode _copyMode);

        Property detach();

        void applyToPrefab();

        bool operator==(Property const& _rho) const
        {
            if (!hasValue())
            {
                return !_rho.hasValue();
            }
            if (!_rho.hasValue())
            {
                return false;
            }
            return getRawJson() == _rho.getRawJson();
        }

        PropImpl& getPimpl() const
        {
            return *m_self;
        }

    private:
        PropImplPtr m_self{};
    };
} // namespace Ent
