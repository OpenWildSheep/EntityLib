
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class CollectibleTypeEnum(Enum):
    Vertebrae = "Vertebrae"
    Schmetre = "Schmetre"
    EnergyFruit = "EnergyFruit"
    UNDEFINED = "UNDEFINED"


class CollectibleType(Primitive[CollectibleTypeEnum]):  # Enum
    def __init__(self, node):
        super(CollectibleType, self).__init__(CollectibleTypeEnum, node)
    schema_name = "CollectibleType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CollectibleType
        return CollectibleType(node)
    def set(self, val):  # type: (CollectibleTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




