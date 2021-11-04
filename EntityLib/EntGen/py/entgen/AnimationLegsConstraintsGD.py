
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimationLegsConstraints_SlopeOffsetInfo import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ScaleConverter import *
from entgen.Vector2 import *

from EntityLibPy import Node

class AnimationLegsConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationLegsConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationLegsConstraintsGD
        return AnimationLegsConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationLegsConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationLegsConstraintsGD
        return AnimationLegsConstraintsGD(entlib.make_node(AnimationLegsConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllowHeightMapCastFallback(self):  # type: ()->Bool
        return Bool(self._node.at("AllowHeightMapCastFallback"))
    @AllowHeightMapCastFallback.setter
    def AllowHeightMapCastFallback(self, val): self.AllowHeightMapCastFallback.set(val)
    @property
    def AscendingSlopeOffsetInfo(self):  # type: ()->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(self._node.at("AscendingSlopeOffsetInfo"))
    @property
    def BackLegsCompensateExtensionThreshold(self):  # type: ()->Float
        return Float(self._node.at("BackLegsCompensateExtensionThreshold"))
    @BackLegsCompensateExtensionThreshold.setter
    def BackLegsCompensateExtensionThreshold(self, val): self.BackLegsCompensateExtensionThreshold.set(val)
    @property
    def BackLegsHeightRangeForIKInfluence(self):  # type: ()->Vector2
        return Vector2(self._node.at("BackLegsHeightRangeForIKInfluence"))
    @BackLegsHeightRangeForIKInfluence.setter
    def BackLegsHeightRangeForIKInfluence(self, val): self.BackLegsHeightRangeForIKInfluence.set(val)
    @property
    def BoneBending(self):  # type: ()->Bool
        return Bool(self._node.at("BoneBending"))
    @BoneBending.setter
    def BoneBending(self, val): self.BoneBending.set(val)
    @property
    def BoneBendingAnticipation(self):  # type: ()->Float
        return Float(self._node.at("BoneBendingAnticipation"))
    @BoneBendingAnticipation.setter
    def BoneBendingAnticipation(self, val): self.BoneBendingAnticipation.set(val)
    @property
    def BoneBendingAnticipationBackward(self):  # type: ()->Float
        return Float(self._node.at("BoneBendingAnticipationBackward"))
    @BoneBendingAnticipationBackward.setter
    def BoneBendingAnticipationBackward(self, val): self.BoneBendingAnticipationBackward.set(val)
    @property
    def BoneBendingLocomotionInfluenceSpeed(self):  # type: ()->Float
        return Float(self._node.at("BoneBendingLocomotionInfluenceSpeed"))
    @BoneBendingLocomotionInfluenceSpeed.setter
    def BoneBendingLocomotionInfluenceSpeed(self, val): self.BoneBendingLocomotionInfluenceSpeed.set(val)
    @property
    def CastDeltaDistToTriggerSmooth(self):  # type: ()->Float
        return Float(self._node.at("CastDeltaDistToTriggerSmooth"))
    @CastDeltaDistToTriggerSmooth.setter
    def CastDeltaDistToTriggerSmooth(self, val): self.CastDeltaDistToTriggerSmooth.set(val)
    @property
    def DescendingSlopeOffsetInfo(self):  # type: ()->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(self._node.at("DescendingSlopeOffsetInfo"))
    @property
    def FeetInfluence(self):  # type: ()->Float
        return Float(self._node.at("FeetInfluence"))
    @FeetInfluence.setter
    def FeetInfluence(self, val): self.FeetInfluence.set(val)
    @property
    def FrontLegsCompensateExtensionThreshold(self):  # type: ()->Float
        return Float(self._node.at("FrontLegsCompensateExtensionThreshold"))
    @FrontLegsCompensateExtensionThreshold.setter
    def FrontLegsCompensateExtensionThreshold(self, val): self.FrontLegsCompensateExtensionThreshold.set(val)
    @property
    def FrontLegsHeightRangeForIKInfluence(self):  # type: ()->Vector2
        return Vector2(self._node.at("FrontLegsHeightRangeForIKInfluence"))
    @FrontLegsHeightRangeForIKInfluence.setter
    def FrontLegsHeightRangeForIKInfluence(self, val): self.FrontLegsHeightRangeForIKInfluence.set(val)
    @property
    def GlobalInfluence(self):  # type: ()->Float
        return Float(self._node.at("GlobalInfluence"))
    @GlobalInfluence.setter
    def GlobalInfluence(self, val): self.GlobalInfluence.set(val)
    @property
    def LegInfluence(self):  # type: ()->Float
        return Float(self._node.at("LegInfluence"))
    @LegInfluence.setter
    def LegInfluence(self, val): self.LegInfluence.set(val)
    @property
    def LegLock(self):  # type: ()->Bool
        return Bool(self._node.at("LegLock"))
    @LegLock.setter
    def LegLock(self, val): self.LegLock.set(val)
    @property
    def MaxHeightForFootInfluence(self):  # type: ()->Float
        return Float(self._node.at("MaxHeightForFootInfluence"))
    @MaxHeightForFootInfluence.setter
    def MaxHeightForFootInfluence(self, val): self.MaxHeightForFootInfluence.set(val)
    @property
    def ObstructionCastHitPosMarginOffsetFactor(self):  # type: ()->Float
        return Float(self._node.at("ObstructionCastHitPosMarginOffsetFactor"))
    @ObstructionCastHitPosMarginOffsetFactor.setter
    def ObstructionCastHitPosMarginOffsetFactor(self, val): self.ObstructionCastHitPosMarginOffsetFactor.set(val)
    @property
    def ObstructionCastOffsetFactor(self):  # type: ()->Float
        return Float(self._node.at("ObstructionCastOffsetFactor"))
    @ObstructionCastOffsetFactor.setter
    def ObstructionCastOffsetFactor(self, val): self.ObstructionCastOffsetFactor.set(val)
    @property
    def ObstructionCastSafeRadiusFactor(self):  # type: ()->Float
        return Float(self._node.at("ObstructionCastSafeRadiusFactor"))
    @ObstructionCastSafeRadiusFactor.setter
    def ObstructionCastSafeRadiusFactor(self, val): self.ObstructionCastSafeRadiusFactor.set(val)
    @property
    def SpeedFactorFromLockedRootDistance(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedFactorFromLockedRootDistance"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UseObstructionCast(self):  # type: ()->Bool
        return Bool(self._node.at("UseObstructionCast"))
    @UseObstructionCast.setter
    def UseObstructionCast(self, val): self.UseObstructionCast.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




