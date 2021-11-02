
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class PathPosition(HelperObject):
    schema_name = "PathPosition"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathPosition
        return PathPosition(entlib.load_node_file(sourcefile, entlib.get_schema(PathPosition.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathPosition
        return PathPosition(entlib.make_node(PathPosition.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Ratio(self):  # type: ()->Float
        return Float(self._node.at("Ratio"))
    @Ratio.setter
    def Ratio(self, val): self.Ratio.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




