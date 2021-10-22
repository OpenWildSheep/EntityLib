#pragma once

#pragma warning(push, 0)
#include "../external/json.hpp"
#include "../external/filesystem.hpp"
#pragma warning(pop)

/// \cond PRIVATE

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

    nlohmann::json createValidationSchema(Ent::Schema const& schema);
} // namespace Ent

/// \endcond
