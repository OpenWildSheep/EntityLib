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

        PropImpl(EntityLib* _entityLib);
        PropImpl(PropImpl const&) = delete;
        PropImpl& operator=(PropImpl const&) = delete;
        PropImpl(
            EntityLib* _entityLib,
            PropImplPtr _parent,
            Subschema const* _schema, ///< Schema of the file to load
            char const* _filename,
            VersionedJson& _document);
        PropImpl(
            EntityLib* _entityLib,
            PropImplPtr _parent,
            Subschema const* _schema, ///< Schema of the file to load
            char const* _filename,
            nlohmann::json* _doc,
            JsonMetaData* _metaData);

        PropImpl(
            EntityLib* _entityLib,
            PropImplPtr _parent,
            Subschema const* _schema, ///< Schema of the file to load
            char const* _filename);

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr);

        /// @brief The Node is default if no values are set inside
        [[nodiscard]] bool isDefault();

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
        /// @remake only look in the instance
        [[nodiscard]] char const* getInstanceOf();

        /// @return The first "InstanceOf" field, following prefabs, an empty string if set to empty, or nullptr if no prefab.
        /// @pre It is an Object
        /// @remark Will follow the prefab chain until a InstanceOf is found
        [[nodiscard]] char const* getFirstInstanceOf();

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
        [[nodiscard]] char const* getUnionType();

        /// @return The index of the type of the Union
        /// @pre It is a Union
        [[nodiscard]] size_t getUnionTypeIndex();
        [[nodiscard]] DataType getDataType(); ///< Get the DataType of a Node

        [[nodiscard]] Subschema const* getSchema(); ///< Get the Schema of the current Node

        [[nodiscard]] char const* getTypeName(); ///< Get the Schema name of the current Node

        [[nodiscard]] DataType getMapKeyType(); ///< @pre Map @brief Get the key type current Map
        [[nodiscard]] DataType
        getObjectSetKeyType(); ///< @pre ObjectSet @brief Get the key type current ObjectSet
        [[nodiscard]] DataType getPrimSetKeyType(); ///< @pre PrimitiveSet @brief Get the key type Set

        [[nodiscard]] size_t size(); ///< @return the size the this Node whatever it is.
        [[nodiscard]] bool contains(Key const& _key); ///< @pre map/set. @return true if it contains _key.
        [[nodiscard]] size_t arraySize(); ///< @return size of a simple array
        [[nodiscard]] bool empty(); ///< Check if size() == 0
        [[nodiscard]] bool isNull(); ///< @brief check if this Node is json null

        [[nodiscard]] std::set<char const*, CmpStr> getMapKeysString(); ///< Get map keys as strings
        [[nodiscard]] std::set<int64_t> getMapKeysInt(); ///< Get map keys as ints
        [[nodiscard]] std::set<int64_t> getPrimSetKeysInt(); ///< Get set elements as ints
        [[nodiscard]] std::set<char const*, CmpStr> getPrimSetKeysString(); ///< Get set elements as strings
        /// Get UnionSet keys as strings
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetKeysString();
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetKeysString(); ///< Get keys of objects as strings
        [[nodiscard]] std::set<int64_t> getObjectSetKeysInt(); ///< Get keys of objects as ints

        [[nodiscard]] std::set<char const*, CmpStr> getMapRemovedKeysString();
        [[nodiscard]] std::set<int64_t> getMapRemovedKeysInt();
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetRemovedKeysString();
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetRemovedKeysString();
        [[nodiscard]] std::set<int64_t> getObjectSetRemovedKeysInt();

        [[nodiscard]] bool mapContains(char const* _key); ///< Check if the map contains this _key
        [[nodiscard]] bool mapContains(int64_t _key); ///< Check if the map contains this _key
        [[nodiscard]] bool primSetContains(char const* _key); ///< Check if the set contains this _key
        [[nodiscard]] bool primSetContains(int64_t _key); ///< Check if the set contains this _key
        [[nodiscard]] bool unionSetContains(char const* _key); ///< Check if the UnionSet contains this _key
        [[nodiscard]] bool objectSetContains(char const* _key); ///< Check if the ObjectSet contains this _key
        [[nodiscard]] bool objectSetContains(int64_t _key); ///< Check if the ObjectSet contains this _key

        [[nodiscard]] bool isSet(); ///< Check if the Node is set in the instance
        void unset(); ///< Remove values in instance

        template <typename V>
        [[nodiscard]] V get(); ///< @pre Node is of type V. @brief Get the value in the given V type
        [[nodiscard]] double getFloat(); ///< @pre type==number. @brief Get the value as double
        [[nodiscard]] int64_t getInt(); ///< @pre type==integer. @brief Get the value as int
        [[nodiscard]] char const* getString(); ///< @pre type==string. @brief Get the value as string
        [[nodiscard]] bool getBool(); ///< @pre type==boolean. @brief Get the value as bool
        [[nodiscard]] EntityRef
        getEntityRef(); /// @pre type==entityRef. @brief Get the value as an Entity reference

        void setSize(size_t _size); ///< @pre type==array. @brief Set the size of the array.
        void clear();
        [[nodiscard]] PropImplPtr pushBack();
        void popBack();

        void setFloat(double _value); ///< @pre type==number. @brief Set _value in the instance
        void setInt(int64_t _value); ///< @pre type==integer. @brief Set _value in the instance
        void setString(char const* _value); ///< @pre type==string. @brief Set _value in the instance
        void setBool(bool _value); ///< @pre type==bool. @brief Set _value in the instance
        void setEntityRef(EntityRef const& _value); ///< @pre type==entityref. @brief Set _value in the instance
        PropImplPtr setUnionType(char const* _type); ///< @pre type==union. @brief Set _value in the instance

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

        bool erasePrimSetKey(char const* _key);
        bool erasePrimSetKey(int64_t _key);
        bool eraseObjectSetItem(char const* _key);
        bool eraseObjectSetItem(int64_t _key);
        bool eraseUnionSetItem(char const* _key);
        bool eraseMapItem(char const* _key);
        bool eraseMapItem(int64_t _key);

        void clearArray();
        void clearMap();
        void clearPrimSet();
        void clearObjectSet();
        void clearUnionSet();
        void clearObject();
        void clearUnion();

        [[nodiscard]] double getDefaultFloat();
        [[nodiscard]] int64_t getDefaultInt();
        [[nodiscard]] char const* getDefaultString();
        [[nodiscard]] bool getDefaultBool();
        [[nodiscard]] EntityRef getDefaultEntityRef();
        [[nodiscard]] size_t getDefaultSize();
        [[nodiscard]] char const* getDefaultUnionType();

        [[nodiscard]] PropImplPtr getLastSetPrefab();
        [[nodiscard]] bool hasPrefabValue();
        [[nodiscard]] double getPrefabFloat();
        [[nodiscard]] int64_t getPrefabInt();
        [[nodiscard]] char const* getPrefabString();
        [[nodiscard]] bool getPrefabBool();
        [[nodiscard]] EntityRef getPrefabEntityRef();
        [[nodiscard]] std::optional<int64_t> getPrefabSize();

        [[nodiscard]] std::vector<char const*>
        getFieldNames(); ///< @pre type==Ent::DataType::object @brief Get all field names

        [[nodiscard]] PropImpl* getPrefab() const; ///< Get the PropImpl of the prefab
        [[nodiscard]] nlohmann::json const* getRawJson(); ///< Get the underlying json node of the instance

        [[nodiscard]] PropImplPtr sharedFromThis() const; ///< Create a new smart pointer to this

        [[nodiscard]] PropImplPtr getParent() const; ///< Get the PropImpl which created this one

        [[nodiscard]] EntityLib* getEntityLib() const;

        [[nodiscard]] char const* getFilePath() const;

        [[nodiscard]] DataKind getDataKind();

        [[nodiscard]] PropImplPtr resolveNodeRef(char const* _nodeRef);

        [[nodiscard]] PropImplPtr getRootNode() const;

        [[nodiscard]] NodeRef makeNodeRef(PropImpl const& _target) const;

        [[nodiscard]] NodeRef makeAbsoluteNodeRef() const;

        [[nodiscard]] FileProperty::Key getPathToken() const;

        [[nodiscard]] std::pair<PropImplPtr, bool> forceGetUnionData(char const* _type = nullptr);
        [[nodiscard]] std::pair<PropImplPtr, bool>
        forceGetUnionSetItem(char const* _type, Subschema const* _dataSchema = nullptr);
        [[nodiscard]] std::pair<PropImplPtr, bool> forceGetObjectSetItem(char const* _key);
        [[nodiscard]] std::pair<PropImplPtr, bool> forceGetObjectSetItem(int64_t _key);
        [[nodiscard]] std::pair<PropImplPtr, bool> forceGetMapItem(char const* _key);
        [[nodiscard]] std::pair<PropImplPtr, bool> forceGetMapItem(int64_t _field);

        [[nodiscard]] bool sameValue(PropImpl& _other);

    private:
        PropImpl(PropImpl&&) = default;
        PropImpl& operator=(PropImpl&&) = default;

        friend void decRef(PropImpl* self);

        bool _loadInstanceOf();
        void _buildPath(); ///< At the cursor location, ensure the json nodes exists in m_instance
        template <typename K>
        [[nodiscard]] bool _countPrimSetKeyImpl(K _key);
        template <typename E>
        [[nodiscard]] std::pair<PropImplPtr, bool>
        _enterItem(E&& _enter, bool _isDefaultUnionType = false);
        void _checkInvariants() const;
        template <typename Container, typename F>
        [[nodiscard]] Container _getKeys(F const& getKeysInFile);
        void _checkKind(DataKind _expectedKind, char const* _funcName);
        template <typename K>
        auto _checkCanRename(K _newName);
        void _setDefault(
            Subschema const* _schema, char const* _filePath, nlohmann::json const* _document);
        [[nodiscard]] FileProperty const& _getDefault() const;
        void _reResolveFromRoot();
        [[nodiscard]] bool _doNeedReResolve() const;
        bool _reResolveIfNeeded();
        void _updateParentToResolved(); // Inform all parents the m_instance it is actually up to date (called by child)

        EntityLib* m_entityLib = nullptr;
        PropImplPtr m_prefab = nullptr;
        FileProperty m_default; ///< Used to explore the default value in the schema
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

    inline DataKind PropImpl::getDataKind()
    {
        _reResolveIfNeeded();
        return m_instance.getSchema()->getDataKind();
    }

    inline FileProperty::Key PropImpl::getPathToken() const
    {
        return m_instance.getPathToken();
    }

} // namespace Ent
