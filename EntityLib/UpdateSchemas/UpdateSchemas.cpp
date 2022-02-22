#include <ComponentMerge.h>

#include <filesystem>
#include <set>
#include <fstream>

#pragma warning(push, 0)
#include <iostream>
#pragma warning(pop)

using namespace std::filesystem;

int main(int argc, char** argv)
try
{
    if (argc < 2)
    {
        fprintf(stderr, "Expected argument tools dir. Example : 'X:/Tools'");
        return EXIT_FAILURE;
    }

    char const* mergedCompSchemaPath = "WildPipeline/Schema/MergedComponents.json";
    char const* textEditorSchemaPath = "WildPipeline/Schema/TextEditorsSchema.json";
    char const* allSingleSchemaPath = "WildPipeline/Schema/all";
    char editCmd[1024];
    // Edit MergedComponents.json
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%s/%s")", argv[1], mergedCompSchemaPath);
    system(editCmd);

    // Edit TextEditorsSchema.json
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%s/%s")", argv[1], textEditorSchemaPath);
    system(editCmd);

    // Get the list of deleted files
    std::set<path> deletedFiles;
    for (directory_entry const& dir_entry : directory_iterator{path(argv[1]) / allSingleSchemaPath})
    {
        deletedFiles.insert(dir_entry.path());
    }

    // Delete single schema files
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 delete "%s/%s/...")", argv[1], allSingleSchemaPath);
    system(editCmd);

    // Generate schema files (MergedComponents.json, TextEditorsSchema.json and all single schema files)
    Ent::updateComponents(argv[1]);

    // Make the list of files to restore and files to add
    auto fileToRestorePath = std::filesystem::temp_directory_path() / "tempRestoreFileList.txt";
    auto fileToAddPath = std::filesystem::temp_directory_path() / "tempAddFileList.txt";
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
        for (directory_entry const& dir_entry :
             directory_iterator{path(argv[1]) / allSingleSchemaPath})
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
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%s/%s")", argv[1], mergedCompSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%s/%s")", argv[1], textEditorSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%s/%s/...")", argv[1], allSingleSchemaPath);
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
