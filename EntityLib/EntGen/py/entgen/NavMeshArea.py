
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class NavMeshAreaEnum(Enum):
    Hole = "Hole"
    Ground = "Ground"
    ShallowWater = "ShallowWater"
    DeepWater = "DeepWater"
    Special = "Special"
    NavMeshArea_COUNT = "NavMeshArea_COUNT"


class NavMeshArea(Primitive[NavMeshAreaEnum]):  # Enum
    def __init__(self, node):
        super(NavMeshArea, self).__init__(NavMeshAreaEnum, node)
    schema_name = "NavMeshArea"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> NavMeshArea
        return NavMeshArea(node)
    def set(self, val):  # type: (NavMeshAreaEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




