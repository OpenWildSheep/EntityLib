#pragma warning(push, 0)
#include <ciso646>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cxxopts.hpp>
#pragma warning(pop)

#include <EntityLib/EntityLib.h>
#include <EntGen.h>
#include <EntityLib/ComponentMerge.h>

#include "TestCursor.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

namespace Ent
{
    namespace Gen = Gen2;
}

using namespace Ent;

TEST_CASE("Test Properties", "[all]")
{

    std::filesystem::path rawdataPath = ".";
    std::filesystem::path schemaPath = "../build/Schemas";

    EntityLib entlib(rawdataPath, schemaPath);
    using namespace std::filesystem;

    SECTION("ENTLIB_LOGIC_ERROR")
    {
        entlib.setLogicErrorPolicy(LogicErrorPolicy::Throw);
        auto testLogicError = []
        {
            ENTLIB_LOGIC_ERROR("Test logic error");
        };
        CHECK_THROWS_AS(testLogicError(), std::logic_error);
        entlib.setLogicErrorPolicy(LogicErrorPolicy::Terminate);
    }
    SECTION("copyInto")
    {
        auto source = Gen::Entity::create(entlib);
        source.Components().addTestArrays().Variant().setPosition();
        source.Components().addTestSetOfObject().MapOfObject().add("Blue");
        source.Components().addTestSetOfObject().MapOfPrimitive().add("Yellow");
        source.Components().addTestSetOfObject().SetOfObject().add("Red");
        source.Name().set("Cyan");

        auto target = Gen::Entity::create(entlib);
        source.copyInto(target, CopyMode::MinimalOverride);
        CHECK(*source.getProperty().getRawJson() == *target.getProperty().getRawJson());
    }
    SECTION("Property::getObjectSetItems")
    {
        auto source = Gen::Entity::create(entlib);
        auto setOfObject = source.Components().addTestSetOfObject().SetOfObject();
        auto a = setOfObject.add("Blue");
        auto b = setOfObject.add("Yellow");
        auto c = setOfObject.add("Red");

        auto items = setOfObject.getProperty().getObjectSetItems();
        CHECK(items.size() == 3);
        CHECK(items[0].makeAbsoluteNodeRef() == a.getProperty().makeAbsoluteNodeRef());
        CHECK(items[1].makeAbsoluteNodeRef() == c.getProperty().makeAbsoluteNodeRef());
        CHECK(items[2].makeAbsoluteNodeRef() == b.getProperty().makeAbsoluteNodeRef());
    }
    SECTION("Property::insertMapItem/IntKey")
    {
        auto source = Gen::Entity::create(entlib);
        auto intIntMap = source.Components().addTestSetOfObject().MapOfIntInt().getProperty();
        CHECK(intIntMap.empty());
        intIntMap.insertMapItem(3);
        CHECK(intIntMap.contains(3));
        CHECK(intIntMap.size() == 1);
        intIntMap.insertMapItem(4);
        CHECK(intIntMap.contains(4));
        CHECK(intIntMap.size() == 2);
    }
    SECTION("Property Save/Load")
    {
        auto ent = entlib.newProperty(entlib.getSchema("Entity"));
        ent.save("test_output/test_create2.entity");
        auto copy = entlib.loadProperty("test_output/test_create2.entity");
        CHECK(*ent.getRawJson() == *copy.getRawJson());
    }
    SECTION("Test NodeRef in error message")
    {
        // Ensure that error message contains the file name and NodeRef
        auto&& entJson = entlib.createTempJsonFile("Entity");
        entJson.document["Name"] = 45;
        entJson.document["Components"] = 45;
        auto filename = "test_wrong_type.entity";
        auto entProp = Property(&entlib, entlib.getSchema("Entity"), filename, entJson);
        auto name = entProp.getObjectField("Name");
        auto comp = entProp.getObjectField("Components");
        std::string errorMessage;
        try
        {
            [[maybe_unused]] auto str = name.getString();
        }
        catch (ContextException& ex)
        {
            errorMessage = ex.what();
        }
        CHECK(errorMessage.find(filename) != std::string::npos);
        CHECK(errorMessage.find("Name") != std::string::npos);
        std::string errorMessage2;
        try
        {
            [[maybe_unused]] auto itemMap = comp.getUnionSetItems();
        }
        catch (ContextException& ex)
        {
            errorMessage2 = ex.what();
        }
        CHECK(errorMessage2.find(filename) != std::string::npos);
        CHECK(errorMessage2.find("Components") != std::string::npos);
    }
    SECTION("Entity Save/Load")
    {
        auto ent = Gen::Entity::create(entlib);
        ent.save("test_output/test_create.entity");
        auto copy = Gen::Entity::load(entlib, "test_output/test_create.entity");
        CHECK(*ent.getProperty().getRawJson() == *copy.getProperty().getRawJson());
    }
    SECTION("D")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto strings = ent.Components().UnitTestComponent()->SimpleArray();
        CHECK(strings.getPrefab()->size() == 5);
        CHECK(strings.size() == 5);
        auto cel2 = strings[2].getProperty();
        cel2.setString("test4851");
        CHECK(strings.getPrefab()->size() == 5);
        CHECK(strings.size() == 5);
    }
    SECTION("getInstanceOf in union")
    {
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
        CHECK(unionInstanceOf == std::string_view("BlendDurationIn.node"));
    }
    SECTION("re-insertion of a deleted map item")
    {
        // Check re-insertion of a deleted map item (avoid to create a 2nd json item)
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto commonDataMap = ent.Components().ScriptComponentGD()->CommonDataMap();
        CHECK(commonDataMap.get("NbBeams").has_value());
        [[maybe_unused]] auto nbbeams = commonDataMap.get("NbBeams");
        commonDataMap.remove("NbBeams");
        CHECK(not commonDataMap.get("NbBeams").has_value());
        auto nbbeams2 = commonDataMap.add("NbBeams");
        CHECK(commonDataMap.get("NbBeams").has_value());
        nbbeams2.unset(); // Do not remove it since it is present in prefab
        CHECK(commonDataMap.get("NbBeams").has_value());
    }
    SECTION("visitor, in case of map of primitive")
    {
        // Check the visitor, in case of map of primitive
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto detached = ent.detach();
        auto speed2 = detached.Components().TestSetOfObject()->MapOfPrimitive().get("speed2");
        CHECK(speed2.has_value());
    }
    SECTION("Unset in map/set when value exist in prefab but not in instance")
    {
        // Test unset
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        // On unionset
        auto netGD = ent.Components().addNetGD(); // exist in prefab but not in instance
        CHECK(netGD.isSet());
        netGD.unset();
        CHECK(netGD.isSet() == false);
        // On objectset
        auto subent = ent.Components().SubScene()->Embedded().add(
            "EP1-Spout_LINK_001"); // exist in prefab but not in instance
        CHECK(subent.isSet());
        subent.unset();
        CHECK(subent.isSet() == false);
        // On map
        auto mapitem = ent.Components().TestSetOfObject()->MapOfObject().add(
            "OldNode1"); // exist in prefab but not in instance
        CHECK(mapitem.isSet());
        mapitem.unset();
        CHECK(mapitem.isSet() == false);
        ent.save("output/check_unset_output.entity");
    }
    SECTION("I")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        // unset - unset children
        auto comp = ent.Components();
        CHECK(comp.isSet());
        auto embedded = comp.SubScene()->Embedded();
        CHECK(embedded.isSet());
        auto subent = *embedded.get("EntityWithInstanceOf");
        CHECK(subent.isSet());
        comp.unset();
        CHECK(comp.isSet() == false);
        CHECK(embedded.isSet() == false);
        CHECK(subent.isSet() == false);
        // set - set parent
        comp = ent.Components();
        embedded = comp.SubScene()->Embedded();
        subent = *embedded.get("EntityWithInstanceOf");
        comp = ent.Components(); // Make a clone of the real parent
        embedded = comp.SubScene()->Embedded();
        CHECK(comp.isSet() == false);
        CHECK(embedded.isSet() == false);
        CHECK(subent.isSet() == false);
        subent.Color()[0] = 3;
        CHECK(subent.isSet());
        CHECK(embedded.isSet());
        CHECK(comp.isSet());
        // Remove component in prefab and still use the instance Prop of component
        ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        CHECK(ent.getPrefab().has_value());
        comp = ent.Components();
        CHECK(comp.getPrefab().has_value());
        auto instNetworkNode = comp.SmoothScaleComponentGD();
        CHECK(instNetworkNode->getPrefab().has_value());
        auto prefab = Gen::Entity::load(entlib, "prefab.entity");
        CHECK(comp.SmoothScaleComponentGD().has_value());
        CHECK(instNetworkNode->getPrefab().has_value());
        prefab.Components().removeSmoothScaleComponentGD();
        CHECK(comp.SmoothScaleComponentGD().has_value() == false);
        CHECK(instNetworkNode->getSchema() == nullptr);
        instNetworkNode.reset();
    }

    SECTION("Ent::format")
    {
        CHECK(Ent::format("Toto %d", 37) == "Toto 37");
    }

    SECTION("J")
    {
        std::map<std::string, int> emptyMap;
        CHECK_THROWS_AS(AT(emptyMap, "not"), Ent::InvalidKey);
    }

    SECTION("$ref links in entlib.schema.schema.allDefinitions")
    {
        // Test $ref links in entlib.schema.schema.allDefinitions
        auto const* colorRef = "Color";
        CHECK(entlib.schema.schema.allDefinitions.count(colorRef) == 1);
    }

    static constexpr auto PrefabSubEntityCount = 5;

    SECTION("insertMapItem_wrong_enum_key")
    {
        // Check insert a key which is an enum, but with a wrong value.
        auto ent = Gen::Entity::create(entlib);
        auto map = ent.Components()
                       .addAnimationModelGD()
                       .additionalSpeedDebug()
                       .get(Gen::LocomotionModeEnum::buried)
                       ->getProperty();
        CHECK_THROWS_AS(map.insertMapItem("test"), BreakSchemaRules);
    }
    SECTION("L")
    {
        auto ent = Gen::SeedPatchDataList::loadCopy(entlib, "myseedpatchMarianne.seedpatchdata.node");
        ent.save("myseedpatchMarianne.seedpatchdata.copy.node");
    }
    SECTION("Check getPrefab when all prefabs are unset") // (should not be null)
    {
        auto ent = Gen::Entity::create(entlib).makeInstanceOf();
        auto entProp = ent.getProperty();
        auto color = entProp.getObjectField("Color");
        CHECK(color.getPrefab().has_value());
        auto red = color.getArrayItem(0);
        CHECK(red.getPrefab().has_value());
    }
    SECTION("loadProperty schema detection")
    {
        // When there is a $schema field
        auto node = entlib.loadProperty("myseedpatch_schema.node");
        CHECK(node.getSchema() == entlib.getSchema("SeedPatchDataList"));
        // When there is a $schema field with different style
        node = entlib.loadProperty("myseedpatch_schema_style.node");
        CHECK(node.getSchema() == entlib.getSchema("SeedPatchDataList"));
        // No $schema, no .entity, wrong pre-extention
        CHECK_THROWS_AS(entlib.loadProperty("test.ThisTypeDoesntExist.node"), Ent::UnknownSchema);
    }
    SECTION("O")
    {
        auto node = entlib.loadProperty("Entity", "instance.entity");
        auto prefabHisto = getPrefabHistory(node);
    }
    SECTION("Test NodeRef")
    {
        auto node = entlib.loadPropertyCopy("Entity", "instance.entity");
        auto const* nodeRef =
            R"(Components/SubScene/Embedded/EP1-Spout_LINK_001/Components/TransformGD)";
        auto ent = node.resolveNodeRef(nodeRef);
        REQUIRE(ent.has_value());
        auto entpath = node.makeNodeRef(*ent);
        CHECK(entpath == nodeRef);
        auto nullPath = ent->makeNodeRef(*ent);
        CHECK((nullPath.empty() or nullPath == "."));
    }
    SECTION("Test NodeRef in Union")
    {
        auto node = entlib.loadPropertyCopy("Entity", "instance.entity");
        // Test Union
        auto typedValueUnion =
            node.getObjectField("Components").insertUnionSetItem("TestUnion").getObjectField("Union");
        auto const* typeValueRef = R"(Components/TestUnion/Union)";
        CHECK(node.makeNodeRef(typedValueUnion) == typeValueRef);
        auto stringUnionData = typedValueUnion.setUnionType("string");
        auto const* strRef = R"(Components/TestUnion/Union/string)";
        CHECK(node.makeNodeRef(stringUnionData) == strRef);
        CHECK(typedValueUnion.makeNodeRef(stringUnionData) == "string");
    }
    auto testPrefabEntity = [&entlib](Gen::Entity ent)
    {
        // ActorStates
        auto actorStates = ent.ActorStates();
        CHECK(actorStates.getProperty().getDataKind() == Ent::DataKind::unionSet);
        CHECK(actorStates.size() == 2);
        auto actorState = actorStates.ActorStateHoldingItem();
        CHECK(actorState.has_value());
        static_assert(std::is_same_v<decltype(*actorState), Gen::ActorStateHoldingItem&>);
        CHECK(actorState->getProperty().hasValue());
        auto exitRequired = actorState->ItemEntityRef();
        CHECK(exitRequired.getProperty().hasValue());
        CHECK(exitRequired.get().entityPath == std::string("tutu"));
        auto entityStatePlayerData = actorStates.EntityStatePlayer();
        CHECK(entityStatePlayerData.has_value());

        // Map and Set overridePolicy
        auto pathNodeGD = ent.Components().TestTagsList();
        auto tags = pathNodeGD->Tags().Tags();
        CHECK(tags.size() == 3);
        CHECK(tags.get("a").has_value());
        CHECK(tags.get("c").has_value());
        CHECK(tags.get("c")->size() == 1);
        CHECK(tags.get("c")->count("2"));
        // Test get on map and set
        CHECK(tags.get("a")->count("1"));

        CHECK(tags.getProperty().getMapKeyKind() == Ent::DataKind::string);
        auto keys = tags.getKeys();
        CHECK(keys.size() == 3);
        for (auto&& k : keys)
        {
            CHECK(tags.get(k).has_value());
        }

        // Test default value
        auto testDefaultValues = ent.Components().TestDefaultValues();
        CHECK(testDefaultValues->DoubleWithDefaultValue().get() == 1.23456);
        CHECK(testDefaultValues->DoubleWithDefaultValue().isDefault());
        CHECK(testDefaultValues->schemaName == std::string("TestDefaultValues"));

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(heightObj->Subdivision().isSet());
        CHECK(not heightObj->Subdivision().isDefault());
        CHECK(heightObj->Subdivision().getDefault() == 3);
        CHECK(
            heightObj->Subdivision().getProperty().getSchema()->userMeta["testUserMetatdata"].get<int>()
            == 42);

        CHECK(heightObj->DisplaceNoiseList()[0llu].MapChannel().get() == 51248);
        CHECK(heightObj->DisplaceNoiseList()[0llu].MapChannel().isSet());

        // Test read Thumbnail
        CHECK(ent.Thumbnail().get() != nullptr);
        CHECK(ent.Thumbnail() == std::string("TestThumbnail"));

        // Test read prefab
        auto sysCreat = ent.Components().SystemicCreature();
        CHECK(sysCreat.has_value());

        // TEST read setted values
        CHECK(sysCreat->Faction().get() == std::string("Shamans")); // set
        CHECK(sysCreat->Faction().isSet()); // is set
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set
        CHECK(sysCreat->Inventory().isSet()); // is set

        // TEST comment
        CHECK(sysCreat->BehaviorState().get() == std::string("W/*at*/c//h")); // set

        // TEST read array
        CHECK(sysCreat->ScriptList().isSet());
        CHECK(sysCreat->ScriptList().size() == 3);

        // TEST default values
        CHECK(sysCreat->Burried().get() == false); // default
        CHECK(not sysCreat->Burried().isSet()); // default

        // TEST SubScene
        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        CHECK(allSubEntities.size() == PrefabSubEntityCount);
        CHECK(allSubEntities.get("EP1-Spout_LINK_001").has_value());
        CHECK(allSubEntities.get("EP1-Spout_LINK_001")->Color()[0llu].get() == 255.);

        // TEST subScenecomp
        auto subent = allSubEntities.get("EP1-Spout_LINK_001");
        auto parent = entlib.getParentEntity(subent->getProperty());
        CHECK((parent.has_value() and *parent == ent.getProperty()));
        CHECK(entlib.getParentEntity(ent.getProperty()).has_value() == false);

        // TEST sub-object with non-default values
        auto ldprimitive = ent.Components().LDPrimitive();
        auto primitiveData = ldprimitive->PrimitiveData();
        CHECK(primitiveData.Height().get() == 42.0);

        // TEST Default size for array is minItems
        auto physicsGD = ent.Components().PhysicsGD();
        auto axisRestriction = physicsGD->AxisRestriction();
        CHECK(axisRestriction.size() == 3);

        // Test default values related to a property of type class/struct.
        auto characterController = ent.Components().CharacterControllerGD();
        auto slideData = characterController->SlideData();
        auto adherenceMin = slideData.speedMediumCoeffIn();
        auto in = adherenceMin.in_();
        CHECK(in.size() == 2);
        CHECK(in[0].get() == -1.);
        CHECK(in[1].get() == 0.5);

        // Ensure that default values of property are not poluted by default values of pointer class
        CHECK(testDefaultValues.has_value());
        auto propertyWithDefault = testDefaultValues->propertyWithDefault();
        auto propertyWithDefault2 = propertyWithDefault.propertyWithDefault2();
        CHECK(propertyWithDefault2.A().get() == 3);
        CHECK(propertyWithDefault2.B().get() == 0);
        auto propertyWithDefault3 = propertyWithDefault.propertyWithDefault3();
        CHECK(propertyWithDefault3.A().get() == 3);
        CHECK(propertyWithDefault3.B().get() == 0);

        // Test Property's InstanceOf
        auto seedPatch = ent.Components().SeedPatch();
        CHECK(seedPatch->NoiseSizeX().get() == 1.);
        CHECK(seedPatch->NoiseSizeY().get() == 2.);
        CHECK(seedPatch->NoiseOffsetX().get() == 2.);
    };

    SECTION("Q")
    {
        auto ent = Gen::Entity::create(entlib);
        ent.Name() = "TestResetInstanceOf";
        ent.resetInstanceOf("prefab.entity");
        CHECK(ent.hasOverride()); // resetInstanceOf does override the "instanceOf"
        CHECK(ent.getInstanceOf() == std::string("prefab.entity"));
    }
    SECTION("R")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "missing_embedded.entity");
        CHECK(ent.Components().size() == 1); // Contains only SubScene
    }
    SECTION("S")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.entity");

        auto setOfObject = ent.Components().TestSetOfObject();
        CHECK(setOfObject);
        auto mapTest = setOfObject->MapOfObject();
        auto testParent = mapTest.add("Should_not_appear_in_diff");
        CHECK(testParent.getProperty().getParent()->getDataKind() == DataKind::map); // parent is the map
        CHECK(testParent.getProperty().getParent()->isMapOrSet());
        mapTest.remove("Should_not_appear_in_diff");
        CHECK(not mapTest.get("Should_not_appear_in_diff").has_value());

        // Test a fixed-size array is not "addedInInstance"
        auto trans = ent.Components().TransformGD();
        CHECK(trans.has_value());
        trans->Position()[0] = 36.f;
        trans->Position().unset();
        CHECK(not trans->Position().hasOverride());

        // Test Variant
        auto testArrays = ent.Components().TestArrays();
        CHECK(testArrays->Variant().float_().has_value());
        CHECK(testArrays->Variant().float_()->get() == 3.1416);
        nlohmann::json const* withoutIndex = testArrays->Variant().getRawJson();
        CHECK(withoutIndex->count("variantIndex") == 0);
        CHECK(withoutIndex->at("variantType").get_ref<std::string const&>() == "float");

        // Test saveNode
        auto heightObj = ent.Components().HeightObj();
        heightObj->getProperty().save("test.HeightObj.node");

        testPrefabEntity(ent);
        // Test mapErase in set of primitive
        auto pathNodeGD = ent.Components().TestTagsList();
        pathNodeGD = pathNodeGD->makeInstanceOf(); // erasePrimSetKey fail only if key exist in prefab
        auto tags = pathNodeGD->Tags().Tags();
        auto primSet = tags.get("a");
        CHECK(primSet->getProperty().getParent()->getDataKind() == DataKind::map);
        CHECK_THROWS_AS(primSet->getProperty().erasePrimSetKey("1"), Ent::BadArrayType);

        // TEST simple entity ref creation
        auto testEntityRef = ent.Components().addTestEntityRef();
        CHECK(testEntityRef.TestRef().get().entityPath.empty());
        testEntityRef.TestRef().set(entlib.makeEntityRef(ent.getProperty(), ent.getProperty()));
        CHECK(testEntityRef.TestRef().get().entityPath == ".");
        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        testEntityRef.TestRef().set(
            entlib.makeEntityRef(ent.getProperty(), allSubEntities.begin()->getProperty()));

        // TEST Union not in Object
        auto testUnion = ent.Components().addTestUnion();
        auto un = testUnion.Union();
        un.unset();
        CHECK(not un.hasOverride());
        CHECK(un.getType() == std::string("s32"));
        un.setfloat_();
        CHECK(un.hasOverride());
        CHECK(un.getType() == std::string("float"));
        un.sets32();
        CHECK(un.hasOverride());
        CHECK(un.getType() == std::string("s32"));
        un.unset();
        CHECK(not un.hasOverride());
        CHECK(un.getType() == std::string("s32"));
        // TEST Union not in Array
        auto unArr = testUnion.UnionArray();
        auto newUnion = unArr.push();
        CHECK(not newUnion.getProperty().getUnionData().hasOverride());
        CHECK(newUnion.getType() == std::string("s32"));
        // TEST Union not in Object in Array
        auto obj = testUnion.UnionObjectArray().push();
        newUnion = obj.Union();
        CHECK(not newUnion.getProperty().getUnionData().hasOverride());
        CHECK(newUnion.getType() == std::string("s32"));
        // Test getUnionTypesMap
        auto&& nameToTypeMap = newUnion.getSchema()->getUnionTypesMap();
        CHECK(size(nameToTypeMap) == 8);
        CHECK(nameToTypeMap.count("s32") == 1);
        CHECK(nameToTypeMap.count("float") == 1);
        CHECK(nameToTypeMap.count("Vector3") == 1);

        // TEST MaxActivationLevel
        ent.MaxActivationLevel().set(Gen::MaxActivationLevelEnum::InWorld);

        auto sysCreat = ent.Components().SystemicCreature();
        CHECK(sysCreat->Name().get() == std::string()); // default
        CHECK(not sysCreat->Name().isSet()); // default
        sysCreat->Name().set("Shamane_male");
        ent.save("prefab.copy.entity");

        // TEST SubScene detach
        auto originalSubEntities = ent.Components().SubScene()->Embedded();
        CHECK(not originalSubEntities.empty());
        ent.Components().SubScene()->Embedded().clear();
        CHECK(ent.Components().SubScene()->Embedded().empty());

        ent.Components().removeSubScene();
        ent.save("prefab.emptyembbeded.entity");

        // TEST arrays default values
        ent.Components().removeTransformGD();
        auto transformGD = ent.Components().addTransformGD();
        auto mat33 = transformGD.Matrix();
        auto testMat33 = [&]
        {
            CHECK(mat33[0].get() == 1.);
            CHECK(mat33[0].getDefault() == 1.);
            CHECK(mat33[1].get() == 0.);
            CHECK(mat33[1].getDefault() == 0.);
            CHECK(mat33[2].get() == 0.);
            CHECK(mat33[3].get() == 0.);
            CHECK(mat33[4].get() == 1.);
            CHECK(mat33[4].getDefault() == 1.);
            CHECK(mat33[5].get() == 0.);
        };

        auto testDefaultValues = ent.Components().addTestDefaultValues();
        CHECK(testDefaultValues.getProperty().getParent()->hasOverride());
        mat33 = testDefaultValues.Matrix();
        testMat33();
        mat33 = testDefaultValues.Matrix2();
        CHECK(mat33[4].getDefault() == 4.);
        CHECK(mat33[4].get() == 4.);
        CHECK(not mat33[4].hasOverride());
        CHECK(not mat33[4].isSet());
    }
    SECTION("T")
    {
        // Test Arrays size overrides
        auto ent = Gen::Entity::loadCopy(entlib, "instance_arrays.entity");
        CHECK(ent.hasPrefabValue());

        auto comp = ent.Components().TestArrays();
        CHECK(comp);
        auto const testArrayMember = [&](char const* _arrayName,
                                         size_t defaultSize,
                                         std::optional<size_t> prefabSize,
                                         std::optional<size_t> overrideSize)
        {
            auto const node = comp->getProperty().getObjectField(_arrayName);
            CHECK(node.hasValue());
            CHECK(node.hasPrefabValue() == prefabSize.has_value());
            CHECK(node.hasOverride() == overrideSize.has_value());
            CHECK(node.getDefaultSize() == defaultSize);
            CHECK(node.getPrefabSize() == prefabSize);
            if (not overrideSize.has_value())
            {
                CHECK(not node.isSet());
            }
            else
            {
                CHECK(node.size() == overrideSize);
            }
        };
        testArrayMember("DefaultValue", 2, std::nullopt, std::nullopt);
        testArrayMember("PrefabValue", 2, 4, std::nullopt);
        testArrayMember("OverridedDefaultValue", 2, std::nullopt, 3);
        testArrayMember("OverridedPrefabValue", 2, 4, 3);
    }
    SECTION("V")
    {
        // Test the readOnly prefab.entity
        testPrefabEntity(Gen::Entity::loadCopy(entlib, "prefab.entity"));
    }
    SECTION("W")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.copy.entity");
        [[maybe_unused]] auto const newNodeCachesize = entlib.getJsonDatabase().size();
        auto testEntityRef = ent.Components().TestEntityRef();
        CHECK(testEntityRef.has_value());
        CHECK(testEntityRef->TestRef().isSet());
        EntityRef entityRef = testEntityRef->TestRef().get();
        auto resolvedEntity = entlib.resolveEntityRef(ent.getProperty(), entityRef);
        CHECK(resolvedEntity.has_value());

        auto subScenecomp = ent.Components().SubScene();
        auto allSubEntities = subScenecomp->Embedded();
        CHECK(not allSubEntities.empty());
        auto originalEnt = allSubEntities.begin();
        CHECK(resolvedEntity == originalEnt->getProperty());

        auto newSubEnt = allSubEntities.add("prefab.entity");
        CHECK_THROWS_AS(newSubEnt.Name().set("newSubEnt"), CantRename);

        auto embedded = ent.Components().SubScene()->Embedded();
        embedded.insertInstanceOf("prefab.entity");
        CHECK(embedded.get("PlayerSpawner_")->Name() == std::string("PlayerSpawner_"));
    }

    SECTION("X")
    {
        // Test write prefab
        auto ent = Gen::Entity::loadCopy(entlib, "prefab.copy.entity");

        testPrefabEntity(ent);

        // TEST Tuple hasOverride
        auto unitTestComponent = ent.Components().addUnitTestComponent();
        auto wp = unitTestComponent.Position();
        CHECK(wp.hasOverride() == false);
        CHECK(wp.get<0>().hasOverride() == false);

        // TEST MaxActivationLevel
        CHECK(ent.MaxActivationLevel() == Ent::Gen::MaxActivationLevelEnum::InWorld);

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(heightObj->Subdivision().isSet());
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        auto sysCreat = ent.Components().SystemicCreature();
        CHECK(sysCreat.has_value());
        // TEST read setted values
        CHECK(sysCreat->Faction().get() == std::string("Shamans")); // set
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set

        // TEST read array
        CHECK(sysCreat->ScriptList().isSet());
        CHECK(sysCreat->ScriptList().size() == 3);

        // TEST default values unchanged
        CHECK(sysCreat->Burried().get() == false); // default
        CHECK(not sysCreat->Burried().isSet()); // default

        // TEST changed values
        CHECK(sysCreat->Name().get() == std::string("Shamane_male")); // set. changed.
        CHECK(sysCreat->Name().isSet()); // set. changed.

        // TEST simple entity refs resolution
        auto testEntityRef = ent.Components().TestEntityRef();
        CHECK(testEntityRef.has_value());
        CHECK(testEntityRef->TestRef().isSet());
        EntityRef entityRef = testEntityRef->TestRef().get();
        auto resolvedEntity = entlib.resolveEntityRef(ent.getProperty(), entityRef);
        CHECK(resolvedEntity.has_value());

        auto subScenecomp = *ent.Components().SubScene();
        auto allSubEntities = subScenecomp.Embedded();
        CHECK(not allSubEntities.empty());
        auto originalEnt = allSubEntities.begin()->getProperty();
        CHECK(resolvedEntity == originalEnt);
    }

    SECTION("Y")
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
        CHECK(strcmp(instanceOfA.Name(), "InstanceOfA") == 0);
        auto subSceneComp = instanceOfA.Components().SubScene();
        CHECK(subSceneComp.has_value());
        CHECK(subSceneComp->Embedded().size() == 1);
        auto B = *subSceneComp->Embedded().get("B");
        CHECK(strcmp(B.Name(), "B") == 0);
        auto C = *scene.get("C");
        CHECK(strcmp(C.Name(), "C") == 0);

        // TEST entity ref creation
        EntityRef BToInstanceOfAref =
            entlib.makeEntityRef(B.getProperty(), instanceOfA.getProperty());
        CHECK(BToInstanceOfAref.entityPath == "..");
        EntityRef InstanceOfAToBref =
            entlib.makeEntityRef(instanceOfA.getProperty(), B.getProperty());
        CHECK(InstanceOfAToBref.entityPath == "B");
        EntityRef CToBref = entlib.makeEntityRef(C.getProperty(), B.getProperty());
        CHECK(CToBref.entityPath == "../InstanceOfA/B");
        EntityRef BToCref = entlib.makeEntityRef(B.getProperty(), C.getProperty());
        CHECK(BToCref.entityPath == "../../C");

        // TEST entity ref resolution
        auto resolvedEmptyRef = entlib.resolveEntityRef(instanceOfA.getProperty(), {});
        CHECK(not resolvedEmptyRef.has_value());
        auto resolvedInstanceOfA = entlib.resolveEntityRef(B.getProperty(), {".."});
        CHECK(resolvedInstanceOfA == instanceOfA.getProperty());
        auto resolvedB = entlib.resolveEntityRef(instanceOfA.getProperty(), {"B"});
        CHECK(resolvedB == B.getProperty());
        auto resolvedBbis = entlib.resolveEntityRef(C.getProperty(), {"../InstanceOfA/B"});
        CHECK(resolvedBbis == B.getProperty());
        auto resolvedC = entlib.resolveEntityRef(B.getProperty(), {"../../C"});
        CHECK(resolvedC == C.getProperty());

        // TEST entity ref resolution from scenes
        CHECK(not entlib.resolveEntityRef(scene.getProperty(), {".."}).has_value());
        CHECK(
            entlib.resolveEntityRef(scene.getProperty(), {"InstanceOfA"})
            == instanceOfA.getProperty());
        CHECK(entlib.resolveEntityRef(scene.getProperty(), {"InstanceOfA/B"}) == B.getProperty());
        CHECK(entlib.resolveEntityRef(scene.getProperty(), {"C"}) == C.getProperty());
        CHECK(
            entlib.resolveEntityRef(scene.getProperty(), {"InstanceOfA/B/../../C"})
            == C.getProperty());
    }

    auto testInstanceOf = [](Gen::Entity const& ent, bool testIsSet = true, bool testPrefab = true)
    {
        // ActorStates
        auto actorStates = ent.ActorStates();
        CHECK(actorStates.getDataKind() == Ent::DataKind::unionSet);
        CHECK(actorStates.size() == 3);
        auto climbEdge = actorStates.ActorStateHoldingItem();
        CHECK(climbEdge.has_value());
        CHECK(climbEdge->getProperty().getParent() == actorStates.getProperty());
        auto exitRequired = climbEdge->ItemEntityRef();
        // CHECK(exitRequired.hasValue());
        CHECK(exitRequired.get().entityPath == std::string("tutu"));
        auto dead = actorStates.ActorStateDead();
        CHECK(dead.has_value());
        auto deadData = *dead;
        auto actorStateHoldingItem = actorStates.ActorStateHoldingItem();
        CHECK(actorStateHoldingItem.has_value());
        auto itemEntityRef = actorStateHoldingItem->ItemEntityRef();
        CHECK(itemEntityRef.get().entityPath == "tutu");

        // Map and Set overridePolicy
        auto pathNodeGD = *ent.Components().TestTagsList();
        auto tags = pathNodeGD.Tags().Tags();
        CHECK(tags.getProperty().getParent()->getParent().value() == pathNodeGD.getProperty());
        CHECK(tags.size() == 3);
        CHECK(tags.get("a")->getProperty().getParent() == tags.getProperty());
        CHECK(tags.get("a")->getProperty().hasValue());
        CHECK(tags.get("b").has_value());
        CHECK(tags.get("c").has_value());
        CHECK(tags.get("c")->size() == 3);
        CHECK(tags.get("c")->count("1"));
        CHECK(tags.get("c")->count("2"));
        CHECK(tags.get("c")->count("3"));
        // Test get on map
        auto cValueSet = tags.get("c");
        CHECK(cValueSet.has_value());
        // Test get on set
        CHECK(cValueSet->count("1"));

        // TEST SubScene (without override)
        auto subScene = ent.Components().SubScene();
        CHECK(subScene.has_value());
        auto subObj = *subScene->Embedded().begin();
        CHECK(subObj.Name() == std::string("EP1-Spout_LINK_001"));
        if (testIsSet)
        {
            CHECK(not subObj.Name().isSet());
            CHECK(not subObj.hasOverride());
        }
        auto netLink = subObj.Components().NetworkLink();
        CHECK(netLink.has_value());
        CHECK(netLink->Source().get() == std::string(".EP1-Spout_"));
        CHECK(netLink->Target().get() == std::string(".EP1-crook_"));
        if (testIsSet)
        {
            CHECK(netLink->Source().isSet() == false);
            CHECK(netLink->Target().isSet() == false);
        }
        auto trans = *subObj.Components().TransformGD();
        CHECK(trans.Position()[0].get() == 0.0);

        // "InstanceOf" in sub entitites
        auto entityWithInstanceOf = *subScene->Embedded().get(R"(EntityWithInstanceOf)");
        CHECK(entityWithInstanceOf.Name() == std::string("EntityWithInstanceOf"));
        if (auto const* instOf = entityWithInstanceOf.getProperty().getInstanceOf())
        {
            CHECK(instOf == std::string("subentity2.entity"));
        }
        else
        {
            CHECK(
                entityWithInstanceOf.getProperty().getPrefab()->getInstanceOf()
                == std::string("subentity2.entity"));
        }
        auto networkLink = *entityWithInstanceOf.Components().NetworkLink();
        CHECK(networkLink.Source().get() == std::string("instance"));
        CHECK(networkLink.Target().get() == std::string("subentity2"));
        CHECK(networkLink.ThumbnailMesh().get() == std::string());

        // Test instanciation of a prefab Property
        auto stickToTerrain = *ent.Components().StickToTerrain();
        if (testPrefab)
        {
            if (stickToTerrain.getInstanceOf() == nullptr)
            {
                CHECK(stickToTerrain.getProperty().getPrefab()->getInstanceOf() != nullptr);
                CHECK(
                    stickToTerrain.getProperty().getPrefab()->getInstanceOf()
                    == std::string("test.StickToTerrain.node"));
            }
            else
            {
                CHECK(stickToTerrain.getInstanceOf() != nullptr);
                CHECK(stickToTerrain.getInstanceOf() == std::string("test.StickToTerrain.node"));
            }
        }
        CHECK(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        CHECK(stickToTerrain.ZOffset().isSet() == false);
        CHECK(stickToTerrain.ZOffset().isDefault() == false);
        CHECK(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        // Test PRoperty's InstanceOf
        auto seedPatch = *ent.Components().SeedPatch();
        CHECK(seedPatch.NoiseSizeX().isDefault());
        CHECK(seedPatch.NoiseSizeY().get() == 3.);
        CHECK(not seedPatch.NoiseOffsetX().isSet());
        CHECK(seedPatch.NoiseOffsetY().get() == 3.);
    };

    SECTION("Z")
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
        CHECK(ent.hasOverride()); // Because applyToPrefab set the old name

        ent = Gen::Entity::loadCopy(entlib, "instance_applied.entity");
        testInstanceOf(ent, false);
        CHECK(ent.hasOverride()); // Because applyToPrefab set the old name
    }

    SECTION("Test1")
    {
        // ***** Test loadProperty without schemaName *****
        // File without $schema inside
        CHECK_THROWS_AS(entlib.loadProperty("instance.entity"), Ent::UnknownSchema);
        // File with $schema inside
        auto ent = entlib.loadProperty("instance3.entity");
        CHECK(ent.getSchema()->name == "Entity");
    }
    SECTION("Test2")
    {
        // Test read instance of
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");
        auto sysCreat = ent.Components().SystemicCreature();
        CHECK(sysCreat.has_value());

        CHECK(ent.Color().hasOverride());

        // TEST read overrided value
        CHECK(sysCreat->Faction().get() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // Inherited
        CHECK(sysCreat->Life().get() == 1000.); // Inherited

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(not heightObj->Subdivision().isSet());
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        CHECK(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST read default value
        CHECK(sysCreat->Burried().get() == false); // Inherited (from default)
        CHECK(not sysCreat->Burried().isSet()); // default

        // TEST read overrided in array
        CHECK(sysCreat->ScriptList()[1].get() == std::string("b2")); // Overrided
        CHECK(sysCreat->ScriptList()[1].isSet()); // Overrided
        // TEST read Not overrided in array
        CHECK(sysCreat->ScriptList()[2].get() == std::string("c1")); // not overrided
        CHECK(not sysCreat->ScriptList()[2].isSet()); // Not overrided

        // Programatically unset
        sysCreat->ScriptList()[1].unset();
        // Programatically set
        sysCreat->ScriptList()[2].set("c2");
        CHECK(sysCreat->ScriptList()[2].get() == std::string("c2")); // Overrided
        CHECK(sysCreat->ScriptList()[2].isSet()); // Overrided

        // TEST read array
        CHECK(sysCreat->ScriptList().isSet());
        CHECK(sysCreat->ScriptList().size() == 3);

        // TEST Extand array
        sysCreat->ScriptList().push().set("d2");
        CHECK(sysCreat->ScriptList()[2].get() == std::string("c2")); // Overrided
        CHECK(sysCreat->ScriptList()[2].isSet()); // Overrided
        CHECK(sysCreat->ScriptList().size() == 4);

        // TEST SubScene (without override)
        testInstanceOf(ent);

        auto testSetOfObject = *ent.Components().TestSetOfObject();
        {
            auto setOfObject = testSetOfObject.SetOfObject();

            // Test hasOverride
            CHECK(setOfObject.get("C")->hasOverride() == false); // Already in prefab
            CHECK(setOfObject.get("A")->hasOverride()); // new in instance

            // Test remove object in set
            CHECK(setOfObject.size() == 6);
            CHECK(setOfObject.remove("B"));
            CHECK(not setOfObject.contains("B"));
            CHECK(setOfObject.remove("C"));
            CHECK(not setOfObject.contains("C"));
            CHECK(setOfObject.size() == 4);

            // Test override object in set (especially override name)
            CHECK(setOfObject.get("E").has_value());
            CHECK(not setOfObject.contains("E2"));
            CHECK(setOfObject.get("E")->Value().get() == std::string("e2"));
            CHECK(setOfObject.get("E")->Name().get() == std::string("E"));
            CHECK(setOfObject.get("F").has_value());
            CHECK(setOfObject.get("F")->Value().get() == std::string("f"));
            CHECK(setOfObject.get("F")->Name().get() == std::string("F"));
            // Test resetInstanceOf with overriden key
            setOfObject.get("F")->resetInstanceOf("ObjectInSet.node");
            CHECK(setOfObject.get("F")->Value().get() == std::string("e2"));
            CHECK(setOfObject.get("F")->Name().get() == std::string("F"));

            // Test insert the __removed__ element get back the prefab values
            // insert => makeInstanceOf => __remove__ => insert
            //          => restore values since we dont know how to reset an element when saving
            CHECK(not setOfObject.contains("G"));
            CHECK(setOfObject.add("G").getProperty().hasValue());
            CHECK(setOfObject.get("G").has_value());
            CHECK(setOfObject.get("G")->getProperty().hasValue());
            CHECK(setOfObject.get("G")->hasOverride() == true);
            CHECK(setOfObject.get("G")->Value().get() == std::string("g"));
            setOfObject.remove("G");
        }

        // Test remove entity
        auto subsceneCmp = *ent.Components().SubScene();
        CHECK(subsceneCmp.Embedded().size() == PrefabSubEntityCount);
        subsceneCmp.Embedded().remove("TestRemove");
        CHECK(subsceneCmp.Embedded().size() == PrefabSubEntityCount - 1);

        subsceneCmp.Embedded().add("PrettiestName");

        // ****************************** Test hasASuper ******************************************
        // *************** ENTITY ***************
        auto subscene = *ent.Components().SubScene();
        // new entity : Since the entityname is mandatory, it is always overriden when new
        subscene.Embedded().add("Entity");
        // entity with override
        auto entWithOverride = subscene.Embedded().get("TestSaveEntWithOverride");
        CHECK(entWithOverride.has_value());
        auto networkLink = entWithOverride->Components().NetworkLink();
        CHECK(networkLink.has_value());
        networkLink->ThumbnailMesh().set("DefaultLinkVisual.wbm");
        CHECK(entWithOverride->hasOverride());
        // entity with instanceOf overriden
        auto entWithoutOverride = subscene.Embedded().get(R"(EntityWithInstanceOfButNoOverride)");
        entWithoutOverride->resetInstanceOf("subentity2.entity");
        CHECK(entWithoutOverride->getInstanceOf() == std::string("subentity2.entity"));
        CHECK(entWithoutOverride->hasOverride());
        // *************** COMPONENT ***************
        // new Component
        auto comp = ent.Components().addAnimationEventsGeneratorGD();
        CHECK(ent.Components().AnimationEventsGeneratorGD().has_value());
        CHECK(comp.getProperty().getParent()->hasOverride()); // A new item in an array in always override
        // Component with override
        ent.Components().TestDefaultValues()->DoubleWithDefaultValue().set(36.);
        CHECK(ent.Components().TestDefaultValues().has_value());
        CHECK(ent.Components().TestDefaultValues()->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = *ent.Components().CharacterControllerGD();
        compWithInstOf.resetInstanceOf("test.CharacterControllerGD.node");
        CHECK(compWithInstOf.getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        CHECK(compWithInstOf.hasOverride());
        // *************** NODE ***************
        // new Property
        auto setOfObject = ent.Components().TestSetOfObject();
        CHECK(setOfObject);
        auto mapTest = setOfObject->MapOfObject();
        mapTest.add("NewNode");
        CHECK(mapTest.get("NewNode").has_value());
        CHECK(mapTest.get("NewNode")->hasOverride()); // Newly inserted noeds are always overriden
        // Property with override
        mapTest.get("OldNode1")->Value().set("overriden");
        CHECK(mapTest.get("OldNode1")->Value().get() == std::string("overriden"));
        CHECK(mapTest.get("OldNode1")->hasOverride());
        // Property with instanceOf overriden
        mapTest.get("OldNode2")->resetInstanceOf("OldNode2.MapOfObject.node");
        auto val = mapTest.get("OldNode2");
        CHECK(val->Value().get() == std::string("overriden"));
        CHECK(val->hasOverride());

        // Test mapInsert in map
        {
            mapTest = setOfObject->MapOfObject();
            auto newNode2 = mapTest.add("NewNode2");
            CHECK(newNode2.getDataKind() == Ent::DataKind::object);
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
            CHECK(not setOfObject3.get("G").has_value());
            setOfObject3.add("G");
            CHECK(setOfObject3.get("G")->Value().get() == std::string());
            instance3.save("instance3.entity");
        }
    }
    SECTION("Test3")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance3.entity");

        auto testSetOfObject3 = ent.Components().TestSetOfObject();
        auto setOfObject3 = testSetOfObject3->SetOfObject();

        // Test insert an element in an instance of the __removed__ one, do not resore the old values
        // insert => makeInstanceOf => __remove__ => makeInstanceOf => insert
        //          => do not restore values
        CHECK(setOfObject3.get("G")->Value().get() == std::string());
    }

    auto test_erase = [](Gen::Entity const& ent)
    {
        auto actorStates = ent.ActorStates();
        auto const pathNodeGD = *ent.Components().TestTagsList();
        auto tags = pathNodeGD.Tags().Tags();

        // Test erase in map (+save/load)
        CHECK(tags.size() == 3);
        CHECK(not tags.get("c").has_value());

        // Test insert in map (+save/load)
        auto const e = tags.get("A");
        CHECK(e.has_value());
        CHECK(e->getDataKind() == Ent::DataKind::primitiveSet);

        // Test erase in union_set (+save/load)
        CHECK(actorStates.get("EntityStatePlayer").has_value() == false);

        // Test insert in union_set (+save/load)
        CHECK(actorStates.get("ActorStateAlive").has_value());

        // Test remove component
        CHECK(ent.Components().TransformGD().has_value() == false);
        CHECK(ent.Components().SubScene().has_value() == false);
    };

    SECTION("Test4")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");

        // Test erase in union_set
        auto actorStates = ent.ActorStates();
        CHECK(actorStates.get("EntityStatePlayer").has_value());
        CHECK(actorStates.remove("EntityStatePlayer"));
        CHECK(actorStates.get("EntityStatePlayer").has_value() == false);

        // Test insert in union_set
        actorStates.addActorStateAlive();

        // Test erase in map
        auto pathNodeGD = *ent.Components().TestTagsList();
        auto tags = pathNodeGD.Tags().Tags();
        CHECK(tags.get("c").has_value());
        CHECK(tags.size() == 3);
        CHECK(tags.remove("c"));
        CHECK(tags.size() == 2);
        CHECK(tags.get("c").has_value() == false);
        CHECK(not tags.remove("c"));

        // Test insert in map
        CHECK(tags.get("A").has_value() == false);
        tags.add("A");
        CHECK(tags.begin()->first == std::string("A")); // "A" should be first

        // Test erase in Components
        CHECK(ent.Components().TransformGD().has_value());
        ent.Components().removeTransformGD();
        CHECK(ent.Components().TransformGD().has_value() == false);

        CHECK(ent.Components().SubScene().has_value());
        ent.Components().removeSubScene();
        CHECK(ent.Components().SubScene().has_value() == false);

        test_erase(ent);

        ent.save("test_erase.entity");
    }

    SECTION("Test5")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "test_erase.entity");
        test_erase(ent);
    }
    SECTION("Test6")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance2.entity");
        testInstanceOf(ent, true, false);
    }
    auto testInstanceOverrideSubscene = [](Gen::Entity const& ent)
    {
        // TEST SubScene (with override)
        auto const subScene = ent.Components().SubScene();
        CHECK(subScene.has_value());
        auto const subObj = subScene->Embedded().get("EP1-Spout_LINK_001");
        CHECK(subObj->Name() == std::string("EP1-Spout_LINK_001"));

        // Test an overrided Component
        auto const netLink = subObj->Components().NetworkLink();
        CHECK(netLink.has_value());
        CHECK(netLink->Source().get() == std::string(".EP1-Spout_"));
        CHECK(netLink->Source().isSet() == false);
        CHECK(netLink->Target().get() == std::string(".EP1-crook_2"));
        CHECK(netLink->Target().isSet());

        // Test a not overrided Component
        auto const trans = subObj->Components().TransformGD();
        CHECK(trans.has_value());
        CHECK(trans->Position()[0].get() == 0.0);
    };
    SECTION("Test7")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_override_subscene.entity");
        testInstanceOverrideSubscene(ent);
        ent.save("instance_override_subscene.copy.entity");
    }
    SECTION("Test8")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_override_subscene.copy.entity");
        testInstanceOverrideSubscene(ent);
    }
    SECTION("Test9")
    {
        // Test write instance of
        auto ent = Gen::Entity::loadCopy(entlib, "instance.copy.entity");
        auto sysCreat = ent.Components().SystemicCreature();
        CHECK(sysCreat.has_value());

        // Test remove object in set
        auto testSetOfObject = *ent.Components().TestSetOfObject();
        auto setOfObject = testSetOfObject.SetOfObject();
        CHECK(setOfObject.get("B").has_value() == false);
        CHECK(setOfObject.get("C").has_value() == false);
        CHECK(setOfObject.size() == 4);

        // Test override object in set (especially override name)
        CHECK(setOfObject.get("E").has_value());
        CHECK(setOfObject.get("E2").has_value() == false);
        CHECK(setOfObject.get("E")->Value().get() == std::string("e2"));
        CHECK(setOfObject.get("E")->Name().get() == std::string("E"));

        // Test insert the __removed__ element get back the prefab values
        // insert => makeInstanceOf => __remove__ => insert
        //          => restore values since we dont know how to reset an element when saving
        CHECK(setOfObject.get("G").has_value() == false);
        setOfObject.add("G");
        CHECK(setOfObject.get("G")->Value().get() == std::string("g"));

        // Test remove entity
        auto subsceneCmp = *ent.Components().SubScene();
        // Removed : TestRemove. Added : PrettiestName, Entity
        CHECK(subsceneCmp.Embedded().size() == PrefabSubEntityCount + 1);

        // ****************************** Test hasASuper ******************************************
        // *************** ENTITY ***************
        auto subscene = *ent.Components().SubScene();
        // new entity
        auto ent2 = subscene.Embedded().get("Entity");
        CHECK(ent2.has_value());
        CHECK(ent2->hasOverride()); // Name is always overriden since it is alway declared
        // entity with override
        ent2 = subscene.Embedded().get("TestSaveEntWithOverride");
        CHECK(ent2.has_value());
        CHECK(ent2->hasOverride());
        // entity with instanceOf overriden
        ent2 = subscene.Embedded().get("EntityWithInstanceOfButNoOverride");
        CHECK(ent2.has_value());
        CHECK(ent2->getInstanceOf() == std::string("subentity2.entity"));
        CHECK(ent2->hasOverride());

        // *************** COMPONENT ***************
        // new Component (A new component is override true)
        CHECK(ent.Components().AnimationEventsGeneratorGD().has_value());
        CHECK(ent.Components().AnimationEventsGeneratorGD()->getProperty().getParent()->hasOverride());
        // Component with override
        CHECK(ent.Components().TestDefaultValues().has_value());
        CHECK(ent.Components().TestDefaultValues()->DoubleWithDefaultValue().get() == 36.);
        CHECK(ent.Components().TestDefaultValues()->hasOverride());
        // Component with instanceOf overriden
        auto compWithInstOf = *ent.Components().CharacterControllerGD();
        CHECK(compWithInstOf.getInstanceOf() == std::string("test.CharacterControllerGD.node"));
        CHECK(compWithInstOf.hasOverride());
        // *************** NODE ***************
        // new Property
        auto pathNodeGD = *ent.Components().TestSetOfObject();
        auto mapTest = pathNodeGD.MapOfObject();
        CHECK(mapTest.get("NewNode").has_value());
        // Newly inserted Nodes are overriden
        CHECK(mapTest.get("NewNode")->hasOverride());
        // Property with override
        CHECK(mapTest.get("OldNode1")->Value().get() == std::string("overriden"));
        CHECK(mapTest.get("OldNode1")->hasOverride());
        // Property with instanceOf overriden
        CHECK(mapTest.get("OldNode2")->Value().get() == std::string("overriden"));
        CHECK(mapTest.get("OldNode2")->hasOverride());

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(not heightObj->Subdivision().isSet());
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        CHECK(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST read overrided value
        CHECK(sysCreat->Faction().get() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // Inherited
        CHECK(sysCreat->Life().get() == 1000.); // Inherited

        // TEST read default value
        CHECK(sysCreat->Burried().get() == false); // Inherited (from default)
        CHECK(not sysCreat->Burried().isSet()); // default

        // TEST read programatically overrided in array
        CHECK(sysCreat->ScriptList()[1].get() == std::string("b1")); // No more overrided
        CHECK(not sysCreat->ScriptList()[1].isSet()); // No more overrided
        // TEST read programatically unset in array
        CHECK(sysCreat->ScriptList()[2].get() == std::string("c2")); // Overrided
        CHECK(sysCreat->ScriptList()[2].isSet()); // Overrided

        // TEST read programatically extand array
        CHECK(sysCreat->ScriptList()[3].get() == std::string("d2")); // Overrided
        CHECK(sysCreat->ScriptList()[3].isSet()); // Overrided

        // TEST read extanded array
        CHECK(sysCreat->ScriptList().isSet());
        CHECK(sysCreat->ScriptList().size() == 4);

        // TEST override value from code
        CHECK(sysCreat->BehaviorState().get() == std::string("Overrided")); // set. changed.
        CHECK(sysCreat->BehaviorState().isSet()); // set. changed.

        testInstanceOf(ent);

        ent.save("instance.copy.entity");
    }
    SECTION("Test10")
    {
        // Test create detached
        auto ent = Gen::Entity::loadCopy(entlib, "instance.entity");

        auto detached = ent.detach();

        CHECK(detached.Color().hasOverride());

        auto sysCreat = detached.Components().SystemicCreature();

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(not heightObj->Subdivision().isSet());
        CHECK(not heightObj->Subdivision().hasDefaultValue()); // Prefab has value
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        CHECK(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST default values
        CHECK(sysCreat->Burried().get() == false); // default
        CHECK(not sysCreat->Burried().isSet()); // default
        CHECK(sysCreat->Burried().hasDefaultValue()); // default
        CHECK(sysCreat->Name().get() == std::string()); // default
        CHECK(not sysCreat->Name().isSet()); // default

        // TEST read setted values
        CHECK(sysCreat->Faction().get() == std::string("Plouf")); // set
        CHECK(not sysCreat->Faction().hasDefaultValue()); // is set in instance
        CHECK(sysCreat->Faction().isSet()); // is set
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set
        CHECK(sysCreat->Inventory().isSet()); // is set

        detached.save("instance.detached.entity");
    }
    SECTION("Test11")
    {
        // Test read detached
        auto ent = Gen::Entity::loadCopy(entlib, "instance.detached.entity");

        auto sysCreat = ent.Components().SystemicCreature();

        // TEST read inherited values in inherited component
        auto heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(heightObj->Subdivision().isSet());
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // TEST default values
        CHECK(sysCreat->Burried().get() == false); // default
        CHECK(not sysCreat->Burried().isSet()); // default
        CHECK(sysCreat->Name().get() == std::string()); // default
        CHECK(not sysCreat->Name().isSet()); // default

        // TEST read setted values
        CHECK(sysCreat->Faction().get() == std::string("Plouf")); // set
        CHECK(sysCreat->Faction().isSet()); // is set
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey")); // set
        CHECK(sysCreat->Inventory().isSet()); // is set
    }
    SECTION("Test12")
    {
        // Test makeInstanceOf
        auto prefab = Gen::Entity::loadCopy(entlib, "prefab.entity");
        auto instanceOf = prefab.makeInstanceOf();

        // Test instanciation of a prefab Property
        auto stickToTerrain = instanceOf.Components().addStickToTerrain();
        CHECK_THROWS_AS(
            stickToTerrain.resetInstanceOf("C:/test.StickToTerrain.node"), std::runtime_error);
        stickToTerrain.resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain.resetInstanceOf(
            (current_path() / "test.StickToTerrain.node").generic_u8string().c_str());
        CHECK(stickToTerrain.getInstanceOf() != nullptr);
        stickToTerrain.NormalRatio().set(0.6);
        stickToTerrain.precisionRadius().set(0.6e-15);

        CHECK(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        CHECK(fabs(stickToTerrain.precisionRadius().get() - 0.6e-15) < 0.0000001);
        CHECK(stickToTerrain.ZOffset().isSet() == false);
        CHECK(stickToTerrain.ZOffset().isDefault() == false);
        CHECK(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        CHECK(instanceOf.Components().NetworkNode().has_value());
        instanceOf.save("instance.create.entity");
    }
    auto testCreateInstanceOf = [&entlib](char const* _instancePath)
    {
        // Test read instance of
        auto const ent = Gen::Entity::loadCopy(entlib, _instancePath);

        // Test instanciation of a prefab Property
        auto stickToTerrain = *ent.Components().StickToTerrain();
        CHECK(stickToTerrain.getInstanceOf() != nullptr);
        CHECK(fabs(stickToTerrain.NormalRatio().get() - 0.6) < 0.0001);
        CHECK(stickToTerrain.ZOffset().isSet() == false);
        CHECK(stickToTerrain.ZOffset().isDefault() == false);
        CHECK(fabs(stickToTerrain.ZOffset().get() - 10.) < 0.0001);

        // TEST read inherited values in inherited component
        auto const heightObj = ent.Components().HeightObj();
        CHECK(heightObj.has_value());
        CHECK(heightObj->Subdivision().get() == 0);
        CHECK(not heightObj->Subdivision().isSet());
        CHECK(heightObj->DisplaceNoiseList()[0].MapChannel().get() == 51248);
        CHECK(not heightObj->DisplaceNoiseList()[0].MapChannel().isSet());

        // Test read prefab
        auto const sysCreat = ent.Components().SystemicCreature();
        CHECK(sysCreat.has_value());

        // TEST read setted values
        CHECK(sysCreat->Faction().get() == std::string("Shamans"));
        CHECK(not sysCreat->Faction().isSet()); // Not overrided
        CHECK(sysCreat->Inventory().get() == std::string("KaiWOLgrey"));
        CHECK(not sysCreat->Inventory().isSet()); // Not overrided

        // TEST read array
        CHECK(not sysCreat->ScriptList().isSet()); // Arrays are NOT always set
        CHECK(sysCreat->ScriptList().size() == 3);

        // TEST default values
        CHECK(sysCreat->Burried().get() == false); // default
        CHECK(not sysCreat->Burried().isSet()); // default
        CHECK(sysCreat->Name().get() == std::string()); // default
        CHECK(not sysCreat->Name().isSet()); // default
    };
    SECTION("Test13")
    {
        testCreateInstanceOf("instance.create.entity");
    }
    SECTION("Test14")
    {
        // Test resetInstanceOf
        auto instanceOf = Gen::Entity::create(entlib);

        instanceOf.Name().set("TestResetInstanceOf");

        instanceOf.resetInstanceOf("prefab.entity");
        CHECK(instanceOf.Components().NetworkNode().has_value());
        instanceOf.Components().TransformGD()->getProperty().getSchema()->properties;

        // Test instanciation of a prefab Property
        auto stickToTerrain = instanceOf.Components().addStickToTerrain();
        stickToTerrain.resetInstanceOf("test.StickToTerrain.node");
        stickToTerrain.NormalRatio().set(0.6);

        instanceOf.save("setInstanceOf.entity");
    }
    SECTION("Test15")
    {
        testCreateInstanceOf("setInstanceOf.entity");
    }

    // ******************* Test load/save complex entity pinetreec50cmh5mbasic ********************
    SECTION("Test16")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "pinetreec50cmh5mbasic.entity");
        ent.save("pinetreec50cmh5mbasic.copy.entity");
        auto copyEnt = Gen::Entity::loadCopy(entlib, "pinetreec50cmh5mbasic.copy.entity");

        // TEST keeping empty component after entity save
        CHECK(copyEnt.Components().EventHandlerGD().has_value());
    }

    // ******************* Test the override of an entity in a SubScene ***************************
    auto testOverrideSubEntity = [](Gen::Entity const& ent)
    {
        auto const subScenecomp = *ent.Components().SubScene();
        auto const allSubEntities = subScenecomp.Embedded();
        CHECK(allSubEntities.size() == PrefabSubEntityCount);
        auto ep1 = subScenecomp.Embedded().get("EP1-Spout_LINK_001");
        REQUIRE(ep1);
        CHECK(ep1->Color()[0].get() == 42);
    };
    SECTION("Test17")
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
        CHECK(allSubEntities.size() == PrefabSubEntityCount + 1);
        auto const ent0 = subScenecomp.Embedded().get("EP1-Spout_LINK_001");
        auto const ent1 = subScenecomp.Embedded().get("EP1-Spout_LINK_001_added");
        CHECK(ent0->Name() == std::string("EP1-Spout_LINK_001"));
        auto const red = ent0->Color()[0];
        CHECK(not ent0->hasOverride());
        CHECK(red.get() == 255);
        CHECK(ent1->Name() == std::string("EP1-Spout_LINK_001_added"));
        CHECK(ent1->Color()[0].get() == 44);
    };
    SECTION("Test18")
    {
        auto ent = Gen::Entity::loadCopy(entlib, "instance_add_subentity.entity");
        testAddSubEntity(ent);
        ent.save("instance_add_subentity.copy.entity");
        auto copyEnt = Gen::Entity::loadCopy(entlib, "instance_add_subentity.copy.entity");
        testAddSubEntity(copyEnt);
    }
    SECTION("Test access subscene override")
    {
        // Test access subscene override
        auto ent = Gen::Entity::load(entlib, "entity-subscene.entity").makeInstanceOf();
        auto subs = *ent.Components().SubScene();

        CHECK(ent.hasOverride()); // makeInstanceOf does override the instanceOf
        CHECK(not subs.Embedded().empty());

        subs.Embedded().get("wolf_skeleton_lush")->Components().addActorGD().InSpiritWorld().set(true);
        ent.save("entity-subscene-override-saved.entity");

        auto ovrdEntt = Gen::Entity::loadCopy(entlib, "entity-subscene-override-saved.entity");
        auto ovrdSubs = *ovrdEntt.Components().SubScene();

        //Test that we properly still have access to the prefab subscene entities
        CHECK(not ovrdSubs.Embedded().empty());
    }

    SECTION("Test20")
    {
        auto ent = Gen::Entity::loadCopy(entlib, R"(Creature/my_creature_level2.entity)");
        auto entities = ent.Components().SubScene()->Embedded();
        auto firstEnt = *begin(entities);
        auto subscene = firstEnt.Components().SubScene()->Embedded();
        CHECK(subscene.size() == 1);
        CHECK(strcmp(subscene.begin()->Name(), "default_level2") == 0);
    }

    // ******************* Test the EntLibException ***********************************************
    SECTION("Test21")
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
            CHECK(strstr(what, "this_component_doesnt_exist") != nullptr);
        }
        CHECK(exceptionThrown);
    }

    SECTION("Test default color")
    {
        auto ent = Gen::Entity::create(entlib);
        ent.Name().set("TestDefaultColor");

        CHECK((std::array<double, 4>(ent.Color())) == (std::array<double, 4>{1., 1., 1., 1.}));
    }
}
