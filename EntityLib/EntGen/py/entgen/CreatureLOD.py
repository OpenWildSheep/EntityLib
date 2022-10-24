
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class CreatureLODEnum(Enum):
    High = "High"
    Low = "Low"
    CreatureLOD_COUNT = "CreatureLOD_COUNT"


class CreatureLOD(Primitive[CreatureLODEnum]):  # Enum
    def __init__(self, node):
        super(CreatureLOD, self).__init__(CreatureLODEnum, node)
    schema_name = "CreatureLOD"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CreatureLOD
        return CreatureLOD(node)
    def set(self, val):  # type: (CreatureLODEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




