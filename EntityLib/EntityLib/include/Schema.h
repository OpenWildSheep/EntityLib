#pragma once

#pragma warning(push, 0)
#include <map>
#include <memory>
#include <vector>

#include "../external/optional.hpp"
#include "../external/json.hpp" // TODO : Try to remove this inclusion
#pragma warning(pop)

#include "EntityLibCore.h"

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

    struct ENTLIB_DLLEXPORT Subschema
    {
        DataType type = DataType::null;
        bool required = true;
        std::map<std::string, Subschema> properties;
        size_t maxItems = size_t(-1);
        size_t minItems = 0;
        nlohmann::json defaultValue;
        std::unique_ptr<Subschema> singularItems; // In valijson it is a SingularItems
        tl::optional<std::vector<Subschema>> linearItems;
        std::vector<std::string> enumValues;
    };

    struct Schema
    {
        std::map<std::string, Subschema> definitions;
    };

} // namespace Ent
