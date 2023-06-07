#pragma once

#include <filesystem>

#pragma warning(push, 0)
#include "../external/json.hpp"
#pragma warning(pop)

namespace Ent
{
    // *********************** Merge Runtime components into Entity schema ************************

    enum class SchemaSource
    {
        Edition,
        Runtime
    };

    struct SchemaInput
    {
        std::filesystem::path path;
        SchemaSource source;
    };

    /// Merge some schema files to make one final schema
    nlohmann::json mergeSchemas(
        std::filesystem::path const& _dependencyPaths, ///< Path to the file describing dependencies between Components
        std::vector<SchemaInput> const& _schemaInputs ///< List of schema files to merge together
    );

    /// Merge some schema files to make one final schema file used by EntityLib
    void updateSchemas(
        std::filesystem::path const& _toolsDir, ///< Path to P4:/Tools
        std::filesystem::path const& _dependencyPaths, ///< Path to the file describing dependencies between Components
        std::vector<SchemaInput> const& _schemaInputs, ///< List of schema files to merge together
        std::filesystem::path const& _outputPath ///< Path to the output EntityLib schema and the TexEditor schema
    );
} // namespace Ent
