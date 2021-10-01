
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class SizeEnum(Enum):
    tiny = "tiny"
    small = "small"
    medium = "medium"
    big = "big"
    enormous = "enormous"
    Size_COUNT = "Size_COUNT"


class Size(Primitive[SizeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SizeEnum, node)
    schema_name = "Size"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Size
        return Size(node)
    def set(self, val):  # type: (SizeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




