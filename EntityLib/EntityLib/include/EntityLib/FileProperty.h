/// @cond PRIVATE
#pragma once

#include <variant>
#include <set>

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Schema.h"
#include "../../Tools.h"
#pragma warning(pop)

namespace Ent
{

    struct CmpStr
    {
        bool operator()(char const* a, char const* b) const
        {
            return strcmp(a, b) < 0;
        }
    };

    /// Navigate and extract data from .node(.entity/.scene) files
    ///
    /// @remark FileProperty know nothing about prefab ("InstanceOf"). It only know about one file.
    struct ENTLIB_DLLEXPORT FileProperty
    {
        /// Token of the NodeRef used to access to this FileProperty
        ///
        /// @remark It is not possible to ensure that the "char*" will be kept in memory, so it is needed to
        /// own the memory inside a std::string.
        using Key = std::variant<std::string, int64_t>;
        struct Schema
        {
            Subschema const* base = nullptr;
            nlohmann::json const* propDefVal = nullptr; ///< Property default values
        };

        enum class MapItemAction
        {
            None,
            Add,
            Remove
        };

        FileProperty();

        FileProperty(Subschema const* _schema, char const* _filePath);

        FileProperty(Subschema const* _schema, char const* m_filePath, nlohmann::json* _document);

        void pushBack(char const* _key) const; ///< @pre json is an array. @brief Push back _key in json

        void pushBack(int64_t _key) const; ///< @pre json is an array. @brief Push back _key in json

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const;

        /// Get the const pointer json node
        [[nodiscard]] nlohmann::json const* getRawJson() const;

        void setRawJson(nlohmann::json* _jsonNode);

        /// Check if this Node exist
        [[nodiscard]] bool hasJsonPointer() const;

        /// Check if this Node exist and is NOT null
        [[nodiscard]] bool isSet() const;

        /// Check if the json is null
        [[nodiscard]] bool isNull() const;

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        [[nodiscard]] FileProperty
        getObjectField(char const* _field, SubschemaRef const* _fieldRef = nullptr) const;

        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        [[nodiscard]] std::pair<FileProperty, MapItemAction>
        forceGetUnionSetItem(char const* _key, Subschema const* _dataSchema = nullptr) const;

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] std::pair<FileProperty, MapItemAction> forceGetObjectSetItem(char const* _key) const;

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        [[nodiscard]] std::pair<FileProperty, MapItemAction> forceGetObjectSetItem(int64_t _key) const;

        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        [[nodiscard]] std::pair<FileProperty, MapItemAction> forceGetMapItem(char const* _key) const;

        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        [[nodiscard]] std::pair<FileProperty, MapItemAction> forceGetMapItem(int64_t _key) const;

        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        [[nodiscard]] FileProperty getArrayItem(size_t _index) const;

        /// @return The type of the Union
        /// @pre It is a Union
        [[nodiscard]] char const* getUnionType() const;

        /// @brief Get the schema of the union inner type
        [[nodiscard]] Subschema const* getUnionSchema() const;

        /// Check if the union has to be removed from its parent container (A UnionSet)
        [[nodiscard]] bool isUnionRemoved() const;

        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        [[nodiscard]] std::pair<FileProperty, MapItemAction>
        forceGetUnionData(char const* _unionType) const;

        [[nodiscard]] Subschema const* getSchema() const; ///< Get the Schema of the curent Node

        /// @brief Get the default value related to the object field
        /// @pre this is a field of an object
        [[nodiscard]] nlohmann::json const* getPropertyDefaultValue() const;

        /// @brief Update this to become 'set' (has a m_values)
        /// @pre _parent.isSet()
        /// @param _parent last layer which was "set" (has a json node)
        void createChildNode(FileProperty& _parent);

        [[nodiscard]] size_t size() const; ///< @pre type==array. @brief Get the size of the array.
        void setSize(size_t _size) const; ///< @pre type==array. @brief Set the size of the array.
        template <typename T>
        void set(T&& _value); ///< @pre node os a primitive of type T. Set _value into the instance
        void setFloat(double _value); ///< @pre type==number. @brief Set _value in the instance
        void setInt(int64_t _value); ///< @pre type==integer. @brief Set _value in the instance
        void setString(char const* _value); ///< @pre type==string. @brief Set _value in the instance
        void setBool(bool _value); ///< @pre type==bool. @brief Set _value in the instance
        void setEntityRef(EntityRef const& _value); ///< @pre type==entityref. @brief Set _value in the instance
        void setUnionType(char const* _type) const; ///< @pre type==union. @brief Set inner type of the union
        template <typename T>
        [[nodiscard]] T get() const; ///< @pre Node is of type V. @brief Get the value in the given V type
        [[nodiscard]] double getFloat() const; ///< @pre type==number. @brief Get the value as double
        [[nodiscard]] int64_t getInt() const; ///< @pre type==integer. @brief Get the value as ingeter
        [[nodiscard]] char const* getString() const; ///< @pre type==string. @brief Get the value as string
        [[nodiscard]] bool getBool() const; ///< @pre type==bool. @brief Get the value as bool
        [[nodiscard]] EntityRef
        getEntityRef() const; ///< @pre type==entityref. @brief Get the value as entityref

        [[nodiscard]] Key const& getPathToken() const; ///< Get the path token used to get this from parent

        [[nodiscard]] DataType getMapKeyType() const; ///< Get the type of the ket of the map or set

        [[nodiscard]] bool countPrimSetKey(char const* _key);
        [[nodiscard]] bool countPrimSetKey(int64_t _key);

