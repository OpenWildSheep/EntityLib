
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateSoulPathfindAndMove(HelperObject):
    schema_name = "ActorStateSoulPathfindAndMove"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateSoulPathfindAndMove
        return ActorStateSoulPathfindAndMove(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateSoulPathfindAndMove.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateSoulPathfindAndMove
        return ActorStateSoulPathfindAndMove(entlib.make_node(ActorStateSoulPathfindAndMove.schema_name))
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




