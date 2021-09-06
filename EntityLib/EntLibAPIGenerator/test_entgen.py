import os
import entgen_helpers
# from entgen.inline import *
# from entgen._all import *
from entgen.Object import *
from entgen.String import *
from entgen.SubScene import *
from entgen.TransformGD import *
from entgen.HeightObj import *
from entgen.ActorStateBeingImmersed import *
from entgen.UnitTestComponent import *
from entgen.BeamTargetGD import *
from entgen.PathNodeGD import *
from entgen.EnvStampGD import *

import EntityLibPy as Ent

Entity = Object

entlib = Ent.EntityLib("X:/")
entlib.rawdata_path = Ent.path(os.path.normpath(os.getcwd() + "/../Test"))

ent = Entity(entlib.load_node_entity(Ent.path("instance.entity")))

# Test Object
name = ent.Name  # inferred type : String
assert isinstance(name, String)
components = ent.Components  # inferred type : UnionSet

# Test Set of Union
ss = components.get(SubScene)  # inferred type : SubScene
tgd = ent.Components.get(TransformGD)  # inferred type : TransformGD
heightObj = components.get(HeightObj)
assert isinstance(heightObj, HeightObj)
actorStateCreature = ent.ActorStates.add(ActorStateBeingImmersed)
unitTestCpt = components.add(UnitTestComponent)   # inferred type : UnitTestComponent
assert isinstance(unitTestCpt, UnitTestComponent)

# Test fixed size array
pos = ent.Components.get(TransformGD).Position  # inferred type : Array[Float]
x = tgd.Position[0]                             # inferred type : Float
# Copy point into Node double
tgd.Position = (1., 2., 3.)
tgd.Position = [1., 2., 3.]
# Copy Node into point
v = tgd.Position.value
assert v == [1., 2., 3.]
tgd.Position.value = [4., 5., 6.]
v = tgd.Position.value
assert v == [4., 5., 6.]

# Test set of primitive
side = unitTestCpt.EnumSet   # inferred type : PrimitiveSet[ReviveSideEnum]
assert isinstance(side, PrimitiveSet)
unitTestCpt.EnumSet.add(ReviveSideEnum.neutral)
unitTestCpt.EnumSet.add(ReviveSideEnum.cursed)
# unitTestCpt.EnumSet.remove("neutral")
assert unitTestCpt.EnumSet.count(ReviveSideEnum.cursed)
# unitTestCpt.EnumSet.erase("cursed")
unitTestCpt.EnumSet.add(ReviveSideEnum.sacred)  # inferred type : String
# del unitTestCpt.EnumSet["sacred"]

# Test Enum prop
# Do we want that a property of type BeamStaffModeEnum:
#     ent.Components.add(BeamTargetGD).Mode = BeamStaffModeEnum.Hatching
#     mode = ent.Components.add(BeamTargetGD).Mode  # return BeamStaffModeEnum
#     assert mode == BeamStaffModeEnum.Hatching
# Or do we want an object to manipulate the Node:
mode = ent.Components.add(BeamTargetGD).Mode  # inferred type: BeamStaffMode
assert isinstance(mode, BeamStaffMode)
mode.value = BeamStaffModeEnum.Hatching
assert isinstance(mode, BeamStaffMode)
enm = mode.value
assert enm is BeamStaffModeEnum.Hatching


# Test primitive types
assert ent.Name.value == "PlayerSpawner_"
assert ent.Name.get() == "PlayerSpawner_"
# ent.Name = "PlayerSpawner_2"  # Not possible
ent.Name.set("PlayerSpawner_3")
assert ent.Name.get() == "PlayerSpawner_3"
ent.Name.value = "PlayerSpawner_2"
assert ent.Name.get() == "PlayerSpawner_2"
ent.Name = "PlayerSpawner_4"
assert ent.Name.get() == "PlayerSpawner_4"
assert ent.Name.is_set() is True
ent.Name.unset()
assert ent.Name.is_set() is False
assert heightObj.Subdivision.value == 0
displaceNoise0 = heightObj.DisplaceNoiseList[0]  # inferred type : DisplaceNoiseListItem
assert ent.Components.get(PathNodeGD).Radius.value == 30.0

# Test Tuple
position = unitTestCpt.Position   # inferred type : Position
elt2 = position[2]           # inferred type : Any   :‑(     (waiting for python 3.9)
assert isinstance(elt2, Float)
elt2_ = position.get_2()                 # inferred type : Float
assert isinstance(elt2_, Float)
val0 = position.get_0().value            # inferred type : int
assert isinstance(val0, int)
assert len(position) == 5

# Test Set of Object
subscene = ent.Components.get(SubScene).Embedded   # inferred type : ObjectSet[Object]
subent = subscene["EntityWithInstanceOf"]          # inferred type : Object
assert isinstance(subent, Entity)
new_ent = subscene.add("NewEntity")                # inferred type : Object
assert isinstance(new_ent, Entity)

# Test Map
pathNodeGD = ent.Components.get(PathNodeGD)   # inferred type : PathNodeGD
tags = pathNodeGD.Tags.Tags     # inferred type : Map[str, PrimitiveSet[String]]
assert isinstance(tags, Map)
b = tags.get("b")               # inferred type : PrimitiveSet[String]
tags.remove("c")
c = tags.add("c")               # inferred type : PrimitiveSet[String]

# Test Map with enum key
stamps = ent.Components.add(EnvStampGD).Stamps
stamps.add(RegenerationStateEnum.Dead)
stamps.add(RegenerationStateEnum.Dead)
deadArr = stamps.get(RegenerationStateEnum.Dead)
assert deadArr.node is not None
lushArr = stamps.get(RegenerationStateEnum.Lush)
assert lushArr.node is None
stamps.remove(RegenerationStateEnum.Dead)
assert stamps.get(RegenerationStateEnum.Dead).node is None

# other
# scp = EntityStateCreatureProfile(None)
# vm = scp.Profile.ValueMap
# vm.get_0()   # Doesn't work yet