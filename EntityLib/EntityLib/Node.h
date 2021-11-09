#pragma once

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Override.h"
#include "../Array.h"
#include "../Union.h"
#include "../Object.h"
#pragma warning(pop)

#include "include/Schema.h"

namespace Ent
{
    struct EntityRef
    {
        /// @brief string representation of this entity ref, works like a file path, always relative.
        String entityPath;

        bool operator==(EntityRef const& _rho) const
        {
            return entityPath == _rho.entityPath;
        }

        bool operator!=(EntityRef const& _rho) const
        {
            return !(*this == _rho);
        }
    };

    /// @brief The possible source of an Override value
    enum class OverrideValueSource
    {
        /// Value is set in this Override. Write the "InstanceOf" field.
        Override,
        /// Value is set in the Prefab or in this Override. Don't write the "InstanceOf" field.
        OverrideOrPrefab,
        /// Value can be any source: Override, Prefab or the default value. Don't write the "InstaneOf" field.
        Any,
    };

    /// \cond PRIVATE
    void destroyAndFree(Node* ptr); ///< Internally used by the Node memory Pool
    Pool<Node>& getPool(Node const* ptr); ///< Internally used by the Node memory Pool
    /// \endcond

    // *********************************** Scene/Entity/Component/Node ****************************

    struct Subschema;
    class EntityLib;

    struct Node;

    /// Property node. Can contains any type in Ent::DataType
    struct ENTLIB_DLLEXPORT Node
    {
        /// @cond PRIVATE
        using Value = std::variant<
            Null,
            Override<String>,
            Override<double>,
            Override<int64_t>,
            Object,
            Array,
            Override<bool>,
            Override<EntityRef>,
            Union>;
        Node(Value _val, Subschema const* _schema);

        /// @brief return the node containing the data and the type nodes (An element of the oneOf array)
        /// @pre type==Ent::DataType::oneOf
        /// @remark For internal use
        Node const* getUnionDataWrapper() const;
        /// @endcond

        DataType getDataType() const; ///< Type of this Node. @see Ent::DataType

        // Object
        Node* at(char const* _field); ///< @pre type==Ent::DataType::object @brief Get the _field
        Node const* at(char const* _field) const; ///< @pre type==Ent::DataType::object  @brief Get the _field
        bool count(char const* _field)
            const; ///< @pre type==Ent::DataType::object @brief true if a field with this name exist
        std::vector<char const*>
        getFieldNames() const; ///< @pre type==Ent::DataType::object @brief Get all field names
        std::map<char const*, Node const*>
        getFields() const; ///< @pre type==Ent::DataType::object @brief Get all fields
        char const* getInstanceOf() const; ///< @pre type==Ent::DataType::object @brief path to the tmpl Node

        // Array
        Node* at(size_t _index); ///< @pre type==Ent::DataType::array. @brief Get the item at _index
        Node const* at(size_t _index) const; ///< @pre type==Ent::DataType::array. @brief Get the item at _index
        size_t size() const; ///< @pre type==Ent::DataType::array. @brief Get array size
        /// @pre type==Ent::DataType::array.
        /// @brief Get the raw Override value of the array size.
        /// @param _location the desired Override value location.
        /// @return the array size at the given Override value location.
        tl::optional<size_t> getRawSize(OverrideValueLocation _location) const;
        std::vector<Node const*> getItems() const; ///< @pre type==Ent::DataType::array. @brief Get all items
        std::vector<Node*> getItems(); ///< @pre type==Ent::DataType::array. @brief Get all items
        Node* push(); ///< @pre type==Ent::DataType::array. @brief Add a new item at the end of array
        void pop(); ///< @pre type==Ent::DataType::array. @brief Remove an item at the end of array
        void clear(); ///< @pre type==Ent::DataType::array. @brief Remove all items in array
        bool empty() const; ///< @pre type==Ent::DataType::array. @brief return true if array is empty
        // Array - map
        bool mapErase(char const* _key); ///< @pre isMapOrSet() @brief erase the item with _key or return false
        Node* mapGet(char const* _key); ///< @pre isMapOrSet() @brief Get the item with _key or nullptr
        Node const* mapGet(char const* _key) const; ///< @pre isMapOrSet() @brief Get the item with _key or nullptr
        Node* mapInsert(char const* _key); ///< @pre isMapOrSet() @brief Insert a new item at the given _key
        void mapInsert(char const* _key, NodeUniquePtr _newNode);
        void mapInsert(int64_t _key, NodeUniquePtr _newNode);
        /// @pre isMapOrSet()
        /// @brief Insert a new item at the given _key
        Node* mapInsertInstanceOf(char const* _prefabPath);
        /// @brief Copy the _key Node into the _newkey Node. Will update the keyField to _newkey if relevant.
        /// @pre The _key Node is not present in the prefab.
        Node* mapRename(char const* _key, char const* _newkey);
        bool mapErase(int64_t _key); ///< @pre isMapOrSet() @brief Erase the item at the given _key
        Node* mapGet(int64_t _key); ///< @pre isMapOrSet() @brief Get the item with _key or nullptr
        Node const* mapGet(int64_t _key) const; ///< @pre isMapOrSet() @brief Get the item with _key or nullptr
        Node* mapInsert(int64_t _key); ///< @pre isMapOrSet() @brief Insert a new item at the given _key
        /// @brief Copy the _key Node into the _newkey Node. Will update the keyField to _newkey if relevant.
        /// @pre The _key Node is not present in the prefab.
        Node* mapRename(int64_t _key, int64_t _newkey);
        bool isMapOrSet() const; ///< @return true if type==Ent::DataType::array and overridePolicy is map or set
        DataType getKeyType() const; ///< @pre isMapOrSet() @return the Ent::DataType of the key
        /// @pre isMapOrSet()
        /// @pre getKeyType() == string or getKeyType() == entityRef
        /// @return All keys of the map, as String
        std::vector<String> getKeysString() const;
        /// @pre isMapOrSet()
        /// @pre getKeyType() == integer
        /// @return All keys of the map, as int64_t
        std::vector<int64_t> getKeysInt() const;
        std::vector<NodeUniquePtr> releaseAllElements();

