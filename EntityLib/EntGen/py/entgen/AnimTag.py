
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class AnimTagEnum(Enum):
    none = "none"
    apex = "apex"
    forward = "forward"
    forwardright = "forwardright"
    right = "right"
    backwardright = "backwardright"
    backward = "backward"
    backwardleft = "backwardleft"
    left = "left"
    forwardleft = "forwardleft"
    regular = "regular"
    alignedregular = "alignedregular"
    goofy = "goofy"
    alignedgoofy = "alignedgoofy"
    top = "top"
    bottom = "bottom"
    up = "up"
    upforward = "upforward"
    upward = "upward"
    down = "down"
    downforward = "downforward"
    downward = "downward"
    in_ = "in"
    out = "out"
    horizontal = "horizontal"
    vertical = "vertical"
    count = "count"


class AnimTag(Primitive[AnimTagEnum]):  # Enum
    def __init__(self, node):
        super().__init__(AnimTagEnum, node)
    schema_name = "AnimTag"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimTag
        return AnimTag(node)
    def set(self, val):  # type: (AnimTagEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




