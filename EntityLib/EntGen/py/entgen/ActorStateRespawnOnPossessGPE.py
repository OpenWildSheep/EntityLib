
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateRespawnOnPossessGPE(HelperObject):
    schema_name = "ActorStateRespawnOnPossessGPE"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateRespawnOnPossessGPE
        return ActorStateRespawnOnPossessGPE(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateRespawnOnPossessGPE.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateRespawnOnPossessGPE
        return ActorStateRespawnOnPossessGPE(entlib.make_node(ActorStateRespawnOnPossessGPE.schema_name))
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




