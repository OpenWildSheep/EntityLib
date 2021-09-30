
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class AttackTypeEnum(Enum):
    Short = "Short"
    Long = "Long"
    Backward = "Backward"
    Charged = "Charged"
    Distant = "Distant"
    Push = "Push"
    Unmount = "Unmount"
    Dodge = "Dodge"
    Uppercut = "Uppercut"
    Landing = "Landing"
    JumpOnto = "JumpOnto"
    Bite = "Bite"
    Stomp = "Stomp"
    AttackType_COUNT = "AttackType_COUNT"


class AttackType(Primitive[AttackTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(AttackTypeEnum, node)
    schema_name = "AttackType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AttackType
        return AttackType(node)
    def set(self, val):  # type: (AttackTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




