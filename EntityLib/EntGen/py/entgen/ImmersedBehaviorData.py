
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *
from entgen.ScaleConverter import *
from entgen.FluidType import *

from EntityLibPy import Node

class ImmersedBehaviorData(HelperObject):
    schema_name = "ImmersedBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ImmersedBehaviorData
        return ImmersedBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(ImmersedBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ImmersedBehaviorData
        return ImmersedBehaviorData(entlib.make_node(ImmersedBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def depth(self):  # type: ()->Float
        return Float(self._node.at("depth"))
    @depth.setter
    def depth(self, val): self.depth.set(val)
    @property
    def depthHysteresisCoeff(self):  # type: ()->Float
        return Float(self._node.at("depthHysteresisCoeff"))
    @depthHysteresisCoeff.setter
    def depthHysteresisCoeff(self, val): self.depthHysteresisCoeff.set(val)
    @property
    def depthMaxRange(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("depthMaxRange"))
    @property
    def flotation(self):  # type: ()->Float
        return Float(self._node.at("flotation"))
    @flotation.setter
    def flotation(self, val): self.flotation.set(val)
    @property
    def isAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("isAllowed"))
    @isAllowed.setter
    def isAllowed(self, val): self.isAllowed.set(val)
    @property
    def minTooDeepPushSpeed(self):  # type: ()->Float
        return Float(self._node.at("minTooDeepPushSpeed"))
    @minTooDeepPushSpeed.setter
    def minTooDeepPushSpeed(self, val): self.minTooDeepPushSpeed.set(val)
    @property
    def reachSurfaceAccelerationCoeff(self):  # type: ()->Float
        return Float(self._node.at("reachSurfaceAccelerationCoeff"))
    @reachSurfaceAccelerationCoeff.setter
    def reachSurfaceAccelerationCoeff(self, val): self.reachSurfaceAccelerationCoeff.set(val)
    @property
    def slowDowns(self):  # type: ()->Map[FluidTypeEnum, ScaleConverter]
        return (lambda n: Map(FluidTypeEnum, ScaleConverter, n))(self._node.at("slowDowns"))
    pass




