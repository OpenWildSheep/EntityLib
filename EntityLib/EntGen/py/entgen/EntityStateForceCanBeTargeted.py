
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class EntityStateForceCanBeTargeted(HelperObject):
    schema_name = "EntityStateForceCanBeTargeted"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateForceCanBeTargeted
        return EntityStateForceCanBeTargeted(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateForceCanBeTargeted.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateForceCanBeTargeted
        return EntityStateForceCanBeTargeted(entlib.make_node(EntityStateForceCanBeTargeted.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanBeTargeted(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeTargeted"))
    @CanBeTargeted.setter
    def CanBeTargeted(self, val): self.CanBeTargeted.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




