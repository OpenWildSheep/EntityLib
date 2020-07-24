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

namespace Ent
{
    enum class DataType
    {
        null,
        string,
        number,
        integer,
        object,
        array,
        boolean,
        freeobject, // Object without schema. Used in Subscene/Embedded
    };

    struct Null
    {
    };

    struct ENTLIB_DLLEXPORT Subschema
    {
        DataType type = DataType::null;
        bool required = true;
        std::map<std::string, Subschema> properties;
        size_t maxItems = size_t(-1);
        size_t minItems = 0;
        using DefaultValue = std::variant<Null, std::string, float, int64_t, Null, Null, bool>;
        DefaultValue defaultValue;
        std::unique_ptr<Subschema> singularItems; // In valijson it is a SingularItems
        tl::optional<std::vector<Subschema>> linearItems;
        std::vector<std::string> enumValues;
    };

    struct Schema
    {
        std::map<std::string, Subschema> definitions;
    };

} // namespace Ent
