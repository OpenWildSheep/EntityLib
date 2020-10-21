#include <ComponentMerge.h>
#include <iostream>

int main(int argc, char** argv)
try
{
    if (argc < 2)
    {
        fprintf(stderr, "Expected argument tools dir. Example : 'X:/Tools'");
        return EXIT_FAILURE;
    }

    char editCmd[1024];
    sprintf_s(
        editCmd, sizeof(editCmd), R"(p4 edit "%s\WildPipeline\Schema\Scene-schema.json)", argv[1]);

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
