
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class TrailUVUnwrappingModeEnum(Enum):
    TailToHead = "TailToHead"
    SnakeHeadToTail = "SnakeHeadToTail"
    TrailUVUnwrappingMode_COUNT = "TrailUVUnwrappingMode_COUNT"


class TrailUVUnwrappingMode(Primitive[TrailUVUnwrappingModeEnum]):  # Enum
    def __init__(self, node):
        super(TrailUVUnwrappingMode, self).__init__(TrailUVUnwrappingModeEnum, node)
    schema_name = "TrailUVUnwrappingMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> TrailUVUnwrappingMode
        return TrailUVUnwrappingMode(node)
    def set(self, val):  # type: (TrailUVUnwrappingModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




