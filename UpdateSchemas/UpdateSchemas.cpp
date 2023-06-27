#include <ComponentMerge.h>

#include <ciso646>
#include <filesystem>
#include <set>
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>

using namespace std::filesystem;

int main(int argc, char** argv)
try
{
    cxxopts::Options options(
        "UpdateSchemas",
        "Merge RuntimeComponents.json with EditionComponents.json and Scene-schema.json");
    // clang-format off
    options.add_options()
        ("o,outputdir", "Path to the directory to export merges schemas", cxxopts::value<path>())
        ("e,edition-schema", "Absolute path to schema files to merge as 'edition' schema", cxxopts::value<std::vector<path>>())
        ("r,runtime-schema", "Absolute path to schema files to merge as 'runtime' schema", cxxopts::value<std::vector<path>>())
        ("h,help", "Print usage");
    // clang-format on

    path schemaDir;
    std::vector<path> editionSchemaToMerge;
    std::vector<path> runtimeSchemaToMerge;

    try
    {
        auto result = options.parse(argc, argv);
        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return EXIT_SUCCESS;
        }

        schemaDir = result["outputdir"].as<path>();
        editionSchemaToMerge = result["edition-schema"].as<std::vector<path>>();
        runtimeSchemaToMerge = result["runtime-schema"].as<std::vector<path>>();
    }
    catch (std::exception& ex)
    {
        std::cout << typeid(ex).name() << " - " << ex.what() << std::endl;
        std::cout << options.help() << std::endl;
        return EXIT_FAILURE;
    }

    path allSingleSchemaPath = schemaDir / "all";

    // Delete single schema files
    remove_all(allSingleSchemaPath);

    // Generate schema files (MergedComponents.json, TextEditorsSchema.json and all single schema files)
    std::vector<Ent::SchemaInput> schemaFiles;
    for (path const& schema : editionSchemaToMerge)
    {
        schemaFiles.push_back(Ent::SchemaInput{schema, Ent::SchemaSource::Edition});
    }
    for (path const& schema : runtimeSchemaToMerge)
    {
        schemaFiles.push_back(Ent::SchemaInput{schema, Ent::SchemaSource::Runtime});
    }

    Ent::updateSchemas(schemaFiles, schemaDir);

    printf("Schemas update done");
    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    std::cerr << typeid(ex).name() << " : " << ex.what() << std::endl;
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "UNKOWN EXCEPTION" << std::endl;
    return EXIT_FAILURE;
}
