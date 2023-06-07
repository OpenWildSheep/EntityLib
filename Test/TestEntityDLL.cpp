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
#include <../cpp2/EntGen.h>
#include <ComponentMerge.h>

#include "TestCursor.h"

namespace Ent
{
    namespace Gen = Gen2;
}

using namespace Ent;

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
        catch (std::exception & ex)                                                                \
        {                                                                                          \
            ENTLIB_LOGIC_ERROR(                                                                    \
                "Wrong exception thrown! Expected : '%s', got '%s'\n%s",                           \
                #excep_type,                                                                       \
                typeid(ex).name(),                                                                 \
                ex.what());                                                                        \
        }                                                                                          \
        catch (...)                                                                                \
        {                                                                                          \
            ENTLIB_LOGIC_ERROR("Wrong exception thrown! Expected : %s");                           \
        }                                                                                          \
        ENTLIB_ASSERT_MSG(exception_throw, "Exception not thrown!");                               \
    }

// NOLINTNEXTLINE(readability-function-size)
int main(int argc, char** argv)
try
{
    SetConsoleOutputCP(65001);
    bool doTestRawData = false;
    std::filesystem::path rootPath = "X:";
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--rootPath") == 0)
        {
            ++i;
            ENTLIB_ASSERT(i < argc);
            rootPath = argv[i];
        }
        else if (strcmp(argv[i], "--test-raw_data") == 0)
        {
            doTestRawData = true;
        }
    }

    if (rootPath.native().back() != L'/' || rootPath.native().back() != L'\\')
    {
        rootPath = (rootPath.native() + L'/');
    }
    std::filesystem::path rawdataPath = rootPath / "RawData";

    EntityLib entlib(rawdataPath, rootPath / "Tools/WildPipeline/Schema");
    using namespace std::filesystem;

    entlib.setLogicErrorPolicy(LogicErrorPolicy::Throw);
    ENTLIB_CHECK_EXCEPTION(ENTLIB_LOGIC_ERROR("Test logic error"), std::logic_error);
    entlib.setLogicErrorPolicy(LogicErrorPolicy::Terminate);

    entlib.rawdataPath = current_path(); // It is a hack to work in the working dir
#ifdef _DEBUG
    entlib.validationEnabled = false;
#else
    entlib.validationEnabled = true;
