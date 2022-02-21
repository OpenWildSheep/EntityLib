
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class WindTurbulenceTypeEnum(Enum):
    radial = "radial"
    swirlcw = "swirlcw"
    swirlccw = "swirlccw"
    WindTurbulenceType_COUNT = "WindTurbulenceType_COUNT"


class WindTurbulenceType(Primitive[WindTurbulenceTypeEnum]):  # Enum
    def __init__(self, node):
        super(WindTurbulenceType, self).__init__(WindTurbulenceTypeEnum, node)
    schema_name = "WindTurbulenceType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> WindTurbulenceType
        return WindTurbulenceType(node)
    def set(self, val):  # type: (WindTurbulenceTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




