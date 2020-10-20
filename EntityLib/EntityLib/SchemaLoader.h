#pragma once

#include <set>

#pragma warning(push, 0)
#include "../external/json.hpp"
#include "../external/filesystem.hpp"
#pragma warning(pop)

#include "include/Schema.h"

/// \cond PRIVATE

namespace Ent
{
    /// Use the global schema to read the Schema of a Component or a property
    struct SchemaLoader
    {
    public:
        /// Create a SchemaLoader given the file of the global Scene schema
        SchemaLoader(std::filesystem::path _toolsdir, std::filesystem::path _schemaPath);

        /// Load the Schema of a Component or a property
        /// @remark _data can be a reference ($ref)
        void readSchema(
            Schema* _globalSchema,
            std::string const& _filename,
            nlohmann::json const& _fileRoot, ///< Full file containing _data
            nlohmann::json const& _data ///< json node to extract schema
        );

        struct Visitor abstract
        {
            virtual void openProperty(char const*) = 0;
            virtual void closeProperty() = 0;
            virtual void setLinearItem(size_t) = 0;
            virtual void openLinearItem(size_t) = 0;
            virtual void closeLinearItem() = 0;
            virtual void openSingularItem() = 0;
            virtual void closeSingularItem() = 0;
            virtual void setMaxItems(size_t) = 0;
            virtual void setMinItems(size_t) = 0;
            virtual void setType(DataType) = 0;
            virtual void addEnumValue(char const*) = 0;
            virtual void setDefaultValue(Subschema::DefaultValue) = 0;
            virtual void setConstValue(Subschema::DefaultValue) = 0;
            virtual void setOneOf(size_t) = 0;
            virtual void openOneOfItem(size_t) = 0;
            virtual void closeOneOfItem() = 0;
            virtual void openRef(char const*) = 0;
            virtual void closeRef() = 0;
            virtual void openSubschema() = 0;
            virtual void closeSubschema() = 0;
            virtual void setMeta(Subschema::Meta) = 0;
            virtual void setName(std::string) = 0;
        };

        void parseSchema(
            std::string const& _filename,
            nlohmann::json const& _fileRoot, ///< Full file containing _data
            nlohmann::json const& _data, ///< json node to extract schema
            Visitor& _vis,
            int _depth = 0 ///< depth of this Node. (For internal use)
        );

    private:
        /// Load the Schema of a Component or a property
        /// @pre _data CAN NOT be a reference ($ref)
        void parseSchemaNoRef(
            std::string const& _filename,
            nlohmann::json const& _rootFile,
            nlohmann::json const& _data,
            Visitor& vis,
            int depth);

        std::filesystem::path m_schemaPath; ///< Path to the global Scene Schema
        std::filesystem::path m_toolsdir; ///< Path to the X:/Tools directory
        std::map<std::string, nlohmann::json> m_schemaMap; ///< Cache of already loaded schema documents
        std::set<std::string> parsedRef; ///< To know if a definition was already parsed
    };

} // namespace Ent

/// \endcond
