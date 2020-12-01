#pragma warning(push, 0)
#pragma warning(pop)

#include <WildRPCClient.h>
#include <exception>
#include <iostream>

int main() // int argc, char** argv
try
{
    WRPC::RPCClient client;

	WRPC_ASSERT(client.test1());
    WRPC_ASSERT(client.test2());

    std::cerr << "Test success" << std::endl;
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
