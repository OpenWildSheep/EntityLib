
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class MeshNavigationAllowedModeEnum(Enum):
    Never = "Never"
    PlayerOnly = "PlayerOnly"
    Always = "Always"
    MeshNavigationAllowedMode_COUNT = "MeshNavigationAllowedMode_COUNT"


class MeshNavigationAllowedMode(Primitive[MeshNavigationAllowedModeEnum]):  # Enum
    def __init__(self, node):
        super(MeshNavigationAllowedMode, self).__init__(MeshNavigationAllowedModeEnum, node)
    schema_name = "MeshNavigationAllowedMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> MeshNavigationAllowedMode
        return MeshNavigationAllowedMode(node)
    def set(self, val):  # type: (MeshNavigationAllowedModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




