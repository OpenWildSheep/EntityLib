#include <ComponentMerge.h>

#include <filesystem>

#pragma warning(push, 0)
#include <iostream>
#pragma warning(pop)

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
    char const* allSingleSchemaPath = "WildPipeline/Schema/all/...";
    // canonical or weakly_canonical find the original physic drive but we want to keep X:
    char editCmd[1024];
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%s/%s")", argv[1], mergedCompSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%s/%s")", argv[1], textEditorSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 delete "%s/%s")", argv[1], allSingleSchemaPath);
    system(editCmd);

    Ent::updateComponents(argv[1]);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 add "%s/%s")", argv[1], allSingleSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%s/%s")", argv[1], mergedCompSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%s/%s")", argv[1], textEditorSchemaPath);
    system(editCmd);

    sprintf_s(editCmd, sizeof(editCmd), R"(p4 revert -a "%s/%s")", argv[1], allSingleSchemaPath);
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
