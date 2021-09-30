
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class PhysicsLayerEnum(Enum):
    Default = "Default"
    Ground = "Ground"
    Static = "Static"
    Raycast = "Raycast"
    Trigger = "Trigger"
    Walkable = "Walkable"
    Camera = "Camera"
    ClimbEdge = "ClimbEdge"
    Kinematic = "Kinematic"
    Ragdoll = "Ragdoll"
    Projectile = "Projectile"
    Hit = "Hit"
    MotionConstraint = "MotionConstraint"
    Heal = "Heal"
    Body = "Body"
    Fluid = "Fluid"
    Hitable = "Hitable"
    None_ = "None"
    All = "All"
    PHYSICLAYER_COUNT = "PHYSICLAYER_COUNT"


class PhysicsLayer(Primitive[PhysicsLayerEnum]):  # Enum
    def __init__(self, node):
        super().__init__(PhysicsLayerEnum, node)
    schema_name = "PhysicsLayer"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> PhysicsLayer
        return PhysicsLayer(node)
    def set(self, val):  # type: (PhysicsLayerEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




