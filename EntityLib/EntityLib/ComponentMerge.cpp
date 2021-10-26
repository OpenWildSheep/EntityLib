#include "include/ComponentMerge.h"
#include "include/EntityLibCore.h"
#include "include/EntityLib.h"
#include "ValidJson.h"

#include <set>
#include <fstream>
#include <sstream>
#include <ciso646>

#include "Tools.h"

using namespace nlohmann;

// When schema branches a copied from a file to an other, the local references become external
void updateRefLinks(std::string const& _sourceFile, json& _node)
{
    switch (_node.type())
    {
    case nlohmann::detail::value_t::null:
    case nlohmann::detail::value_t::string:
    case nlohmann::detail::value_t::boolean:
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
    case nlohmann::detail::value_t::number_float: break;
    case nlohmann::detail::value_t::object:
    {
        for (auto& field : _node.items())
        {
            if (field.key() == "$ref")
            {
                std::string link = field.value();
                // Only keep the def name (no more external references)
                auto pos = link.find('#');
                if (pos != std::string::npos)
                {
                    link = link.substr(pos);
                    field.value() = link;
                }
            }
            else
            {
                updateRefLinks(_sourceFile, field.value());
            }
        }
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        for (auto& item : _node)
        {
            updateRefLinks(_sourceFile, item);
        }
    }
    break;
    case nlohmann::detail::value_t::binary:
    case nlohmann::detail::value_t::discarded: break;
    }
};

json Ent::mergeComponents(std::filesystem::path const& _toolsDir)
{
    json const runtimeCmps = loadJsonFile(_toolsDir, "WildPipeline/Schema/RuntimeComponents.json");
    json const editionCmps = loadJsonFile(_toolsDir, "WildPipeline/Schema/EditionComponents.json");
    json const sceneDefs = loadJsonFile(_toolsDir, "WildPipeline/Schema/Scene-schema.json");
    json const dependencies = loadJsonFile(_toolsDir, "WildPipeline/Schema/Dependencies.json");

    json const& runtimeCompSch = runtimeCmps.at("definitions");
    json const& editionCompSch = editionCmps.at("definitions");
    json const& sceneDefSch = sceneDefs.at("definitions");

    json mergedCompSch;
    mergedCompSch["$schema"] = "http://json-schema.org/draft-07/schema#";

    mergedCompSch["definitions"]["Component"]["meta"]["unionDataField"] = "Data";
    mergedCompSch["definitions"]["Component"]["meta"]["unionTypeField"] = "Type";

    auto&& compList = mergedCompSch["definitions"]["Component"]["oneOf"];
    compList = json();
    std::set<std::string> componentNames = {"ComponentGD"};

    auto isComponent = [&componentNames](json const& node) {
        if (node.count("properties") != 0)
        {
            if (node.at("properties").count("Super") != 0)
            {
                auto ref = node.at("properties").at("Super").at("$ref").get<std::string>();
                auto lastSlash = ref.find_last_of('/');
                auto name = ref.substr(lastSlash + 1);
                return componentNames.count(name) != 0;
            }
        }
        return false;
    };

    // Looking for components with same name and merge them
    std::map<std::string, json const*> editionCompMap;
    struct Def
    {
        std::vector<json const*> defintions;
        bool inRuntime = false;
        bool inEdition = false;
    };
    std::map<std::string, Def> definitionsMap;
    for (auto&& [name, comp] : runtimeCompSch.items())
    {
        definitionsMap[name].defintions.push_back(&comp);
        definitionsMap[name].inRuntime = true;
    }
    for (auto&& [name, comp] : editionCompSch.items())
    {
        definitionsMap[name].defintions.push_back(&comp);
        definitionsMap[name].inEdition = true;
    }
    for (auto&& [name, comp] : sceneDefSch.items())
    {
        definitionsMap[name].defintions.push_back(&comp);
        definitionsMap[name].inEdition = true;
    }

    for (auto&& [name, defs] : definitionsMap)
    {
        json mergedDefinition = *defs.defintions.back();
        defs.defintions.pop_back();
        for (auto* def : defs.defintions)
        {
            if (def->count("properties") != 0)
            {
                mergedDefinition["properties"].update(def->at("properties"));
            }
        }
        // Merge the meta data
        mergedDefinition["meta"]["editor"] = defs.inEdition;
        mergedDefinition["meta"]["runtime"] = defs.inRuntime;

        updateRefLinks("RuntimeComponents.json", mergedDefinition);
        // Add the new schema of the merged component in Scene-schema.json
        mergedCompSch["definitions"][name] = std::move(mergedDefinition);
    }

    for (bool newComp = true; newComp; newComp = false)
    {
        for (auto&& [name, defs] : definitionsMap)
        {
            json& mergedDefinition = mergedCompSch["definitions"][name];

            if (isComponent(mergedDefinition))
            {
                // Make the component wrapper (containing "Type" and "Data" field)
                json wrapper;
                auto&& prop = wrapper["properties"];
                prop["Type"]["const"] = name;
                prop["Data"]["$ref"] = "#/definitions/" + name;
                wrapper["meta"] = mergedDefinition["meta"];

                // Add the component wrapper in the oneOf of Component (definitions/Component/oneOf)
                compList.push_back(std::move(wrapper));
                componentNames.emplace(name);
                newComp = true;
            }
        }
    }

    return mergedCompSch;
}

