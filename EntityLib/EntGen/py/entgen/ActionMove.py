
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionMove(HelperObject):
    schema_name = "ActionMove"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionMove
        return ActionMove(entlib.load_node_file(sourcefile, entlib.get_schema(ActionMove.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionMove
        return ActionMove(entlib.make_node(ActionMove.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CurrentDirection(self):  # type: ()->Vector3
        return Vector3(self._node.at("CurrentDirection"))
    @CurrentDirection.setter
    def CurrentDirection(self, val): self.CurrentDirection.set(val)
    @property
    def InstantReachSpeedRequired(self):  # type: ()->Bool
        return Bool(self._node.at("InstantReachSpeedRequired"))
    @InstantReachSpeedRequired.setter
    def InstantReachSpeedRequired(self, val): self.InstantReachSpeedRequired.set(val)
    @property
    def Speed(self):  # type: ()->Float
        return Float(self._node.at("Speed"))
    @Speed.setter
    def Speed(self, val): self.Speed.set(val)
    @property
    def SpeedModeDest(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("SpeedModeDest"))
    @SpeedModeDest.setter
    def SpeedModeDest(self, val): self.SpeedModeDest.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




