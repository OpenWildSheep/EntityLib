
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class NavMeshTagEnum(Enum):
    Lush = "Lush"
    Corrupted = "Corrupted"
    Spirit = "Spirit"
    NonSpirit = "NonSpirit"
    NavMeshTag_COUNT = "NavMeshTag_COUNT"


class NavMeshTag(Primitive[NavMeshTagEnum]):  # Enum
    def __init__(self, node):
        super(NavMeshTag, self).__init__(NavMeshTagEnum, node)
    schema_name = "NavMeshTag"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> NavMeshTag
        return NavMeshTag(node)
    def set(self, val):  # type: (NavMeshTagEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




