
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class OutfitPieceTypeEnum(Enum):
    OutfitPieceType_NONE = "OutfitPieceType_NONE"
    Head = "Head"
    Torso = "Torso"
    Skirt = "Skirt"
    Boots = "Boots"
    Brace = "Brace"
    Body = "Body"
    Hair = "Hair"
    OutfitPieceType_COUNT = "OutfitPieceType_COUNT"


class OutfitPieceType(Primitive[OutfitPieceTypeEnum]):  # Enum
    def __init__(self, node):
        super(OutfitPieceType, self).__init__(OutfitPieceTypeEnum, node)
    schema_name = "OutfitPieceType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> OutfitPieceType
        return OutfitPieceType(node)
    def set(self, val):  # type: (OutfitPieceTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




