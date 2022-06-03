
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AaModeEnum(Enum):
    Fxaa = "Fxaa"
    Smaa = "Smaa"
    None_ = "None"
    AaMode_Count = "AaMode_Count"


class AaMode(Primitive[AaModeEnum]):  # Enum
    def __init__(self, node):
        super(AaMode, self).__init__(AaModeEnum, node)
    schema_name = "AaMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AaMode
        return AaMode(node)
    def set(self, val):  # type: (AaModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




