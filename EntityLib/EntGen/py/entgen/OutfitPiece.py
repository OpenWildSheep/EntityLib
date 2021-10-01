
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.OutfitPieceType import *
from entgen.String import *
from entgen.EntityRef import *

from EntityLibPy import Node

class OutfitPiece(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/OutfitPiece"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitPiece
        return OutfitPiece(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitPiece.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitPiece
        return OutfitPiece(entlib.make_node(OutfitPiece.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Slot(self):  # type: ()->OutfitPieceType
        return OutfitPieceType(self._node.at("Slot"))
    @Slot.setter
    def Slot(self, val): self.Slot.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




