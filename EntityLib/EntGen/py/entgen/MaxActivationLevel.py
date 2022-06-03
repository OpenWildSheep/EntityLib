
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class MaxActivationLevelEnum(Enum):
    Created = "Created"
    InWorld = "InWorld"
    Loading = "Loading"
    Started = "Started"


class MaxActivationLevel(Primitive[MaxActivationLevelEnum]):  # Enum
    def __init__(self, node):
        super(MaxActivationLevel, self).__init__(MaxActivationLevelEnum, node)
    
    def __call__(self, node):  # type: (EntityLibPy.Node) -> MaxActivationLevel
        return MaxActivationLevel(node)
    def set(self, val):  # type: (MaxActivationLevelEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




