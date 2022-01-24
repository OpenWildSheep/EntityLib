
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class GroupAvoidanceEnumEnum(Enum):
    lush = "lush"
    corrupted = "corrupted"
    tiny = "tiny"
    small = "small"
    medium = "medium"
    big = "big"
    enormous = "enormous"
    GroupAvoidanceEnum_COUNT = "GroupAvoidanceEnum_COUNT"


class GroupAvoidanceEnum(Primitive[GroupAvoidanceEnumEnum]):  # Enum
    def __init__(self, node):
        super(GroupAvoidanceEnum, self).__init__(GroupAvoidanceEnumEnum, node)
    schema_name = "GroupAvoidanceEnum"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> GroupAvoidanceEnum
        return GroupAvoidanceEnum(node)
    def set(self, val):  # type: (GroupAvoidanceEnumEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




