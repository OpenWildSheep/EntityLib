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
    case Ent::DataType::entityRef:
        printf("%s%s [EntityRef] : %s\n", tab.c_str(), name, node.getEntityRef().entityPath.c_str());
        break;
    case Ent::DataType::oneOf:
        printf("%s%s [Union]\n", tab.c_str(), name);
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
    std::cout << indent << name << " : ";
    switch (subschema.type)
    {
    case Ent::DataType::array:
        std::cout << "array" << std::endl;
        if (subschema.minItems != 0)
        {
            std::cout << indent << "  minItems:" << subschema.minItems << std::endl;
        }
        if (subschema.maxItems != size_t(-1))
        {
            std::cout << indent << "  maxItems:" << subschema.maxItems << std::endl;
        }
        if (subschema.singularItems != nullptr)
        {
            displaySubSchema("items", subschema.singularItems->get(), indent + "  ");
        }
        break;
    case Ent::DataType::boolean: std::cout << "boolean" << std::endl; break;
    case Ent::DataType::integer: std::cout << "integer" << std::endl; break;
    case Ent::DataType::null: std::cout << "null" << std::endl; break;
    case Ent::DataType::number: std::cout << "number" << std::endl; break;
    case Ent::DataType::object:
        std::cout << "object" << std::endl;
        for (auto&& name_sub : subschema.properties)
        {
            displaySubSchema(std::get<0>(name_sub), *std::get<1>(name_sub), indent + "  ");
        }
        break;
    case Ent::DataType::string: std::cout << "string" << std::endl; break;
    case Ent::DataType::entityRef: std::cout << "entity ref" << std::endl; break;
    case Ent::DataType::oneOf: std::cout << "oneOf" << std::endl; break;
    case Ent::DataType::COUNT: ENTLIB_LOGIC_ERROR("Invalid DataType when parsing meta"); break;
    }
}

#define ENTLIB_CHECK_EXCEPTION(expression, excep_type)                                             \
    {                                                                                              \
        bool exception_throw = false;                                                              \
        try                                                                                        \
        {                                                                                          \
            expression;                                                                            \
        }                                                                                          \
        catch (excep_type&)                                                                        \
        {                                                                                          \
            exception_throw = true;                                                                \
        }                                                                                          \
        catch (...)                                                                                \
        {                                                                                          \
            ENTLIB_LOGIC_ERROR("Wrong exception thrown!");                                         \
        }                                                                                          \
        ENTLIB_ASSERT_MSG(exception_throw, "Exception not thrown!");                               \
    }

