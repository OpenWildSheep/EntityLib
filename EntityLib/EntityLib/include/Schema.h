#pragma once

#pragma warning(push, 0)
#include <map>
#include <memory>
#include <vector>
#include <variant>
#include <optional>

#include "../external/json.hpp"
#pragma warning(pop)

#include "EntityLibCore.h"

/// EntityLib namespace
namespace Ent
{
    /// Internal type of a property Node
    enum class DataType
    {
        null,
        string, ///< Contains a string
        number, ///< Contains a number (real)
        integer, ///< Contains an integer
        object, ///< Contains a json object (it has properties)
        array, ///< Contains an array . It can be singular (one type for all) or linear (one type per element)
        boolean, ///< Contains a boolean value
        entityRef, ///< Contains a string which is a path to an Entity
        oneOf, ///< It is actually a union type, but union is a C keyword
        COUNT
    };

    /// Detailed schema type.
    /// Especially with array, which can be unionSet, map, objectSet, primitiveSet or simple array
    enum class DataKind
    {
        string, ///< Contains a string
        number, ///< Contains a number (real)
        integer, ///< Contains an integer
        object, ///< Contains a json object (it has properties)
        array, ///< Contains an array . It can be singular (one type for all) or linear (one type per element)
        boolean, ///< Contains a boolean value
        entityRef, ///< Contains a string which is a path to an Entity
        union_, ///< It is actually a union type, but union is a C keyword
        unionSet,
        map,
        objectSet,
        primitiveSet,
        COUNT
    };

    /// @cond PRIVATE
    using Null = std::nullptr_t;
    /// @endcond

    // *************************************** Subschema ******************************************

    struct SubschemaRef;
    class Schema;

    /// Definition of a json Node
    struct ENTLIB_DLLEXPORT Subschema
    {
        /// @cond PRIVATE
        Subschema() = default;
        Subschema(Subschema const&) = delete;
        Subschema& operator=(Subschema const&) = delete;
        Subschema(Subschema&&) noexcept = default;
        Subschema& operator=(Subschema&&) noexcept = default;
        DeleteCheck deleteCheck;

        /// @brief Get the Subschema related to the given \p _subtype (className)
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        /// @throw BadUnionType if \p _subtype is not listed in the oneOf field
        std::pair<Subschema const*, size_t> getUnionTypeWrapper(char const* _subtype) const;
        /// @endcond

        Schema* rootSchema{};
        DataType type = DataType::null; ///< type of this Subschema. @see Ent::DataType
        bool required = false; ///< Is this property required?
        std::map<std::string, SubschemaRef> properties; ///< If type == Ent::DataType::object, child properties
        size_t maxItems =
            static_cast<size_t>(-1); ///< Maximum size of the array. (inclusive) [min, max]
        size_t minItems = 0; ///< @brief Minimum size of an array
        std::optional<std::vector<SubschemaRef>> oneOf; ///< This object have to match with one of thos schema (union)
        std::string name; ///< This is not a constraint. Just the name of the definition
        nlohmann::json userMeta;
        bool isKeyField = false;
        std::string title;
        std::string description;

        struct UnionSubTypeInfo
        {
            Subschema const* wrapperSchema = nullptr;
            Subschema const* dataSchema = nullptr;
            size_t index = 0;
        };
        /// @brief Fast lookup in union types
        std::map<std::string, UnionSubTypeInfo> unionTypeMap;

        // Meta informations
        /// Store metadata for any type
        struct BaseMeta
        {
            bool usedInEditor = true; ///< Does this Subschema exists in edition context ?
            bool usedInRuntime = true; ///< Does this Subschema exists in runtime context ?
            bool deprecated = false; ///< Is this Subschema deprecated ?
        };
        /// Store metadata for numeric type
        struct NumberMeta : BaseMeta
        {
            uint32_t bitDepth = 32; ///< Bit depth of this number, either 8, 16, 32 or 64
            bool isSigned = true; ///< is this number signed ?
        };
        /// Store metadata for union type (oneOf in json schema)
        struct UnionMeta : BaseMeta
        {
            std::string dataField; ///< Name of the field containing the data (ex : classData)
            std::string typeField; ///< Name of the field containing the type of the data (ex : className)
            std::optional<std::string> indexField; ///< Name of the field containing the index of the type
        };
        /// Store metadata for array type
        struct ArrayMeta : BaseMeta
        {
            std::string overridePolicy; ///< Policy used to override the array from the prefab
            bool ordered = true;
            bool isMapItem = false; ///< Can't be discarded at write (neither null)
            std::optional<std::string> keyField;
        };
        /// Store metadata for all schema which doesn't have specific field
        struct GenericMeta : BaseMeta
        {
        };
        /// Meta data for any type of Node
        using Meta = std::variant<GenericMeta, NumberMeta, UnionMeta, ArrayMeta>;
        Meta meta{}; ///< Contains meta data for any type of Node

