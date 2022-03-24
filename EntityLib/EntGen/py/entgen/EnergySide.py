
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class EnergySideEnum(Enum):
    none = "none"
    lush = "lush"
    corrupted = "corrupted"
    EnergySide_COUNT = "EnergySide_COUNT"


class EnergySide(Primitive[EnergySideEnum]):  # Enum
    def __init__(self, node):
        super(EnergySide, self).__init__(EnergySideEnum, node)
    schema_name = "EnergySide"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> EnergySide
        return EnergySide(node)
    def set(self, val):  # type: (EnergySideEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




