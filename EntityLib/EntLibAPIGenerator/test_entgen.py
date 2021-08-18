import os
from entgen.inline import *
import EntityLibPy as Ent

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
actorStateCreature = ent.ActorStates.add(ActorStateCreature)
turret = components.add(TurretComponentGD)   # inferred type : TurretComponentGD
assert isinstance(turret, TurretComponentGD)

# Test fixed size array
pos = ent.Components.get(TransformGD).Position  # inferred type : Array[Float]
x = tgd.Position[0]                             # inferred type : Float

# Test set of primitive
side = turret.ReviveSideTargeted   # inferred type : PrimitiveSet[String]
assert isinstance(side, PrimitiveSet)
turret.ReviveSideTargeted.add("neutral")
turret.ReviveSideTargeted.add("cursed")
# turret.ReviveSideTargeted.remove("neutral")
assert isinstance(turret.ReviveSideTargeted["cursed"].value, str)
assert turret.ReviveSideTargeted["cursed"].value == "cursed"
# turret.ReviveSideTargeted.erase("cursed")
sacred = turret.ReviveSideTargeted.add("sacred")  # inferred type : String
# del turret.ReviveSideTargeted["sacred"]

# Test primitive types
assert ent.Name.value == "PlayerSpawner_"
assert ent.Name.get() == "PlayerSpawner_"
# ent.Name = "PlayerSpawner_2"  # Not possible
ent.Name.set("PlayerSpawner_2")
assert ent.Name.get() == "PlayerSpawner_2"
assert ent.Name.is_set() is True
ent.Name.unset()
assert ent.Name.is_set() is False
assert heightObj.Subdivision.value == 0
displaceNoise0 = heightObj.DisplaceNoiseList[0]  # inferred type : DisplaceNoiseListItem
assert ent.Components.get(PathNodeGD).Radius.value == 30.0

# Test Tuple
position = actorStateCreature.Position   # inferred type : Position
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
