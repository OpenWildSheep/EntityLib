
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class BoidGoalModeEnum(Enum):
    none = "none"
    parent = "parent"
    home = "home"
    BoidGoalMode_COUNT = "BoidGoalMode_COUNT"


class BoidGoalMode(Primitive[BoidGoalModeEnum]):  # Enum
    def __init__(self, node):
        super(BoidGoalMode, self).__init__(BoidGoalModeEnum, node)
    schema_name = "BoidGoalMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BoidGoalMode
        return BoidGoalMode(node)
    def set(self, val):  # type: (BoidGoalModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




