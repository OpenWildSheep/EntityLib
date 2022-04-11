
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateUseAsActiveCheckpoint(HelperObject):
    schema_name = "EntityStateUseAsActiveCheckpoint"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateUseAsActiveCheckpoint
        return EntityStateUseAsActiveCheckpoint(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateUseAsActiveCheckpoint.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateUseAsActiveCheckpoint
        return EntityStateUseAsActiveCheckpoint(entlib.make_node(EntityStateUseAsActiveCheckpoint.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




