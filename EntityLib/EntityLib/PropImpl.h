#pragma once

#include <variant>
#include <set>
#include <deque>

#include "include/EntityLib/FileProperty.h"

#pragma warning(push)
#pragma warning(disable : 4464)
#include "Tools.h"
#pragma warning(pop)

namespace Ent
{
    class EntityLib;

    struct PropImpl;

    /// Functor used by PropImplPtr
    /// to decrement the refcounter on the unique_ptr destruction,
    /// and delete the PropImpl if refcount == 0.
    struct DecRef
    {
        template <typename C>
        void operator()(C* _cursorPtr)
        {
            decRef(_cursorPtr);
        }
    };

    /// smart pointer to a PropImpl (use reference counting)
    using PropImplPtr = std::unique_ptr<PropImpl, DecRef>;

    /// @brief Internal implementation of a Property
    struct ENTLIB_DLLEXPORT PropImpl
    {
    public:
        using Key = std::variant<std::string, size_t>;

        PropImpl();
        PropImpl(PropImpl const&) = delete;
        PropImpl& operator=(PropImpl const&) = delete;
        PropImpl(PropImpl&&) = delete;
        PropImpl& operator=(PropImpl&&) = delete;
        PropImpl(
            EntityLib* _entityLib,
            PropImplPtr _parent,
            Subschema const* _schema, ///< Schema of the file to load
            char const* _filename,
            nlohmann::json* _doc);

        PropImpl(
            EntityLib* _entityLib,
            PropImplPtr _parent,
            Subschema const* _schema, ///< Schema of the file to load
            char const* _filename);

        void
        setDefault(Subschema const* _schema, char const* _filePath, nlohmann::json const* _document);
        [[nodiscard]] FileProperty const& getDefault() const;

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const;

