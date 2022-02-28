#pragma once

#include <variant>
#include <set>
#include <deque>

#include "include/EntityLib/FileCursor.h"

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Tools.h"
#pragma warning(pop)

namespace Ent
{
    class EntityLib;

    struct Cursor;

    /// Functor used by PropImplPtr
    /// to decrement the refcounter on the unique_ptr destruction,
    /// and delete the Cursor if refcount == 0.
    struct DecRef
    {
        template <typename C>
        void operator()(C* _cursorPtr)
        {
            decRef(_cursorPtr);
        }
    };

    /// smart pointer to a Cursor (use reference counting)
    using PropImplPtr = std::unique_ptr<Cursor, DecRef>;

    /// @brief Internal implementation of a Property
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
            PropImplPtr _parent,
            Ent::Subschema const* _schema, ///< Schema of the file to load
            char const* _filename,
            nlohmann::json* _doc);

        Cursor(
            EntityLib* _entityLib,
            PropImplPtr _parent,
            Ent::Subschema const* _schema, ///< Schema of the file to load
            char const* _filename);

        void
        setDefault(Subschema const* _schema, char const* _filePath, nlohmann::json const* _document);
        FileCursor* getDefault();
        FileCursor const* getDefault() const;

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const;

        /// @brief The Node is default if no values are set inside
        bool isDefault() const;

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        PropImplPtr enterObjectField(
            char const* _field, ///< field to enter in
            SubschemaRef const* _fieldRef = nullptr ///< SubschemaRef of the field (For performance)
        );
        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        PropImplPtr enterUnionData(
            char const* _type = nullptr ///< type of the internal data of the union
        );
        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        PropImplPtr enterUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        );
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        PropImplPtr enterObjectSetItem(char const* _key ///< Key of the object
        );
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        PropImplPtr enterObjectSetItem(int64_t _key ///< Key of the object
        );
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        PropImplPtr enterMapItem(char const* _key ///< Key of the value
        );
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        PropImplPtr enterMapItem(int64_t _field ///< Key of the value
        );
        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        PropImplPtr enterArrayItem(size_t _index ///< index of the targeted element
        );
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        char const* getInstanceOf();

        /// @brief Set the InstanceOf field which point the prefab of the object
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void setInstanceOf(char const* _instanceOf);

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType();

        /// @return The index of the type of the Union
        /// @pre It is a Union
        size_t getUnionTypeIndex();
        DataType getDataType() const; ///< Get the DataType of a Node

        Subschema const* getSchema() const; ///< Get the Schema of the curent Node

        char const* getTypeName() const; ///< Get the Schema name of the curent Node

        DataType getMapKeyType() const; ///< @pre Map @brief Get the key type curent Map
        DataType getObjectSetKeyType() const; ///< @pre ObjectSet @brief Get the key type curent ObjectSet

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

        Cursor* getPrefab(); ///< Get the Cursor of the prefab
        nlohmann::json const* getRawJson(); ///< Get the underlying json node of the instance

        PropImplPtr shared_from_this(); ///< Create a new smart pointer to this

        PropImplPtr getParent() const; ///< Get the Cursor which created this one

    private:
        friend void decRef(Cursor* self);

        bool _loadInstanceOf();
        Cursor& _getLastLayer();
        Cursor const& _getLastLayer() const;
        void _buildPath(); ///< At the cursor location, ensure the json nodes exists in m_instance
        template <typename K, typename E>
        bool _countPrimSetKeyImpl(K _key, E&& _isEqual);
        template <typename E>
        PropImplPtr _enterItem(E&& _enter);
        void _checkInvariants() const;

        EntityLib* m_entityLib = nullptr;
        PropImplPtr prefab = nullptr;
        std::optional<FileCursor> defaultStorage; ///< Used to explore the defalt value in the schema
        size_t m_arraySize = 0;
        FileCursor m_instance;
        PropImplPtr m_parent = nullptr;
        size_t m_refCount = 0;
        DeleteCheck m_deleteCheck;
    };

    using PropImpl = Cursor;

    inline PropImpl* PropImpl::getPrefab()
    {
        return prefab.get();
    }

    inline PropImplPtr PropImpl::shared_from_this()
    {
        ++m_refCount;
        return PropImplPtr(this);
    }

    // Used temporarily to make the PR easier
    inline PropImpl const& PropImpl::_getLastLayer() const
    {
        return *this;
    }

    inline PropImpl& PropImpl::_getLastLayer()
    {
        return *this;
    }

    inline PropImplPtr PropImpl::getParent() const
    {
        if (m_parent != nullptr)
        {
            return m_parent->shared_from_this();
        }
        return {};
    }
} // namespace Ent
