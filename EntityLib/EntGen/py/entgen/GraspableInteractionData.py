
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.HotSpotType import *
from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GraspableInteractionData(HelperObject):
    schema_name = "GraspableInteractionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GraspableInteractionData
        return GraspableInteractionData(entlib.load_node_file(sourcefile, entlib.get_schema(GraspableInteractionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GraspableInteractionData
        return GraspableInteractionData(entlib.make_node(GraspableInteractionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def damageAccumulatedRequiredToIncapacitate(self):  # type: ()->Float
        return Float(self._node.at("damageAccumulatedRequiredToIncapacitate"))
    @damageAccumulatedRequiredToIncapacitate.setter
    def damageAccumulatedRequiredToIncapacitate(self, val): self.damageAccumulatedRequiredToIncapacitate.set(val)
    @property
    def graspedDurationMax(self):  # type: ()->Float
        return Float(self._node.at("graspedDurationMax"))
    @graspedDurationMax.setter
    def graspedDurationMax(self, val): self.graspedDurationMax.set(val)
    @property
    def hotspotType(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("hotspotType"))
    @hotspotType.setter
    def hotspotType(self, val): self.hotspotType.set(val)
    @property
    def impactRetiming(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("impactRetiming"))
    @property
    def incapacitatedTime(self):  # type: ()->Float
        return Float(self._node.at("incapacitatedTime"))
    @incapacitatedTime.setter
    def incapacitatedTime(self, val): self.incapacitatedTime.set(val)
    @property
    def interactableBoneName(self):  # type: ()->String
        return String(self._node.at("interactableBoneName"))
    @interactableBoneName.setter
    def interactableBoneName(self, val): self.interactableBoneName.set(val)
    @property
    def visualRotationRate(self):  # type: ()->Float
        return Float(self._node.at("visualRotationRate"))
    @visualRotationRate.setter
    def visualRotationRate(self, val): self.visualRotationRate.set(val)
    pass




