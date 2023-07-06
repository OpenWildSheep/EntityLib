#pragma once
#include "../../PropImpl.h"
#include "../EntityLib.h"

namespace Ent
{
    struct PrefabInfo;
    struct ENTLIB_DLLEXPORT Property
    {
    public:
        using Key = std::variant<std::string, size_t>;

        Property(Property const& _other)
            : m_self(_other.m_self == nullptr ? nullptr : _other.m_self->sharedFromThis())
        {
        }

        explicit Property(PropImplPtr _prop)
            : m_self(std::move(_prop))
        {
            ENTLIB_ASSERT(m_self != nullptr);
        }
        Property& operator=(Property const& _other)
        {
            Property copy(_other);
            std::swap(copy, *this);
            return *this;
        }
        Property(Property&& _other) noexcept = default;
        Property& operator=(Property&& _other) noexcept = default;
        Property(EntityLib* _entityLib, Subschema const* _schema, char const* _filename);
        Property(
            EntityLib* _entityLib,
            Subschema const* _schema,
            char const* _filename,
            nlohmann::json* _doc,
            JsonMetaData* _metaData);
        Property(
            EntityLib* _entityLib, Subschema const* _schema, char const* _filename, VersionedJson& _doc);

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const
        {
            getPimpl().save(_filename);
        }

        /// The Property is default if no values are set in the instance or a prefab
        [[nodiscard]] bool isDefault() const
        {
            return getPimpl().isDefault();
        }

        /// @brief Get the Property of a field of this object
        /// @pre It is an object
        [[nodiscard]] Property getObjectField(
            char const* _field, ///< Name of the field to enter
            SubschemaRef const* _fieldRef = nullptr ///< Schema of this field (for performance)
        ) const
        {
            return Property{getPimpl().getObjectField(_field, _fieldRef)};
        }
        /// @brief Get the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] std::optional<Property>
        getUnionData(char const* _type ///< type of the internal data of the union
        ) const
        {
            if (auto unionData = getPimpl().getUnionData(_type))
            {
                return Property{std::move(unionData)};
            }
            return std::nullopt;
        }
        [[nodiscard]] Property getUnionData() const
        {
            auto unionData = getPimpl().getUnionData();
            ENTLIB_ASSERT(unionData != nullptr);
            return Property{std::move(unionData)};
        }

