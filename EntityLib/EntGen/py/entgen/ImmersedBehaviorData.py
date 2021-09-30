
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *


class ImmersedBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ImmersedBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ImmersedBehaviorData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def depth(self): return Float(self._node.at("depth"))
    @depth.setter
    def depth(self, val): self.depth.set(val)
    @property
    def depthHysteresisCoeff(self): return Float(self._node.at("depthHysteresisCoeff"))
    @depthHysteresisCoeff.setter
    def depthHysteresisCoeff(self, val): self.depthHysteresisCoeff.set(val)
    @property
    def depthMaxRange(self): return ScaleConverter(self._node.at("depthMaxRange"))
    @property
    def flotation(self): return Float(self._node.at("flotation"))
    @flotation.setter
    def flotation(self, val): self.flotation.set(val)
    @property
    def isAllowed(self): return Bool(self._node.at("isAllowed"))
    @isAllowed.setter
    def isAllowed(self, val): self.isAllowed.set(val)
    @property
    def minTooDeepPushSpeed(self): return Float(self._node.at("minTooDeepPushSpeed"))
    @minTooDeepPushSpeed.setter
    def minTooDeepPushSpeed(self, val): self.minTooDeepPushSpeed.set(val)
    @property
    def reachSurfaceAccelerationCoeff(self): return Float(self._node.at("reachSurfaceAccelerationCoeff"))
    @reachSurfaceAccelerationCoeff.setter
    def reachSurfaceAccelerationCoeff(self, val): self.reachSurfaceAccelerationCoeff.set(val)
    pass




