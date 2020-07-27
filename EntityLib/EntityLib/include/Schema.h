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

    /// Definition of an object
    struct ENTLIB_DLLEXPORT Subschema
    {
        DataType type = DataType::null; ///< type of this Subschema. @see Ent::DataType
        bool required = true; ///< Is this peroperty required?
        std::map<std::string, Subschema> properties; ///< If type == Ent::DataType::object, child properties
        size_t maxItems = size_t(-1); ///< Maximum size of the array. (inclusive) [min, max]
        size_t minItems = 0; ///< @brief Minimum size of an array

        /// Contains the simple value of one of the possible Ent::DataType
        using DefaultValue = std::variant<Null, std::string, float, int64_t, Null, Null, bool>;
        DefaultValue defaultValue; ///< @brief Contains the data according to the type

        /// @brief Subschema of the unique type of item
        ///
        /// If type == Ent::DataType::array,
        ///   If all items have the same type (SingularItem),
        ///     This is the description of the items
        std::unique_ptr<Subschema> singularItems;
        /// @brief Subschema of each items
        ///
        /// If type == Ent::DataType::array,
        ///   If all items have a different type (LinearItem),
        ///     This is the description of each items
        tl::optional<std::vector<Subschema>> linearItems;
        std::vector<std::string> enumValues; ///< List of all posible values for enum
    };

    /// Definition of all components
    struct Schema
    {
        std::map<std::string, Subschema> definitions; ///< Schema of all possible Component s
    };

} // namespace Ent
