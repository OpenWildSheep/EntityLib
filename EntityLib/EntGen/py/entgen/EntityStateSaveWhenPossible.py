
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateSaveWhenPossible(HelperObject):
    schema_name = "EntityStateSaveWhenPossible"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateSaveWhenPossible
        return EntityStateSaveWhenPossible(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateSaveWhenPossible.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateSaveWhenPossible
        return EntityStateSaveWhenPossible(entlib.make_node(EntityStateSaveWhenPossible.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RespawnSlot(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("RespawnSlot"))
    @RespawnSlot.setter
    def RespawnSlot(self, val): self.RespawnSlot.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




