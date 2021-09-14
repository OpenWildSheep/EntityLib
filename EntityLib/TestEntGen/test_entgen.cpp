#include <EntGen.h>
#include <ciso646>
#include <filesystem>

using namespace Ent::Gen;

int main()
try
{
    Ent::EntityLib entlib("X:/", true);
    entlib.rawdataPath =
        std::filesystem::canonical(std::filesystem::current_path() / "../Test");

    Ent::Node entNode = entlib.loadEntityAsNode("instance.entity");
    auto ent = Entity(&entNode);

    // Test Object
    auto name = ent.Name(); // inferred type : String
    static_assert(std::is_same_v<decltype(name), String>);
    auto components = ent.Components(); // inferred type : Components
    // Object Load
    Ent::Node ent2node = Entity::load(entlib, "instance.entity");
    auto ent2 = Entity(&ent2node);
    // Object save
    ent2.save("instance_test_save.entity");

    // Test Set of Union
    auto ss = components.get<SubScene>(); // inferred type : SubScene
    auto tgd = ent.Components().get<TransformGD>(); // inferred type : TransformGD
    auto heightObj = components.get<HeightObj>();
    static_assert(std::is_same_v<decltype(heightObj), HeightObj>);
    auto actorStateCreature = ent.ActorStates().add<ActorStateBeingImmersed>();
    auto unitTestCpt =
        components.add<UnitTestComponent>(); // inferred type : TurretComponentGD
    static_assert(std::is_same_v<decltype(unitTestCpt), UnitTestComponent>);
    heightObj = components.HeightObj(); // Keep this method??

    // Test fixed size array
    auto pos =
        ent.Components().get<TransformGD>().Position(); // inferred type : Vector3
    auto x = tgd.Position()[0]; // inferred type : Float
    // Copy point into Node
    double arr[] = {1., 2., 3.};
    tgd.Position() = std::vector<double>{1., 2., 3.};
    tgd.Position() = std::array<double, 3>{1., 2., 3.};
    tgd.Position() = std::tuple{1., 2., 3.};
    tgd.Position() = std::initializer_list<double>{1., 2., 3.};
    tgd.Position() = arr;
    tgd.Position()[1] = 2.;
    // Copy Node into point
    std::vector<double> v = tgd.Position();
    std::array<double, 3> a = tgd.Position();
    std::tuple<double, double, double> t = tgd.Position();

    // Test set of primitive
    auto side =
        unitTestCpt.EnumSet(); // inferred type : PrimitiveSet<ReviveSideTargetedItem_ReviveSide>
    static_assert(std::is_same_v<decltype(side), PrimitiveSet<ReviveSideEnum>>);
    unitTestCpt.EnumSet().add(ReviveSideEnum::neutral);
    unitTestCpt.EnumSet().add(ReviveSideEnum::cursed);
    // turret.ReviveSideTargeted.remove(ReviveSideEnum::neutral);
    ENTLIB_ASSERT(unitTestCpt.EnumSet().count(ReviveSideEnum::cursed));
    unitTestCpt.EnumSet().add(ReviveSideEnum::sacred); // inferred type : String

    // Test Enum prop
    auto mode =
        ent.Components().add<BeamTargetGD>().Mode(); // inferred type : BeamStaffMode
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
    ENTLIB_ASSERT(heightObj.Subdivision().get() == 0);
    auto displaceNoise0 =
        heightObj.DisplaceNoiseList()[0]; // inferred type : DisplaceNoiseListItem
    ENTLIB_ASSERT(ent.Components().get<PathNodeGD>().Radius().get() == 30.0);
    ENTLIB_ASSERT(ent.Components().get<PathNodeGD>().Radius() == 30.0);
    ent.Components().get<PathNodeGD>().Radius() = 20.0;
    double rad = ent.Components().get<PathNodeGD>().Radius();
    ENTLIB_ASSERT(rad == 20.0);

    // Test Tuple
    auto position = unitTestCpt.Position(); // inferred type : Position
    auto elt2_ = position.get<2>(); // inferred type : Float
    static_assert(std::is_same_v<decltype(elt2_), Float>);
    auto val0 = position.get<0>().get(); // inferred type : int
    static_assert(std::is_same_v<decltype(val0), int64_t>);
    ENTLIB_ASSERT(position.size() == 5);

    // Test Set of Object
    auto subscene =
        ent.Components().get<SubScene>().Embedded(); // inferred type : ObjectSet<Object>
    auto subent = subscene["EntityWithInstanceOf"]; // inferred type : Object
    static_assert(std::is_same_v<decltype(subent), Entity>);
    auto new_ent = subscene.add("NewEntity"); // inferred type : Object
    static_assert(std::is_same_v<decltype(new_ent), Entity>);

    // Test Map
    auto pathNodeGD =
        ent.Components().get<PathNodeGD>(); // inferred type : PathNodeGD
    auto tags =
        pathNodeGD.Tags().Tags(); // inferred type : Map<char const*, PrimitiveSet<String>>
    static_assert(
        std::is_same_v<decltype(tags), Map<char const*, PrimitiveSet<char const*>>>);
    auto b = tags.get("b"); // inferred type : PrimitiveSet<String>
    tags.remove("c");
    auto c = tags.add("c"); // inferred type : PrimitiveSet<String>

    // Test Map with enum key
    Map<RegenerationStateEnum, Array<sEnvStamp>> stamps =
        ent.Components().add<EnvStampGD>().Stamps();
    stamps.add(RegenerationStateEnum::Dead);
    stamps.add(RegenerationStateEnum::Dead);
    Array<sEnvStamp> deadArr = stamps.get(RegenerationStateEnum::Dead);
    ENTLIB_ASSERT(deadArr.hasValue());
    Array<sEnvStamp> lushArr = stamps.get(RegenerationStateEnum::Lush);
    ENTLIB_ASSERT(not lushArr.hasValue());
    stamps.remove(RegenerationStateEnum::Dead);
    ENTLIB_ASSERT(not stamps.get(RegenerationStateEnum::Dead).hasValue());
    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    fprintf(stderr, ex.what());
}
catch (...)
{
    fprintf(stderr, "Exception thrown");
}
