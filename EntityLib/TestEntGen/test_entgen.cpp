#include "../EntLibAPIGenerator/cpp/EntGen.h"
#include <ciso646>
#include <filesystem>

using namespace Ent::Gen;

void main()
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

    // Test Set of Union
    auto ss = components.get<SubScene>(); // inferred type : SubScene
    auto tgd = ent.Components().get<TransformGD>(); // inferred type : TransformGD
    auto heightObj = components.get<HeightObj>();
    static_assert(std::is_same_v<decltype(heightObj), HeightObj>);
    auto actorStateCreature = ent.ActorStates().add<ActorStateCreature>();
    auto turret =
        components.add<TurretComponentGD>(); // inferred type : TurretComponentGD
    static_assert(std::is_same_v<decltype(turret), TurretComponentGD>);
    heightObj = components.HeightObj(); // Keep this method??

    // Test fixed size array
    auto pos =
        ent.Components().get<TransformGD>().Position(); // inferred type : Vector3
    auto x = tgd.Position()[0]; // inferred type : Float

    // Test set of primitive
    auto side =
        turret.ReviveSideTargeted(); // inferred type : PrimitiveSet<String>
    static_assert(std::is_same_v<decltype(side), PrimitiveSet<String>>);
    turret.ReviveSideTargeted().add("neutral");
    turret.ReviveSideTargeted().add("cursed");
    // turret.ReviveSideTargeted.remove("neutral");
    static_assert(
        std::is_same_v<decltype(turret.ReviveSideTargeted()["cursed"].get()), char const*>);
    ENTLIB_ASSERT(
        turret.ReviveSideTargeted()["cursed"].get() == std::string("cursed"));
    turret.ReviveSideTargeted().add("sacred"); // inferred type : String
    // del turret.ReviveSideTargeted["sacred"]

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
    auto position = actorStateCreature.Position(); // inferred type : Position
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
        pathNodeGD.Tags().Tags(); // inferred type : Map<String, PrimitiveSet<String>>
    static_assert(
        std::is_same_v<decltype(tags), Map<String, PrimitiveSet<String>>>);
    auto b = tags.get("b"); // inferred type : PrimitiveSet<String>
    tags.remove("c");
    auto c = tags.add("c"); // inferred type : PrimitiveSet<String>
}
