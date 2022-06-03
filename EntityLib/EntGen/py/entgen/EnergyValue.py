
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class EnergyValueEnum(Enum):
    corrupted_strong = "corrupted_strong"
    corrupted = "corrupted"
    lush = "lush"
    lush_strong = "lush_strong"


class EnergyValue(Primitive[EnergyValueEnum]):  # Enum
    def __init__(self, node):
        super(EnergyValue, self).__init__(EnergyValueEnum, node)
    schema_name = "EnergyValue"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> EnergyValue
        return EnergyValue(node)
    def set(self, val):  # type: (EnergyValueEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