int main() // int argc, char** argv
try
{
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

    using EntityPtr = std::unique_ptr<Ent::Entity>;

    // Test $ref links in entlib.schema.schema.allDefinitions
    char const* colorRef = "file://RuntimeComponents.json#/definitions/Color";
    ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(colorRef) == 1);

    // Check Ent::Subschema::getUnionTypesMap
    char const* cinematicGDRef = "file://RuntimeComponents.json#/definitions/CinematicGD";
    Ent::Subschema const& cinematicGDSchema = entlib.schema.schema.allDefinitions.at(cinematicGDRef);
    Ent::Subschema const& scriptEventUnionSchema =
        cinematicGDSchema.properties.at("ScriptEvents")->singularItems->get();
    auto&& nameToTypeMap = scriptEventUnionSchema.getUnionTypesMap();
    ENTLIB_ASSERT(size(nameToTypeMap) == 14);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTest") == 1);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTestBlackboardHasFact") == 1);
    ENTLIB_ASSERT(nameToTypeMap.count("CineEventTestEndCurrentSequence") == 1);

    // Ensure that all components have a ref and is in entlib.schema.schema.allDefinitions
    for (auto&& name_schema : entlib.schema.components)
    {
        auto&& absRef = std::get<1>(name_schema)->name;
        ENTLIB_ASSERT(absRef.find("file://") == 0);
        ENTLIB_ASSERT(entlib.schema.schema.allDefinitions.count(absRef) == 1);
    }

    auto testPrefabEntity = [](Ent::Entity const* ent) {
        // Test default value
        Ent::Component const* voxelSimulationGD = ent->getComponent("VoxelSimulationGD");
        ENTLIB_ASSERT(voxelSimulationGD->root.at("TransmissionBySecond")->getFloat() == 100.f);
        ENTLIB_ASSERT(voxelSimulationGD->root.at("TransmissionBySecond")->isDefault());
        ENTLIB_ASSERT(
            voxelSimulationGD->root.getTypeName()
            == std::string("file://RuntimeComponents.json#/definitions/VoxelSimulationGD"));

        // TEST read inherited values in inherited component
        Ent::Component const* heightObj = ent->getComponent("HeightObj");
        ENTLIB_ASSERT(heightObj != nullptr);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getInt() == 0);
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->isSet());
        ENTLIB_ASSERT(not heightObj->root.at("Subdivision")->isDefault());
        ENTLIB_ASSERT(heightObj->root.at("Subdivision")->getDefaultInt() == 6);
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
        ENTLIB_ASSERT(sysCreat->root.at("Name")->getString() == std::string()); // default
        ENTLIB_ASSERT(not sysCreat->root.at("Name")->isSet()); // default

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
        ENTLIB_ASSERT(
            cineEvent->getTypeName()
            == std::string(
                R"(file://RuntimeComponents.json#/definitions/CineEventTestBlackboardHasFact)"));
        auto fieldNames = cineEvent->getFieldNames();
        ENTLIB_ASSERT(fieldNames[0] == std::string("FactName"));
        ENTLIB_ASSERT(fieldNames[1] == std::string("Super"));

        Ent::Node const* nbEnt = cineEvent->at("FactName");
        ENTLIB_ASSERT(nbEnt != nullptr);
        ENTLIB_ASSERT(nbEnt->getDataType() == Ent::DataType::string);
        ENTLIB_ASSERT(nbEnt->getString() == std::string("Toto"));

        // TEST sub-object with non-default values
        Ent::Component const* explosionEffect = ent->getComponent("ExplosionEffect");
        Ent::Node const* shakeData = explosionEffect->root.at("ShakeData");
        ENTLIB_ASSERT(shakeData->at("shakeDuration")->getFloat() == 0.0f);
    };

    {
        EntityPtr ent = entlib.loadEntity("prefab.entity");

        testPrefabEntity(ent.get());

        // Set Union type and override
        Ent::Component* cinematicGD = ent->getComponent("CinematicGD");
        Ent::Node* scriptEvents = cinematicGD->root.at("ScriptEvents");
        Ent::Node* oneOfScripts2 = scriptEvents->at(1llu);
        ENTLIB_ASSERT(oneOfScripts2->getDataType() == Ent::DataType::oneOf);
        ENTLIB_ASSERT(oneOfScripts2->getUnionType() == std::string("CineEventTestBlackboardHasFact"));
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
        ENTLIB_ASSERT(oneOfScripts3->getUnionType() == std::string("CineEventTestBlackboardHasFact"));
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
        sysCreat->root.at("Name")->setString("Shamane_male");
        entlib.saveEntity(*ent, "prefab.copy.entity");
    }
    {
        // Test the readOnly prefab.entity
        Ent::Entity const* ent = entlib.loadEntityReadOnly("prefab.entity");
        testPrefabEntity(ent);
    }
    {
        // Test write prefab
        EntityPtr ent = entlib.loadEntity("prefab.copy.entity");

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
        Ent::Entity* resolvedInstanceOfA = B.resolveEntityRef({ ".." });
        ENTLIB_ASSERT(resolvedInstanceOfA == &instanceOfA);
        Ent::Entity* resolvedB = instanceOfA.resolveEntityRef({ "B" });
        ENTLIB_ASSERT(resolvedB == &B);
        Ent::Entity* resolvedBbis = C.resolveEntityRef({ "../InstanceOfA/B" });
        ENTLIB_ASSERT(resolvedBbis == &B);
        Ent::Entity* resolvedC = B.resolveEntityRef({ "../../C" });
        ENTLIB_ASSERT(resolvedC == &C);

        // TEST entity ref resolution from scenes
        ENTLIB_ASSERT(scene->resolveEntityRef({ ".." }) == nullptr);
        ENTLIB_ASSERT(scene->resolveEntityRef({ "InstanceOfA" }) == &instanceOfA);
        ENTLIB_ASSERT(scene->resolveEntityRef({ "InstanceOfA/B" }) == &B);
        ENTLIB_ASSERT(scene->resolveEntityRef({ "C" }) == &C);
        ENTLIB_ASSERT(scene->resolveEntityRef({ "InstanceOfA/B/../../C" }) == &C);
    }

    auto testInstanceOf = [](Ent::Entity const& ent) {
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
        ENTLIB_ASSERT(sysCreat->root.at("Life")->getFloat() == 1000.f); // Inherited

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
        ENTLIB_ASSERT(sysCreat->root.at("Life")->getFloat() == 1000.f); // Inherited

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
        // Test create instance of
        EntityPtr instanceOf = entlib.makeInstanceOf("prefab.entity");
        ENTLIB_ASSERT(instanceOf->getComponent("NetworkNode") != nullptr);
        instanceOf->getComponent("TransformGD")->root.getFieldNames();
        entlib.saveEntity(*instanceOf, "instance.create.entity");
    }
    {
        // Test read instance of
        EntityPtr ent = entlib.loadEntity("instance.create.entity");

        ent->getComponent("TransformGD")->root.getFieldNames();

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
    }

    // ******************************** Test iteration of schema **********************************
    for (auto&& name_sub : entlib.schema.components)
    {
        displaySubSchema(std::get<0>(name_sub), *std::get<1>(name_sub), {});
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

    // ********************************** Test load/save scene ************************************
    entlib.rawdataPath = "X:/RawData";

    std::unique_ptr<Ent::Scene> scene = entlib.loadScene("X:/RawData/22_World/SceneMainWorld/"
                                                         "SceneMainWorld.scene");

    printf("Scene Loaded\n");
    printf("Entity count : %zu\n", scene->getObjects().size());

    for (EntityPtr const& ent : scene->getObjects())
    {
        printf("  Name \"%s\"\n", ent->getName());

        for (char const* type : ent->getComponentTypes())
        {
            printf("    Type \"%s\"\n", type);
            Ent::Node const& root = ent->getComponent(type)->root;
            printNode("", root, "      ");
        }
    }

    Ent::Component* heightObj = scene->getObjects().front()->addComponent("HeightObj");
    heightObj->root.at("DisplaceNoiseList")->push();

    scene->getObjects().front()->addComponent("BeamGeneratorGD")->root.getFieldNames();
    ENTLIB_ASSERT(
        scene->getObjects().front()->addComponent("ExplosionEffect")->root.getFieldNames().size()
        == 23);

    auto ep1Iter = std::find_if(
        begin(scene->getObjects()),
        end(scene->getObjects()),
        [ep1 = std::string("EP1_")](auto&& ent) { return ent->getName() == ep1; });
    ENTLIB_ASSERT(ep1Iter != end(scene->getObjects()));
    ENTLIB_ASSERT((*ep1Iter)->getSubSceneComponent() != nullptr);

    scene->addEntity(entlib.makeInstanceOf((current_path() / "prefab.entity").generic_u8string()));

    entlib.saveScene(*scene, "X:/RawData/22_World/SceneMainWorld/SceneMainWorld.test.scene");

    std::cout << "Done" << std::endl;
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
