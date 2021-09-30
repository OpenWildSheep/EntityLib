
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class GrowingStateEnum(Enum):
    invalid = "invalid"
    nogrow = "nogrow"
    growing = "growing"
    grown = "grown"
    manualgrow = "manualgrow"
    degrowing = "degrowing"
    GrowingState_COUNT = "GrowingState_COUNT"


class GrowingState(Primitive[GrowingStateEnum]):  # Enum
    def __init__(self, node):
        super().__init__(GrowingStateEnum, node)
    schema_name = "GrowingState"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> GrowingState
        return GrowingState(node)
    def set(self, val):  # type: (GrowingStateEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




