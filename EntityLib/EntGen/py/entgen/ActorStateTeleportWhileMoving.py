
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.ActorStateTeleportWhileMovingInputs import *

from EntityLibPy import Node

class ActorStateTeleportWhileMoving(HelperObject):
    schema_name = "ActorStateTeleportWhileMoving"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateTeleportWhileMoving
        return ActorStateTeleportWhileMoving(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleportWhileMoving.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateTeleportWhileMoving
        return ActorStateTeleportWhileMoving(entlib.make_node(ActorStateTeleportWhileMoving.schema_name))
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
    @property
    def input(self):  # type: ()->ActorStateTeleportWhileMovingInputs
        return ActorStateTeleportWhileMovingInputs(self._node.at("input"))
    pass




