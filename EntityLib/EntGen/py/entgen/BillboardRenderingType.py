
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class BillboardRenderingTypeEnum(Enum):
    Cross = "Cross"
    CameraFacingQuad = "CameraFacingQuad"
    Mesh = "Mesh"
    BillboardRenderingType_COUNT = "BillboardRenderingType_COUNT"


class BillboardRenderingType(Primitive[BillboardRenderingTypeEnum]):  # Enum
    def __init__(self, node):
        super(BillboardRenderingType, self).__init__(BillboardRenderingTypeEnum, node)
    schema_name = "BillboardRenderingType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BillboardRenderingType
        return BillboardRenderingType(node)
    def set(self, val):  # type: (BillboardRenderingTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




