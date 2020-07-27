#pragma once

#pragma warning(push, 0)
#include <filesystem>

#include "../external/json.hpp" // TODO : Try to remove this inclusion
#pragma warning(pop)

/// \cond PRIVATE

namespace std
{
    using namespace experimental;
} // namespace std

namespace Ent
{
    /// Valid a Scene using the JSON scheme of scene
    /// @throw JsonValidation when the Scene in invalid
    void validScene(std::filesystem::path toolsDir, nlohmann::json const& scene);
    /// Valid an Entity using the JSON scheme of entities
    /// @throw JsonValidation when the Entity in invalid
    void validEntity(std::filesystem::path toolsDir, nlohmann::json const& entity);
} // namespace Ent

/// \endcond