        /// @brief Get an item in a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] std::optional<Property> getUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        ) const
        {
            if (auto item = getPimpl().getUnionSetItem(_type, _dataSchema))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        /// @brief Get the object in an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] std::optional<Property> getObjectSetItem(char const* _key ///< Key of the object
        ) const
        {
            if (auto item = getPimpl().getObjectSetItem(_key))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        /// @brief Get the object in an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] std::optional<Property> getObjectSetItem(int64_t _key ///< Key of the object
        ) const
        {
            if (auto item = getPimpl().getObjectSetItem(_key))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        /// @brief Given a key, get the related value in a Map
        /// @pre It is an Map
        [[nodiscard]] std::optional<Property> getMapItem(char const* _key ///< Key of the value
        ) const
        try
        {
            if (auto item = getPimpl().getMapItem(_key))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage(getDebugString());
            throw;
        }
        /// @brief Given a key, get the related value in a Map
        /// @pre It is an Map
        [[nodiscard]] std::optional<Property> getMapItem(int64_t _key ///< Key of the value
        ) const
        try
        {
            if (auto item = getPimpl().getMapItem(_key))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage(getDebugString());
            throw;
        }
        /// @brief Get the element in a Array
        /// @pre It is an Array
        [[nodiscard]] Property getArrayItem(size_t _index ///< index of the targeted element
        ) const
        {
            return Property{getPimpl().getArrayItem(_index)};
        }
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        /// @remake only look in the instance
        [[nodiscard]] char const* getInstanceOf() const
        {
            return getPimpl().getInstanceOf();
        }
        /// @return The first "InstanceOf" field, following prefabs, an empty string if set to empty, or nullptr if no prefab.
        /// @pre It is an Object
        /// @remark Will follow the prefab chain until a InstanceOf is found
        [[nodiscard]] char const* getFirstInstanceOf() const
        {
            return getPimpl().getFirstInstanceOf();
        }

        /// @brief Set the prefab (and reset all overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark resetInstanceOf("") mean explicitly set to InstanceOf : ""
        void resetInstanceOf(char const* _instanceOf) const
        {
            return getPimpl().resetInstanceOf(_instanceOf);
        }

        /// @brief Set the prefab (and keep overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark changeInstanceOf("") mean explicitly set to InstanceOf : ""
        void changeInstanceOf(char const* _instanceOf) const
        {
            return getPimpl().changeInstanceOf(_instanceOf);
        }

        /// @brief Create a new Property which is an instance of this one
        [[nodiscard]] Property makeInstanceOf() const
        {
            return Property{getPimpl().makeInstanceOf()};
        }

        /// @return The type of the Union
        /// @pre It is a Union
        [[nodiscard]] char const* getUnionType() const
        {
            return getPimpl().getUnionType();
        }
        /// @return The index of the type of the Union
        /// @pre It is a Union
        [[nodiscard]] size_t getUnionTypeIndex() const
        {
            return getPimpl().getUnionTypeIndex();
        }
        [[nodiscard]] Subschema const* getSchema() const ///< Get the Schema of the current Property
        {
            return getPimpl().getSchema();
        }
        [[nodiscard]] char const* getTypeName() const ///< Get the Schema name of the current Property
        {
            return getPimpl().getTypeName();
        }

        [[nodiscard]] DataKind getMapKeyKind() const ///< @pre Map @brief Get the key type current Map
        {
            return getPimpl().getMapKeyKind();
        }
        [[nodiscard]] DataKind
        getObjectSetKeyKind() const ///< @pre ObjectSet @brief Get the key type current ObjectSet
        {
            return getPimpl().getObjectSetKeyKind();
        }
        [[nodiscard]] DataKind getPrimSetKeyKind() const ///< @pre PrimitiveSet @brief Get the key type Set
        {
            return getPimpl().getPrimSetKeyKind();
        }
        [[nodiscard]] size_t size() const ///< @return the size the this Property whatever it is.
        {
            return getPimpl().size();
        }
        /// @brief Push a new property in the array and return it
        /// @pre array
        [[nodiscard]] Property pushBack() const
        {
            return Property{getPimpl().pushBack()};
        }
        /// @brief Pop the last property in the array
        /// @pre array and size() != 0
        void popBack() const
        {
            getPimpl().popBack();
        }
        [[nodiscard]] bool contains(Key const& _key) const ///< @pre map/set. @return true if it contains _key.
        {
            return getPimpl().contains(_key);
        }
        [[nodiscard]] size_t arraySize() const ///< @return size of a simple array
        {
            return getPimpl().arraySize();
        }
        [[nodiscard]] bool empty() const ///< Check if size() == 0
        {
            return getPimpl().empty();
        }
        [[nodiscard]] void clear() const ///< Make the array empty
        {
            getPimpl().clear();
        }
        [[nodiscard]] bool isNull() const ///< @brief check if this Property is json null
        {
            return getPimpl().isNull();
        }

        [[nodiscard]] std::set<char const*, CmpStr> getMapKeysString() const ///< Get map keys as strings
        {
            return getPimpl().getMapKeysString();
        }
        [[nodiscard]] std::set<int64_t> getMapKeysInt() const ///< Get map keys as ints
        {
            return getPimpl().getMapKeysInt();
        }
        [[nodiscard]] std::set<int64_t> getPrimSetKeysInt() const ///< Get set elements as ints
        {
            return getPimpl().getPrimSetKeysInt();
        }
        [[nodiscard]] std::set<char const*, CmpStr> getPrimSetKeysString() const ///< Get set elements as strings
        {
            return getPimpl().getPrimSetKeysString();
        }
        /// Get UnionSet keys as strings
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString() const
        {
            return getPimpl().getUnionSetKeysString();
        }
        [[nodiscard]] std::set<char const*, CmpStr>
        getObjectSetKeysString() const ///< Get keys of objects as strings
        {
            return getPimpl().getObjectSetKeysString();
        }
        [[nodiscard]] std::set<int64_t> getObjectSetKeysInt() const ///< Get keys of objects as ints
        {
            return getPimpl().getObjectSetKeysInt();
        }

        /// TODO : PropImpl should implement getMapStringItems, and return a view, for efficiency
        ///                   https://wildsheepstudio.atlassian.net/browse/WLD-8887
        [[nodiscard]] std::map<char const*, Property, CmpStr> getMapStringItems() const;
        [[nodiscard]] std::map<int64_t, Property> getMapIntItems() const;
        [[nodiscard]] std::vector<Property> getObjectSetItems() const;
        [[nodiscard]] std::map<char const*, Property, CmpStr> getUnionSetItems() const;

        /// @brief Ket keys removed in the instance
        /// @pre Is a Map with string keys
        [[nodiscard]] std::set<char const*, CmpStr> getMapRemovedKeysString() const
        {
            return getPimpl().getMapRemovedKeysString();
        }
        /// @brief Ket keys removed in the instance
        /// @pre Is a Map with integer keys
        [[nodiscard]] std::set<int64_t> getMapRemovedKeysInt() const
        {
            return getPimpl().getMapRemovedKeysInt();
        }
        /// @brief Ket keys removed in the instance
        /// @pre Is a UnionSet
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetRemovedKeysString() const
        {
            return getPimpl().getUnionSetRemovedKeysString();
        }
        /// @brief Ket keys removed in the instance
        /// @pre Is an ObjectSet with string keys
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetRemovedKeysString() const
        {
            return getPimpl().getObjectSetRemovedKeysString();
        }
        /// @brief Ket keys removed in the instance
        /// @pre Is an ObjectSet with integer keys
        [[nodiscard]] std::set<int64_t> getObjectSetRemovedKeysInt() const
        {
            return getPimpl().getObjectSetRemovedKeysInt();
        }

        Property mapRename(char const* _current, char const* _new);
        [[nodiscard]] Property mapRename(int64_t _current, int64_t _new) const;
        Property unionSetRename(char const* _current, char const* _new) const;

        [[nodiscard]] bool mapContains(char const* _key) const ///< Check if the map contains this _key
        {
            return getPimpl().mapContains(_key);
        }
        [[nodiscard]] bool mapContains(int64_t _key) const ///< Check if the map contains this _key
        {
            return getPimpl().mapContains(_key);
        }
        [[nodiscard]] bool primSetContains(char const* _key) const ///< Check if the set contains this _key
        {
            return getPimpl().primSetContains(_key);
        }
        [[nodiscard]] bool primSetContains(int64_t _key) const ///< Check if the set contains this _key
        {
            return getPimpl().primSetContains(_key);
        }
        [[nodiscard]] bool unionSetContains(char const* _key) const ///< Check if the UnionSet contains this _key
        {
            return getPimpl().unionSetContains(_key);
        }
        [[nodiscard]] bool
        objectSetContains(char const* _key) const ///< Check if the ObjectSet contains this _key
        {
            return getPimpl().objectSetContains(_key);
        }
        [[nodiscard]] bool objectSetContains(int64_t _key) const ///< Check if the ObjectSet contains this _key
        {
            return getPimpl().objectSetContains(_key);
        }

        [[nodiscard]] bool isSet() const ///< Check if the Property is set in the instance
        {
            return getPimpl().isSet();
        }
        [[nodiscard]] bool hasOverride() const ///< Check if the Property is set in the instance
        {
            return getPimpl().isSet();
        }
        void unset() const ///< Remove overriden values in instance. Can't remove an item in a map.
        {
            return getPimpl().unset();
        }

        template <typename V>
        [[nodiscard]] V get() const ///< @pre Property is of type V. @brief Get the value in the given V type
        {
            return getPimpl().get<V>();
        }
        [[nodiscard]] double getFloat() const ///< @pre type==number. @brief Get the value as double
        {
            return getPimpl().getFloat();
        }
        [[nodiscard]] int64_t getInt() const ///< @pre type==integer. @brief Get the value as int
        {
            return getPimpl().getInt();
        }
        [[nodiscard]] char const* getString() const ///< @pre type==string. @brief Get the value as string
        {
            return getPimpl().getString();
        }
        [[nodiscard]] bool getBool() const ///< @pre type==boolean. @brief Get the value as bool
        {
            return getPimpl().getBool();
        }
        [[nodiscard]] EntityRef
        getEntityRef() const /// @pre type==entityRef. @brief Get the value as an Entity reference
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
            return Property{getPimpl().setUnionType(_type)};
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
        /// @brief Insert _key in the UnionSet (or do nothing if already in)
        /// @pre is a UnionSet
        /// @return The element with key _key
        Property insertUnionSetItem(char const* _key) const
        {
            return Property{getPimpl().insertUnionSetItem(_key)};
        }
        /// @brief Insert _key in the ObjectSet (or do nothing if already in)
        /// @pre is an ObjectSet
        /// @return The element with key _key
        Property insertObjectSetItem(char const* _key) const
        {
            return Property{getPimpl().insertObjectSetItem(_key)};
        }
        /// @brief Insert _key in the ObjectSet (or do nothing if already in)
        /// @pre is an ObjectSet
        /// @return The element with key _key
        Property insertObjectSetItem(int64_t _key) const
        {
            return Property{getPimpl().insertObjectSetItem(_key)};
        }
        /// @brief Insert an element with the given prefab
        ///
        /// Will read the key in the prefab, then insert the key and change the prefab
        ///
        /// @pre is an ObjectSet
        /// @return The element with prefab _prefabPath
        Property insertInstanceObjectSetItem(char const* _prefabPath) const
        {
            return Property{getPimpl().insertInstanceObjectSetItem(_prefabPath)};
        }
        /// @brief Insert _key in the Map (or do nothing if already in)
        /// @pre is a Map with string keys
        /// @return The element with key _key
        Property insertMapItem(char const* _key) const
        try
        {
            return Property{getPimpl().insertMapItem(_key)};
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage(getDebugString());
            throw;
        }
        /// @brief Insert _key in the Map (or do nothing if already in)
        /// @pre is a Map with integer keys
        /// @return The element with key _key
        Property insertMapItem(int64_t _key) const
        try
        {
            return Property{getPimpl().insertMapItem(_key)};
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage(getDebugString());
            throw;
        }
        /// @brief Get the data of the union, as the given _type and a bool to inform if it is the actual data type
        ///
        /// @remark If not the right type, the type will be changed on writing.
        [[nodiscard]] std::pair<Property, bool> forceGetUnionData(char const* _type = nullptr) const
        {
            auto [ptr, found] = getPimpl().forceGetUnionData(_type);
            return {Property{std::move(ptr)}, found};
        }

        /// @brief Get the data in the union set and a bool to inform if it is actually in the unionset
        ///
        /// @remark If not in the unionset, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool>
        forceGetUnionSetItem(char const* _type, Subschema const* _dataSchema = nullptr) const
        {
            auto [ptr, found] = getPimpl().forceGetUnionSetItem(_type, _dataSchema);
            return {Property{std::move(ptr)}, found};
        }

        /// @brief Get the data in the objectset and a bool to inform if it is actually in the objectset
        ///
        /// @remark If not in the objectset, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetObjectSetItem(char const* _key) const
        {
            auto [ptr, found] = getPimpl().forceGetObjectSetItem(_key);
            return {Property{std::move(ptr)}, found};
        }

        /// @brief Get the data in the objectset and a bool to inform if it is actually in the objectset
        ///
        /// @remark If not in the map, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetObjectSetItem(int64_t _key) const
        {
            auto [ptr, found] = getPimpl().forceGetObjectSetItem(_key);
            return {Property{std::move(ptr)}, found};
        }

        /// @brief Get the data in the map and a bool to inform if it is actually in the map
        ///
        /// @remark If not in the map, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetMapItem(char const* _key) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetMapItem(_key);
            return {Property{std::move(ptr)}, found};
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage(getDebugString());
            throw;
        }

