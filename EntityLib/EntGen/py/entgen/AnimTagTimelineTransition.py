
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AnimTagTimelineTransitionEnum(Enum):
    beginning = "beginning"
    copy = "copy"
    reverse = "reverse"
    AnimTagTimelineTransition_COUNT = "AnimTagTimelineTransition_COUNT"


class AnimTagTimelineTransition(Primitive[AnimTagTimelineTransitionEnum]):  # Enum
    def __init__(self, node):
        super().__init__(AnimTagTimelineTransitionEnum, node)
    schema_name = "AnimTagTimelineTransition"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimTagTimelineTransition
        return AnimTagTimelineTransition(node)
    def set(self, val):  # type: (AnimTagTimelineTransitionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




