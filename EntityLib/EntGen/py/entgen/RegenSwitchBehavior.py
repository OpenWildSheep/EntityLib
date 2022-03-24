
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class RegenSwitchBehaviorEnum(Enum):
    CrossFade = "CrossFade"
    CrossMetamorphosis = "CrossMetamorphosis"
    SequentialMetamorphosis = "SequentialMetamorphosis"
    InterruptibleSequentialMetamorphosis = "InterruptibleSequentialMetamorphosis"


class RegenSwitchBehavior(Primitive[RegenSwitchBehaviorEnum]):  # Enum
    def __init__(self, node):
        super(RegenSwitchBehavior, self).__init__(RegenSwitchBehaviorEnum, node)
    schema_name = "RegenSwitchBehavior"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> RegenSwitchBehavior
        return RegenSwitchBehavior(node)
    def set(self, val):  # type: (RegenSwitchBehaviorEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




