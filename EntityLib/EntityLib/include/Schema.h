#pragma once

#pragma warning(push, 0)
#include <map>
#include <memory>
#include <vector>

#include "../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
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

    /// @cond PRIVATE
    using Null = std::nullptr_t;
    /// @endcond

    // ******************************** Exception declarations ************************************

    /// Exception thrown when calling a method of a Node which has not the apropriate Ent::DataType
    struct BadType : std::runtime_error
    {
        BadType(); ///< ctor
    };

    /// Exception thrown when a metadata is missing in the json schema
    ///
    /// Example : oneOf need className and classData
    struct MissingMetadata : std::runtime_error
    {
        MissingMetadata(char const* _schemaName); ///< ctor
    };

    /// Exception thrown when trying to switch a Union to a type that woesn't exit
    struct BadUnionType : std::runtime_error
    {
        /// ctor
        BadUnionType(char const* _type ///< The type/className that doen't exist in this union
        );
    };

    // *************************************** Subschema ******************************************

    struct SubschemaRef;

    /// Definition of a json Node
    struct ENTLIB_DLLEXPORT Subschema
    {
        /// @cond PRIVATE
        Subschema() = default;
        Subschema(Subschema const&) = delete;
        Subschema& operator=(Subschema const&) = delete;
        Subschema(Subschema&&) = default;
        Subschema& operator=(Subschema&&) = default;
        DeleteCheck deleteCheck;
        /// @endcond

        DataType type = DataType::null; ///< type of this Subschema. @see Ent::DataType
        bool required = false; ///< Is this property required?
        std::map<std::string, SubschemaRef> properties; ///< If type == Ent::DataType::object, child properties
        size_t maxItems = size_t(-1); ///< Maximum size of the array. (inclusive) [min, max]
        size_t minItems = 0; ///< @brief Minimum size of an array
        tl::optional<std::vector<SubschemaRef>> oneOf; ///< This object have to match with one of thos schema (union)
        std::string name; ///< This is not a constraint. Just the name of the definition

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
        };
        /// Store metadata for all schema which doesn't have specific field
        struct GenericMeta : BaseMeta
        {
        };
        /// Meta data for any type of Node
        using Meta = mapbox::util::variant<GenericMeta, NumberMeta, UnionMeta>;
        Meta meta; ///< Contains meta data for any type of Node

        // helper methods
        bool IsDeprecated() const; ///< Is this node deprecated? (access to meta data)
        bool IsUsedInEditor() const; ///< Is this node used in editor? (access to meta data)
        bool IsUsedInRuntime() const; ///< Is this node used in runtime? (access to meta data)
        bool IsRuntimeOnly() const /// Is this node used in runtime only? (access to meta data)
        {
            return IsUsedInRuntime() && !IsUsedInEditor();
        }
        bool IsEditorOnly() const /// Is this node used in editor only? (access to meta data)
        {
            return !IsUsedInRuntime() && IsUsedInEditor();
        }
        /// @brief Get the Subschema related to the given \p _type (className)
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        /// @throw BadUnionType if \p _type is not listed in the oneOf field
        Subschema const* getUnionType(char const* _subtype) const;

        /// Contains the simple value of one of the possible Ent::DataType
        using DefaultValue =
            mapbox::util::variant<Null, std::string, float, int64_t, Null, Null, bool, Null>;
        DefaultValue defaultValue; ///< @brief Contains the data according to the type
        tl::optional<DefaultValue> constValue; ///< This property can only have this value

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
        tl::optional<std::vector<SubschemaRef>> linearItems;
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

        /// @cond PRIVATE
        /// Make this private
        struct Ref
        {
            Schema* schema; //!< Schema of the referenced object
            std::string ref; //!< Name of the referenced object
        };

        mapbox::util::variant<Null, Ref, Subschema> subSchemaOrRef;
        DeleteCheck deleteCheck;
        /// @endcond

        Subschema const& get() const; //!< Get the referenced subschema
        Subschema& get(); //!< Get the referenced subschema

        Subschema const& operator*() const; //!< Get the referenced subschema
        Subschema& operator*(); //!< Get the referenced subschema
        Subschema const* operator->() const; //!< Get the referenced subschema
        Subschema* operator->(); //!< Get the referenced subschema
    };

    /// Definition of everything
    class Schema
    {
    public:
        Schema() = default;
        Schema(Schema const&) = delete;
        Schema& operator=(Schema const&) = delete;
        SubschemaRef root; ///< Root Schema : Schema of the scene
        std::map<std::string, Subschema> allDefinitions; ///< Definition of everything, by type name

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
        std::function<bool(const Subschema::BaseMeta*)> _fieldSelector;

        template <class MetaT>
        bool operator()(const MetaT& _meta)
        {
            return _fieldSelector(&_meta);
        }
    };

    inline bool Subschema::IsDeprecated() const
    {
        return mapbox::util::apply_visitor(
            BasicFieldGetter{ [](const Subschema::BaseMeta* _meta) {
                return _meta->deprecated;
            } },
            meta);
    }

    inline bool Subschema::IsUsedInEditor() const
    {
        return mapbox::util::apply_visitor(
            BasicFieldGetter{ [](const Subschema::BaseMeta* _meta) {
                return _meta->usedInEditor;
            } },
            meta);
    }

    inline bool Subschema::IsUsedInRuntime() const
    {
        return mapbox::util::apply_visitor(
            BasicFieldGetter{ [](const Subschema::BaseMeta* _meta) {
                return _meta->usedInRuntime;
            } },
            meta);
    }

    inline Subschema const& SubschemaRef::get() const
    {
        if (subSchemaOrRef.is<Ref>())
        {
            Ref const& ref = subSchemaOrRef.get<Ref>();
            return ref.schema->allDefinitions.at(ref.ref);
        }
        else if (subSchemaOrRef.is<Subschema>())
            return subSchemaOrRef.get<Subschema>();
        else
        {
            // TODO : Loïc - Prefer to use ENTLIB_LOGIC_ERROR to capture the __FILE__ and __LINE__
            logicError("Uninitialized SubschemaRef!", __FILE__, __LINE__);
            return subSchemaOrRef.get<Subschema>();
        }
    }

    inline Subschema& SubschemaRef::get()
    {
        if (subSchemaOrRef.is<Ref>())
        {
            Ref const& ref = subSchemaOrRef.get<Ref>();
            return ref.schema->allDefinitions.at(ref.ref);
        }
        else if (subSchemaOrRef.is<Subschema>())
            return subSchemaOrRef.get<Subschema>();
        else
        {
            logicError("Uninitialized SubschemaRef!", __FILE__, __LINE__);
            return subSchemaOrRef.get<Subschema>();
        }
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
