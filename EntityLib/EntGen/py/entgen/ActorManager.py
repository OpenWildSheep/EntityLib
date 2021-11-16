
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *
from entgen.Float import *
from entgen.Float import *

from EntityLibPy import Node

class ActorManager(HelperObject):
    schema_name = "ActorManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorManager
        return ActorManager(entlib.load_node_file(sourcefile, entlib.get_schema(ActorManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorManager
        return ActorManager(entlib.make_node(ActorManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SizePerceptionRanges(self):  # type: ()->Array[PrimArray[Float]]
        return (lambda n: Array((lambda n: PrimArray(Float, n)), n))(self._node.at("SizePerceptionRanges"))
    @property
    def Sizes(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Sizes"))
    @Sizes.setter
    def Sizes(self, val): self.Sizes.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




