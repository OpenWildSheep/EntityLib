
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class MenaceSelectionEnum(Enum):
    closest = "closest"
    weakest = "weakest"
    strongest = "strongest"
    MenaceSelection_COUNT = "MenaceSelection_COUNT"


class MenaceSelection(Primitive[MenaceSelectionEnum]):  # Enum
    def __init__(self, node):
        super().__init__(MenaceSelectionEnum, node)
    schema_name = "MenaceSelection"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> MenaceSelection
        return MenaceSelection(node)
    def set(self, val):  # type: (MenaceSelectionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




