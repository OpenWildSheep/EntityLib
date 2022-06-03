
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class BillboardCameraFacingQuadTypeEnum(Enum):
    AroundAxis = "AroundAxis"
    AroundCenter = "AroundCenter"
    NotFacingCamera = "NotFacingCamera"
    BGELikeShaft = "BGELikeShaft"
    BillboardCameraFacingQuadType_COUNT = "BillboardCameraFacingQuadType_COUNT"


class BillboardCameraFacingQuadType(Primitive[BillboardCameraFacingQuadTypeEnum]):  # Enum
    def __init__(self, node):
        super(BillboardCameraFacingQuadType, self).__init__(BillboardCameraFacingQuadTypeEnum, node)
    schema_name = "BillboardCameraFacingQuadType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BillboardCameraFacingQuadType
        return BillboardCameraFacingQuadType(node)
    def set(self, val):  # type: (BillboardCameraFacingQuadTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




