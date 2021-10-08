
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class CinematicUpdateTypeEnum(Enum):
    none = "none"
    Internal = "Internal"
    Pesto = "Pesto"
    CinematicUpdateType_COUNT = "CinematicUpdateType_COUNT"


class CinematicUpdateType(Primitive[CinematicUpdateTypeEnum]):  # Enum
    def __init__(self, node):
        super(CinematicUpdateType, self).__init__(CinematicUpdateTypeEnum, node)
    schema_name = "CinematicUpdateType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CinematicUpdateType
        return CinematicUpdateType(node)
    def set(self, val):  # type: (CinematicUpdateTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




