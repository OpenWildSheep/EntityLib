
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AdditionnalTag import *
from entgen.AnimationModelComponentInput_ActionMode import *
from entgen.AnimationModelComponentInput_AnimTag import *
from entgen.AnimationModelComponentInput_AttitudeMode import *
from entgen.AnimationModelComponentInput_CarryMode import *
from entgen.AnimationModelComponentInput_LocomotionMode import *
from entgen.AnimationModelComponentInput_SpeedMode import *
from entgen.AnimationModelComponentInput_StyleMode import *
from entgen.ComponentInput import *
from entgen.ForceBlendIn import *
from entgen.ForceBlendInReachRequired import *
from entgen.PlayRatio import *
from entgen.SpeedModeMax import *
from entgen.SpeedScaleXY import *
from entgen.VariantAllowed import *

from EntityLibPy import Node

class AnimationModelComponentInput(HelperObject):
    schema_name = "AnimationModelComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationModelComponentInput
        return AnimationModelComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationModelComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationModelComponentInput
        return AnimationModelComponentInput(entlib.make_node(AnimationModelComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActionMode(self):  # type: ()->AnimationModelComponentInput_ActionMode
        return AnimationModelComponentInput_ActionMode(self._node.at("ActionMode"))
    @property
    def AdditionnalTag(self):  # type: ()->AdditionnalTag
        return AdditionnalTag(self._node.at("AdditionnalTag"))
    @property
    def AnimTag(self):  # type: ()->AnimationModelComponentInput_AnimTag
        return AnimationModelComponentInput_AnimTag(self._node.at("AnimTag"))
    @property
    def AttitudeMode(self):  # type: ()->AnimationModelComponentInput_AttitudeMode
        return AnimationModelComponentInput_AttitudeMode(self._node.at("AttitudeMode"))
    @property
    def CarryMode(self):  # type: ()->AnimationModelComponentInput_CarryMode
        return AnimationModelComponentInput_CarryMode(self._node.at("CarryMode"))
    @property
    def ForceBlendIn(self):  # type: ()->ForceBlendIn
        return ForceBlendIn(self._node.at("ForceBlendIn"))
    @property
    def ForceBlendInReachRequired(self):  # type: ()->ForceBlendInReachRequired
        return ForceBlendInReachRequired(self._node.at("ForceBlendInReachRequired"))
    @property
    def LocomotionMode(self):  # type: ()->AnimationModelComponentInput_LocomotionMode
        return AnimationModelComponentInput_LocomotionMode(self._node.at("LocomotionMode"))
    @property
    def PlayRatio(self):  # type: ()->PlayRatio
        return PlayRatio(self._node.at("PlayRatio"))
    @property
    def SpeedMode(self):  # type: ()->AnimationModelComponentInput_SpeedMode
        return AnimationModelComponentInput_SpeedMode(self._node.at("SpeedMode"))
    @property
    def SpeedModeMax(self):  # type: ()->SpeedModeMax
        return SpeedModeMax(self._node.at("SpeedModeMax"))
    @property
    def SpeedScaleXY(self):  # type: ()->SpeedScaleXY
        return SpeedScaleXY(self._node.at("SpeedScaleXY"))
    @property
    def StyleMode(self):  # type: ()->AnimationModelComponentInput_StyleMode
        return AnimationModelComponentInput_StyleMode(self._node.at("StyleMode"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def VariantAllowed(self):  # type: ()->VariantAllowed
        return VariantAllowed(self._node.at("VariantAllowed"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




