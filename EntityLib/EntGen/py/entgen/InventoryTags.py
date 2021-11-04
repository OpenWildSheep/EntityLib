
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class InventoryTagsEnum(Enum):
    outfit = "outfit"
    item = "item"
    default_ = "default"
    neutral = "neutral"
    sacred = "sacred"
    cursed = "cursed"
    skeleton = "skeleton"
    zombie = "zombie"
    full = "full"
    soul = "soul"
    disguise = "disguise"
    soulfreedflying = "soulfreedflying"
    soulfreednormal = "soulfreednormal"
    InventoryTags_COUNT = "InventoryTags_COUNT"


class InventoryTags(Primitive[InventoryTagsEnum]):  # Enum
    def __init__(self, node):
        super(InventoryTags, self).__init__(InventoryTagsEnum, node)
    schema_name = "InventoryTags"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> InventoryTags
        return InventoryTags(node)
    def set(self, val):  # type: (InventoryTagsEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




