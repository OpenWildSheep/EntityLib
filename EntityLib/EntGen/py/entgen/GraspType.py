
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class GraspTypeEnum(Enum):
    Bite = "Bite"
    Grab = "Grab"
    Hold = "Hold"
    GraspType_COUNT = "GraspType_COUNT"


class GraspType(Primitive[GraspTypeEnum]):  # Enum
    def __init__(self, node):
        super(GraspType, self).__init__(GraspTypeEnum, node)
    schema_name = "GraspType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> GraspType
        return GraspType(node)
    def set(self, val):  # type: (GraspTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




