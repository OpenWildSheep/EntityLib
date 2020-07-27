#pragma once

#pragma warning(push, 0)
#include <filesystem>

#include "../external/json.hpp"
#pragma warning(pop)

#include "include/Schema.h"

/// \cond PRIVATE

namespace std
{
    using namespace experimental;
} // namespace std

namespace Ent
{
    /// Use the global schema to read the Schema of a Component or a property
    struct SchemaLoader
    {
    public:
        /// Create a SchemaLoader given the file of the global Scene schema
        SchemaLoader(std::filesystem::path _schemaPath);

        /// Load the Schema of a Component or a property
        /// @remark _data can be a reference ($ref)
        Ent::Subschema readSchema(
            nlohmann::json const& _fileRoot, ///< Full file containing _data
            nlohmann::json const& _data, ///< json node to extract schema
            int depth = 0 ///< depth of this Node. (For internal use)
        );

    private:
        /// Load the Schema of a Component or a property
        /// @pre _data CANT be a reference ($ref)
        Ent::Subschema
        readSchemaNoRef(nlohmann::json const& _fileRoot, nlohmann::json const& _data, int depth);

        std::filesystem::path m_schemaPath; ///< Path to the global Scene Schema
        std::map<std::string, nlohmann::json> m_schemaMap; ///< Cache of already loaded schema documents
    };

} // namespace Ent

/// \endcond
