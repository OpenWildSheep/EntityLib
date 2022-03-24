
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class TrailRenderingTypeEnum(Enum):
    Cross = "Cross"
    Billboard = "Billboard"
    Patches = "Patches"
    Mesh = "Mesh"
    TrailRenderingType_COUNT = "TrailRenderingType_COUNT"


class TrailRenderingType(Primitive[TrailRenderingTypeEnum]):  # Enum
    def __init__(self, node):
        super(TrailRenderingType, self).__init__(TrailRenderingTypeEnum, node)
    schema_name = "TrailRenderingType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> TrailRenderingType
        return TrailRenderingType(node)
    def set(self, val):  # type: (TrailRenderingTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




