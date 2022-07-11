
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ClimbEdgeData_LedgeData(HelperObject):
    schema_name = "ClimbEdgeData::LedgeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClimbEdgeData_LedgeData
        return ClimbEdgeData_LedgeData(entlib.load_node_file(sourcefile, entlib.get_schema(ClimbEdgeData_LedgeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClimbEdgeData_LedgeData
        return ClimbEdgeData_LedgeData(entlib.make_node(ClimbEdgeData_LedgeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def ledgeApproachSpeedMaxZ(self):  # type: ()->Float
        return Float(self._node.at("ledgeApproachSpeedMaxZ"))
    @ledgeApproachSpeedMaxZ.setter
    def ledgeApproachSpeedMaxZ(self, val): self.ledgeApproachSpeedMaxZ.set(val)
    @property
    def ledgeDepthRadiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("ledgeDepthRadiusCoeff"))
    @ledgeDepthRadiusCoeff.setter
    def ledgeDepthRadiusCoeff(self, val): self.ledgeDepthRadiusCoeff.set(val)
    @property
    def ledgeDetectionOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("ledgeDetectionOffset"))
    @ledgeDetectionOffset.setter
    def ledgeDetectionOffset(self, val): self.ledgeDetectionOffset.set(val)
    @property
    def ledgeDetectionRadiusMultiplier(self):  # type: ()->Float
        return Float(self._node.at("ledgeDetectionRadiusMultiplier"))
    @ledgeDetectionRadiusMultiplier.setter
    def ledgeDetectionRadiusMultiplier(self, val): self.ledgeDetectionRadiusMultiplier.set(val)
    @property
    def ledgeMaxDistance(self):  # type: ()->Float
        return Float(self._node.at("ledgeMaxDistance"))
    @ledgeMaxDistance.setter
    def ledgeMaxDistance(self, val): self.ledgeMaxDistance.set(val)
    @property
    def ledgeMaxHeightEpsilon(self):  # type: ()->Float
        return Float(self._node.at("ledgeMaxHeightEpsilon"))
    @ledgeMaxHeightEpsilon.setter
    def ledgeMaxHeightEpsilon(self, val): self.ledgeMaxHeightEpsilon.set(val)
    @property
    def ledgeMinDepthEpsilon(self):  # type: ()->Float
        return Float(self._node.at("ledgeMinDepthEpsilon"))
    @ledgeMinDepthEpsilon.setter
    def ledgeMinDepthEpsilon(self, val): self.ledgeMinDepthEpsilon.set(val)
    @property
    def ledgeMinWidthEpsilon(self):  # type: ()->Float
        return Float(self._node.at("ledgeMinWidthEpsilon"))
    @ledgeMinWidthEpsilon.setter
    def ledgeMinWidthEpsilon(self, val): self.ledgeMinWidthEpsilon.set(val)
    pass




