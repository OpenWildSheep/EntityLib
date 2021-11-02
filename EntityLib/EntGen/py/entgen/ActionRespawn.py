
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Position import *

from EntityLibPy import Node

class ActionRespawn(HelperObject):
    schema_name = "ActionRespawn"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionRespawn
        return ActionRespawn(entlib.load_node_file(sourcefile, entlib.get_schema(ActionRespawn.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionRespawn
        return ActionRespawn(entlib.make_node(ActionRespawn.schema_name))
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
    def respawnDone(self):  # type: ()->Bool
        return Bool(self._node.at("respawnDone"))
    @respawnDone.setter
    def respawnDone(self, val): self.respawnDone.set(val)
    @property
    def respawnPosition(self):  # type: ()->Position
        return Position(self._node.at("respawnPosition"))
    @property
    def respawnSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("respawnSide"))
    @respawnSide.setter
    def respawnSide(self, val): self.respawnSide.set(val)
    pass




