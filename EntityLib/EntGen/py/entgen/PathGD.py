
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class PathGD(HelperObject):
    schema_name = "PathGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathGD
        return PathGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathGD
        return PathGD(entlib.make_node(PathGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FilePath(self):  # type: ()->String
        return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




