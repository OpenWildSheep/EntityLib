
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class LodSelectionModeEnum(Enum):
    NoLod = "NoLod"
    DistanceBased = "DistanceBased"
    TriangleSizeBased = "TriangleSizeBased"


class LodSelectionMode(Primitive[LodSelectionModeEnum]):  # Enum
    def __init__(self, node):
        super(LodSelectionMode, self).__init__(LodSelectionModeEnum, node)
    schema_name = "LodSelectionMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> LodSelectionMode
        return LodSelectionMode(node)
    def set(self, val):  # type: (LodSelectionModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




