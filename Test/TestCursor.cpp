#include "TestCursor.h"
#include <EntityLib.h>
#include <../Tools.h>
#include <fstream>
#include <variant>
#include <iostream>

#include <EntityLib/Visitor.h>
#include <EntityLib/CopyProperty.h>
#include <EntityLib/Property.h>

#include "EntityLib/SearchProperty.h"

using namespace Ent;

void testCursor(EntityLib& entlib)
{
    {
        auto storage = nlohmann::json::object();
        Property entity(&entlib, entlib.getEntitySchema(), nullptr, &storage, nullptr);
        auto name = entity.getObjectField("Name");
        name.setString("Debug Quick Creatures Switch");
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, static_cast<char>(0));
        auto d = loadJsonFile(std::filesystem::current_path(), "test.SeedPatch.node");
        auto const& schema = d["$schema"].get_ref<nlohmann::json::string_t const&>();
        auto typeName = std::string(getRefTypeName(schema.c_str()));
        Property simpleObject(
            &entlib, entlib.getSchema(typeName.c_str()), "test.SeedPatch.node", &d, nullptr);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 1.f);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, static_cast<char>(0));
        auto d = loadJsonFile(std::filesystem::current_path(), "test.SeedPatch.node");
        auto typeName =
            std::string(getRefTypeName(d["$schema"].get_ref<std::string const&>().c_str()));
        Property simpleObject(
            &entlib, entlib.getSchema(typeName.c_str()), "test.SeedPatch.node", &d, nullptr);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 1.f);
        simpleObject.getObjectField("NoiseSizeX").setFloat(2.);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 2.);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        Property expl = entlib.loadPropertyCopy("Entity", "prefab.entity");
        ENTLIB_ASSERT(expl.getObjectField("Name").getString() == std::string("PlayerSpawner_"));
        {
            ENTLIB_ASSERT(
                expl.getObjectField("Components")
                    .getUnionSetItem("NetworkNode")
                    ->getObjectField("Type")
                    .getString()
                == std::string("Spawner"));
        }
        auto posX = expl.getObjectField("Components")
                        .getUnionSetItem("TransformGD")
                        ->getObjectField("Position")
                        .getArrayItem(0llu);
        std::cout << posX.getFloat() << std::endl;
        ENTLIB_ASSERT(posX.getFloat() == 105.2244);
        auto& entityRung = expl;
        auto floatA = entityRung.getObjectField("Components")
                          .getUnionSetItem("TransformGD")
                          ->getObjectField("Position")
                          .getArrayItem(0llu)
                          .getFloat();
        auto floatB = entityRung.getObjectField("Components")
                          .getUnionSetItem("TransformGD")
                          ->getObjectField("Position")
                          .getArrayItem(0llu)
                          .getFloat();
        ENTLIB_ASSERT(floatA == 105.2244);
        ENTLIB_ASSERT(floatB == 105.2244);

        ENTLIB_ASSERT(
            expl.getObjectField("Components")
                .getUnionSetItem("SubScene")
                ->getObjectField("Embedded")
                .getObjectSetItem("EP1-Spout_LINK_001")
                ->getObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
    }
    {
        Property expl = entlib.loadPropertyCopy("Entity", "instance.entity");
        ENTLIB_ASSERT(expl.getObjectField("Name").getString() == std::string("PlayerSpawner_"));
        auto type =
            expl.getObjectField("Components").getUnionSetItem("NetworkNode")->getObjectField("Type");
        std::cout << type.getString() << std::endl;
        ENTLIB_ASSERT(
            expl.getObjectField("Components").getUnionSetItem("NetworkNode")->getObjectField("Type").getString()
            == std::string("Spawner"));
        std::cout << expl.getObjectField("Components")
                         .getUnionSetItem("TransformGD")
                         ->getObjectField("Matrix")
                         .getArrayItem(3llu)
                         .getFloat()
                  << std::endl;
        auto pos2 = expl.getObjectField("Components")
                        .getUnionSetItem("TransformGD")
                        ->getObjectField("Position")
                        .getArrayItem(2llu)
                        .getFloat();
        ENTLIB_ASSERT(fabs(pos2 - 29.6635) < FLT_EPSILON);
        ENTLIB_ASSERT(
            expl.getObjectField("Components")
                .getUnionSetItem("SubScene")
                ->getObjectField("Embedded")
                .getObjectSetItem("EP1-Spout_LINK_001")
                ->getObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(
            expl.getObjectField("ActorStates")
                .getUnionSetItem("ActorStateHoldingItem")
                ->getObjectField("ItemEntityRef")
                .getEntityRef()
                .entityPath
            == std::string("tutu"));
        auto components = expl.getObjectField("Components");
        auto ori3 =
            components.getUnionSetItem("TransformGD")->getObjectField("Orientation").getArrayItem(3llu);
        ENTLIB_ASSERT(fabs(ori3.getFloat() - 0.9916236400604248) < FLT_EPSILON);
        ori3.setFloat(2.);
        ENTLIB_ASSERT(ori3.getFloat() == 2.);
        auto soundAreaGD =
            expl.getObjectField("Components").forceGetUnionSetItem("SoundAreaGD").first;
        ENTLIB_ASSERT(soundAreaGD.isSet() == false);
        ENTLIB_ASSERT(soundAreaGD.isDefault() == true);
        auto keys = components.getUnionSetKeysString();
        keys = components.getUnionSetKeysString();

        expl.save("instance.prout.entity");
        // Must not crash
        Property prefab2(&entlib, entlib.getSchema(entitySchemaName), "instance.prout.entity");
        auto comp2 = prefab2.getObjectField("Components");
        auto characterControllerGD = *comp2.getUnionSetItem("CharacterControllerGD");
        auto clamberData = characterControllerGD.getObjectField("ClamberData");
        auto vertOriRatio = clamberData.getObjectField("VerticalOrientationRatio");
        auto in = vertOriRatio.getObjectField("in");
        auto in0 = in.getArrayItem(0);
        in0.setFloat(3.33);
    }
    {
        std::cout << "Read instance.entity with LazyLib" << std::endl;
        Property expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");

        nlohmann::json newDoc = nlohmann::json::object();
        Property destExpl(&entlib, expl.getSchema(), "", &newDoc, nullptr);
        CopyProperty copier(
            destExpl, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        visitRecursive(expl, copier);
        entlib.saveJsonFile(&newDoc, "instance.cursor.entity", "Entity");

        // test SearchProperty
        auto pattern = "eMbeDdEd";
        SearchProperty searcher(pattern);
        visitRecursive(expl, searcher);
        auto matching = searcher.getMatchingProperties();
        ENTLIB_ASSERT(matching.size() == 1);
    }
}
