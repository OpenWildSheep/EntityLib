#include "include/ComponentMerge.h"
#include "include/EntityLibCore.h"
#include "include/EntityLib.h"
#include "ValidJson.h"

#include <set>
#include <fstream>
#include <sstream>
#include <ciso646>
#include <iostream>

#include "Tools.h"

using namespace nlohmann;

namespace Ent
{

    // When schema branches a copied from a file to an other, the local references become external
    void updateRefLinks(json& _node)
    {
        switch (_node.type())
        {
        case detail::value_t::null:
        case detail::value_t::string:
        case detail::value_t::boolean:
        case detail::value_t::number_integer:
        case detail::value_t::number_unsigned:
        case detail::value_t::number_float: break;
        case detail::value_t::object:
        {
            for (auto& field : _node.items())
            {
                if (field.key() == "$ref")
                {
                    std::string link = field.value();
                    // Only keep the def name (no more external references)
                    auto const pos = link.find('#');
                    if (pos != std::string::npos)
                    {
                        link = link.substr(pos);
                        field.value() = link;
                    }
                }
                else
                {
                    updateRefLinks(field.value());
                }
            }
        }
        break;
        case detail::value_t::array:
        {
            for (auto& item : _node)
            {
                updateRefLinks(item);
            }
        }
        break;
        case detail::value_t::binary:
        case detail::value_t::discarded: break;
        }
    }

    bool isComponent(json const& mergedCompSch, json const& node)
    {
        if (node.count("properties") != 0)
        {
            if (node.at("properties").count("Super") != 0)
            {
                auto const ref = node.at("properties").at("Super").at("$ref").get<std::string>();
                auto const lastSlash = ref.find_last_of('/');
                auto const name = ref.substr(lastSlash + 1);
                if (name == "ComponentGD")
                {
                    return true;
                }
                return isComponent(mergedCompSch, mergedCompSch.at("definitions").at(name));
            }
        }
        return false;
    }

    json mergeSchemas(std::vector<SchemaInput> const& _schemaInputs)
    {
        json mergedCompSch;
        mergedCompSch["$schema"] = "http://json-schema.org/draft-07/schema#";

        mergedCompSch["definitions"]["Component"]["meta"]["unionDataField"] = "Data";
        mergedCompSch["definitions"]["Component"]["meta"]["unionTypeField"] = "Type";

        auto&& compList = mergedCompSch["definitions"]["Component"]["oneOf"];
        compList = json();

        // Looking for components with same name and merge them
        std::map<std::string, json const*> editionCompMap;
        struct Def
        {
            std::vector<json> definitions;
            bool inRuntime = false;
            bool inEdition = false;
        };
        std::map<std::string, Def> definitionsMap;
        auto addInDefinitions =
            [&](std::filesystem::path const& _schemaPath, SchemaSource _schemaSource)
        {
            json schemaDoc = loadJsonFile("", _schemaPath);
            json& definitions = schemaDoc.at("definitions");
            for (auto&& [name, comp] : definitions.items())
            {
                definitionsMap[name].definitions.emplace_back(move(comp));
                switch (_schemaSource)
                {
                case SchemaSource::Runtime: definitionsMap[name].inRuntime = true; break;
                case SchemaSource::Edition: definitionsMap[name].inEdition = true; break;
                }
            }
        };

        for (auto const& [path, source] : _schemaInputs)
        {
            addInDefinitions(path, source);
        }

        for (auto&& [name, defs] : definitionsMap)
        {
            json mergedDefinition = defs.definitions.back();
            mergedDefinition["meta"];
            defs.definitions.pop_back();
            mergedDefinition["meta"];
            for (json const& def : defs.definitions)
            {
                mergedDefinition["meta"];
                printf("Merged type : %s\n", name.c_str());
                if (def.count("properties") != 0)
                {
                    for (auto&& [pname, prop] : def.at("properties").items())
                    {
                        if (mergedDefinition["properties"].count(pname) != 0)
                        {
                            printf(
                                "WARNING : The property %s/%s already exist!\n",
                                name.c_str(),
                                pname.c_str());
                        }
                        mergedDefinition["properties"][pname] = prop;
                    }
                }
                mergedDefinition["meta"];
            }
            // Merge the meta data
            mergedDefinition["meta"]["editor"] = defs.inEdition;
            mergedDefinition["meta"]["runtime"] = defs.inRuntime;

            updateRefLinks(mergedDefinition);
            // Add the new schema of the merged component in Scene-schema.json
            mergedCompSch["definitions"][name] = std::move(mergedDefinition);
        }

        for (auto&& [name, defs] : definitionsMap)
        {
            json& mergedDefinition = mergedCompSch["definitions"][name];

            if (isComponent(mergedCompSch, mergedDefinition))
            {
                // Make the component wrapper (containing "Type" and "Data" field)
                json wrapper;
                auto&& prop = wrapper["properties"];
                prop["Type"]["const"] = name;
                prop["Data"]["$ref"] = "#/definitions/" + name;
                wrapper["meta"] = mergedDefinition["meta"];

                // Add the component wrapper in the oneOf of Component (definitions/Component/oneOf)
                compList.push_back(std::move(wrapper));
            }
        }

        return mergedCompSch;
    }

