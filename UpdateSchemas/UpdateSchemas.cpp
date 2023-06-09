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

    path mergedCompSchemaPath = schemaDir / "MergedComponents.json";
    path textEditorSchemaPath = schemaDir / "TextEditorsSchema.json";
    path allSingleSchemaPath = schemaDir / "all";
    char editCmd[1024];
    // Edit MergedComponents.json
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%ls")", mergedCompSchemaPath.c_str());
    system(editCmd);

    // Edit TextEditorsSchema.json
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%ls")", textEditorSchemaPath.c_str());
    system(editCmd);

    // Get the list of deleted files
    std::set<path> deletedFiles;
    for (directory_entry const& dir_entry : directory_iterator{allSingleSchemaPath})
    {
        deletedFiles.insert(dir_entry.path());
    }

    // Delete single schema files
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 delete "%ls/...")", allSingleSchemaPath.c_str());
    system(editCmd);

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

    // Make the list of files to restore and files to add
    auto fileToRestorePath = temp_directory_path() / "tempRestoreFileList.txt";
    auto fileToAddPath = temp_directory_path() / "tempAddFileList.txt";
    {
        std::ofstream fileToRestore(fileToRestorePath);
        if (not fileToRestore.is_open())
        {
            fprintf(stderr, R"(Can't open file "%ls" for write)", fileToRestorePath.c_str());
            return EXIT_FAILURE;
        }
        std::ofstream fileToAdd(fileToAddPath);
        if (not fileToAdd.is_open())
        {
            fprintf(stderr, R"(Can't open file "%ls" for write)", fileToAddPath.c_str());
            return EXIT_FAILURE;
        }
        for (directory_entry const& dir_entry : directory_iterator{allSingleSchemaPath})
        {
            if (deletedFiles.count(dir_entry.path()) != 0)
            {
                fileToRestore << dir_entry.path().generic_string() << std::endl;
            }
            else
            {
                fileToAdd << dir_entry.path().generic_string() << std::endl;
            }
        }
    }
    // Restore
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 -x "%ls" revert)", fileToRestorePath.c_str());
    system(editCmd);
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 -x "%ls" edit)", fileToRestorePath.c_str());
    system(editCmd);
    // Add
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 -x "%ls" add)", fileToAddPath.c_str());
    system(editCmd);
    std::filesystem::remove(fileToRestorePath);
    std::filesystem::remove(fileToAddPath);

    // Revert unchanged
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%ls")", mergedCompSchemaPath.c_str());
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%ls")", textEditorSchemaPath.c_str());
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%ls/...")", allSingleSchemaPath.c_str());
    system(editCmd);

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
