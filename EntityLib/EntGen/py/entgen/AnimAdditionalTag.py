
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AnimAdditionalTagEnum(Enum):
    none = "none"
    small = "small"
    light = "light"
    medium = "medium"
    big = "big"
    enormous = "enormous"
    menace = "menace"
    variant1 = "variant1"
    variant2 = "variant2"
    variant3 = "variant3"
    variant4 = "variant4"
    variant5 = "variant5"
    variant6 = "variant6"
    variant7 = "variant7"
    variant8 = "variant8"
    variant9 = "variant9"
    variant10 = "variant10"
    variant11 = "variant11"
    variant12 = "variant12"
    variant13 = "variant13"
    variant14 = "variant14"
    variant15 = "variant15"
    variant16 = "variant16"
    variant17 = "variant17"
    variant18 = "variant18"
    variant19 = "variant19"
    variant20 = "variant20"
    ejected = "ejected"
    ejectedfar = "ejectedfar"
    plunge = "plunge"
    lateralplunge = "lateralplunge"
    aerialplunge = "aerialplunge"
    waterfall = "waterfall"
    AnimAdditionalTag_COUNT = "AnimAdditionalTag_COUNT"


class AnimAdditionalTag(Primitive[AnimAdditionalTagEnum]):  # Enum
    def __init__(self, node):
        super(AnimAdditionalTag, self).__init__(AnimAdditionalTagEnum, node)
    schema_name = "AnimAdditionalTag"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimAdditionalTag
        return AnimAdditionalTag(node)
    def set(self, val):  # type: (AnimAdditionalTagEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




