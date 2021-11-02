
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class BillboardRenderingSidesEnum(Enum):
    SideA = "SideA"
    SideB = "SideB"
    BothSides = "BothSides"
    BillboardRenderingSides_COUNT = "BillboardRenderingSides_COUNT"


class BillboardRenderingSides(Primitive[BillboardRenderingSidesEnum]):  # Enum
    def __init__(self, node):
        super(BillboardRenderingSides, self).__init__(BillboardRenderingSidesEnum, node)
    schema_name = "BillboardRenderingSides"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BillboardRenderingSides
        return BillboardRenderingSides(node)
    def set(self, val):  # type: (BillboardRenderingSidesEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