        void updateMapKeysString(std::set<char const*, CmpStr>& _keys, bool onlyRemoved = false) const;
        void updateMapKeysInt(std::set<int64_t>& _keys, bool onlyRemoved = false) const;
        void updatePrimSetKeysString(std::set<char const*, CmpStr>& _keys) const;
        void updatePrimSetKeysInt(std::set<int64_t>& _keys) const;
        void updateUnionSetKeysString(
            std::map<char const*, Subschema const*, CmpStr>& _keys, bool onlyRemoved = false) const;
        void updateObjectSetKeysString(
            std::set<char const*, CmpStr>& _keys, bool onlyRemoved = false) const;
        void updateObjectSetKeysInt(std::set<int64_t>& _keys, bool onlyRemoved = false) const;

        [[nodiscard]] std::set<char const*, CmpStr> getMapRemovedKeysString() const;
        [[nodiscard]] std::set<int64_t> getMapRemovedKeysInt() const;
        [[nodiscard]] std::map<char const*, Subschema const*, CmpStr> getUnionSetRemovedKeysString() const;
        [[nodiscard]] std::set<char const*, CmpStr> getObjectSetRemovedKeysString() const;
        [[nodiscard]] std::set<int64_t> getObjectSetRemovedKeysInt() const;

        [[nodiscard]] bool erasePrimSetKey(char const* _key);
        [[nodiscard]] bool erasePrimSetKey(int64_t _key);
        [[nodiscard]] bool eraseObjectSetItem(char const* _key, bool _isInPrefab);
        [[nodiscard]] bool eraseObjectSetItem(int64_t _key, bool _isInPrefab);
        [[nodiscard]] bool eraseUnionSetItem(char const* _key, bool _isInPrefab);
        [[nodiscard]] bool eraseMapItem(char const* _key, bool _isInPrefab);
        [[nodiscard]] bool eraseMapItem(int64_t _key, bool _isInPrefab);

        void unsetObjectField(FileProperty& _field) const;
        void unsetUnionData() const;
        void setToDefault(Subschema const* _parentSchema) const;
        void setToNull() const;

        [[nodiscard]] bool isRemovedObject() const;
        void unRemoveObject() const;

        [[nodiscard]] char const* getFilePath() const;

    private:
        [[nodiscard]] nlohmann::json::iterator
        _findUnionSetItem(char const* _key, bool _withRemoved) const;
        template <typename K>
        [[nodiscard]] nlohmann::json::iterator _findMapItem(K _key, bool _withRemoved) const;
        template <typename K>
        [[nodiscard]] nlohmann::json::iterator _findObjectSetItem(K _key, bool _withRemoved) const;
        template <typename K>
        [[nodiscard]] nlohmann::json::iterator _findPrimSetKey(K _key);
        template <typename K>
        [[nodiscard]] bool _countPrimSetKeyImpl(K _key);
        template <typename K>
        [[nodiscard]] bool _eraseMapItemImpl(K _key, bool _isInPrefab);
        template <typename K>
        [[nodiscard]] bool _eraseObjectSetItemImpl(K _key, bool _isInPrefab);
        template <typename K>
        [[nodiscard]] bool _erasePrimSetKeyImpl(K _key);
        /// @brief Find an element in a map/set
        /// @tparam K Key type
        /// @tparam GetKey Get the key in the element
        /// @tparam IsRemoved Is the element marked removed
        /// @param _withRemoved true to add the removed element in the result
        /// @param _key Searched key
        /// @param _isEqual Function to extract key from element
        /// @param _isRemoved Function to know if this element is removed
        /// @return
        template <typename K, typename GetKey, typename IsRemoved>
        [[nodiscard]] nlohmann::json::iterator
        _findArrayItem(bool _withRemoved, K _key, GetKey&& _getKey, IsRemoved&& _isRemoved) const;
        /// @brief Erase an element in a map/set
        /// @tparam K Key type
        /// @tparam FindItem Function to find the target element
        /// @tparam IsRemoved Function to know if the element is removed
        /// @tparam MarkRemoved Mask the element as removed
        /// @tparam PushBack Add a new removed element
        /// @param _key Searched key
        /// @param _isInPrefab This key still exist in prefab
        /// @param _findItem Function to the item in the array
        /// @param _isRemoved Function to know if this element is marked as removed
        /// @param _markRemoved Function mark an element has removed
        /// @param _pushBack Function to push back a new element marked as removed
        /// @return true if the element was removed (or marked has removed)
        template <typename K, typename FindItem, typename IsRemoved, typename MarkRemoved, typename PushBack>
        [[nodiscard]] bool _eraseImpl(
            K _key,
            bool _isInPrefab,
            FindItem&& _findItem,
            IsRemoved&& _isRemoved,
            MarkRemoved&& _markRemoved,
            PushBack&& _pushBack);

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        template <typename K>
        [[nodiscard]] std::pair<FileProperty, MapItemAction> _enterObjectSetItemImpl(K _key) const;
        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        template <typename K>
        [[nodiscard]] std::pair<FileProperty, MapItemAction> _enterMapItemImpl(K _key) const;
        /// Get the mutable json node of the instance (or nullptr)
        [[nodiscard]] nlohmann::json* _getRawJson() const;

        std::string m_filePath; ///< Path of the instance json file
        Schema m_schema{};
        nlohmann::json* m_wrapper{}; ///< Union wrapper if the Data in a UnionSet
        nlohmann::json* m_values{};
        Key m_key;
    };

    inline DataType FileProperty::getMapKeyType() const
    {
        return getSchema()->getMapKeyType();
    }

} // namespace Ent
/// @endcond
