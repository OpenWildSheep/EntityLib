#pragma warning(push, 0)
#include <ciso646>
#include <iostream>
#include <fstream>
#include <sstream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(pop)

#include <EntityLib.h>
#include <EntGen.h>
#include <ComponentMerge.h>

#include "TestCursor.h"

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
    testCursor(entlib);
    entlib.rawdataPath = current_path();
    entlib.validationEnabled = prevValidationEnabled;

    ENTLIB_ASSERT(Ent::format("Toto %d", 37) == "Toto 37");

    {
        std::map<std::string, int> emptyMap;
        ENTLIB_CHECK_EXCEPTION(AT(emptyMap, "not"), Ent::InvalidKey);
    }

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
    auto testPrefabEntity = [](Ent::Gen::Entity ent)
    {
        // ActorStates
        auto actorStates = ent.ActorStates();
        ENTLIB_ASSERT(actorStates.node->getDataType() == Ent::DataType::array);
        ENTLIB_ASSERT(actorStates.size() == 2);
        auto actorState = actorStates.ActorStateHoldingItem();
        ENTLIB_ASSERT(actorState.has_value());
        static_assert(std::is_same_v<decltype(*actorState), Ent::Gen::ActorStateHoldingItem&>);
        ENTLIB_ASSERT(actorState->node != nullptr);
        auto exitRequired = actorState->ItemEntityRef();
        ENTLIB_ASSERT(exitRequired.node != nullptr);
        ENTLIB_ASSERT(exitRequired.get().entityPath == std::string("tutu"));
        auto entityStatePlayerData = actorStates.EntityStatePlayer();
        ENTLIB_ASSERT(entityStatePlayerData.has_value());

        // Map and Set overridePolicy
        auto pathNodeGD = ent.Components().PathNodeGD();
        auto tags = pathNodeGD->Tags().Tags();
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(tags.get("a").has_value());
        ENTLIB_ASSERT(tags.get("c").has_value());
        ENTLIB_ASSERT(tags.get("c")->size() == 1);
        ENTLIB_ASSERT(tags.get("c")->count("2"));
        // Test get on map and set
        ENTLIB_ASSERT(tags.get("a")->count("1"));

        ENTLIB_ASSERT(tags.node->getKeyType() == Ent::DataType::string);
        auto keys = tags.getKeys();
        ENTLIB_ASSERT(keys.size() == 3);
        for (auto&& k : keys)
        {
            ENTLIB_ASSERT(tags.get(k.c_str()).has_value());
        }

        // Test default value
        auto voxelSimulationGD = ent.Components().VoxelSimulationGD();
        ENTLIB_ASSERT(voxelSimulationGD->TransmissionBySecond().get() == 3.402823466385289e+38);
        ENTLIB_ASSERT(voxelSimulationGD->TransmissionBySecond().isDefault());
        ENTLIB_ASSERT(voxelSimulationGD->schemaName == std::string("VoxelSimulationGD"));

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(not heightObj->Subdivision().isDefault());
        ENTLIB_ASSERT(heightObj->Subdivision().getDefault() == 3);
        ENTLIB_ASSERT(
            heightObj->Subdivision().node->getSchema()->userMeta["testUserMetatdata"].get<int>()
            == 42);

        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0llu].MapChannel().get() == 51248);
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0llu].MapChannel().isSet());

        // Test read Thumbnail
        ENTLIB_ASSERT(ent.Thumbnail().get() != nullptr);
        ENTLIB_ASSERT(ent.Thumbnail() == std::string("TestThumbnail"));

        // Test read prefab
        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat.has_value());

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Shamans")); // set
        ENTLIB_ASSERT(sysCreat->Faction().isSet()); // is set
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->Inventory().isSet()); // is set

        // TEST comment
        ENTLIB_ASSERT(sysCreat->BehaviorState().get() == std::string("W/*at*/c//h")); // set

        // TEST read array
        ENTLIB_ASSERT(sysCreat->ScriptList().isSet());
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 3);

        // TEST default values
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // default
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default

        // TEST SubScene
        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount);
        ENTLIB_ASSERT(allSubEntities.get("EP1-Spout_LINK_001").has_value());
        ENTLIB_ASSERT(allSubEntities.get("EP1-Spout_LINK_001")->Color()[0llu].get() == 255.);

        // TEST union
        auto cinematicGD = ent.Components().CinematicGD();
        auto scriptEvents = cinematicGD->ScriptEvents();
        ENTLIB_ASSERT(scriptEvents.getDataType() == Ent::DataType::array);

        // Read Union type
        auto oneOfScripts = scriptEvents[0llu];
        ENTLIB_ASSERT(oneOfScripts.getDataType() == Ent::DataType::oneOf);
        auto cineEvent = oneOfScripts.CineEventTriggerEventHandlerPost();
        ENTLIB_ASSERT(cineEvent.has_value());
        ENTLIB_ASSERT(cineEvent->schemaName == std::string("CineEventTriggerEventHandlerPost"));
        cineEvent->Super(); // If it compile, it exust

        auto nbEnt = cineEvent->EventName();
        ENTLIB_ASSERT(nbEnt.getDataType() == Ent::DataType::string);
        ENTLIB_ASSERT(nbEnt == std::string("Toto"));

        // TEST sub-object with non-default values
        auto ldprimitive = ent.Components().LDPrimitive();
        auto primitiveData = ldprimitive->PrimitiveData();
        ENTLIB_ASSERT(primitiveData.Height().get() == 42.0);

        // TEST Default size for array is minItems
        auto physicsGD = ent.Components().PhysicsGD();
        auto axisRestriction = physicsGD->AxisRestriction();
        ENTLIB_ASSERT(axisRestriction.size() == 3);

        // Test default values related to a property of type class/struct.
        auto characterController = ent.Components().CharacterControllerGD();
        auto slideData = characterController->SlideData();
        auto adherenceMin = slideData.speedMediumCoeffIn();
        auto in = adherenceMin.in_();
        ENTLIB_ASSERT(in.size() == 2);
        ENTLIB_ASSERT(in[0].get() == -1.);
        ENTLIB_ASSERT(in[1].get() == 0.5);

        // Ensure that default values of property are not poluted by default values of pointer class
        auto testDefaultValues = ent.Components().TestDefaultValues();
        ENTLIB_ASSERT(testDefaultValues.has_value());
        auto propertyWithDefault = testDefaultValues->propertyWithDefault();
        auto propertyWithDefault2 = propertyWithDefault.propertyWithDefault2();
        ENTLIB_ASSERT(propertyWithDefault2.A().get() == 3);
        ENTLIB_ASSERT(propertyWithDefault2.B().get() == 0);
        auto propertyWithDefault3 = propertyWithDefault.propertyWithDefault3();
        ENTLIB_ASSERT(propertyWithDefault3.A().get() == 3);
        ENTLIB_ASSERT(propertyWithDefault3.B().get() == 0);

        // Test Node's InstanceOf
        auto seedPatch = ent.Components().SeedPatch();
        ENTLIB_ASSERT(seedPatch->NoiseSizeX().get() == 1.);
        ENTLIB_ASSERT(seedPatch->NoiseSizeY().get() == 2.);
        ENTLIB_ASSERT(seedPatch->NoiseOffsetX().get() == 2.);
    };

    {
        auto entStorage = entlib.makeEntityNode();
        Ent::Gen::Entity ent(entStorage.get());
        ent.Name() = "TestResetInstanceOf";
        ent.resetInstanceOf("prefab.entity");
        ENTLIB_ASSERT(ent.hasOverride()); // resetInstanceOf does override the "instanceOf"
        ENTLIB_ASSERT(ent.getInstanceOf() == std::string("prefab.entity"));
    }
    {
        auto ent = entlib.loadEntityAsNode("missing_embedded.entity");
        ENTLIB_ASSERT(ent->at("Components")->size() == 1); // Contains only SubScene
    }
    {
        auto entNode = entlib.loadEntityAsNode("prefab.entity");
        Ent::Gen::Entity ent(entNode.get());

        // Test title/description
        {
            auto rigodBodyCoeffSchema = ent.Components()
                                            .CharacterControllerGD()
                                            ->HeadCollisionData()
                                            .softCollisionRigidbodyCoeff()
                                            .getSchema();
            ENTLIB_ASSERT(rigodBodyCoeffSchema->title.find("Rigidbody") != std::string::npos);
            ENTLIB_ASSERT(rigodBodyCoeffSchema->description.find("rigidbody") != std::string::npos);
        }

        auto setOfObject = ent.Components().TestSetOfObject();
        ENTLIB_ASSERT(setOfObject);
        auto mapTest = setOfObject->MapOfObject();
        auto testParent = mapTest.add("Should_not_appear_in_diff");
        ENTLIB_ASSERT(testParent.node->getParentNode()->getSchema()->linearItems.has_value());
        ENTLIB_ASSERT(testParent.node->getParentNode()->getParentNode()->isMapOrSet());
        mapTest.remove("Should_not_appear_in_diff");
        ENTLIB_ASSERT(not mapTest.get("Should_not_appear_in_diff").has_value());

        // Test a fixed-size array is not "addedInInstance"
        auto trans = ent.Components().TransformGD();
        ENTLIB_ASSERT(trans.has_value());
        trans->Position()[0] = 36.f;
        trans->Position().unset();
        ENTLIB_ASSERT(not trans->Position().hasOverride());

        // Test Variant
        auto testArrays = ent.Components().TestArrays();
        ENTLIB_ASSERT(testArrays->Variant().float_()->get() == 3.1416);
        nlohmann::json withoutIndex = testArrays->Variant().node->toJson(
            Ent::OverrideValueSource::OverrideOrPrefab, true, {}, false);
        ENTLIB_ASSERT(withoutIndex.count("variantIndex") == 0);
        nlohmann::json withIndex = testArrays->Variant().node->toJson(
            Ent::OverrideValueSource::OverrideOrPrefab, true, {}, true);
        ENTLIB_ASSERT(withIndex.at("variantIndex") == 1);

        // Test saveNode
        auto heightObj = ent.Components().HeightObj();
        heightObj->node->saveNode("test.HeightObj.node");

        testPrefabEntity(ent);
        // Test mapErase in set of primitive
        auto pathNodeGD = ent.Components().PathNodeGD();
        auto tags = pathNodeGD->Tags().Tags();
        auto primSet = tags.get("a");
        ENTLIB_ASSERT(primSet->node->getParentNode()->getParentNode()->isMapOrSet());
        ENTLIB_CHECK_EXCEPTION(primSet->node->mapErase("1"), Ent::BadArrayType);

        // Set Union type and override
        auto cinematicGD = ent.Components().CinematicGD();
        auto scriptEvents = cinematicGD->ScriptEvents();
        auto oneOfScripts2 = scriptEvents[1];
        ENTLIB_ASSERT(oneOfScripts2.getDataType() == Ent::DataType::oneOf);
        ENTLIB_ASSERT(oneOfScripts2.getType() == std::string("CineEventTriggerEventHandlerPost"));
        oneOfScripts2.setCineEventTestCurrentGameState();
        ENTLIB_CHECK_EXCEPTION(
            oneOfScripts2.node->setUnionType("ThisTypeDoesntExist"), Ent::BadUnionType);
        auto testCurrentState = oneOfScripts2.CineEventTestCurrentGameState();
        ENTLIB_ASSERT(oneOfScripts2.getType() == std::string("CineEventTestCurrentGameState"));
        testCurrentState->GameStateName().set("Pouet!");

        // Set Union type without override
        auto oneOfScripts3 = scriptEvents[2];
        ENTLIB_ASSERT(oneOfScripts3.getDataType() == Ent::DataType::oneOf);
        ENTLIB_ASSERT(oneOfScripts3.getType() == std::string("CineEventTriggerEventHandlerPost"));
        oneOfScripts3.setCineEventTestCurrentGameState();

        // Push in an array of Union
        auto oneOfScripts4 = scriptEvents.push();
        ENTLIB_ASSERT(oneOfScripts4.getDataType() == Ent::DataType::oneOf);
        // CineEventTestCurrentGameState is the first one
        ENTLIB_ASSERT(oneOfScripts4.getType() == std::string("CineEventTestCurrentGameState"));
        ENTLIB_ASSERT(scriptEvents[3].node == oneOfScripts4.node);

        // TEST simple entity ref creation
        auto testEntityRef = ent.Components().addTestEntityRef();
        ENTLIB_ASSERT(testEntityRef.TestRef().get().entityPath.empty());
        testEntityRef.TestRef().set(entlib.makeEntityRef(*ent.node, *ent.node));
        ENTLIB_ASSERT(testEntityRef.TestRef().get().entityPath == ".");
        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        testEntityRef.TestRef().set(entlib.makeEntityRef(*ent.node, *allSubEntities.begin()->node));

        // TEST Union not in Object
        auto testUnion = ent.Components().addTestUnion();
        auto un = testUnion.Union();
        un.unset();
        ENTLIB_ASSERT(not un.hasOverride());
        ENTLIB_ASSERT(un.getType() == std::string("s32"));
        un.setfloat_();
        ENTLIB_ASSERT(un.hasOverride());
        ENTLIB_ASSERT(un.getType() == std::string("float"));
        un.sets32();
        ENTLIB_ASSERT(un.hasOverride());
        ENTLIB_ASSERT(un.getType() == std::string("s32"));
        un.unset();
        ENTLIB_ASSERT(not un.hasOverride());
        ENTLIB_ASSERT(un.getType() == std::string("s32"));
        // TEST Union not in Array
        auto unArr = testUnion.UnionArray();
        auto newUnion = unArr.push();
        ENTLIB_ASSERT(not newUnion.node->getUnionData()->hasOverride());
        ENTLIB_ASSERT(newUnion.getType() == std::string("s32"));
        // TEST Union not in Object in Array
        auto obj = testUnion.UnionObjectArray().push();
        newUnion = obj.Union();
        ENTLIB_ASSERT(not newUnion.node->getUnionData()->hasOverride());
        ENTLIB_ASSERT(newUnion.getType() == std::string("s32"));

        // TEST MaxActivationLevel
        ent.MaxActivationLevel().set(Ent::Gen::MaxActivationLevelEnum::InWorld);

        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat->Name().get() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->Name().isSet()); // default
        sysCreat->Name().set("Shamane_male");
        entlib.saveNodeAsEntity(ent.node, "prefab.copy.entity");

        // TEST SubScene detach
        auto originalSubEntities = ent.Components().SubScene()->Embedded();
        ENTLIB_ASSERT(not originalSubEntities.empty());
        ent.Components().SubScene()->Embedded().clear();
        ENTLIB_ASSERT(ent.Components().SubScene()->Embedded().empty());

        ent.Components().removeSubScene();
        entlib.saveNodeAsEntity(ent.node, "prefab.emptyembbeded.entity"); // to check the schema

        // TEST arrays default values
        ent.Components().removeTransformGD();
        auto transformGD = ent.Components().addTransformGD();
        auto mat33 = transformGD.Matrix();
        auto testMat33 = [&]()
        {
            ENTLIB_ASSERT(mat33[0].get() == 1.);
            ENTLIB_ASSERT(mat33[0].getDefault() == 1.);
            ENTLIB_ASSERT(mat33[1].get() == 0.);
            ENTLIB_ASSERT(mat33[1].getDefault() == 0.);
            ENTLIB_ASSERT(mat33[2].get() == 0.);
            ENTLIB_ASSERT(mat33[3].get() == 0.);
            ENTLIB_ASSERT(mat33[4].get() == 1.);
            ENTLIB_ASSERT(mat33[4].getDefault() == 1.);
            ENTLIB_ASSERT(mat33[5].get() == 0.);
        };

        auto testDefaultValues = ent.Components().addTestDefaultValues();
        ENTLIB_ASSERT(testDefaultValues.node->getParentNode()->hasOverride());
        mat33 = testDefaultValues.Matrix();
        testMat33();
        mat33 = testDefaultValues.Matrix2();
        ENTLIB_ASSERT(mat33[4].getDefault() == 4.);
        ENTLIB_ASSERT(mat33[4].get() == 4.);
        ENTLIB_ASSERT(not mat33[4].hasOverride());
        ENTLIB_ASSERT(not mat33[4].isSet());
    }
    {
        // Test Arrays size overrides
        auto entStorage = entlib.loadEntityAsNode("instance_arrays.entity");
        Ent::Gen::Entity ent(entStorage.get());

        ENTLIB_ASSERT(entStorage);
        auto comp = ent.Components().TestArrays();
        ENTLIB_ASSERT(comp);
        const auto testArrayMember = [&](char const* _arrayName,
                                         size_t defaultSize,
                                         std::optional<size_t> prefabSize,
                                         std::optional<size_t> overrideSize)
        {
            auto node = comp->node->at(_arrayName);
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
        auto ent = entlib.loadNodeEntityReadOnly("prefab.entity");
        testPrefabEntity(Ent::Gen::Entity(const_cast<Ent::Node*>(ent.get())));
    }
    {
        auto const nodeCachesize = entlib.getNodeCache().size();
        auto entStorage = entlib.loadEntityAsNode("prefab.copy.entity");
        Ent::Gen::Entity ent(entStorage.get());
        auto const newNodeCachesize = entlib.getNodeCache().size();
        // 1 files more in cache:
        //     "prefab.copy.entity"
        ENTLIB_ASSERT(newNodeCachesize == nodeCachesize + 1);
        // TEST simple entity refs resolution
        auto testEntityRef = ent.Components().TestEntityRef();
        ENTLIB_ASSERT(testEntityRef.has_value());
        ENTLIB_ASSERT(testEntityRef->TestRef().isSet());
        Ent::EntityRef entityRef = testEntityRef->TestRef().get();
        auto resolvedEntity = entlib.resolveEntityRef(ent.node, entityRef);
        ENTLIB_ASSERT(resolvedEntity != nullptr);

        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        ENTLIB_ASSERT(not allSubEntities.empty());
        auto originalEnt = allSubEntities.begin();
        ENTLIB_ASSERT(resolvedEntity == originalEnt->node);

        auto newSubEnt = allSubEntities.add("prefab.entity");
        newSubEnt.Name().set("newSubEnt");
        ENTLIB_ASSERT(entlib.makeEntityRef(*ent.node, *newSubEnt.node).entityPath == "newSubEnt");

        auto embedded = ent.Components().SubScene()->Embedded();
        auto insertedEnt = embedded.insertInstanceOf("prefab.entity");
        insertedEnt.node->checkParent(embedded.node);
    }

    {
        // Test write prefab
        auto entStorage = entlib.loadEntityAsNode("prefab.copy.entity");
        Ent::Gen::Entity ent(entStorage.get());

        testPrefabEntity(ent);

        // TEST Tuple hasOverride
        auto unitTestComponent = ent.Components().addUnitTestComponent();
        auto wp = unitTestComponent.Position();
        ENTLIB_ASSERT(wp.hasOverride() == false);
        ENTLIB_ASSERT(wp.get<0>().hasOverride() == false);

        // TEST MaxActivationLevel
        ENTLIB_ASSERT(ent.MaxActivationLevel() == Ent::Gen::MaxActivationLevelEnum::InWorld);

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat.has_value());
        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Shamans")); // set
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set

        // TEST read array
        ENTLIB_ASSERT(sysCreat->ScriptList().isSet());
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 3);

        // TEST default values unchanged
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // default
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default

        // TEST changed values
        ENTLIB_ASSERT(sysCreat->Name().get() == std::string("Shamane_male")); // set. changed.
        ENTLIB_ASSERT(sysCreat->Name().isSet()); // set. changed.

        // TEST simple entity refs resolution
        auto testEntityRef = ent.Components().TestEntityRef();
        ENTLIB_ASSERT(testEntityRef.has_value());
        ENTLIB_ASSERT(testEntityRef->TestRef().isSet());
        Ent::EntityRef entityRef = testEntityRef->TestRef().get();
        auto resolvedEntity = entlib.resolveEntityRef(ent.node, entityRef);
        ENTLIB_ASSERT(resolvedEntity != nullptr);

        auto subScenecomp = *ent.Components().SubScene();
        auto allSubEntities = subScenecomp.Embedded();
        ENTLIB_ASSERT(not allSubEntities.empty());
        auto originalEnt = allSubEntities.begin()->node;
        ENTLIB_ASSERT(resolvedEntity == originalEnt);
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
        auto entStorage = entlib.loadEntityAsNode("entity-references.scene");
        Ent::Gen::Entity ent(entStorage.get());
        auto scene = ent.Components().SubScene()->Embedded();
        auto instanceOfA = *scene.get("InstanceOfA");
        ENTLIB_ASSERT(strcmp(instanceOfA.Name(), "InstanceOfA") == 0);
        auto subSceneComp = instanceOfA.Components().SubScene();
        ENTLIB_ASSERT(subSceneComp.has_value());
        ENTLIB_ASSERT(subSceneComp->Embedded().size() == 1);
        auto B = *subSceneComp->Embedded().get("B");
        ENTLIB_ASSERT(strcmp(B.Name(), "B") == 0);
        auto C = *scene.get("C");
        ENTLIB_ASSERT(strcmp(C.Name(), "C") == 0);

        // TEST entity ref creation
        Ent::EntityRef BToInstanceOfAref = entlib.makeEntityRef(*B.node, *instanceOfA.node);
        ENTLIB_ASSERT(BToInstanceOfAref.entityPath == "..");
        Ent::EntityRef InstanceOfAToBref = entlib.makeEntityRef(*instanceOfA.node, *B.node);
        ENTLIB_ASSERT(InstanceOfAToBref.entityPath == "B");
        Ent::EntityRef CToBref = entlib.makeEntityRef(*C.node, *B.node);
        ENTLIB_ASSERT(CToBref.entityPath == "../InstanceOfA/B");
        Ent::EntityRef BToCref = entlib.makeEntityRef(*B.node, *C.node);
        ENTLIB_ASSERT(BToCref.entityPath == "../../C");

        // TEST entity ref resolution
        auto resolvedEmptyRef = entlib.resolveEntityRef(instanceOfA.node, {});
        ENTLIB_ASSERT(resolvedEmptyRef == nullptr);
        auto resolvedInstanceOfA = entlib.resolveEntityRef(B.node, {".."});
        ENTLIB_ASSERT(resolvedInstanceOfA == instanceOfA.node);
        auto resolvedB = entlib.resolveEntityRef(instanceOfA.node, {"B"});
        ENTLIB_ASSERT(resolvedB == B.node);
        auto resolvedBbis = entlib.resolveEntityRef(C.node, {"../InstanceOfA/B"});
        ENTLIB_ASSERT(resolvedBbis == B.node);
        auto resolvedC = entlib.resolveEntityRef(B.node, {"../../C"});
        ENTLIB_ASSERT(resolvedC == C.node);

        // TEST entity ref resolution from scenes
        ENTLIB_ASSERT(entlib.resolveEntityRef(scene.node, {".."}) == nullptr);
        ENTLIB_ASSERT(entlib.resolveEntityRef(scene.node, {"InstanceOfA"}) == instanceOfA.node);
        ENTLIB_ASSERT(entlib.resolveEntityRef(scene.node, {"InstanceOfA/B"}) == B.node);
        ENTLIB_ASSERT(entlib.resolveEntityRef(scene.node, {"C"}) == C.node);
        ENTLIB_ASSERT(entlib.resolveEntityRef(scene.node, {"InstanceOfA/B/../../C"}) == C.node);
    }

    auto testInstanceOf = [](Ent::Gen::Entity ent, bool testIsSet = true, bool testPrefab = true)
    {
        // ActorStates
        auto actorStates = ent.ActorStates();
        actorStates.node->checkParent(ent.node); // Check the parent of nodes is valid
        auto& actorStatesCopy = actorStates; //NOLINT(performance-unnecessary-copy-initialization)
        actorStatesCopy.node->checkParent(ent.node); // Check the parent of nodes is valid
        ENTLIB_ASSERT(actorStates.getDataType() == Ent::DataType::array);
        ENTLIB_ASSERT(actorStates.size() == 3);
        auto actorState = *actorStates.begin();
        ENTLIB_ASSERT(actorState.node != nullptr);
        auto climbEdge = actorState.node->getUnionData();
        ENTLIB_ASSERT(climbEdge != nullptr);
        ENTLIB_ASSERT(climbEdge->getParentNode()->getParentNode() == actorState.node);
        auto exitRequired = climbEdge->at("ItemEntityRef");
        ENTLIB_ASSERT(exitRequired != nullptr);
        ENTLIB_ASSERT(exitRequired->getEntityRef().entityPath == std::string("tutu"));
        auto dead = actorStates.ActorStateDead();
        ENTLIB_ASSERT(dead.has_value());
        auto deadData = *dead;
        auto actorStateHoldingItem = actorStates.ActorStateHoldingItem();
        ENTLIB_ASSERT(actorStateHoldingItem.has_value());
        auto itemEntityRef = actorStateHoldingItem->ItemEntityRef();
        ENTLIB_ASSERT(itemEntityRef.get().entityPath == "tutu");

        // Map and Set overridePolicy
        auto pathNodeGD = *ent.Components().PathNodeGD();
        auto tags = pathNodeGD.Tags().Tags();
        ENTLIB_ASSERT(tags.node->getParentNode()->getParentNode() == pathNodeGD.node);
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(tags.get("a")->node->getParentNode()->getParentNode() == tags.node);
        ENTLIB_ASSERT(tags.get("a")->node != nullptr);
        ENTLIB_ASSERT(tags.get("b").has_value());
        ENTLIB_ASSERT(tags.get("c").has_value());
        ENTLIB_ASSERT(tags.get("c")->size() == 3);
        ENTLIB_ASSERT(tags.get("c")->count("1"));
        ENTLIB_ASSERT(tags.get("c")->count("2"));
        ENTLIB_ASSERT(tags.get("c")->count("3"));
        // Test get on map
        auto cValueSet = tags.get("c");
        ENTLIB_ASSERT(cValueSet.has_value());
        // Test get on set
        ENTLIB_ASSERT(cValueSet->count("1"));

        // TEST SubScene (without override)
        auto subScene = ent.Components().SubScene();
        ENTLIB_ASSERT(subScene.has_value());
        auto subObj = *subScene->Embedded().begin();
        ENTLIB_ASSERT(subObj.Name() == std::string("EP1-Spout_LINK_001"));
        if (testIsSet)
        {
            ENTLIB_ASSERT(not subObj.Name().isSet());
            ENTLIB_ASSERT(not subObj.hasOverride());
        }
        auto netLink = subObj.Components().NetworkLink();
        ENTLIB_ASSERT(netLink.has_value());
        ENTLIB_ASSERT(netLink->Source().get() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->Target().get() == std::string(".EP1-crook_"));
        if (testIsSet)
        {
            ENTLIB_ASSERT(netLink->Source().isSet() == false);
            ENTLIB_ASSERT(netLink->Target().isSet() == false);
        }
        auto trans = *subObj.Components().TransformGD();
        ENTLIB_ASSERT(trans.Position()[0].get() == 0.0);

        // Test unset union in unionset
        auto transGDUnion = subObj.Components().node->mapGet("TransformGD");
        ENTLIB_CHECK_EXCEPTION(transGDUnion->unset(), Ent::BadType);

        // "InstanceOf" in sub entitites
        auto entityWithInstanceOf = *subScene->Embedded().get(R"(EntityWithInstanceOf)");
        ENTLIB_ASSERT(entityWithInstanceOf.Name() == std::string("EntityWithInstanceOf"));
        ENTLIB_ASSERT(entityWithInstanceOf.getInstanceOf() == std::string("subentity2.entity"));
        auto networkLink = *entityWithInstanceOf.Components().NetworkLink();
        ENTLIB_ASSERT(networkLink.Source().get() == std::string("instance"));
        ENTLIB_ASSERT(networkLink.Target().get() == std::string("subentity2"));
        ENTLIB_ASSERT(networkLink.ThumbnailMesh().get() == std::string());

        // Test instanciation of a prefab Node
        auto stickToTerrain = *ent.Components().StickToTerrain();
        if (testPrefab)
        {
            ENTLIB_ASSERT(stickToTerrain.getInstanceOf() != nullptr);
            ENTLIB_ASSERT(stickToTerrain.getInstanceOf() == std::string("test.StickToTerrain.node"));
        }
        ENTLIB_ASSERT(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isSet() == false);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        // Test Node's InstanceOf
        auto seedPatch = *ent.Components().SeedPatch();
        ENTLIB_ASSERT(seedPatch.NoiseSizeX().isDefault());
        ENTLIB_ASSERT(seedPatch.NoiseSizeY().get() == 3.);
        ENTLIB_ASSERT(not seedPatch.NoiseOffsetX().isSet());
        ENTLIB_ASSERT(seedPatch.NoiseOffsetY().get() == 3.);
    };

    {
        // Test applyToPrefab

        // Prepare data
        auto entStorage = entlib.loadEntityAsNode("instance.entity");
        Ent::Gen::Entity ent(entStorage.get());
        auto entJson = ent.node->toJson();
        entJson["InstanceOf"] = "prefab_updated.entity";
        {
            std::ofstream outEnt("instance_applied.entity");
            outEnt << entJson.dump(4);
        }
        std::filesystem::copy_file(
            "prefab.entity", "prefab_updated.entity", copy_options::overwrite_existing);

        entStorage = entlib.loadEntityAsNode("instance_applied.entity");
        // Do the applyToPrefab
        ent = Ent::Gen::Entity(entStorage.get());
        ent.node->applyToPrefab();
        auto actorStates = ent.ActorStates();
        actorStates.node->checkParent(ent.node); // Check the parent of nodes is valid
        ent.save("instance_applied.entity");
        actorStates.node->checkParent(ent.node); // Check the parent of nodes is valid
        auto prefab = entlib.loadEntityAsNode("prefab_updated.entity");
        actorStates.node->checkParent(ent.node); // Check the parent of nodes is valid

        // Test result
        testInstanceOf(Ent::Gen::Entity(prefab.get()), false);
        actorStates.node->checkParent(ent.node); // Check the parent of nodes is valid
        testInstanceOf(ent, false);
        ENTLIB_ASSERT(ent.hasOverride()); // Because applyToPrefab set the old name

        entStorage = entlib.loadEntityAsNode("instance_applied.entity");
        ent = Ent::Gen::Entity(entStorage.get());
        testInstanceOf(ent, false);
        ENTLIB_ASSERT(ent.hasOverride()); // Because applyToPrefab set the old name
    }

    {
        // Test read instance of
        auto entStorage = entlib.loadEntityAsNode("instance.entity");
        Ent::Gen::Entity ent(entStorage.get());
        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat.has_value());

        ENTLIB_ASSERT(ent.Color().hasOverride());

        // TEST read overrided value
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // Inherited
        ENTLIB_ASSERT(sysCreat->Life().get() == 1000.); // Inherited

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(not heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST read default value
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // Inherited (from default)
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default

        // TEST read overrided in array
        ENTLIB_ASSERT(sysCreat->ScriptList()[1].get() == std::string("b2")); // Overrided
        ENTLIB_ASSERT(sysCreat->ScriptList()[1].isSet()); // Overrided
        // TEST read Not overrided in array
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].get() == std::string("c1")); // not overrided
        ENTLIB_ASSERT(not sysCreat->ScriptList()[2].isSet()); // Not overrided

        // Programatically unset
        sysCreat->ScriptList()[1].unset();
        // Programatically set
        sysCreat->ScriptList()[2].set("c2");

        // TEST read array
        ENTLIB_ASSERT(sysCreat->ScriptList().isSet());
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 3);

        // TEST Extand array
        sysCreat->ScriptList().push().set("d2");
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 4);

        // TEST SubScene (without override)
        testInstanceOf(ent);

        auto testSetOfObject = *ent.Components().TestSetOfObject();
        {
            auto setOfObject = testSetOfObject.SetOfObject().node;

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
        auto subsceneCmp = *ent.Components().SubScene();
        ENTLIB_ASSERT(subsceneCmp.Embedded().size() == PrefabSubEntityCount);
        subsceneCmp.Embedded().remove("TestRemove");
        ENTLIB_ASSERT(subsceneCmp.Embedded().size() == PrefabSubEntityCount - 1);

        // Test rename Entity
        // - Possible
        auto uglyent = subsceneCmp.Embedded().add("UglyName");
        ENTLIB_ASSERT(subsceneCmp.Embedded().get("UglyName")->Name() == std::string("UglyName"));
        subsceneCmp.Embedded().node->mapRename("UglyName", "PrettyName");
        ENTLIB_ASSERT(subsceneCmp.Embedded().get("PrettyName")->Name() == std::string("PrettyName"));
        subsceneCmp.Embedded().node->mapRename("PrettyName", "PrettiestName");
        ENTLIB_ASSERT(
            subsceneCmp.Embedded().get("PrettiestName")->Name() == std::string("PrettiestName"));
        // - Not possible
        ENTLIB_CHECK_EXCEPTION(
            subsceneCmp.Embedded().node->mapRename("EntityWithInstanceOf", "EntityWithInstanceOf2"),
            Ent::CantRename);

        // Test rename object in set
        // - Possible
        ENTLIB_ASSERT(testSetOfObject.SetOfObject().get("A")->Value().get() == std::string("a"));
        testSetOfObject.SetOfObject().node->mapRename("A", "A3");
        testSetOfObject.SetOfObject().node->mapRename("A3", "A2");
        ENTLIB_ASSERT(testSetOfObject.SetOfObject().get("A2")->Value().get() == std::string("a"));
        ENTLIB_ASSERT(testSetOfObject.SetOfObject().get("A").has_value() == false);
        // - Not possible
        ENTLIB_ASSERT(testSetOfObject.SetOfObject().get("D")->Value().get() == std::string("d"));
        // TODO : decomment!!
        ENTLIB_CHECK_EXCEPTION(
            testSetOfObject.SetOfObject().node->mapRename("D", "D2"), Ent::CantRename);

        // ****************************** Test hasASuper ******************************************
        // *************** ENTITY ***************
        auto subscene = *ent.Components().SubScene();
        // new entity : Since the entityname is mandatory, it is always overriden when new
        subscene.Embedded().add("Entity");
        // entity with override
        auto entWithOverride = subscene.Embedded().get("TestSaveEntWithOverride");
        ENTLIB_ASSERT(entWithOverride.has_value());
        auto networkLink = entWithOverride->Components().NetworkLink();
        ENTLIB_ASSERT(networkLink.has_value());
        networkLink->ThumbnailMesh().set("DefaultLinkVisual.wbm");
        ENTLIB_ASSERT(entWithOverride->hasOverride());
        // entity with instanceOf overriden
        auto entWithoutOverride = subscene.Embedded().get(R"(EntityWithInstanceOfButNoOverride)");
        entWithoutOverride->resetInstanceOf("subentity2.entity");
        ENTLIB_ASSERT(entWithoutOverride->getInstanceOf() == std::string("subentity2.entity"));
        ENTLIB_ASSERT(entWithoutOverride->hasOverride());
        // *************** COMPONENT ***************
        // new Component
        auto comp = ent.Components().addAnimationEventsGeneratorGD();
        ENTLIB_ASSERT(ent.Components().AnimationEventsGeneratorGD().has_value());
        ENTLIB_ASSERT(
            comp.node->getParentNode()->hasOverride()); // A new item in an array in always override
        // Component with override
        ent.Components().VoxelSimulationGD()->LossBySecond().set(36.);
        ENTLIB_ASSERT(ent.Components().VoxelSimulationGD().has_value());
        ENTLIB_ASSERT(ent.Components().VoxelSimulationGD()->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = *ent.Components().CharacterControllerGD();
        compWithInstOf.resetInstanceOf("test.CharacterControllerGD.node");
        ENTLIB_ASSERT(
            compWithInstOf.getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        ENTLIB_ASSERT(compWithInstOf.hasOverride());
        // *************** NODE ***************
        // new Node
        auto setOfObject = ent.Components().TestSetOfObject();
        ENTLIB_ASSERT(setOfObject);
        auto mapTest = setOfObject->MapOfObject();
        mapTest.add("NewNode");
        ENTLIB_ASSERT(mapTest.get("NewNode").has_value());
        ENTLIB_ASSERT(mapTest.get("NewNode")->hasOverride()); // Newly inserted noeds are always overriden
        // Node with override
        mapTest.get("OldNode1")->Value().set("overriden");
        ENTLIB_ASSERT(mapTest.get("OldNode1")->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest.get("OldNode1")->hasOverride());
        // Node with instanceOf overriden
        mapTest.get("OldNode2")->resetInstanceOf("OldNode2.MapOfObject.node");
        auto val = mapTest.get("OldNode2");
        ENTLIB_ASSERT(val->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(val->hasOverride());

        // Test mapInsert in map
        {
            mapTest = setOfObject->MapOfObject();
            auto newNode2 = mapTest.add("NewNode2");
            ENTLIB_ASSERT(newNode2.getDataType() == Ent::DataType::object);
        }

        sysCreat->BehaviorState().set("Overrided");
        ent.save("instance.copy.entity");

        {
            auto instance3Storage = ent.makeInstanceOf();
            Ent::Gen::Entity instance3(instance3Storage.get());

            auto testSetOfObject3 = *instance3.Components().TestSetOfObject();
            auto setOfObject3 = testSetOfObject3.SetOfObject();

            auto mapTest2 = testSetOfObject3.MapOfObject();
            mapTest2.add("Should_not_appear_in_diff");
            mapTest2.remove("Should_not_appear_in_diff");

            // Test insert an element in an instance of the __removed__ one, do not resore the old values
            // insert => makeInstanceOf => __remove__ => makeInstanceOf => insert
            //          => do not restore values
            ENTLIB_ASSERT(not setOfObject3.get("G").has_value());
            setOfObject3.add("G");
            ENTLIB_ASSERT(setOfObject3.get("G")->Value().get() == std::string());
            instance3.save("instance3.entity");
        }
    }
    {
        auto entStorage = entlib.loadEntityAsNode("instance3.entity");
        Ent::Gen::Entity ent(entStorage.get());

        auto testSetOfObject3 = *ent.Components().TestSetOfObject();
        auto setOfObject3 = testSetOfObject3.SetOfObject();

        // Test insert an element in an instance of the __removed__ one, do not resore the old values
        // insert => makeInstanceOf => __remove__ => makeInstanceOf => insert
        //          => do not restore values
        ENTLIB_ASSERT(setOfObject3.get("G")->Value().get() == std::string());
    }

    auto test_erase = [](Ent::Gen::Entity ent)
    {
        auto actorStates = ent.ActorStates();
        auto pathNodeGD = *ent.Components().PathNodeGD();
        auto tags = pathNodeGD.Tags().Tags();

        // Test erase in map (+save/load)
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(not tags.get("c").has_value());

        // Test insert in map (+save/load)
        auto e = tags.get("A");
        ENTLIB_ASSERT(e.has_value());
        ENTLIB_ASSERT(e->getDataType() == Ent::DataType::array);

        // Test erase in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.get("EntityStatePlayer").has_value() == false);

        // Test insert in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.get("ActorStateAlive").has_value());

        // Test remove component
        ENTLIB_ASSERT(ent.Components().TransformGD().has_value() == false);
        ENTLIB_ASSERT(ent.Components().SubScene().has_value() == false);
    };

    {
        auto entStorage = entlib.loadEntityAsNode("instance.entity");
        Ent::Gen::Entity ent(entStorage.get());

        // Test erase in union_set
        auto actorStates = ent.ActorStates();
        ENTLIB_ASSERT(actorStates.get("EntityStatePlayer").has_value());
        ENTLIB_ASSERT(actorStates.remove("EntityStatePlayer"));
        ENTLIB_ASSERT(actorStates.get("EntityStatePlayer").has_value() == false);

        // Test insert in union_set
        actorStates.addActorStateAlive();

        // Test erase in map
        auto pathNodeGD = *ent.Components().PathNodeGD();
        auto tags = pathNodeGD.Tags().Tags();
        ENTLIB_ASSERT(tags.get("c").has_value());
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(tags.remove("c"));
        ENTLIB_ASSERT(tags.size() == 2);
        ENTLIB_ASSERT(tags.get("c").has_value() == false);
        ENTLIB_ASSERT(not tags.remove("c"));

        // Test insert in map
        ENTLIB_ASSERT(tags.get("A").has_value() == false);
        tags.add("A");
        ENTLIB_ASSERT(tags.begin()->first == std::string("A")); // "A" should be first

        // Test erase in Components
        ENTLIB_ASSERT(ent.Components().TransformGD().has_value());
        ent.Components().removeTransformGD();
        ENTLIB_ASSERT(ent.Components().TransformGD().has_value() == false);

        ENTLIB_ASSERT(ent.Components().SubScene().has_value());
        ent.Components().removeSubScene();
        ENTLIB_ASSERT(ent.Components().SubScene().has_value() == false);

        test_erase(ent);

        ent.save("test_erase.entity");
    }

    {
        auto entStorage = entlib.loadEntityAsNode("test_erase.entity");
        Ent::Gen::Entity ent(entStorage.get());
        test_erase(ent);
    }
    {
        auto entStorage = entlib.loadEntityAsNode("test_erase.entity");
        Ent::Gen::Entity ent(entStorage.get());
        test_erase(ent);
        auto json = ent.ActorStates().node->toJson(Ent::OverrideValueSource::OverrideOrPrefab, true);
        ENTLIB_ASSERT(json.size() == 3);
        for (auto&& actState : json)
        {
            ENTLIB_ASSERT(actState["className"] != "EntityStatePlayer");
        }
    }
    {
        auto entStorage = entlib.loadEntityAsNode("instance2.entity");
        Ent::Gen::Entity ent(entStorage.get());
        testInstanceOf(ent, true, false);
    }
    auto testInstanceOverrideSubscene = [](Ent::Gen::Entity ent)
    {
        // TEST SubScene (with override)
        auto subScene = ent.Components().SubScene();
        ENTLIB_ASSERT(subScene.has_value());
        auto subObj = subScene->Embedded().get("EP1-Spout_LINK_001");
        ENTLIB_ASSERT(subObj->Name() == std::string("EP1-Spout_LINK_001"));

        // Test an overrided Component
        auto netLink = subObj->Components().NetworkLink();
        ENTLIB_ASSERT(netLink.has_value());
        ENTLIB_ASSERT(netLink->Source().get() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->Source().isSet() == false);
        ENTLIB_ASSERT(netLink->Target().get() == std::string(".EP1-crook_2"));
        ENTLIB_ASSERT(netLink->Target().isSet());

        // Test a not overrided Component
        auto trans = subObj->Components().TransformGD();
        ENTLIB_ASSERT(trans.has_value());
        ENTLIB_ASSERT(trans->Position()[0].get() == 0.0);
    };
    {
        auto entStorage = entlib.loadEntityAsNode("instance_override_subscene.entity");
        Ent::Gen::Entity ent(entStorage.get());
        testInstanceOverrideSubscene(ent);
        ent.save("instance_override_subscene.copy.entity");
    }
    {
        auto entStorage = entlib.loadEntityAsNode("instance_override_subscene.copy.entity");
        Ent::Gen::Entity ent(entStorage.get());
        testInstanceOverrideSubscene(ent);
    }
    {
        // Test write instance of
        auto entStorage = entlib.loadEntityAsNode("instance.copy.entity");
        Ent::Gen::Entity ent(entStorage.get());
        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat.has_value());

        // Test remove object in set
        auto testSetOfObject = *ent.Components().TestSetOfObject();
        auto setOfObject = testSetOfObject.SetOfObject();
        ENTLIB_ASSERT(setOfObject.get("B").has_value() == false);
        ENTLIB_ASSERT(setOfObject.get("C").has_value() == false);
        ENTLIB_ASSERT(setOfObject.size() == 4);

        // Test override object in set (especially override name)
        ENTLIB_ASSERT(setOfObject.get("E").has_value());
        ENTLIB_ASSERT(setOfObject.get("E2").has_value() == false);
        ENTLIB_ASSERT(setOfObject.get("E")->Value().get() == std::string("e2"));
        ENTLIB_ASSERT(setOfObject.get("E")->Name().get() == std::string("E"));

        // Test insert the __removed__ element get back the prefab values
        // insert => makeInstanceOf => __remove__ => insert
        //          => restore values since we dont know how to reset an element when saving
        ENTLIB_ASSERT(setOfObject.get("G").has_value() == false);
        setOfObject.add("G");
        ENTLIB_ASSERT(setOfObject.get("G")->Value().get() == std::string("g"));

        // Test remove entity
        auto subsceneCmp = *ent.Components().SubScene();
        // Removed : TestRemove. Added : PrettiestName, Entity
        ENTLIB_ASSERT(subsceneCmp.Embedded().size() == PrefabSubEntityCount + 1);

        // Test rename Entity
        ENTLIB_ASSERT(
            subsceneCmp.Embedded().get("PrettiestName")->Name() == std::string("PrettiestName"));

        // Test rename object in set
        ENTLIB_ASSERT(testSetOfObject.SetOfObject().get("A2")->Value().get() == std::string("a"));
        ENTLIB_ASSERT(testSetOfObject.SetOfObject().get("A").has_value() == false);

        // ****************************** Test hasASuper ******************************************
        // *************** ENTITY ***************
        auto subscene = *ent.Components().SubScene();
        // new entity
        auto ent2 = subscene.Embedded().get("Entity");
        ENTLIB_ASSERT(ent2.has_value());
        ENTLIB_ASSERT(ent2->hasOverride()); // Name is always overriden since it is alway declared
        // entity with override
        ent2 = subscene.Embedded().get("TestSaveEntWithOverride");
        ENTLIB_ASSERT(ent2.has_value());
        ENTLIB_ASSERT(ent2->hasOverride());
        // entity with instanceOf overriden
        ent2 = subscene.Embedded().get("EntityWithInstanceOfButNoOverride");
        ENTLIB_ASSERT(ent2.has_value());
        ENTLIB_ASSERT(ent2->getInstanceOf() == std::string("subentity2.entity"));
        ENTLIB_ASSERT(ent2->hasOverride());

        // *************** COMPONENT ***************
        // new Component (A new component is override true)
        ENTLIB_ASSERT(ent.Components().AnimationEventsGeneratorGD().has_value());
        ENTLIB_ASSERT(
            ent.Components().AnimationEventsGeneratorGD()->node->getParentNode()->hasOverride());
        // Component with override
        ENTLIB_ASSERT(ent.Components().VoxelSimulationGD().has_value());
        ENTLIB_ASSERT(ent.Components().VoxelSimulationGD()->LossBySecond().get() == 36.);
        ENTLIB_ASSERT(ent.Components().VoxelSimulationGD()->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = *ent.Components().CharacterControllerGD();
        ENTLIB_ASSERT(
            compWithInstOf.getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        ENTLIB_ASSERT(compWithInstOf.hasOverride());
        // *************** NODE ***************
        // new Node
        auto pathNodeGD = *ent.Components().TestSetOfObject();
        auto mapTest = pathNodeGD.MapOfObject();
        ENTLIB_ASSERT(mapTest.get("NewNode").has_value());
        // Newly inserted Nodes are overriden
        ENTLIB_ASSERT(mapTest.get("NewNode")->hasOverride());
        // Node with override
        ENTLIB_ASSERT(mapTest.get("OldNode1")->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest.get("OldNode1")->hasOverride());
        // Node with instanceOf overriden
        ENTLIB_ASSERT(mapTest.get("OldNode2")->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest.get("OldNode2")->hasOverride());

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(not heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST read overrided value
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // Inherited
        ENTLIB_ASSERT(sysCreat->Life().get() == 1000.); // Inherited

        // TEST read default value
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // Inherited (from default)
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default

        // TEST read programatically overrided in array
        ENTLIB_ASSERT(sysCreat->ScriptList()[1].get() == std::string("b1")); // No more overrided
        ENTLIB_ASSERT(not sysCreat->ScriptList()[1].isSet()); // No more overrided
        // TEST read programatically unset in array
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].get() == std::string("c2")); // Overrided
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].isSet()); // Overrided

        // TEST read programatically extand array
        ENTLIB_ASSERT(sysCreat->ScriptList()[3].get() == std::string("d2")); // Overrided
        ENTLIB_ASSERT(sysCreat->ScriptList()[3].isSet()); // Overrided

        // TEST read extanded array
        ENTLIB_ASSERT(sysCreat->ScriptList().isSet());
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 4);

        // TEST override value from code
        ENTLIB_ASSERT(sysCreat->BehaviorState().get() == std::string("Overrided")); // set. changed.
        ENTLIB_ASSERT(sysCreat->BehaviorState().isSet()); // set. changed.

        testInstanceOf(ent);

        ent.save("instance.copy.entity");
    }

    {
        // Test create detached
        auto entStorage = entlib.loadEntityAsNode("instance.entity");
        Ent::Gen::Entity ent(entStorage.get());

        auto detachedStorage = ent.node->detach();
        Ent::Gen::Entity detached(detachedStorage.get());

        ENTLIB_ASSERT(detached.Color().hasOverride());

        auto sysCreat = detached.Components().SystemicCreature();

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(not heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(not heightObj->Subdivision().hasDefaultValue()); // Prefab has value
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST default values
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // default
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default
        ENTLIB_ASSERT(sysCreat->Burried().hasDefaultValue()); // default
        ENTLIB_ASSERT(sysCreat->Name().get() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->Name().isSet()); // default

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Plouf")); // set
        ENTLIB_ASSERT(not sysCreat->Faction().hasDefaultValue()); // is set in instance
        ENTLIB_ASSERT(sysCreat->Faction().isSet()); // is set
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->Inventory().isSet()); // is set

        detached.save("instance.detached.entity");
    }
    {
        // Test read detached
        auto entStorage = entlib.loadEntityAsNode("instance.detached.entity");
        Ent::Gen::Entity ent(entStorage.get());

        auto sysCreat = ent.Components().SystemicCreature();

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST default values
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // default
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default
        ENTLIB_ASSERT(sysCreat->Name().get() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->Name().isSet()); // default

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Plouf")); // set
        ENTLIB_ASSERT(sysCreat->Faction().isSet()); // is set
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->Inventory().isSet()); // is set
    }

    {
        // Test makeInstanceOf
        auto instanceOfStorage = entlib.makeEntityNodeInstanceOf("prefab.entity");
        Ent::Gen::Entity instanceOf(instanceOfStorage.get());

        // Test instanciation of a prefab Node
        auto stickToTerrain = instanceOf.Components().addStickToTerrain();
        ENTLIB_CHECK_EXCEPTION(
            stickToTerrain.resetInstanceOf("C:/test.StickToTerrain.node"), std::runtime_error);
        stickToTerrain.resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain.resetInstanceOf(
            (current_path() / "test.StickToTerrain.node").generic_u8string().c_str());
        ENTLIB_ASSERT(stickToTerrain.getInstanceOf() != nullptr);
        stickToTerrain.NormalRatio().set(0.6);
        stickToTerrain.precisionRadius().set(0.6e-15);

        ENTLIB_ASSERT(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        ENTLIB_ASSERT(fabs(stickToTerrain.precisionRadius().get() - 0.6e-15) < 0.0000001);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isSet() == false);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        ENTLIB_ASSERT(instanceOf.Components().NetworkNode().has_value());
        instanceOf.save("instance.create.entity");
    }
    auto testCreateInstanceOf = [&entlib](char const* _instancePath)
    {
        // Test read instance of
        auto entStorage = entlib.loadEntityAsNode(_instancePath);
        Ent::Gen::Entity ent(entStorage.get());

        // Test instanciation of a prefab Node
        auto stickToTerrain = *ent.Components().StickToTerrain();
        ENTLIB_ASSERT(stickToTerrain.getInstanceOf() != nullptr);
        ENTLIB_ASSERT(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isSet() == false);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(not heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // Test read prefab
        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat.has_value());

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Shamans"));
        ENTLIB_ASSERT(not sysCreat->Faction().isSet()); // Not overrided
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey"));
        ENTLIB_ASSERT(not sysCreat->Inventory().isSet()); // Not overrided

        // TEST read array
        ENTLIB_ASSERT(sysCreat->ScriptList().isSet()); // Arrays are always set
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 3);

        // TEST default values
        ENTLIB_ASSERT(sysCreat->Burried().get() == false); // default
        ENTLIB_ASSERT(not sysCreat->Burried().isSet()); // default
        ENTLIB_ASSERT(sysCreat->Name().get() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->Name().isSet()); // default
    };
    testCreateInstanceOf("instance.create.entity");
    {
        // Test resetInstanceOf
        auto instanceOfStorage = entlib.makeEntityNode();
        Ent::Gen::Entity instanceOf(instanceOfStorage.get());
        instanceOf.Name().set("TestResetInstanceOf");

        instanceOf.resetInstanceOf("prefab.entity");
        ENTLIB_ASSERT(instanceOf.Components().NetworkNode().has_value());
        instanceOf.Components().TransformGD()->node->getFieldNames();

        // Test instanciation of a prefab Node
        auto stickToTerrain = instanceOf.Components().addStickToTerrain();
        stickToTerrain.resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain.NormalRatio().set(0.6);

        instanceOf.save("setInstanceOf.entity");
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
        auto entStorage = entlib.loadEntityAsNode("pinetreec50cmh5mbasic.entity");
        Ent::Gen::Entity ent(entStorage.get());
        ent.save("pinetreec50cmh5mbasic.copy.entity");
        auto entStorage2 = entlib.loadEntityAsNode("pinetreec50cmh5mbasic.copy.entity");
        Ent::Gen::Entity copyEnt(entStorage2.get());

        // TEST keeping empty component after entity save
        ENTLIB_ASSERT(copyEnt.Components().EventHandlerGD().has_value());
    }

    // ******************* Test the override of an entity in a SubScene ***************************
    auto testOverrideSubEntity = [](Ent::Gen::Entity ent)
    {
        auto subScenecomp = *ent.Components().SubScene();
        auto allSubEntities = subScenecomp.Embedded();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount);
        ENTLIB_ASSERT(subScenecomp.Embedded().get("EP1-Spout_LINK_001")->Color()[0].get() == 42);
    };
    {
        auto entStorage = entlib.loadEntityAsNode("instance_override_subentity.entity");
        Ent::Gen::Entity ent(entStorage.get());
        testOverrideSubEntity(ent);
        ent.save("instance_override_subentity.copy.entity");
        auto entStorage2 = entlib.loadEntityAsNode("instance_override_subentity.copy.entity");
        Ent::Gen::Entity copyEnt(entStorage2.get());
        testOverrideSubEntity(copyEnt);
    }

    // ******************* Test the add of an entity in a SubScene *****************************
    auto testAddSubEntity = [](Ent::Gen::Entity ent)
    {
        auto subScenecomp = *ent.Components().SubScene();
        auto allSubEntities = subScenecomp.Embedded();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount + 1);
        auto ent0 = subScenecomp.Embedded().get("EP1-Spout_LINK_001");
        auto ent1 = subScenecomp.Embedded().get("EP1-Spout_LINK_001_added");
        ENTLIB_ASSERT(ent0->Name() == std::string("EP1-Spout_LINK_001"));
        auto red = ent0->Color()[0];
        ENTLIB_ASSERT(not ent0->hasOverride());
        ENTLIB_ASSERT(red.get() == 255);
        ENTLIB_ASSERT(ent1->Name() == std::string("EP1-Spout_LINK_001_added"));
        ENTLIB_ASSERT(ent1->Color()[0].get() == 44);
    };
    {
        auto entStorage = entlib.loadEntityAsNode("instance_add_subentity.entity");
        Ent::Gen::Entity ent(entStorage.get());
        testAddSubEntity(ent);
        ent.save("instance_add_subentity.copy.entity");
        auto entStorage2 = entlib.loadEntityAsNode("instance_add_subentity.entity");
        Ent::Gen::Entity copyEnt(entStorage2.get());
        testAddSubEntity(copyEnt);
    }
    {
        // Test access subscene override
        auto entStorage = entlib.makeEntityNodeInstanceOf("entity-subscene.entity");
        Ent::Gen::Entity ent(entStorage.get());
        auto subs = *ent.Components().SubScene();

        ENTLIB_ASSERT(ent.hasOverride()); // makeInstanceOf does override the instanceOf
        ENTLIB_ASSERT(not subs.Embedded().empty());

        subs.Embedded().get("wolf_skeleton_lush")->Components().addActorGD().InSpiritWorld().set(true);
        ent.save("entity-subscene-override-saved.entity");

        auto entStorage2 = entlib.loadEntityAsNode("entity-subscene-override-saved.entity");
        Ent::Gen::Entity ovrdEntt(entStorage2.get());
        auto ovrdSubs = *ovrdEntt.Components().SubScene();

        //Test that we properly still have access to the prefab subscene entities
        ENTLIB_ASSERT(not ovrdSubs.Embedded().empty());
    }

    {
        auto entStorage = entlib.loadEntityAsNode(R"(Creature/my_creature_level2.entity)");
        Ent::Gen::Entity ent(entStorage.get());
        auto subscene = Ent::Gen::Entity(ent.Components().SubScene()->Embedded().node->at(0llu))
                            .Components()
                            .SubScene()
                            ->Embedded();
        ENTLIB_ASSERT(subscene.size() == 1);
        ENTLIB_ASSERT(strcmp(subscene.begin()->Name(), "default_level2") == 0);
    }

    // ******************* Test twice the same key in map *************************************
    {
        ENTLIB_CHECK_EXCEPTION(entlib.loadEntityAsNode("key_double.entity"), Ent::InvalidJsonData);
    }

    // ******************* Test the EntLibException ***********************************************
    {
        bool exceptionThrown = false;
        try
        {
            entlib.loadEntityAsNode("scene_with_invalid_entity.scene");
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
        auto entStorage = entlib.makeEntityNode();
        Ent::Gen::Entity ent(entStorage.get());
        ent.Name().set("TestDefaultColor");

        ENTLIB_ASSERT((std::array<double, 4>(ent.Color())) == (std::array<double, 4>{1., 1., 1., 1.}));
    }
    // ********************************** Test load/save scene ************************************
    entlib.rawdataPath = "X:/RawData";

    ENTLIB_LOG("Loading SceneWild.scene...");
    // auto scene = entlib.loadScene("X:/RawData/01_World/Wild/scenewild/editor/SceneWild.scene");
    entlib.validationEnabled = false;
    auto entStorage = entlib.loadEntityAsNode("20_scene/personal/simont/vfxGym/ScenevfxGym.scene");
    Ent::Gen::Entity sceneent(entStorage.get());
    auto scene = sceneent.Components().SubScene()->Embedded();

    ENTLIB_LOG("Done");

    if (doDisplayScene)
    {
        using namespace Ent;
        printfmt("Scene Loaded\n");
        printfmt("Entity count : %zu\n", scene.size());

        for (auto ent : scene)
        {
            printfmt("  Name \"%s\"\n", ent.Name());

            for (auto comp : ent.Components())
            {
                printfmt("    Type \"%s\"\n", comp.getType());
                printNode("", *comp.node->getUnionData(), "      ");
            }
        }
    }

    auto heightObj = scene.begin()->Components().addHeightObj();
    heightObj.DisplaceNoiseList().push();

    auto fieldNameCount = scene.begin()->Components().addHeightObj().node->getFieldNames().size();
    ENTLIB_ASSERT(fieldNameCount == 9);

    entlib.rawdataPath = current_path();
    scene.insertInstanceOf((current_path() / "prefab.entity").string().c_str());

    sceneent.save((current_path() / "SceneWild.test.scene").string().c_str());

    auto addedEntity = *scene.get("PlayerSpawner_");
    auto cinematicCmp = addedEntity.Components().CinematicGD();
    ENTLIB_ASSERT(cinematicCmp.has_value());

    // Test dumpNode
    if (dumpNodes)
    {
        Ent::printfmt("dumpNode(Override):\n");
        Ent::printfmt(
            "%s\n",
            cinematicCmp->node->toJson(Ent::OverrideValueSource::Override, true).dump(4).c_str());

        Ent::printfmt("dumpNode(OverrideOrPrefab):\n");
        Ent::printfmt(
            "%s\n",
            cinematicCmp->node->toJson(Ent::OverrideValueSource::OverrideOrPrefab, true).dump(4).c_str());

        Ent::printfmt("dumpNode(Any):\n");
        Ent::printfmt(
            "%s\n", cinematicCmp->node->toJson(Ent::OverrideValueSource::Any, true).dump(4).c_str());
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
