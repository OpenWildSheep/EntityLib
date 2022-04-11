
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class sBiomeSFXResult(HelperObject):
    schema_name = "sBiomeSFXResult"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sBiomeSFXResult
        return sBiomeSFXResult(entlib.load_node_file(sourcefile, entlib.get_schema(sBiomeSFXResult.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sBiomeSFXResult
        return sBiomeSFXResult(entlib.make_node(sBiomeSFXResult.schema_name))
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




