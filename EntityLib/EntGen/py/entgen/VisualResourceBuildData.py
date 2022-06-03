
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class VisualResourceBuildData(HelperObject):
    schema_name = "VisualResourceBuildData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VisualResourceBuildData
        return VisualResourceBuildData(entlib.load_node_file(sourcefile, entlib.get_schema(VisualResourceBuildData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VisualResourceBuildData
        return VisualResourceBuildData(entlib.make_node(VisualResourceBuildData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GRCs(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("GRCs"))
    @GRCs.setter
    def GRCs(self, val): self.GRCs.set(val)
    @property
    def LODs(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("LODs"))
    @LODs.setter
    def LODs(self, val): self.LODs.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