void Ent::updateComponents(std::filesystem::path const& _toolsDir)
{
    json sceneSch = mergeComponents(_toolsDir);
    char const* mergedComponentsSchemaLocation = "WildPipeline/Schema/MergedComponents.json";
    auto mergedSchemaPath = _toolsDir / mergedComponentsSchemaLocation;
    {
        std::stringstream buffer;
        buffer << sceneSch.dump(4);
        std::ofstream file(mergedSchemaPath);
        if (not file.is_open())
        {
            throw FileSystemError(
                "Trying to open file for write", _toolsDir, mergedComponentsSchemaLocation);
        }
        file << buffer.str();
    }
    // Export all type schemas in the "all" subdirectory
    // Actually each file only reference the "TextEditorsSchema.json" file.
    auto allSingleSchemaPath = std::filesystem::path("WildPipeline/Schema/all");
    std::filesystem::create_directories(_toolsDir / allSingleSchemaPath);
    for (auto&& [name, defs] : sceneSch["definitions"].items())
    {
        auto escapedName = name;
        std::replace(begin(escapedName), end(escapedName), ':', '_');
        std::replace(begin(escapedName), end(escapedName), '>', '_');
        std::replace(begin(escapedName), end(escapedName), '<', '_');
        if (escapedName.size() < 256) // Can't write filename longer than 255 characters
        {
            json singleSchema;
            singleSchema["$ref"] = "../TextEditorsSchema.json#/definitions/" + escapedName;
            escapedName += ".json";
            auto singleSchemaPath = allSingleSchemaPath / escapedName;
            std::stringstream buffer;
            buffer << singleSchema.dump(4);
            std::ofstream file(_toolsDir / singleSchemaPath);
            if (not file.is_open())
            {
                throw FileSystemError("Trying to open file for write", _toolsDir, singleSchemaPath);
            }
            file << buffer.str();
        }
    }
    // Write the "TextEditorsSchema.json" file. Containing all schema for all types.
    Ent::EntityLib entlib(_toolsDir.parent_path());
    json fullWildSchema = createValidationSchema(entlib.schema.schema);
    {
        char const* fullWildSchemaLocation = "WildPipeline/Schema/TextEditorsSchema.json";
        std::stringstream buffer;
        buffer << fullWildSchema.dump(4);

        std::ofstream file(_toolsDir / fullWildSchemaLocation);
        if (not file.is_open())
        {
            throw FileSystemError("Trying to open file for write", _toolsDir, fullWildSchemaLocation);
        }
        file << buffer.str();
    }
}
