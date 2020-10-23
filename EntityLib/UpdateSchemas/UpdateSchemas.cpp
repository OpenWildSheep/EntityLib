#include <ComponentMerge.h>
#include <iostream>
#include <filesystem>

int main(int argc, char** argv)
try
{
    if (argc < 2)
    {
        fprintf(stderr, "Expected argument tools dir. Example : 'X:/Tools'");
        return EXIT_FAILURE;
    }

    std::experimental::filesystem::path sceneSchemaPath = argv[1];
    sceneSchemaPath /= "WildPipeline/Schema/Scene-schema.json";
    sceneSchemaPath = std::experimental::filesystem::canonical(sceneSchemaPath);
    char editCmd[1024];
    sprintf_s(editCmd, sizeof(editCmd), R"(p4 edit "%ls")", sceneSchemaPath.c_str());

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
