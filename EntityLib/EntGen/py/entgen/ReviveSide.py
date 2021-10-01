
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class ReviveSideEnum(Enum):
    neutral = "neutral"
    sacred = "sacred"
    cursed = "cursed"
    ReviveSide_COUNT = "ReviveSide_COUNT"


class ReviveSide(Primitive[ReviveSideEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ReviveSideEnum, node)
    schema_name = "ReviveSide"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ReviveSide
        return ReviveSide(node)
    def set(self, val):  # type: (ReviveSideEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




