
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.MenaceSelection import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ShootSequenceData import *

from EntityLibPy import Node

class BehaviorScriptData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BehaviorScriptData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BehaviorScriptData
        return BehaviorScriptData(entlib.load_node_file(sourcefile, entlib.get_schema(BehaviorScriptData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BehaviorScriptData
        return BehaviorScriptData(entlib.make_node(BehaviorScriptData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def additionalDangerousnessDiffToFlee(self):  # type: ()->Float
        return Float(self._node.at("additionalDangerousnessDiffToFlee"))
    @additionalDangerousnessDiffToFlee.setter
    def additionalDangerousnessDiffToFlee(self, val): self.additionalDangerousnessDiffToFlee.set(val)
    @property
    def aimingDuration(self):  # type: ()->Float
        return Float(self._node.at("aimingDuration"))
    @aimingDuration.setter
    def aimingDuration(self, val): self.aimingDuration.set(val)
    @property
    def answerAttackRunSpeed(self):  # type: ()->Int
        return Int(self._node.at("answerAttackRunSpeed"))
    @answerAttackRunSpeed.setter
    def answerAttackRunSpeed(self, val): self.answerAttackRunSpeed.set(val)
    @property
    def artificialArenaRadius(self):  # type: ()->Float
        return Float(self._node.at("artificialArenaRadius"))
    @artificialArenaRadius.setter
    def artificialArenaRadius(self, val): self.artificialArenaRadius.set(val)
    @property
    def attackAggressivityDecrease(self):  # type: ()->Int
        return Int(self._node.at("attackAggressivityDecrease"))
    @attackAggressivityDecrease.setter
    def attackAggressivityDecrease(self, val): self.attackAggressivityDecrease.set(val)
    @property
    def attackIfEnemyHasBeenSeenSince(self):  # type: ()->Float
        return Float(self._node.at("attackIfEnemyHasBeenSeenSince"))
    @attackIfEnemyHasBeenSeenSince.setter
    def attackIfEnemyHasBeenSeenSince(self, val): self.attackIfEnemyHasBeenSeenSince.set(val)
    @property
    def attackInPack(self):  # type: ()->Bool
        return Bool(self._node.at("attackInPack"))
    @attackInPack.setter
    def attackInPack(self, val): self.attackInPack.set(val)
    @property
    def attackOrderCanFlee(self):  # type: ()->Bool
        return Bool(self._node.at("attackOrderCanFlee"))
    @attackOrderCanFlee.setter
    def attackOrderCanFlee(self, val): self.attackOrderCanFlee.set(val)
    @property
    def attackRunSpeed(self):  # type: ()->Int
        return Int(self._node.at("attackRunSpeed"))
    @attackRunSpeed.setter
    def attackRunSpeed(self, val): self.attackRunSpeed.set(val)
    @property
    def attackWaitCircle_Offset_Z(self):  # type: ()->Float
        return Float(self._node.at("attackWaitCircle_Offset_Z"))
    @attackWaitCircle_Offset_Z.setter
    def attackWaitCircle_Offset_Z(self, val): self.attackWaitCircle_Offset_Z.set(val)
    @property
    def avoidGroundMovements(self):  # type: ()->Bool
        return Bool(self._node.at("avoidGroundMovements"))
    @avoidGroundMovements.setter
    def avoidGroundMovements(self, val): self.avoidGroundMovements.set(val)
    @property
    def avoidWaterMovements(self):  # type: ()->Bool
        return Bool(self._node.at("avoidWaterMovements"))
    @avoidWaterMovements.setter
    def avoidWaterMovements(self, val): self.avoidWaterMovements.set(val)
    @property
    def blockedByScaryWeather(self):  # type: ()->Bool
        return Bool(self._node.at("blockedByScaryWeather"))
    @blockedByScaryWeather.setter
    def blockedByScaryWeather(self, val): self.blockedByScaryWeather.set(val)
    @property
    def canBite(self):  # type: ()->Bool
        return Bool(self._node.at("canBite"))
    @canBite.setter
    def canBite(self, val): self.canBite.set(val)
    @property
    def canFlee(self):  # type: ()->Bool
        return Bool(self._node.at("canFlee"))
    @canFlee.setter
    def canFlee(self, val): self.canFlee.set(val)
    @property
    def closeAttack_Offset_Z(self):  # type: ()->Float
        return Float(self._node.at("closeAttack_Offset_Z"))
    @closeAttack_Offset_Z.setter
    def closeAttack_Offset_Z(self, val): self.closeAttack_Offset_Z.set(val)
    @property
    def closeCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("closeCombatDistance"))
    @closeCombatDistance.setter
    def closeCombatDistance(self, val): self.closeCombatDistance.set(val)
    @property
    def combatFlyingHeightOffset(self):  # type: ()->Float
        return Float(self._node.at("combatFlyingHeightOffset"))
    @combatFlyingHeightOffset.setter
    def combatFlyingHeightOffset(self, val): self.combatFlyingHeightOffset.set(val)
    @property
    def combatSpeedModeOnNodes(self):  # type: ()->Int
        return Int(self._node.at("combatSpeedModeOnNodes"))
    @combatSpeedModeOnNodes.setter
    def combatSpeedModeOnNodes(self, val): self.combatSpeedModeOnNodes.set(val)
    @property
    def combatStopOnNodeCoolDown(self):  # type: ()->Float
        return Float(self._node.at("combatStopOnNodeCoolDown"))
    @combatStopOnNodeCoolDown.setter
    def combatStopOnNodeCoolDown(self, val): self.combatStopOnNodeCoolDown.set(val)
    @property
    def combatStopOnNodeMaxTime(self):  # type: ()->Float
        return Float(self._node.at("combatStopOnNodeMaxTime"))
    @combatStopOnNodeMaxTime.setter
    def combatStopOnNodeMaxTime(self, val): self.combatStopOnNodeMaxTime.set(val)
    @property
    def combatTooCloseDistance(self):  # type: ()->Float
        return Float(self._node.at("combatTooCloseDistance"))
    @combatTooCloseDistance.setter
    def combatTooCloseDistance(self, val): self.combatTooCloseDistance.set(val)
    @property
    def combatTriggerStopOnNodeTimerDistance(self):  # type: ()->Float
        return Float(self._node.at("combatTriggerStopOnNodeTimerDistance"))
    @combatTriggerStopOnNodeTimerDistance.setter
    def combatTriggerStopOnNodeTimerDistance(self, val): self.combatTriggerStopOnNodeTimerDistance.set(val)
    @property
    def considersRunnerAsAMenace(self):  # type: ()->Bool
        return Bool(self._node.at("considersRunnerAsAMenace"))
    @considersRunnerAsAMenace.setter
    def considersRunnerAsAMenace(self, val): self.considersRunnerAsAMenace.set(val)
    @property
    def coolDownBetweenProjectileDodge(self):  # type: ()->Float
        return Float(self._node.at("coolDownBetweenProjectileDodge"))
    @coolDownBetweenProjectileDodge.setter
    def coolDownBetweenProjectileDodge(self, val): self.coolDownBetweenProjectileDodge.set(val)
    @property
    def drivingAimAngle(self):  # type: ()->Float
        return Float(self._node.at("drivingAimAngle"))
    @drivingAimAngle.setter
    def drivingAimAngle(self, val): self.drivingAimAngle.set(val)
    @property
    def drivingAimSpeed(self):  # type: ()->Float
        return Float(self._node.at("drivingAimSpeed"))
    @drivingAimSpeed.setter
    def drivingAimSpeed(self, val): self.drivingAimSpeed.set(val)
    @property
    def enemyAggressivity(self):  # type: ()->Int
        return Int(self._node.at("enemyAggressivity"))
    @enemyAggressivity.setter
    def enemyAggressivity(self, val): self.enemyAggressivity.set(val)
    @property
    def energyAttackProbability(self):  # type: ()->Float
        return Float(self._node.at("energyAttackProbability"))
    @energyAttackProbability.setter
    def energyAttackProbability(self, val): self.energyAttackProbability.set(val)
    @property
    def engageInCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("engageInCombatDistance"))
    @engageInCombatDistance.setter
    def engageInCombatDistance(self, val): self.engageInCombatDistance.set(val)
    @property
    def farCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("farCombatDistance"))
    @farCombatDistance.setter
    def farCombatDistance(self, val): self.farCombatDistance.set(val)
    @property
    def feelsSafeWhenDangerIsThisFar(self):  # type: ()->Float
        return Float(self._node.at("feelsSafeWhenDangerIsThisFar"))
    @feelsSafeWhenDangerIsThisFar.setter
    def feelsSafeWhenDangerIsThisFar(self, val): self.feelsSafeWhenDangerIsThisFar.set(val)
    @property
    def fleeDistToEnemy(self):  # type: ()->Float
        return Float(self._node.at("fleeDistToEnemy"))
    @fleeDistToEnemy.setter
    def fleeDistToEnemy(self, val): self.fleeDistToEnemy.set(val)
    @property
    def fleeMaxDist(self):  # type: ()->Float
        return Float(self._node.at("fleeMaxDist"))
    @fleeMaxDist.setter
    def fleeMaxDist(self, val): self.fleeMaxDist.set(val)
    @property
    def fleeTime(self):  # type: ()->Float
        return Float(self._node.at("fleeTime"))
    @fleeTime.setter
    def fleeTime(self, val): self.fleeTime.set(val)
    @property
    def flockingArenaRadius(self):  # type: ()->Float
        return Float(self._node.at("flockingArenaRadius"))
    @flockingArenaRadius.setter
    def flockingArenaRadius(self, val): self.flockingArenaRadius.set(val)
    @property
    def friendAggressivity(self):  # type: ()->Int
        return Int(self._node.at("friendAggressivity"))
    @friendAggressivity.setter
    def friendAggressivity(self, val): self.friendAggressivity.set(val)
    @property
    def goToTargetCheckDistance(self):  # type: ()->Float
        return Float(self._node.at("goToTargetCheckDistance"))
    @goToTargetCheckDistance.setter
    def goToTargetCheckDistance(self, val): self.goToTargetCheckDistance.set(val)
    @property
    def guideFollowMalusScorePerSec(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMalusScorePerSec"))
    @guideFollowMalusScorePerSec.setter
    def guideFollowMalusScorePerSec(self, val): self.guideFollowMalusScorePerSec.set(val)
    @property
    def guideFollowMaxBonusScorePerSec(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMaxBonusScorePerSec"))
    @guideFollowMaxBonusScorePerSec.setter
    def guideFollowMaxBonusScorePerSec(self, val): self.guideFollowMaxBonusScorePerSec.set(val)
    @property
    def guideFollowMaxDistToScore(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMaxDistToScore"))
    @guideFollowMaxDistToScore.setter
    def guideFollowMaxDistToScore(self, val): self.guideFollowMaxDistToScore.set(val)
    @property
    def guideFollowMaxDistanceToTrail(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMaxDistanceToTrail"))
    @guideFollowMaxDistanceToTrail.setter
    def guideFollowMaxDistanceToTrail(self, val): self.guideFollowMaxDistanceToTrail.set(val)
    @property
    def guideFollowMinBonusScorePerSec(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMinBonusScorePerSec"))
    @guideFollowMinBonusScorePerSec.setter
    def guideFollowMinBonusScorePerSec(self, val): self.guideFollowMinBonusScorePerSec.set(val)
    @property
    def guideFollowMinDistToScore(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMinDistToScore"))
    @guideFollowMinDistToScore.setter
    def guideFollowMinDistToScore(self, val): self.guideFollowMinDistToScore.set(val)
    @property
    def guideFollowScoreThreshold(self):  # type: ()->Float
        return Float(self._node.at("guideFollowScoreThreshold"))
    @guideFollowScoreThreshold.setter
    def guideFollowScoreThreshold(self, val): self.guideFollowScoreThreshold.set(val)
    @property
    def guideFollowTimeBetweenTeleport(self):  # type: ()->Float
        return Float(self._node.at("guideFollowTimeBetweenTeleport"))
    @guideFollowTimeBetweenTeleport.setter
    def guideFollowTimeBetweenTeleport(self, val): self.guideFollowTimeBetweenTeleport.set(val)
    @property
    def guideMinSpeed(self):  # type: ()->Float
        return Float(self._node.at("guideMinSpeed"))
    @guideMinSpeed.setter
    def guideMinSpeed(self, val): self.guideMinSpeed.set(val)
    @property
    def guideRepulsiveDistIn(self):  # type: ()->Float
        return Float(self._node.at("guideRepulsiveDistIn"))
    @guideRepulsiveDistIn.setter
    def guideRepulsiveDistIn(self, val): self.guideRepulsiveDistIn.set(val)
    @property
    def guideRepulsiveDistOut(self):  # type: ()->Float
        return Float(self._node.at("guideRepulsiveDistOut"))
    @guideRepulsiveDistOut.setter
    def guideRepulsiveDistOut(self, val): self.guideRepulsiveDistOut.set(val)
    @property
    def hardFeelingsFriendlyHitCount(self):  # type: ()->Int
        return Int(self._node.at("hardFeelingsFriendlyHitCount"))
    @hardFeelingsFriendlyHitCount.setter
    def hardFeelingsFriendlyHitCount(self, val): self.hardFeelingsFriendlyHitCount.set(val)
    @property
    def hardFeelingsNotFriendlyHitCount(self):  # type: ()->Int
        return Int(self._node.at("hardFeelingsNotFriendlyHitCount"))
    @hardFeelingsNotFriendlyHitCount.setter
    def hardFeelingsNotFriendlyHitCount(self, val): self.hardFeelingsNotFriendlyHitCount.set(val)
    @property
    def helpOtherDoneIfLifeAboveThreshold(self):  # type: ()->Float
        return Float(self._node.at("helpOtherDoneIfLifeAboveThreshold"))
    @helpOtherDoneIfLifeAboveThreshold.setter
    def helpOtherDoneIfLifeAboveThreshold(self, val): self.helpOtherDoneIfLifeAboveThreshold.set(val)
    @property
    def helpOtherIfLifeBelowThreshold(self):  # type: ()->Float
        return Float(self._node.at("helpOtherIfLifeBelowThreshold"))
    @helpOtherIfLifeBelowThreshold.setter
    def helpOtherIfLifeBelowThreshold(self, val): self.helpOtherIfLifeBelowThreshold.set(val)
    @property
    def innerArenaRatio(self):  # type: ()->Float
        return Float(self._node.at("innerArenaRatio"))
    @innerArenaRatio.setter
    def innerArenaRatio(self, val): self.innerArenaRatio.set(val)
    @property
    def isAffectedByStench(self):  # type: ()->Bool
        return Bool(self._node.at("isAffectedByStench"))
    @isAffectedByStench.setter
    def isAffectedByStench(self, val): self.isAffectedByStench.set(val)
    @property
    def isCourageous(self):  # type: ()->Bool
        return Bool(self._node.at("isCourageous"))
    @isCourageous.setter
    def isCourageous(self, val): self.isCourageous.set(val)
    @property
    def isScaredBySoundEffect(self):  # type: ()->Bool
        return Bool(self._node.at("isScaredBySoundEffect"))
    @isScaredBySoundEffect.setter
    def isScaredBySoundEffect(self, val): self.isScaredBySoundEffect.set(val)
    @property
    def jumpAttackProbability(self):  # type: ()->Float
        return Float(self._node.at("jumpAttackProbability"))
    @jumpAttackProbability.setter
    def jumpAttackProbability(self, val): self.jumpAttackProbability.set(val)
    @property
    def lifeInDangerThreshold(self):  # type: ()->Float
        return Float(self._node.at("lifeInDangerThreshold"))
    @lifeInDangerThreshold.setter
    def lifeInDangerThreshold(self, val): self.lifeInDangerThreshold.set(val)
    @property
    def lifeInNoMoreDangerThreshold(self):  # type: ()->Float
        return Float(self._node.at("lifeInNoMoreDangerThreshold"))
    @lifeInNoMoreDangerThreshold.setter
    def lifeInNoMoreDangerThreshold(self, val): self.lifeInNoMoreDangerThreshold.set(val)
    @property
    def lockEnemyFollowMaxDistFromGuide(self):  # type: ()->Float
        return Float(self._node.at("lockEnemyFollowMaxDistFromGuide"))
    @lockEnemyFollowMaxDistFromGuide.setter
    def lockEnemyFollowMaxDistFromGuide(self, val): self.lockEnemyFollowMaxDistFromGuide.set(val)
    @property
    def maxDistanceToFollowBeam(self):  # type: ()->Float
        return Float(self._node.at("maxDistanceToFollowBeam"))
    @maxDistanceToFollowBeam.setter
    def maxDistanceToFollowBeam(self, val): self.maxDistanceToFollowBeam.set(val)
    @property
    def maxFollowerCount(self):  # type: ()->Int
        return Int(self._node.at("maxFollowerCount"))
    @maxFollowerCount.setter
    def maxFollowerCount(self, val): self.maxFollowerCount.set(val)
    @property
    def maxLookOutModeTimer(self):  # type: ()->Float
        return Float(self._node.at("maxLookOutModeTimer"))
    @maxLookOutModeTimer.setter
    def maxLookOutModeTimer(self, val): self.maxLookOutModeTimer.set(val)
    @property
    def maxTimeBeforeStoppingToWaitForBeam(self):  # type: ()->Float
        return Float(self._node.at("maxTimeBeforeStoppingToWaitForBeam"))
    @maxTimeBeforeStoppingToWaitForBeam.setter
    def maxTimeBeforeStoppingToWaitForBeam(self, val): self.maxTimeBeforeStoppingToWaitForBeam.set(val)
    @property
    def menaceSelection(self):  # type: ()->MenaceSelection
        return MenaceSelection(self._node.at("menaceSelection"))
    @menaceSelection.setter
    def menaceSelection(self, val): self.menaceSelection.set(val)
    @property
    def middleCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("middleCombatDistance"))
    @middleCombatDistance.setter
    def middleCombatDistance(self, val): self.middleCombatDistance.set(val)
    @property
    def minAbsoluteDistanceToTeleportToMaster(self):  # type: ()->Float
        return Float(self._node.at("minAbsoluteDistanceToTeleportToMaster"))
    @minAbsoluteDistanceToTeleportToMaster.setter
    def minAbsoluteDistanceToTeleportToMaster(self, val): self.minAbsoluteDistanceToTeleportToMaster.set(val)
    @property
    def minDistanceToBeamPosition(self):  # type: ()->Float
        return Float(self._node.at("minDistanceToBeamPosition"))
    @minDistanceToBeamPosition.setter
    def minDistanceToBeamPosition(self, val): self.minDistanceToBeamPosition.set(val)
    @property
    def minDistanceToFollowBeam(self):  # type: ()->Float
        return Float(self._node.at("minDistanceToFollowBeam"))
    @minDistanceToFollowBeam.setter
    def minDistanceToFollowBeam(self, val): self.minDistanceToFollowBeam.set(val)
    @property
    def minNavmeshDistanceToTeleportToMaster(self):  # type: ()->Float
        return Float(self._node.at("minNavmeshDistanceToTeleportToMaster"))
    @minNavmeshDistanceToTeleportToMaster.setter
    def minNavmeshDistanceToTeleportToMaster(self, val): self.minNavmeshDistanceToTeleportToMaster.set(val)
    @property
    def minTimeBeforeStoppingToWaitForBeam(self):  # type: ()->Float
        return Float(self._node.at("minTimeBeforeStoppingToWaitForBeam"))
    @minTimeBeforeStoppingToWaitForBeam.setter
    def minTimeBeforeStoppingToWaitForBeam(self, val): self.minTimeBeforeStoppingToWaitForBeam.set(val)
    @property
    def noAttackTimeAfterAttack(self):  # type: ()->Float
        return Float(self._node.at("noAttackTimeAfterAttack"))
    @noAttackTimeAfterAttack.setter
    def noAttackTimeAfterAttack(self, val): self.noAttackTimeAfterAttack.set(val)
    @property
    def offerAGiftWhenChosen(self):  # type: ()->Bool
        return Bool(self._node.at("offerAGiftWhenChosen"))
    @offerAGiftWhenChosen.setter
    def offerAGiftWhenChosen(self, val): self.offerAGiftWhenChosen.set(val)
    @property
    def panicAggressivityDecrease(self):  # type: ()->Int
        return Int(self._node.at("panicAggressivityDecrease"))
    @panicAggressivityDecrease.setter
    def panicAggressivityDecrease(self, val): self.panicAggressivityDecrease.set(val)
    @property
    def panicsWhenGameEffect(self):  # type: ()->Int
        return Int(self._node.at("panicsWhenGameEffect"))
    @panicsWhenGameEffect.setter
    def panicsWhenGameEffect(self, val): self.panicsWhenGameEffect.set(val)
    @property
    def returnOnCircleAfterMaxAttacks(self):  # type: ()->Int
        return Int(self._node.at("returnOnCircleAfterMaxAttacks"))
    @returnOnCircleAfterMaxAttacks.setter
    def returnOnCircleAfterMaxAttacks(self, val): self.returnOnCircleAfterMaxAttacks.set(val)
    @property
    def roamSpeedModeOnNodes(self):  # type: ()->Int
        return Int(self._node.at("roamSpeedModeOnNodes"))
    @roamSpeedModeOnNodes.setter
    def roamSpeedModeOnNodes(self, val): self.roamSpeedModeOnNodes.set(val)
    @property
    def runsForDistancesSuperiorTo(self):  # type: ()->Float
        return Float(self._node.at("runsForDistancesSuperiorTo"))
    @runsForDistancesSuperiorTo.setter
    def runsForDistancesSuperiorTo(self, val): self.runsForDistancesSuperiorTo.set(val)
    @property
    def searchSoulOpportunity(self):  # type: ()->Bool
        return Bool(self._node.at("searchSoulOpportunity"))
    @searchSoulOpportunity.setter
    def searchSoulOpportunity(self, val): self.searchSoulOpportunity.set(val)
    @property
    def shootPreferedEnemyDistance(self):  # type: ()->Float
        return Float(self._node.at("shootPreferedEnemyDistance"))
    @shootPreferedEnemyDistance.setter
    def shootPreferedEnemyDistance(self, val): self.shootPreferedEnemyDistance.set(val)
    @property
    def shootSequence(self):  # type: ()->Array[ShootSequenceData]
        return (lambda n: Array(ShootSequenceData, n))(self._node.at("shootSequence"))
    @property
    def shootingMistakeMaxDelta(self):  # type: ()->Float
        return Float(self._node.at("shootingMistakeMaxDelta"))
    @shootingMistakeMaxDelta.setter
    def shootingMistakeMaxDelta(self, val): self.shootingMistakeMaxDelta.set(val)
    @property
    def shouldConquer(self):  # type: ()->Bool
        return Bool(self._node.at("shouldConquer"))
    @shouldConquer.setter
    def shouldConquer(self, val): self.shouldConquer.set(val)
    @property
    def shouldDodgeAfterAttack(self):  # type: ()->Bool
        return Bool(self._node.at("shouldDodgeAfterAttack"))
    @shouldDodgeAfterAttack.setter
    def shouldDodgeAfterAttack(self, val): self.shouldDodgeAfterAttack.set(val)
    @property
    def shouldHealPools(self):  # type: ()->Bool
        return Bool(self._node.at("shouldHealPools"))
    @shouldHealPools.setter
    def shouldHealPools(self, val): self.shouldHealPools.set(val)
    @property
    def shouldJumpInArena(self):  # type: ()->Bool
        return Bool(self._node.at("shouldJumpInArena"))
    @shouldJumpInArena.setter
    def shouldJumpInArena(self, val): self.shouldJumpInArena.set(val)
    @property
    def shouldStrafe(self):  # type: ()->Bool
        return Bool(self._node.at("shouldStrafe"))
    @shouldStrafe.setter
    def shouldStrafe(self, val): self.shouldStrafe.set(val)
    @property
    def shouldTranshumance(self):  # type: ()->Bool
        return Bool(self._node.at("shouldTranshumance"))
    @shouldTranshumance.setter
    def shouldTranshumance(self, val): self.shouldTranshumance.set(val)
    @property
    def staffAngleFullHint(self):  # type: ()->Float
        return Float(self._node.at("staffAngleFullHint"))
    @staffAngleFullHint.setter
    def staffAngleFullHint(self, val): self.staffAngleFullHint.set(val)
    @property
    def staffMaxTimeInAlert(self):  # type: ()->Float
        return Float(self._node.at("staffMaxTimeInAlert"))
    @staffMaxTimeInAlert.setter
    def staffMaxTimeInAlert(self, val): self.staffMaxTimeInAlert.set(val)
    @property
    def staffMinScoreToAlert(self):  # type: ()->Int
        return Int(self._node.at("staffMinScoreToAlert"))
    @staffMinScoreToAlert.setter
    def staffMinScoreToAlert(self, val): self.staffMinScoreToAlert.set(val)
    @property
    def staffTimeBeforeAlertAgain(self):  # type: ()->Float
        return Float(self._node.at("staffTimeBeforeAlertAgain"))
    @staffTimeBeforeAlertAgain.setter
    def staffTimeBeforeAlertAgain(self, val): self.staffTimeBeforeAlertAgain.set(val)
    @property
    def usesWarningShot(self):  # type: ()->Bool
        return Bool(self._node.at("usesWarningShot"))
    @usesWarningShot.setter
    def usesWarningShot(self, val): self.usesWarningShot.set(val)
    pass




