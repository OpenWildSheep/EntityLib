
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.GrowingState import *
from entgen.String import *
from entgen.Float import *
from entgen.ProgressSoundEventData import *


class AnimationTreeConstraintsGD_GrowData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::GrowData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_GrowData.schema_name))
    @property
    def DegrowShakeForce(self): return Float(self._node.at("DegrowShakeForce"))
    @DegrowShakeForce.setter
    def DegrowShakeForce(self, val): self.DegrowShakeForce.set(val)
    @property
    def GrowShakeForce(self): return Float(self._node.at("GrowShakeForce"))
    @GrowShakeForce.setter
    def GrowShakeForce(self, val): self.GrowShakeForce.set(val)
    @property
    def GrowSpeed(self): return Float(self._node.at("GrowSpeed"))
    @GrowSpeed.setter
    def GrowSpeed(self, val): self.GrowSpeed.set(val)
    @property
    def GrowingState(self): return GrowingState(self._node.at("GrowingState"))
    @GrowingState.setter
    def GrowingState(self, val): self.GrowingState.set(val)
    @property
    def ProgressSoundEventData(self): return ProgressSoundEventData(self._node.at("ProgressSoundEventData"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




