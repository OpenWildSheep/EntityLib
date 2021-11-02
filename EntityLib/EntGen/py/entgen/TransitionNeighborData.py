
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class TransitionNeighborData(HelperObject):
    schema_name = "TransitionNeighborData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TransitionNeighborData
        return TransitionNeighborData(entlib.load_node_file(sourcefile, entlib.get_schema(TransitionNeighborData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TransitionNeighborData
        return TransitionNeighborData(entlib.make_node(TransitionNeighborData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Backward(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("Backward"))
    @Backward.setter
    def Backward(self, val): self.Backward.set(val)
    @property
    def Forward(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("Forward"))
    @Forward.setter
    def Forward(self, val): self.Forward.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




