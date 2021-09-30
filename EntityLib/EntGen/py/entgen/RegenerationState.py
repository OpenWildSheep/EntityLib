
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class RegenerationStateEnum(Enum):
    None_ = "None"
    Sacred = "Sacred"
    Cursed = "Cursed"
    Lush = "Lush"
    Neutral = "Neutral"
    Dead = "Dead"
    RegenerationState_COUNT = "RegenerationState_COUNT"


class RegenerationState(Primitive[RegenerationStateEnum]):  # Enum
    def __init__(self, node):
        super().__init__(RegenerationStateEnum, node)
    schema_name = "RegenerationState"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> RegenerationState
        return RegenerationState(node)
    def set(self, val):  # type: (RegenerationStateEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




