
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class EnergyIntensityEnum(Enum):
    normal = "normal"
    strong = "strong"
    COUNT = "COUNT"


class EnergyIntensity(Primitive[EnergyIntensityEnum]):  # Enum
    def __init__(self, node):
        super(EnergyIntensity, self).__init__(EnergyIntensityEnum, node)
    schema_name = "EnergyIntensity"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> EnergyIntensity
        return EnergyIntensity(node)
    def set(self, val):  # type: (EnergyIntensityEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




