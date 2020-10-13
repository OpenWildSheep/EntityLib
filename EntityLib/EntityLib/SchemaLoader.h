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

        /// @todo Make Visitor an interface to inherit
        struct Visitor
        {
            std::function<void(char const*)> openProperty;
            std::function<void()> closeProperty;
            std::function<void(size_t)> setLinearItem;
            std::function<void(size_t)> openLinearItem;
            std::function<void()> closeLinearItem;
            std::function<void()> openSingularItem;
            std::function<void()> closeSingularItem;
            std::function<void(size_t)> setMaxItems;
            std::function<void(size_t)> setMinItems;
            std::function<void(DataType)> setType;
            std::function<void(char const*)> addEnumValue;
            std::function<void(Subschema::DefaultValue)> setDefaultValue;
            std::function<void(Subschema::DefaultValue)> setConstValue;
            std::function<void(size_t)> setOneOf;
            std::function<void(size_t)> openOneOfItem;
            std::function<void()> closeOneOfItem;
            std::function<void(char const*)> openRef;
            std::function<void()> closeRef;
            std::function<void()> openSubschema;
            std::function<void()> closeSubschema;
            std::function<void(Subschema::Meta)> setMeta;
            std::function<void(std::string)> setName;
        };

        void parseSchema(
            std::string const& _filename,
            nlohmann::json const& _fileRoot, ///< Full file containing _data
            nlohmann::json const& _data, ///< json node to extract schema
            Visitor const& _vis,
            int _depth = 0 ///< depth of this Node. (For internal use)
        );

    private:
        /// Load the Schema of a Component or a property
        /// @pre _data CAN NOT be a reference ($ref)
        void parseSchemaNoRef(
            std::string const& _filename,
            nlohmann::json const& _rootFile,
            nlohmann::json const& _data,
            Visitor const& vis,
            int depth);

        std::filesystem::path m_schemaPath; ///< Path to the global Scene Schema
        std::filesystem::path m_toolsdir; ///< Path to the X:/Tools directory
        std::map<std::string, nlohmann::json> m_schemaMap; ///< Cache of already loaded schema documents
        std::set<std::string> parsedRef; ///< To know if a definition was already parsed
    };

} // namespace Ent

/// \endcond
