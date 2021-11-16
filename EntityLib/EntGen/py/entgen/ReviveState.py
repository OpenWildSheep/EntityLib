
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class ReviveStateEnum(Enum):
    skeleton = "skeleton"
    zombie = "zombie"
    full = "full"
    ReviveState_COUNT = "ReviveState_COUNT"


class ReviveState(Primitive[ReviveStateEnum]):  # Enum
    def __init__(self, node):
        super(ReviveState, self).__init__(ReviveStateEnum, node)
    schema_name = "ReviveState"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ReviveState
        return ReviveState(node)
    def set(self, val):  # type: (ReviveStateEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




