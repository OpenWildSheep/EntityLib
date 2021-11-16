
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class HitTypeEnum(Enum):
    HitInstant = "HitInstant"
    HitPoison = "HitPoison"
    HitDestroy = "HitDestroy"
    HitType_COUNT = "HitType_COUNT"


class HitType(Primitive[HitTypeEnum]):  # Enum
    def __init__(self, node):
        super(HitType, self).__init__(HitTypeEnum, node)
    schema_name = "HitType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> HitType
        return HitType(node)
    def set(self, val):  # type: (HitTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




