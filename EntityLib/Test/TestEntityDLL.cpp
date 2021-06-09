#pragma warning(push, 0)
#include <ciso646>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning(pop)

#include <EntityLib.h>
#include <ComponentMerge.h>

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
        for (auto&& name_sub : subschema.properties)
        {
            displaySubSchema(std::get<0>(name_sub), *std::get<1>(name_sub), indent + "  ");
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

int main(int argc, char** argv)
try
{
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

    Ent::EntityLib entlib("X:/", doMergeComponents);
    using namespace std::filesystem;

    entlib.rawdataPath = current_path(); // It is a hack to work in the working dir
#ifdef _DEBUG
    entlib.validationEnabled = false;
#else
    entlib.validationEnabled = true;
#endif

    ENTLIB_ASSERT(Ent::format("Toto %d", 37) == "Toto 37");

    {
        std::map<std::string, int> emptyMap;
        ENTLIB_CHECK_EXCEPTION(AT(emptyMap, "not"), Ent::InvalidKey);
    }

    using EntityPtr = std::unique_ptr<Ent::Entity>;

    // Test $ref links in entlib.schema.schema.allDefinitions
    char const* colorRef = "./RuntimeComponents.json#/definitions/Color";
    ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(colorRef) == 1);

    // Check Ent::Subschema::getUnionTypesMap
    char const* cinematicGDRef = "./RuntimeComponents.json#/definitions/CinematicGD";
    Ent::Subschema const& cinematicGDSchema = entlib.schema.schema.allDefinitions.at(cinematicGDRef);
    Ent::Subschema const& scriptEventUnionSchema =
        cinematicGDSchema.properties.at("ScriptEvents")->singularItems->get();
    auto&& nameToTypeMap = scriptEventUnionSchema.getUnionTypesMap();
    ENTLIB_ASSERT(size(nameToTypeMap) == 12);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTest") == 1);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTriggerEventHandlerPost") == 1);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTestEndCurrentSequence") == 1);

    // Ensure that all components have a ref and is in entlib.schema.schema.allDefinitions
    for (auto&& name_schema : entlib.schema.components)
    {
        auto&& absRef = std::get<1>(name_schema)->name;
        ENTLIB_ASSERT(absRef.find("./") == 0);
        ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(absRef) == 1);
    }

    auto testPrefabEntity = [](Ent::Entity const* ent) {
        // ActorStates
        Ent::Node const& actorStates = ent->getActorStates();
        ENTLIB_ASSERT(actorStates.getDataType() == Ent::DataType::array);
        ENTLIB_ASSERT(actorStates.size() == 2);
        Ent::Node const* actorState = actorStates.at(0llu);
        ENTLIB_ASSERT(actorState != nullptr);
        ENTLIB_ASSERT(actorState->getSchema()->getUnionNameField() == std::string("className"));
        ENTLIB_ASSERT(actorState->getSchema()->getUnionDataField() == std::string("classData"));
        Ent::Node const* climbEdge = actorState->getUnionData();
        char const* climbEdgeType = actorState->getUnionType();
        ENTLIB_ASSERT(strcmp(climbEdgeType, "ActionClimbEdge") == 0);
        ENTLIB_ASSERT(climbEdge != nullptr);
        Ent::Node const* exitRequired = climbEdge->at("locomotionMode");
        ENTLIB_ASSERT(exitRequired != nullptr);
        ENTLIB_ASSERT(exitRequired->getString() == std::string("crouch"));
        Ent::Node const* actorState2 = actorStates.at(1llu);
        ENTLIB_ASSERT(actorState2 != nullptr);
        Ent::Node const* cinematic = actorState2->getUnionData();
        ENTLIB_ASSERT(cinematic != nullptr);
        Ent::Node const* type = cinematic->at("Type");
        ENTLIB_ASSERT(type != nullptr);
        ENTLIB_ASSERT(type->getInt() == -1);

        // Map and Set overridePolicy
        Ent::Component const* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node const* tags = pathNodeGD->root.at("Tags")->at("Tags");
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->at(0llu)->at(0llu)->getString() == std::string("a"));
        ENTLIB_ASSERT(tags->at(1llu)->at(0llu)->getString() == std::string("c"));
        ENTLIB_ASSERT(tags->at(1llu)->at(1llu)->size() == 1);
        ENTLIB_ASSERT(tags->at(1llu)->at(1llu)->at(0llu)->getString() == std::string("2"));
        // Test mapGet on map and set
        ENTLIB_ASSERT(tags->mapGet("a")->at(1llu)->mapGet("1")->getString() == std::string("1"));

        // Test default value
        Ent::Component const* voxelSimulationGD = ent->getComponent("VoxelSimulationGD");
        ENTLIB_ASSERT(voxelSimulationGD->root.at("TransmissionBySecond")->getFloat() == 100.);
        ENTLIB_ASSERT(voxelSimulationGD->root.at("TransmissionBySecond")->isDefault());
        ENTLIB_ASSERT(
            voxelSimulationGD->root.getTypeName()
            == std::string("./RuntimeComponents.json#/definitions/VoxelSimulationGD"));

        // TEST read inherited values in inherited component
        Ent::Component const* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->isDefault());
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getDefaultInt() == 3);
        ENTLIB_ASSERT(
            heightObj->root.at("Subdivision")->getSchema()->userMeta["testUserMetatdata"].get<int>()
            == 42);

        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // Test read Thumbnail
        ENTLIB_ASSERT(ent->getThumbnail() != nullptr);
        ENTLIB_ASSERT(ent->getThumbnail() == std::string("TestThumbnail"));

        // Test read prefab
        Ent::Component const* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Shamans")); // set
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->isSet()); // is set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->isSet()); // is set

        // TEST comment
        ENTLIB_ASSERT(
            sysCreat->root.at("BehaviorState")->getString() == std::string("W/*at*/c//h")); // set

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST SubScene
        Ent::SubSceneComponent const* subScenecomp = ent->getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == 1);
        ENTLIB_ASSERT(allSubEntities.front()->getName() == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(allSubEntities.front()->getColor()[0] == 255);

        // TEST union
        Ent::Component const* cinematicGD = ent->getComponent("CinematicGD");
        Ent::Node const* scriptEvents = cinematicGD->root.at("ScriptEvents");
        ENTLIB_ASSERT(scriptEvents->getDataType() == Ent::DataType::array);

        // Read Union type
        Ent::Node const* oneOfScripts = scriptEvents->at(0llu);
        ENTLIB_ASSERT(oneOfScripts->getDataType() == Ent::DataType::oneOf);
        Ent::Node const* cineEvent = oneOfScripts->getUnionData();
        ENTLIB_ASSERT(cineEvent != nullptr);
        ENTLIB_ASSERT(
            cineEvent->getTypeName()
            == std::string(
                R"(./RuntimeComponents.json#/definitions/CineEventTriggerEventHandlerPost)"));
        auto fieldNames = cineEvent->getFieldNames();
        ENTLIB_ASSERT(fieldNames[1] == std::string("EventName"));
        ENTLIB_ASSERT(fieldNames[2] == std::string("Super"));

        Ent::Node const* nbEnt = cineEvent->at("EventName");
        ENTLIB_ASSERT(nbEnt != nullptr);
        ENTLIB_ASSERT(nbEnt->getDataType() == Ent::DataType::string);
        ENTLIB_ASSERT(nbEnt->getString() == std::string("Toto"));

        // TEST sub-object with non-default values
        Ent::Component const* ldprimitive = ent->getComponent("LDPrimitive");
        Ent::Node const* primitiveData = ldprimitive->root.at("PrimitiveData");
        ENTLIB_ASSERT(primitiveData->at("Height")->getFloat() == 42.0);

        // TEST Default size for array is minItems
        Ent::Component const* physicsGD = ent->getComponent("PhysicsGD");
        Ent::Node const* axisRestriction = physicsGD->root.at("AxisRestriction");
        ENTLIB_ASSERT(axisRestriction->size() == 3);

        // Test default values related to a property of type class/struct.
        Ent::Component const* characterController = ent->getComponent("CharacterControllerGD");
        Ent::Node const* slideData = characterController->root.at("SlideData");
        Ent::Node const* adherenceMin = slideData->at("adherenceMinDependingOnTheSlope");
        Ent::Node const* in = adherenceMin->at("in");
        ENTLIB_ASSERT(in->size() == 2);
        ENTLIB_ASSERT(in->at(0llu)->getFloat() == -1.);
        ENTLIB_ASSERT(in->at(1llu)->getFloat() == 0.5);

        // Ensure that default values of property are not poluted by default values of pointer class
        Ent::Component const* testDefaultValues = ent->getComponent("TestDefaultValues");
        ENTLIB_ASSERT(testDefaultValues != nullptr);
        Ent::Node const* propertyWithDefault = testDefaultValues->root.at("propertyWithDefault");
        Ent::Node const* propertyWithDefault2 = propertyWithDefault->at("propertyWithDefault2");
        ENTLIB_ASSERT(propertyWithDefault2->at("A")->getInt() == 3);
        ENTLIB_ASSERT(propertyWithDefault2->at("B")->getInt() == 0);
        Ent::Node const* propertyWithDefault3 = propertyWithDefault->at("propertyWithDefault3");
        ENTLIB_ASSERT(propertyWithDefault3->at("A")->getInt() == 3);
        ENTLIB_ASSERT(propertyWithDefault3->at("B")->getInt() == 0);
    };

    {
        Ent::Entity ent(entlib);
        ent.setInstanceOf("prefab.entity");
        ENTLIB_ASSERT(not ent.hasOverride());
        ENTLIB_ASSERT(ent.getInstanceOf() == std::string("prefab.entity"));
    }

    {
        EntityPtr ent = entlib.loadEntity("prefab.entity");

        // Test saveNode
        Ent::Component const* heightObj = ent->getComponent("HeightObj");
        heightObj->root.saveNode("test.HeightObj.node");

        testPrefabEntity(ent.get());
        // Test mapErase in set of primitive
        Ent::Component* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node* tags = pathNodeGD->root.at("Tags")->at("Tags");
        auto primSet = tags->mapGet("a")->at(1llu);
        ENTLIB_CHECK_EXCEPTION(primSet->mapErase("1"), Ent::BadArrayType);

        // Set Union type and override
        Ent::Component* cinematicGD = ent->getComponent("CinematicGD");
        Ent::Node* scriptEvents = cinematicGD->root.at("ScriptEvents");
        Ent::Node* oneOfScripts2 = scriptEvents->at(1llu);
        ENTLIB_ASSERT(oneOfScripts2->getDataType() == Ent::DataType::oneOf);
        ENTLIB_ASSERT(
            oneOfScripts2->getUnionType() == std::string("CineEventTriggerEventHandlerPost"));
        oneOfScripts2->setUnionType("CineEventTestCurrentGameState");
        ENTLIB_CHECK_EXCEPTION(oneOfScripts2->setUnionType("ThisTypeDoesntExist"), Ent::BadUnionType);
        Ent::Node* testCurrentState = oneOfScripts2->getUnionData();
        ENTLIB_ASSERT(oneOfScripts2->getUnionType() == std::string("CineEventTestCurrentGameState"));
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
        ENTLIB_ASSERT(oneOfScripts4->getUnionType() == std::string("CineEvent"));
        ENTLIB_ASSERT(scriptEvents->at(3llu) == oneOfScripts4);

        // TEST simple entity ref creation
        Ent::Component* testEntityRef = ent->addComponent("TestEntityRef");
        ENTLIB_ASSERT(testEntityRef != nullptr);
        ENTLIB_ASSERT(testEntityRef->root.at("TestRef")->getEntityRef().entityPath.empty());
        testEntityRef->root.at("TestRef")->setEntityRef(ent->makeEntityRef(*ent));
        ENTLIB_ASSERT(testEntityRef->root.at("TestRef")->getEntityRef().entityPath == ".");
        Ent::SubSceneComponent* subScenecomp = ent->getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        testEntityRef->root.at("TestRef")->setEntityRef(ent->makeEntityRef(*allSubEntities.front()));

        // TEST MaxActivationLevel
        ent->setMaxActivationLevel(Ent::ActivationLevel::InWorld);

        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat->root.at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Name")->isSet()); // default
        sysCreat->root.at("Name")->setString("Shamane_male");
        entlib.saveEntity(*ent, "prefab.copy.entity");

        // TEST SubScene detach
        const auto& subEntities = ent->getSubSceneComponent()->embedded->getObjects();
        ENTLIB_ASSERT(not subEntities.empty());
        std::vector<Ent::Entity*> originalSubEntities;
        std::transform(
            begin(subEntities),
            end(subEntities),
            std::back_inserter(originalSubEntities),
            [](auto&& entityPtr) { return entityPtr.get(); });
        ENTLIB_ASSERT(not originalSubEntities.empty());
        auto detachedSubScene = ent->getSubSceneComponent()->detachEmbedded();
        ENTLIB_ASSERT(ent->getSubSceneComponent()->embedded->getObjects().empty());
        std::vector<Ent::Entity*> detachedSubEntities;
        std::transform(
            begin(detachedSubScene->getObjects()),
            end(detachedSubScene->getObjects()),
            std::back_inserter(detachedSubEntities),
            [](auto&& entityPtr) { return entityPtr.get(); });
        ENTLIB_ASSERT(std::equal(
            begin(originalSubEntities), end(originalSubEntities), begin(detachedSubEntities)));

        ent->removeSubSceneComponent();
        ent->addSubSceneComponent()->makeEmbedded(true);
        entlib.saveEntity(*ent, "prefab.emptyembbeded.entity"); // to check the schema

        // TEST arrays default values
        ent->removeComponent("TransformGD");
        Ent::Component* transformGD = ent->addComponent("TransformGD");
        Ent::Node* mat33 = transformGD->root.at("Matrix");
        auto testMat33 = [&]() {
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
        mat33 = testDefaultValues->root.at("Matrix");
        testMat33();
        mat33 = testDefaultValues->root.at("Matrix2");
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
                                         tl::optional<size_t> prefabSize,
                                         tl::optional<size_t> overrideSize) {
            Ent::Node const* node = comp->root.at(_arrayName);
            ENTLIB_ASSERT(node);
            ENTLIB_ASSERT(node->hasPrefabValue() == prefabSize.has_value());
            ENTLIB_ASSERT(node->hasOverride() == overrideSize.has_value());
            ENTLIB_ASSERT(
                node->getRawSize(Ent::OverrideValueLocation::Default).value() == defaultSize);
            ENTLIB_ASSERT(node->getRawSize(Ent::OverrideValueLocation::Prefab) == prefabSize);
            ENTLIB_ASSERT(node->getRawSize(Ent::OverrideValueLocation::Override) == overrideSize);
        };
        testArrayMember("DefaultValue", 2, tl::nullopt, tl::nullopt);
        testArrayMember("PrefabValue", 2, 4, tl::nullopt);
        testArrayMember("OverridedDefaultValue", 2, tl::nullopt, 3);
        testArrayMember("OverridedPrefabValue", 2, 4, 3);
    }
    {
        // Test the readOnly prefab.entity
        std::shared_ptr<Ent::Entity const> ent = entlib.loadEntityReadOnly("prefab.entity");
        testPrefabEntity(ent.get());
    }
    {
        // Test write prefab
        EntityPtr ent = entlib.loadEntity("prefab.copy.entity");

        testPrefabEntity(ent.get());

        // TEST MaxActivationLevel
        ENTLIB_ASSERT(ent->getMaxActivationLevel() == Ent::ActivationLevel::InWorld);

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);
        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Shamans")); // set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // set

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST default values unchanged
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST changed values
        ENTLIB_ASSERT(
            sysCreat->root.at("Name")->getString() == std::string("Shamane_male")); // set. changed.
        ENTLIB_ASSERT(sysCreat->root.at("Name")->isSet()); // set. changed.

        // TEST simple entity refs resolution
        Ent::Component* testEntityRef = ent->getComponent("TestEntityRef");
        ENTLIB_ASSERT(testEntityRef != nullptr);
        ENTLIB_ASSERT(testEntityRef->root.at("TestRef")->isSet());
        Ent::EntityRef entityRef = testEntityRef->root.at("TestRef")->getEntityRef();
        Ent::Entity* resolvedEntity = ent->resolveEntityRef(entityRef);
        ENTLIB_ASSERT(resolvedEntity != nullptr);

        Ent::SubSceneComponent* subScenecomp = ent->getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == 1);
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
        Ent::Entity& instanceOfA = *scene->getObjects().front();
        ENTLIB_ASSERT(strcmp(instanceOfA.getName(), "InstanceOfA") == 0);
        Ent::SubSceneComponent* subSceneComp = instanceOfA.getSubSceneComponent();
        ENTLIB_ASSERT(subSceneComp != nullptr);
        ENTLIB_ASSERT(subSceneComp->isEmbedded);
        ENTLIB_ASSERT(subSceneComp->embedded->getObjects().size() == 1);
        Ent::Entity& B = *subSceneComp->embedded->getObjects().front();
        ENTLIB_ASSERT(strcmp(B.getName(), "B") == 0);
        Ent::Entity& C = *scene->getObjects()[1];
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

    auto testInstanceOf = [](Ent::Entity const& ent) {
        // ActorStates
        Ent::Node const& actorStates = ent.getActorStates();
        ENTLIB_ASSERT(actorStates.getDataType() == Ent::DataType::array);
        ENTLIB_ASSERT(actorStates.size() == 3);
        Ent::Node const* actorState = actorStates.at(0llu);
        ENTLIB_ASSERT(actorState != nullptr);
        Ent::Node const* climbEdge = actorState->getUnionData();
        ENTLIB_ASSERT(climbEdge != nullptr);
        Ent::Node const* exitRequired = climbEdge->at("locomotionMode");
        ENTLIB_ASSERT(exitRequired != nullptr);
        ENTLIB_ASSERT(exitRequired->getString() == std::string("crouch"));
        Ent::Node const* actorState2 = actorStates.at(1llu);
        ENTLIB_ASSERT(actorState2 != nullptr);
        Ent::Node const* cinematic = actorState2->getUnionData();
        ENTLIB_ASSERT(cinematic != nullptr);
        Ent::Node const* type = cinematic->at("Type");
        ENTLIB_ASSERT(type != nullptr);
        ENTLIB_ASSERT(type->getInt() == 13);
        Ent::Node const* actorState3 = actorStates.at(2llu);
        ENTLIB_ASSERT(actorState3 != nullptr);
        Ent::Node const* chosen = actorState3->getUnionData();
        ENTLIB_ASSERT(chosen != nullptr);
        Ent::Node const* exitRequ = chosen->at("ExitRequired");
        ENTLIB_ASSERT(exitRequ != nullptr);
        ENTLIB_ASSERT(exitRequ->getBool() == true);

        // Map and Set overridePolicy
        Ent::Component const* pathNodeGD = ent.getComponent("PathNodeGD");
        Ent::Node const* tags = pathNodeGD->root.at("Tags")->at("Tags");
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->at(0llu)->at(0llu)->getString() == std::string("a"));
        ENTLIB_ASSERT(tags->at(1llu)->at(0llu)->getString() == std::string("b"));
        ENTLIB_ASSERT(tags->at(2llu)->at(0llu)->getString() == std::string("c"));
        ENTLIB_ASSERT(tags->at(2llu)->at(1llu)->size() == 3);
        ENTLIB_ASSERT(tags->at(2llu)->at(1llu)->at(0llu)->getString() == std::string("1"));
        ENTLIB_ASSERT(tags->at(2llu)->at(1llu)->at(1llu)->getString() == std::string("2"));
        ENTLIB_ASSERT(tags->at(2llu)->at(1llu)->at(2llu)->getString() == std::string("3"));
        // Test mapGet on map
        auto cPair = tags->mapGet("c");
        ENTLIB_ASSERT(cPair != nullptr);
        ENTLIB_ASSERT(cPair->at(0llu)->getString() == std::string("c"));
        // Test mapGet on set
        auto cValueSet = cPair->at(1llu);
        ENTLIB_ASSERT(cValueSet->mapGet("1")->getString() == std::string("1"));

        // TEST SubScene (without override)
        Ent::SubSceneComponent const* subScene = ent.getSubSceneComponent();
        ENTLIB_ASSERT(subScene != nullptr);
        ENTLIB_ASSERT(subScene->isEmbedded);
        Ent::Entity const& subObj = *subScene->embedded->getObjects()[0];
        ENTLIB_ASSERT(subObj.getName() == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(not subObj.getNameValue().isSet());
        ENTLIB_ASSERT(not subObj.hasOverride());
        Ent::Component const* netLink = subObj.getComponent("NetworkLink");
        ENTLIB_ASSERT(netLink != nullptr);
        ENTLIB_ASSERT(netLink->root.at("Source")->getString() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->root.at("Source")->isSet() == false);
        ENTLIB_ASSERT(netLink->root.at("Target")->getString() == std::string(".EP1-crook_"));
        ENTLIB_ASSERT(netLink->root.at("Target")->isSet() == false);
        Ent::Component const* trans = subObj.getComponent("TransformGD");
        ENTLIB_ASSERT(trans->root.at("Position")->at(0llu)->getFloat() == 0.0);

        // Test instanciation of a prefab Node
        Ent::Component const* stickToTerrain = ent.getComponent("StickToTerrain");
        ENTLIB_ASSERT(fabs(stickToTerrain->root.at("NormalRatio")->getFloat() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain->root.at("ZOffset")->isSet() == false);
        ENTLIB_ASSERT(stickToTerrain->root.at("ZOffset")->isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain->root.at("ZOffset")->getFloat() - 10.) < 0.0001);
    };

    {
        // Test read instance of
        EntityPtr ent = entlib.loadEntity("instance.entity");
        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        ENTLIB_ASSERT(ent->getColorValue().hasOverride());

        // TEST read overrided value
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        ENTLIB_ASSERT(
            sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // Inherited
        ENTLIB_ASSERT(sysCreat->root.at("Life")->getFloat() == 1000.); // Inherited

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST read default value
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // Inherited (from default)
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST read overrided in array
        ENTLIB_ASSERT(
            sysCreat->root.at("ScriptList")->at(1)->getString() == std::string("b2")); // Overrided
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->at(1)->isSet()); // Overrided
        // TEST read Not overrided in array
        ENTLIB_ASSERT(
            sysCreat->root.at("ScriptList")->at(2)->getString() == std::string("c1")); // not overrided
        ENTLIB_ASSERT(not sysCreat->root.at("ScriptList")->at(2)->isSet()); // Not overrided

        // Programatically unset
        sysCreat->root.at("ScriptList")->at(1)->unset();
        // Programatically set
        sysCreat->root.at("ScriptList")->at(2)->setString("c2");

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST Extand array
        sysCreat->root.at("ScriptList")->push()->setString("d2");
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->size() == 4);

        // TEST SubScene (without override)
        testInstanceOf(*ent);

        sysCreat->root.at("BehaviorState")->setString("Overrided");
        entlib.saveEntity(*ent, "instance.copy.entity");
    }
    auto test_erase = [](Ent::Entity* ent) {
        Ent::Node& actorStates = ent->getActorStates();
        Ent::Component* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node* tags = pathNodeGD->root.at("Tags")->at("Tags");

        // Test erase in map (+save/load)
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->mapGet("c") == nullptr);

        // Test insert in map (+save/load)
        auto e = tags->mapGet("e");
        ENTLIB_ASSERT(e != nullptr);
        ENTLIB_ASSERT(e->at(0llu)->getString() == std::string("e"));

        // Test erase in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.mapGet("ActionCinematic") == nullptr);

        // Test insert in union_set (+save/load)
        ENTLIB_ASSERT(actorStates.mapGet("ActionClamberRise") != nullptr);

        // Test remove component
        ENTLIB_ASSERT(ent->getComponent("TransformGD") == nullptr);
        ENTLIB_ASSERT(ent->getSubSceneComponent() == nullptr);
    };

    {
        EntityPtr ent = entlib.loadEntity("instance.entity");
        // Test erase in union_set
        Ent::Node& actorStates = ent->getActorStates();
        ENTLIB_ASSERT(actorStates.mapGet("ActionCinematic") != nullptr);
        ENTLIB_ASSERT(actorStates.mapErase("ActionCinematic"));
        ENTLIB_ASSERT(actorStates.mapGet("ActionCinematic") == nullptr);

        // Test insert in union_set
        ENTLIB_ASSERT(actorStates.mapInsert("ActionClamberRise") != nullptr);

        // Test erase in map
        Ent::Component* pathNodeGD = ent->getComponent("PathNodeGD");
        Ent::Node* tags = pathNodeGD->root.at("Tags")->at("Tags");
        ENTLIB_ASSERT(tags->mapGet("c") != nullptr);
        ENTLIB_ASSERT(tags->size() == 3);
        ENTLIB_ASSERT(tags->mapErase("c"));
        ENTLIB_ASSERT(tags->size() == 2);
        ENTLIB_ASSERT(tags->mapGet("c") == nullptr);
        ENTLIB_ASSERT(not tags->mapErase(2));

        // Test insert in map
        ENTLIB_ASSERT(tags->mapGet("e") == nullptr);
        ENTLIB_ASSERT(tags->mapInsert("e") != nullptr);

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
    }
    {
        EntityPtr ent = entlib.loadEntity("instance2.entity");
        testInstanceOf(*ent);
    }
    auto testInstanceOverrideSubscene = [](Ent::Entity const& ent) {
        // TEST SubScene (with override)
        Ent::SubSceneComponent const* subScene = ent.getSubSceneComponent();
        ENTLIB_ASSERT(subScene != nullptr);
        ENTLIB_ASSERT(subScene->isEmbedded);
        EntityPtr const& subObj = subScene->embedded->getObjects()[0];
        ENTLIB_ASSERT(subObj->getName() == std::string("EP1-Spout_LINK_001"));

        // Test an overrided Component
        Ent::Component const* netLink = subObj->getComponent("NetworkLink");
        ENTLIB_ASSERT(netLink != nullptr);
        ENTLIB_ASSERT(netLink->root.at("Source")->getString() == std::string(".EP1-Spout_"));
        ENTLIB_ASSERT(netLink->root.at("Source")->isSet() == false);
        ENTLIB_ASSERT(netLink->root.at("Target")->getString() == std::string(".EP1-crook_2"));
        ENTLIB_ASSERT(netLink->root.at("Target")->isSet());

        // Test a not overrided Component
        Ent::Component const* trans = subObj->getComponent("TransformGD");
        ENTLIB_ASSERT(trans != nullptr);
        ENTLIB_ASSERT(trans->root.at("Position")->at(0llu)->getFloat() == 0.0);
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

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST read overrided value
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Plouf")); // Overrided

        // TEST read inherited values
        ENTLIB_ASSERT(
            sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // Inherited
        ENTLIB_ASSERT(sysCreat->root.at("Life")->getFloat() == 1000.); // Inherited

        // TEST read default value
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // Inherited (from default)
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default

        // TEST read programatically overrided in array
        ENTLIB_ASSERT(
            sysCreat->root.at("ScriptList")->at(1)->getString()
            == std::string("b1")); // No more overrided
        ENTLIB_ASSERT(not sysCreat->root.at("ScriptList")->at(1)->isSet()); // No more overrided
        // TEST read programatically unset in array
        ENTLIB_ASSERT(
            sysCreat->root.at("ScriptList")->at(2)->getString() == std::string("c2")); // Overrided
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->at(2)->isSet()); // Overrided

        // TEST read programatically extand array
        ENTLIB_ASSERT(
            sysCreat->root.at("ScriptList")->at(3)->getString() == std::string("d2")); // Overrided
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->at(3)->isSet()); // Overrided

        // TEST read extanded array
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->isSet());
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->size() == 4);

        // TEST override value from code
        ENTLIB_ASSERT(
            sysCreat->root.at("BehaviorState")->getString() == std::string("Overrided")); // set. changed.
        ENTLIB_ASSERT(sysCreat->root.at("BehaviorState")->isSet()); // set. changed.

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
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->hasDefaultValue()); // Prefab has value
        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->hasDefaultValue()); // default
        ENTLIB_ASSERT(sysCreat->root.at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Name")->isSet()); // default

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Plouf")); // set
        ENTLIB_ASSERT(not sysCreat->root.at("Faction")->hasDefaultValue()); // is set in instance
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->isSet()); // is set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->isSet()); // is set

        entlib.saveEntity(*detached, "instance.detached.entity");
    }
    {
        // Test read detached
        EntityPtr ent = entlib.loadEntity("instance.detached.entity");

        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default
        ENTLIB_ASSERT(sysCreat->root.at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Name")->isSet()); // default

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Plouf")); // set
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->isSet()); // is set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey")); // set
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->isSet()); // is set
    }

    {
        // Test makeInstanceOf
        EntityPtr instanceOf = entlib.makeInstanceOf("prefab.entity");

        // Test instanciation of a prefab Node
        Ent::Component* stickToTerrain = instanceOf->addComponent("StickToTerrain");
        ENTLIB_CHECK_EXCEPTION(
            stickToTerrain->root.setInstanceOf("C:/test.StickToTerrain.node"), std::runtime_error);
        stickToTerrain->root.setInstanceOf("test.StickToTerrain.node");
        stickToTerrain->root.setInstanceOf(
            (current_path() / "test.StickToTerrain.node").generic_u8string().c_str());
        ENTLIB_ASSERT(stickToTerrain->root.getInstanceOf() != nullptr);
        stickToTerrain->root.at("NormalRatio")->setFloat(0.6);

        ENTLIB_ASSERT(fabs(stickToTerrain->root.at("NormalRatio")->getFloat() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain->root.at("ZOffset")->isSet() == false);
        ENTLIB_ASSERT(stickToTerrain->root.at("ZOffset")->isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain->root.at("ZOffset")->getFloat() - 10.) < 0.0001);

        ENTLIB_ASSERT(instanceOf->getComponent("NetworkNode") != nullptr);
        instanceOf->getComponent("TransformGD")->root.getFieldNames();
        entlib.saveEntity(*instanceOf, "instance.create.entity");
    }
    auto testCreateInstanceOf = [&entlib](char const* _instancePath) {
        // Test read instance of
        EntityPtr ent = entlib.loadEntity(_instancePath);

        ent->getComponent("TransformGD")->root.getFieldNames();

        // Test instanciation of a prefab Node
        Ent::Component const* stickToTerrain = ent->getComponent("StickToTerrain");
        ENTLIB_ASSERT(stickToTerrain->root.getInstanceOf() != nullptr);
        ENTLIB_ASSERT(fabs(stickToTerrain->root.at("NormalRatio")->getFloat() - 0.6) < 0.0001);
        ENTLIB_ASSERT(stickToTerrain->root.at("ZOffset")->isSet() == false);
        ENTLIB_ASSERT(stickToTerrain->root.at("ZOffset")->isDefault() == false);
        ENTLIB_ASSERT(fabs(stickToTerrain->root.at("ZOffset")->getFloat() - 10.) < 0.0001);

        // TEST read inherited values in inherited component
        Ent::Component* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(
            heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->getInt() == 51248);
        ENTLIB_ASSERT(
            not heightObj->root.at("DisplaceNoiseList")->at(0llu)->at("MapChannel")->isSet());

        // Test read prefab
        Ent::Component* sysCreat = ent->getComponent("SystemicCreature");
        ENTLIB_ASSERT(sysCreat != nullptr);

        // TEST read setted values
        ENTLIB_ASSERT(sysCreat->root.at("Faction")->getString() == std::string("Shamans"));
        ENTLIB_ASSERT(not sysCreat->root.at("Faction")->isSet()); // Not overrided
        ENTLIB_ASSERT(sysCreat->root.at("Inventory")->getString() == std::string("KaiWOLgrey"));
        ENTLIB_ASSERT(not sysCreat->root.at("Inventory")->isSet()); // Not overrided

        // TEST read array
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->isSet()); // Arrays are always set
        ENTLIB_ASSERT(sysCreat->root.at("ScriptList")->size() == 3);

        // TEST default values
        ENTLIB_ASSERT(sysCreat->root.at("Burried")->getBool() == false); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Burried")->isSet()); // default
        ENTLIB_ASSERT(sysCreat->root.at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Name")->isSet()); // default
    };
    testCreateInstanceOf("instance.create.entity");
    {
        // Test setInstanceOf
        Ent::Entity instanceOf(entlib);
        instanceOf.setInstanceOf("prefab.entity");
        ENTLIB_ASSERT(instanceOf.getComponent("NetworkNode") != nullptr);
        instanceOf.getComponent("TransformGD")->root.getFieldNames();

        // Test instanciation of a prefab Node
        Ent::Component* stickToTerrain = instanceOf.addComponent("StickToTerrain");
        stickToTerrain->root.setInstanceOf("test.StickToTerrain.node");
        stickToTerrain->root.at("NormalRatio")->setFloat(0.6);

        entlib.saveEntity(instanceOf, "setInstanceOf.entity");
    }
    testCreateInstanceOf("setInstanceOf.entity");

    // ******************************** Test iteration of schema **********************************
    if (doDisplaySubSchema)
    {
        for (auto&& name_sub : entlib.schema.components)
        {
            displaySubSchema(std::get<0>(name_sub), *std::get<1>(name_sub), {});
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
    auto testOverrideSubEntity = [](Ent::Entity const& ent) {
        Ent::SubSceneComponent const* subScenecomp = ent.getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == 1);
        ENTLIB_ASSERT(allSubEntities.front()->getName() == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(allSubEntities.front()->getColor()[0] == 42);
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
    auto testAddSubEntity = [](Ent::Entity const& ent) {
        Ent::SubSceneComponent const* subScenecomp = ent.getSubSceneComponent();
        auto&& allSubEntities = subScenecomp->embedded->getObjects();
        ENTLIB_ASSERT(allSubEntities.size() == 2);
        char const* name0 = allSubEntities[0]->getName();
        char const* name1 = allSubEntities[1]->getName();
        ENTLIB_ASSERT(name0 == std::string("EP1-Spout_LINK_001"));
        auto red = allSubEntities[0]->getColor()[0];
        ENTLIB_ASSERT(not allSubEntities[0]->hasOverride());
        ENTLIB_ASSERT(red == 255);
        ENTLIB_ASSERT(not allSubEntities[0]->canBeRenamed());
        ENTLIB_ASSERT(name1 == std::string("EP1-Spout_LINK_001_added"));
        ENTLIB_ASSERT(allSubEntities[1]->getColor()[0] == 44);
        ENTLIB_ASSERT(allSubEntities[1]->canBeRenamed());
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

        ENTLIB_ASSERT(not ent->hasOverride());
        ENTLIB_ASSERT(not empty(subs->embedded->getObjects()));

        auto&& allSubEntities = subs->embedded->getObjects();
        allSubEntities[0]->addComponent("ActorGD")->root.at("InSpiritWorld")->setBool(true);
        entlib.saveEntity(*ent, "entity-subscene-override-saved.entity");

        EntityPtr ovrdEntt = entlib.loadEntity("entity-subscene-override-saved.entity");
        auto ovrdSubs = ovrdEntt->getSubSceneComponent();

        //Test that we properly still have access to the prefab subscene entities
        ENTLIB_ASSERT(not empty(ovrdSubs->embedded->getObjects()));
    }

    {
        auto ent = entlib.loadEntity(R"(Creature/my_creature_level2.entity)");
        auto& subscene = ent->getSubSceneComponent()
                             ->embedded->getEntity(0)
                             ->getSubSceneComponent()
                             ->embedded->getObjects();
        ENTLIB_ASSERT(subscene.size() == 1);
        ENTLIB_ASSERT(strcmp(subscene.front()->getName(), "default_level2") == 0);
    }

    // ******************* Test twice the same key in map *************************************
    {
        ENTLIB_CHECK_EXCEPTION(entlib.loadEntity("key_double.entity"), Ent::InvalidJsonData);
    }

    // ******************* Test default color *****************************************************
    {
        EntityPtr ent = std::make_unique<Ent::Entity>(entlib);
        ENTLIB_ASSERT(ent->getColor() == (std::array<double, 4>{1., 1., 1., 1.}));
    }
    // ********************************** Test load/save scene ************************************
    entlib.rawdataPath = "X:/RawData";

    auto scene = entlib.loadScene("X:/RawData/22_World/SceneMainWorld/"
                                  "SceneMainWorld_entitylib_unit_test.scene");

    if (doDisplayScene)
    {
        using namespace Ent;
        printfmt("Scene Loaded\n");
        printfmt("Entity count : %zu\n", scene->getObjects().size());

        for (EntityPtr const& ent : scene->getObjects())
        {
            printfmt("  Name \"%s\"\n", ent->getName());

            for (char const* type : ent->getComponentTypes())
            {
                printfmt("    Type \"%s\"\n", type);
                Ent::Node const& root = ent->getComponent(type)->root;
                printNode("", root, "      ");
            }
        }
    }

    Ent::Component* heightObj = scene->getObjects().front()->addComponent("HeightObj");
    heightObj->root.at("DisplaceNoiseList")->push();

    scene->getObjects().front()->addComponent("BeamGeneratorGD")->root.getFieldNames();
    auto fieldNameCount =
        scene->getObjects().front()->addComponent("HeightObj")->root.getFieldNames().size();
    ENTLIB_ASSERT(fieldNameCount == 8);

    auto ep1Iter = std::find_if(
        begin(scene->getObjects()),
        end(scene->getObjects()),
        [ep1 = std::string("EP1_")](auto&& ent) { return ent->getName() == ep1; });
    ENTLIB_ASSERT(ep1Iter != end(scene->getObjects()));
    ENTLIB_ASSERT((*ep1Iter)->getSubSceneComponent() != nullptr);

    entlib.rawdataPath = current_path();
    scene->addEntity(entlib.makeInstanceOf((current_path() / "prefab.entity").generic_u8string()));

    entlib.saveScene(*scene, current_path() / "SceneMainWorld.test.scene");

    auto const& addedEntity = scene->getObjects().back();
    Ent::Component const* cinematicCmp = addedEntity->getComponent("CinematicGD");
    ENTLIB_ASSERT(cinematicCmp != nullptr);

    // Test dumpNode
    if (dumpNodes)
    {
        Ent::printfmt("dumpNode(Override):\n");
        Ent::printfmt(
            "%s\n",
            cinematicCmp->root.toJson(Ent::OverrideValueSource::Override, true).dump(4).c_str());

        Ent::printfmt("dumpNode(OverrideOrPrefab):\n");
        Ent::printfmt(
            "%s\n",
            cinematicCmp->root.toJson(Ent::OverrideValueSource::OverrideOrPrefab, true).dump(4).c_str());

        Ent::printfmt("dumpNode(Any):\n");
        Ent::printfmt(
            "%s\n", cinematicCmp->root.toJson(Ent::OverrideValueSource::Any, true).dump(4).c_str());
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