        /// @brief The Node is default if no values are set inside
        [[nodiscard]] bool isDefault() const;

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        [[nodiscard]] PropImplPtr getObjectField(
            char const* _field, ///< field to enter in
            SubschemaRef const* _fieldRef = nullptr ///< SubschemaRef of the field (For performance)
        );
        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] PropImplPtr getUnionData(
            char const* _type = nullptr ///< type of the internal data of the union
        );
        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] PropImplPtr getUnionSetItem(
            char const* _type, ///< Type of the item
            Subschema const* _dataSchema = nullptr ///< Schema of the item (For performance)
        );
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] PropImplPtr getObjectSetItem(char const* _key ///< Key of the object
        );
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] PropImplPtr getObjectSetItem(int64_t _key ///< Key of the object
        );
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] PropImplPtr getMapItem(char const* _key ///< Key of the value
        );
        /// @brief Enter in the value of an Map
        /// @pre It is an Map
        [[nodiscard]] PropImplPtr getMapItem(int64_t _field ///< Key of the value
        );
        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        [[nodiscard]] PropImplPtr getArrayItem(size_t _index ///< index of the targeted element
        );
        /// @return The "InstanceOf" field, an empty string if set to empty, or nullptr if unset.
        /// @pre It is an Object
        [[nodiscard]] char const* getInstanceOf();

        /// @brief Set the prefab (and reset all overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void resetInstanceOf(char const* _instanceOf);

        /// @brief Set the prefab (and keep overriden values)
        /// @pre It is an Object
        /// @pre _instanceOf != nullptr
        /// @remark setInstanceOf("") mean explicitly set
        void changeInstanceOf(char const* _instanceOf);

        [[nodiscard]] PropImplPtr makeInstanceOf();

        /// @return The type of the Union
        /// @pre It is a Union
        [[nodiscard]] char const* getUnionType() const;

        /// @return The index of the type of the Union
        /// @pre It is a Union
        [[nodiscard]] size_t getUnionTypeIndex() const;
        [[nodiscard]] DataType getDataType() const; ///< Get the DataType of a Node

        [[nodiscard]] Subschema const* getSchema() const; ///< Get the Schema of the current Node

        [[nodiscard]] char const* getTypeName() const; ///< Get the Schema name of the current Node

        [[nodiscard]] DataType getMapKeyType() const; ///< @pre Map @brief Get the key type current Map
        [[nodiscard]] DataType
        getObjectSetKeyType() const; ///< @pre ObjectSet @brief Get the key type current ObjectSet

        [[nodiscard]] size_t size(); ///< @return the size the this Node whatever it is.
        [[nodiscard]] bool contains(Key const& _key); ///< @pre map/set. @return true if it contains _key.
        [[nodiscard]] size_t arraySize() const; ///< @return size of a simple array
        [[nodiscard]] bool empty(); ///< Check if size() == 0
        [[nodiscard]] bool isNull() const; ///< @brief check if this Node is json null

        [[nodiscard]] std::set<char const*, CmpStr> getMapKeysString(); ///< Get map keys as strings
        [[nodiscard]] std::set<int64_t> getMapKeysInt(); ///< Get map keys as ints
        [[nodiscard]] std::set<int64_t> getPrimSetKeysInt(); ///< Get set elements as ints
        [[nodiscard]] std::set<char const*, CmpStr> getPrimSetKeysString(); ///< Get set elements as strings
        /// Get UnionSet keys as strings
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString();
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetKeysString(); ///< Get keys of objects as strings
        [[nodiscard]] std::set<int64_t> getObjectSetKeysInt(); ///< Get keys of objects as ints

        [[nodiscard]] std::set<char const*, CmpStr> getMapRemovedKeysString() const;
        [[nodiscard]] std::set<int64_t> getMapRemovedKeysInt() const;
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetRemovedKeysString() const;
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetRemovedKeysString() const;
        [[nodiscard]] std::set<int64_t> getObjectSetRemovedKeysInt() const;

        [[nodiscard]] bool mapContains(char const* _key); ///< Check if the map contains this _key
        [[nodiscard]] bool mapContains(int64_t _key); ///< Check if the map contains this _key
        [[nodiscard]] bool primSetContains(char const* _key); ///< Check if the set contains this _key
        [[nodiscard]] bool primSetContains(int64_t _key); ///< Check if the set contains this _key
        [[nodiscard]] bool unionSetContains(char const* _key); ///< Check if the UnionSet contains this _key
        [[nodiscard]] bool objectSetContains(char const* _key); ///< Check if the ObjectSet contains this _key
        [[nodiscard]] bool objectSetContains(int64_t _key); ///< Check if the ObjectSet contains this _key

        [[nodiscard]] bool isSet() const; ///< Check if the Node is set in the instance
        void unset(); ///< Remove values in instance

        template <typename V>
        [[nodiscard]] V get() const; ///< @pre Node is of type V. @brief Get the value in the given V type
        [[nodiscard]] double getFloat() const; ///< @pre type==number. @brief Get the value as double
        [[nodiscard]] int64_t getInt() const; ///< @pre type==integer. @brief Get the value as int
        [[nodiscard]] char const* getString() const; ///< @pre type==string. @brief Get the value as string
        [[nodiscard]] bool getBool() const; ///< @pre type==boolean. @brief Get the value as bool
        [[nodiscard]] EntityRef
        getEntityRef() const; /// @pre type==entityRef. @brief Get the value as an Entity reference

        void setSize(size_t _size); ///< @pre type==array. @brief Set the size of the array.
        void clear();
        [[nodiscard]] PropImplPtr push_back();
        void pop_back();

        void setFloat(double _value); ///< @pre type==number. @brief Set _value in the instance
        void setInt(int64_t _value); ///< @pre type==integer. @brief Set _value in the instance
        void setString(char const* _value); ///< @pre type==string. @brief Set _value in the instance
        void setBool(bool _value); ///< @pre type==bool. @brief Set _value in the instance
        void setEntityRef(EntityRef const& _value); ///< @pre type==entityref. @brief Set _value in the instance
        [[nodiscard]] PropImplPtr
        setUnionType(char const* _type); ///< @pre type==union. @brief Set _value in the instance

        void buildPath(); ///< Build json path but not set any value. Usefull for UnionSet items
        void insertPrimSetKey(char const* _key); ///< Insert _key in the set (or do nothing if already in)
        void insertPrimSetKey(int64_t _key); ///< Insert _key in the set (or do nothing if already in)
        [[nodiscard]] PropImplPtr insertObjectSetItem(
            char const* _key); ///< Insert _key in the set (or do nothing if already in)
        [[nodiscard]] PropImplPtr insertInstanceObjectSetItem(char const* _prefabPath);
        [[nodiscard]] PropImplPtr
        insertObjectSetItem(int64_t _key); ///< Insert _key in the set (or do nothing if already in)
        [[nodiscard]] PropImplPtr insertUnionSetItem(char const* _key);
        [[nodiscard]] PropImplPtr insertMapItem(char const* _key);
        [[nodiscard]] PropImplPtr insertMapItem(int64_t _key);

        [[nodiscard]] bool erasePrimSetKey(char const* _key);
        [[nodiscard]] bool erasePrimSetKey(int64_t _key);
        [[nodiscard]] bool eraseObjectSetItem(char const* _key);
        [[nodiscard]] bool eraseObjectSetItem(int64_t _key);
        [[nodiscard]] bool eraseUnionSetItem(char const* _key);
        [[nodiscard]] bool eraseMapItem(char const* _key);
        [[nodiscard]] bool eraseMapItem(int64_t _key);

        [[nodiscard]] double getDefaultFloat() const;
        [[nodiscard]] int64_t getDefaultInt() const;
        [[nodiscard]] char const* getDefaultString() const;
        [[nodiscard]] bool getDefaultBool() const;
        [[nodiscard]] EntityRef getDefaultEntityRef() const;
        [[nodiscard]] size_t getDefaultSize() const;

        [[nodiscard]] PropImplPtr getLastSetPrefab() const;
        [[nodiscard]] bool hasPrefabValue() const;
        [[nodiscard]] double getPrefabFloat() const;
        [[nodiscard]] int64_t getPrefabInt() const;
        [[nodiscard]] char const* getPrefabString() const;
        [[nodiscard]] bool getPrefabBool() const;
        [[nodiscard]] EntityRef getPrefabEntityRef() const;
        [[nodiscard]] std::optional<int64_t> getPrefabSize() const;

        [[nodiscard]] std::vector<char const*>
        getFieldNames() const; ///< @pre type==Ent::DataType::object @brief Get all field names

        [[nodiscard]] PropImpl* getPrefab() const; ///< Get the PropImpl of the prefab
        [[nodiscard]] nlohmann::json const* getRawJson() const; ///< Get the underlying json node of the instance

        [[nodiscard]] PropImplPtr sharedFromThis() const; ///< Create a new smart pointer to this

        [[nodiscard]] PropImplPtr getParent() const; ///< Get the PropImpl which created this one

        [[nodiscard]] EntityLib* getEntityLib() const;

        [[nodiscard]] char const* getFilePath() const;

        [[nodiscard]] DataKind getDataKind() const;

        [[nodiscard]] PropImplPtr resolveNodeRef(char const* _nodeRef);

        [[nodiscard]] PropImplPtr getRootNode() const;

        [[nodiscard]] NodeRef makeNodeRef(PropImpl const& _target) const;

        [[nodiscard]] NodeRef makeAbsoluteNodeRef() const;

        [[nodiscard]] FileProperty::Key getPathToken() const; 

    private:
        friend void decRef(PropImpl* self);

        bool _loadInstanceOf();
        void _buildPath(); ///< At the cursor location, ensure the json nodes exists in m_instance
        template <typename K>
        [[nodiscard]] bool _countPrimSetKeyImpl(K _key);
        template <typename E>
        [[nodiscard]] PropImplPtr _enterItem(E&& _enter);
        void _checkInvariants() const;
        template <typename Container, typename F>
        [[nodiscard]] Container getKeys(F const& getKeysInFile);

        EntityLib* m_entityLib = nullptr;
        PropImplPtr m_prefab = nullptr;
        FileProperty m_default; ///< Used to explore the default value in the schema
        size_t m_arraySize = 0;
        FileProperty m_instance;
        PropImplPtr m_parent = nullptr;
        mutable size_t m_refCount = 0;
        DeleteCheck m_deleteCheck;
    };

    inline PropImpl* PropImpl::getPrefab() const
    {
        return m_prefab.get();
    }

    inline PropImplPtr PropImpl::sharedFromThis() const
    {
        ++m_refCount;
        return PropImplPtr(const_cast<PropImpl*>(this));
    }

    inline PropImplPtr PropImpl::getParent() const
    {
        if (m_parent != nullptr)
        {
            return m_parent->sharedFromThis();
        }
        return {};
    }

    inline EntityLib* PropImpl::getEntityLib() const
    {
        return m_entityLib;
    }

    inline char const* PropImpl::getFilePath() const
    {
        return m_instance.getFilePath();
    }

    inline DataKind PropImpl::getDataKind() const
    {
        return m_instance.getSchema()->getDataKind();
    }

    inline FileProperty::Key PropImpl::getPathToken() const
    {
        return m_instance.getPathToken();
    }

} // namespace Ent
