
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AnimationSpaceEnum(Enum):
    bonespace = "bonespace"
    rootspace = "rootspace"


class AnimationSpace(Primitive[AnimationSpaceEnum]):  # Enum
    def __init__(self, node):
        super(AnimationSpace, self).__init__(AnimationSpaceEnum, node)
    schema_name = "AnimationSpace"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimationSpace
        return AnimationSpace(node)
    def set(self, val):  # type: (AnimationSpaceEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




