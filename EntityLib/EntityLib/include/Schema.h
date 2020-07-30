#pragma once

#pragma warning(push, 0)
#include <map>
#include <memory>
#include <vector>

#include "../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#pragma warning(pop)

#include "EntityLibCore.h"

namespace std
{
    using namespace mapbox::util;
} // namespace std

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
    struct Null
    {
    };
    /// @endcond

    struct SubschemaRef;

    /// Definition of an object
    struct ENTLIB_DLLEXPORT Subschema
    {
        Subschema() = default;
        Subschema(Subschema const&) = delete;
        Subschema& operator=(Subschema const&) = delete;
        Subschema(Subschema&&) = default;
        Subschema& operator=(Subschema&&) = default;

        DataType type = DataType::null; ///< type of this Subschema. @see Ent::DataType
        bool required = false; ///< Is this peroperty required?
        std::map<std::string, SubschemaRef> properties; ///< If type == Ent::DataType::object, child properties
        size_t maxItems = size_t(-1); ///< Maximum size of the array. (inclusive) [min, max]
        size_t minItems = 0; ///< @brief Minimum size of an array
        tl::optional<std::vector<SubschemaRef>> oneOf;

        /// Contains the simple value of one of the possible Ent::DataType
        using DefaultValue = std::variant<Null, std::string, float, int64_t, Null, Null, bool>;
        DefaultValue defaultValue; ///< @brief Contains the data according to the type
        tl::optional<DefaultValue> constValue;

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
        struct Ref
        {
            Schema* schema;
            std::string ref;
        };

        std::variant<Null, Ref, Subschema> subSchemaOrRef;

        Subschema const& get() const;
        Subschema& get();

        Subschema const& operator*() const;
        Subschema& operator*();
        Subschema const* operator->() const;
        Subschema* operator->();
    };

    /// Definition of all components
    class Schema
    {
    public:
        Schema() = default;
        Schema(Schema const&) = delete;
        Schema& operator=(Schema const&) = delete;
        SubschemaRef root; ///< Schema of all possible Component s
        std::map<std::string, Subschema> allDefinitions;
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
