
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class HitStyleEnum(Enum):
    None_ = "None"
    Bite = "Bite"
    Light = "Light"
    Medium = "Medium"
    Big = "Big"
    Eject = "Eject"
    EjectFar = "EjectFar"
    Fall = "Fall"
    Impact = "Impact"
    HitStyle_COUNT = "HitStyle_COUNT"


class HitStyle(Primitive[HitStyleEnum]):  # Enum
    def __init__(self, node):
        super(HitStyle, self).__init__(HitStyleEnum, node)
    schema_name = "HitStyle"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> HitStyle
        return HitStyle(node)
    def set(self, val):  # type: (HitStyleEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