        /// @brief Get the data in the map and a bool to inform if it is actually in the map
        ///
        /// @remark If not in the map, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetMapItem(int64_t _field) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetMapItem(_field);
            return {Property{std::move(ptr)}, found};
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage(getDebugString());
            throw;
        }

        /// @brief Erase the item _key in the set of string
        /// @pre is a set of string
        /// @return true if an element was removed
        bool erasePrimSetKey(char const* _key) const
        {
            return getPimpl().erasePrimSetKey(_key);
        }
        /// @brief Erase the item _key in the set of integer
        /// @pre is a set of integer
        /// @return true if an element was removed
        bool erasePrimSetKey(int64_t _key) const
        {
            return getPimpl().erasePrimSetKey(_key);
        }
        /// @brief Erase the item _key in the ObjectSet
        /// @pre is an ObjectSet
        /// @return true if an element was removed
        bool eraseObjectSetItem(char const* _key) const
        {
            return getPimpl().eraseObjectSetItem(_key);
        }
        /// @brief Erase the item _key in the ObjectSet
        /// @pre is an ObjectSet
        /// @return true if an element was removed
        bool eraseObjectSetItem(int64_t _key) const
        {
            return getPimpl().eraseObjectSetItem(_key);
        }
        /// @brief Erase the item _key in the Map
        /// @pre is an Map with string keys
        /// @return true if an element was removed
        bool eraseMapItem(char const* _key) const
        {
            return getPimpl().eraseMapItem(_key);
        }
        /// @brief Erase the item _key in the Map
        /// @pre is an Map with integer keys
        /// @return true if an element was removed
        bool eraseMapItem(int64_t _key) const
        {
            return getPimpl().eraseMapItem(_key);
        }
        /// @brief Erase the item _key in the UnionSet
        /// @pre is an UnionSet
        /// @return true if an element was removed
        bool eraseUnionSetItem(char const* _key) const
        {
            return getPimpl().eraseUnionSetItem(_key);
        }

