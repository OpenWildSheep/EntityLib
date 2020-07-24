#pragma once

#pragma warning(push, 0)
#include <filesystem>
#pragma warning(pop)

#include "include/Schema.h"

namespace std
{
    using namespace experimental;
} // namespace std

namespace Ent
{

    struct SchemaLoader
    {
    public:
        SchemaLoader(std::filesystem::path _schemaPath);
        Ent::Subschema readSchema(
            nlohmann::json const& _fileRoot, ///< Full file containing _data
            nlohmann::json const& _data, ///< json node to extract schema
            int depth);

    private:
        Ent::Subschema
        readSchemaNoRef(nlohmann::json const& _fileRoot, nlohmann::json const& _data, int depth);

        std::filesystem::path m_schemaPath;
        std::map<std::string, nlohmann::json> m_schemaMap;
    };

} // namespace Ent
