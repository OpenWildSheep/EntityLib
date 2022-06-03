
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimTag import *
from entgen.SpeedMode import *
from entgen.String import *
from entgen.ActionTurn_Inputs import *
from entgen.ActorState import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionTurn(HelperObject):
    schema_name = "ActionTurn"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionTurn
        return ActionTurn(entlib.load_node_file(sourcefile, entlib.get_schema(ActionTurn.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionTurn
        return ActionTurn(entlib.make_node(ActionTurn.schema_name))
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
    def animTag(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("animTag"))
    @animTag.setter
    def animTag(self, val): self.animTag.set(val)
    @property
    def direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def inputs(self):  # type: ()->ActionTurn_Inputs
        return ActionTurn_Inputs(self._node.at("inputs"))
    @property
    def speedAtStart(self):  # type: ()->Float
        return Float(self._node.at("speedAtStart"))
    @speedAtStart.setter
    def speedAtStart(self, val): self.speedAtStart.set(val)
    @property
    def speedModeRequired(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("speedModeRequired"))
    @speedModeRequired.setter
    def speedModeRequired(self, val): self.speedModeRequired.set(val)
    @property
    def speedModeStart(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("speedModeStart"))
    @speedModeStart.setter
    def speedModeStart(self, val): self.speedModeStart.set(val)
    pass