        // Union
        Node* getUnionData(); ///< @pre type==Ent::DataType::oneOf. @brief return the underlying data
        Node const* getUnionData() const; ///< @pre type==Ent::DataType::oneOf. @brief return the underlying data
        /// @brief Get the type inside the union
        /// @pre type==Ent::DataType::oneOf
        char const* getUnionType() const;
        /// @brief Get the index of the type inside the union
        /// @pre type==Ent::DataType::oneOf
        size_t getUnionTypeIndex() const;
        /// @brief Change the type inside the union
        /// @pre type==Ent::DataType::oneOf
        /// @pre type match with a type declared inside the json "oneOf"
        Node* setUnionType(char const* _type);

        // Value
        double getFloat() const; ///< @pre number or integer. @brief Get the value as double
        int64_t getInt() const; ///< @pre integer. @brief Get the value as int
        char const* getString() const; ///< @pre Ent::DataType == string. @brief Get the value as string
        bool getBool() const; ///< @pre type==Ent::DataType::boolean. @brief Get the value as bool
        EntityRef getEntityRef()
            const; ///< @pre type==Ent::DataType::entityRef. @brief Get the value as an Entity reference

        const Value& GetRawValue()
            const; ///< returns a reference to the raw Value (variant) stored at this node. Useful to write visitors.

        void setFloat(double _val); ///< @pre type==Ent::DataType::number. @brief Set the double value
        void setInt(int64_t _val); ///< @pre type==Ent::DataType::integer. @brief Set the int64_t value
        void setString(char const* _val); ///< @pre type==Ent::DataType::string. @brief Set the string value
        void setBool(bool _val); ///< @pre type==Ent::DataType::boolean. @brief Set the bool value
        void setEntityRef(EntityRef _entityRef); ///< @pre type==Ent::DataType::entityRef. @brief Set the Entity reference value

        /// Fallback to the prefab or default value. The value will not be saved in json.
        /// If the type is Array, Object or Union, \b unset will be applied recursively
        void unset();

        /// Check if the value is set explicitly (it override the prefab or default value)
        /// @remark return true when object or array
        bool isSet() const;

        /// @brief Recursively check if there is an override inside.
        ///
        /// If there is no override, there is no need to save it.
        bool hasOverride() const;

        /// @brief Recursively check if value is set in a prefab (overriden or not by this Node)
        bool hasPrefabValue() const;

        /// @brief Check recursively if this node content match the given value source.
        bool matchValueSource(OverrideValueSource _source) const;

        /// \cond PRIVATE
        /// Create a Node with the same value but which doesn't rely on prefab.
        NodeUniquePtr detach() const;

        /// Create a Node which is an "instance of" this one. With no override.
        NodeUniquePtr makeInstanceOf() const;
        /// \endcond

        /// @remark obsolete. Use resetInstanceOf
        void setInstanceOf(char const* _prefabNodePath);
        /// Reset the Node to be an instance of the given \b _prefabNodePath
        ///
        /// @warning All sub-nodes into \b _node will be invalidated
        /// @param _prefabNodePath path to the prefab Node (relative to RawData)
        void resetInstanceOf(char const* _prefabNodePath);
        void resetInstanceOf();

        /// @brief Change this Entity to be an instance of the given \b _newPrefab, keeping
        /// all internal values the same.
        /// @param _newPrefab path to the new prefab
        void changeInstanceOf(char const* _newPrefab);

