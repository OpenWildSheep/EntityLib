
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
from entgen.Float import *

from EntityLibPy import Node

class AnimTags(HelperObject):
    schema_name = "AnimTags"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimTags
        return AnimTags(entlib.load_node_file(sourcefile, entlib.get_schema(AnimTags.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimTags
        return AnimTags(entlib.make_node(AnimTags.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActionMode(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("ActionMode"))
    @ActionMode.setter
    def ActionMode(self, val): self.ActionMode.set(val)
    @property
    def AnimAdditionalTag(self):  # type: ()->AnimAdditionalTag
        return AnimAdditionalTag(self._node.at("AnimAdditionalTag"))
    @AnimAdditionalTag.setter
    def AnimAdditionalTag(self, val): self.AnimAdditionalTag.set(val)
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
    def PlayRatio(self):  # type: ()->Float
        return Float(self._node.at("PlayRatio"))
    @PlayRatio.setter
    def PlayRatio(self, val): self.PlayRatio.set(val)
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
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




