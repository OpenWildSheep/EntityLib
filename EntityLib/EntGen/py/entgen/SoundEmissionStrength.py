
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class SoundEmissionStrengthEnum(Enum):
    none = "none"
    low = "low"
    medium = "medium"
    high = "high"
    SoundEmissionStrength_COUNT = "SoundEmissionStrength_COUNT"


class SoundEmissionStrength(Primitive[SoundEmissionStrengthEnum]):  # Enum
    def __init__(self, node):
        super(SoundEmissionStrength, self).__init__(SoundEmissionStrengthEnum, node)
    schema_name = "SoundEmissionStrength"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SoundEmissionStrength
        return SoundEmissionStrength(node)
    def set(self, val):  # type: (SoundEmissionStrengthEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




