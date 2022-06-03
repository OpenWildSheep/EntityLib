
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class OutfitFadeParameter(HelperObject):
    schema_name = "OutfitFadeParameter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitFadeParameter
        return OutfitFadeParameter(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitFadeParameter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitFadeParameter
        return OutfitFadeParameter(entlib.make_node(OutfitFadeParameter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Delay(self):  # type: ()->Float
        return Float(self._node.at("Delay"))
    @Delay.setter
    def Delay(self, val): self.Delay.set(val)
    @property
    def Emissive(self):  # type: ()->Bool
        return Bool(self._node.at("Emissive"))
    @Emissive.setter
    def Emissive(self, val): self.Emissive.set(val)
    @property
    def Enabled(self):  # type: ()->Bool
        return Bool(self._node.at("Enabled"))
    @Enabled.setter
    def Enabled(self, val): self.Enabled.set(val)
    @property
    def FadeBodyPiece(self):  # type: ()->Bool
        return Bool(self._node.at("FadeBodyPiece"))
    @FadeBodyPiece.setter
    def FadeBodyPiece(self, val): self.FadeBodyPiece.set(val)
    @property
    def Time(self):  # type: ()->Float
        return Float(self._node.at("Time"))
    @Time.setter
    def Time(self, val): self.Time.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




