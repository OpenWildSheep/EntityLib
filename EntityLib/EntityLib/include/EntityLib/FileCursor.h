/// @cond PRIVATE
#pragma once

#include <variant>
#include <ciso646>

#pragma warning(push)
#pragma warning(disable : 4464)
#include "../EntityLib.h"
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
    /// @remark FileCursor know nothing about prefab ("InstanceOf"). It only know about one file.
    struct ENTLIB_DLLEXPORT FileCursor
    {
        using Key = std::variant<char const*, size_t>;
        struct Schema
        {
            Ent::Subschema const* base = nullptr;
            nlohmann::json const* propDefVal = nullptr; ///< Property default values
        };
        struct Layer
        {
            Schema schema{};
            nlohmann::json* values{};
            Key additionalPath;
        };

        FileCursor();

        FileCursor(Ent::Subschema const* _schema, char const* _filePath);

        FileCursor(Ent::Subschema const* _schema, char const* m_filePath, nlohmann::json* _document);

        void init(Ent::Subschema const* _schema, char const* _filePath, nlohmann::json* _document);

        void reset(); ///< Reset FileCursor without freeing memory

        Layer* layerBegin(); ///< begin iterator to the Layer range

        Layer* layerEnd(); ///< (past-the-)end iterator to the Layer range

        Layer const* layerBegin() const; ///< begin const-iterator to the Layer range

        Layer const* layerEnd() const; ///< (past-the-)end const-iterator to the Layer range

        Layer& lastLayer(); ///< Last layer of the layer range

        Layer const& lastLayer() const; ///< Last layer (const) of the layer range

        size_t layerCount() const; ///< count of layer

        void pushBack(char const* _key); ///< @pre json is an array. @brief Push back _key in json

        void pushBack(int64_t _key); ///< @pre json is an array. @brief Push back _key in json

        /// Save to _filename or to the source file
        void save(char const* _filename = nullptr) const;

        /// Get the const pointer json node
        nlohmann::json const* getRawJson() const;

        /// Check if this Node exist
        bool isSetOrNull() const;

        /// Check if this Node exist and is NOT null
        bool isSet() const;

        /// Check if the json is null
        bool isNull() const;

        /// @brief Enter in the given field of the object
        /// @pre It is an object
        FileCursor& enterObjectField(char const* _field, SubschemaRef const* _fieldRef = nullptr);

        /// @brief Enter in the item of a UnionSet
        /// @pre It is a UnionSet
        FileCursor& enterUnionSetItem(char const* _field, Subschema const* _dataSchema = nullptr);

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        FileCursor& enterObjectSetItem(char const* _field);

        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        FileCursor& enterObjectSetItem(int64_t _field);

        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        FileCursor& enterMapItem(char const* _field);

        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        FileCursor& enterMapItem(int64_t _field);

        /// @brief Enter in the element of an Array
        /// @pre It is an Array
        FileCursor& enterArrayItem(size_t _index);

        /// @return The type of the Union
        /// @pre It is a Union
        char const* getUnionType() const;

        /// @brief Get the schema of the union inner type
        Ent::Subschema const* getUnionSchema() const;

        /// Check if the union has to be removed from its parent container (A UnionSet)
        bool isUnionRemoved() const;

        /// @brief Enter in the internal data of the union
        /// @pre It is a Union
        FileCursor& enterUnionData(char const* _unionType);

        /// Used after "enter..." function. From an item, get back to the parent container.
        FileCursor& exit();

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
            Layer& _lastLayer,
            Ent::FileCursor::Key const& _childName,
            Ent::Subschema const& _newLayerSchema,
            size_t _arraySize);

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

    private:
        /// @brief Enter in the object of an ObjectSet
        /// @pre It is an ObjectSet
        template <typename K, typename C>
        FileCursor& _enterObjectSetItemImpl(K _field, C&& _equalKey);
        /// @brief Enter in the value of a Map
        /// @pre It is an Map
        template <typename K, typename E>
        FileCursor& _enterMapItemImpl(K _field, E&& _isEqual);
        /// Get the mutable json node of the instance (or nullptr)
        nlohmann::json* _getRawJson();

        std::string m_filePath; ///< Path of the instance json file
        std::vector<Layer> m_layers; ///< stack of the Layers
        nlohmann::json* m_rootDoc = nullptr; ///< Root instance data
    };

} // namespace Ent
/// @endcond