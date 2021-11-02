
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class AutoRotationTypeEnum(Enum):
    None_ = "None"
    _2D = "2D"
    _3D = "3D"
    AutoRotationType_COUNT = "AutoRotationType_COUNT"


class AutoRotationType(Primitive[AutoRotationTypeEnum]):  # Enum
    def __init__(self, node):
        super(AutoRotationType, self).__init__(AutoRotationTypeEnum, node)
    schema_name = "AutoRotationType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AutoRotationType
        return AutoRotationType(node)
    def set(self, val):  # type: (AutoRotationTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




