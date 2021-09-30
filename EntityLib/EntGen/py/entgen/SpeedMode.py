
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class SpeedModeEnum(Enum):
    speed0 = "speed0"
    speed1 = "speed1"
    speed2 = "speed2"
    speed3 = "speed3"
    speed4 = "speed4"
    SpeedMode_COUNT = "SpeedMode_COUNT"


class SpeedMode(Primitive[SpeedModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SpeedModeEnum, node)
    schema_name = "SpeedMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SpeedMode
        return SpeedMode(node)
    def set(self, val):  # type: (SpeedModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




