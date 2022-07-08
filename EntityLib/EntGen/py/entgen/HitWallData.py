
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.HitWallEnvironmentData import *

from EntityLibPy import Node

class HitWallData(HelperObject):
    schema_name = "HitWallData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HitWallData
        return HitWallData(entlib.load_node_file(sourcefile, entlib.get_schema(HitWallData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HitWallData
        return HitWallData(entlib.make_node(HitWallData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AverageSpeedThreshold(self):  # type: ()->Float
        return Float(self._node.at("AverageSpeedThreshold"))
    @AverageSpeedThreshold.setter
    def AverageSpeedThreshold(self, val): self.AverageSpeedThreshold.set(val)
    @property
    def ContactAngleMax(self):  # type: ()->Float
        return Float(self._node.at("ContactAngleMax"))
    @ContactAngleMax.setter
    def ContactAngleMax(self, val): self.ContactAngleMax.set(val)
    @property
    def DefaultEnvironmentData(self):  # type: ()->HitWallEnvironmentData
        return HitWallEnvironmentData(self._node.at("DefaultEnvironmentData"))
    @property
    def GroundedEnvironmentData(self):  # type: ()->HitWallEnvironmentData
        return HitWallEnvironmentData(self._node.at("GroundedEnvironmentData"))
    @property
    def HitWallFallHeightThreshold(self):  # type: ()->Float
        return Float(self._node.at("HitWallFallHeightThreshold"))
    @HitWallFallHeightThreshold.setter
    def HitWallFallHeightThreshold(self, val): self.HitWallFallHeightThreshold.set(val)
    @property
    def OrientationAlignementFactor(self):  # type: ()->Float
        return Float(self._node.at("OrientationAlignementFactor"))
    @OrientationAlignementFactor.setter
    def OrientationAlignementFactor(self, val): self.OrientationAlignementFactor.set(val)
    @property
    def RetimingHorizontalAngleMax(self):  # type: ()->Float
        return Float(self._node.at("RetimingHorizontalAngleMax"))
    @RetimingHorizontalAngleMax.setter
    def RetimingHorizontalAngleMax(self, val): self.RetimingHorizontalAngleMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