        // helper methods
        [[nodiscard]] bool IsDeprecated() const; ///< Is this node deprecated? (access to meta data)
        [[nodiscard]] bool IsUsedInEditor() const; ///< Is this node used in editor? (access to meta data)
        [[nodiscard]] bool IsUsedInRuntime() const; ///< Is this node used in runtime? (access to meta data)
        [[nodiscard]] bool IsRuntimeOnly() const /// Is this node used in runtime only? (access to meta data)
        {
            return IsUsedInRuntime() && !IsUsedInEditor();
        }

        [[nodiscard]] bool IsEditorOnly() const /// Is this node used in editor only? (access to meta data)
        {
            return !IsUsedInRuntime() && IsUsedInEditor();
        }

        /// @brief Get all types acceptable in the union, with their names
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        [[nodiscard]] std::map<std::string, Subschema const*> getUnionTypesMap() const;

        /// @brief Get the Subschema related to the given \p _type (className)
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        /// @throw BadUnionType if \p _type is not listed in the oneOf field
        Subschema const* getUnionType(char const* _subtype) const;

        /// @brief Get the name of the json field containing the type name
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        [[nodiscard]] char const* getUnionNameField() const;

        /// @brief Get the name of the json field containing the data
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        [[nodiscard]] char const* getUnionDataField() const;

        [[nodiscard]] char const* getUnionDefaultTypeName() const;

        /// @brief Get the type of the Key of a map or set
        [[nodiscard]] DataType getMapKeyType() const;

        [[nodiscard]] DataKind getDataKind() const;

        /// Contains the simple value of one of the possible Ent::DataType
        using DefaultValue = nlohmann::json;
        DefaultValue defaultValue; ///< @brief Contains the data according to the type
        std::optional<DefaultValue> constValue; ///< This property can only have this value

        /// @brief Subschema of the unique type of item
        ///
        /// If type == Ent::DataType::array,
        ///   If all items have the same type (SingularItem),
        ///     This is the description of the items
        std::unique_ptr<SubschemaRef> singularItems;
        /// @brief Subschema of each items
        ///
        /// If type == Ent::DataType::array,
        ///   If all items have a different type (LinearItem),
        ///     This is the description of each items
        std::optional<std::vector<SubschemaRef>> linearItems;
        std::vector<std::string> enumValues; ///< List of all posible values for enum
    };

    class Schema;

    /// Can hold a Subschema OR a reference to a Subschema
    struct SubschemaRef
    {
        /// @cond PRIVATE
        SubschemaRef() = default;
        SubschemaRef(SubschemaRef const&) = delete;
        SubschemaRef& operator=(SubschemaRef const&) = delete;
        SubschemaRef(SubschemaRef&&) = default;
        SubschemaRef& operator=(SubschemaRef&&) = default;
        /// @endcond

        using DefaultValue = nlohmann::json;

        /// @cond PRIVATE
        /// Make this private
        struct Ref
        {
            Schema* schema; //!< Schema of the referenced object
            std::string ref; //!< Name of the referenced object
            DefaultValue defaultValue; ///< Additional default values (beside a "$ref")
            std::string title;
            std::string description;
        };

        std::variant<Null, Ref, Subschema> subSchemaOrRef;
        DeleteCheck deleteCheck;
        /// @endcond

        [[nodiscard]] Subschema const& get() const; //!< Get the referenced subschema
        Subschema& get(); //!< Get the referenced subschema

