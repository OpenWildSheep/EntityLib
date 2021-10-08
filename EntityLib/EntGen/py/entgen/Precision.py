
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class PrecisionEnum(Enum):
    full = "full"
    half = "half"
    quarter = "quarter"
    eighth = "eighth"
    sixteenth = "sixteenth"
    highest = "highest"
    lowest = "lowest"


class Precision(Primitive[PrecisionEnum]):  # Enum
    def __init__(self, node):
        super(Precision, self).__init__(PrecisionEnum, node)
    schema_name = "Precision"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Precision
        return Precision(node)
    def set(self, val):  # type: (PrecisionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




