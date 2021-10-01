
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.AIContextSlot import *

from EntityLibPy import Node

class AIContextGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AIContextGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIContextGD
        return AIContextGD(entlib.load_node_file(sourcefile, entlib.get_schema(AIContextGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIContextGD
        return AIContextGD(entlib.make_node(AIContextGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FollowAccelerationCoeff(self):  # type: ()->Float
        return Float(self._node.at("FollowAccelerationCoeff"))
    @FollowAccelerationCoeff.setter
    def FollowAccelerationCoeff(self, val): self.FollowAccelerationCoeff.set(val)
    @property
    def FollowCanStopMaxStateDuration(self):  # type: ()->Float
        return Float(self._node.at("FollowCanStopMaxStateDuration"))
    @FollowCanStopMaxStateDuration.setter
    def FollowCanStopMaxStateDuration(self, val): self.FollowCanStopMaxStateDuration.set(val)
    @property
    def FollowCanStopMaxTimeInExpandedZone(self):  # type: ()->Float
        return Float(self._node.at("FollowCanStopMaxTimeInExpandedZone"))
    @FollowCanStopMaxTimeInExpandedZone.setter
    def FollowCanStopMaxTimeInExpandedZone(self, val): self.FollowCanStopMaxTimeInExpandedZone.set(val)
    @property
    def FollowDecelerationCoeff(self):  # type: ()->Float
        return Float(self._node.at("FollowDecelerationCoeff"))
    @FollowDecelerationCoeff.setter
    def FollowDecelerationCoeff(self, val): self.FollowDecelerationCoeff.set(val)
    @property
    def FollowDeltaAngleTarget(self):  # type: ()->Float
        return Float(self._node.at("FollowDeltaAngleTarget"))
    @FollowDeltaAngleTarget.setter
    def FollowDeltaAngleTarget(self, val): self.FollowDeltaAngleTarget.set(val)
    @property
    def FollowHotspotRadius(self):  # type: ()->Float
        return Float(self._node.at("FollowHotspotRadius"))
    @FollowHotspotRadius.setter
    def FollowHotspotRadius(self, val): self.FollowHotspotRadius.set(val)
    @property
    def FollowHotspotSpace(self):  # type: ()->Float
        return Float(self._node.at("FollowHotspotSpace"))
    @FollowHotspotSpace.setter
    def FollowHotspotSpace(self, val): self.FollowHotspotSpace.set(val)
    @property
    def FollowRandomSpeedZoneInBeginCoeffMax(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInBeginCoeffMax"))
    @FollowRandomSpeedZoneInBeginCoeffMax.setter
    def FollowRandomSpeedZoneInBeginCoeffMax(self, val): self.FollowRandomSpeedZoneInBeginCoeffMax.set(val)
    @property
    def FollowRandomSpeedZoneInBeginCoeffMin(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInBeginCoeffMin"))
    @FollowRandomSpeedZoneInBeginCoeffMin.setter
    def FollowRandomSpeedZoneInBeginCoeffMin(self, val): self.FollowRandomSpeedZoneInBeginCoeffMin.set(val)
    @property
    def FollowRandomSpeedZoneInEndCoeffMax(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInEndCoeffMax"))
    @FollowRandomSpeedZoneInEndCoeffMax.setter
    def FollowRandomSpeedZoneInEndCoeffMax(self, val): self.FollowRandomSpeedZoneInEndCoeffMax.set(val)
    @property
    def FollowRandomSpeedZoneInEndCoeffMin(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInEndCoeffMin"))
    @FollowRandomSpeedZoneInEndCoeffMin.setter
    def FollowRandomSpeedZoneInEndCoeffMin(self, val): self.FollowRandomSpeedZoneInEndCoeffMin.set(val)
    @property
    def FollowRandomSynchroDelayMax(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSynchroDelayMax"))
    @FollowRandomSynchroDelayMax.setter
    def FollowRandomSynchroDelayMax(self, val): self.FollowRandomSynchroDelayMax.set(val)
    @property
    def FollowRandomSynchroDelayMin(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSynchroDelayMin"))
    @FollowRandomSynchroDelayMin.setter
    def FollowRandomSynchroDelayMin(self, val): self.FollowRandomSynchroDelayMin.set(val)
    @property
    def FollowSpeedChangeThreshold(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedChangeThreshold"))
    @FollowSpeedChangeThreshold.setter
    def FollowSpeedChangeThreshold(self, val): self.FollowSpeedChangeThreshold.set(val)
    @property
    def FollowSpeedZoneInBegin(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedZoneInBegin"))
    @FollowSpeedZoneInBegin.setter
    def FollowSpeedZoneInBegin(self, val): self.FollowSpeedZoneInBegin.set(val)
    @property
    def FollowSpeedZoneInEnd(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedZoneInEnd"))
    @FollowSpeedZoneInEnd.setter
    def FollowSpeedZoneInEnd(self, val): self.FollowSpeedZoneInEnd.set(val)
    @property
    def FollowSpeedZoneOutEnd(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedZoneOutEnd"))
    @FollowSpeedZoneOutEnd.setter
    def FollowSpeedZoneOutEnd(self, val): self.FollowSpeedZoneOutEnd.set(val)
    @property
    def FollowTargetDistRadiusFactor(self):  # type: ()->Float
        return Float(self._node.at("FollowTargetDistRadiusFactor"))
    @FollowTargetDistRadiusFactor.setter
    def FollowTargetDistRadiusFactor(self, val): self.FollowTargetDistRadiusFactor.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("attackCircleRadius"))
    @attackCircleRadius.setter
    def attackCircleRadius(self, val): self.attackCircleRadius.set(val)
    @property
    def distanceBetweenCreatures(self):  # type: ()->Float
        return Float(self._node.at("distanceBetweenCreatures"))
    @distanceBetweenCreatures.setter
    def distanceBetweenCreatures(self, val): self.distanceBetweenCreatures.set(val)
    @property
    def distantReachCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("distantReachCircleRadius"))
    @distantReachCircleRadius.setter
    def distantReachCircleRadius(self, val): self.distantReachCircleRadius.set(val)
    @property
    def followCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("followCircleRadius"))
    @followCircleRadius.setter
    def followCircleRadius(self, val): self.followCircleRadius.set(val)
    @property
    def lockTargetCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("lockTargetCircleRadius"))
    @lockTargetCircleRadius.setter
    def lockTargetCircleRadius(self, val): self.lockTargetCircleRadius.set(val)
    @property
    def slots(self):  # type: ()->Array[AIContextSlot]
        return (lambda n: Array(AIContextSlot, n))(self._node.at("slots"))
    pass




