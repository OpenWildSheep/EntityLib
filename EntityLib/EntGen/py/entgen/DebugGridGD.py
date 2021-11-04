
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class DebugGridGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DebugGridGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DebugGridGD
        return DebugGridGD(entlib.load_node_file(sourcefile, entlib.get_schema(DebugGridGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DebugGridGD
        return DebugGridGD(entlib.make_node(DebugGridGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Height(self):  # type: ()->Int
        return Int(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Width(self):  # type: ()->Int
        return Int(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




