
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.AIContextSlot import *


class AIContextGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AIContextGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AIContextGD.schema_name))
    @property
    def FollowAccelerationCoeff(self): return Float(self._node.at("FollowAccelerationCoeff"))
    @FollowAccelerationCoeff.setter
    def FollowAccelerationCoeff(self, val): self.FollowAccelerationCoeff.set(val)
    @property
    def FollowCanStopMaxStateDuration(self): return Float(self._node.at("FollowCanStopMaxStateDuration"))
    @FollowCanStopMaxStateDuration.setter
    def FollowCanStopMaxStateDuration(self, val): self.FollowCanStopMaxStateDuration.set(val)
    @property
    def FollowCanStopMaxTimeInExpandedZone(self): return Float(self._node.at("FollowCanStopMaxTimeInExpandedZone"))
    @FollowCanStopMaxTimeInExpandedZone.setter
    def FollowCanStopMaxTimeInExpandedZone(self, val): self.FollowCanStopMaxTimeInExpandedZone.set(val)
    @property
    def FollowDecelerationCoeff(self): return Float(self._node.at("FollowDecelerationCoeff"))
    @FollowDecelerationCoeff.setter
    def FollowDecelerationCoeff(self, val): self.FollowDecelerationCoeff.set(val)
    @property
    def FollowDeltaAngleTarget(self): return Float(self._node.at("FollowDeltaAngleTarget"))
    @FollowDeltaAngleTarget.setter
    def FollowDeltaAngleTarget(self, val): self.FollowDeltaAngleTarget.set(val)
    @property
    def FollowHotspotRadius(self): return Float(self._node.at("FollowHotspotRadius"))
    @FollowHotspotRadius.setter
    def FollowHotspotRadius(self, val): self.FollowHotspotRadius.set(val)
    @property
    def FollowHotspotSpace(self): return Float(self._node.at("FollowHotspotSpace"))
    @FollowHotspotSpace.setter
    def FollowHotspotSpace(self, val): self.FollowHotspotSpace.set(val)
    @property
    def FollowRandomSpeedZoneInBeginCoeffMax(self): return Float(self._node.at("FollowRandomSpeedZoneInBeginCoeffMax"))
    @FollowRandomSpeedZoneInBeginCoeffMax.setter
    def FollowRandomSpeedZoneInBeginCoeffMax(self, val): self.FollowRandomSpeedZoneInBeginCoeffMax.set(val)
    @property
    def FollowRandomSpeedZoneInBeginCoeffMin(self): return Float(self._node.at("FollowRandomSpeedZoneInBeginCoeffMin"))
    @FollowRandomSpeedZoneInBeginCoeffMin.setter
    def FollowRandomSpeedZoneInBeginCoeffMin(self, val): self.FollowRandomSpeedZoneInBeginCoeffMin.set(val)
    @property
    def FollowRandomSpeedZoneInEndCoeffMax(self): return Float(self._node.at("FollowRandomSpeedZoneInEndCoeffMax"))
    @FollowRandomSpeedZoneInEndCoeffMax.setter
    def FollowRandomSpeedZoneInEndCoeffMax(self, val): self.FollowRandomSpeedZoneInEndCoeffMax.set(val)
    @property
    def FollowRandomSpeedZoneInEndCoeffMin(self): return Float(self._node.at("FollowRandomSpeedZoneInEndCoeffMin"))
    @FollowRandomSpeedZoneInEndCoeffMin.setter
    def FollowRandomSpeedZoneInEndCoeffMin(self, val): self.FollowRandomSpeedZoneInEndCoeffMin.set(val)
    @property
    def FollowRandomSynchroDelayMax(self): return Float(self._node.at("FollowRandomSynchroDelayMax"))
    @FollowRandomSynchroDelayMax.setter
    def FollowRandomSynchroDelayMax(self, val): self.FollowRandomSynchroDelayMax.set(val)
    @property
    def FollowRandomSynchroDelayMin(self): return Float(self._node.at("FollowRandomSynchroDelayMin"))
    @FollowRandomSynchroDelayMin.setter
    def FollowRandomSynchroDelayMin(self, val): self.FollowRandomSynchroDelayMin.set(val)
    @property
    def FollowSpeedChangeThreshold(self): return Float(self._node.at("FollowSpeedChangeThreshold"))
    @FollowSpeedChangeThreshold.setter
    def FollowSpeedChangeThreshold(self, val): self.FollowSpeedChangeThreshold.set(val)
    @property
    def FollowSpeedZoneInBegin(self): return Float(self._node.at("FollowSpeedZoneInBegin"))
    @FollowSpeedZoneInBegin.setter
    def FollowSpeedZoneInBegin(self, val): self.FollowSpeedZoneInBegin.set(val)
    @property
    def FollowSpeedZoneInEnd(self): return Float(self._node.at("FollowSpeedZoneInEnd"))
    @FollowSpeedZoneInEnd.setter
    def FollowSpeedZoneInEnd(self, val): self.FollowSpeedZoneInEnd.set(val)
    @property
    def FollowSpeedZoneOutEnd(self): return Float(self._node.at("FollowSpeedZoneOutEnd"))
    @FollowSpeedZoneOutEnd.setter
    def FollowSpeedZoneOutEnd(self, val): self.FollowSpeedZoneOutEnd.set(val)
    @property
    def FollowTargetDistRadiusFactor(self): return Float(self._node.at("FollowTargetDistRadiusFactor"))
    @FollowTargetDistRadiusFactor.setter
    def FollowTargetDistRadiusFactor(self, val): self.FollowTargetDistRadiusFactor.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackCircleRadius(self): return Float(self._node.at("attackCircleRadius"))
    @attackCircleRadius.setter
    def attackCircleRadius(self, val): self.attackCircleRadius.set(val)
    @property
    def distanceBetweenCreatures(self): return Float(self._node.at("distanceBetweenCreatures"))
    @distanceBetweenCreatures.setter
    def distanceBetweenCreatures(self, val): self.distanceBetweenCreatures.set(val)
    @property
    def distantReachCircleRadius(self): return Float(self._node.at("distantReachCircleRadius"))
    @distantReachCircleRadius.setter
    def distantReachCircleRadius(self, val): self.distantReachCircleRadius.set(val)
    @property
    def followCircleRadius(self): return Float(self._node.at("followCircleRadius"))
    @followCircleRadius.setter
    def followCircleRadius(self, val): self.followCircleRadius.set(val)
    @property
    def lockTargetCircleRadius(self): return Float(self._node.at("lockTargetCircleRadius"))
    @lockTargetCircleRadius.setter
    def lockTargetCircleRadius(self, val): self.lockTargetCircleRadius.set(val)
    @property
    def slots(self): return (lambda n: Array(AIContextSlot, n))(self._node.at("slots"))
    pass




