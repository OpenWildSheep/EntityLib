#include <EntGen.h>
#include <ciso646>
#include <filesystem>
#include <iostream>

using namespace Ent::Gen2;

int main()
try
{
    Ent::EntityLib entlib("X:/RawData", "X:/Tools/WildPipeline/Schema");
    entlib.rawdataPath = canonical(std::filesystem::current_path() / "../Test");

    Ent::Property expl(&entlib, entlib.getSchema(Entity::schemaName), "instance.entity");
    auto ent = Entity(expl);

    // Test Object
    [[maybe_unused]] auto name = ent.Name(); // inferred type : String
    static_assert(std::is_same_v<decltype(name), String>);
    auto components = ent.Components(); // inferred type : Components
    // Object Load
    auto ent2 = Entity::load(entlib, "instance.entity");
    // Object save
    ent2.save("instance_test_save.entity");

    // Test Set of Union
    [[maybe_unused]] auto ss = components.get<SubScene>(); // inferred type : SubScene
    for (std::string const& key : components.getKeys())
    {
        auto comp = components.get(key.c_str());
        std::cout << comp->getTypeName() << std::endl;
    }
    for (Ent::Property const& comp : components)
    {
        std::cout << comp.getTypeName() << std::endl;
    }
    auto tgd = ent.Components().get<TransformGD>(); // inferred type : std::optional<TransformGD>
    auto heightObj = components.get<HeightObj>();
    static_assert(std::is_same_v<std::remove_reference_t<decltype(*heightObj)>, HeightObj>);
    [[maybe_unused]] auto actorStateCreature = ent.ActorStates().add<ActorStateBeingImmersed>();
    auto unitTestCpt = components.add<UnitTestComponent>(); // inferred type : TurretComponentGD
    static_assert(std::is_same_v<decltype(unitTestCpt), UnitTestComponent>);
    heightObj = *components.HeightObj(); // Keep this method??
    components.removeAnimationModelGD();
    // Test fixed size array
    auto pos = ent.Components().get<TransformGD>()->Position(); // inferred type : Vector3
    [[maybe_unused]] auto x = tgd->Position()[0]; // inferred type : Float
    // Copy point into Node
    double arr[] = {1., 2., 3.};
    tgd->Position() = std::vector{1., 2., 3.};
    tgd->Position() = std::array<double, 3>{1., 2., 3.};
    tgd->Position() = std::tuple{1., 2., 3.};
    tgd->Position() = std::initializer_list<double>{1., 2., 3.};
    tgd->Position() = arr;
    tgd->Position()[1] = 2.;
    // Copy Node into point
    std::vector<double> v = tgd->Position();
    [[maybe_unused]] std::array<double, 3> a = tgd->Position();
    [[maybe_unused]] std::tuple<double, double, double> t = tgd->Position();
    tgd->Position().clear();
    ENTLIB_ASSERT(tgd->Position().size() == 0);

    // Test set of primitive
    [[maybe_unused]] auto side =
        unitTestCpt.EnumSet(); // inferred type : PrimitiveSet<ReviveSideTargetedItem_ReviveSide>
    static_assert(std::is_same_v<decltype(side), PrimitiveSet<ReviveSideEnum>>);
    unitTestCpt.EnumSet().add(ReviveSideEnum::neutral);
    unitTestCpt.EnumSet().add(ReviveSideEnum::cursed);
    unitTestCpt.EnumSet().remove(ReviveSideEnum::neutral);
    ENTLIB_ASSERT(unitTestCpt.EnumSet().count(ReviveSideEnum::cursed));
    unitTestCpt.EnumSet().add(ReviveSideEnum::sacred); // inferred type : String
    for (auto&& enm : unitTestCpt.EnumSet())
    {
        std::cout << toString(enm) << std::endl;
        ENTLIB_ASSERT(unitTestCpt.EnumSet().count(enm));
    }
    // Test Enum prop
    auto mode = ent.Components().add<BeamTargetGD>().Mode(); // inferred type : BeamStaffMode
    mode = BeamStaffModeEnum::Hatching;
    BeamStaffModeEnum enm = mode;
    ENTLIB_ASSERT(enm == BeamStaffModeEnum::Hatching);

    // Test primitive types
    ENTLIB_ASSERT(ent.Name().get() == std::string("PlayerSpawner_"));
    ent.Name() = std::string("PlayerSpawner_2");
    ent.Name().set(std::string("PlayerSpawner_2"));
    ENTLIB_ASSERT(ent.Name().get() == std::string("PlayerSpawner_2"));
    ent.Name() = "PlayerSpawner_3";
    ENTLIB_ASSERT(ent.Name().isSet());
    ent.Name().unset();
    ENTLIB_ASSERT(not ent.Name().isSet());
    ENTLIB_ASSERT(heightObj->Subdivision().get() == 0);
    [[maybe_unused]] auto displaceNoise0 =
        heightObj->DisplaceNoiseList()[0]; // inferred type : DisplaceNoiseListItem
    ENTLIB_ASSERT(ent.Components().get<TestTagsList>()->Radius().get() == 30.0);
    ENTLIB_ASSERT(ent.Components().get<TestTagsList>()->Radius().toFloat() == 30.0f);
    [[maybe_unused]] float rad2 = ent.Components().get<TestTagsList>()->Radius().toFloat();
    ent.Components().get<TestTagsList>()->Radius() = 20.0;
    double rad = ent.Components().get<TestTagsList>()->Radius();
    ENTLIB_ASSERT(rad == 20.0);

    // Test Tuple
    auto position = unitTestCpt.Position(); // inferred type : Position
    [[maybe_unused]] auto elt2_ = position.get<2>(); // inferred type : Float
    static_assert(std::is_same_v<decltype(elt2_), Float>);
    [[maybe_unused]] auto val0 = position.get<0>().get(); // inferred type : int
    static_assert(std::is_same_v<decltype(val0), int64_t>);
    ENTLIB_ASSERT(position.size() == 5);

    // Test Set of Object
    auto subscene = ent.Components().get<SubScene>()->Embedded(); // inferred type : ObjectSet<Entity>
    [[maybe_unused]] auto subent = subscene["EntityWithInstanceOf"]; // inferred type : Entity
    static_assert(std::is_same_v<decltype(subent), std::optional<Entity>>);
    [[maybe_unused]] auto new_ent = subscene.add("NewEntity"); // inferred type : Entity
    static_assert(std::is_same_v<decltype(new_ent), Entity>);
    for (auto&& entname : subscene.getKeys())
    {
        [[maybe_unused]] auto ent3 = subscene.get(entname);
        static_assert(std::is_same_v<decltype(ent3), std::optional<Entity>>);
    }
    for ([[maybe_unused]] auto ent3 : subscene)
    {
        static_assert(std::is_same_v<decltype(ent3), Entity>);
    }

    // Test Map
    auto pathNodeGD = ent.Components().get<TestTagsList>(); // inferred type : TestTagsList
    auto tags = pathNodeGD->Tags().Tags(); // inferred type : Map<char const*, PrimitiveSet<String>>
    static_assert(std::is_same_v<decltype(tags), Map<char const*, PrimitiveSet<char const*>>>);
    [[maybe_unused]] auto b = tags.get("b"); // inferred type : PrimitiveSet<String>
    tags.remove("c");
    [[maybe_unused]] auto c = tags.add("c"); // inferred type : PrimitiveSet<String>
    for (auto&& mapName : tags.getKeys())
    {
        [[maybe_unused]] auto set = tags.get(mapName);
        static_assert(std::is_same_v<decltype(set), std::optional<PrimitiveSet<char const*>>>);
    }
    for (auto&& [setname, set] : tags)
    {
        static_assert(std::is_same_v<decltype(set), PrimitiveSet<char const*>>);
    }

    // Test Map with enum key
    /*
    Map<EnergySideEnum, Array<sEnvStamp>> stamps = ent.Components().add<EnvStampGD>().Stamps();
    stamps.add(EnergySideEnum::corrupted);
    stamps.add(EnergySideEnum::corrupted);
    std::optional<Array<sEnvStamp>> deadArr = stamps.get(EnergySideEnum::corrupted);
    ENTLIB_ASSERT(deadArr.has_value());
    std::optional<Array<sEnvStamp>> lushArr = stamps.get(EnergySideEnum::lush);
    ENTLIB_ASSERT(not lushArr.has_value());
    for (auto&& stampname : stamps.getKeys())
    {
        [[maybe_unused]] auto stamp = stamps.get(stampname);
        std::cout << toString(stampname) << std::endl;
        static_assert(std::is_same_v<decltype(stamp), std::optional<Array<sEnvStamp>>>);
    }
    for (auto&& [stampname, stamp] : stamps)
    {
        std::cout << toString(stampname) << std::endl;
        static_assert(std::is_same_v<decltype(stamp), Array<sEnvStamp>>);
    }
    stamps.remove(EnergySideEnum::corrupted);
    ENTLIB_ASSERT(not stamps.get(EnergySideEnum::corrupted).has_value());
    */
    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    fprintf(stderr, ex.what());
    return EXIT_FAILURE;
}
catch (...)
{
    fprintf(stderr, "Exception thrown");
    return EXIT_FAILURE;
}
