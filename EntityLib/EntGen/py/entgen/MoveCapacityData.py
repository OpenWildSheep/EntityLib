
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.MoveCapacityData_AnimTagTimelineTransitionTable import *
from entgen.MoveCapacityData_OrientationSpeed import *
from entgen.ScaleConverter import *
from entgen.Vector3 import *
from entgen.MoveCapacityData_ReachSpeed import *


class MoveCapacityData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def airControlFactor(self): return Float(self._node.at("airControlFactor"))
    @airControlFactor.setter
    def airControlFactor(self, val): self.airControlFactor.set(val)
    @property
    def allowClampSpeedBiggerThanLocomotionDuringBlend(self): return Bool(self._node.at("allowClampSpeedBiggerThanLocomotionDuringBlend"))
    @allowClampSpeedBiggerThanLocomotionDuringBlend.setter
    def allowClampSpeedBiggerThanLocomotionDuringBlend(self, val): self.allowClampSpeedBiggerThanLocomotionDuringBlend.set(val)
    @property
    def allowKeepAnimationPlayRatioUnclamped(self): return Bool(self._node.at("allowKeepAnimationPlayRatioUnclamped"))
    @allowKeepAnimationPlayRatioUnclamped.setter
    def allowKeepAnimationPlayRatioUnclamped(self, val): self.allowKeepAnimationPlayRatioUnclamped.set(val)
    @property
    def angularSpeedMaxFlyDumpFactor(self): return Float(self._node.at("angularSpeedMaxFlyDumpFactor"))
    @angularSpeedMaxFlyDumpFactor.setter
    def angularSpeedMaxFlyDumpFactor(self, val): self.angularSpeedMaxFlyDumpFactor.set(val)
    @property
    def angularSpeedMaxGroundDumpFactor(self): return Float(self._node.at("angularSpeedMaxGroundDumpFactor"))
    @angularSpeedMaxGroundDumpFactor.setter
    def angularSpeedMaxGroundDumpFactor(self, val): self.angularSpeedMaxGroundDumpFactor.set(val)
    @property
    def angularSpeedMaxRiderDumpFactor(self): return Float(self._node.at("angularSpeedMaxRiderDumpFactor"))
    @angularSpeedMaxRiderDumpFactor.setter
    def angularSpeedMaxRiderDumpFactor(self, val): self.angularSpeedMaxRiderDumpFactor.set(val)
    @property
    def angularSpeedMaxWaterDumpFactor(self): return Float(self._node.at("angularSpeedMaxWaterDumpFactor"))
    @angularSpeedMaxWaterDumpFactor.setter
    def angularSpeedMaxWaterDumpFactor(self, val): self.angularSpeedMaxWaterDumpFactor.set(val)
    @property
    def animTagTimelineTransitionTable(self): return MoveCapacityData_AnimTagTimelineTransitionTable(self._node.at("animTagTimelineTransitionTable"))
    @property
    def brakeDeceleration(self): return Float(self._node.at("brakeDeceleration"))
    @brakeDeceleration.setter
    def brakeDeceleration(self, val): self.brakeDeceleration.set(val)
    @property
    def capsuleBigRadius(self): return Float(self._node.at("capsuleBigRadius"))
    @capsuleBigRadius.setter
    def capsuleBigRadius(self, val): self.capsuleBigRadius.set(val)
    @property
    def capsuleEnormousRadius(self): return Float(self._node.at("capsuleEnormousRadius"))
    @capsuleEnormousRadius.setter
    def capsuleEnormousRadius(self, val): self.capsuleEnormousRadius.set(val)
    @property
    def capsuleMediumRadius(self): return Float(self._node.at("capsuleMediumRadius"))
    @capsuleMediumRadius.setter
    def capsuleMediumRadius(self, val): self.capsuleMediumRadius.set(val)
    @property
    def capsuleSmallRadius(self): return Float(self._node.at("capsuleSmallRadius"))
    @capsuleSmallRadius.setter
    def capsuleSmallRadius(self, val): self.capsuleSmallRadius.set(val)
    @property
    def capsuleTinyRadius(self): return Float(self._node.at("capsuleTinyRadius"))
    @capsuleTinyRadius.setter
    def capsuleTinyRadius(self, val): self.capsuleTinyRadius.set(val)
    @property
    def constraintDetectionAnticipation(self): return ScaleConverter(self._node.at("constraintDetectionAnticipation"))
    @property
    def constraintDetectionOffset(self): return Vector3(self._node.at("constraintDetectionOffset"))
    @constraintDetectionOffset.setter
    def constraintDetectionOffset(self, val): self.constraintDetectionOffset.set(val)
    @property
    def constraintDetectionRadius(self): return ScaleConverter(self._node.at("constraintDetectionRadius"))
    @property
    def coyoteJumpMaxTime(self): return Float(self._node.at("coyoteJumpMaxTime"))
    @coyoteJumpMaxTime.setter
    def coyoteJumpMaxTime(self, val): self.coyoteJumpMaxTime.set(val)
    @property
    def crashPreventionSafeguardFactor(self): return Float(self._node.at("crashPreventionSafeguardFactor"))
    @crashPreventionSafeguardFactor.setter
    def crashPreventionSafeguardFactor(self, val): self.crashPreventionSafeguardFactor.set(val)
    @property
    def doubleJump(self): return Bool(self._node.at("doubleJump"))
    @doubleJump.setter
    def doubleJump(self, val): self.doubleJump.set(val)
    @property
    def dropPlaneLegLenFactor(self): return ScaleConverter(self._node.at("dropPlaneLegLenFactor"))
    @property
    def dropSyncTrajectoryAndVisual(self): return Bool(self._node.at("dropSyncTrajectoryAndVisual"))
    @dropSyncTrajectoryAndVisual.setter
    def dropSyncTrajectoryAndVisual(self, val): self.dropSyncTrajectoryAndVisual.set(val)
    @property
    def ellipseCoeff(self): return Float(self._node.at("ellipseCoeff"))
    @ellipseCoeff.setter
    def ellipseCoeff(self, val): self.ellipseCoeff.set(val)
    @property
    def extirpateObstacleAcceleration(self): return ScaleConverter(self._node.at("extirpateObstacleAcceleration"))
    @property
    def extirpateObstacleDuration(self): return Float(self._node.at("extirpateObstacleDuration"))
    @extirpateObstacleDuration.setter
    def extirpateObstacleDuration(self, val): self.extirpateObstacleDuration.set(val)
    @property
    def flyCentrifugalCoeff(self): return ScaleConverter(self._node.at("flyCentrifugalCoeff"))
    @property
    def flyCentrifugalRate(self): return Float(self._node.at("flyCentrifugalRate"))
    @flyCentrifugalRate.setter
    def flyCentrifugalRate(self, val): self.flyCentrifugalRate.set(val)
    @property
    def jumpAnalogScale(self): return Float(self._node.at("jumpAnalogScale"))
    @jumpAnalogScale.setter
    def jumpAnalogScale(self, val): self.jumpAnalogScale.set(val)
    @property
    def jumpOntoPosition(self): return Bool(self._node.at("jumpOntoPosition"))
    @jumpOntoPosition.setter
    def jumpOntoPosition(self, val): self.jumpOntoPosition.set(val)
    @property
    def ledgeApproachSpeedMaxZ(self): return Float(self._node.at("ledgeApproachSpeedMaxZ"))
    @ledgeApproachSpeedMaxZ.setter
    def ledgeApproachSpeedMaxZ(self, val): self.ledgeApproachSpeedMaxZ.set(val)
    @property
    def ledgeDepthRadiusCoeff(self): return Float(self._node.at("ledgeDepthRadiusCoeff"))
    @ledgeDepthRadiusCoeff.setter
    def ledgeDepthRadiusCoeff(self, val): self.ledgeDepthRadiusCoeff.set(val)
    @property
    def ledgeMaxDistance(self): return Float(self._node.at("ledgeMaxDistance"))
    @ledgeMaxDistance.setter
    def ledgeMaxDistance(self, val): self.ledgeMaxDistance.set(val)
    @property
    def ledgeMaxHeightEpsilon(self): return Float(self._node.at("ledgeMaxHeightEpsilon"))
    @ledgeMaxHeightEpsilon.setter
    def ledgeMaxHeightEpsilon(self, val): self.ledgeMaxHeightEpsilon.set(val)
    @property
    def ledgeMinDepthEpsilon(self): return Float(self._node.at("ledgeMinDepthEpsilon"))
    @ledgeMinDepthEpsilon.setter
    def ledgeMinDepthEpsilon(self, val): self.ledgeMinDepthEpsilon.set(val)
    @property
    def ledgeMinWidthEpsilon(self): return Float(self._node.at("ledgeMinWidthEpsilon"))
    @ledgeMinWidthEpsilon.setter
    def ledgeMinWidthEpsilon(self, val): self.ledgeMinWidthEpsilon.set(val)
    @property
    def legLength(self): return Float(self._node.at("legLength"))
    @legLength.setter
    def legLength(self, val): self.legLength.set(val)
    @property
    def mass(self): return Float(self._node.at("mass"))
    @mass.setter
    def mass(self, val): self.mass.set(val)
    @property
    def maxAverageSpeedDuringJumpOnto(self): return Float(self._node.at("maxAverageSpeedDuringJumpOnto"))
    @maxAverageSpeedDuringJumpOnto.setter
    def maxAverageSpeedDuringJumpOnto(self, val): self.maxAverageSpeedDuringJumpOnto.set(val)
    @property
    def maxFlapTime(self): return Float(self._node.at("maxFlapTime"))
    @maxFlapTime.setter
    def maxFlapTime(self, val): self.maxFlapTime.set(val)
    @property
    def maxTimeBetweenFlaps(self): return Float(self._node.at("maxTimeBetweenFlaps"))
    @maxTimeBetweenFlaps.setter
    def maxTimeBetweenFlaps(self, val): self.maxTimeBetweenFlaps.set(val)
    @property
    def minFlapTime(self): return Float(self._node.at("minFlapTime"))
    @minFlapTime.setter
    def minFlapTime(self, val): self.minFlapTime.set(val)
    @property
    def minSpeedToSteerPitch(self): return Float(self._node.at("minSpeedToSteerPitch"))
    @minSpeedToSteerPitch.setter
    def minSpeedToSteerPitch(self, val): self.minSpeedToSteerPitch.set(val)
    @property
    def minTimeBetweenFlaps(self): return Float(self._node.at("minTimeBetweenFlaps"))
    @minTimeBetweenFlaps.setter
    def minTimeBetweenFlaps(self, val): self.minTimeBetweenFlaps.set(val)
    @property
    def orientationSpeedFly(self): return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedFly"))
    @property
    def orientationSpeedGround(self): return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedGround"))
    @property
    def orientationSpeedWater(self): return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedWater"))
    @property
    def patinateSpeedMinEnter(self): return Float(self._node.at("patinateSpeedMinEnter"))
    @patinateSpeedMinEnter.setter
    def patinateSpeedMinEnter(self, val): self.patinateSpeedMinEnter.set(val)
    @property
    def patinateSpeedMinExit(self): return Float(self._node.at("patinateSpeedMinExit"))
    @patinateSpeedMinExit.setter
    def patinateSpeedMinExit(self, val): self.patinateSpeedMinExit.set(val)
    @property
    def reachSpeedAcceleration(self): return Float(self._node.at("reachSpeedAcceleration"))
    @reachSpeedAcceleration.setter
    def reachSpeedAcceleration(self, val): self.reachSpeedAcceleration.set(val)
    @property
    def reachSpeedByLocomotion(self): return (lambda n: Array(MoveCapacityData_ReachSpeed, n))(self._node.at("reachSpeedByLocomotion"))
    @property
    def reachSpeedDeceleration(self): return Float(self._node.at("reachSpeedDeceleration"))
    @reachSpeedDeceleration.setter
    def reachSpeedDeceleration(self, val): self.reachSpeedDeceleration.set(val)
    @property
    def reactToOtherCharacterBodyCollision(self): return Bool(self._node.at("reactToOtherCharacterBodyCollision"))
    @reactToOtherCharacterBodyCollision.setter
    def reactToOtherCharacterBodyCollision(self, val): self.reactToOtherCharacterBodyCollision.set(val)
    @property
    def sphereCastRadiusRatio(self): return Float(self._node.at("sphereCastRadiusRatio"))
    @sphereCastRadiusRatio.setter
    def sphereCastRadiusRatio(self, val): self.sphereCastRadiusRatio.set(val)
    @property
    def sphereOverrideRadius(self): return Float(self._node.at("sphereOverrideRadius"))
    @sphereOverrideRadius.setter
    def sphereOverrideRadius(self, val): self.sphereOverrideRadius.set(val)
    @property
    def strafeBlendIn(self): return Float(self._node.at("strafeBlendIn"))
    @strafeBlendIn.setter
    def strafeBlendIn(self, val): self.strafeBlendIn.set(val)
    @property
    def strafeBlendWeightMinToChangeAnim(self): return Float(self._node.at("strafeBlendWeightMinToChangeAnim"))
    @strafeBlendWeightMinToChangeAnim.setter
    def strafeBlendWeightMinToChangeAnim(self, val): self.strafeBlendWeightMinToChangeAnim.set(val)
    @property
    def strafeOrientationRateFactor(self): return Float(self._node.at("strafeOrientationRateFactor"))
    @strafeOrientationRateFactor.setter
    def strafeOrientationRateFactor(self, val): self.strafeOrientationRateFactor.set(val)
    @property
    def strafeSpeedModeMax(self): return SpeedMode(self._node.at("strafeSpeedModeMax"))
    @strafeSpeedModeMax.setter
    def strafeSpeedModeMax(self, val): self.strafeSpeedModeMax.set(val)
    @property
    def strafeStopOrientationRateFactor(self): return Float(self._node.at("strafeStopOrientationRateFactor"))
    @strafeStopOrientationRateFactor.setter
    def strafeStopOrientationRateFactor(self, val): self.strafeStopOrientationRateFactor.set(val)
    @property
    def strafeTurnAngleMin(self): return Float(self._node.at("strafeTurnAngleMin"))
    @strafeTurnAngleMin.setter
    def strafeTurnAngleMin(self, val): self.strafeTurnAngleMin.set(val)
    @property
    def trajectoryRateFactorDuringLateralLand(self): return Float(self._node.at("trajectoryRateFactorDuringLateralLand"))
    @trajectoryRateFactorDuringLateralLand.setter
    def trajectoryRateFactorDuringLateralLand(self, val): self.trajectoryRateFactorDuringLateralLand.set(val)
    @property
    def turnAroundInputDirectionAngleDeltaMin(self): return Float(self._node.at("turnAroundInputDirectionAngleDeltaMin"))
    @turnAroundInputDirectionAngleDeltaMin.setter
    def turnAroundInputDirectionAngleDeltaMin(self, val): self.turnAroundInputDirectionAngleDeltaMin.set(val)
    pass




