
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateManageChildEntityPool_Inputs import *

from EntityLibPy import Node

class EntityStateManageChildEntityPool(HelperObject):
    schema_name = "EntityStateManageChildEntityPool"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateManageChildEntityPool
        return EntityStateManageChildEntityPool(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateManageChildEntityPool.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateManageChildEntityPool
        return EntityStateManageChildEntityPool(entlib.make_node(EntityStateManageChildEntityPool.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStateManageChildEntityPool_Inputs
        return EntityStateManageChildEntityPool_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




