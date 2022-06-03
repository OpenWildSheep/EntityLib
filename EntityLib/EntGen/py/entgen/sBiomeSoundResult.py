
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class sBiomeSoundResult(HelperObject):
    schema_name = "sBiomeSoundResult"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sBiomeSoundResult
        return sBiomeSoundResult(entlib.load_node_file(sourcefile, entlib.get_schema(sBiomeSoundResult.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sBiomeSoundResult
        return sBiomeSoundResult(entlib.make_node(sBiomeSoundResult.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ID(self):  # type: ()->Int
        return Int(self._node.at("ID"))
    @ID.setter
    def ID(self, val): self.ID.set(val)
    @property
    def Weight(self):  # type: ()->Float
        return Float(self._node.at("Weight"))
    @Weight.setter
    def Weight(self, val): self.Weight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




