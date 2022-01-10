#pragma warning(push, 0)
#include <ciso646>
#include <iostream>
#include <fstream>
#include <sstream>
#define NOMINMAX
#include <windows.h>
#pragma warning(pop)

#include <EntityLib.h>
#include <ComponentMerge.h>

#include "TestNodeHandler.h"

static void printNode(char const* name, Ent::Node const& node, std::string const& tab)
{
    using namespace Ent;
    switch (node.getDataType())
    {
    case Ent::DataType::null: printfmt("%s%s [null]\n", tab.c_str(), name); break;
    case Ent::DataType::string:
        printfmt("%s%s [string] : %s\n", tab.c_str(), name, node.getString());
        break;
    case Ent::DataType::number:
        printfmt("%s%s [number] : %f\n", tab.c_str(), name, node.getFloat());
        break;
    case Ent::DataType::integer:
        printfmt("%s%s [integer] : %lld\n", tab.c_str(), name, node.getInt());
        break;
    case Ent::DataType::object:
        printfmt("%s%s [object]\n", tab.c_str(), name);
        for (char const* field : node.getFieldNames())
        {
            // printfmt("%s  \"%s\"\n", tab.c_str(), field);
            Ent::Node const* sub = node.at(field);
            printNode(field, *sub, tab + "    ");
        }
        break;
    case Ent::DataType::array:
        printfmt("%s%s [array]\n", tab.c_str(), name);
        // for (Ent::Node const* item : node.getItems())
        for (size_t i = 0; i < node.size(); ++i)
        {
            std::stringstream ss;
            ss << i;
            printNode(ss.str().c_str(), *node.at(i), tab + "    ");
        }
        break;
    case Ent::DataType::boolean:
        printfmt("%s%s [boolean] : %s\n", tab.c_str(), name, node.getBool() ? "true" : "false");
        break;
    case Ent::DataType::entityRef:
        printfmt(
            "%s%s [EntityRef] : %s\n", tab.c_str(), name, node.getEntityRef().entityPath.c_str());
        break;
    case Ent::DataType::oneOf:
        printfmt("%s%s [Union]\n", tab.c_str(), name);
        printNode("Data", *node.getUnionData(), tab + "    ");
        break;
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid DataType when parsing meta"); break;
    }
}

static void
displaySubSchema(std::string const& name, Ent::Subschema const& subschema, std::string const& indent)
{
    if (size(indent) > 80)
    {
        return;
    }
    Ent::printfmt("%s%s : ", indent.c_str(), name.c_str());
    switch (subschema.type)
    {
    case Ent::DataType::array:
        Ent::printfmt("array\n");
        if (subschema.minItems != 0)
        {
            Ent::printfmt("%s  minItems:%d\n", indent.c_str(), subschema.minItems);
        }
        if (subschema.maxItems != size_t(-1))
        {
            Ent::printfmt("%s  maxItems:%d\n", indent.c_str(), subschema.maxItems);
        }
        if (subschema.singularItems != nullptr)
        {
            displaySubSchema("items", subschema.singularItems->get(), indent + "  ");
        }
        break;
    case Ent::DataType::boolean: Ent::printfmt("boolean\n"); break;
    case Ent::DataType::integer: Ent::printfmt("integer\n"); break;
    case Ent::DataType::null: Ent::printfmt("null\n"); break;
    case Ent::DataType::number: Ent::printfmt("number\n"); break;
    case Ent::DataType::object:
        Ent::printfmt("object\n");
        for (auto&& [propname, sub] : subschema.properties)
        {
            displaySubSchema(propname, *sub, indent + "  ");
        }
        break;
    case Ent::DataType::string: Ent::printfmt("string\n"); break;
    case Ent::DataType::entityRef: Ent::printfmt("entity ref\n"); break;
    case Ent::DataType::oneOf: Ent::printfmt("oneOf\n"); break;
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid DataType when parsing meta"); break;
    }
}

// NOLINTNEXTLINE
#define ENTLIB_CHECK_EXCEPTION(expression, excep_type)                                             \
    {                                                                                              \
        bool exception_throw = false;                                                              \
        try                                                                                        \
        {                                                                                          \
            expression;                                                                            \
        }                                                                                          \
        catch (std::remove_reference_t<excep_type>&)                                               \
        {                                                                                          \
            exception_throw = true;                                                                \
        }                                                                                          \
        catch (...)                                                                                \
        {                                                                                          \
            ENTLIB_LOGIC_ERROR("Wrong exception thrown!");                                         \
        }                                                                                          \
        ENTLIB_ASSERT_MSG(exception_throw, "Exception not thrown!");                               \
    }

// NOLINTNEXTLINE(readability-function-size)
int main(int argc, char** argv)
try
{
    SetConsoleOutputCP(65001);
    bool doDisplayScene = false;
    bool doDisplaySubSchema = false;
    bool dumpNodes = false;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--displaySchema") == 0)
        {
            doDisplaySubSchema = true;
        }
        else if (strcmp(argv[i], "--displayScene") == 0)
        {
            doDisplayScene = true;
        }
        else if (strcmp(argv[i], "--dumpNodes") == 0)
        {
            dumpNodes = true;
        }
    }

    // Ent::updateComponents("X:/Tools");
#ifdef _DEBUG
    bool const doMergeComponents = false;
#else
    bool const doMergeComponents = true;
#endif

    Ent::EntityLib entlib("X:/RawData/..", doMergeComponents);
    using namespace std::filesystem;

    entlib.setLogicErrorPolicy(Ent::LogicErrorPolicy::Throw);
    ENTLIB_CHECK_EXCEPTION(ENTLIB_LOGIC_ERROR("Test logic error"), std::logic_error);
    entlib.setLogicErrorPolicy(Ent::LogicErrorPolicy::Terminate);

    entlib.rawdataPath = current_path(); // It is a hack to work in the working dir
#ifdef _DEBUG
    entlib.validationEnabled = false;
#else
    entlib.validationEnabled = true;
