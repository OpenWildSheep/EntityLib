
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionJump(HelperObject):
    schema_name = "ActionJump"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionJump
        return ActionJump(entlib.load_node_file(sourcefile, entlib.get_schema(ActionJump.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionJump
        return ActionJump(entlib.make_node(ActionJump.schema_name))
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
    def direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def isDoubleJump(self):  # type: ()->Bool
        return Bool(self._node.at("isDoubleJump"))
    @isDoubleJump.setter
    def isDoubleJump(self, val): self.isDoubleJump.set(val)
    @property
    def jumpAnalog(self):  # type: ()->Bool
        return Bool(self._node.at("jumpAnalog"))
    @jumpAnalog.setter
    def jumpAnalog(self, val): self.jumpAnalog.set(val)
    @property
    def speedMode(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("speedMode"))
    @speedMode.setter
    def speedMode(self, val): self.speedMode.set(val)
    @property
    def speedModeRequired(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("speedModeRequired"))
    @speedModeRequired.setter
    def speedModeRequired(self, val): self.speedModeRequired.set(val)
    pass




