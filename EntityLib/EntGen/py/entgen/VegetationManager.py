
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class VegetationManager(HelperObject):
    schema_name = "VegetationManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VegetationManager
        return VegetationManager(entlib.load_node_file(sourcefile, entlib.get_schema(VegetationManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VegetationManager
        return VegetationManager(entlib.make_node(VegetationManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BuryDepth(self):  # type: ()->Float
        return Float(self._node.at("BuryDepth"))
    @BuryDepth.setter
    def BuryDepth(self, val): self.BuryDepth.set(val)
    @property
    def BuryScaleThreshold(self):  # type: ()->Float
        return Float(self._node.at("BuryScaleThreshold"))
    @BuryScaleThreshold.setter
    def BuryScaleThreshold(self, val): self.BuryScaleThreshold.set(val)
    @property
    def BuryVeget(self):  # type: ()->Bool
        return Bool(self._node.at("BuryVeget"))
    @BuryVeget.setter
    def BuryVeget(self, val): self.BuryVeget.set(val)
    @property
    def FadeOutScaleThreshold(self):  # type: ()->Float
        return Float(self._node.at("FadeOutScaleThreshold"))
    @FadeOutScaleThreshold.setter
    def FadeOutScaleThreshold(self, val): self.FadeOutScaleThreshold.set(val)
    @property
    def FadeOutVeget(self):  # type: ()->Bool
        return Bool(self._node.at("FadeOutVeget"))
    @FadeOutVeget.setter
    def FadeOutVeget(self, val): self.FadeOutVeget.set(val)
    @property
    def FullScaleGrowDistanceHysteresis(self):  # type: ()->Float
        return Float(self._node.at("FullScaleGrowDistanceHysteresis"))
    @FullScaleGrowDistanceHysteresis.setter
    def FullScaleGrowDistanceHysteresis(self, val): self.FullScaleGrowDistanceHysteresis.set(val)
    @property
    def FullScaleGrowDistanceThreshold(self):  # type: ()->Float
        return Float(self._node.at("FullScaleGrowDistanceThreshold"))
    @FullScaleGrowDistanceThreshold.setter
    def FullScaleGrowDistanceThreshold(self, val): self.FullScaleGrowDistanceThreshold.set(val)
    @property
    def FullScaleGrowMaxRatio(self):  # type: ()->Float
        return Float(self._node.at("FullScaleGrowMaxRatio"))
    @FullScaleGrowMaxRatio.setter
    def FullScaleGrowMaxRatio(self, val): self.FullScaleGrowMaxRatio.set(val)
    @property
    def FullScaleGrowMinRatio(self):  # type: ()->Float
        return Float(self._node.at("FullScaleGrowMinRatio"))
    @FullScaleGrowMinRatio.setter
    def FullScaleGrowMinRatio(self, val): self.FullScaleGrowMinRatio.set(val)
    @property
    def GlobalDistanceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("GlobalDistanceMultiplier"))
    @GlobalDistanceMultiplier.setter
    def GlobalDistanceMultiplier(self, val): self.GlobalDistanceMultiplier.set(val)
    @property
    def RegenInterpolation(self):  # type: ()->Bool
        return Bool(self._node.at("RegenInterpolation"))
    @RegenInterpolation.setter
    def RegenInterpolation(self, val): self.RegenInterpolation.set(val)
    @property
    def ScaleSpeed(self):  # type: ()->Float
        return Float(self._node.at("ScaleSpeed"))
    @ScaleSpeed.setter
    def ScaleSpeed(self, val): self.ScaleSpeed.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def VegetationBankPath(self):  # type: ()->String
        return String(self._node.at("VegetationBankPath"))
    @VegetationBankPath.setter
    def VegetationBankPath(self, val): self.VegetationBankPath.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




