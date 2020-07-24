#include "include/ComponentMerge.h"

#include <set>
#include <fstream>

#include "Tools.h"

using namespace nlohmann;

char const* sceneSchemaLocation = "WildPipeline/Schema/Scene-schema.json";

// When schema branches a copied from a file to an other, the local references become external
void updateRefLinks(std::string const& sourceFile, json& node)
{
    switch (node.type())
    {
    case nlohmann::detail::value_t::null: break;
    case nlohmann::detail::value_t::string: break;
    case nlohmann::detail::value_t::boolean: break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned: break;
    case nlohmann::detail::value_t::number_float: break;
    case nlohmann::detail::value_t::object:
    {
        for (auto& field : node.items())
        {
            if (field.key() == "$ref")
            {
                std::string link = field.value();
                if (link.front() == '#')
                {
                    link = "file://" + sourceFile + link;
                    field.value() = link;
                }
            }
            else
                updateRefLinks(sourceFile, field.value());
        }
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        for (auto& item : node)
        {
            updateRefLinks(sourceFile, item);
        }
    }
    break;
    case nlohmann::detail::value_t::discarded: break;
    }
};

json Ent::mergeComponants(std::filesystem::path const& toolsDir)
{
    json runtimeCompSch = loadJsonFile(toolsDir / "WildPipeline/Schema/RuntimeComponants.json");
    json editionCompSch = loadJsonFile(toolsDir / "WildPipeline/Schema/EditionComponents.json");
    auto sceneSchemaPath = toolsDir / sceneSchemaLocation;
    json sceneSch = loadJsonFile(sceneSchemaPath);
    json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");

    runtimeCompSch = runtimeCompSch["definitions"];
    editionCompSch = editionCompSch["definitions"];

    auto&& compList = sceneSch["definitions"]["Component"]["oneOf"];
    compList = json();

    // Looking for components with same name and merge them
    std::map<std::string, json const*> editionCompMap;
    std::set<std::string> alreadyInsertedComponents;
    for (auto&& name_comp : editionCompSch.items())
    {
        editionCompMap.emplace(name_comp.key(), &(name_comp.value()));
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        auto iter = editionCompMap.find(name);
        if (iter != editionCompMap.end())
        {
            json merged = runtimeCompSch[name].value("properties", json());
            updateRefLinks("RuntimeComponants.json", merged);
            json editionComp = iter->second->value("properties", json());
            updateRefLinks("EditionComponents.json", editionComp);
            merged.update(editionComp);

            json newComp;
            auto&& prop = newComp["properties"];
            prop["Type"]["const"] = name;
            prop["Data"]["type"] = "object";
            prop["Data"]["properties"] = std::move(merged);

            compList.push_back(std::move(newComp));
            alreadyInsertedComponents.insert(name);
        }
    }

    // Add other components
    auto addComponent = [&](std::string const& name, char const* filename) {
        if (alreadyInsertedComponents.count(name))
            return;
        json newComp;
        auto&& prop = newComp["properties"];
        prop["Type"]["const"] = name;
        prop["Data"]["$ref"] = "file://" + (filename + ("#/definitions/" + name));

        compList.push_back(std::move(newComp));
    };
    for (auto&& name_comp : editionCompSch.items())
    {
        addComponent(name_comp.key(), "EditionComponents.json");
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        addComponent(name, "RuntimeComponants.json");
    }
    return sceneSch;
}

void Ent::updateComponants(std::filesystem::path const& toolsDir)
{
    json sceneSch = mergeComponants(toolsDir);
    auto sceneSchemaPath = toolsDir / sceneSchemaLocation;
    std::ofstream file(sceneSchemaPath);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for write: " + sceneSchemaPath.u8string());
    }
    file << sceneSch.dump(4);
}
