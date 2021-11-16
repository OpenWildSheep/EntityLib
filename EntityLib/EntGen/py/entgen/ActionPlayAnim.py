
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActionMode import *
from entgen.AnimAdditionalTag import *
from entgen.AnimTag import *
from entgen.AttitudeMode import *
from entgen.CarryMode import *
from entgen.LocomotionMode import *
from entgen.SpeedMode import *
from entgen.StyleMode import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ActionPlayAnim(HelperObject):
    schema_name = "ActionPlayAnim"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionPlayAnim
        return ActionPlayAnim(entlib.load_node_file(sourcefile, entlib.get_schema(ActionPlayAnim.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionPlayAnim
        return ActionPlayAnim(entlib.make_node(ActionPlayAnim.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActionMode(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("ActionMode"))
    @ActionMode.setter
    def ActionMode(self, val): self.ActionMode.set(val)
    @property
    def AddTag(self):  # type: ()->AnimAdditionalTag
        return AnimAdditionalTag(self._node.at("AddTag"))
    @AddTag.setter
    def AddTag(self, val): self.AddTag.set(val)
    @property
    def AnimTag(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("AnimTag"))
    @AnimTag.setter
    def AnimTag(self, val): self.AnimTag.set(val)
    @property
    def AttitudeMode(self):  # type: ()->AttitudeMode
        return AttitudeMode(self._node.at("AttitudeMode"))
    @AttitudeMode.setter
    def AttitudeMode(self, val): self.AttitudeMode.set(val)
    @property
    def CarryMode(self):  # type: ()->CarryMode
        return CarryMode(self._node.at("CarryMode"))
    @CarryMode.setter
    def CarryMode(self, val): self.CarryMode.set(val)
    @property
    def LocomotionMode(self):  # type: ()->LocomotionMode
        return LocomotionMode(self._node.at("LocomotionMode"))
    @LocomotionMode.setter
    def LocomotionMode(self, val): self.LocomotionMode.set(val)
    @property
    def MaxTime(self):  # type: ()->Float
        return Float(self._node.at("MaxTime"))
    @MaxTime.setter
    def MaxTime(self, val): self.MaxTime.set(val)
    @property
    def SpeedMode(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("SpeedMode"))
    @SpeedMode.setter
    def SpeedMode(self, val): self.SpeedMode.set(val)
    @property
    def StyleMode(self):  # type: ()->StyleMode
        return StyleMode(self._node.at("StyleMode"))
    @StyleMode.setter
    def StyleMode(self, val): self.StyleMode.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def exitRequired(self):  # type: ()->Bool
        return Bool(self._node.at("exitRequired"))
    @exitRequired.setter
    def exitRequired(self, val): self.exitRequired.set(val)
    pass




