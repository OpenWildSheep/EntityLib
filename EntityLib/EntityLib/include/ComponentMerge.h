#pragma once

#include <filesystem>

#pragma warning(push, 0)
#include "../external/json.hpp"
#pragma warning(pop)

namespace Ent
{
    // *********************** Merge Runtime components into Entity schema ************************

    /// Merge the runtime components and the edition components, and generate the final scene schema
    nlohmann::json mergeComponents(std::filesystem::path const& _toolsDir);

    /// Merge the runtime components and the edition components, update the scene schema file
    void updateComponents(std::filesystem::path const& _toolsDir);
} // namespace Ent
