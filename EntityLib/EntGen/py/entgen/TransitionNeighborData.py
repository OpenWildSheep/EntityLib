
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *


class TransitionNeighborData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TransitionNeighborData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TransitionNeighborData.schema_name))
    @property
    def Backward(self): return (lambda n: PrimArray(Int, n))(self._node.at("Backward"))
    @Backward.setter
    def Backward(self, val): self.Backward.set(val)
    @property
    def Forward(self): return (lambda n: PrimArray(Int, n))(self._node.at("Forward"))
    @Forward.setter
    def Forward(self, val): self.Forward.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




