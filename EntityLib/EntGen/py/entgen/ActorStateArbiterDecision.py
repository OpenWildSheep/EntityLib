
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class ActorStateArbiterDecisionEnum(Enum):
    CancelCurrent = "CancelCurrent"
    Coexist = "Coexist"
    RejectNew = "RejectNew"
    Specific = "Specific"
    Wait = "Wait"
    ArbiterDecision_COUNT = "ArbiterDecision_COUNT"


class ActorStateArbiterDecision(Primitive[ActorStateArbiterDecisionEnum]):  # Enum
    def __init__(self, node):
        super(ActorStateArbiterDecision, self).__init__(ActorStateArbiterDecisionEnum, node)
    schema_name = "ActorStateArbiterDecision"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ActorStateArbiterDecision
        return ActorStateArbiterDecision(node)
    def set(self, val):  # type: (ActorStateArbiterDecisionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




