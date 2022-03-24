
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *
from entgen.GroupAvoidanceEnum import *
from entgen.Size import *

from EntityLibPy import Node

class VelocityObstaclesManager(HelperObject):
    schema_name = "VelocityObstaclesManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VelocityObstaclesManager
        return VelocityObstaclesManager(entlib.load_node_file(sourcefile, entlib.get_schema(VelocityObstaclesManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VelocityObstaclesManager
        return VelocityObstaclesManager(entlib.make_node(VelocityObstaclesManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AcceptableAccelerationForAvoidance(self):  # type: ()->Float
        return Float(self._node.at("AcceptableAccelerationForAvoidance"))
    @AcceptableAccelerationForAvoidance.setter
    def AcceptableAccelerationForAvoidance(self, val): self.AcceptableAccelerationForAvoidance.set(val)
    @property
    def Active(self):  # type: ()->Bool
        return Bool(self._node.at("Active"))
    @Active.setter
    def Active(self, val): self.Active.set(val)
    @property
    def AvoidanceRadiusAdaptabilityFactor(self):  # type: ()->Float
        return Float(self._node.at("AvoidanceRadiusAdaptabilityFactor"))
    @AvoidanceRadiusAdaptabilityFactor.setter
    def AvoidanceRadiusAdaptabilityFactor(self, val): self.AvoidanceRadiusAdaptabilityFactor.set(val)
    @property
    def GroupsAvoidanceIgnoredBySize(self):  # type: ()->Map[SizeEnum, PrimArray[GroupAvoidanceEnum]]
        return (lambda n: Map(SizeEnum, (lambda n: PrimArray(GroupAvoidanceEnum, n)), n))(self._node.at("GroupsAvoidanceIgnoredBySize"))
    @property
    def RunningSpeed(self):  # type: ()->Float
        return Float(self._node.at("RunningSpeed"))
    @RunningSpeed.setter
    def RunningSpeed(self, val): self.RunningSpeed.set(val)
    @property
    def SimMaxNeighbors(self):  # type: ()->Int
        return Int(self._node.at("SimMaxNeighbors"))
    @SimMaxNeighbors.setter
    def SimMaxNeighbors(self, val): self.SimMaxNeighbors.set(val)
    @property
    def SimMaxSpeed(self):  # type: ()->Float
        return Float(self._node.at("SimMaxSpeed"))
    @SimMaxSpeed.setter
    def SimMaxSpeed(self, val): self.SimMaxSpeed.set(val)
    @property
    def SimNeighborDist(self):  # type: ()->Float
        return Float(self._node.at("SimNeighborDist"))
    @SimNeighborDist.setter
    def SimNeighborDist(self, val): self.SimNeighborDist.set(val)
    @property
    def SimPrefSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("SimPrefSpeedFactor"))
    @SimPrefSpeedFactor.setter
    def SimPrefSpeedFactor(self, val): self.SimPrefSpeedFactor.set(val)
    @property
    def SimRadius(self):  # type: ()->Float
        return Float(self._node.at("SimRadius"))
    @SimRadius.setter
    def SimRadius(self, val): self.SimRadius.set(val)
    @property
    def SimSlowDownWhenAvoiding(self):  # type: ()->Int
        return Int(self._node.at("SimSlowDownWhenAvoiding"))
    @SimSlowDownWhenAvoiding.setter
    def SimSlowDownWhenAvoiding(self, val): self.SimSlowDownWhenAvoiding.set(val)
    @property
    def SimTimeHorizon(self):  # type: ()->Float
        return Float(self._node.at("SimTimeHorizon"))
    @SimTimeHorizon.setter
    def SimTimeHorizon(self, val): self.SimTimeHorizon.set(val)
    @property
    def SimTimeHorizonObst(self):  # type: ()->Float
        return Float(self._node.at("SimTimeHorizonObst"))
    @SimTimeHorizonObst.setter
    def SimTimeHorizonObst(self, val): self.SimTimeHorizonObst.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def WalkingSpeed(self):  # type: ()->Float
        return Float(self._node.at("WalkingSpeed"))
    @WalkingSpeed.setter
    def WalkingSpeed(self, val): self.WalkingSpeed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




