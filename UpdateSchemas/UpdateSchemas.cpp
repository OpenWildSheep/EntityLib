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
        ("t,toolsdir", "Path to the 'Tools' directory", cxxopts::value<path>()->default_value("X:/Tools"))
        ("h,help", "Print usage");
    // clang-format on

    path toolsPath;

    try
    {
        auto result = options.parse(argc, argv);
        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return EXIT_SUCCESS;
        }

        toolsPath = result["toolsdir"].as<path>();
    }
    catch (std::exception& ex)
    {
        std::cout << typeid(ex).name() << " - " << ex.what() << std::endl;
        std::cout << options.help() << std::endl;
        return EXIT_FAILURE;
    }

    auto const* mergedCompSchemaPath = "WildPipeline/Schema/MergedComponents.json";
    auto const* textEditorSchemaPath = "WildPipeline/Schema/TextEditorsSchema.json";
    auto const* allSingleSchemaPath = "WildPipeline/Schema/all";
    char editCmd[1024];
    // Edit MergedComponents.json
    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 edit "%ls/%s")", toolsPath.c_str(), mergedCompSchemaPath);
    system(editCmd);

    // Edit TextEditorsSchema.json
    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 edit "%ls/%s")", toolsPath.c_str(), textEditorSchemaPath);
    system(editCmd);

    // Get the list of deleted files
    std::set<path> deletedFiles;
    for (directory_entry const& dir_entry : directory_iterator{toolsPath / allSingleSchemaPath})
    {
        deletedFiles.insert(dir_entry.path());
    }

    // Delete single schema files
    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 delete "%ls/%s/...")", toolsPath.c_str(), allSingleSchemaPath);
    system(editCmd);

    // Generate schema files (MergedComponents.json, TextEditorsSchema.json and all single schema files)
    std::vector<Ent::SchemaInput> schemaFiles = {
        {toolsPath / "WildPipeline/Schema/RuntimeComponents.json", Ent::SchemaSource::Runtime},
        {toolsPath / "WildPipeline/Schema/EditionComponents.json", Ent::SchemaSource::Edition},
        {toolsPath / "WildPipeline/Schema/Scene-schema.json", Ent::SchemaSource::Edition},
    };

    Ent::updateSchemas(
        toolsPath,
        toolsPath / "WildPipeline/Schema/Dependencies.json",
        schemaFiles,
        toolsPath / "WildPipeline/Schema");

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
        for (directory_entry const& dir_entry : directory_iterator{toolsPath / allSingleSchemaPath})
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
    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 revert -a "%ls/%s")", toolsPath.c_str(), mergedCompSchemaPath);
    system(editCmd);

    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 revert -a "%ls/%s")", toolsPath.c_str(), textEditorSchemaPath);
    system(editCmd);

    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 revert -a "%ls/%s/...")", toolsPath.c_str(), allSingleSchemaPath);
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
