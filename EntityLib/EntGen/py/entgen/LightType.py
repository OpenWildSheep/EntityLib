
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class LightTypeEnum(Enum):
    Omni = "Omni"
    Hemi = "Hemi"
    Spot = "Spot"
    Dir = "Dir"
    LightType_Count = "LightType_Count"


class LightType(Primitive[LightTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(LightTypeEnum, node)
    schema_name = "LightType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> LightType
        return LightType(node)
    def set(self, val):  # type: (LightTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




