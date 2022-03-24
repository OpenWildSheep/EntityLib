
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class SyncTempoModeEnum(Enum):
    None_ = "None"
    OnGrid = "OnGrid"
    OnBeat = "OnBeat"
    OnBar = "OnBar"
    OnEnterCue = "OnEnterCue"
    OnExitCue = "OnExitCue"
    OnCustomCue = "OnCustomCue"
    OnSwitchTransition = "OnSwitchTransition"
    SyncTempoMode_COUNT = "SyncTempoMode_COUNT"
    SyncTempoMode_FIRST = "SyncTempoMode_FIRST"


class SyncTempoMode(Primitive[SyncTempoModeEnum]):  # Enum
    def __init__(self, node):
        super(SyncTempoMode, self).__init__(SyncTempoModeEnum, node)
    schema_name = "SyncTempoMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SyncTempoMode
        return SyncTempoMode(node)
    def set(self, val):  # type: (SyncTempoModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




