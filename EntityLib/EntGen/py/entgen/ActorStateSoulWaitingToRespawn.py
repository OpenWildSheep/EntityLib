
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateSoulWaitingToRespawn(HelperObject):
    schema_name = "ActorStateSoulWaitingToRespawn"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateSoulWaitingToRespawn
        return ActorStateSoulWaitingToRespawn(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateSoulWaitingToRespawn.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateSoulWaitingToRespawn
        return ActorStateSoulWaitingToRespawn(entlib.make_node(ActorStateSoulWaitingToRespawn.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