        void clearMap() const
        {
            return getPimpl().clearMap();
        }
        void clearPrimSet() const
        {
            return getPimpl().clearPrimSet();
        }
        void clearObjectSet() const
        {
            return getPimpl().clearObjectSet();
        }
        void clearUnionSet() const
        {
            return getPimpl().clearUnionSet();
        }

        /// Get the default number
        [[nodiscard]] double getDefaultFloat() const
        {
            return getPimpl().getDefaultFloat();
        }
        /// Get the default integer
        [[nodiscard]] int64_t getDefaultInt() const
        {
            return getPimpl().getDefaultInt();
        }
        /// Get the default string
        [[nodiscard]] char const* getDefaultString() const
        {
            return getPimpl().getDefaultString();
        }
        /// Get the default bool
        [[nodiscard]] bool getDefaultBool() const
        {
            return getPimpl().getDefaultBool();
        }
        /// Get the default EntityRef
        [[nodiscard]] EntityRef getDefaultEntityRef() const
        {
            return getPimpl().getDefaultEntityRef();
        }
        /// Get the default array size
        [[nodiscard]] size_t getDefaultSize() const
        {
            return getPimpl().getDefaultSize();
        }

        /// Get the last prefab which is set
        [[nodiscard]] PropImplPtr getLastSetPrefab() const
        {
            return getPimpl().getLastSetPrefab();
        }
        /// Check if the is a prefab value
        [[nodiscard]] bool hasPrefabValue() const
        {
            return getPimpl().hasPrefabValue();
        }

