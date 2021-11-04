
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.GrowingState import *
from entgen.String import *
from entgen.Float import *
from entgen.ProgressSoundEventData import *

from EntityLibPy import Node

class AnimationTreeConstraintsGD_GrowData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::GrowData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD_GrowData
        return AnimationTreeConstraintsGD_GrowData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_GrowData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD_GrowData
        return AnimationTreeConstraintsGD_GrowData(entlib.make_node(AnimationTreeConstraintsGD_GrowData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DegrowShakeForce(self):  # type: ()->Float
        return Float(self._node.at("DegrowShakeForce"))
    @DegrowShakeForce.setter
    def DegrowShakeForce(self, val): self.DegrowShakeForce.set(val)
    @property
    def GrowShakeForce(self):  # type: ()->Float
        return Float(self._node.at("GrowShakeForce"))
    @GrowShakeForce.setter
    def GrowShakeForce(self, val): self.GrowShakeForce.set(val)
    @property
    def GrowSpeed(self):  # type: ()->Float
        return Float(self._node.at("GrowSpeed"))
    @GrowSpeed.setter
    def GrowSpeed(self, val): self.GrowSpeed.set(val)
    @property
    def GrowingState(self):  # type: ()->GrowingState
        return GrowingState(self._node.at("GrowingState"))
    @GrowingState.setter
    def GrowingState(self, val): self.GrowingState.set(val)
    @property
    def ProgressSoundEventData(self):  # type: ()->ProgressSoundEventData
        return ProgressSoundEventData(self._node.at("ProgressSoundEventData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




