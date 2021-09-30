
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *


class DebugGridGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DebugGridGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(DebugGridGD.schema_name))
    @property
    def Height(self): return Int(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Width(self): return Int(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




