
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class Object_MaxActivationLevelEnum(Enum):
    Created = "Created"
    InWorld = "InWorld"
    Loading = "Loading"
    Started = "Started"


class Object_MaxActivationLevel(Primitive[Object_MaxActivationLevelEnum]):  # Enum
    def __init__(self, node):
        super().__init__(Object_MaxActivationLevelEnum, node)
    
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Object_MaxActivationLevel
        return Object_MaxActivationLevel(node)
    def set(self, val):  # type: (Object_MaxActivationLevelEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




