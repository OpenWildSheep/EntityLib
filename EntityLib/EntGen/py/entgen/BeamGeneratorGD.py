
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *


class BeamGeneratorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BeamGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(BeamGeneratorGD.schema_name))
    @property
    def BonesStartPoints(self): return (lambda n: PrimArray(String, n))(self._node.at("BonesStartPoints"))
    @BonesStartPoints.setter
    def BonesStartPoints(self, val): self.BonesStartPoints.set(val)
    @property
    def ExtraDistanceBeyondTarget(self): return Float(self._node.at("ExtraDistanceBeyondTarget"))
    @ExtraDistanceBeyondTarget.setter
    def ExtraDistanceBeyondTarget(self, val): self.ExtraDistanceBeyondTarget.set(val)
    @property
    def LengthDuration(self): return Float(self._node.at("LengthDuration"))
    @LengthDuration.setter
    def LengthDuration(self, val): self.LengthDuration.set(val)
    @property
    def PathBeamEffect(self): return String(self._node.at("PathBeamEffect"))
    @PathBeamEffect.setter
    def PathBeamEffect(self, val): self.PathBeamEffect.set(val)
    @property
    def PointsPerBeam(self): return Int(self._node.at("PointsPerBeam"))
    @PointsPerBeam.setter
    def PointsPerBeam(self, val): self.PointsPerBeam.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




