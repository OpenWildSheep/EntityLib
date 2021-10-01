
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class HotSpotTypeEnum(Enum):
    all = "all"
    none = "none"
    back = "back"
    beam = "beam"
    bite = "bite"
    biter = "biter"
    breakablestrong = "breakablestrong"
    breakableweak = "breakableweak"
    camera = "camera"
    center = "center"
    head = "head"
    heal = "heal"
    ride = "ride"
    root = "root"
    snap = "snap"
    slot = "slot"
    spawnlife = "spawnlife"
    shoot = "shoot"
    take = "take"
    takehandle = "takehandle"
    vertebra = "vertebra"
    respawnslot = "respawnslot"
    HotSpotType_COUNT = "HotSpotType_COUNT"


class HotSpotType(Primitive[HotSpotTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(HotSpotTypeEnum, node)
    schema_name = "HotSpotType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> HotSpotType
        return HotSpotType(node)
    def set(self, val):  # type: (HotSpotTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