    void updateSchemas(
        std::vector<SchemaInput> const& _schemaInputs, std::filesystem::path const& _outputPath)
    {
        auto absOutputPath = absolute(_outputPath);
        json sceneSch = mergeSchemas(_schemaInputs);
        {
            create_directories(absOutputPath);
            auto const mergedSchemaPath = absOutputPath / "MergedComponents.json";
            std::stringstream buffer;
            buffer << sceneSch.dump(4);
            std::cout << "Write file : " << mergedSchemaPath << std::endl;
            std::ofstream file(mergedSchemaPath);
            if (not file.is_open())
            {
                throw FileSystemError(
                    "Trying to open file for write", absOutputPath, "MergedComponents.json");
            }
            file << buffer.str();
        }
        // Export all type schemas in the "all" subdirectory
        // Actually each file only reference the "TextEditorsSchema.json" file.
        auto allSingleSchemaPath = std::filesystem::path(absOutputPath / "all");
        create_directories(allSingleSchemaPath);
        for (auto&& [name, defs] : sceneSch["definitions"].items())
        {
            auto escapedName = name;
            std::replace(begin(escapedName), end(escapedName), ':', '_');
            std::replace(begin(escapedName), end(escapedName), '>', '_');
            std::replace(begin(escapedName), end(escapedName), '<', '_');
            auto const schemaPath = allSingleSchemaPath / (escapedName + ".json");
            if (schemaPath.native().size() < 255) // Can't write filename longer than 255 characters
            {
                json singleSchema;
                singleSchema["$ref"] = "../TextEditorsSchema.json#/definitions/" + name;
                std::stringstream buffer;
                buffer << singleSchema.dump(4);
                std::ofstream file(schemaPath);
                if (not file.is_open())
                {
                    throw FileSystemError("Trying to open file for write", "", schemaPath);
                }
                file << buffer.str();
            }
        }
        // Write the "TextEditorsSchema.json" file. Containing all schema for all types.
        EntityLib entlib(std::filesystem::current_path(), absOutputPath);
        json fullWildSchema = createValidationSchema(entlib.schema.schema);
        auto const fullWildSchemaLocation = absOutputPath / "TextEditorsSchema.json";
        std::stringstream buffer;
        buffer << fullWildSchema.dump(4);

        std::cout << "Write file : " << fullWildSchemaLocation << std::endl;
        std::ofstream file(fullWildSchemaLocation);
        if (not file.is_open())
        {
            throw FileSystemError(
                "Trying to open file for write", absOutputPath, "TextEditorsSchema.json");
        }
        file << buffer.str();
    }

} // namespace Ent