#endif

    auto prevValidationEnabled = entlib.validationEnabled;
    entlib.validationEnabled = false;
    testNodeHandler(entlib);
    entlib.rawdataPath = current_path();
    entlib.validationEnabled = prevValidationEnabled;

    ENTLIB_ASSERT(Ent::format("Toto %d", 37) == "Toto 37");

    {
        std::map<std::string, int> emptyMap;
        ENTLIB_CHECK_EXCEPTION(AT(emptyMap, "not"), Ent::InvalidKey);
    }

    using EntityPtr = std::unique_ptr<Ent::Entity>;

    // Test $ref links in entlib.schema.schema.allDefinitions
    char const* colorRef = "Color";
    ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(colorRef) == 1);

    // Check Ent::Subschema::getUnionTypesMap
    char const* cinematicGDRef = "CinematicGD";
    Ent::Subschema const& cinematicGDSchema = entlib.schema.schema.allDefinitions.at(cinematicGDRef);
    Ent::Subschema const& scriptEventUnionSchema =
        cinematicGDSchema.properties.at("ScriptEvents")->singularItems->get();
    auto&& nameToTypeMap = scriptEventUnionSchema.getUnionTypesMap();
    ENTLIB_ASSERT(size(nameToTypeMap) == 9);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTestCurrentGameState") == 1);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTriggerEventHandlerPost") == 1);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTestEndCurrentSequence") == 1);

    // Ensure that all components have a ref and is in entlib.schema.schema.allDefinitions
    for (auto&& name_schema : entlib.schema.components)
    {
        auto&& absRef = std::get<1>(name_schema)->name;
        ENTLIB_ASSERT(absRef.find("./") == std::string::npos);
        ENTLIB_ASSERT(absRef.find('#') == std::string::npos);
        ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(absRef) == 1);
    }

    static constexpr auto PrefabSubEntityCount = 5;

    {
        auto node = entlib.loadFileAsNode(
            "myseedpatchMarianne.seedpatchdata.node",
            entlib.schema.schema.allDefinitions["SeedPatchDataList"]);
        node->saveNode("myseedpatchMarianne.seedpatchdata.copy.node");
    }
    {
        // When there is a $schema field
        auto node = entlib.loadFileAsNode("myseedpatch_schema.node");
        ENTLIB_ASSERT(node->getSchema() == entlib.getSchema("SeedPatchDataList"));
        // When there is a $schema field with different style
        node = entlib.loadFileAsNode("myseedpatch_schema_style.node");
        ENTLIB_ASSERT(node->getSchema() == entlib.getSchema("SeedPatchDataList"));
        // When it is an Entity without schema field
        node = entlib.loadFileAsNode("prefab.entity");
        ENTLIB_ASSERT(node->getSchema() == entlib.getSchema(Ent::entitySchemaName));
        // No $schema but a right pre-extention
        node = entlib.loadFileAsNode("test.CharacterControllerGD.node");
        ENTLIB_ASSERT(node->getSchema() == entlib.getSchema("CharacterControllerGD"));
        // No $schema but pre-extention with bad case
        node = entlib.loadFileAsNode("test_wrong_casse.chAracTercontrOlleRgd.nOde");
        ENTLIB_ASSERT(node->getSchema() == entlib.getSchema("CharacterControllerGD"));
        // No $schema, no .entity, wrong pre-extention
        ENTLIB_CHECK_EXCEPTION(
            entlib.loadFileAsNode("test.ThisTypeDoesntExist.node"), Ent::UnknownSchema);
    }
    entlib.clearCache();
    {
        auto node =
            entlib.loadFileAsNode("instance.entity", entlib.schema.schema.allDefinitions["Entity"]);
        auto prefabHisto = node->getPrefabHistory();
    }
    // Temporarily disable validation to read some RawData files
    entlib.validationEnabled = false;
    {
        entlib.rawdataPath = "X:/RawData"; // It is a hack to work in the working dir
        auto node = entlib.loadFileAsNode(
            "20_Scene/KOM2021/SubScenesKOM/FindWolvesRegenBubble/"
            "FindWolvesRegenBubbleMain/editor/FindWolvesRegenBubbleMain.scene",
            entlib.schema.schema.allDefinitions["Entity"]);
        auto nodeRef = "Components/SubScene/Embedded/ShamanFullBlue_ent_001";
        auto ent = node->resolveNodeRef(nodeRef);
        auto entpath = node->makeNodeRef(ent);
        ENTLIB_ASSERT(entpath == nodeRef);
        entpath = ent->makeAbsoluteNodeRef();
        ENTLIB_ASSERT(entpath == nodeRef);
        entpath = node->makeAbsoluteNodeRef();
        ENTLIB_ASSERT(entpath == ".");

        auto prefabHisto = ent->getPrefabHistory();
        ENTLIB_ASSERT(prefabHisto.size() == 3);
        ENTLIB_ASSERT(
            prefabHisto[0].prefabPath == "02_creature/human/male/entity/legacy/human_male.entity");
        ENTLIB_ASSERT(
            prefabHisto[1].prefabPath == "02_creature/human/male/entity/legacy/shaman_male.entity");
        ENTLIB_ASSERT(
            prefabHisto[2].prefabPath
            == "02_Creature/Human/MALE/Entity/validate/ShamanFullBlue.entity");
    }
    {
        auto node = entlib.loadFileAsNode(
            "20_Scene/KOM2021/SubScenesKOM/FindWolvesRegenBubble/"
            "FindWolvesRegenBubbleMain/editor/FindWolvesRegenBubbleMain.scene",
            entlib.schema.schema.allDefinitions["Entity"]);
        auto nodeRef =
            R"(Components/SubScene/Embedded/ShamanFullBlue_ent_001/Components/TransformGD)";
        auto ent = node->resolveNodeRef(nodeRef);
        auto entpath = node->makeNodeRef(ent);
        ENTLIB_ASSERT(entpath == nodeRef);
        auto prefabHisto = ent->getPrefabHistory();
        ENTLIB_ASSERT(
            prefabHisto[0].prefabPath == "02_creature/human/male/entity/legacy/human_male.entity");
        ENTLIB_ASSERT(
            prefabHisto[1].prefabPath == "02_creature/human/male/entity/legacy/shaman_male.entity");
        ENTLIB_ASSERT(
            prefabHisto[2].prefabPath
            == "02_Creature/Human/MALE/Entity/validate/ShamanFullBlue.entity");
        entlib.rawdataPath = current_path(); // Work in Test dir
    }
    entlib.validationEnabled = prevValidationEnabled;
    {
        auto node =
            entlib.loadFileAsNode("instance.entity", entlib.schema.schema.allDefinitions["Entity"]);
        auto nodeRef = R"(Components/SubScene/Embedded/EP1-Spout_LINK_001/Components/NetworkLink)";
        auto ent = node->resolveNodeRef(nodeRef);
        auto entpath = node->makeNodeRef(ent);
        ENTLIB_ASSERT(entpath == nodeRef);
        auto nullPath = ent->makeNodeRef(ent);
        ENTLIB_ASSERT(nullPath.empty() or nullPath == ".");
        // Test Union
        auto typedValueUnion = node->at("Components")
                                   ->mapInsert("ScriptComponentGD")
                                   ->getUnionData()
                                   ->at("CommonDataMap")
                                   ->mapInsert("Test")
                                   ->at("Value");
        auto typeValueRef = R"(Components/ScriptComponentGD/CommonDataMap/Test/Value)";
        ENTLIB_ASSERT(node->makeNodeRef(typedValueUnion) == typeValueRef);
        auto stringUnionData = typedValueUnion->setUnionType("string");
        auto strRef = R"(Components/ScriptComponentGD/CommonDataMap/Test/Value/string)";
        ENTLIB_ASSERT(node->makeNodeRef(stringUnionData) == strRef);
        ENTLIB_ASSERT(typedValueUnion->makeNodeRef(stringUnionData) == "string");

        auto prefabHisto = ent->getPrefabHistory();
        ENTLIB_ASSERT(prefabHisto.size() == 3);
        ENTLIB_ASSERT(std::all_of(
            begin(prefabHisto),
            end(prefabHisto),
            [](Ent::Node::PrefabInfo const& pi)
            { return pi.node->getSchema()->name == "NetworkLink"; }));
        ENTLIB_ASSERT(prefabHisto[0].nodeRef == ".");
        ENTLIB_ASSERT(prefabHisto[1].nodeRef == "Components/NetworkLink");
        ENTLIB_ASSERT(
            prefabHisto[2].nodeRef
            == "Components/SubScene/Embedded/EP1-Spout_LINK_001/Components/NetworkLink");
        ENTLIB_ASSERT(prefabHisto[0].prefabPath == "test.NetworkLink.node");
        ENTLIB_ASSERT(prefabHisto[1].prefabPath == "test_prefab_history.entity");
        ENTLIB_ASSERT(prefabHisto[2].prefabPath == "prefab.entity");
        node->checkParent(nullptr);
    }
    entlib.clearCache();
    auto testPrefabEntity = [](Ent::Entity const* ent)
    {
        // ActorStates
        Ent::Node const& actorStates = ent->getActorStates();
        ENTLIB_ASSERT(actorStates.getDataType() == Ent::DataType::array);
        ENTLIB_ASSERT(actorStates.size() == 2);
        Ent::Node const* actorState = actorStates.at(0llu);
        ENTLIB_ASSERT(actorState != nullptr);
        ENTLIB_ASSERT(actorState->getSchema()->getUnionNameField() == std::string("className"));
        ENTLIB_ASSERT(actorState->getSchema()->getUnionDataField() == std::string("classData"));
        Ent::Node const* actorStateDead = actorState->getUnionData();
        char const* actorStateDeadType = actorState->getUnionType();
        ENTLIB_ASSERT(strcmp(actorStateDeadType, "ActorStateHoldingItem") == 0);
        ENTLIB_ASSERT(actorStateDead != nullptr);
        Ent::Node const* exitRequired = actorStateDead->at("ItemEntityRef");
        ENTLIB_ASSERT(exitRequired != nullptr);
        ENTLIB_ASSERT(exitRequired->getEntityRef().entityPath == std::string("tutu"));
        Ent::Node const* entityStatePlayer = actorStates.mapGet("EntityStatePlayer");
        ENTLIB_ASSERT(entityStatePlayer != nullptr);
        Ent::Node const* entityStatePlayerData = entityStatePlayer->getUnionData();
        ENTLIB_ASSERT(entityStatePlayerData != nullptr);

        // Map and Set overridePolicy
        Ent::Component const* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node const* tags = pathNodeGD->root->at("Tags")->at("Tags");
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->at(0llu)->at(0llu)->getString() == std::string("a"));
        ENTLIB_ASSERT(tags->at(1llu)->at(0llu)->getString() == std::string("c"));
        ENTLIB_ASSERT(tags->at(1llu)->at(1llu)->size() == 1);
        ENTLIB_ASSERT(tags->at(1llu)->at(1llu)->at(0llu)->getString() == std::string("2"));
        // Test mapGet on map and set
        ENTLIB_ASSERT(tags->mapGet("a")->mapGet("1")->getString() == std::string("1"));

        ENTLIB_ASSERT(tags->getKeyType() == Ent::DataType::string);
        auto keys = tags->getKeysString();
        ENTLIB_ASSERT(keys.size() == 3);
        for (auto&& k : keys)
        {
            ENTLIB_ASSERT(tags->mapGet(k.c_str()) != nullptr);
        }

        // Test default value
        Ent::Component const* voxelSimulationGD = ent->getComponent("VoxelSimulationGD");
        ENTLIB_ASSERT(
            voxelSimulationGD->root->at("TransmissionBySecond")->getFloat() == 3.402823466385289e+38);
        ENTLIB_ASSERT(voxelSimulationGD->root->at("TransmissionBySecond")->isDefault());
        ENTLIB_ASSERT(voxelSimulationGD->root->getTypeName() == std::string("VoxelSimulationGD"));

        // TEST read inherited values in inherited component
        Ent::Component const* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(not heightObj->root->at("Subdivision")->isDefault());
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getDefaultInt() == 3);
        ENTLIB_ASSERT(
            heightObj->root->at("Subdivision")->getSchema()->userMeta["testUserMetatdata"].get<int>()
            == 42);

        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // Test read Thumbnail
        ENTLIB_ASSERT(ent->getThumbnail() != nullptr);
        ENTLIB_ASSERT(ent->getThumbnail() == std::string("TestThumbnail"));

        // Test read prefab
        Ent::Component const* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Shamans")); // set
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->isSet()); // is set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->isSet()); // is set

        // TEST comment
        ENTLIB_ASSERT(
            sysCreat->root->at("BehaviorState")->getString() == std::string("W/*at*/c//h")); // set

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->size() == 3);

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default

        // TEST SubScene
        Ent::SubSceneComponent const* subScenecomp = ent->getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount);
        ENTLIB_ASSERT(allSubEntities.front()->getName() == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(allSubEntities.front()->getColor()[0] == 255);

        // TEST union
        Ent::Component const* cinematicGD = ent->getComponent("CinematicGD");
        Ent::Node const* scriptEvents = cinematicGD->root->at("ScriptEvents");
        ENTLIB_ASSERT(scriptEvents->getDataType() == Ent::DataType::array);

        // Read Union type
        Ent::Node const* oneOfScripts = scriptEvents->at(0llu);
        ENTLIB_ASSERT(oneOfScripts->getDataType() == Ent::DataType::oneOf);
        Ent::Node const* cineEvent = oneOfScripts->getUnionData();
        ENTLIB_ASSERT(cineEvent != nullptr);
        ENTLIB_ASSERT(cineEvent->getTypeName() == std::string("CineEventTriggerEventHandlerPost"));
        auto fieldNames = cineEvent->getFieldNames();
        ENTLIB_ASSERT(fieldNames[1] == std::string("EventName"));
        ENTLIB_ASSERT(fieldNames[2] == std::string("Super"));

        Ent::Node const* nbEnt = cineEvent->at("EventName");
        ENTLIB_ASSERT(nbEnt != nullptr);
        ENTLIB_ASSERT(nbEnt->getDataType() == Ent::DataType::string);
        ENTLIB_ASSERT(nbEnt->getString() == std::string("Toto"));

        // TEST sub-object with non-default values
        Ent::Component const* ldprimitive = ent->getComponent("LDPrimitive");
        Ent::Node const* primitiveData = ldprimitive->root->at("PrimitiveData");
        ENTLIB_ASSERT(primitiveData->at("Height")->getFloat() == 42.0);

        // TEST Default size for array is minItems
        Ent::Component const* physicsGD = ent->getComponent("PhysicsGD");
        Ent::Node const* axisRestriction = physicsGD->root->at("AxisRestriction");
        ENTLIB_ASSERT(axisRestriction->size() == 3);

        // Test default values related to a property of type class/struct.
        Ent::Component const* characterController = ent->getComponent("CharacterControllerGD");
        Ent::Node const* slideData = characterController->root->at("SlideData");
        Ent::Node const* adherenceMin = slideData->at("speedMediumCoeffIn");
        Ent::Node const* in = adherenceMin->at("in");
        ENTLIB_ASSERT(in->size() == 2);
        ENTLIB_ASSERT(in->at(0llu)->getFloat() == -1.);
        ENTLIB_ASSERT(in->at(1llu)->getFloat() == 0.5);

        // Ensure that default values of property are not poluted by default values of pointer class
        Ent::Component const* testDefaultValues = ent->getComponent("TestDefaultValues");
        ENTLIB_ASSERT(testDefaultValues != nullptr);
        Ent::Node const* propertyWithDefault = testDefaultValues->root->at("propertyWithDefault");
        Ent::Node const* propertyWithDefault2 = propertyWithDefault->at("propertyWithDefault2");
        ENTLIB_ASSERT(propertyWithDefault2->at("A")->getInt() == 3);
        ENTLIB_ASSERT(propertyWithDefault2->at("B")->getInt() == 0);
        Ent::Node const* propertyWithDefault3 = propertyWithDefault->at("propertyWithDefault3");
        ENTLIB_ASSERT(propertyWithDefault3->at("A")->getInt() == 3);
        ENTLIB_ASSERT(propertyWithDefault3->at("B")->getInt() == 0);

        // Test Node's InstanceOf
        Ent::Component const* seedPatch = ent->getComponent("SeedPatch");
        ENTLIB_ASSERT(seedPatch->root->at("NoiseSizeX")->getFloat() == 1.);
        ENTLIB_ASSERT(seedPatch->root->at("NoiseSizeY")->getFloat() == 2.);
        ENTLIB_ASSERT(seedPatch->root->at("NoiseOffsetX")->getFloat() == 2.);
    };

    {
        Ent::Entity ent(entlib, "TestResetInstanceOf");
        ent.resetInstanceOf("prefab.entity");
        ENTLIB_ASSERT(ent.hasOverride()); // resetInstanceOf does override the "instanceOf"
        ENTLIB_ASSERT(ent.getInstanceOf() == std::string("prefab.entity"));
    }
    {
        EntityPtr ent = entlib.loadEntity("missing_embedded.entity");
        ENTLIB_ASSERT(ent->getComponents().empty());
    }
    {
        EntityPtr ent = entlib.loadEntity("prefab.entity");

        // Test title/description
        {
            auto rigodBodyCoeffSchema = ent->getComponent("CharacterControllerGD")
                                            ->root->at("HeadCollisionData")
                                            ->at("softCollisionRigidbodyCoeff")
                                            ->getSchema();
            ENTLIB_ASSERT(rigodBodyCoeffSchema->title.find("Rigidbody") != std::string::npos);
            ENTLIB_ASSERT(rigodBodyCoeffSchema->description.find("rigidbody") != std::string::npos);
        }

        auto setOfObject = ent->getComponent("TestSetOfObject");
        ENTLIB_ASSERT(setOfObject);
        auto mapTest = setOfObject->root->at("MapOfObject");
        auto testParent = mapTest->mapInsert("Should_not_appear_in_diff");
        ENTLIB_ASSERT(testParent);
        ENTLIB_ASSERT(testParent->getParentNode()->getSchema()->linearItems.has_value());
        ENTLIB_ASSERT(testParent->getParentNode()->getParentNode()->isMapOrSet());
        ENTLIB_ASSERT(mapTest->mapErase("Should_not_appear_in_diff"));

        // Test a fixed-size array is not "addedInInstance"
        Ent::Component* trans = ent->getComponent("TransformGD");
        ENTLIB_ASSERT(trans != nullptr);
        trans->root->at("Position")->at(0llu)->setFloat(36.f);
        trans->root->at("Position")->unset();
        ENTLIB_ASSERT(not trans->root->at("Position")->hasOverride());

        // Test Variant
        Ent::Component const* testArrays = ent->getComponent("TestArrays");
        ENTLIB_ASSERT(testArrays->root->at("Variant")->getUnionData()->getFloat() == 3.1416);
        nlohmann::json withoutIndex = testArrays->root->at("Variant")->toJson(
            Ent::OverrideValueSource::OverrideOrPrefab, true, {}, false);
        ENTLIB_ASSERT(withoutIndex.count("variantIndex") == 0);
        nlohmann::json withIndex = testArrays->root->at("Variant")->toJson(
            Ent::OverrideValueSource::OverrideOrPrefab, true, {}, true);
        ENTLIB_ASSERT(withIndex.at("variantIndex") == 1);

        // Test saveNode
        Ent::Component const* heightObj = ent->getComponent("HeightObj");
        heightObj->root->saveNode("test.HeightObj.node");

        testPrefabEntity(ent.get());
        // Test mapErase in set of primitive
        Ent::Component* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node* tags = pathNodeGD->root->at("Tags")->at("Tags");
        auto primSet = tags->mapGet("a");
        ENTLIB_ASSERT(primSet->getParentNode()->getParentNode()->isMapOrSet());
        ENTLIB_CHECK_EXCEPTION(primSet->mapErase("1"), Ent::BadArrayType);

        // Set Union type and override
        Ent::Component* cinematicGD = ent->getComponent("CinematicGD");
        Ent::Node* scriptEvents = cinematicGD->root->at("ScriptEvents");
        Ent::Node* oneOfScripts2 = scriptEvents->at(1llu);
        ENTLIB_ASSERT(oneOfScripts2->getDataType() == Ent::DataType::oneOf);
        ENTLIB_ASSERT(
            oneOfScripts2->getUnionType() == std::string("CineEventTriggerEventHandlerPost"));
        ENTLIB_ASSERT(oneOfScripts2->getUnionTypeIndex() == 5);
        oneOfScripts2->setUnionType("CineEventTestCurrentGameState");
        ENTLIB_CHECK_EXCEPTION(oneOfScripts2->setUnionType("ThisTypeDoesntExist"), Ent::BadUnionType);
        Ent::Node* testCurrentState = oneOfScripts2->getUnionData();
        ENTLIB_ASSERT(oneOfScripts2->getUnionType() == std::string("CineEventTestCurrentGameState"));
        ENTLIB_ASSERT(oneOfScripts2->getUnionTypeIndex() == 0);
        auto fieldNames2 = testCurrentState->getFieldNames();
        ENTLIB_ASSERT(fieldNames2[0] == std::string("GameStateName"));
        ENTLIB_ASSERT(fieldNames2[1] == std::string("Super"));
        testCurrentState->at("GameStateName")->setString("Pouet!");

        // Set Union type without override
        Ent::Node* oneOfScripts3 = scriptEvents->at(2llu);
        ENTLIB_ASSERT(oneOfScripts3->getDataType() == Ent::DataType::oneOf);
        ENTLIB_ASSERT(
            oneOfScripts3->getUnionType() == std::string("CineEventTriggerEventHandlerPost"));
        oneOfScripts3->setUnionType("CineEventTestCurrentGameState");

        // Push in an array of Union
        Ent::Node const* oneOfScripts4 = scriptEvents->push();
        ENTLIB_ASSERT(oneOfScripts4->getDataType() == Ent::DataType::oneOf);
        // CineEventTestCurrentGameState is the first one
        ENTLIB_ASSERT(oneOfScripts4->getUnionType() == std::string("CineEventTestCurrentGameState"));
        ENTLIB_ASSERT(scriptEvents->at(3llu) == oneOfScripts4);

        // TEST simple entity ref creation
        Ent::Component* testEntityRef = ent->addComponent("TestEntityRef");
        ENTLIB_ASSERT(testEntityRef != nullptr);
        ENTLIB_ASSERT(testEntityRef->root->at("TestRef")->getEntityRef().entityPath.empty());
        testEntityRef->root->at("TestRef")->setEntityRef(ent->makeEntityRef(*ent));
        ENTLIB_ASSERT(testEntityRef->root->at("TestRef")->getEntityRef().entityPath == ".");
        Ent::SubSceneComponent* subScenecomp = ent->getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        testEntityRef->root->at("TestRef")->setEntityRef(ent->makeEntityRef(*allSubEntities.front()));

        // TEST Union not in Object
        Ent::Component* testUnion = ent->addComponent("TestUnion");
        Ent::Node* un = testUnion->root->at("Union");
        un->unset();
        ENTLIB_ASSERT(not un->hasOverride());
        ENTLIB_ASSERT(un->getUnionType() == std::string("s32"));
        un->setUnionType("float");
        ENTLIB_ASSERT(un->hasOverride());
        ENTLIB_ASSERT(un->getUnionType() == std::string("float"));
        un->setUnionType("s32");
        ENTLIB_ASSERT(un->hasOverride());
        ENTLIB_ASSERT(un->getUnionType() == std::string("s32"));
        un->unset();
        ENTLIB_ASSERT(not un->hasOverride());
        ENTLIB_ASSERT(un->getUnionType() == std::string("s32"));
        // TEST Union not in Array
        Ent::Node* unArr = testUnion->root->at("UnionArray");
        Ent::Node* newUnion = unArr->push();
        ENTLIB_ASSERT(not newUnion->getUnionData()->hasOverride());
        ENTLIB_ASSERT(newUnion->getUnionType() == std::string("s32"));
        // TEST Union not in Object in Array
        unArr = testUnion->root->at("UnionObjectArray");
        Ent::Node* obj = unArr->push();
        newUnion = obj->at("Union");
        ENTLIB_ASSERT(not newUnion->getUnionData()->hasOverride());
        ENTLIB_ASSERT(newUnion->getUnionType() == std::string("s32"));

        // TEST MaxActivationLevel
        ent->setMaxActivationLevel(Ent::ActivationLevel::InWorld);

        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat->root->at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Name")->isSet()); // default
        sysCreat->root->at("Name")->setString("Shamane_male");
        entlib.saveEntity(*ent, "prefab.copy.entity");

        // TEST SubScene detach
        auto originalSubEntities = ent->getSubSceneComponent()->embedded->getObjects();
        ENTLIB_ASSERT(not originalSubEntities.empty());
        auto detachedSubScene = ent->getSubSceneComponent()->detachEmbedded();
        ENTLIB_ASSERT(ent->getSubSceneComponent()->embedded->getObjects().empty());
        auto detachedSubEntities = detachedSubScene->getObjects();
        ENTLIB_ASSERT(std::equal(
            begin(originalSubEntities), end(originalSubEntities), begin(detachedSubEntities)));

        ent->removeSubSceneComponent();
        entlib.saveEntity(*ent, "prefab.emptyembbeded.entity"); // to check the schema

        // TEST arrays default values
        ent->removeComponent("TransformGD");
        Ent::Component* transformGD = ent->addComponent("TransformGD");
        Ent::Node* mat33 = transformGD->root->at("Matrix");
        auto testMat33 = [&]()
        {
            ENTLIB_ASSERT(mat33->at(0llu)->getFloat() == 1.);
            ENTLIB_ASSERT(mat33->at(0llu)->getDefaultFloat() == 1.);
            ENTLIB_ASSERT(mat33->at(1llu)->getFloat() == 0.);
            ENTLIB_ASSERT(mat33->at(1llu)->getDefaultFloat() == 0.);
            ENTLIB_ASSERT(mat33->at(2llu)->getFloat() == 0.);
            ENTLIB_ASSERT(mat33->at(3llu)->getFloat() == 0.);
            ENTLIB_ASSERT(mat33->at(4llu)->getFloat() == 1.);
            ENTLIB_ASSERT(mat33->at(4llu)->getDefaultFloat() == 1.);
            ENTLIB_ASSERT(mat33->at(5llu)->getFloat() == 0.);
        };

        Ent::Component* testDefaultValues = ent->addComponent("TestDefaultValues");
        ENTLIB_ASSERT(testDefaultValues->root->hasOverride());
        mat33 = testDefaultValues->root->at("Matrix");
        testMat33();
        mat33 = testDefaultValues->root->at("Matrix2");
        ENTLIB_ASSERT(mat33->at(4llu)->getDefaultFloat() == 4.);
        ENTLIB_ASSERT(mat33->at(4llu)->getFloat() == 4.);
        ENTLIB_ASSERT(not mat33->at(4llu)->hasOverride());
        ENTLIB_ASSERT(not mat33->at(4llu)->isSet());
    }
    {
        // Test Arrays size overrides
        auto ent = entlib.loadEntityReadOnly("instance_arrays.entity");
        ENTLIB_ASSERT(ent);
        Ent::Component const* comp = ent->getComponent("TestArrays");
        ENTLIB_ASSERT(comp);
        const auto testArrayMember = [&](char const* _arrayName,
                                         size_t defaultSize,
                                         std::optional<size_t> prefabSize,
                                         std::optional<size_t> overrideSize)
        {
            Ent::Node const* node = comp->root->at(_arrayName);
            ENTLIB_ASSERT(node);
            ENTLIB_ASSERT(node->hasPrefabValue() == prefabSize.has_value());
            ENTLIB_ASSERT(node->hasOverride() == overrideSize.has_value());
            ENTLIB_ASSERT(
                node->getRawSize(Ent::OverrideValueLocation::Default).value() == defaultSize);
            ENTLIB_ASSERT(node->getRawSize(Ent::OverrideValueLocation::Prefab) == prefabSize);
            ENTLIB_ASSERT(node->getRawSize(Ent::OverrideValueLocation::Override) == overrideSize);
        };
        testArrayMember("DefaultValue", 2, std::nullopt, std::nullopt);
        testArrayMember("PrefabValue", 2, 4, std::nullopt);
        testArrayMember("OverridedDefaultValue", 2, std::nullopt, 3);
        testArrayMember("OverridedPrefabValue", 2, 4, 3);
    }
    {
        // Test the readOnly prefab.entity
        std::shared_ptr<Ent::Entity const> ent = entlib.loadEntityReadOnly("prefab.entity");
        testPrefabEntity(ent.get());
    }
    {
        auto const nodeCachesize = entlib.getNodeCache().size();
        auto ent = entlib.loadEntityAsNode("prefab.copy.entity");
        auto const newNodeCachesize = entlib.getNodeCache().size();
        // 3 files more in cache:
        //     "test_prefab_history.entity"
        //     "prefab.copy.entity"
        //     "subentity.entity"
        ENTLIB_ASSERT(newNodeCachesize == nodeCachesize + 3);
        // TEST simple entity refs resolution
        Ent::Node* testEntityRef = ent->at("Components")->mapGet("TestEntityRef")->getUnionData();
        ENTLIB_ASSERT(testEntityRef != nullptr);
        ENTLIB_ASSERT(testEntityRef->at("TestRef")->isSet());
        Ent::EntityRef entityRef = testEntityRef->at("TestRef")->getEntityRef();
        Ent::Node* resolvedEntity = entlib.resolveEntityRef(ent.get(), entityRef);
        ENTLIB_ASSERT(resolvedEntity != nullptr);

        Ent::Node* subScenecomp = ent->at("Components")->mapGet("SubScene")->getUnionData();
        Ent::Node* allSubEntities = subScenecomp->at("Embedded");
        ENTLIB_ASSERT(not allSubEntities->empty());
        Ent::Node* originalEnt = allSubEntities->at(0llu);
        ENTLIB_ASSERT(resolvedEntity == originalEnt);

        auto newSubEnt = allSubEntities->mapInsert("prefab.entity");
        newSubEnt->at("Name")->setString("newSubEnt");
        ENTLIB_ASSERT(entlib.makeEntityRef(*ent, *newSubEnt).entityPath == "newSubEnt");

        auto embedded = ent->at("Components")->mapGet("SubScene")->getUnionData()->at("Embedded");
        auto insertedEnt = embedded->mapInsertInstanceOf("prefab.entity");
        insertedEnt->checkParent(embedded);
    }

    {
        // Test write prefab
        EntityPtr ent = entlib.loadEntity("prefab.copy.entity");

        testPrefabEntity(ent.get());

        // TEST Tuple hasOverride
        Ent::Component* unitTestComponent = ent->addComponent("UnitTestComponent");
        auto* wp = unitTestComponent->root->at("Position");
        ENTLIB_ASSERT(wp->hasOverride() == false);
        ENTLIB_ASSERT(wp->at(0llu)->hasOverride() == false);

        // TEST MaxActivationLevel
        ENTLIB_ASSERT(ent->getMaxActivationLevel() == Ent::ActivationLevel::InWorld);

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);
        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Shamans")); // set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey")); // set

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->size() == 3);

        // TEST default values unchanged
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default

        // TEST changed values
        ENTLIB_ASSERT(
            sysCreat->root->at("Name")->getString() == std::string("Shamane_male")); // set. changed.
        ENTLIB_ASSERT(sysCreat->root->at("Name")->isSet()); // set. changed.

        // TEST simple entity refs resolution
        Ent::Component* testEntityRef = ent->getComponent("TestEntityRef");
        ENTLIB_ASSERT(testEntityRef != nullptr);
        ENTLIB_ASSERT(testEntityRef->root->at("TestRef")->isSet());
        Ent::EntityRef entityRef = testEntityRef->root->at("TestRef")->getEntityRef();
        Ent::Entity* resolvedEntity = ent->resolveEntityRef(entityRef);
        ENTLIB_ASSERT(resolvedEntity != nullptr);

        Ent::SubSceneComponent* subScenecomp = ent->getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(not allSubEntities.empty());
        Ent::Entity& originalEnt = *allSubEntities.front();
        ENTLIB_ASSERT(resolvedEntity == &originalEnt);
    }

    {
        // TEST entity refs
        // file: entity-references-a.entity
        // - A-entity [ref to B: "B"]
        //     - B [ref to A: ".."]
        //
        // file: entity-references.scene
        // - root-scene
        //     - InstanceOfA
        //     - C [ref to B in InstanceOfA: "../InstanceOfA/B"]
        //
        std::unique_ptr<Ent::Scene> scene = entlib.loadScene("entity-references.scene");
        ENTLIB_ASSERT(scene->getObjects().size() == 2);
        Ent::Entity& instanceOfA = *scene->getEntity("InstanceOfA");
        ENTLIB_ASSERT(strcmp(instanceOfA.getName(), "InstanceOfA") == 0);
        Ent::SubSceneComponent* subSceneComp = instanceOfA.getSubSceneComponent();
        ENTLIB_ASSERT(subSceneComp != nullptr);
        ENTLIB_ASSERT(subSceneComp->embedded->getObjects().size() == 1);
        Ent::Entity& B = *subSceneComp->embedded->getEntity("B");
        ENTLIB_ASSERT(strcmp(B.getName(), "B") == 0);
        Ent::Entity& C = *scene->getEntity("C");
        ENTLIB_ASSERT(strcmp(C.getName(), "C") == 0);

        // TEST entity ref creation
        Ent::EntityRef BToInstanceOfAref = B.makeEntityRef(instanceOfA);
        ENTLIB_ASSERT(BToInstanceOfAref.entityPath == "..");
        Ent::EntityRef InstanceOfAToBref = instanceOfA.makeEntityRef(B);
        ENTLIB_ASSERT(InstanceOfAToBref.entityPath == "B");
        Ent::EntityRef CToBref = C.makeEntityRef(B);
        ENTLIB_ASSERT(CToBref.entityPath == "../InstanceOfA/B");
        Ent::EntityRef BToCref = B.makeEntityRef(C);
        ENTLIB_ASSERT(BToCref.entityPath == "../../C");

        // TEST entity ref resolution
        Ent::Entity* resolvedEmptyRef = instanceOfA.resolveEntityRef({});
        ENTLIB_ASSERT(resolvedEmptyRef == nullptr);
        Ent::Entity* resolvedInstanceOfA = B.resolveEntityRef({".."});
        ENTLIB_ASSERT(resolvedInstanceOfA == &instanceOfA);
        Ent::Entity* resolvedB = instanceOfA.resolveEntityRef({"B"});
        ENTLIB_ASSERT(resolvedB == &B);
        Ent::Entity* resolvedBbis = C.resolveEntityRef({"../InstanceOfA/B"});
        ENTLIB_ASSERT(resolvedBbis == &B);
        Ent::Entity* resolvedC = B.resolveEntityRef({"../../C"});
        ENTLIB_ASSERT(resolvedC == &C);

        // TEST entity ref resolution from scenes
        ENTLIB_ASSERT(scene->resolveEntityRef({".."}) == nullptr);
        ENTLIB_ASSERT(scene->resolveEntityRef({"InstanceOfA"}) == &instanceOfA);
        ENTLIB_ASSERT(scene->resolveEntityRef({"InstanceOfA/B"}) == &B);
        ENTLIB_ASSERT(scene->resolveEntityRef({"C"}) == &C);
        ENTLIB_ASSERT(scene->resolveEntityRef({"InstanceOfA/B/../../C"}) == &C);
    }

    auto testInstanceOf = [](Ent::Entity const& ent, bool testIsSet = true, bool testPrefab = true)
    {
        // ActorStates
        Ent::Node const& actorStates = ent.getActorStates();
        actorStates.checkParent(nullptr); // Check the parent of nodes is valid
        auto& actorStatesCopy = actorStates; //NOLINT(performance-unnecessary-copy-initialization)
        actorStatesCopy.checkParent(nullptr); // Check the parent of nodes is valid
        ENTLIB_ASSERT(actorStates.getDataType() == Ent::DataType::array);
        ENTLIB_ASSERT(actorStates.size() == 3);
        Ent::Node const* actorState = actorStates.at(0llu);
        ENTLIB_ASSERT(actorState != nullptr);
        Ent::Node const* climbEdge = actorState->getUnionData();
        ENTLIB_ASSERT(climbEdge->getParentNode()->getParentNode() == actorState);
        ENTLIB_ASSERT(climbEdge != nullptr);
        Ent::Node const* exitRequired = climbEdge->at("ItemEntityRef");
        ENTLIB_ASSERT(exitRequired != nullptr);
        ENTLIB_ASSERT(exitRequired->getEntityRef().entityPath == std::string("tutu"));
        Ent::Node const* dead = actorStates.mapGet("ActorStateDead");
        ENTLIB_ASSERT(dead != nullptr);
        Ent::Node const* deadData = dead->getUnionData();
        ENTLIB_ASSERT(deadData != nullptr);
        Ent::Node const* reviveLife = deadData->at("ReviveLifeSigned");
        ENTLIB_ASSERT(reviveLife != nullptr);
        ENTLIB_ASSERT(reviveLife->getFloat() == 13.);
        Ent::Node const* actorStateHoldingItem = actorStates.mapGet("ActorStateHoldingItem");
        ENTLIB_ASSERT(actorStateHoldingItem != nullptr);
        Ent::Node const* actorStateHoldingItemData = actorStateHoldingItem->getUnionData();
        ENTLIB_ASSERT(actorStateHoldingItemData != nullptr);
        Ent::Node const* itemEntityRef = actorStateHoldingItemData->at("ItemEntityRef");
        ENTLIB_ASSERT(itemEntityRef != nullptr);
        ENTLIB_ASSERT(itemEntityRef->getEntityRef().entityPath == "tutu");

        // Map and Set overridePolicy
        Ent::Component const* pathNodeGD = ent.getComponent("PathNodeGD");
        Ent::Node const* tags = pathNodeGD->root->at("Tags")->at("Tags");
        ENTLIB_ASSERT(tags->getParentNode()->getParentNode() == pathNodeGD->root.get());
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->mapGet("a")->getParentNode()->getParentNode() == tags);
        ENTLIB_ASSERT(tags->mapGet("a") != nullptr);
        ENTLIB_ASSERT(tags->mapGet("b") != nullptr);
        ENTLIB_ASSERT(tags->mapGet("c") != nullptr);
        ENTLIB_ASSERT(tags->mapGet("c")->size() == 3);
        ENTLIB_ASSERT(tags->mapGet("c")->mapGet("1") != nullptr);
        ENTLIB_ASSERT(tags->mapGet("c")->mapGet("2") != nullptr);
        ENTLIB_ASSERT(tags->mapGet("c")->mapGet("3") != nullptr);
        // Test mapGet on map
        auto cValueSet = tags->mapGet("c");
        ENTLIB_ASSERT(cValueSet != nullptr);
        // Test mapGet on set
        ENTLIB_ASSERT(cValueSet->mapGet("1")->getString() == std::string("1"));

        // TEST SubScene (without override)
        Ent::SubSceneComponent const* subScene = ent.getSubSceneComponent();
        ENTLIB_ASSERT(subScene != nullptr);
        Ent::Entity const& subObj = *subScene->embedded->getObjects()[0];
        ENTLIB_ASSERT(subObj.getName() == std::string("EP1-Spout_LINK_001"));
        if (testIsSet)
        {
            ENTLIB_ASSERT(not subObj.getNameValue().isSet());
            ENTLIB_ASSERT(not subObj.hasOverride());
        }
        Ent::Component const* netLink = subObj.getComponent("NetworkLink");
        ENTLIB_ASSERT(netLink != nullptr);
        ENTLIB_ASSERT(netLink->root->at("Source")->getString() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->root->at("Target")->getString() == std::string(".EP1-crook_"));
        if (testIsSet)
        {
            ENTLIB_ASSERT(netLink->root->at("Source")->isSet() == false);
            ENTLIB_ASSERT(netLink->root->at("Target")->isSet() == false);
        }
        Ent::Component const* trans = subObj.getComponent("TransformGD");
        ENTLIB_ASSERT(trans->root->at("Position")->at(0llu)->getFloat() == 0.0);

        // "InstanceOf" in sub entitites
        auto& entityWithInstanceOf = *subScene->embedded->getEntity(R"(EntityWithInstanceOf)");
        ENTLIB_ASSERT(entityWithInstanceOf.getName() == std::string("EntityWithInstanceOf"));
        ENTLIB_ASSERT(entityWithInstanceOf.getInstanceOf() == std::string("subentity2.entity"));
        auto* networkLink = entityWithInstanceOf.getComponent("NetworkLink");
        ENTLIB_ASSERT(networkLink->root->at("Source")->getString() == std::string("instance"));
        ENTLIB_ASSERT(networkLink->root->at("Target")->getString() == std::string("subentity2"));
        ENTLIB_ASSERT(networkLink->root->at("ThumbnailMesh")->getString() == std::string());

        // Test instanciation of a prefab Node
        Ent::Component const* stickToTerrain = ent.getComponent("StickToTerrain");
        if (testPrefab)
        {
            ENTLIB_ASSERT(stickToTerrain->root->getInstanceOf() != nullptr);
            ENTLIB_ASSERT(
                stickToTerrain->root->getInstanceOf() == std::string("test.StickToTerrain.node"));
        }
        ENTLIB_ASSERT(fabs(stickToTerrain->root->at("NormalRatio")->getFloat() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain->root->at("ZOffset")->isSet() == false);
        ENTLIB_ASSERT(stickToTerrain->root->at("ZOffset")->isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain->root->at("ZOffset")->getFloat() - 10.) < 0.0001);

        // Test Node's InstanceOf
        Ent::Component const* seedPatch = ent.getComponent("SeedPatch");
        ENTLIB_ASSERT(seedPatch->root->at("NoiseSizeX")->isDefault());
        ENTLIB_ASSERT(seedPatch->root->at("NoiseSizeY")->getFloat() == 3.);
        ENTLIB_ASSERT(not seedPatch->root->at("NoiseOffsetX")->isSet());
        ENTLIB_ASSERT(seedPatch->root->at("NoiseOffsetY")->getFloat() == 3.);
    };

    {
        // Test applyToPrefab

        // Prepare data
        EntityPtr ent = entlib.loadEntity("instance.entity");
        auto entJson = ent->saveEntity();
        entJson["InstanceOf"] = "prefab_updated.entity";
        {
            std::ofstream outEnt("instance_applied.entity");
            outEnt << entJson.dump(4);
        }
        std::filesystem::copy_file(
            "prefab.entity", "prefab_updated.entity", copy_options::overwrite_existing);

        // Do the applyToPrefab
        ent = entlib.loadEntity("instance_applied.entity");
        ent->applyToPrefab();
        Ent::Node const& actorStates = ent->getActorStates();
        actorStates.checkParent(nullptr); // Check the parent of nodes is valid
        entlib.saveEntity(*ent, "instance_applied.entity");
        actorStates.checkParent(nullptr); // Check the parent of nodes is valid
        EntityPtr prefab = entlib.loadEntity("prefab_updated.entity");
        actorStates.checkParent(nullptr); // Check the parent of nodes is valid

        // Test result
        testInstanceOf(*prefab, false);
        actorStates.checkParent(nullptr); // Check the parent of nodes is valid
        testInstanceOf(*ent, false);
        ENTLIB_ASSERT(ent->hasOverride()); // Because applyToPrefab set the old name

        ent = entlib.loadEntity("instance_applied.entity");
        testInstanceOf(*ent, false);
        ENTLIB_ASSERT(ent->hasOverride()); // Because applyToPrefab set the old name
    }

    {
        // Test read instance of
        EntityPtr ent = entlib.loadEntity("instance.entity");
        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        ENTLIB_ASSERT(ent->getColorValue().hasOverride());

        // TEST read overrided value
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        ENTLIB_ASSERT(
            sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey")); // Inherited
        ENTLIB_ASSERT(sysCreat->root->at("Life")->getFloat() == 1000.); // Inherited

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST read default value
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // Inherited (from default)
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default

        // TEST read overrided in array
        ENTLIB_ASSERT(
            sysCreat->root->at("ScriptList")->at(1)->getString() == std::string("b2")); // Overrided
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->at(1)->isSet()); // Overrided
        // TEST read Not overrided in array
        ENTLIB_ASSERT(
            sysCreat->root->at("ScriptList")->at(2)->getString() == std::string("c1")); // not overrided
        ENTLIB_ASSERT(not sysCreat->root->at("ScriptList")->at(2)->isSet()); // Not overrided

        // Programatically unset
        sysCreat->root->at("ScriptList")->at(1)->unset();
        // Programatically set
        sysCreat->root->at("ScriptList")->at(2)->setString("c2");

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->size() == 3);

        // TEST Extand array
        sysCreat->root->at("ScriptList")->push()->setString("d2");
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->size() == 4);

        // TEST SubScene (without override)
        testInstanceOf(*ent);

        Ent::Component* testSetOfObject = ent->getComponent("TestSetOfObject");
        {
            auto* setOfObject = testSetOfObject->root->at("SetOfObject");

            // Test hasOverride
            ENTLIB_ASSERT(setOfObject->mapGet("C")->hasOverride() == false); // Already in prefab
            ENTLIB_ASSERT(setOfObject->mapGet("A")->hasOverride()); // new in instance

            // Test remove object in set
            ENTLIB_ASSERT(setOfObject->size() == 6);
            ENTLIB_ASSERT(setOfObject->mapErase("B"));
            ENTLIB_ASSERT(setOfObject->mapGet("B") == nullptr);
            ENTLIB_ASSERT(setOfObject->mapErase("C"));
            ENTLIB_ASSERT(setOfObject->mapGet("C") == nullptr);
            ENTLIB_ASSERT(setOfObject->size() == 4);

            // Test override object in set (especially override name)
            ENTLIB_ASSERT(setOfObject->mapGet("E") != nullptr);
            ENTLIB_ASSERT(setOfObject->mapGet("E2") == nullptr);
            ENTLIB_ASSERT(setOfObject->mapGet("E")->at("Value")->getString() == std::string("e2"));
            ENTLIB_ASSERT(setOfObject->mapGet("E")->at("Name")->getString() == std::string("E"));
            ENTLIB_ASSERT(setOfObject->mapGet("F") != nullptr);
            ENTLIB_ASSERT(setOfObject->mapGet("F")->at("Value")->getString() == std::string("f"));
            ENTLIB_ASSERT(setOfObject->mapGet("F")->at("Name")->getString() == std::string("F"));
            // Test resetInstanceOf with overriden key
            setOfObject->mapGet("F")->resetInstanceOf("ObjectInSet.node");
            ENTLIB_ASSERT(setOfObject->mapGet("F")->at("Value")->getString() == std::string("e2"));
            ENTLIB_ASSERT(setOfObject->mapGet("F")->at("Name")->getString() == std::string("F"));

            // Test insert the __removed__ element get back the prefab values
            // insert => makeInstanceOf => __remove__ => insert
            //          => restore values since we dont know how to reset an element when saving
            ENTLIB_ASSERT(setOfObject->mapGet("G") == nullptr);
            ENTLIB_ASSERT(setOfObject->mapInsert("G"));
            ENTLIB_ASSERT(setOfObject->mapGet("G")->hasOverride() == true);
            ENTLIB_ASSERT(setOfObject->mapGet("G")->at("Value")->getString() == std::string("g"));
            setOfObject->mapErase("G");
        }

        // Test remove entity
        auto subsceneCmp = ent->getSubSceneComponent();
        ENTLIB_ASSERT(subsceneCmp->embedded->getObjects().size() == PrefabSubEntityCount);
        subsceneCmp->embedded->removeEntity("TestRemove");
        ENTLIB_ASSERT(subsceneCmp->embedded->getObjects().size() == PrefabSubEntityCount - 1);

        // Test rename Entity
        // - Possible
        auto uglyent =
            subsceneCmp->embedded->addEntity(std::make_unique<Ent::Entity>(entlib, "UglyName"));
        ENTLIB_ASSERT(
            subsceneCmp->embedded->getEntity("UglyName")->getName() == std::string("UglyName"));
        uglyent->setName("PrettyName");
        ENTLIB_ASSERT(
            subsceneCmp->embedded->getEntity("PrettyName")->getName() == std::string("PrettyName"));
        subsceneCmp->embedded->renameEntity("PrettyName", "PrettiestName");
        ENTLIB_ASSERT(
            subsceneCmp->embedded->getEntity("PrettiestName")->getName()
            == std::string("PrettiestName"));
        // - Not possible
        ENTLIB_CHECK_EXCEPTION(
            subsceneCmp->embedded->renameEntity("EntityWithInstanceOf", "EntityWithInstanceOf2"),
            Ent::CantRename);

        // Test rename object in set
        // - Possible
        ENTLIB_ASSERT(
            testSetOfObject->root->at("SetOfObject")->mapGet("A")->at("Value")->getString()
            == std::string("a"));
        testSetOfObject->root->at("SetOfObject")->mapRename("A", "A3");
        testSetOfObject->root->at("SetOfObject")->mapRename("A3", "A2");
        ENTLIB_ASSERT(
            testSetOfObject->root->at("SetOfObject")->mapGet("A2")->at("Value")->getString()
            == std::string("a"));
        ENTLIB_ASSERT(testSetOfObject->root->at("SetOfObject")->mapGet("A") == nullptr);
        // - Not possible
        ENTLIB_ASSERT(
            testSetOfObject->root->at("SetOfObject")->mapGet("D")->at("Value")->getString()
            == std::string("d"));
        // TODO : decomment!!
        ENTLIB_CHECK_EXCEPTION(
            testSetOfObject->root->at("SetOfObject")->mapRename("D", "D2"), Ent::CantRename);

        // ****************************** Test hasASuper ******************************************
        // *************** ENTITY ***************
        auto subscene = ent->getSubSceneComponent();
        // new entity : Since the entityname is mandatory, it is always overriden when new
        auto newEnt = std::make_unique<Ent::Entity>(entlib, "Entity");
        ENTLIB_ASSERT(newEnt->hasOverride() == true);
        subscene->embedded->addEntity(std::move(newEnt));
        // entity with override
        auto entWithOverride = subscene->embedded->getEntity("TestSaveEntWithOverride");
        ENTLIB_ASSERT(entWithOverride != nullptr);
        auto networkLink = entWithOverride->getComponent("NetworkLink");
        ENTLIB_ASSERT(networkLink != nullptr);
        networkLink->root->at("ThumbnailMesh")->setString("DefaultLinkVisual.wbm");
        ENTLIB_ASSERT(entWithOverride->hasOverride());
        // entity with instanceOf overriden
        auto entWithoutOverride =
            subscene->embedded->getEntity(R"(EntityWithInstanceOfButNoOverride)");
        entWithoutOverride->resetInstanceOf("subentity2.entity");
        ENTLIB_ASSERT(entWithoutOverride->getInstanceOf() == std::string("subentity2.entity"));
        ENTLIB_ASSERT(entWithoutOverride->hasOverride());
        // *************** COMPONENT ***************
        // new Component
        auto comp = ent->addComponent("AnimationEventsGeneratorGD");
        ENTLIB_ASSERT(ent->getComponent("AnimationEventsGeneratorGD") != nullptr);
        ENTLIB_ASSERT(comp->hasOverride()); // A new item in an array in always override
        // Component with override
        ent->getComponent("VoxelSimulationGD")->root->at("LossBySecond")->setFloat(36.);
        ENTLIB_ASSERT(ent->getComponent("VoxelSimulationGD") != nullptr);
        ENTLIB_ASSERT(ent->getComponent("VoxelSimulationGD")->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = ent->getComponent("CharacterControllerGD");
        compWithInstOf->root->resetInstanceOf("test.CharacterControllerGD.node");
        ENTLIB_ASSERT(
            compWithInstOf->root->getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        ENTLIB_ASSERT(compWithInstOf->hasOverride());
        // *************** NODE ***************
        // new Node
        auto setOfObject = ent->getComponent("TestSetOfObject");
        ENTLIB_ASSERT(setOfObject);
        auto mapTest = setOfObject->root->at("MapOfObject");
        mapTest->mapInsert("NewNode");
        ENTLIB_ASSERT(mapTest->mapGet("NewNode") != nullptr);
        ENTLIB_ASSERT(
            mapTest->mapGet("NewNode")->hasOverride()); // Newly inserted noeds are always overriden
        // Node with override
        mapTest->mapGet("OldNode1")->at("Value")->setString("overriden");
        ENTLIB_ASSERT(
            mapTest->mapGet("OldNode1")->at("Value")->getString() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest->mapGet("OldNode1")->hasOverride());
        // Node with instanceOf overriden
        mapTest->mapGet("OldNode2")->resetInstanceOf("OldNode2.MapOfObject.node");
        auto val = mapTest->mapGet("OldNode2");
        ENTLIB_ASSERT(val->at("Value")->getString() == std::string("overriden"));
        ENTLIB_ASSERT(val->hasOverride());

        // Test mapInsert in map
        {
            mapTest = setOfObject->root->at("MapOfObject");
            auto newNode2 = mapTest->mapInsert("NewNode2");
            ENTLIB_ASSERT(newNode2->getDataType() == Ent::DataType::object);
        }

        sysCreat->root->at("BehaviorState")->setString("Overrided");
        entlib.saveEntity(*ent, "instance.copy.entity");

        {
            auto instance3 = ent->makeInstanceOf();

            Ent::Component* testSetOfObject3 = instance3->getComponent("TestSetOfObject");
            auto* setOfObject3 = testSetOfObject3->root->at("SetOfObject");

            auto mapTest2 = testSetOfObject3->root->at("MapOfObject");
            ENTLIB_ASSERT(mapTest2->mapInsert("Should_not_appear_in_diff"));
            ENTLIB_ASSERT(mapTest2->mapErase("Should_not_appear_in_diff"));

            // Test insert an element in an instance of the __removed__ one, do not resore the old values
            // insert => makeInstanceOf => __remove__ => makeInstanceOf => insert
            //          => do not restore values
            ENTLIB_ASSERT(setOfObject3->mapGet("G") == nullptr);
            ENTLIB_ASSERT(setOfObject3->mapInsert("G"));
            ENTLIB_ASSERT(setOfObject3->mapGet("G")->at("Value")->getString() == std::string());
            entlib.saveEntity(*instance3, "instance3.entity");
        }
    }
    {
        EntityPtr ent = entlib.loadEntity("instance3.entity");
        Ent::Component* testSetOfObject3 = ent->getComponent("TestSetOfObject");
        auto* setOfObject3 = testSetOfObject3->root->at("SetOfObject");

        // Test insert an element in an instance of the __removed__ one, do not resore the old values
        // insert => makeInstanceOf => __remove__ => makeInstanceOf => insert
        //          => do not restore values
        ENTLIB_ASSERT(setOfObject3->mapGet("G")->at("Value")->getString() == std::string());
    }

    auto test_erase = [](Ent::Entity* ent)
    {
        Ent::Node& actorStates = ent->getActorStates();
        Ent::Component* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node* tags = pathNodeGD->root->at("Tags")->at("Tags");

        // Test erase in map (+save/load)
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->mapGet("c") == nullptr);

        // Test insert in map (+save/load)
        auto e = tags->mapGet("A");
        ENTLIB_ASSERT(e != nullptr);
        ENTLIB_ASSERT(e->getDataType() == Ent::DataType::array);

        // Test erase in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.mapGet("EntityStatePlayer") == nullptr);

        // Test insert in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.mapGet("ActorStateAlive") != nullptr);

        // Test remove component
        ENTLIB_ASSERT(ent->getComponent("TransformGD") == nullptr);
        ENTLIB_ASSERT(ent->getSubSceneComponent() == nullptr);
    };

    {
        EntityPtr ent = entlib.loadEntity("instance.entity");
        // Test erase in union_set
        Ent::Node& actorStates = ent->getActorStates();
        ENTLIB_ASSERT(actorStates.mapGet("EntityStatePlayer") != nullptr);
        ENTLIB_ASSERT(actorStates.mapErase("EntityStatePlayer"));
        ENTLIB_ASSERT(actorStates.mapGet("EntityStatePlayer") == nullptr);

        // Test insert in union_set
        ENTLIB_ASSERT(actorStates.mapInsert("ActorStateAlive") != nullptr);

        // Test erase in map
        Ent::Component* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node* tags = pathNodeGD->root->at("Tags")->at("Tags");
        ENTLIB_ASSERT(tags->mapGet("c") != nullptr);
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->mapErase("c"));
        ENTLIB_ASSERT(tags->size() == 2);
        ENTLIB_ASSERT(tags->mapGet("c") == nullptr);
        ENTLIB_ASSERT(not tags->mapErase(2));

        // Test insert in map
        ENTLIB_ASSERT(tags->mapGet("A") == nullptr);
        ENTLIB_ASSERT(tags->mapInsert("A") != nullptr);
        auto items = tags->getItems();
        ENTLIB_ASSERT(items.front()->at(0llu)->getString() == std::string("A")); // "A" should be first

        // Test erase in Components
        ENTLIB_ASSERT(ent->getComponent("TransformGD") != nullptr);
        ent->removeComponent("TransformGD");
        ENTLIB_ASSERT(ent->getComponent("TransformGD") == nullptr);

        ENTLIB_ASSERT(ent->getComponent("SubScene") == nullptr);
        ENTLIB_ASSERT(ent->getSubSceneComponent() != nullptr);
        ent->removeSubSceneComponent();
        ENTLIB_ASSERT(ent->getSubSceneComponent() == nullptr);

        test_erase(ent.get());

        entlib.saveEntity(*ent, "test_erase.entity");
    }

    {
        EntityPtr ent = entlib.loadEntity("test_erase.entity");
        test_erase(ent.get());
    }
    {
        EntityPtr ent = entlib.makeInstanceOf("test_erase.entity");
        test_erase(ent.get());
        auto json = ent->getActorStates().toJson(Ent::OverrideValueSource::OverrideOrPrefab, true);
        ENTLIB_ASSERT(json.size() == 3);
        for (auto&& actState : json)
        {
            ENTLIB_ASSERT(actState["className"] != "EntityStatePlayer");
        }
    }
    {
        EntityPtr ent = entlib.loadEntity("instance2.entity");
        testInstanceOf(*ent, true, false);
    }
    auto testInstanceOverrideSubscene = [](Ent::Entity const& ent)
    {
        // TEST SubScene (with override)
        Ent::SubSceneComponent const* subScene = ent.getSubSceneComponent();
        ENTLIB_ASSERT(subScene != nullptr);
        auto const* subObj = subScene->embedded->getEntity("EP1-Spout_LINK_001");
        ENTLIB_ASSERT(subObj->getName() == std::string("EP1-Spout_LINK_001"));

        // Test an overrided Component
        Ent::Component const* netLink = subObj->getComponent("NetworkLink");
        ENTLIB_ASSERT(netLink != nullptr);
        ENTLIB_ASSERT(netLink->root->at("Source")->getString() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->root->at("Source")->isSet() == false);
        ENTLIB_ASSERT(netLink->root->at("Target")->getString() == std::string(".EP1-crook_2"));
        ENTLIB_ASSERT(netLink->root->at("Target")->isSet());

        // Test a not overrided Component
        Ent::Component const* trans = subObj->getComponent("TransformGD");
        ENTLIB_ASSERT(trans != nullptr);
        ENTLIB_ASSERT(trans->root->at("Position")->at(0llu)->getFloat() == 0.0);
    };
    {
        EntityPtr ent = entlib.loadEntity("instance_override_subscene.entity");
        testInstanceOverrideSubscene(*ent);
        entlib.saveEntity(*ent, "instance_override_subscene.copy.entity");
    }
    {
        EntityPtr ent = entlib.loadEntity("instance_override_subscene.copy."
                                          "entity");
        testInstanceOverrideSubscene(*ent);
    }
    {
        // Test write instance of
        EntityPtr ent = entlib.loadEntity("instance.copy.entity");
        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        // Test remove object in set
        Ent::Component* testSetOfObject = ent->getComponent("TestSetOfObject");
        auto* setOfObject = testSetOfObject->root->at("SetOfObject");
        ENTLIB_ASSERT(setOfObject->mapGet("B") == nullptr);
        ENTLIB_ASSERT(setOfObject->mapGet("C") == nullptr);
        ENTLIB_ASSERT(setOfObject->size() == 4);

        // Test override object in set (especially override name)
        ENTLIB_ASSERT(setOfObject->mapGet("E") != nullptr);
        ENTLIB_ASSERT(setOfObject->mapGet("E2") == nullptr);
        ENTLIB_ASSERT(setOfObject->mapGet("E")->at("Value")->getString() == std::string("e2"));
        ENTLIB_ASSERT(setOfObject->mapGet("E")->at("Name")->getString() == std::string("E"));

        // Test insert the __removed__ element get back the prefab values
        // insert => makeInstanceOf => __remove__ => insert
        //          => restore values since we dont know how to reset an element when saving
        ENTLIB_ASSERT(setOfObject->mapGet("G") == nullptr);
        ENTLIB_ASSERT(setOfObject->mapInsert("G"));
        ENTLIB_ASSERT(setOfObject->mapGet("G")->at("Value")->getString() == std::string("g"));

        // Test remove entity
        auto subsceneCmp = ent->getSubSceneComponent();
        // Removed : TestRemove. Added : PrettiestName, Entity
        ENTLIB_ASSERT(subsceneCmp->embedded->getObjects().size() == PrefabSubEntityCount + 1);

        // Test rename Entity
        ENTLIB_ASSERT(
            subsceneCmp->embedded->getEntity("PrettiestName")->getName()
            == std::string("PrettiestName"));

        // Test rename object in set
        ENTLIB_ASSERT(
            testSetOfObject->root->at("SetOfObject")->mapGet("A2")->at("Value")->getString()
            == std::string("a"));
        ENTLIB_ASSERT(testSetOfObject->root->at("SetOfObject")->mapGet("A") == nullptr);

        // ****************************** Test hasASuper ******************************************
        // *************** ENTITY ***************
        auto subscene = ent->getSubSceneComponent();
        // new entity
        auto ent2 = subscene->embedded->getEntity("Entity");
        ENTLIB_ASSERT(ent2 != nullptr);
        ENTLIB_ASSERT(ent2->hasOverride()); // Name is always overriden since it is alway declared
        // entity with override
        ent2 = subscene->embedded->getEntity("TestSaveEntWithOverride");
        ENTLIB_ASSERT(ent2 != nullptr);
        ENTLIB_ASSERT(ent2->hasOverride());
        // entity with instanceOf overriden
        ent2 = subscene->embedded->getEntity("EntityWithInstanceOfButNoOverride");
        ENTLIB_ASSERT(ent2 != nullptr);
        ENTLIB_ASSERT(ent2->getInstanceOf() == std::string("subentity2.entity"));
        ENTLIB_ASSERT(ent2->hasOverride());

        // *************** COMPONENT ***************
        // new Component (A new component is override true)
        ENTLIB_ASSERT(ent->getComponent("AnimationEventsGeneratorGD") != nullptr);
        ENTLIB_ASSERT(ent->getComponent("AnimationEventsGeneratorGD")->hasOverride());
        // Component with override
        ENTLIB_ASSERT(ent->getComponent("VoxelSimulationGD") != nullptr);
        ENTLIB_ASSERT(
            ent->getComponent("VoxelSimulationGD")->root->at("LossBySecond")->getFloat() == 36.);
        ENTLIB_ASSERT(ent->getComponent("VoxelSimulationGD")->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = ent->getComponent("CharacterControllerGD");
        ENTLIB_ASSERT(
            compWithInstOf->root->getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        ENTLIB_ASSERT(compWithInstOf->hasOverride());
        // *************** NODE ***************
        // new Node
        auto pathNodeGD = ent->getComponent("TestSetOfObject");
        auto mapTest = pathNodeGD->root->at("MapOfObject");
        ENTLIB_ASSERT(mapTest->mapGet("NewNode") != nullptr);
        // Newly inserted Nodes are overriden
        ENTLIB_ASSERT(mapTest->mapGet("NewNode")->hasOverride());
        // Node with override
        ENTLIB_ASSERT(
            mapTest->mapGet("OldNode1")->at("Value")->getString() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest->mapGet("OldNode1")->hasOverride());
        // Node with instanceOf overriden
        ENTLIB_ASSERT(
            mapTest->mapGet("OldNode2")->at("Value")->getString() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest->mapGet("OldNode2")->hasOverride());

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST read overrided value
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        ENTLIB_ASSERT(
            sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey")); // Inherited
        ENTLIB_ASSERT(sysCreat->root->at("Life")->getFloat() == 1000.); // Inherited

        // TEST read default value
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // Inherited (from default)
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default

        // TEST read programatically overrided in array
        ENTLIB_ASSERT(
            sysCreat->root->at("ScriptList")->at(1)->getString()
            == std::string("b1")); // No more overrided
        ENTLIB_ASSERT(not sysCreat->root->at("ScriptList")->at(1)->isSet()); // No more overrided
        // TEST read programatically unset in array
        ENTLIB_ASSERT(
            sysCreat->root->at("ScriptList")->at(2)->getString() == std::string("c2")); // Overrided
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->at(2)->isSet()); // Overrided

        // TEST read programatically extand array
        ENTLIB_ASSERT(
            sysCreat->root->at("ScriptList")->at(3)->getString() == std::string("d2")); // Overrided
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->at(3)->isSet()); // Overrided

        // TEST read extanded array
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->size() == 4);

        // TEST override value from code
        ENTLIB_ASSERT(
            sysCreat->root->at("BehaviorState")->getString()
            == std::string("Overrided")); // set. changed.
        ENTLIB_ASSERT(sysCreat->root->at("BehaviorState")->isSet()); // set. changed.

        testInstanceOf(*ent);

        entlib.saveEntity(*ent, "instance.copy.entity");
    }

    {
        // Test create detached
        EntityPtr ent = entlib.loadEntity("instance.entity");
        EntityPtr detached = ent->detachEntityFromPrefab();

        ENTLIB_ASSERT(detached->getColorValue().hasOverride());

        Ent::Component* sysCreat = detached->getComponent("SystemicCreature");

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(not heightObj->root->at("Subdivision")->hasDefaultValue()); // Prefab has value
        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->hasDefaultValue()); // default
        ENTLIB_ASSERT(sysCreat->root->at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Name")->isSet()); // default

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Plouf")); // set
        ENTLIB_ASSERT(not sysCreat->root->at("Faction")->hasDefaultValue()); // is set in instance
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->isSet()); // is set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->isSet()); // is set

        entlib.saveEntity(*detached, "instance.detached.entity");
    }
    {
        // Test read detached
        EntityPtr ent = entlib.loadEntity("instance.detached.entity");

        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default
        ENTLIB_ASSERT(sysCreat->root->at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Name")->isSet()); // default

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Plouf")); // set
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->isSet()); // is set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->isSet()); // is set
    }

    {
        // Test makeInstanceOf
        EntityPtr instanceOf = entlib.makeInstanceOf("prefab.entity");

        // Test instanciation of a prefab Node
        Ent::Component* stickToTerrain = instanceOf->addComponent("StickToTerrain");
        ENTLIB_CHECK_EXCEPTION(
            stickToTerrain->root->resetInstanceOf("C:/test.StickToTerrain.node"), std::runtime_error);
        stickToTerrain->root->resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain->root->resetInstanceOf(
            (current_path() / "test.StickToTerrain.node").generic_u8string().c_str());
        ENTLIB_ASSERT(stickToTerrain->root->getInstanceOf() != nullptr);
        stickToTerrain->root->at("NormalRatio")->setFloat(0.6);
        stickToTerrain->root->at("precisionRadius")->setFloat(0.6e-15);

        ENTLIB_ASSERT(fabs(stickToTerrain->root->at("NormalRatio")->getFloat() - 0.6) < 0.0001);
        ENTLIB_ASSERT(
            fabs(stickToTerrain->root->at("precisionRadius")->getFloat() - 0.6e-15) < 0.0000001);
        ENTLIB_ASSERT(stickToTerrain->root->at("ZOffset")->isSet() == false);
        ENTLIB_ASSERT(stickToTerrain->root->at("ZOffset")->isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain->root->at("ZOffset")->getFloat() - 10.) < 0.0001);

        ENTLIB_ASSERT(instanceOf->getComponent("NetworkNode") != nullptr);
        instanceOf->getComponent("TransformGD")->root->getFieldNames();
        entlib.saveEntity(*instanceOf, "instance.create.entity");
    }
    auto testCreateInstanceOf = [&entlib](char const* _instancePath)
    {
        // Test read instance of
        EntityPtr ent = entlib.loadEntity(_instancePath);

        ent->getComponent("TransformGD")->root->getFieldNames();

        // Test instanciation of a prefab Node
        Ent::Component const* stickToTerrain = ent->getComponent("StickToTerrain");
        ENTLIB_ASSERT(stickToTerrain->root->getInstanceOf() != nullptr);
        ENTLIB_ASSERT(fabs(stickToTerrain->root->at("NormalRatio")->getFloat() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain->root->at("ZOffset")->isSet() == false);
        ENTLIB_ASSERT(stickToTerrain->root->at("ZOffset")->isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain->root->at("ZOffset")->getFloat() - 10.) < 0.0001);

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root->at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root->at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root->at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // Test read prefab
        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root->at("Faction")->getString() == std::string("Shamans"));
        ENTLIB_ASSERT(not sysCreat->root->at("Faction")->isSet()); // Not overrided
        ENTLIB_ASSERT(sysCreat->root->at("Inventory")->getString() == std::string("KaiWOLgrey"));
        ENTLIB_ASSERT(not sysCreat->root->at("Inventory")->isSet()); // Not overrided

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->isSet()); // Arrays are always set
        ENTLIB_ASSERT(sysCreat->root->at("ScriptList")->size() == 3);

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root->at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Burried")->isSet()); // default
        ENTLIB_ASSERT(sysCreat->root->at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root->at("Name")->isSet()); // default
    };
    testCreateInstanceOf("instance.create.entity");
    {
        // Test resetInstanceOf
        Ent::Entity instanceOf(entlib, "TestResetInstanceOf");
        instanceOf.resetInstanceOf("prefab.entity");
        ENTLIB_ASSERT(instanceOf.getComponent("NetworkNode") != nullptr);
        instanceOf.getComponent("TransformGD")->root->getFieldNames();

        // Test instanciation of a prefab Node
        Ent::Component* stickToTerrain = instanceOf.addComponent("StickToTerrain");
        stickToTerrain->root->resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain->root->at("NormalRatio")->setFloat(0.6);

        entlib.saveEntity(instanceOf, "setInstanceOf.entity");
    }
    testCreateInstanceOf("setInstanceOf.entity");

    // ******************************** Test iteration of schema **********************************
    if (doDisplaySubSchema)
    {
        for (auto&& [name, sub] : entlib.schema.components)
        {
            displaySubSchema(name, *sub, {});
        }
    }

    // ******************* Test load/save complex entity pinetreec50cmh5mbasic ********************
    {
        EntityPtr ent = entlib.loadEntity("pinetreec50cmh5mbasic.entity");
        entlib.saveEntity(*ent, "pinetreec50cmh5mbasic.copy.entity");
        EntityPtr copyEnt = entlib.loadEntity("pinetreec50cmh5mbasic.copy."
                                              "entity");

        // TEST keeping empty component after entity save
        ENTLIB_ASSERT(copyEnt->getComponent("EventHandlerGD") != nullptr);
    }

    // ******************* Test the override of an entity in a SubScene ***************************
    auto testOverrideSubEntity = [](Ent::Entity const& ent)
    {
        Ent::SubSceneComponent const* subScenecomp = ent.getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount);
        ENTLIB_ASSERT(subScenecomp->embedded->getEntity("EP1-Spout_LINK_001")->getColor()[0] == 42);
    };
    {
        EntityPtr ent = entlib.loadEntity("instance_override_subentity.entity");
        testOverrideSubEntity(*ent);
        entlib.saveEntity(*ent, "instance_override_subentity.copy.entity");
        EntityPtr copyEnt = entlib.loadEntity("instance_override_subentity.copy."
                                              "entity");
        testOverrideSubEntity(*copyEnt);
    }

    // ******************* Test the add of an entity in a SubScene *****************************
    auto testAddSubEntity = [](Ent::Entity const& ent)
    {
        Ent::SubSceneComponent const* subScenecomp = ent.getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount + 1);
        auto* ent0 = subScenecomp->embedded->getEntity("EP1-Spout_LINK_001");
        auto* ent1 = subScenecomp->embedded->getEntity("EP1-Spout_LINK_001_added");
        ENTLIB_ASSERT(ent0->getName() == std::string("EP1-Spout_LINK_001"));
        auto red = ent0->getColor()[0];
        ENTLIB_ASSERT(not ent0->hasOverride());
        ENTLIB_ASSERT(red == 255);
        ENTLIB_ASSERT(not ent0->canBeRenamed());
        ENTLIB_ASSERT(ent1->getName() == std::string("EP1-Spout_LINK_001_added"));
        ENTLIB_ASSERT(ent1->getColor()[0] == 44);
        ENTLIB_ASSERT(ent1->canBeRenamed());
    };
    {
        EntityPtr ent = entlib.loadEntity("instance_add_subentity.entity");
        testAddSubEntity(*ent);
        entlib.saveEntity(*ent, "instance_add_subentity.copy.entity");
        EntityPtr copyEnt = entlib.loadEntity("instance_add_subentity.copy."
                                              "entity");
        testAddSubEntity(*copyEnt);
    }
    {
        // Test access subscene override
        EntityPtr ent = entlib.makeInstanceOf("entity-subscene.entity");
        auto subs = ent->getSubSceneComponent();

        ENTLIB_ASSERT(ent->hasOverride()); // makeInstanceOf does override the instanceOf
        ENTLIB_ASSERT(not empty(subs->embedded->getObjects()));

        subs->embedded->getEntity("wolf_skeleton_lush")
            ->addComponent("ActorGD")
            ->root->at("InSpiritWorld")
            ->setBool(true);
        entlib.saveEntity(*ent, "entity-subscene-override-saved.entity");

        EntityPtr ovrdEntt = entlib.loadEntity("entity-subscene-override-saved.entity");
        auto ovrdSubs = ovrdEntt->getSubSceneComponent();

        //Test that we properly still have access to the prefab subscene entities
        ENTLIB_ASSERT(not empty(ovrdSubs->embedded->getObjects()));
    }

    {
        auto ent = entlib.loadEntity(R"(Creature/my_creature_level2.entity)");
        auto subscene = ent->getSubSceneComponent()
                            ->embedded->getEntity(0llu)
                            ->getSubSceneComponent()
                            ->embedded->getObjects();
        ENTLIB_ASSERT(subscene.size() == 1);
        ENTLIB_ASSERT(strcmp(subscene.front()->getName(), "default_level2") == 0);
    }

    // ******************* Test twice the same key in map *************************************
    {
        ENTLIB_CHECK_EXCEPTION(entlib.loadEntity("key_double.entity"), Ent::InvalidJsonData);
    }

    // ******************* Test the EntLibException ***********************************************
    {
        bool exceptionThrown = false;
        try
        {
            entlib.loadScene("scene_with_invalid_entity.scene");
        }
        catch (std::runtime_error& ex)
        {
            exceptionThrown = true;
            char const* what = ex.what();
            ENTLIB_ASSERT(strstr(what, R"("this_entity_doesnt_exist.entity")") != nullptr);
            ENTLIB_ASSERT(strstr(what, R"("scene_with_invalid_entity.scene")") != nullptr);
        }
        ENTLIB_ASSERT(exceptionThrown);
    }

    // ******************* Test default color *****************************************************
    {
        EntityPtr ent = std::make_unique<Ent::Entity>(entlib, "TestDefaultColor");
        ENTLIB_ASSERT(ent->getColor() == (std::array<double, 4>{1., 1., 1., 1.}));
    }
    // ********************************** Test load/save scene ************************************
    entlib.rawdataPath = "X:/RawData";

    ENTLIB_LOG("Loading SceneWild.scene...");
    // auto scene = entlib.loadScene("X:/RawData/01_World/Wild/scenewild/editor/SceneWild.scene");
    entlib.validationEnabled = false;
    auto scene = entlib.loadScene("20_scene/personal/simont/vfxGym/ScenevfxGym.scene");
    ENTLIB_LOG("Done");

    if (doDisplayScene)
    {
        using namespace Ent;
        printfmt("Scene Loaded\n");
        printfmt("Entity count : %zu\n", scene->getObjects().size());

        for (auto&& ent : scene->getObjects())
        {
            printfmt("  Name \"%s\"\n", ent->getName());

            for (char const* type : ent->getComponentTypes())
            {
                printfmt("    Type \"%s\"\n", type);
                Ent::Node const& root = *ent->getComponent(type)->root;
                printNode("", root, "      ");
            }
        }
    }

    Ent::Component* heightObj = scene->getObjects().front()->addComponent("HeightObj");
    heightObj->root->at("DisplaceNoiseList")->push();

    scene->getObjects().front()->addComponent("BeamGeneratorGD")->root->getFieldNames();
    auto fieldNameCount =
        scene->getObjects().front()->addComponent("HeightObj")->root->getFieldNames().size();
    ENTLIB_ASSERT(fieldNameCount == 9);

    entlib.rawdataPath = current_path();
    scene->addEntity(entlib.makeInstanceOf((current_path() / "prefab.entity").generic_u8string()));

    entlib.saveScene(*scene, current_path() / "SceneWild.test.scene");

    auto const* addedEntity = scene->getEntity("PlayerSpawner_");
    Ent::Component const* cinematicCmp = addedEntity->getComponent("CinematicGD");
    ENTLIB_ASSERT(cinematicCmp != nullptr);

    // Test dumpNode
    if (dumpNodes)
    {
        Ent::printfmt("dumpNode(Override):\n");
        Ent::printfmt(
            "%s\n",
            cinematicCmp->root->toJson(Ent::OverrideValueSource::Override, true).dump(4).c_str());

        Ent::printfmt("dumpNode(OverrideOrPrefab):\n");
        Ent::printfmt(
            "%s\n",
            cinematicCmp->root->toJson(Ent::OverrideValueSource::OverrideOrPrefab, true).dump(4).c_str());

        Ent::printfmt("dumpNode(Any):\n");
        Ent::printfmt(
            "%s\n", cinematicCmp->root->toJson(Ent::OverrideValueSource::Any, true).dump(4).c_str());
    }
    Ent::printfmt("Done\n");
    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    ENTLIB_LOG_ERROR("%s : %s", typeid(ex).name(), ex.what());
    return EXIT_FAILURE;
}
catch (...)
{
    ENTLIB_LOG_ERROR("UNKOWN EXCEPTION");
    return EXIT_FAILURE;
}
