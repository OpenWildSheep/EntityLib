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
    /// Valid a document using the JSON scheme of type _rootName
    /// @throw JsonValidation when the document in invalid
    void validateJson(
        Schema const& _schema,
        std::filesystem::path const& _toolsDir,
        nlohmann::json const& _entity,
        char const* _rootName);

    /// Create a validation schema for a given type
    nlohmann::json createValidationSchema(Ent::Schema const& schema);
} // namespace Ent

/// \endcond
