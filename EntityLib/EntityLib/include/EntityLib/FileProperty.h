/// @cond PRIVATE
#pragma once

#include <variant>

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../Schema.h"
#include "../Tools.h"
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
        using Key = std::variant<char const*, size_t>;
        struct Schema
        {
            Subschema const* base = nullptr;
            nlohmann::json const* propDefVal = nullptr; ///< Property default values
        };

        FileProperty();

        FileProperty(Subschema const* _schema, char const* _filePath);

        FileProperty(Subschema const* _schema, char const* m_filePath, nlohmann::json* _document);

        void pushBack(char const* _key); ///< @pre json is an array. @brief Push back _key in json

        void pushBack(int64_t _key); ///< @pre json is an array. @brief Push back _key in json

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const;

        /// Get the const pointer json node
        nlohmann::json const* getRawJson() const;

        void setRawJson(nlohmann::json* _jsonNode);

        /// Check if this Node exist
        bool isSetOrNull() const;

        /// Check if this Node exist and is NOT null
        bool isSet() const;

        /// Check if the json is null
        bool isNull() const;

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        FileProperty getObjectField(char const* _field, SubschemaRef const* _fieldRef = nullptr);

        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        FileProperty getUnionSetItem(char const* _field, Subschema const* _dataSchema = nullptr);

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        FileProperty getObjectSetItem(char const* _field);

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        FileProperty getObjectSetItem(int64_t _field);

        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        FileProperty getMapItem(char const* _field);

        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        FileProperty getMapItem(int64_t _field);

        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        FileProperty getArrayItem(size_t _index);

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType() const;

        /// @brief Get the schema of the union inner type
        Subschema const* getUnionSchema() const;

        /// Check if the union has to be removed from its parent container (A UnionSet)
        bool isUnionRemoved() const;

        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        FileProperty getUnionData(char const* _unionType);

        Subschema const* getSchema() const; ///< Get the Schema of the curent Node

        /// @brief Get the default value related to the object field
        /// @pre this is a field of an object
        nlohmann::json const* getPropertyDefaultValue() const;

        /// @brief Create inside the last layer _lastSet the json Node of the new layer
        /// @param _lastLayer last layer which was "set" (has a json node)
        /// @param _childName path to the direct child node which is the next layer
        /// @param _newLayerSchema schema of the child node
        /// @param _arraySize If the child is an array : Size of the array (from prefab)
        /// @return json pointer to the child node
        static nlohmann::json* createChildNode(
            FileProperty& _lastLayer,
            Key const& _childName,
            Subschema const& _newLayerSchema,
            size_t _arraySize);

        size_t size() const; ///< @pre type==array. @brief Get the size of the array.
        void setSize(size_t _size); ///< @pre type==array. @brief Set the size of the array.
        template <typename T>
        void set(T&& _value); ///< @pre node os a primitive of type T. Set _value into the instance
        void setFloat(double _value); ///< @pre type==number. @brief Set _value in the instance
        void setInt(int64_t _value); ///< @pre type==integer. @brief Set _value in the instance
        void setString(char const* _value); ///< @pre type==string. @brief Set _value in the instance
        void setBool(bool _value); ///< @pre type==bool. @brief Set _value in the instance
        void setEntityRef(EntityRef const& _value); ///< @pre type==entityref. @brief Set _value in the instance
        void setUnionType(char const* _type); ///< @pre type==union. @brief Set inner type of the union
        template <typename T>
        T get() const; ///< @pre Node is of type V. @brief Get the value in the given V type
        double getFloat() const; ///< @pre type==number. @brief Get the value as double
        int64_t getInt() const; ///< @pre type==integer. @brief Get the value as ingeter
        char const* getString() const; ///< @pre type==string. @brief Get the value as string
        bool getBool() const; ///< @pre type==bool. @brief Get the value as bool
        EntityRef getEntityRef() const; ///< @pre type==entityref. @brief Get the value as entityref

        Key const& getPathToken() const;

    private:
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        template <typename K, typename C>
        FileProperty _enterObjectSetItemImpl(K _field, C&& _equalKey);
        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        template <typename K, typename E>
        FileProperty _enterMapItemImpl(K _field, E&& _isEqual);
        /// Get the mutable json node of the instance (or nullptr)
        nlohmann::json* _getRawJson();

        std::string m_filePath; ///< Path of the instance json file
        Schema m_schema{};
        nlohmann::json* m_values{};
        Key m_key;
    };
} // namespace Ent
/// @endcond
