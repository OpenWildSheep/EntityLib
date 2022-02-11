
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class RegenFieldEnum(Enum):
    energy = "energy"
    absorption = "absorption"
    RegenField_COUNT = "RegenField_COUNT"


class RegenField(Primitive[RegenFieldEnum]):  # Enum
    def __init__(self, node):
        super(RegenField, self).__init__(RegenFieldEnum, node)
    schema_name = "RegenField"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> RegenField
        return RegenField(node)
    def set(self, val):  # type: (RegenFieldEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




