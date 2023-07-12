#pragma once
#include "../../PropImpl.h"
#include "EntityLib.h"

#define ENTLIB_PROP_CATCH                                                                          \
    catch (ContextException & ex)                                                                  \
    {                                                                                              \
        ex.addContextMessage(getDebugString());                                                    \
        throw;                                                                                     \
    }                                                                                              \
    catch (...)                                                                                    \
    {                                                                                              \
        throw WrapperException(std::current_exception(), "%s", getDebugString());                  \
    }

namespace Ent
{
    struct PrefabInfo;
    struct ENTLIB_DLLEXPORT Property
    {
    public:
        using Key = std::variant<std::string, int64_t>;

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
        try
        {
            getPimpl().save(_filename);
        }
        ENTLIB_PROP_CATCH

        /// The Property is default if no values are set in the instance or a prefab
        [[nodiscard]] bool isDefault() const
        try
        {
            return getPimpl().isDefault();
        }
        ENTLIB_PROP_CATCH

        /// @brief Get the Property of a field of this object
        /// @pre It is an object
        [[nodiscard]] Property getObjectField(
            char const* _field, ///< Name of the field to enter
            SubschemaRef const* _fieldRef = nullptr ///< Schema of this field (for performance)
        ) const
        try
        {
            return Property{getPimpl().getObjectField(_field, _fieldRef)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] std::optional<Property>
        getUnionData(char const* _type ///< type of the internal data of the union
        ) const
        try
        {
            if (auto unionData = getPimpl().getUnionData(_type))
            {
                return Property{std::move(unionData)};
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] Property getUnionData() const
        try
        {
            auto unionData = getPimpl().getUnionData();
            ENTLIB_ASSERT(unionData != nullptr);
            return Property{std::move(unionData)};
        }
        ENTLIB_PROP_CATCH

        /// @brief Get an item in a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] std::optional<Property> getUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        ) const
        try
        {
            if (auto item = getPimpl().getUnionSetItem(_type, _dataSchema))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the object in an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] std::optional<Property> getObjectSetItem(char const* _key ///< Key of the object
        ) const
        try
        {
            if (auto item = getPimpl().getObjectSetItem(_key))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the object in an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] std::optional<Property> getObjectSetItem(int64_t _key ///< Key of the object
        ) const
        try
        {
            if (auto item = getPimpl().getObjectSetItem(_key))
            {
                return Property{std::move(item)};
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
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
        ENTLIB_PROP_CATCH
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
        ENTLIB_PROP_CATCH
        /// @brief Get the element in a Array
        /// @pre It is an Array
        [[nodiscard]] Property getArrayItem(size_t _index ///< index of the targeted element
        ) const
        try
        {
            return Property{getPimpl().getArrayItem(_index)};
        }
        ENTLIB_PROP_CATCH
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        /// @remake only look in the instance
        [[nodiscard]] char const* getInstanceOf() const
        try
        {
            return getPimpl().getInstanceOf();
        }
        ENTLIB_PROP_CATCH
        /// @return The first "InstanceOf" field, following prefabs, an empty string if set to empty, or nullptr if no prefab.
        /// @pre It is an Object
        /// @remark Will follow the prefab chain until a InstanceOf is found
        [[nodiscard]] char const* getFirstInstanceOf() const
        try
        {
            return getPimpl().getFirstInstanceOf();
        }
        ENTLIB_PROP_CATCH

        /// @brief Set the prefab (and reset all overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark resetInstanceOf("") mean explicitly set to InstanceOf : ""
        void resetInstanceOf(char const* _instanceOf) const
        try
        {
            return getPimpl().resetInstanceOf(_instanceOf);
        }
        ENTLIB_PROP_CATCH
        /// @brief Set the prefab (and keep overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark changeInstanceOf("") mean explicitly set to InstanceOf : ""
        void changeInstanceOf(char const* _instanceOf) const
        try
        {
            return getPimpl().changeInstanceOf(_instanceOf);
        }
        ENTLIB_PROP_CATCH
        /// @brief Create a new Property which is an instance of this one
        [[nodiscard]] Property makeInstanceOf() const
        try
        {
            return Property{getPimpl().makeInstanceOf()};
        }
        ENTLIB_PROP_CATCH

        /// @return The type of the Union
        /// @pre It is a Union
        [[nodiscard]] char const* getUnionType() const
        try
        {
            return getPimpl().getUnionType();
        }
        ENTLIB_PROP_CATCH
        /// @return The index of the type of the Union
        /// @pre It is a Union
        [[nodiscard]] size_t getUnionTypeIndex() const
        try
        {
            return getPimpl().getUnionTypeIndex();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] Subschema const* getSchema() const ///< Get the Schema of the current Property
        try
        {
            return getPimpl().getSchema();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] char const* getTypeName() const ///< Get the Schema name of the current Property
        try
        {
            return getPimpl().getTypeName();
        }
        ENTLIB_PROP_CATCH

        [[nodiscard]] DataKind getMapKeyKind() const ///< @pre Map @brief Get the key type current Map
        try
        {
            return getPimpl().getMapKeyKind();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] DataKind
        getObjectSetKeyKind() const ///< @pre ObjectSet @brief Get the key type current ObjectSet
        try
        {
            return getPimpl().getObjectSetKeyKind();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] DataKind getPrimSetKeyKind() const ///< @pre PrimitiveSet @brief Get the key type Set
        try
        {
            return getPimpl().getPrimSetKeyKind();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] size_t size() const ///< @return the size the this Property whatever it is.
        try
        {
            return getPimpl().size();
        }
        ENTLIB_PROP_CATCH
        /// @brief Push a new property in the array and return it
        /// @pre array
        [[nodiscard]] Property pushBack() const
        try
        {
            return Property{getPimpl().pushBack()};
        }
        ENTLIB_PROP_CATCH
        /// @brief Pop the last property in the array
        /// @pre array and size() != 0
        void popBack() const
        try
        {
            getPimpl().popBack();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool contains(Key const& _key) const ///< @pre map/set. @return true if it contains _key.
        try
        {
            return getPimpl().contains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] size_t arraySize() const ///< @return size of a simple array
        try
        {
            return getPimpl().arraySize();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool empty() const ///< Check if size() == 0
        try
        {
            return getPimpl().empty();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] void clear() const ///< Make the array empty
        try
        {
            getPimpl().clear();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool isNull() const ///< @brief check if this Property is json null
        try
        {
            return getPimpl().isNull();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::set<char const*, CmpStr> getMapKeysString() const ///< Get map keys as strings
        try
        {
            return getPimpl().getMapKeysString();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::set<int64_t> getMapKeysInt() const ///< Get map keys as ints
        try
        {
            return getPimpl().getMapKeysInt();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::set<int64_t> getPrimSetKeysInt() const ///< Get set elements as ints
        try
        {
            return getPimpl().getPrimSetKeysInt();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::set<char const*, CmpStr> getPrimSetKeysString() const ///< Get set elements as strings
        try
        {
            return getPimpl().getPrimSetKeysString();
        }
        ENTLIB_PROP_CATCH
        /// Get UnionSet keys as strings
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString() const
        try
        {
            return getPimpl().getUnionSetKeysString();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::set<char const*, CmpStr>
        getObjectSetKeysString() const ///< Get keys of objects as strings
        try
        {
            return getPimpl().getObjectSetKeysString();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::set<int64_t> getObjectSetKeysInt() const ///< Get keys of objects as ints
        try
        {
            return getPimpl().getObjectSetKeysInt();
        }
        ENTLIB_PROP_CATCH

        /// TODO : PropImpl should implement getMapStringItems, and return a view, for efficiency
        ///                   https://wildsheepstudio.atlassian.net/browse/WLD-8887
        [[nodiscard]] std::map<char const*, Property, CmpStr> getMapStringItems() const;
        [[nodiscard]] std::map<int64_t, Property> getMapIntItems() const;
        [[nodiscard]] std::vector<Property> getObjectSetItems() const;
        [[nodiscard]] std::map<char const*, Property, CmpStr> getUnionSetItems() const;

        /// @brief Ket keys removed in the instance
        /// @pre Is a Map with string keys
        [[nodiscard]] std::set<char const*, CmpStr> getMapRemovedKeysString() const
        try
        {
            return getPimpl().getMapRemovedKeysString();
        }
        ENTLIB_PROP_CATCH
        /// @brief Ket keys removed in the instance
        /// @pre Is a Map with integer keys
        [[nodiscard]] std::set<int64_t> getMapRemovedKeysInt() const
        try
        {
            return getPimpl().getMapRemovedKeysInt();
        }
        ENTLIB_PROP_CATCH
        /// @brief Ket keys removed in the instance
        /// @pre Is a UnionSet
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetRemovedKeysString() const
        try
        {
            return getPimpl().getUnionSetRemovedKeysString();
        }
        ENTLIB_PROP_CATCH
        /// @brief Ket keys removed in the instance
        /// @pre Is an ObjectSet with string keys
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetRemovedKeysString() const
        try
        {
            return getPimpl().getObjectSetRemovedKeysString();
        }
        ENTLIB_PROP_CATCH
        /// @brief Ket keys removed in the instance
        /// @pre Is an ObjectSet with integer keys
        [[nodiscard]] std::set<int64_t> getObjectSetRemovedKeysInt() const
        try
        {
            return getPimpl().getObjectSetRemovedKeysInt();
        }
        ENTLIB_PROP_CATCH

        Property mapRename(char const* _current, char const* _new);
        [[nodiscard]] Property mapRename(int64_t _current, int64_t _new) const;
        Property unionSetRename(char const* _current, char const* _new) const;

        [[nodiscard]] bool mapContains(char const* _key) const ///< Check if the map contains this _key
        try
        {
            return getPimpl().mapContains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool mapContains(int64_t _key) const ///< Check if the map contains this _key
        try
        {
            return getPimpl().mapContains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool primSetContains(char const* _key) const ///< Check if the set contains this _key
        try
        {
            return getPimpl().primSetContains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool primSetContains(int64_t _key) const ///< Check if the set contains this _key
        try
        {
            return getPimpl().primSetContains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool unionSetContains(char const* _key) const ///< Check if the UnionSet contains this _key
        try
        {
            return getPimpl().unionSetContains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool
        objectSetContains(char const* _key) const ///< Check if the ObjectSet contains this _key
        try
        {
            return getPimpl().objectSetContains(_key);
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool objectSetContains(int64_t _key) const ///< Check if the ObjectSet contains this _key
        try
        {
            return getPimpl().objectSetContains(_key);
        }
        ENTLIB_PROP_CATCH

        [[nodiscard]] bool isSet() const ///< Check if the Property is set in the instance
        try
        {
            return getPimpl().isSet();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool hasOverride() const ///< Check if the Property is set in the instance
        try
        {
            return getPimpl().isSet();
        }
        ENTLIB_PROP_CATCH
        void unset() const ///< Remove overriden values in instance. Can't remove an item in a map.
        try
        {
            return getPimpl().unset();
        }
        ENTLIB_PROP_CATCH

        template <typename V>
        [[nodiscard]] V get() const ///< @pre Property is of type V. @brief Get the value in the given V type
        try
        {
            return getPimpl().get<V>();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] double getFloat() const ///< @pre type==number. @brief Get the value as double
        try
        {
            return getPimpl().getFloat();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] int64_t getInt() const ///< @pre type==integer. @brief Get the value as int
        try
        {
            return getPimpl().getInt();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] char const* getString() const ///< @pre type==string. @brief Get the value as string
        try
        {
            return getPimpl().getString();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] bool getBool() const ///< @pre type==boolean. @brief Get the value as bool
        try
        {
            return getPimpl().getBool();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] EntityRef
        getEntityRef() const /// @pre type==entityRef. @brief Get the value as an Entity reference
        try
        {
            return getPimpl().getEntityRef();
        }
        ENTLIB_PROP_CATCH
        void setSize(size_t _size) const ///< @pre type==array. @brief Set the size of the array.
        try
        {
            return getPimpl().setSize(_size);
        }
        ENTLIB_PROP_CATCH

        void setFloat(double _value) const ///< @pre type==number. @brief Set _value in the instance
        try
        {
            return getPimpl().setFloat(_value);
        }
        ENTLIB_PROP_CATCH
        void setInt(int64_t _value) const ///< @pre type==integer. @brief Set _value in the instance
        try
        {
            return getPimpl().setInt(_value);
        }
        ENTLIB_PROP_CATCH
        void setString(char const* _value) const ///< @pre type==string. @brief Set _value in the instance
        try
        {
            return getPimpl().setString(_value);
        }
        ENTLIB_PROP_CATCH
        void setBool(bool _value) const ///< @pre type==bool. @brief Set _value in the instance
        try
        {
            return getPimpl().setBool(_value);
        }
        ENTLIB_PROP_CATCH
        void setEntityRef(EntityRef const& _value) const ///< @pre type==entityref. @brief Set _value in the instance
        try
        {
            return getPimpl().setEntityRef(_value);
        }
        ENTLIB_PROP_CATCH
        Property setUnionType(char const* _type) const ///< @pre type==union. @brief Set _value in the instance
        try
        {
            return Property{getPimpl().setUnionType(_type)};
        }
        ENTLIB_PROP_CATCH

        void buildPath() const ///< Build json path but not set any value. Usefull for UnionSet items
        try
        {
            return getPimpl().buildPath();
        }
        ENTLIB_PROP_CATCH
        void insertPrimSetKey(char const* _key) const ///< Insert _key in the set (or do nothing if already in)
        try
        {
            return getPimpl().insertPrimSetKey(_key);
        }
        ENTLIB_PROP_CATCH
        void insertPrimSetKey(int64_t _key) const ///< Insert _key in the set (or do nothing if already in)
        try
        {
            return getPimpl().insertPrimSetKey(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Insert _key in the UnionSet (or do nothing if already in)
        /// @pre is a UnionSet
        /// @return The element with key _key
        Property insertUnionSetItem(char const* _key) const
        try
        {
            return Property{getPimpl().insertUnionSetItem(_key)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Insert _key in the ObjectSet (or do nothing if already in)
        /// @pre is an ObjectSet
        /// @return The element with key _key
        Property insertObjectSetItem(char const* _key) const
        try
        {
            return Property{getPimpl().insertObjectSetItem(_key)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Insert _key in the ObjectSet (or do nothing if already in)
        /// @pre is an ObjectSet
        /// @return The element with key _key
        Property insertObjectSetItem(int64_t _key) const
        try
        {
            return Property{getPimpl().insertObjectSetItem(_key)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Insert an element with the given prefab
        ///
        /// Will read the key in the prefab, then insert the key and change the prefab
        ///
        /// @pre is an ObjectSet
        /// @return The element with prefab _prefabPath
        Property insertInstanceObjectSetItem(char const* _prefabPath) const
        try
        {
            return Property{getPimpl().insertInstanceObjectSetItem(_prefabPath)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Insert _key in the Map (or do nothing if already in)
        /// @pre is a Map with string keys
        /// @return The element with key _key
        Property insertMapItem(char const* _key) const
        try
        {
            return Property{getPimpl().insertMapItem(_key)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Insert _key in the Map (or do nothing if already in)
        /// @pre is a Map with integer keys
        /// @return The element with key _key
        Property insertMapItem(int64_t _key) const
        try
        {
            return Property{getPimpl().insertMapItem(_key)};
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the data of the union, as the given _type and a bool to inform if it is the actual data type
        ///
        /// @remark If not the right type, the type will be changed on writing.
        [[nodiscard]] std::pair<Property, bool> forceGetUnionData(char const* _type = nullptr) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetUnionData(_type);
            return {Property{std::move(ptr)}, found};
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the data in the union set and a bool to inform if it is actually in the unionset
        ///
        /// @remark If not in the unionset, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool>
        forceGetUnionSetItem(char const* _type, Subschema const* _dataSchema = nullptr) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetUnionSetItem(_type, _dataSchema);
            return {Property{std::move(ptr)}, found};
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the data in the objectset and a bool to inform if it is actually in the objectset
        ///
        /// @remark If not in the objectset, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetObjectSetItem(char const* _key) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetObjectSetItem(_key);
            return {Property{std::move(ptr)}, found};
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the data in the objectset and a bool to inform if it is actually in the objectset
        ///
        /// @remark If not in the map, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetObjectSetItem(int64_t _key) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetObjectSetItem(_key);
            return {Property{std::move(ptr)}, found};
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the data in the map and a bool to inform if it is actually in the map
        ///
        /// @remark If not in the map, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetMapItem(char const* _key) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetMapItem(_key);
            return {Property{std::move(ptr)}, found};
        }
        ENTLIB_PROP_CATCH

        /// @brief Get the data in the map and a bool to inform if it is actually in the map
        ///
        /// @remark If not in the map, it will be added only when writing.
        [[nodiscard]] std::pair<Property, bool> forceGetMapItem(int64_t _field) const
        try
        {
            auto [ptr, found] = getPimpl().forceGetMapItem(_field);
            return {Property{std::move(ptr)}, found};
        }
        ENTLIB_PROP_CATCH

        /// @brief Erase the item _key in the set of string
        /// @pre is a set of string
        /// @return true if an element was removed
        bool erasePrimSetKey(char const* _key) const
        try
        {
            return getPimpl().erasePrimSetKey(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Erase the item _key in the set of integer
        /// @pre is a set of integer
        /// @return true if an element was removed
        bool erasePrimSetKey(int64_t _key) const
        try
        {
            return getPimpl().erasePrimSetKey(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Erase the item _key in the ObjectSet
        /// @pre is an ObjectSet
        /// @return true if an element was removed
        bool eraseObjectSetItem(char const* _key) const
        try
        {
            return getPimpl().eraseObjectSetItem(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Erase the item _key in the ObjectSet
        /// @pre is an ObjectSet
        /// @return true if an element was removed
        bool eraseObjectSetItem(int64_t _key) const
        try
        {
            return getPimpl().eraseObjectSetItem(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Erase the item _key in the Map
        /// @pre is an Map with string keys
        /// @return true if an element was removed
        bool eraseMapItem(char const* _key) const
        try
        {
            return getPimpl().eraseMapItem(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Erase the item _key in the Map
        /// @pre is an Map with integer keys
        /// @return true if an element was removed
        bool eraseMapItem(int64_t _key) const
        try
        {
            return getPimpl().eraseMapItem(_key);
        }
        ENTLIB_PROP_CATCH
        /// @brief Erase the item _key in the UnionSet
        /// @pre is an UnionSet
        /// @return true if an element was removed
        bool eraseUnionSetItem(char const* _key) const
        try
        {
            return getPimpl().eraseUnionSetItem(_key);
        }
        ENTLIB_PROP_CATCH

        void clearMap() const
        try
        {
            return getPimpl().clearMap();
        }
        ENTLIB_PROP_CATCH
        void clearPrimSet() const
        try
        {
            return getPimpl().clearPrimSet();
        }
        ENTLIB_PROP_CATCH
        void clearObjectSet() const
        try
        {
            return getPimpl().clearObjectSet();
        }
        ENTLIB_PROP_CATCH
        void clearUnionSet() const
        try
        {
            return getPimpl().clearUnionSet();
        }
        ENTLIB_PROP_CATCH

        /// Get the default number
        [[nodiscard]] double getDefaultFloat() const
        try
        {
            return getPimpl().getDefaultFloat();
        }
        ENTLIB_PROP_CATCH
        /// Get the default integer
        [[nodiscard]] int64_t getDefaultInt() const
        try
        {
            return getPimpl().getDefaultInt();
        }
        ENTLIB_PROP_CATCH
        /// Get the default string
        [[nodiscard]] char const* getDefaultString() const
        try
        {
            return getPimpl().getDefaultString();
        }
        ENTLIB_PROP_CATCH
        /// Get the default bool
        [[nodiscard]] bool getDefaultBool() const
        try
        {
            return getPimpl().getDefaultBool();
        }
        ENTLIB_PROP_CATCH
        /// Get the default EntityRef
        [[nodiscard]] EntityRef getDefaultEntityRef() const
        try
        {
            return getPimpl().getDefaultEntityRef();
        }
        ENTLIB_PROP_CATCH
        /// Get the default array size
        [[nodiscard]] size_t getDefaultSize() const
        try
        {
            return getPimpl().getDefaultSize();
        }
        ENTLIB_PROP_CATCH
        /// Get the last prefab which is set
        [[nodiscard]] PropImplPtr getLastSetPrefab() const
        try
        {
            return getPimpl().getLastSetPrefab();
        }
        ENTLIB_PROP_CATCH
        /// Check if the is a prefab value
        [[nodiscard]] bool hasPrefabValue() const
        try
        {
            return getPimpl().hasPrefabValue();
        }
        ENTLIB_PROP_CATCH
        /// Get the prefab number
        [[nodiscard]] double getPrefabFloat() const
        try
        {
            return getPimpl().getPrefabFloat();
        }
        ENTLIB_PROP_CATCH
        /// Get the prefab integer
        [[nodiscard]] int64_t getPrefabInt() const
        try
        {
            return getPimpl().getPrefabInt();
        }
        ENTLIB_PROP_CATCH
        /// Get the prefab string
        [[nodiscard]] char const* getPrefabString() const
        try
        {
            return getPimpl().getPrefabString();
        }
        ENTLIB_PROP_CATCH
        /// Get the prefab bool
        [[nodiscard]] bool getPrefabBool() const
        try
        {
            return getPimpl().getPrefabBool();
        }
        ENTLIB_PROP_CATCH
        /// Get the prefab EntityRef
        [[nodiscard]] EntityRef getPrefabEntityRef() const
        try
        {
            return getPimpl().getPrefabEntityRef();
        }
        ENTLIB_PROP_CATCH
        /// Get the prefab size
        [[nodiscard]] std::optional<size_t> getPrefabSize() const
        try
        {
            return getPimpl().getPrefabSize();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] nlohmann::json const* getRawJson() const ///< Get the underlying json node of the instance
        try
        {
            return getPimpl().getRawJson();
        }
        ENTLIB_PROP_CATCH
        /// @brief Check if the Property is not nullptr inside (have to be true to call any method)
        [[nodiscard]] bool hasValue() const
        try
        {
            return m_self != nullptr;
        }
        ENTLIB_PROP_CATCH
        /// @brief Check if the Property has a "InstanceOf" declared and not empty
        [[nodiscard]] bool hasPrefab() const
        try
        {
            return m_self->getPrefab() != nullptr;
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::vector<char const*>
        getFieldNames() const ///< @pre getDataKind()==Ent::DataKind::object @brief Get all field names
        try
        {
            return m_self->getFieldNames();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::optional<Property> getPrefab() const ///< Get the prefab of the Property
        try
        {
            if (auto* const prefab = m_self->getPrefab())
            {
                return Property{prefab->sharedFromThis()};
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] std::optional<Property> getParent() const ///< Get the Property which own this one
        try
        {
            if (auto parent = m_self->getParent())
            {
                return Property{std::move(parent)};
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] EntityLib* getEntityLib() const
        try
        {
            return m_self->getEntityLib();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] char const* getFilePath() const
        try
        {
            return m_self->getFilePath();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] DataKind getDataKind() const
        try
        {
            return m_self->getDataKind();
        }
        ENTLIB_PROP_CATCH
        /// Return true if this is a Map or a Set
        [[nodiscard]] bool isMapOrSet() const
        try
        {
            auto const kind = getDataKind();
            return kind == DataKind::map || kind == DataKind::objectSet
                   || kind == DataKind::unionSet || kind == DataKind::primitiveSet;
        }
        ENTLIB_PROP_CATCH
        void copyInto(
            Property const& _dest,
            CopyMode _copyMode,
            OverrideValueSource _overrideValueSource = OverrideValueSource::OverrideOrPrefab,
            bool _copyRootInstanceOf = true) const;

        [[nodiscard]] Property detach();

        // Create a copy of this Property, but with no parent
        [[nodiscard]] Property clone();

        void applyToPrefab();

        [[nodiscard]] bool operator==(Property const& _rho) const
        try
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
        ENTLIB_PROP_CATCH

        bool operator!=(Property const& _rho) const
        try
        {
            return !(*this == _rho);
        }
        ENTLIB_PROP_CATCH
        bool operator==(nullptr_t) const
        try
        {
            return hasValue();
        }
        ENTLIB_PROP_CATCH
        bool operator!=(nullptr_t) const
        try
        {
            return !hasValue();
        }
        ENTLIB_PROP_CATCH
        explicit operator bool() const
        try
        {
            return hasValue();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] PropImpl& getPimpl() const
        try
        {
            ENTLIB_ASSERT(m_self != nullptr);
            return *m_self;
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the target pointed by _nodeRef, starting from this
        [[nodiscard]] std::optional<Property> resolveNodeRef(char const* _nodeRef) const
        try
        {
            if (auto prop = m_self->resolveNodeRef(_nodeRef); prop != nullptr)
            {
                return Property(std::move(prop));
            }
            return std::nullopt;
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] Property getRootNode() const
        try
        {
            return Property(m_self->getRootNode());
        }
        ENTLIB_PROP_CATCH
        /// @brief Make a NodeRef going from this to _target
        [[nodiscard]] NodeRef makeNodeRef(Property const& _target) const
        try
        {
            return m_self->makeNodeRef(*_target.m_self);
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the NodeRef from root to this
        [[nodiscard]] NodeRef makeAbsoluteNodeRef() const
        try
        {
            return m_self->makeAbsoluteNodeRef();
        }
        ENTLIB_PROP_CATCH
        [[nodiscard]] FileProperty::Key getPathToken() const
        try
        {
            return m_self->getPathToken();
        }
        ENTLIB_PROP_CATCH
        /// @brief Get the primitive values are equal
        [[nodiscard]] bool sameValue(Property const& _other) const
        try
        {
            return getPimpl().sameValue(_other.getPimpl());
        }
        ENTLIB_PROP_CATCH
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