        Subschema const& operator*() const; //!< Get the referenced subschema
        Subschema& operator*(); //!< Get the referenced subschema
        Subschema const* operator->() const; //!< Get the referenced subschema
        Subschema* operator->(); //!< Get the referenced subschema

        /// Get the default values beside a "$ref", or nullptr
        [[nodiscard]] DefaultValue const* getRefDefaultValues() const
        {
            if (std::holds_alternative<Ref>(subSchemaOrRef)
                && !std::get<Ref>(subSchemaOrRef).defaultValue.is_null())
            {
                return &std::get<Ref>(subSchemaOrRef).defaultValue;
            }
            return nullptr;
        }

        [[nodiscard]] char const* getDescription() const
        {
            if (auto const* const ref = std::get_if<Ref>(&subSchemaOrRef))
            {
                return ref->description.c_str();
            }
            if (auto const* const schema = std::get_if<Subschema>(&subSchemaOrRef))
            {
                return schema->description.c_str();
            }
            return nullptr;
        }
    };

    class EntityLib;

    /// Definition of everything
    class Schema
    {
    public:
        Schema() = default;
        Schema(Schema const&) = delete;
        Schema& operator=(Schema const&) = delete;
        std::map<std::string, Subschema> allDefinitions; ///< Definition of everything, by type name
        EntityLib* entityLib = nullptr;

        /// @cond PRIVATE
        DeleteCheck deleteCheck;
        /// @endcond
    };

#pragma warning(push)
#pragma warning(disable : 4702)
    /// @cond PRIVATE

    /// variant visitor to get a specifique field in a Subschema::BaseMeta
    struct BasicFieldGetter
    {
        std::function<bool(Subschema::BaseMeta const*)> _fieldSelector;

        template <class MetaT>
        bool operator()(MetaT const& _meta)
        {
            return _fieldSelector(&_meta);
        }
    };

    inline bool Subschema::IsDeprecated() const
    {
        return std::visit(
            BasicFieldGetter{[](BaseMeta const* _meta)
                             {
                                 return _meta->deprecated;
                             }},
            meta);
    }

    inline bool Subschema::IsUsedInEditor() const
    {
        return std::visit(
            BasicFieldGetter{[](BaseMeta const* _meta)
                             {
                                 return _meta->usedInEditor;
                             }},
            meta);
    }

    inline bool Subschema::IsUsedInRuntime() const
    {
        return std::visit(
            BasicFieldGetter{[](BaseMeta const* _meta)
                             {
                                 return _meta->usedInRuntime;
                             }},
            meta);
    }

    inline DataType Subschema::getMapKeyType() const
    {
        return singularItems->get().linearItems->at(0)->type;
    }

    inline Subschema const& SubschemaRef::get() const
    {
        if (std::holds_alternative<Ref>(subSchemaOrRef))
        {
            Ref const& ref = std::get<Ref>(subSchemaOrRef);
            return AT(ref.schema->allDefinitions, ref.ref);
        }
        if (std::holds_alternative<Subschema>(subSchemaOrRef))
        {
            return std::get<Subschema>(subSchemaOrRef);
        }
        ENTLIB_LOGIC_ERROR("Uninitialized SubschemaRef!");
        return std::get<Subschema>(subSchemaOrRef);
    }

    inline Subschema& SubschemaRef::get()
    {
        if (std::holds_alternative<Ref>(subSchemaOrRef))
        {
            Ref const& ref = std::get<Ref>(subSchemaOrRef);
            return AT(ref.schema->allDefinitions, ref.ref);
        }
        if (std::holds_alternative<Subschema>(subSchemaOrRef))
        {
            return std::get<Subschema>(subSchemaOrRef);
        }
        ENTLIB_LOGIC_ERROR("Uninitialized SubschemaRef!");
        return std::get<Subschema>(subSchemaOrRef);
    }

    inline Subschema const& SubschemaRef::operator*() const
    {
        return get();
    }
    inline Subschema& SubschemaRef::operator*()
    {
        return get();
    }
    inline Subschema const* SubschemaRef::operator->() const
    {
        return &get();
    }
    inline Subschema* SubschemaRef::operator->()
    {
        return &get();
    }

    /// @endcond

#pragma warning(pop)

} // namespace Ent
