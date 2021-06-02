#include "include/ComponentMerge.h"
#include "include/EntityLibCore.h"

#include <set>
#include <fstream>
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
                if (link.front() == '#')
                {
                    link = "./" + _sourceFile + link;
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
    json const runtimeCmps = loadJsonFile(_toolsDir / "WildPipeline/Schema/RuntimeComponents.json");
    json const editionCmps = loadJsonFile(_toolsDir / "WildPipeline/Schema/EditionComponents.json");
    json const dependencies = loadJsonFile(_toolsDir / "WildPipeline/Schema/Dependencies.json");

    json const& runtimeCompSch = runtimeCmps.at("definitions");
    json const& editionCompSch = editionCmps.at("definitions");

    json mergedCompSch;
    mergedCompSch["$ref"] = "#/definitions/Component";
    mergedCompSch["$schema"] = "http://json-schema.org/draft-07/schema#";

    mergedCompSch["definitions"]["Component"]["meta"]["unionDataField"] = "Data";
    mergedCompSch["definitions"]["Component"]["meta"]["unionTypeField"] = "Type";

    auto&& compList = mergedCompSch["definitions"]["Component"]["oneOf"];
    compList = json();

    auto isComponent = [](json const& node) {
        if (node.count("properties"))
        {
            if (node.at("properties").count("Super"))
            {
                auto ref = node.at("properties").at("Super").at("$ref").get<std::string>();
                return ref.find("ComponentGD") != std::string::npos;
            }
        }
        return false;
    };

    // Looking for components with same name and merge them
    std::map<std::string, json const*> editionCompMap;
    std::set<std::string> alreadyInsertedComponents;
    for (auto&& name_comp : editionCompSch.items())
    {
        if (isComponent(name_comp.value()))
        {
            editionCompMap.emplace(name_comp.key(), &(name_comp.value()));
        }
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        auto iter = editionCompMap.find(name);
        if (iter != editionCompMap.end())
        {
            // Merge properties
            json mergedProperties = runtimeCompSch[name].value("properties", json());
            updateRefLinks("RuntimeComponents.json", mergedProperties);
            json editionComp = iter->second->value("properties", json());
            updateRefLinks("EditionComponents.json", editionComp);
            mergedProperties.update(editionComp);

            // Create the schema of the component
            json mergedComponent;
            mergedComponent["type"] = "object";
            mergedComponent["properties"] = std::move(mergedProperties);

            // Add the new schema of the merged component in Scene-schema.json
            mergedCompSch["definitions"][name] = std::move(mergedComponent);

            // Merge the meta data
            json mergedMetas = runtimeCompSch[name].value("meta", json());
            json editionCompMetas = iter->second->value("meta", json::object());
            mergedMetas.update(editionCompMetas);
            mergedMetas["editor"] = true;
            mergedMetas["runtime"] = true;

            // Make the component wrapper (containing "Type" and "Data" field)
            json wrapper;
            auto&& prop = wrapper["properties"];
            prop["Type"]["const"] = name;
            prop["Data"]["$ref"] = "#/definitions/" + name;
            wrapper["meta"] = std::move(mergedMetas);

            // Add the component wrapper in the oneOf of Component (definitions/Component/oneOf)
            compList.push_back(std::move(wrapper));
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
            prop["Data"]["$ref"] = "./" + (filename + ("#/definitions/" + name));

            json metas = newComp.value("meta", json());
            metas.update(additionalMetas);
            newComp["meta"] = std::move(metas);
            compList.push_back(std::move(newComp));
        };
    for (auto&& name_comp : editionCompSch.items())
    {
        if (isComponent(name_comp.value()))
        {
            json editorOnlyMeta;
            editorOnlyMeta["editor"] = true;
            editorOnlyMeta["runtime"] = false;

            addComponent(name_comp.key(), "EditionComponents.json", editorOnlyMeta);
        }
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        json runtimeOnlyMeta;
        runtimeOnlyMeta["editor"] = false;
        runtimeOnlyMeta["runtime"] = true;

        auto name = dep["className"].get<std::string>();
        addComponent(name, "RuntimeComponents.json", runtimeOnlyMeta);
    }
    return mergedCompSch;
}

void Ent::updateComponents(std::filesystem::path const& _toolsDir)
{
    json sceneSch = mergeComponents(_toolsDir);
    char const* mergedComponentsSchemaLocation = "WildPipeline/Schema/MergedComponents.json";
    auto mergedSchemaPath = _toolsDir / mergedComponentsSchemaLocation;
    std::ofstream file(mergedSchemaPath);
    if (not file.is_open())
    {
        throw std::runtime_error(format(
            R"(Can't open file for write: "%s")", mergedSchemaPath.generic_string().c_str()));
    }
    file << sceneSch.dump(4);
}
