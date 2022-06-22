
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AttitudeModeEnum(Enum):
    normal = "normal"
    injured = "injured"
    dead = "dead"
    aggressive = "aggressive"
    groggy = "groggy"
    bitten = "bitten"
    charge = "charge"
    AttitudeMode_COUNT = "AttitudeMode_COUNT"


class AttitudeMode(Primitive[AttitudeModeEnum]):  # Enum
    def __init__(self, node):
        super(AttitudeMode, self).__init__(AttitudeModeEnum, node)
    schema_name = "AttitudeMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AttitudeMode
        return AttitudeMode(node)
    def set(self, val):  # type: (AttitudeModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




