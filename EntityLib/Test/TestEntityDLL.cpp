#include <ciso646>
#include <iostream>
#include <fstream>
#include <sstream>

#include <EntityLib.h>

void printNode(char const* name, Ent::Node const& node, std::string tab)
{
    switch (node.getDataType())
    {
    case Ent::DataType::null: printf("%s%s [null]\n", tab.c_str(), name); break;
    case Ent::DataType::string:
        printf("%s%s [string] : %s\n", tab.c_str(), name, node.getString());
        break;
    case Ent::DataType::number:
        printf("%s%s [number] : %f\n", tab.c_str(), name, node.getFloat());
        break;
    case Ent::DataType::integer:
        printf("%s%s [integer] : %lld\n", tab.c_str(), name, node.getInt());
        break;
    case Ent::DataType::object:
        printf("%s%s [object]\n", tab.c_str(), name);
        for (char const* field : node.getFieldNames())
        {
            // printf("%s  \"%s\"\n", tab.c_str(), field);
            Ent::Node const* sub = node.at(field);
            printNode(field, *sub, tab + "    ");
        }
        break;
    case Ent::DataType::array:
        printf("%s%s [array]\n", tab.c_str(), name);
        // for (Ent::Node const* item : node.getItems())
        for (int i = 0; i < node.size(); ++i)
        {
            std::stringstream ss;
            ss << i;
            printNode(ss.str().c_str(), *node.at(i), tab + "    ");
        }
        break;
    case Ent::DataType::boolean:
        printf("%s%s [boolean] : %s\n", tab.c_str(), name, node.getBool() ? "true" : "false");
        break;
    }
}

int main() // int argc, char** argv
try
{
    // Ent::loadStaticData();

    Ent::Scene scene = Ent::loadScene("X:/RawData/22_World/SceneMainWorld/SceneMainWorld.scene");
    printf("Scene Loaded\n");
    printf("Entity count : %zu\n", scene.objects.size());

    for (Ent::Entity const& ent : scene.objects)
    {
        printf("  Name \"%s\"\n", ent.getName());

        for (char const* type : ent.getComponentTypes())
        {
            printf("    Type \"%s\"\n", type);
            Ent::Node const& root = ent.getComponent(type)->root;
            printNode("", root, "      ");
        }
    }

    Ent::saveScene(scene, "X:/RawData/22_World/SceneMainWorld/SceneMainWorld.test.scene");

    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    std::cerr << typeid(ex).name() << " " << ex.what() << std::endl;
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "UNKOWN EXCEPTION" << std::endl;
    return EXIT_FAILURE;
}
