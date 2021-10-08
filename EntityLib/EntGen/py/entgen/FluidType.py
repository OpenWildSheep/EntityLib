
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class FluidTypeEnum(Enum):
    water = "water"
    lava = "lava"
    mud = "mud"
    FluidType_COUNT = "FluidType_COUNT"


class FluidType(Primitive[FluidTypeEnum]):  # Enum
    def __init__(self, node):
        super(FluidType, self).__init__(FluidTypeEnum, node)
    schema_name = "FluidType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> FluidType
        return FluidType(node)
    def set(self, val):  # type: (FluidTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




