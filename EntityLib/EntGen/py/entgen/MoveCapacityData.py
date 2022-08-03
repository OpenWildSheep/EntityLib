
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.MoveCapacityData_AnimTagTimelineTransitionTable import *
from entgen.MoveCapacityData_OrientationSpeed import *
from entgen.MoveCapacityData_TurnJump import *
from entgen.ScaleConverter import *
from entgen.Vector3 import *
from entgen.MoveCapacityData_ReachSpeed import *

from EntityLibPy import Node

class MoveCapacityData(HelperObject):
    schema_name = "MoveCapacityData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData
        return MoveCapacityData(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData
        return MoveCapacityData(entlib.make_node(MoveCapacityData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def airControlFactor(self):  # type: ()->Float
        return Float(self._node.at("airControlFactor"))
    @airControlFactor.setter
    def airControlFactor(self, val): self.airControlFactor.set(val)
    @property
    def allowClampSpeedBiggerThanLocomotionDuringBlend(self):  # type: ()->Bool
        return Bool(self._node.at("allowClampSpeedBiggerThanLocomotionDuringBlend"))
    @allowClampSpeedBiggerThanLocomotionDuringBlend.setter
    def allowClampSpeedBiggerThanLocomotionDuringBlend(self, val): self.allowClampSpeedBiggerThanLocomotionDuringBlend.set(val)
    @property
    def allowKeepAnimationPlayRatioUnclamped(self):  # type: ()->Bool
        return Bool(self._node.at("allowKeepAnimationPlayRatioUnclamped"))
    @allowKeepAnimationPlayRatioUnclamped.setter
    def allowKeepAnimationPlayRatioUnclamped(self, val): self.allowKeepAnimationPlayRatioUnclamped.set(val)
    @property
    def angularSpeedMaxFlyDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxFlyDumpFactor"))
    @angularSpeedMaxFlyDumpFactor.setter
    def angularSpeedMaxFlyDumpFactor(self, val): self.angularSpeedMaxFlyDumpFactor.set(val)
    @property
    def angularSpeedMaxGroundDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxGroundDumpFactor"))
    @angularSpeedMaxGroundDumpFactor.setter
    def angularSpeedMaxGroundDumpFactor(self, val): self.angularSpeedMaxGroundDumpFactor.set(val)
    @property
    def angularSpeedMaxRiderDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxRiderDumpFactor"))
    @angularSpeedMaxRiderDumpFactor.setter
    def angularSpeedMaxRiderDumpFactor(self, val): self.angularSpeedMaxRiderDumpFactor.set(val)
    @property
    def angularSpeedMaxWaterDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxWaterDumpFactor"))
    @angularSpeedMaxWaterDumpFactor.setter
    def angularSpeedMaxWaterDumpFactor(self, val): self.angularSpeedMaxWaterDumpFactor.set(val)
    @property
    def animTagTimelineTransitionTable(self):  # type: ()->MoveCapacityData_AnimTagTimelineTransitionTable
        return MoveCapacityData_AnimTagTimelineTransitionTable(self._node.at("animTagTimelineTransitionTable"))
    @property
    def brakeDeceleration(self):  # type: ()->Float
        return Float(self._node.at("brakeDeceleration"))
    @brakeDeceleration.setter
    def brakeDeceleration(self, val): self.brakeDeceleration.set(val)
    @property
    def canSpiritAttack(self):  # type: ()->Bool
        return Bool(self._node.at("canSpiritAttack"))
    @canSpiritAttack.setter
    def canSpiritAttack(self, val): self.canSpiritAttack.set(val)
    @property
    def canUseCliffGrip(self):  # type: ()->Bool
        return Bool(self._node.at("canUseCliffGrip"))
    @canUseCliffGrip.setter
    def canUseCliffGrip(self, val): self.canUseCliffGrip.set(val)
    @property
    def capsuleBigRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleBigRadius"))
    @capsuleBigRadius.setter
    def capsuleBigRadius(self, val): self.capsuleBigRadius.set(val)
    @property
    def capsuleEnormousRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleEnormousRadius"))
    @capsuleEnormousRadius.setter
    def capsuleEnormousRadius(self, val): self.capsuleEnormousRadius.set(val)
    @property
    def capsuleMediumRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleMediumRadius"))
    @capsuleMediumRadius.setter
    def capsuleMediumRadius(self, val): self.capsuleMediumRadius.set(val)
    @property
    def capsuleSmallRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleSmallRadius"))
    @capsuleSmallRadius.setter
    def capsuleSmallRadius(self, val): self.capsuleSmallRadius.set(val)
    @property
    def capsuleTinyRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleTinyRadius"))
    @capsuleTinyRadius.setter
    def capsuleTinyRadius(self, val): self.capsuleTinyRadius.set(val)
    @property
    def constraintDetectionAnticipation(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("constraintDetectionAnticipation"))
    @property
    def constraintDetectionOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("constraintDetectionOffset"))
    @constraintDetectionOffset.setter
    def constraintDetectionOffset(self, val): self.constraintDetectionOffset.set(val)
    @property
    def constraintDetectionRadiusMultiplier(self):  # type: ()->Float
        return Float(self._node.at("constraintDetectionRadiusMultiplier"))
    @constraintDetectionRadiusMultiplier.setter
    def constraintDetectionRadiusMultiplier(self, val): self.constraintDetectionRadiusMultiplier.set(val)
    @property
    def coyoteJumpMaxTime(self):  # type: ()->Float
        return Float(self._node.at("coyoteJumpMaxTime"))
    @coyoteJumpMaxTime.setter
    def coyoteJumpMaxTime(self, val): self.coyoteJumpMaxTime.set(val)
    @property
    def crashPreventionSafeguardFactor(self):  # type: ()->Float
        return Float(self._node.at("crashPreventionSafeguardFactor"))
    @crashPreventionSafeguardFactor.setter
    def crashPreventionSafeguardFactor(self, val): self.crashPreventionSafeguardFactor.set(val)
    @property
    def defaultWorldUpSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("defaultWorldUpSpeedFactor"))
    @defaultWorldUpSpeedFactor.setter
    def defaultWorldUpSpeedFactor(self, val): self.defaultWorldUpSpeedFactor.set(val)
    @property
    def dodgeCooldownTime(self):  # type: ()->Float
        return Float(self._node.at("dodgeCooldownTime"))
    @dodgeCooldownTime.setter
    def dodgeCooldownTime(self, val): self.dodgeCooldownTime.set(val)
    @property
    def doubleJump(self):  # type: ()->Bool
        return Bool(self._node.at("doubleJump"))
    @doubleJump.setter
    def doubleJump(self, val): self.doubleJump.set(val)
    @property
    def dropPlaneLegLenFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("dropPlaneLegLenFactor"))
    @property
    def dropSyncTrajectoryAndVisual(self):  # type: ()->Bool
        return Bool(self._node.at("dropSyncTrajectoryAndVisual"))
    @dropSyncTrajectoryAndVisual.setter
    def dropSyncTrajectoryAndVisual(self, val): self.dropSyncTrajectoryAndVisual.set(val)
    @property
    def ellipseCoeff(self):  # type: ()->Float
        return Float(self._node.at("ellipseCoeff"))
    @ellipseCoeff.setter
    def ellipseCoeff(self, val): self.ellipseCoeff.set(val)
    @property
    def extirpateObstacleAcceleration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("extirpateObstacleAcceleration"))
    @property
    def extirpateObstacleDuration(self):  # type: ()->Float
        return Float(self._node.at("extirpateObstacleDuration"))
    @extirpateObstacleDuration.setter
    def extirpateObstacleDuration(self, val): self.extirpateObstacleDuration.set(val)
    @property
    def flyCentrifugalCoeff(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("flyCentrifugalCoeff"))
    @property
    def flyCentrifugalRate(self):  # type: ()->Float
        return Float(self._node.at("flyCentrifugalRate"))
    @flyCentrifugalRate.setter
    def flyCentrifugalRate(self, val): self.flyCentrifugalRate.set(val)
    @property
    def jumpAnalogScale(self):  # type: ()->Float
        return Float(self._node.at("jumpAnalogScale"))
    @jumpAnalogScale.setter
    def jumpAnalogScale(self, val): self.jumpAnalogScale.set(val)
    @property
    def jumpOntoPosition(self):  # type: ()->Bool
        return Bool(self._node.at("jumpOntoPosition"))
    @jumpOntoPosition.setter
    def jumpOntoPosition(self, val): self.jumpOntoPosition.set(val)
    @property
    def legLength(self):  # type: ()->Float
        return Float(self._node.at("legLength"))
    @legLength.setter
    def legLength(self, val): self.legLength.set(val)
    @property
    def mass(self):  # type: ()->Float
        return Float(self._node.at("mass"))
    @mass.setter
    def mass(self, val): self.mass.set(val)
    @property
    def maxAverageSpeedDuringJumpOnto(self):  # type: ()->Float
        return Float(self._node.at("maxAverageSpeedDuringJumpOnto"))
    @maxAverageSpeedDuringJumpOnto.setter
    def maxAverageSpeedDuringJumpOnto(self, val): self.maxAverageSpeedDuringJumpOnto.set(val)
    @property
    def maxFlapTime(self):  # type: ()->Float
        return Float(self._node.at("maxFlapTime"))
    @maxFlapTime.setter
    def maxFlapTime(self, val): self.maxFlapTime.set(val)
    @property
    def maxTimeBetweenFlaps(self):  # type: ()->Float
        return Float(self._node.at("maxTimeBetweenFlaps"))
    @maxTimeBetweenFlaps.setter
    def maxTimeBetweenFlaps(self, val): self.maxTimeBetweenFlaps.set(val)
    @property
    def maxUnmountRetimingDist(self):  # type: ()->Float
        return Float(self._node.at("maxUnmountRetimingDist"))
    @maxUnmountRetimingDist.setter
    def maxUnmountRetimingDist(self, val): self.maxUnmountRetimingDist.set(val)
    @property
    def minFlapTime(self):  # type: ()->Float
        return Float(self._node.at("minFlapTime"))
    @minFlapTime.setter
    def minFlapTime(self, val): self.minFlapTime.set(val)
    @property
    def minSpeedToSteerPitch(self):  # type: ()->Float
        return Float(self._node.at("minSpeedToSteerPitch"))
    @minSpeedToSteerPitch.setter
    def minSpeedToSteerPitch(self, val): self.minSpeedToSteerPitch.set(val)
    @property
    def minTimeBetweenFlaps(self):  # type: ()->Float
        return Float(self._node.at("minTimeBetweenFlaps"))
    @minTimeBetweenFlaps.setter
    def minTimeBetweenFlaps(self, val): self.minTimeBetweenFlaps.set(val)
    @property
    def minimumDropTimeBeforeAClimbEdge(self):  # type: ()->Float
        return Float(self._node.at("minimumDropTimeBeforeAClimbEdge"))
    @minimumDropTimeBeforeAClimbEdge.setter
    def minimumDropTimeBeforeAClimbEdge(self, val): self.minimumDropTimeBeforeAClimbEdge.set(val)
    @property
    def nbAttackJump(self):  # type: ()->Int
        return Int(self._node.at("nbAttackJump"))
    @nbAttackJump.setter
    def nbAttackJump(self, val): self.nbAttackJump.set(val)
    @property
    def orientationSpeedFly(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedFly"))
    @property
    def orientationSpeedGround(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedGround"))
    @property
    def orientationSpeedWater(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedWater"))
    @property
    def patinateSpeedMinEnter(self):  # type: ()->Float
        return Float(self._node.at("patinateSpeedMinEnter"))
    @patinateSpeedMinEnter.setter
    def patinateSpeedMinEnter(self, val): self.patinateSpeedMinEnter.set(val)
    @property
    def patinateSpeedMinExit(self):  # type: ()->Float
        return Float(self._node.at("patinateSpeedMinExit"))
    @patinateSpeedMinExit.setter
    def patinateSpeedMinExit(self, val): self.patinateSpeedMinExit.set(val)
    @property
    def reachSpeedAcceleration(self):  # type: ()->Float
        return Float(self._node.at("reachSpeedAcceleration"))
    @reachSpeedAcceleration.setter
    def reachSpeedAcceleration(self, val): self.reachSpeedAcceleration.set(val)
    @property
    def reachSpeedByLocomotion(self):  # type: ()->Array[MoveCapacityData_ReachSpeed]
        return (lambda n: Array(MoveCapacityData_ReachSpeed, n))(self._node.at("reachSpeedByLocomotion"))
    @property
    def reachSpeedDeceleration(self):  # type: ()->Float
        return Float(self._node.at("reachSpeedDeceleration"))
    @reachSpeedDeceleration.setter
    def reachSpeedDeceleration(self, val): self.reachSpeedDeceleration.set(val)
    @property
    def reactToOtherCharacterBodyCollision(self):  # type: ()->Bool
        return Bool(self._node.at("reactToOtherCharacterBodyCollision"))
    @reactToOtherCharacterBodyCollision.setter
    def reactToOtherCharacterBodyCollision(self, val): self.reactToOtherCharacterBodyCollision.set(val)
    @property
    def rigidbodyScalingSpeed(self):  # type: ()->Float
        return Float(self._node.at("rigidbodyScalingSpeed"))
    @rigidbodyScalingSpeed.setter
    def rigidbodyScalingSpeed(self, val): self.rigidbodyScalingSpeed.set(val)
    @property
    def sphereCastRadiusRatio(self):  # type: ()->Float
        return Float(self._node.at("sphereCastRadiusRatio"))
    @sphereCastRadiusRatio.setter
    def sphereCastRadiusRatio(self, val): self.sphereCastRadiusRatio.set(val)
    @property
    def sphereOverrideRadius(self):  # type: ()->Float
        return Float(self._node.at("sphereOverrideRadius"))
    @sphereOverrideRadius.setter
    def sphereOverrideRadius(self, val): self.sphereOverrideRadius.set(val)
    @property
    def strafeBlendIn(self):  # type: ()->Float
        return Float(self._node.at("strafeBlendIn"))
    @strafeBlendIn.setter
    def strafeBlendIn(self, val): self.strafeBlendIn.set(val)
    @property
    def strafeBlendWeightMinToChangeAnim(self):  # type: ()->Float
        return Float(self._node.at("strafeBlendWeightMinToChangeAnim"))
    @strafeBlendWeightMinToChangeAnim.setter
    def strafeBlendWeightMinToChangeAnim(self, val): self.strafeBlendWeightMinToChangeAnim.set(val)
    @property
    def strafeOrientationRateFactor(self):  # type: ()->Float
        return Float(self._node.at("strafeOrientationRateFactor"))
    @strafeOrientationRateFactor.setter
    def strafeOrientationRateFactor(self, val): self.strafeOrientationRateFactor.set(val)
    @property
    def strafeSpeedModeMax(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("strafeSpeedModeMax"))
    @strafeSpeedModeMax.setter
    def strafeSpeedModeMax(self, val): self.strafeSpeedModeMax.set(val)
    @property
    def strafeStopOrientationRateFactor(self):  # type: ()->Float
        return Float(self._node.at("strafeStopOrientationRateFactor"))
    @strafeStopOrientationRateFactor.setter
    def strafeStopOrientationRateFactor(self, val): self.strafeStopOrientationRateFactor.set(val)
    @property
    def strafeTurnAngleMin(self):  # type: ()->Float
        return Float(self._node.at("strafeTurnAngleMin"))
    @strafeTurnAngleMin.setter
    def strafeTurnAngleMin(self, val): self.strafeTurnAngleMin.set(val)
    @property
    def trajectoryRateFactorDuringLateralLand(self):  # type: ()->Float
        return Float(self._node.at("trajectoryRateFactorDuringLateralLand"))
    @trajectoryRateFactorDuringLateralLand.setter
    def trajectoryRateFactorDuringLateralLand(self, val): self.trajectoryRateFactorDuringLateralLand.set(val)
    @property
    def turnAroundInputDirectionAngleDeltaMin(self):  # type: ()->Float
        return Float(self._node.at("turnAroundInputDirectionAngleDeltaMin"))
    @turnAroundInputDirectionAngleDeltaMin.setter
    def turnAroundInputDirectionAngleDeltaMin(self, val): self.turnAroundInputDirectionAngleDeltaMin.set(val)
    @property
    def turnJump(self):  # type: ()->MoveCapacityData_TurnJump
        return MoveCapacityData_TurnJump(self._node.at("turnJump"))
    @property
    def turnRotationMinRatioForNewTurn(self):  # type: ()->Float
        return Float(self._node.at("turnRotationMinRatioForNewTurn"))
    @turnRotationMinRatioForNewTurn.setter
    def turnRotationMinRatioForNewTurn(self, val): self.turnRotationMinRatioForNewTurn.set(val)
    @property
    def turnRotationMinRatioToFinish(self):  # type: ()->Float
        return Float(self._node.at("turnRotationMinRatioToFinish"))
    @turnRotationMinRatioToFinish.setter
    def turnRotationMinRatioToFinish(self, val): self.turnRotationMinRatioToFinish.set(val)
    pass




