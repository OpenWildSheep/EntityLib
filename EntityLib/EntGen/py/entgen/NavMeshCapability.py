
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class NavMeshCapabilityEnum(Enum):
    Walk = "Walk"
    SwimShallow = "SwimShallow"
    SwimDeep = "SwimDeep"
    LongJump = "LongJump"
    HighJump = "HighJump"
    EdgeWalk = "EdgeWalk"
    TunnelCross = "TunnelCross"
    Jump = "Jump"
    WallRun = "WallRun"
    WaterFall = "WaterFall"
    Climb = "Climb"
    UnderwaterTunnelCross = "UnderwaterTunnelCross"
    NavMeshCapability_COUNT = "NavMeshCapability_COUNT"


class NavMeshCapability(Primitive[NavMeshCapabilityEnum]):  # Enum
    def __init__(self, node):
        super(NavMeshCapability, self).__init__(NavMeshCapabilityEnum, node)
    schema_name = "NavMeshCapability"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> NavMeshCapability
        return NavMeshCapability(node)
    def set(self, val):  # type: (NavMeshCapabilityEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




