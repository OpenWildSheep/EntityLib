
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class RuntimeModeEnum(Enum):
    None_ = "None"
    Container = "Container"
    Compound = "Compound"


class RuntimeMode(Primitive[RuntimeModeEnum]):  # Enum
    def __init__(self, node):
        super(RuntimeMode, self).__init__(RuntimeModeEnum, node)
    
    def __call__(self, node):  # type: (EntityLibPy.Node) -> RuntimeMode
        return RuntimeMode(node)
    def set(self, val):  # type: (RuntimeModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




