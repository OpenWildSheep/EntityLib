#include <ComponentMerge.h>

#pragma warning(push, 0)
#include <iostream>
#pragma warning(pop)

#include "../EntityLib/external/filesystem.hpp"

int main(int argc, char** argv)
try
{
    if (argc < 2)
    {
        fprintf(stderr, "Expected argument tools dir. Example : 'X:/Tools'");
        return EXIT_FAILURE;
    }

    std::filesystem::path mergedCompSchemaPath = argv[1];
    mergedCompSchemaPath /= "WildPipeline/Schema/MergedComponents.json";
    mergedCompSchemaPath = std::filesystem::canonical(mergedCompSchemaPath);
    char editCmd[1024];
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%ls")", mergedCompSchemaPath.c_str());

    system(editCmd);

    Ent::updateComponents(argv[1]);
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