        /// Get the prefab number
        [[nodiscard]] double getPrefabFloat() const
        {
            return getPimpl().getPrefabFloat();
        }
        /// Get the prefab integer
        [[nodiscard]] int64_t getPrefabInt() const
        {
            return getPimpl().getPrefabInt();
        }
        /// Get the prefab string
        [[nodiscard]] char const* getPrefabString() const
        {
            return getPimpl().getPrefabString();
        }
        /// Get the prefab bool
        [[nodiscard]] bool getPrefabBool() const
        {
            return getPimpl().getPrefabBool();
        }
        /// Get the prefab EntityRef
        [[nodiscard]] EntityRef getPrefabEntityRef() const
        {
            return getPimpl().getPrefabEntityRef();
        }
        /// Get the prefab size
        [[nodiscard]] std::optional<size_t> getPrefabSize() const
        {
            return getPimpl().getPrefabSize();
        }

        [[nodiscard]] nlohmann::json const* getRawJson() const ///< Get the underlying json node of the instance
        {
            return getPimpl().getRawJson();
        }

        /// @brief Check if the Property is not nullptr inside (have to be true to call any method)
        [[nodiscard]] bool hasValue() const
        {
            return m_self != nullptr;
        }

        /// @brief Check if the Property has a "InstanceOf" declared and not empty
        [[nodiscard]] bool hasPrefab() const
        {
            return m_self->getPrefab() != nullptr;
        }

