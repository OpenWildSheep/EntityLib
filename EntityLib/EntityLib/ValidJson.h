#pragma once

#pragma warning(push, 0)
#include <filesystem>

#include "../external/json.hpp"
#pragma warning(pop)

/// \cond PRIVATE

namespace std
{
    using namespace experimental;
} // namespace std

namespace Ent
{
    class Schema;

    /// Valid a Scene using the JSON scheme of scene
    /// @throw JsonValidation when the Scene in invalid
    void validateScene(
        Schema const& _schema, std::filesystem::path const& _toolsDir, nlohmann::json const& _scene);
    /// Valid an Entity using the JSON scheme of entities
    /// @throw JsonValidation when the Entity in invalid
    void validateEntity(
        Schema const& _schema, std::filesystem::path const& _toolsDir, nlohmann::json const& _entity);
} // namespace Ent

/// \endcond
