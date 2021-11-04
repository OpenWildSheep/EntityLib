
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class LocomotionModeEnum(Enum):
    standup = "standup"
    quadstandup = "quadstandup"
    crouch = "crouch"
    prone = "prone"
    swim = "swim"
    ride = "ride"
    fly = "fly"
    dive = "dive"
    fall = "fall"
    cinematic = "cinematic"
    ridden = "ridden"
    riddenfly = "riddenfly"
    fight = "fight"
    clamber = "clamber"
    buried = "buried"
    count = "count"


class LocomotionMode(Primitive[LocomotionModeEnum]):  # Enum
    def __init__(self, node):
        super(LocomotionMode, self).__init__(LocomotionModeEnum, node)
    schema_name = "LocomotionMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> LocomotionMode
        return LocomotionMode(node)
    def set(self, val):  # type: (LocomotionModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




