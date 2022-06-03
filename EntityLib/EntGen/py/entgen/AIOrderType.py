
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AIOrderTypeEnum(Enum):
    AIOrderType_None = "AIOrderType_None"
    follow = "follow"
    attack = "attack"
    stay = "stay"
    heal = "heal"
    transhumance = "transhumance"
    changemode = "changemode"
    readytoattack = "readytoattack"
    AIOrderType_COUNT = "AIOrderType_COUNT"


class AIOrderType(Primitive[AIOrderTypeEnum]):  # Enum
    def __init__(self, node):
        super(AIOrderType, self).__init__(AIOrderTypeEnum, node)
    schema_name = "AIOrderType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AIOrderType
        return AIOrderType(node)
    def set(self, val):  # type: (AIOrderTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




