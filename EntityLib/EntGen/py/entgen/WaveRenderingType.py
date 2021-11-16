
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class WaveRenderingTypeEnum(Enum):
    Mesh = "Mesh"
    WaveRenderingType_COUNT = "WaveRenderingType_COUNT"


class WaveRenderingType(Primitive[WaveRenderingTypeEnum]):  # Enum
    def __init__(self, node):
        super(WaveRenderingType, self).__init__(WaveRenderingTypeEnum, node)
    schema_name = "WaveRenderingType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> WaveRenderingType
        return WaveRenderingType(node)
    def set(self, val):  # type: (WaveRenderingTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