        [[nodiscard]] std::vector<char const*>
        getFieldNames() const ///< @pre getDataKind()==Ent::DataKind::object @brief Get all field names
        {
            return m_self->getFieldNames();
        }

        [[nodiscard]] std::optional<Property> getPrefab() const ///< Get the prefab of the Property
        {
            if (auto* const prefab = m_self->getPrefab())
            {
                return Property{prefab->sharedFromThis()};
            }
            return std::nullopt;
        }

        [[nodiscard]] std::optional<Property> getParent() const ///< Get the Property which own this one
        {
            if (auto parent = m_self->getParent())
            {
                return Property{std::move(parent)};
            }
            return std::nullopt;
        }

        [[nodiscard]] EntityLib* getEntityLib() const
        {
            return m_self->getEntityLib();
        }

        [[nodiscard]] char const* getFilePath() const
        {
            return m_self->getFilePath();
        }

        [[nodiscard]] DataKind getDataKind() const
        {
            return m_self->getDataKind();
        }

        /// Return true if this is a Map or a Set
        [[nodiscard]] bool isMapOrSet() const
        {
            auto const kind = getDataKind();
            return kind == DataKind::map || kind == DataKind::objectSet
                   || kind == DataKind::unionSet || kind == DataKind::primitiveSet;
        }

        void copyInto(
            Property const& _dest,
            CopyMode _copyMode,
            OverrideValueSource _overrideValueSource = OverrideValueSource::OverrideOrPrefab) const;

        [[nodiscard]] Property detach();

        // Create a copy of this Property, but with no parent
        [[nodiscard]] Property clone();

        void applyToPrefab();

        [[nodiscard]] bool operator==(Property const& _rho) const
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

        bool operator!=(Property const& _rho) const
        {
            return !(*this == _rho);
        }

        bool operator==(nullptr_t) const
        {
            return hasValue();
        }

        bool operator!=(nullptr_t) const
        {
            return !hasValue();
        }

        explicit operator bool() const
        {
            return hasValue();
        }

        [[nodiscard]] PropImpl& getPimpl() const
        {
            ENTLIB_ASSERT(m_self != nullptr);
            return *m_self;
        }

        /// @brief Get the target pointed by _nodeRef, starting from this
        [[nodiscard]] std::optional<Property> resolveNodeRef(char const* _nodeRef) const
        {
            if (auto prop = m_self->resolveNodeRef(_nodeRef); prop != nullptr)
            {
                return Property(std::move(prop));
            }
            return std::nullopt;
        }

        [[nodiscard]] Property getRootNode() const
        {
            return Property(m_self->getRootNode());
        }

        /// @brief Make a NodeRef going from this to _target
        [[nodiscard]] NodeRef makeNodeRef(Property const& _target) const
        {
            return m_self->makeNodeRef(*_target.m_self);
        }

        /// @brief Get the NodeRef from root to this
        [[nodiscard]] NodeRef makeAbsoluteNodeRef() const
        {
            return m_self->makeAbsoluteNodeRef();
        }

        [[nodiscard]] FileProperty::Key getPathToken() const
        {
            return m_self->getPathToken();
        }

        /// @brief Get the primitive values are equal
        [[nodiscard]] bool sameValue(Property const& _other) const
        {
            return getPimpl().sameValue(_other.getPimpl());
        }

        friend std::vector<PrefabInfo> getPrefabHistory(Property const& _prop);

        char const* getDebugString() const;

    private:
        PropImplPtr m_self{};
    };

    /// Information about a prefab in the prefab history of a Node
    /// @see Ent::getPrefabHistory
    struct PrefabInfo
    {
        std::string prefabPath; ///< Path to the prefab's file
        NodeRef nodeRef; ///< NodeRef from the prefab root the the pointed Node
        Property prop; ///< \b Read-only. Pointed Node in this prefab (if it exist).

        // TODO : Remove when C++20
        PrefabInfo(std::string _prefabPath, NodeRef _nodeRef, PropImplPtr _prop)
            : prefabPath(std::move(_prefabPath))
            , nodeRef(std::move(_nodeRef))
            , prop(std::move(_prop))
        {
        }
    };
    std::vector<PrefabInfo> getPrefabHistory(Property const& _prop);
} // namespace Ent
