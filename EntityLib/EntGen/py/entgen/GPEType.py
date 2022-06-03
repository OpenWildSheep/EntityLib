
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class GPETypeEnum(Enum):
    BendTree = "BendTree"
    Geyser = "Geyser"
    PossessFlocking = "PossessFlocking"
    Bridge = "Bridge"
    GPEType_COUNT = "GPEType_COUNT"


class GPEType(Primitive[GPETypeEnum]):  # Enum
    def __init__(self, node):
        super(GPEType, self).__init__(GPETypeEnum, node)
    schema_name = "GPEType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> GPEType
        return GPEType(node)
    def set(self, val):  # type: (GPETypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




