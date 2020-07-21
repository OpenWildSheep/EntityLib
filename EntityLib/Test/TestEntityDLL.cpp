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
        if (subschema.singularItems != nullptr)
        {
            displaySubSchema("items", *subschema.singularItems, indent + "  ");
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

    Ent::EntityLib entlib = Ent::loadStaticData("X:/Tools");

    {
        // Test read prefab
        Ent::Entity ent = entlib.loadEntity("prefab.entity");
        Ent::Component* sysCreat = ent.getComponent("SystemicCreature");
        assert(sysCreat != nullptr);

        // TEST read setted values
        assert(sysCreat->root.at("Faction")->getString() == std::string("Shamans")); // set
        assert(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // set

        // TEST read array
        assert(sysCreat->root.at("ScriptList")->isSet());
        assert(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST default values
        assert(sysCreat->root.at("Burried")->getBool() == false); // default
        assert(not sysCreat->root.at("Burried")->isSet()); // default
        assert(sysCreat->root.at("Name")->getString() == std::string()); // default
        assert(not sysCreat->root.at("Name")->isSet()); // default

        sysCreat->root.at("Name")->setString("Shamane_male");
        entlib.saveEntity(ent, "prefab.copy.entity");
    }
    {
        // Test write prefab
        Ent::Entity ent = entlib.loadEntity("prefab.copy.entity");
        Ent::Component* sysCreat = ent.getComponent("SystemicCreature");
        assert(sysCreat != nullptr);
        // TEST read setted values
        assert(sysCreat->root.at("Faction")->getString() == std::string("Shamans")); // set
        assert(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // set

        // TEST read array
        assert(sysCreat->root.at("ScriptList")->isSet());
        assert(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST default values unchanged
        assert(sysCreat->root.at("Burried")->getBool() == false); // default
        assert(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST changed values
        assert(sysCreat->root.at("Name")->getString() == std::string("Shamane_male")); // set. changed.
        assert(sysCreat->root.at("Name")->isSet()); // set. changed.
    }
    {
        // Test read instance of
        Ent::Entity ent = entlib.loadEntity("instance.entity");
        Ent::Component* sysCreat = ent.getComponent("SystemicCreature");
        assert(sysCreat != nullptr);

        // TEST read overrided value
        assert(sysCreat->root.at("Faction")->getString() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        assert(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // Inherited
        assert(sysCreat->root.at("Life")->getFloat() == 1000.f); // Inherited

        // TEST read default value
        assert(sysCreat->root.at("Burried")->getBool() == false); // Inherited (from default)
        assert(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST read overrided in array
        assert(sysCreat->root.at("ScriptList")->at(1)->getString() == std::string("b2")); // Overrided
        assert(sysCreat->root.at("ScriptList")->at(1)->isSet()); // Overrided
        // TEST read Not overrided in array
        assert(sysCreat->root.at("ScriptList")->at(2)->getString() == std::string("c1")); // not overrided
        assert(not sysCreat->root.at("ScriptList")->at(2)->isSet()); // Not overrided

        // Programatically unset
        sysCreat->root.at("ScriptList")->at(1)->unset();
        // Programatically set
        sysCreat->root.at("ScriptList")->at(2)->setString("c2");

        // TEST read array
        assert(sysCreat->root.at("ScriptList")->isSet());
        assert(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST Extand array
        sysCreat->root.at("ScriptList")->push()->setString("d2");
        assert(sysCreat->root.at("ScriptList")->size() == 4);

        sysCreat->root.at("BehaviorState")->setString("Overrided");
        entlib.saveEntity(ent, "instance.copy.entity");
    }
    {
        // Test write instance of
        Ent::Entity ent = entlib.loadEntity("instance.copy.entity");
        Ent::Component* sysCreat = ent.getComponent("SystemicCreature");
        assert(sysCreat != nullptr);

        // TEST read overrided value
        assert(sysCreat->root.at("Faction")->getString() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        assert(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // Inherited
        assert(sysCreat->root.at("Life")->getFloat() == 1000.f); // Inherited

        // TEST read default value
        assert(sysCreat->root.at("Burried")->getBool() == false); // Inherited (from default)
        assert(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST read programatically overrided in array
        assert(sysCreat->root.at("ScriptList")->at(1)->getString() == std::string("b1")); // No more
                                                                                          // overrided
        assert(not sysCreat->root.at("ScriptList")->at(1)->isSet()); // No more overrided
        // TEST read programatically unset in array
        assert(sysCreat->root.at("ScriptList")->at(2)->getString() == std::string("c2")); // Overrided
        assert(sysCreat->root.at("ScriptList")->at(2)->isSet()); // Overrided

        // TEST read programatically extand array
        assert(sysCreat->root.at("ScriptList")->at(3)->getString() == std::string("d2")); // Overrided
        assert(sysCreat->root.at("ScriptList")->at(3)->isSet()); // Overrided

        // TEST read extanded array
        assert(sysCreat->root.at("ScriptList")->isSet());
        assert(sysCreat->root.at("ScriptList")->size() == 4);

        // TEST override value from code
        assert(
            sysCreat->root.at("BehaviorState")->getString()
            == std::string("Overrided")); // set. changed.
        assert(sysCreat->root.at("BehaviorState")->isSet()); // set. changed.

        entlib.saveEntity(ent, "instance.copy.entity");
    }

    // ******************************** Test iteration of schema **********************************
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

    Ent::Component* heightObj = scene.objects.front().addComponent(entlib, "HeightObj");
    heightObj->root.at("DisplaceNoiseList")->push();

    scene.objects.front().addComponent(entlib, "BeamGenerator");
    scene.objects.front().addComponent(entlib, "ExplosionEffect");

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
