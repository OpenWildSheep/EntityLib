
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AnimationModeEnum(Enum):
    absolute = "absolute"
    additive = "additive"


class AnimationMode(Primitive[AnimationModeEnum]):  # Enum
    def __init__(self, node):
        super(AnimationMode, self).__init__(AnimationModeEnum, node)
    schema_name = "AnimationMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimationMode
        return AnimationMode(node)
    def set(self, val):  # type: (AnimationModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




