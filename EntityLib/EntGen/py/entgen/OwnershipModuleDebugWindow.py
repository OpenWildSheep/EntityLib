
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class OwnershipModuleDebugWindowEnum(Enum):
    Tree = "Tree"
    Settings = "Settings"
    In_Game_Debug_Data = "In Game Debug Data"
    OwnershipModuleDebugWindow_COUNT = "OwnershipModuleDebugWindow_COUNT"


class OwnershipModuleDebugWindow(Primitive[OwnershipModuleDebugWindowEnum]):  # Enum
    def __init__(self, node):
        super(OwnershipModuleDebugWindow, self).__init__(OwnershipModuleDebugWindowEnum, node)
    schema_name = "OwnershipModuleDebugWindow"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> OwnershipModuleDebugWindow
        return OwnershipModuleDebugWindow(node)
    def set(self, val):  # type: (OwnershipModuleDebugWindowEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