        /// @brief Take all values set in this and set them into \b _dest
        ///   BUT do not change the prefab of _dest
        void applyAllValuesButPrefab(Node& _dest, CopyMode _copyMode) const;

        void applyToPrefab();

        bool hasDefaultValue() const; ///< false if something was set in instance or prefab

        bool isDefault() const; ///< true if the value was set in a prefab or in the instance

        /// Dump this Node as a json value
        nlohmann::json toJson(
            OverrideValueSource _dumpedValueSource =
                OverrideValueSource::Override, ///< Dump only fields with given value source
            bool _superKeyIsTypeName =
                false, ///< Super sub-node are dumped using their type name for key instead of "Super"
            std::function<void(EntityRef&)> const& _entityRefPreProc = {},
            bool _saveUnionIndex = false) const;

        /// @brief Save as a Node prefab
        /// @pre Node is an Object
        void saveNode(std::filesystem::path const& path) const;

        double getDefaultFloat() const; ///< @pre number or integer. @brief Get the default value as double
        int64_t getDefaultInt() const; ///< @pre integer. @brief Get the default value as int
        char const* getDefaultString() const; ///< @pre DataType == string. @brief Get the default value as string
        bool getDefaultBool() const; ///< @pre DataType == bool. @brief Get the default value as bool
        EntityRef getDefaultEntityRef()
            const; ///< @pre DataType == EntityRef. @brief Get the default value as EntityRef

        /// @pre number or integer.
        /// @brief Get the raw Override value as double.
        /// @param _location the desired Override value location.
        /// @return the double value at the given Override value location.
        tl::optional<double> getRawFloat(OverrideValueLocation _location) const;
        /// @pre integer.
        /// @brief Get the raw Override value as int.
        /// @param _location the desired Override value location.
        /// @return the int value at the given Override value location.
        tl::optional<int> getRawInt(OverrideValueLocation _location) const;
        /// @pre DataType == string.
        /// @brief Get the raw Override value as string.
        /// @param _location the desired Override value location.
        /// @return the string value at the given Override value location.
        tl::optional<char const*> getRawString(OverrideValueLocation _location) const;
        /// @pre DataType == bool.
        /// @brief Get the raw Override value as bool.
        /// @param _location the desired Override value location.
        /// @return the bool value at the given Override value location.
        tl::optional<bool> getRawBool(OverrideValueLocation _location) const;
        /// @pre DataType == EntityRef.
        /// @brief Get the raw Override value as EntityRef.
        /// @param _location the desired Override value location.
        /// @return the EntityRef value at the given Override value location.
        tl::optional<EntityRef> getRawEntityRef(OverrideValueLocation _location) const;

        /// Get the absolute full link of the Subschema type, or nullptr if the is no
        /// Example : "./RuntimeComponents.json#/definitions/VoxelSimulationGD"
        char const* getTypeName() const;

        Subschema const* getSchema() const; ///< Get the Node schema.

        void computeMemory(MemoryProfiler& prof) const;

        EntityLib* getEntityLib() const;

        /// Take all values set in this and set them into \b _dest
        void applyAllValues(Node& _dest, CopyMode _copyMode) const;

        Node* getParentNode();
        Node const* getParentNode() const;
        void updateParents(); ///< call setParentNode(this) on all subnodes
        void checkParent(Node const* _parentNode) const; ///< Check that all subnode's parentNode point to this
        void setParentNode(Node* _parentNode); ///< set the parentNode

        void setAddedInInsance(bool _added)
        {
            addedInInstance = _added;
        }

        NodeUniquePtr clone() const;

        /// @brief Get the root Node of the document
        Node const* getRootNode() const;

        /// @brief Make a NodeRef going from this to _target
        NodeRef makeNodeRef(Node const* _target) const;

        /// @brief Get the target pointed by _nodeRef, starting from this
        Node const* resolveNodeRef(char const* _nodeRef) const;

        /// @brief Get the target pointed by _nodeRef, starting from this
        Node* resolveNodeRef(char const* _nodeRef);

        /// @brief Get the NodeRef from root to this
        NodeRef makeAbsoluteNodeRef() const;

    private:
        Node(Node const& _node) = delete;
        Node(Node&& _node) noexcept = delete;
        Node& operator=(Node const& _node) = delete;
        Node& operator=(Node&& _node) noexcept = delete;

        void checkMap(char const* _calledMethod) const; ///< Throw exception if not a set/map

        Node* parentNode = nullptr;
        Subschema const* schema = nullptr; ///< The Node schema. To avoid to pass it to each call
        Value value; ///< Contains one of the types accepted by a Node
        bool addedInInstance = false;

        friend EntityLib;
    };

} // namespace Ent
