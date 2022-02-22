
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class NavMeshActionTypeEnum(Enum):
    none = "none"
    jump = "jump"
    NavMeshActionType_COUNT = "NavMeshActionType_COUNT"


class NavMeshActionType(Primitive[NavMeshActionTypeEnum]):  # Enum
    def __init__(self, node):
        super(NavMeshActionType, self).__init__(NavMeshActionTypeEnum, node)
    schema_name = "NavMeshActionType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> NavMeshActionType
        return NavMeshActionType(node)
    def set(self, val):  # type: (NavMeshActionTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




