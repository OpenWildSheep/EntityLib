
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class CarryModeEnum(Enum):
    carryno = "carryno"
    carrylight = "carrylight"
    CarryMode_COUNT = "CarryMode_COUNT"


class CarryMode(Primitive[CarryModeEnum]):  # Enum
    def __init__(self, node):
        super(CarryMode, self).__init__(CarryModeEnum, node)
    schema_name = "CarryMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CarryMode
        return CarryMode(node)
    def set(self, val):  # type: (CarryModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




