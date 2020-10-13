#include "include/ComponentMerge.h"

#include <set>
#include <fstream>
#include <ciso646>

#include "Tools.h"

using namespace nlohmann;

char const* sceneSchemaLocation = "WildPipeline/Schema/Scene-schema.json";

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
                if (link.front() == '#')
                {
                    link = "file://" + _sourceFile + link;
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
    json runtimeCompSch = loadJsonFile(_toolsDir / "WildPipeline/Schema/RuntimeComponents.json");
    json editionCompSch = loadJsonFile(_toolsDir / "WildPipeline/Schema/EditionComponents.json");
    auto sceneSchemaPath = _toolsDir / sceneSchemaLocation;
    json sceneSch = loadJsonFile(sceneSchemaPath);
    json dependencies = loadJsonFile(_toolsDir / "WildPipeline/Schema/Dependencies.json");

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
            json mergedProperties = runtimeCompSch[name].value("properties", json());
            updateRefLinks("RuntimeComponents.json", mergedProperties);
            json editionComp = iter->second->value("properties", json());
            updateRefLinks("EditionComponents.json", editionComp);
            mergedProperties.update(editionComp);

            json mergedMetas = runtimeCompSch[name].value("meta", json());
            json editionCompMetas = iter->second->value("meta", json::object());
            mergedMetas.update(editionCompMetas);
            mergedMetas["editor"] = true;
            mergedMetas["runtime"] = true;

            json newComp;
            auto&& prop = newComp["properties"];
            prop["Type"]["const"] = name;
            prop["Data"]["type"] = "object";
            prop["Data"]["properties"] = std::move(mergedProperties);
            newComp["meta"] = std::move(mergedMetas);

            compList.push_back(std::move(newComp));
            alreadyInsertedComponents.insert(name);
        }
    }

    // Add other components
    auto addComponent =
        [&](std::string const& name, char const* filename, const json& additionalMetas) {
            if (alreadyInsertedComponents.count(name) != 0)
            {
                return;
            }
            json newComp;
            auto&& prop = newComp["properties"];
            prop["Type"]["const"] = name;
            prop["Data"]["$ref"] = "file://" + (filename + ("#/definitions/" + name));

            json metas = newComp.value("meta", json());
            metas.update(additionalMetas);
            newComp["meta"] = std::move(metas);
            compList.push_back(std::move(newComp));
        };
    for (auto&& name_comp : editionCompSch.items())
    {
        json editorOnlyMeta;
        editorOnlyMeta["editor"] = true;
        editorOnlyMeta["runtime"] = false;

        addComponent(name_comp.key(), "EditionComponents.json", editorOnlyMeta);
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        json runtimeOnlyMeta;
        runtimeOnlyMeta["editor"] = false;
        runtimeOnlyMeta["runtime"] = true;

        auto name = dep["className"].get<std::string>();
        addComponent(name, "RuntimeComponents.json", runtimeOnlyMeta);
    }
    return sceneSch;
}

void Ent::updateComponents(std::filesystem::path const& _toolsDir)
{
    json sceneSch = mergeComponents(_toolsDir);
    auto sceneSchemaPath = _toolsDir / sceneSchemaLocation;
    std::ofstream file(sceneSchemaPath);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for write: " + sceneSchemaPath.u8string());
    }
    file << sceneSch.dump(4);
}
