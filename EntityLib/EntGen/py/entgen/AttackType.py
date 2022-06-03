
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AttackTypeEnum(Enum):
    Normal = "Normal"
    Backward = "Backward"
    Charged = "Charged"
    JumpOnto = "JumpOnto"
    Bite = "Bite"
    Stomp = "Stomp"
    Dive = "Dive"
    AttackType_COUNT = "AttackType_COUNT"


class AttackType(Primitive[AttackTypeEnum]):  # Enum
    def __init__(self, node):
        super(AttackType, self).__init__(AttackTypeEnum, node)
    schema_name = "AttackType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AttackType
        return AttackType(node)
    def set(self, val):  # type: (AttackTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




