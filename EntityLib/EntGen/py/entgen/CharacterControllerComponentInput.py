
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CharacterControllerComponentInput_CreatureLOD import *
from entgen.ComponentInput import *
from entgen.JumpHeightMultiplier import *
from entgen.ResetContinuousPositionOnGround import *
from entgen.RigidbodyScaleMultiplier import *
from entgen.RigidbodyScalingSpeed import *
from entgen.UpdateContinuousPositionOnGround import *

from EntityLibPy import Node

class CharacterControllerComponentInput(HelperObject):
    schema_name = "CharacterControllerComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerComponentInput
        return CharacterControllerComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerComponentInput
        return CharacterControllerComponentInput(entlib.make_node(CharacterControllerComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CreatureLOD(self):  # type: ()->CharacterControllerComponentInput_CreatureLOD
        return CharacterControllerComponentInput_CreatureLOD(self._node.at("CreatureLOD"))
    @property
    def JumpHeightMultiplier(self):  # type: ()->JumpHeightMultiplier
        return JumpHeightMultiplier(self._node.at("JumpHeightMultiplier"))
    @property
    def ResetContinuousPositionOnGround(self):  # type: ()->ResetContinuousPositionOnGround
        return ResetContinuousPositionOnGround(self._node.at("ResetContinuousPositionOnGround"))
    @property
    def RigidbodyScaleMultiplier(self):  # type: ()->RigidbodyScaleMultiplier
        return RigidbodyScaleMultiplier(self._node.at("RigidbodyScaleMultiplier"))
    @property
    def RigidbodyScalingSpeed(self):  # type: ()->RigidbodyScalingSpeed
        return RigidbodyScalingSpeed(self._node.at("RigidbodyScalingSpeed"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def UpdateContinuousPositionOnGround(self):  # type: ()->UpdateContinuousPositionOnGround
        return UpdateContinuousPositionOnGround(self._node.at("UpdateContinuousPositionOnGround"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




