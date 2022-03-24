
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class BeamGeneratorGD(HelperObject):
    schema_name = "BeamGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamGeneratorGD
        return BeamGeneratorGD(entlib.load_node_file(sourcefile, entlib.get_schema(BeamGeneratorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamGeneratorGD
        return BeamGeneratorGD(entlib.make_node(BeamGeneratorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BonesStartPoints(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BonesStartPoints"))
    @BonesStartPoints.setter
    def BonesStartPoints(self, val): self.BonesStartPoints.set(val)
    @property
    def ExtraDistanceBeyondTarget(self):  # type: ()->Float
        return Float(self._node.at("ExtraDistanceBeyondTarget"))
    @ExtraDistanceBeyondTarget.setter
    def ExtraDistanceBeyondTarget(self, val): self.ExtraDistanceBeyondTarget.set(val)
    @property
    def LengthDuration(self):  # type: ()->Float
        return Float(self._node.at("LengthDuration"))
    @LengthDuration.setter
    def LengthDuration(self, val): self.LengthDuration.set(val)
    @property
    def PathBeamEffect(self):  # type: ()->String
        return String(self._node.at("PathBeamEffect"))
    @PathBeamEffect.setter
    def PathBeamEffect(self, val): self.PathBeamEffect.set(val)
    @property
    def PointsPerBeam(self):  # type: ()->Int
        return Int(self._node.at("PointsPerBeam"))
    @PointsPerBeam.setter
    def PointsPerBeam(self, val): self.PointsPerBeam.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