#endif

    auto prevValidationEnabled = entlib.validationEnabled;
    entlib.validationEnabled = false;
    testCursor(entlib, rawdataPath, doTestRawData);
    entlib.rawdataPath = current_path();
    entlib.validationEnabled = prevValidationEnabled;

    {
        auto ent = Gen::Entity::create(entlib);
        ent.save("test_output/test_create.entity");
        Gen::Entity::load(entlib, "test_output/test_create.entity");
    }
    {
        auto ent = entlib.newProperty(entlib.getSchema("Entity"));
        ent.save("test_output/test_create2.entity");
        entlib.loadProperty("test_output/test_create2.entity");
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto strings = ent.Components().UnitTestComponent()->SimpleArray();
        ENTLIB_ASSERT(strings.getPrefab()->size() == 5);
        ENTLIB_ASSERT(strings.size() == 5);
        auto cel2 = strings[2].getProperty();
        cel2.setString("test4851");
        ENTLIB_ASSERT(strings.getPrefab()->size() == 5);
        ENTLIB_ASSERT(strings.size() == 5);
    }
    {
        // getInstanceOf in union
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.entity");
        auto prop = ent.Components()
                        .ScriptComponentGD()
                        ->ScriptsMap()
                        .get("CloudStorm")
                        ->DataMap()
                        .get("BlendDurationIn")
                        ->Value()
                        .getProperty();
        auto unionInstanceOf = prop.getInstanceOf();
        ENTLIB_ASSERT(unionInstanceOf == std::string_view("BlendDurationIn.node"));
    }
    {
        // Check re-insertion of a deleted map item (avoid to create a 2nd json item)
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto commonDataMap = ent.Components().ScriptComponentGD()->CommonDataMap();
        ENTLIB_ASSERT(commonDataMap.get("NbBeams").has_value());
        [[maybe_unused]] auto nbbeams = commonDataMap.get("NbBeams");
        commonDataMap.remove("NbBeams");
        ENTLIB_ASSERT(not commonDataMap.get("NbBeams").has_value());
        auto nbbeams2 = commonDataMap.add("NbBeams");
        ENTLIB_ASSERT(commonDataMap.get("NbBeams").has_value());
        nbbeams2.unset(); // Do not remove it since it is present in prefab
        ENTLIB_ASSERT(commonDataMap.get("NbBeams").has_value());
    }
    {
        // Check the visitor, in case of map of primitive
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto detached = ent.detach();
        auto speed2 = detached.Components().TestSetOfObject()->MapOfPrimitive().get("speed2");
        ENTLIB_ASSERT(speed2.has_value());
    }
    {
        // Test unset
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        // On unionset
        auto netGD = ent.Components().addNetGD(); // exist in prefab but not in instance
        ENTLIB_ASSERT(netGD.isSet());
        netGD.unset();
        ENTLIB_ASSERT(netGD.isSet() == false);
        // On objectset
        auto subent = ent.Components().SubScene()->Embedded().add(
            "EP1-Spout_LINK_001"); // exist in prefab but not in instance
        ENTLIB_ASSERT(subent.isSet());
        subent.unset();
        ENTLIB_ASSERT(subent.isSet() == false);
        // On map
        auto mapitem = ent.Components().TestSetOfObject()->MapOfObject().add(
            "OldNode1"); // exist in prefab but not in instance
        ENTLIB_ASSERT(mapitem.isSet());
        mapitem.unset();
        ENTLIB_ASSERT(mapitem.isSet() == false);
        ent.save("output/check_unset_output.entity");
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        // unset - unset children
        auto comp = ent.Components();
        ENTLIB_ASSERT(comp.isSet());
        auto embedded = comp.SubScene()->Embedded();
        ENTLIB_ASSERT(embedded.isSet());
        auto subent = *embedded.get("EntityWithInstanceOf");
        ENTLIB_ASSERT(subent.isSet());
        comp.unset();
        ENTLIB_ASSERT(comp.isSet() == false);
        ENTLIB_ASSERT(embedded.isSet() == false);
        ENTLIB_ASSERT(subent.isSet() == false);
        // set - set parent
        comp = ent.Components();
        embedded = comp.SubScene()->Embedded();
        subent = *embedded.get("EntityWithInstanceOf");
        comp = ent.Components(); // Make a clone of the real parent
        embedded = comp.SubScene()->Embedded();
        ENTLIB_ASSERT(comp.isSet() == false);
        ENTLIB_ASSERT(embedded.isSet() == false);
        ENTLIB_ASSERT(subent.isSet() == false);
        subent.Color()[0] = 3;
        ENTLIB_ASSERT(subent.isSet());
        ENTLIB_ASSERT(embedded.isSet());
        ENTLIB_ASSERT(comp.isSet());
        // Remove component in prefab and still use the instance Prop of component
        ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        ENTLIB_ASSERT(ent.getPrefab().has_value());
        comp = ent.Components();
        ENTLIB_ASSERT(comp.getPrefab().has_value());
        auto instNetworkNode = comp.SmoothScaleComponentGD();
        ENTLIB_ASSERT(instNetworkNode->getPrefab().has_value());
        auto prefab = Gen::Entity::load(entlib, "prefab.entity");
        ENTLIB_ASSERT(comp.SmoothScaleComponentGD().has_value());
        ENTLIB_ASSERT(instNetworkNode->getPrefab().has_value());
        prefab.Components().removeSmoothScaleComponentGD();
        ENTLIB_ASSERT(comp.SmoothScaleComponentGD().has_value() == false);
        ENTLIB_ASSERT(instNetworkNode->getSchema() == nullptr);
        instNetworkNode.reset();
    }

    ENTLIB_ASSERT(Ent::format("Toto %d", 37) == "Toto 37");

    {
        std::map<std::string, int> emptyMap;
        ENTLIB_CHECK_EXCEPTION(AT(emptyMap, "not"), Ent::InvalidKey);
    }

    // Test $ref links in entlib.schema.schema.allDefinitions
    auto const* colorRef = "Color";
    ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(colorRef) == 1);

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
        // Check insert a key which is an enum, but with a wrong value.
        auto ent = Gen::Entity::create(entlib);
        auto map = ent.Components()
                       .addAnimationModelGD()
                       .additionalSpeedDebug()
                       .get(Gen::LocomotionModeEnum::buried)
                       ->getProperty();
        ENTLIB_CHECK_EXCEPTION(map.insertMapItem("test"), BreakSchemaRules)
    }
    {
        auto ent = Gen::SeedPatchDataList::loadCopy(entlib, "myseedpatchMarianne.seedpatchdata.node");
        ent.save("myseedpatchMarianne.seedpatchdata.copy.node");
    }
    {
        // Check getPrefab when all prefabs are unset (should not null)
        auto ent = Gen::Entity::create(entlib).makeInstanceOf();
        auto entProp = ent.getProperty();
        auto color = entProp.getObjectField("Color");
        ENTLIB_ASSERT(color.getPrefab().has_value());
        auto red = color.getArrayItem(0);
        ENTLIB_ASSERT(red.getPrefab().has_value());
    }
    {
        // When there is a $schema field
        auto node = entlib.loadProperty("myseedpatch_schema.node");
        ENTLIB_ASSERT(node.getSchema() == entlib.getSchema("SeedPatchDataList"));
        // When there is a $schema field with different style
        node = entlib.loadProperty("myseedpatch_schema_style.node");
        ENTLIB_ASSERT(node.getSchema() == entlib.getSchema("SeedPatchDataList"));
        // No $schema, no .entity, wrong pre-extention
        ENTLIB_CHECK_EXCEPTION(
            entlib.loadProperty("test.ThisTypeDoesntExist.node"), Ent::UnknownSchema);
    }
    {
        auto node = entlib.loadProperty("Entity", "instance.entity");
        auto prefabHisto = getPrefabHistory(node);
    }
    // Temporarily disable validation to read some RawData files
    entlib.validationEnabled = false;

    if (doTestRawData)
    {
        entlib.rawdataPath = rawdataPath; // It is a hack to work in the working dir

        {
            auto node = Property(
                &entlib,
                entlib.getSchema("Entity"),
                "20_Scene/KOM2021/SubScenesKOM/FindWolvesRegenBubble/"
                "FindWolvesRegenBubbleMain/editor/FindWolvesRegenBubbleMain.scene");

            auto const* falseNodeRef = "Components/SubScene/Embedded/XXXXX";
            auto nullNode = node.resolveNodeRef(falseNodeRef);
            ENTLIB_ASSERT(nullNode.has_value() == false);
            auto const* nodeRef = "Components/SubScene/Embedded/ShamanFullBlue_ent_001";
            auto ent = node.resolveNodeRef(nodeRef);
            auto entpath = node.makeNodeRef(*ent);
            ENTLIB_ASSERT(entpath == nodeRef);
            entpath = ent->makeAbsoluteNodeRef();
            ENTLIB_ASSERT(entpath == nodeRef);
            entpath = node.makeAbsoluteNodeRef();
            ENTLIB_ASSERT(entpath == ".");

            auto prefabHisto = getPrefabHistory(*ent);
            ENTLIB_ASSERT(prefabHisto.size() == 8);
            ENTLIB_ASSERT(
                prefabHisto[3].prefabPath == "02_creature/human/male/entity/legacy/human_male.entity");
            ENTLIB_ASSERT(
                prefabHisto[4].prefabPath
                == "02_Creature/Human/MALE/Entity/validate/ShamanFullBlue.entity");
            ENTLIB_ASSERT(
                prefabHisto[7].prefabPath
                == "20_Scene/KOM2021/SubScenesKOM/FindWolvesRegenBubble/"
                   "FindWolvesRegenBubbleMain/editor/FindWolvesRegenBubbleMain.scene");
        }
        {
            auto node = entlib.loadPropertyCopy(
                "Entity",
                "20_Scene/KOM2021/SubScenesKOM/FindWolvesRegenBubble/"
                "FindWolvesRegenBubbleMain/editor/FindWolvesRegenBubbleMain.scene");
            auto const* nodeRef = "Components/SubScene/Embedded/ShamanFullBlue_ent_001";
            auto ent = node.resolveNodeRef(nodeRef);
            auto entpath = node.makeNodeRef(*ent);
            ENTLIB_ASSERT(entpath == nodeRef);
            entpath = ent->makeAbsoluteNodeRef();
            ENTLIB_ASSERT(entpath == nodeRef);
            entpath = node.makeAbsoluteNodeRef();
            ENTLIB_ASSERT(entpath == ".");

            auto prefabHisto = getPrefabHistory(*ent);
            ENTLIB_ASSERT(prefabHisto.size() == 7);
            ENTLIB_ASSERT(
                prefabHisto[3].prefabPath == "02_creature/human/male/entity/legacy/human_male.entity");
            ENTLIB_ASSERT(
                prefabHisto[4].prefabPath
                == "02_Creature/Human/MALE/Entity/validate/ShamanFullBlue.entity");
        }
        {
            auto node = entlib.loadPropertyCopy(
                "Entity",
                "20_Scene/KOM2021/SubScenesKOM/FindWolvesRegenBubble/"
                "FindWolvesRegenBubbleMain/editor/FindWolvesRegenBubbleMain.scene");
            auto const* nodeRef =
                R"(Components/SubScene/Embedded/ShamanFullBlue_ent_001/Components/TransformGD)";
            auto ent = node.resolveNodeRef(nodeRef);
            auto entpath = node.makeNodeRef(*ent);
            ENTLIB_ASSERT(entpath == nodeRef);
            auto prefabHisto = getPrefabHistory(*ent);
            ENTLIB_ASSERT(
                prefabHisto[3].prefabPath == "02_creature/human/male/entity/legacy/human_male.entity");
            ENTLIB_ASSERT(
                prefabHisto[4].prefabPath
                == "02_Creature/Human/MALE/Entity/validate/ShamanFullBlue.entity");
        }

        entlib.rawdataPath = current_path(); // Work in Test dir
    }

    entlib.validationEnabled = prevValidationEnabled;
    {
        auto node = entlib.loadPropertyCopy("Entity", "instance.entity");
        auto const* nodeRef =
            R"(Components/SubScene/Embedded/EP1-Spout_LINK_001/Components/NetworkLink)";
        auto ent = node.resolveNodeRef(nodeRef);
        auto entpath = node.makeNodeRef(*ent);
        ENTLIB_ASSERT(entpath == nodeRef);
        auto nullPath = ent->makeNodeRef(*ent);
        ENTLIB_ASSERT(nullPath.empty() or nullPath == ".");
        // Test Union
        auto typedValueUnion = node.getObjectField("Components")
                                   .insertUnionSetItem("ScriptComponentGD")
                                   .getObjectField("CommonDataMap")
                                   .insertMapItem("Test")
                                   .getObjectField("Value");
        auto const* typeValueRef = R"(Components/ScriptComponentGD/CommonDataMap/Test/Value)";
        ENTLIB_ASSERT(node.makeNodeRef(typedValueUnion) == typeValueRef);
        auto stringUnionData = typedValueUnion.setUnionType("string");
        auto const* strRef = R"(Components/ScriptComponentGD/CommonDataMap/Test/Value/string)";
        ENTLIB_ASSERT(node.makeNodeRef(stringUnionData) == strRef);
        ENTLIB_ASSERT(typedValueUnion.makeNodeRef(stringUnionData) == "string");
    }
    auto testPrefabEntity = [&entlib](Gen::Entity ent)
    {
        // ActorStates
        auto actorStates = ent.ActorStates();
        ENTLIB_ASSERT(actorStates.getProperty().getDataKind() == Ent::DataKind::unionSet);
        ENTLIB_ASSERT(actorStates.size() == 2);
        auto actorState = actorStates.ActorStateHoldingItem();
        ENTLIB_ASSERT(actorState.has_value());
        static_assert(std::is_same_v<decltype(*actorState), Gen::ActorStateHoldingItem&>);
        ENTLIB_ASSERT(actorState->getProperty().hasValue());
        auto exitRequired = actorState->ItemEntityRef();
        ENTLIB_ASSERT(exitRequired.getProperty().hasValue());
        ENTLIB_ASSERT(exitRequired.get().entityPath == std::string("tutu"));
        auto entityStatePlayerData = actorStates.EntityStatePlayer();
        ENTLIB_ASSERT(entityStatePlayerData.has_value());

        // Map and Set overridePolicy
        auto pathNodeGD = ent.Components().TestTagsList();
        auto tags = pathNodeGD->Tags().Tags();
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(tags.get("a").has_value());
        ENTLIB_ASSERT(tags.get("c").has_value());
        ENTLIB_ASSERT(tags.get("c")->size() == 1);
        ENTLIB_ASSERT(tags.get("c")->count("2"));
        // Test get on map and set
        ENTLIB_ASSERT(tags.get("a")->count("1"));

        ENTLIB_ASSERT(tags.getProperty().getMapKeyKind() == Ent::DataKind::string);
        auto keys = tags.getKeys();
        ENTLIB_ASSERT(keys.size() == 3);
        for (auto&& k : keys)
        {
            ENTLIB_ASSERT(tags.get(k).has_value());
        }

        // Test default value
        auto testDefaultValues = ent.Components().TestDefaultValues();
        ENTLIB_ASSERT(testDefaultValues->DoubleWithDefaultValue().get() == 1.23456);
        ENTLIB_ASSERT(testDefaultValues->DoubleWithDefaultValue().isDefault());
        ENTLIB_ASSERT(testDefaultValues->schemaName == std::string("TestDefaultValues"));

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(not heightObj->Subdivision().isDefault());
        ENTLIB_ASSERT(heightObj->Subdivision().getDefault() == 3);
        ENTLIB_ASSERT(
            heightObj->Subdivision().getProperty().getSchema()->userMeta["testUserMetatdata"].get<int>()
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

        // TEST subScenecomp
        auto subent = allSubEntities.get("EP1-Spout_LINK_001");
        auto parent = entlib.getParentEntity(subent->getProperty());
        ENTLIB_ASSERT(parent.has_value() and *parent == ent.getProperty());
        ENTLIB_ASSERT(entlib.getParentEntity(ent.getProperty()).has_value() == false);

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
        ENTLIB_ASSERT(testDefaultValues.has_value());
        auto propertyWithDefault = testDefaultValues->propertyWithDefault();
        auto propertyWithDefault2 = propertyWithDefault.propertyWithDefault2();
        ENTLIB_ASSERT(propertyWithDefault2.A().get() == 3);
        ENTLIB_ASSERT(propertyWithDefault2.B().get() == 0);
        auto propertyWithDefault3 = propertyWithDefault.propertyWithDefault3();
        ENTLIB_ASSERT(propertyWithDefault3.A().get() == 3);
        ENTLIB_ASSERT(propertyWithDefault3.B().get() == 0);

        // Test Property's InstanceOf
        auto seedPatch = ent.Components().SeedPatch();
        ENTLIB_ASSERT(seedPatch->NoiseSizeX().get() == 1.);
        ENTLIB_ASSERT(seedPatch->NoiseSizeY().get() == 2.);
        ENTLIB_ASSERT(seedPatch->NoiseOffsetX().get() == 2.);
    };

    {
        auto ent = Gen::Entity::create(entlib);
        ent.Name() = "TestResetInstanceOf";
        ent.resetInstanceOf("prefab.entity");
        ENTLIB_ASSERT(ent.hasOverride()); // resetInstanceOf does override the "instanceOf"
        ENTLIB_ASSERT(ent.getInstanceOf() == std::string("prefab.entity"));
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "missing_embedded.entity");
        ENTLIB_ASSERT(ent.Components().size() == 1); // Contains only SubScene
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.entity");

        // Test title/description
        /*
        {
            auto const* rigodBodyCoeffSchema = ent.Components()
                                                   .CharacterControllerGD()
                                                   ->HeadCollisionData()
                                                   .softCollisionRigidbodyCoeff()
                                                   .getSchema();
            ENTLIB_ASSERT(rigodBodyCoeffSchema->title.find("Rigidbody") != std::string::npos);
            ENTLIB_ASSERT(rigodBodyCoeffSchema->description.find("rigidbody") != std::string::npos);
        }
        */

        auto setOfObject = ent.Components().TestSetOfObject();
        ENTLIB_ASSERT(setOfObject);
        auto mapTest = setOfObject->MapOfObject();
        auto testParent = mapTest.add("Should_not_appear_in_diff");
        ENTLIB_ASSERT(
            testParent.getProperty().getParent()->getDataKind() == DataKind::map); // parent is the map
        ENTLIB_ASSERT(testParent.getProperty().getParent()->isMapOrSet());
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
        ENTLIB_ASSERT(testArrays->Variant().float_().has_value());
        ENTLIB_ASSERT(testArrays->Variant().float_()->get() == 3.1416);
        nlohmann::json const* withoutIndex = testArrays->Variant().getRawJson();
        ENTLIB_ASSERT(withoutIndex->count("variantIndex") == 0);
        ENTLIB_ASSERT(withoutIndex->at("variantType").get_ref<std::string const&>() == "float");

        // Test saveNode
        auto heightObj = ent.Components().HeightObj();
        heightObj->getProperty().save("test.HeightObj.node");

        testPrefabEntity(ent);
        // Test mapErase in set of primitive
        auto pathNodeGD = ent.Components().TestTagsList();
        pathNodeGD = pathNodeGD->makeInstanceOf(); // erasePrimSetKey fail only if key exist in prefab
        auto tags = pathNodeGD->Tags().Tags();
        auto primSet = tags.get("a");
        ENTLIB_ASSERT(primSet->getProperty().getParent()->getDataKind() == DataKind::map);
        ENTLIB_CHECK_EXCEPTION(primSet->getProperty().erasePrimSetKey("1"), Ent::BadArrayType);

        // TEST simple entity ref creation
        auto testEntityRef = ent.Components().addTestEntityRef();
        ENTLIB_ASSERT(testEntityRef.TestRef().get().entityPath.empty());
        testEntityRef.TestRef().set(entlib.makeEntityRef(ent.getProperty(), ent.getProperty()));
        ENTLIB_ASSERT(testEntityRef.TestRef().get().entityPath == ".");
        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        testEntityRef.TestRef().set(
            entlib.makeEntityRef(ent.getProperty(), allSubEntities.begin()->getProperty()));

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
        ENTLIB_ASSERT(not newUnion.getProperty().getUnionData().hasOverride());
        ENTLIB_ASSERT(newUnion.getType() == std::string("s32"));
        // TEST Union not in Object in Array
        auto obj = testUnion.UnionObjectArray().push();
        newUnion = obj.Union();
        ENTLIB_ASSERT(not newUnion.getProperty().getUnionData().hasOverride());
        ENTLIB_ASSERT(newUnion.getType() == std::string("s32"));
        // Test getUnionTypesMap
        auto&& nameToTypeMap = newUnion.getSchema()->getUnionTypesMap();
        ENTLIB_ASSERT(size(nameToTypeMap) == 8);
        ENTLIB_ASSERT(nameToTypeMap.count("s32") == 1);
        ENTLIB_ASSERT(nameToTypeMap.count("float") == 1);
        ENTLIB_ASSERT(nameToTypeMap.count("Vector3") == 1);

        // TEST MaxActivationLevel
        ent.MaxActivationLevel().set(Gen::MaxActivationLevelEnum::InWorld);

        auto sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat->Name().get() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->Name().isSet()); // default
        sysCreat->Name().set("Shamane_male");
        ent.save("prefab.copy.entity");

        // TEST SubScene detach
        auto originalSubEntities = ent.Components().SubScene()->Embedded();
        ENTLIB_ASSERT(not originalSubEntities.empty());
        ent.Components().SubScene()->Embedded().clear();
        ENTLIB_ASSERT(ent.Components().SubScene()->Embedded().empty());

        ent.Components().removeSubScene();
        ent.save("prefab.emptyembbeded.entity");

        // TEST arrays default values
        ent.Components().removeTransformGD();
        auto transformGD = ent.Components().addTransformGD();
        auto mat33 = transformGD.Matrix();
        auto testMat33 = [&]
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
        ENTLIB_ASSERT(testDefaultValues.getProperty().getParent()->hasOverride());
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
        auto ent = Gen::Entity::loadCopy(entlib, "instance_arrays.entity");
        ENTLIB_ASSERT(ent.hasPrefabValue());

        auto comp = ent.Components().TestArrays();
        ENTLIB_ASSERT(comp);
        auto const testArrayMember = [&](char const* _arrayName,
                                         size_t defaultSize,
                                         std::optional<size_t> prefabSize,
                                         std::optional<size_t> overrideSize)
        {
            auto const node = comp->getProperty().getObjectField(_arrayName);
            ENTLIB_ASSERT(node.hasValue());
            ENTLIB_ASSERT(node.hasPrefabValue() == prefabSize.has_value());
            ENTLIB_ASSERT(node.hasOverride() == overrideSize.has_value());
            ENTLIB_ASSERT(node.getDefaultSize() == defaultSize);
            ENTLIB_ASSERT(node.getPrefabSize() == prefabSize);
            if (not overrideSize.has_value())
            {
                ENTLIB_ASSERT(not node.isSet());
            }
            else
            {
                ENTLIB_ASSERT(node.size() == overrideSize);
            }
        };
        testArrayMember("DefaultValue", 2, std::nullopt, std::nullopt);
        testArrayMember("PrefabValue", 2, 4, std::nullopt);
        testArrayMember("OverridedDefaultValue", 2, std::nullopt, 3);
        testArrayMember("OverridedPrefabValue", 2, 4, 3);
    }
    {
        // Test the readOnly prefab.entity
        testPrefabEntity(Gen::Entity::loadCopy(entlib, "prefab.entity"));
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.copy.entity");
        auto const newNodeCachesize = entlib.getJsonDatabase().size();
        auto testEntityRef = ent.Components().TestEntityRef();
        ENTLIB_ASSERT(testEntityRef.has_value());
        ENTLIB_ASSERT(testEntityRef->TestRef().isSet());
        EntityRef entityRef = testEntityRef->TestRef().get();
        auto resolvedEntity = entlib.resolveEntityRef(ent.getProperty(), entityRef);
        ENTLIB_ASSERT(resolvedEntity.has_value());

        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        ENTLIB_ASSERT(not allSubEntities.empty());
        auto originalEnt = allSubEntities.begin();
        ENTLIB_ASSERT(resolvedEntity == originalEnt->getProperty());

        auto newSubEnt = allSubEntities.add("prefab.entity");
        ENTLIB_CHECK_EXCEPTION(newSubEnt.Name().set("newSubEnt"), CantRename);

        auto embedded = ent.Components().SubScene()->Embedded();
        embedded.insertInstanceOf("prefab.entity");
        ENTLIB_ASSERT(embedded.get("PlayerSpawner_")->Name() == std::string("PlayerSpawner_"));
    }

    {
        // Test write prefab
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.copy.entity");

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
        EntityRef entityRef = testEntityRef->TestRef().get();
        auto resolvedEntity = entlib.resolveEntityRef(ent.getProperty(), entityRef);
        ENTLIB_ASSERT(resolvedEntity.has_value());

        auto subScenecomp = *ent.Components().SubScene();
        auto allSubEntities = subScenecomp.Embedded();
        ENTLIB_ASSERT(not allSubEntities.empty());
        auto originalEnt = allSubEntities.begin()->getProperty();
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
        auto ent = Gen::Entity::loadCopy(entlib, "entity-references.scene");
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
        EntityRef BToInstanceOfAref =
            entlib.makeEntityRef(B.getProperty(), instanceOfA.getProperty());
        ENTLIB_ASSERT(BToInstanceOfAref.entityPath == "..");
        EntityRef InstanceOfAToBref =
            entlib.makeEntityRef(instanceOfA.getProperty(), B.getProperty());
        ENTLIB_ASSERT(InstanceOfAToBref.entityPath == "B");
        EntityRef CToBref = entlib.makeEntityRef(C.getProperty(), B.getProperty());
        ENTLIB_ASSERT(CToBref.entityPath == "../InstanceOfA/B");
        EntityRef BToCref = entlib.makeEntityRef(B.getProperty(), C.getProperty());
        ENTLIB_ASSERT(BToCref.entityPath == "../../C");

        // TEST entity ref resolution
        auto resolvedEmptyRef = entlib.resolveEntityRef(instanceOfA.getProperty(), {});
        ENTLIB_ASSERT(not resolvedEmptyRef.has_value());
        auto resolvedInstanceOfA = entlib.resolveEntityRef(B.getProperty(), {".."});
        ENTLIB_ASSERT(resolvedInstanceOfA == instanceOfA.getProperty());
        auto resolvedB = entlib.resolveEntityRef(instanceOfA.getProperty(), {"B"});
        ENTLIB_ASSERT(resolvedB == B.getProperty());
        auto resolvedBbis = entlib.resolveEntityRef(C.getProperty(), {"../InstanceOfA/B"});
        ENTLIB_ASSERT(resolvedBbis == B.getProperty());
        auto resolvedC = entlib.resolveEntityRef(B.getProperty(), {"../../C"});
        ENTLIB_ASSERT(resolvedC == C.getProperty());

        // TEST entity ref resolution from scenes
        ENTLIB_ASSERT(not entlib.resolveEntityRef(scene.getProperty(), {".."}).has_value());
        ENTLIB_ASSERT(
            entlib.resolveEntityRef(scene.getProperty(), {"InstanceOfA"})
            == instanceOfA.getProperty());
        ENTLIB_ASSERT(
            entlib.resolveEntityRef(scene.getProperty(), {"InstanceOfA/B"}) == B.getProperty());
        ENTLIB_ASSERT(entlib.resolveEntityRef(scene.getProperty(), {"C"}) == C.getProperty());
        ENTLIB_ASSERT(
            entlib.resolveEntityRef(scene.getProperty(), {"InstanceOfA/B/../../C"})
            == C.getProperty());
    }

    auto testInstanceOf = [](Gen::Entity const& ent, bool testIsSet = true, bool testPrefab = true)
    {
        // ActorStates
        auto actorStates = ent.ActorStates();
        ENTLIB_ASSERT(actorStates.getDataKind() == Ent::DataKind::unionSet);
        ENTLIB_ASSERT(actorStates.size() == 3);
        auto climbEdge = actorStates.ActorStateHoldingItem();
        ENTLIB_ASSERT(climbEdge.has_value());
        ENTLIB_ASSERT(climbEdge->getProperty().getParent() == actorStates.getProperty());
        auto exitRequired = climbEdge->ItemEntityRef();
        // ENTLIB_ASSERT(exitRequired.hasValue());
        ENTLIB_ASSERT(exitRequired.get().entityPath == std::string("tutu"));
        auto dead = actorStates.ActorStateDead();
        ENTLIB_ASSERT(dead.has_value());
        auto deadData = *dead;
        auto actorStateHoldingItem = actorStates.ActorStateHoldingItem();
        ENTLIB_ASSERT(actorStateHoldingItem.has_value());
        auto itemEntityRef = actorStateHoldingItem->ItemEntityRef();
        ENTLIB_ASSERT(itemEntityRef.get().entityPath == "tutu");

        // Map and Set overridePolicy
        auto pathNodeGD = *ent.Components().TestTagsList();
        auto tags = pathNodeGD.Tags().Tags();
        ENTLIB_ASSERT(tags.getProperty().getParent()->getParent().value() == pathNodeGD.getProperty());
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(tags.get("a")->getProperty().getParent() == tags.getProperty());
        ENTLIB_ASSERT(tags.get("a")->getProperty().hasValue());
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

        // "InstanceOf" in sub entitites
        auto entityWithInstanceOf = *subScene->Embedded().get(R"(EntityWithInstanceOf)");
        ENTLIB_ASSERT(entityWithInstanceOf.Name() == std::string("EntityWithInstanceOf"));
        if (auto const* instOf = entityWithInstanceOf.getProperty().getInstanceOf())
        {
            ENTLIB_ASSERT(instOf == std::string("subentity2.entity"));
        }
        else
        {
            ENTLIB_ASSERT(
                entityWithInstanceOf.getProperty().getPrefab()->getInstanceOf()
                == std::string("subentity2.entity"));
        }
        auto networkLink = *entityWithInstanceOf.Components().NetworkLink();
        ENTLIB_ASSERT(networkLink.Source().get() == std::string("instance"));
        ENTLIB_ASSERT(networkLink.Target().get() == std::string("subentity2"));
        ENTLIB_ASSERT(networkLink.ThumbnailMesh().get() == std::string());

        // Test instanciation of a prefab Property
        auto stickToTerrain = *ent.Components().StickToTerrain();
        if (testPrefab)
        {
            if (stickToTerrain.getInstanceOf() == nullptr)
            {
                ENTLIB_ASSERT(stickToTerrain.getProperty().getPrefab()->getInstanceOf() != nullptr);
                ENTLIB_ASSERT(
                    stickToTerrain.getProperty().getPrefab()->getInstanceOf()
                    == std::string("test.StickToTerrain.node"));
            }
            else
            {
                ENTLIB_ASSERT(stickToTerrain.getInstanceOf() != nullptr);
                ENTLIB_ASSERT(
                    stickToTerrain.getInstanceOf() == std::string("test.StickToTerrain.node"));
            }
        }
        ENTLIB_ASSERT(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isSet() == false);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        // Test PRoperty's InstanceOf
        auto seedPatch = *ent.Components().SeedPatch();
        ENTLIB_ASSERT(seedPatch.NoiseSizeX().isDefault());
        ENTLIB_ASSERT(seedPatch.NoiseSizeY().get() == 3.);
        ENTLIB_ASSERT(not seedPatch.NoiseOffsetX().isSet());
        ENTLIB_ASSERT(seedPatch.NoiseOffsetY().get() == 3.);
    };

    {
        // Test applyToPrefab

        // Prepare data
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto entJson = *ent.getProperty().getRawJson();
        entJson["InstanceOf"] = "prefab_updated.entity";
        {
            std::ofstream outEnt("instance_applied.entity");
            outEnt << entJson.dump(4);
        }
        copy_file("prefab.entity", "prefab_updated.entity", copy_options::overwrite_existing);

        // Do the applyToPrefab
        ent = Gen::Entity::loadCopy(entlib, "instance_applied.entity");
        ent.getProperty().applyToPrefab();
        auto actorStates = ent.ActorStates();
        ent.save("instance_applied.entity");
        Property prefab(&entlib, entlib.getSchema(Gen::Entity::schemaName), "prefab_updated.entity");

        // Test result
        testInstanceOf(Gen::Entity(prefab), false);
        testInstanceOf(ent, false);
        ENTLIB_ASSERT(ent.hasOverride()); // Because applyToPrefab set the old name

        ent = Gen::Entity::loadCopy(entlib, "instance_applied.entity");
        testInstanceOf(ent, false);
        ENTLIB_ASSERT(ent.hasOverride()); // Because applyToPrefab set the old name
    }

    {
        // ***** Test loadProperty without schemaName *****
        // File without $schema inside
        ENTLIB_CHECK_EXCEPTION(entlib.loadProperty("instance.entity"), Ent::UnknownSchema);
        // File with $schema inside
        auto ent = entlib.loadProperty("instance3.entity");
        ENTLIB_ASSERT(ent.getSchema()->name == "Entity");
    }
    {
        // Test read instance of
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
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
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].get() == std::string("c2")); // Overrided
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].isSet()); // Overrided

        // TEST read array
        ENTLIB_ASSERT(sysCreat->ScriptList().isSet());
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 3);

        // TEST Extand array
        sysCreat->ScriptList().push().set("d2");
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].get() == std::string("c2")); // Overrided
        ENTLIB_ASSERT(sysCreat->ScriptList()[2].isSet()); // Overrided
        ENTLIB_ASSERT(sysCreat->ScriptList().size() == 4);

        // TEST SubScene (without override)
        testInstanceOf(ent);

        auto testSetOfObject = *ent.Components().TestSetOfObject();
        {
            auto setOfObject = testSetOfObject.SetOfObject();

            // Test hasOverride
            ENTLIB_ASSERT(setOfObject.get("C")->hasOverride() == false); // Already in prefab
            ENTLIB_ASSERT(setOfObject.get("A")->hasOverride()); // new in instance

            // Test remove object in set
            ENTLIB_ASSERT(setOfObject.size() == 6);
            ENTLIB_ASSERT(setOfObject.remove("B"));
            ENTLIB_ASSERT(not setOfObject.contains("B"));
            ENTLIB_ASSERT(setOfObject.remove("C"));
            ENTLIB_ASSERT(not setOfObject.contains("C"));
            ENTLIB_ASSERT(setOfObject.size() == 4);

            // Test override object in set (especially override name)
            ENTLIB_ASSERT(setOfObject.get("E").has_value());
            ENTLIB_ASSERT(not setOfObject.contains("E2"));
            ENTLIB_ASSERT(setOfObject.get("E")->Value().get() == std::string("e2"));
            ENTLIB_ASSERT(setOfObject.get("E")->Name().get() == std::string("E"));
            ENTLIB_ASSERT(setOfObject.get("F").has_value());
            ENTLIB_ASSERT(setOfObject.get("F")->Value().get() == std::string("f"));
            ENTLIB_ASSERT(setOfObject.get("F")->Name().get() == std::string("F"));
            // Test resetInstanceOf with overriden key
            setOfObject.get("F")->resetInstanceOf("ObjectInSet.node");
            ENTLIB_ASSERT(setOfObject.get("F")->Value().get() == std::string("e2"));
            ENTLIB_ASSERT(setOfObject.get("F")->Name().get() == std::string("F"));

            // Test insert the __removed__ element get back the prefab values
            // insert => makeInstanceOf => __remove__ => insert
            //          => restore values since we dont know how to reset an element when saving
            ENTLIB_ASSERT(not setOfObject.contains("G"));
            ENTLIB_ASSERT(setOfObject.add("G").getProperty().hasValue());
            ENTLIB_ASSERT(setOfObject.get("G").has_value());
            ENTLIB_ASSERT(setOfObject.get("G")->getProperty().hasValue());
            ENTLIB_ASSERT(setOfObject.get("G")->hasOverride() == true);
            ENTLIB_ASSERT(setOfObject.get("G")->Value().get() == std::string("g"));
            setOfObject.remove("G");
        }

        // Test remove entity
        auto subsceneCmp = *ent.Components().SubScene();
        ENTLIB_ASSERT(subsceneCmp.Embedded().size() == PrefabSubEntityCount);
        subsceneCmp.Embedded().remove("TestRemove");
        ENTLIB_ASSERT(subsceneCmp.Embedded().size() == PrefabSubEntityCount - 1);

        subsceneCmp.Embedded().add("PrettiestName");

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
            comp.getProperty().getParent()->hasOverride()); // A new item in an array in always override
        // Component with override
        ent.Components().TestDefaultValues()->DoubleWithDefaultValue().set(36.);
        ENTLIB_ASSERT(ent.Components().TestDefaultValues().has_value());
        ENTLIB_ASSERT(ent.Components().TestDefaultValues()->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = *ent.Components().CharacterControllerGD();
        compWithInstOf.resetInstanceOf("test.CharacterControllerGD.node");
        ENTLIB_ASSERT(
            compWithInstOf.getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        ENTLIB_ASSERT(compWithInstOf.hasOverride());
        // *************** NODE ***************
        // new Property
        auto setOfObject = ent.Components().TestSetOfObject();
        ENTLIB_ASSERT(setOfObject);
        auto mapTest = setOfObject->MapOfObject();
        mapTest.add("NewNode");
        ENTLIB_ASSERT(mapTest.get("NewNode").has_value());
        ENTLIB_ASSERT(mapTest.get("NewNode")->hasOverride()); // Newly inserted noeds are always overriden
        // Property with override
        mapTest.get("OldNode1")->Value().set("overriden");
        ENTLIB_ASSERT(mapTest.get("OldNode1")->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest.get("OldNode1")->hasOverride());
        // Property with instanceOf overriden
        mapTest.get("OldNode2")->resetInstanceOf("OldNode2.MapOfObject.node");
        auto val = mapTest.get("OldNode2");
        ENTLIB_ASSERT(val->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(val->hasOverride());

        // Test mapInsert in map
        {
            mapTest = setOfObject->MapOfObject();
            auto newNode2 = mapTest.add("NewNode2");
            ENTLIB_ASSERT(newNode2.getDataKind() == Ent::DataKind::object);
        }

        sysCreat->BehaviorState().set("Overrided");
        ent.save("instance.copy.entity");

        {
            Gen::Entity instance3(ent.makeInstanceOf());

            auto testSetOfObject3 = instance3.Components().TestSetOfObject();
            auto setOfObject3 = testSetOfObject3->SetOfObject();

            auto mapTest2 = testSetOfObject3->MapOfObject();
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
        auto ent = Gen::Entity::loadCopy(entlib, "instance3.entity");

        auto testSetOfObject3 = ent.Components().TestSetOfObject();
        auto setOfObject3 = testSetOfObject3->SetOfObject();

        // Test insert an element in an instance of the __removed__ one, do not resore the old values
        // insert => makeInstanceOf => __remove__ => makeInstanceOf => insert
        //          => do not restore values
        ENTLIB_ASSERT(setOfObject3.get("G")->Value().get() == std::string());
    }

    auto test_erase = [](Gen::Entity const& ent)
    {
        auto actorStates = ent.ActorStates();
        auto const pathNodeGD = *ent.Components().TestTagsList();
        auto tags = pathNodeGD.Tags().Tags();

        // Test erase in map (+save/load)
        ENTLIB_ASSERT(tags.size() == 3);
        ENTLIB_ASSERT(not tags.get("c").has_value());

        // Test insert in map (+save/load)
        auto const e = tags.get("A");
        ENTLIB_ASSERT(e.has_value());
        ENTLIB_ASSERT(e->getDataKind() == Ent::DataKind::primitiveSet);

        // Test erase in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.get("EntityStatePlayer").has_value() == false);

        // Test insert in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.get("ActorStateAlive").has_value());

        // Test remove component
        ENTLIB_ASSERT(ent.Components().TransformGD().has_value() == false);
        ENTLIB_ASSERT(ent.Components().SubScene().has_value() == false);
    };

    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");

        // Test erase in union_set
        auto actorStates = ent.ActorStates();
        ENTLIB_ASSERT(actorStates.get("EntityStatePlayer").has_value());
        ENTLIB_ASSERT(actorStates.remove("EntityStatePlayer"));
        ENTLIB_ASSERT(actorStates.get("EntityStatePlayer").has_value() == false);

        // Test insert in union_set
        actorStates.addActorStateAlive();

        // Test erase in map
        auto pathNodeGD = *ent.Components().TestTagsList();
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
        auto ent = Gen::Entity::loadCopy(entlib, "test_erase.entity");
        test_erase(ent);
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance2.entity");
        testInstanceOf(ent, true, false);
    }
    auto testInstanceOverrideSubscene = [](Gen::Entity const& ent)
    {
        // TEST SubScene (with override)
        auto const subScene = ent.Components().SubScene();
        ENTLIB_ASSERT(subScene.has_value());
        auto const subObj = subScene->Embedded().get("EP1-Spout_LINK_001");
        ENTLIB_ASSERT(subObj->Name() == std::string("EP1-Spout_LINK_001"));

        // Test an overrided Component
        auto const netLink = subObj->Components().NetworkLink();
        ENTLIB_ASSERT(netLink.has_value());
        ENTLIB_ASSERT(netLink->Source().get() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->Source().isSet() == false);
        ENTLIB_ASSERT(netLink->Target().get() == std::string(".EP1-crook_2"));
        ENTLIB_ASSERT(netLink->Target().isSet());

        // Test a not overrided Component
        auto const trans = subObj->Components().TransformGD();
        ENTLIB_ASSERT(trans.has_value());
        ENTLIB_ASSERT(trans->Position()[0].get() == 0.0);
    };
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_override_subscene.entity");
        testInstanceOverrideSubscene(ent);
        ent.save("instance_override_subscene.copy.entity");
    }
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_override_subscene.copy.entity");
        testInstanceOverrideSubscene(ent);
    }
    {
        // Test write instance of
        auto ent = Gen::Entity::loadCopy(entlib, "instance.copy.entity");
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
            ent.Components().AnimationEventsGeneratorGD()->getProperty().getParent()->hasOverride());
        // Component with override
        ENTLIB_ASSERT(ent.Components().TestDefaultValues().has_value());
        ENTLIB_ASSERT(ent.Components().TestDefaultValues()->DoubleWithDefaultValue().get() == 36.);
        ENTLIB_ASSERT(ent.Components().TestDefaultValues()->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = *ent.Components().CharacterControllerGD();
        ENTLIB_ASSERT(
            compWithInstOf.getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        ENTLIB_ASSERT(compWithInstOf.hasOverride());
        // *************** NODE ***************
        // new Property
        auto pathNodeGD = *ent.Components().TestSetOfObject();
        auto mapTest = pathNodeGD.MapOfObject();
        ENTLIB_ASSERT(mapTest.get("NewNode").has_value());
        // Newly inserted Nodes are overriden
        ENTLIB_ASSERT(mapTest.get("NewNode")->hasOverride());
        // Property with override
        ENTLIB_ASSERT(mapTest.get("OldNode1")->Value().get() == std::string("overriden"));
        ENTLIB_ASSERT(mapTest.get("OldNode1")->hasOverride());
        // Property with instanceOf overriden
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
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");

        auto detached = ent.detach();

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
        auto ent = Gen::Entity::loadCopy(entlib, "instance.detached.entity");

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
        auto prefab = Gen::Entity::loadCopy(entlib, "prefab.entity");
        auto instanceOf = prefab.makeInstanceOf();

        // Test instanciation of a prefab Property
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
        auto const ent = Gen::Entity::loadCopy(entlib, _instancePath);

        // Test instanciation of a prefab Property
        auto stickToTerrain = *ent.Components().StickToTerrain();
        ENTLIB_ASSERT(stickToTerrain.getInstanceOf() != nullptr);
        ENTLIB_ASSERT(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isSet() == false);
        ENTLIB_ASSERT(stickToTerrain.ZOffset().isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        // TEST read inherited values in inherited component
        auto const heightObj = ent.Components().HeightObj();
        ENTLIB_ASSERT(heightObj.has_value());
        ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
        ENTLIB_ASSERT(not heightObj->Subdivision().isSet());
        ENTLIB_ASSERT(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        ENTLIB_ASSERT(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // Test read prefab
        auto const sysCreat = ent.Components().SystemicCreature();
        ENTLIB_ASSERT(sysCreat.has_value());

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->Faction().get() == std::string("Shamans"));
        ENTLIB_ASSERT(not sysCreat->Faction().isSet()); // Not overrided
        ENTLIB_ASSERT(sysCreat->Inventory().get() == std::string("KaiWOLgrey"));
        ENTLIB_ASSERT(not sysCreat->Inventory().isSet()); // Not overrided

        // TEST read array
        ENTLIB_ASSERT(not sysCreat->ScriptList().isSet()); // Arrays are NOT always set
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
        auto instanceOf = Gen::Entity::create(entlib);

        instanceOf.Name().set("TestResetInstanceOf");

        instanceOf.resetInstanceOf("prefab.entity");
        ENTLIB_ASSERT(instanceOf.Components().NetworkNode().has_value());
        instanceOf.Components().TransformGD()->getProperty().getSchema()->properties;

        // Test instanciation of a prefab Property
        auto stickToTerrain = instanceOf.Components().addStickToTerrain();
        stickToTerrain.resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain.NormalRatio().set(0.6);

        instanceOf.save("setInstanceOf.entity");
    }
    testCreateInstanceOf("setInstanceOf.entity");
    
    // ******************* Test load/save complex entity pinetreec50cmh5mbasic ********************
    {
        auto ent = Gen::Entity::loadCopy(entlib, "pinetreec50cmh5mbasic.entity");
        ent.save("pinetreec50cmh5mbasic.copy.entity");
        auto copyEnt = Gen::Entity::loadCopy(entlib, "pinetreec50cmh5mbasic.copy.entity");

        // TEST keeping empty component after entity save
        ENTLIB_ASSERT(copyEnt.Components().EventHandlerGD().has_value());
    }

    // ******************* Test the override of an entity in a SubScene ***************************
    auto testOverrideSubEntity = [](Gen::Entity const& ent)
    {
        auto const subScenecomp = *ent.Components().SubScene();
        auto const allSubEntities = subScenecomp.Embedded();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount);
        ENTLIB_ASSERT(subScenecomp.Embedded().get("EP1-Spout_LINK_001")->Color()[0].get() == 42);
    };
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_override_subentity.entity");
        testOverrideSubEntity(ent);
        ent.save("instance_override_subentity.copy.entity");
        auto copyEnt = Gen::Entity::loadCopy(entlib, "instance_override_subentity.copy.entity");
        testOverrideSubEntity(copyEnt);
    }

    // ******************* Test the add of an entity in a SubScene *****************************
    auto testAddSubEntity = [](Gen::Entity const& ent)
    {
        auto const subScenecomp = *ent.Components().SubScene();
        auto const allSubEntities = subScenecomp.Embedded();
        ENTLIB_ASSERT(allSubEntities.size() == PrefabSubEntityCount + 1);
        auto const ent0 = subScenecomp.Embedded().get("EP1-Spout_LINK_001");
        auto const ent1 = subScenecomp.Embedded().get("EP1-Spout_LINK_001_added");
        ENTLIB_ASSERT(ent0->Name() == std::string("EP1-Spout_LINK_001"));
        auto const red = ent0->Color()[0];
        ENTLIB_ASSERT(not ent0->hasOverride());
        ENTLIB_ASSERT(red.get() == 255);
        ENTLIB_ASSERT(ent1->Name() == std::string("EP1-Spout_LINK_001_added"));
        ENTLIB_ASSERT(ent1->Color()[0].get() == 44);
    };
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_add_subentity.entity");
        testAddSubEntity(ent);
        ent.save("instance_add_subentity.copy.entity");
        auto copyEnt = Gen::Entity::loadCopy(entlib, "instance_add_subentity.copy.entity");
        testAddSubEntity(copyEnt);
    }
    {
        // Test access subscene override
        auto ent = Gen::Entity::load(entlib, "entity-subscene.entity").makeInstanceOf();
        auto subs = *ent.Components().SubScene();

        ENTLIB_ASSERT(ent.hasOverride()); // makeInstanceOf does override the instanceOf
        ENTLIB_ASSERT(not subs.Embedded().empty());

        subs.Embedded().get("wolf_skeleton_lush")->Components().addActorGD().InSpiritWorld().set(true);
        ent.save("entity-subscene-override-saved.entity");

        auto ovrdEntt = Gen::Entity::loadCopy(entlib, "entity-subscene-override-saved.entity");
        auto ovrdSubs = *ovrdEntt.Components().SubScene();

        //Test that we properly still have access to the prefab subscene entities
        ENTLIB_ASSERT(not ovrdSubs.Embedded().empty());
    }

    {
        auto ent = Gen::Entity::loadCopy(entlib, R"(Creature/my_creature_level2.entity)");
        auto subscene =
            Gen::Entity(ent.Components().SubScene()->Embedded().getProperty().getArrayItem(0llu))
                .Components()
                .SubScene()
                ->Embedded();
        ENTLIB_ASSERT(subscene.size() == 1);
        ENTLIB_ASSERT(strcmp(subscene.begin()->Name(), "default_level2") == 0);
    }

    // ******************* Test the EntLibException ***********************************************
    {
        bool exceptionThrown = false;
        try
        {
            auto ent = Gen::Entity::load(entlib, "scene_with_invalid_entity.scene");
            [[maybe_unused]] auto prop =
                ent.Components().getProperty().getUnionSetItem("this_component_doesnt_exist");
        }
        catch (std::runtime_error& ex)
        {
            exceptionThrown = true;
            char const* what = ex.what();
            ENTLIB_ASSERT(strstr(what, "this_component_doesnt_exist") != nullptr);
        }
        ENTLIB_ASSERT(exceptionThrown);
    }

    // ******************* Test default color *****************************************************
    {
        auto ent = Gen::Entity::create(entlib);
        ent.Name().set("TestDefaultColor");

        ENTLIB_ASSERT((std::array<double, 4>(ent.Color())) == (std::array<double, 4>{1., 1., 1., 1.}));
    }
    // ********************************** Test load/save scene ************************************

    if (doTestRawData)
    {
        entlib.rawdataPath = rawdataPath;

        ENTLIB_LOG("Loading SceneWild.scene...");
        // auto scene = entlib.loadScene("X:/RawData/01_World/Wild/scenewild/editor/SceneWild.scene");
        entlib.validationEnabled = false;
        auto sceneent =
            Gen::Entity::loadCopy(entlib, "20_scene/personal/simont/vfxGym/ScenevfxGym.scene");
        auto scene = sceneent.Components().SubScene()->Embedded();

        ENTLIB_LOG("Done");
        
        auto heightObj = scene.begin()->Components().addHeightObj();
        heightObj.DisplaceNoiseList().push();

        auto const& properties =
            scene.begin()->Components().addHeightObj().getProperty().getSchema()->properties;
        auto fieldNameCount = properties.size();
        ENTLIB_ASSERT(fieldNameCount >= 9);

        entlib.rawdataPath = current_path();
        scene.insertInstanceOf((current_path() / "prefab.entity").string().c_str());

        sceneent.save((current_path() / "SceneWild.test.scene").string().c_str());

        auto addedEntity = *scene.get("PlayerSpawner_");
        auto cinematicCmp = addedEntity.Components().CinematicGD();
        ENTLIB_ASSERT(cinematicCmp.has_value());
    }

    printfmt("Done\n");
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