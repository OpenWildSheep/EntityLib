#pragma warning(push, 0)
#include <ciso646>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning(pop)

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
    case Ent::DataType::freeobject:
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
        for (size_t i = 0; i < node.size(); ++i)
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

void displaySubSchema(std::string const& name, Ent::Subschema const& subschema, std::string indent)
{
    std::cout << indent << name << " : ";
    switch (subschema.type)
    {
    case Ent::DataType::array:
        std::cout << "array" << std::endl;
        if (subschema.minItems != 0)
            std::cout << indent << "  minItems:" << subschema.minItems << std::endl;
        if (subschema.maxItems != size_t(-1))
            std::cout << indent << "  maxItems:" << subschema.maxItems << std::endl;
        if (subschema.items != nullptr)
        {
            displaySubSchema("items", *subschema.items, indent + "  ");
        }
        break;
    case Ent::DataType::boolean: std::cout << "boolean" << std::endl; break;
    case Ent::DataType::integer: std::cout << "integer" << std::endl; break;
    case Ent::DataType::null: std::cout << "null" << std::endl; break;
    case Ent::DataType::number: std::cout << "number" << std::endl; break;
    case Ent::DataType::object:
    case Ent::DataType::freeobject:
        std::cout << "object" << std::endl;
        for (auto&& name_sub : subschema.properties)
        {
            displaySubSchema(std::get<0>(name_sub), std::get<1>(name_sub), indent + "  ");
        }
        break;
    case Ent::DataType::string: std::cout << "string" << std::endl; break;
    }
}

int main() // int argc, char** argv
try
{
    // Ent::mergeComponants("X:/Tools");

    // ******************************** Test iteration of schema **********************************
    Ent::EntityLib entlib = Ent::loadStaticData("X:/Tools");
    for (auto&& name_sub : entlib.schema.definitions)
    {
        displaySubSchema(std::get<0>(name_sub), std::get<1>(name_sub), {});
    }

    // ********************************** Test load/save scene ************************************
    Ent::Scene scene = entlib.loadScene("X:/RawData/22_World/SceneMainWorld/SceneMainWorld.scene");
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

    Ent::Component* heightObj = scene.objects.front().addComponent(entlib.schema, "HeightObj");
    heightObj->root.at("DisplaceNoiseList")->push();

    entlib.saveScene(scene, "X:/RawData/22_World/SceneMainWorld/SceneMainWorld.test.scene");

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
