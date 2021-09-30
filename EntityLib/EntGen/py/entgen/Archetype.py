
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class ArchetypeEnum(Enum):
    flying = "flying"
    swimming = "swimming"
    quadripede = "quadripede"
    bipede = "bipede"
    item = "item"
    structure = "structure"
    activator = "activator"
    Archetype_COUNT = "Archetype_COUNT"


class Archetype(Primitive[ArchetypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ArchetypeEnum, node)
    schema_name = "Archetype"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Archetype
        return Archetype(node)
    def set(self, val):  # type: (ArchetypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




