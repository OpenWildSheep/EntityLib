
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class AirControlAssistGD(HelperObject):
    schema_name = "AirControlAssistGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AirControlAssistGD
        return AirControlAssistGD(entlib.load_node_file(sourcefile, entlib.get_schema(AirControlAssistGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AirControlAssistGD
        return AirControlAssistGD(entlib.make_node(AirControlAssistGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxFallingDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxFallingDistance"))
    @MaxFallingDistance.setter
    def MaxFallingDistance(self, val): self.MaxFallingDistance.set(val)
    @property
    def MaxTrajectoryDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxTrajectoryDistance"))
    @MaxTrajectoryDistance.setter
    def MaxTrajectoryDistance(self, val): self.MaxTrajectoryDistance.set(val)
    @property
    def SmoothingAssistSpeed(self):  # type: ()->Float
        return Float(self._node.at("SmoothingAssistSpeed"))
    @SmoothingAssistSpeed.setter
    def SmoothingAssistSpeed(self, val): self.SmoothingAssistSpeed.set(val)
    @property
    def SpeedAddDistanceFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedAddDistanceFactor"))
    @property
    def SphereCastGrowFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SphereCastGrowFactor"))
    @property
    def SphereCastStartRigidbodyRadiusMultiplier(self):  # type: ()->Float
        return Float(self._node.at("SphereCastStartRigidbodyRadiusMultiplier"))
    @SphereCastStartRigidbodyRadiusMultiplier.setter
    def SphereCastStartRigidbodyRadiusMultiplier(self, val): self.SphereCastStartRigidbodyRadiusMultiplier.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TrajectoryDistanceSampling(self):  # type: ()->Float
        return Float(self._node.at("TrajectoryDistanceSampling"))
    @TrajectoryDistanceSampling.setter
    def TrajectoryDistanceSampling(self, val): self.TrajectoryDistanceSampling.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




