
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class BeamStaffModeEnum(Enum):
    Off = "Off"
    Searching = "Searching"
    Creature = "Creature"
    InteractingGPE = "InteractingGPE"
    Item = "Item"
    PickUp = "PickUp"
    Hatching = "Hatching"
    SetRespawnPlaceAsCheckpoint = "SetRespawnPlaceAsCheckpoint"
    SetSavePoint = "SetSavePoint"
    EnableSpiritShrine = "EnableSpiritShrine"
    Any = "Any"
    BeamStaffMode_COUNT = "BeamStaffMode_COUNT"


class BeamStaffMode(Primitive[BeamStaffModeEnum]):  # Enum
    def __init__(self, node):
        super(BeamStaffMode, self).__init__(BeamStaffModeEnum, node)
    schema_name = "BeamStaffMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BeamStaffMode
        return BeamStaffMode(node)
    def set(self, val):  # type: (BeamStaffModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




