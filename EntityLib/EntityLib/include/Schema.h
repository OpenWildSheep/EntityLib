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
        string,
        number,
        integer,
        object, ///< @see Ent::DataType::object
        array, ///< @see Ent::DataType::array
        boolean,
        freeobject, ///< Object without schema. Used in Subscene/Embedded. @todo remove?
    };

    /// @cond PRIVATE
    using Null = std::nullptr_t;
    /// @endcond

    struct SubschemaRef;

    /// Definition of an object
    struct ENTLIB_DLLEXPORT Subschema
    {
        /// @cond PRIVATE
        Subschema() = default;
        Subschema(Subschema const&) = delete;
        Subschema& operator=(Subschema const&) = delete;
        Subschema(Subschema&&) = default;
        Subschema& operator=(Subschema&&) = default;
        /// @endcond

        DataType type = DataType::null; ///< type of this Subschema. @see Ent::DataType
        bool required = false; ///< Is this property required?
        std::map<std::string, SubschemaRef> properties; ///< If type == Ent::DataType::object, child properties
        size_t maxItems = size_t(-1); ///< Maximum size of the array. (inclusive) [min, max]
        size_t minItems = 0; ///< @brief Minimum size of an array
        tl::optional<std::vector<SubschemaRef>> oneOf; ///< This object have to match with one of thos schema (union)
        std::string name; ///< This is not a constraint. Just the name of the definition

        /// Meta informations
        struct BaseMeta
        {
            bool usedInEditor = true; ///< Does this Subschema exists in edition context ?
            bool usedInRuntime = true;  ///< Does this Subschema exists in runtime context ?
            bool deprecated = false; ///< Is this Subschema deprecated ?
        };
        struct NumberMeta : BaseMeta
        {
            uint32_t bitDepth = 32; ///< Bit depth of this number, either 8, 16, 32 or 64
            bool isSigned = true; ///< is this number signed ?
        };
        struct GenericMeta : BaseMeta {};
        using Meta = mapbox::util::variant<NumberMeta, GenericMeta>;
        Meta meta;

        /// Contains the simple value of one of the possible Ent::DataType
        using DefaultValue =
            mapbox::util::variant<Null, std::string, float, int64_t, Null, Null, bool>;
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

        DeleteCheck deleteCheck;
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
        DeleteCheck deleteCheck;
    };

#pragma warning(push)
#pragma warning(disable : 4702)
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

#pragma warning(pop)

} // namespace Ent
