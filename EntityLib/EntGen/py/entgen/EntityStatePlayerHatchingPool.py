
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStatePlayerHatchingPool_Inputs import *

from EntityLibPy import Node

class EntityStatePlayerHatchingPool(HelperObject):
    schema_name = "EntityStatePlayerHatchingPool"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStatePlayerHatchingPool
        return EntityStatePlayerHatchingPool(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStatePlayerHatchingPool.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStatePlayerHatchingPool
        return EntityStatePlayerHatchingPool(entlib.make_node(EntityStatePlayerHatchingPool.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStatePlayerHatchingPool_Inputs
        return EntityStatePlayerHatchingPool_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




