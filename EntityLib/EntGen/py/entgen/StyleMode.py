
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class StyleModeEnum(Enum):
    default_ = "default"
    stick = "stick"
    sword = "sword"
    do_ = "do"
    hammer = "hammer"
    knife = "knife"
    squirrel = "squirrel"
    lush = "lush"
    StyleMode_COUNT = "StyleMode_COUNT"


class StyleMode(Primitive[StyleModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(StyleModeEnum, node)
    schema_name = "StyleMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> StyleMode
        return StyleMode(node)
    def set(self, val):  # type: (StyleModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




