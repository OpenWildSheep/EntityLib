
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class TrailRenderingSidesEnum(Enum):
    SideA = "SideA"
    SideB = "SideB"
    BothSides = "BothSides"
    TrailRenderingSides_COUNT = "TrailRenderingSides_COUNT"


class TrailRenderingSides(Primitive[TrailRenderingSidesEnum]):  # Enum
    def __init__(self, node):
        super(TrailRenderingSides, self).__init__(TrailRenderingSidesEnum, node)
    schema_name = "TrailRenderingSides"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> TrailRenderingSides
        return TrailRenderingSides(node)
    def set(self, val):  # type: (TrailRenderingSidesEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




