
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class ProjectileData(HelperObject):
    schema_name = "ProjectileData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileData
        return ProjectileData(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileData
        return ProjectileData(entlib.make_node(ProjectileData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def canCollideWithOtherProjectiles(self):  # type: ()->Bool
        return Bool(self._node.at("canCollideWithOtherProjectiles"))
    @canCollideWithOtherProjectiles.setter
    def canCollideWithOtherProjectiles(self, val): self.canCollideWithOtherProjectiles.set(val)
    @property
    def damages(self):  # type: ()->Float
        return Float(self._node.at("damages"))
    @damages.setter
    def damages(self, val): self.damages.set(val)
    @property
    def deleteAfterPlantTimer(self):  # type: ()->Float
        return Float(self._node.at("deleteAfterPlantTimer"))
    @deleteAfterPlantTimer.setter
    def deleteAfterPlantTimer(self, val): self.deleteAfterPlantTimer.set(val)
    @property
    def destroyOnHit(self):  # type: ()->Bool
        return Bool(self._node.at("destroyOnHit"))
    @destroyOnHit.setter
    def destroyOnHit(self, val): self.destroyOnHit.set(val)
    @property
    def distanceFromBodyAtLaunch(self):  # type: ()->Float
        return Float(self._node.at("distanceFromBodyAtLaunch"))
    @distanceFromBodyAtLaunch.setter
    def distanceFromBodyAtLaunch(self, val): self.distanceFromBodyAtLaunch.set(val)
    @property
    def explodeOnFire(self):  # type: ()->Bool
        return Bool(self._node.at("explodeOnFire"))
    @explodeOnFire.setter
    def explodeOnFire(self, val): self.explodeOnFire.set(val)
    @property
    def explosionShockForce(self):  # type: ()->Float
        return Float(self._node.at("explosionShockForce"))
    @explosionShockForce.setter
    def explosionShockForce(self, val): self.explosionShockForce.set(val)
    @property
    def gameEffectOnHit(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("gameEffectOnHit"))
    @gameEffectOnHit.setter
    def gameEffectOnHit(self, val): self.gameEffectOnHit.set(val)
    @property
    def gravity(self):  # type: ()->Float
        return Float(self._node.at("gravity"))
    @gravity.setter
    def gravity(self, val): self.gravity.set(val)
    @property
    def hasNoCollision(self):  # type: ()->Bool
        return Bool(self._node.at("hasNoCollision"))
    @hasNoCollision.setter
    def hasNoCollision(self, val): self.hasNoCollision.set(val)
    @property
    def hitSourceOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("hitSourceOffset"))
    @hitSourceOffset.setter
    def hitSourceOffset(self, val): self.hitSourceOffset.set(val)
    @property
    def homingInRangeAnticipationDist(self):  # type: ()->Float
        return Float(self._node.at("homingInRangeAnticipationDist"))
    @homingInRangeAnticipationDist.setter
    def homingInRangeAnticipationDist(self, val): self.homingInRangeAnticipationDist.set(val)
    @property
    def homingMaxAngle(self):  # type: ()->Float
        return Float(self._node.at("homingMaxAngle"))
    @homingMaxAngle.setter
    def homingMaxAngle(self, val): self.homingMaxAngle.set(val)
    @property
    def homingMaxFlightTime(self):  # type: ()->Float
        return Float(self._node.at("homingMaxFlightTime"))
    @homingMaxFlightTime.setter
    def homingMaxFlightTime(self, val): self.homingMaxFlightTime.set(val)
    @property
    def homingMaxInFrontAnticipationDist(self):  # type: ()->Float
        return Float(self._node.at("homingMaxInFrontAnticipationDist"))
    @homingMaxInFrontAnticipationDist.setter
    def homingMaxInFrontAnticipationDist(self, val): self.homingMaxInFrontAnticipationDist.set(val)
    @property
    def homingMaxTotalAnticipationDist(self):  # type: ()->Float
        return Float(self._node.at("homingMaxTotalAnticipationDist"))
    @homingMaxTotalAnticipationDist.setter
    def homingMaxTotalAnticipationDist(self, val): self.homingMaxTotalAnticipationDist.set(val)
    @property
    def homingTotalAnticipationRatioSpeeds(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("homingTotalAnticipationRatioSpeeds"))
    @homingTotalAnticipationRatioSpeeds.setter
    def homingTotalAnticipationRatioSpeeds(self, val): self.homingTotalAnticipationRatioSpeeds.set(val)
    @property
    def impact(self):  # type: ()->Float
        return Float(self._node.at("impact"))
    @impact.setter
    def impact(self, val): self.impact.set(val)
    @property
    def isRegenProjectile(self):  # type: ()->Bool
        return Bool(self._node.at("isRegenProjectile"))
    @isRegenProjectile.setter
    def isRegenProjectile(self, val): self.isRegenProjectile.set(val)
    @property
    def isThrowable(self):  # type: ()->Bool
        return Bool(self._node.at("isThrowable"))
    @isThrowable.setter
    def isThrowable(self, val): self.isThrowable.set(val)
    @property
    def launchRotation(self):  # type: ()->Vector3
        return Vector3(self._node.at("launchRotation"))
    @launchRotation.setter
    def launchRotation(self, val): self.launchRotation.set(val)
    @property
    def launchSpeed(self):  # type: ()->Float
        return Float(self._node.at("launchSpeed"))
    @launchSpeed.setter
    def launchSpeed(self, val): self.launchSpeed.set(val)
    @property
    def noiseLevelOnImpact(self):  # type: ()->Float
        return Float(self._node.at("noiseLevelOnImpact"))
    @noiseLevelOnImpact.setter
    def noiseLevelOnImpact(self, val): self.noiseLevelOnImpact.set(val)
    @property
    def shouldBeVisibleBeforeShoot(self):  # type: ()->Bool
        return Bool(self._node.at("shouldBeVisibleBeforeShoot"))
    @shouldBeVisibleBeforeShoot.setter
    def shouldBeVisibleBeforeShoot(self, val): self.shouldBeVisibleBeforeShoot.set(val)
    @property
    def smoothTime(self):  # type: ()->Float
        return Float(self._node.at("smoothTime"))
    @smoothTime.setter
    def smoothTime(self, val): self.smoothTime.set(val)
    @property
    def stopOnWater(self):  # type: ()->Bool
        return Bool(self._node.at("stopOnWater"))
    @stopOnWater.setter
    def stopOnWater(self, val): self.stopOnWater.set(val)
    @property
    def straightDistance(self):  # type: ()->Float
        return Float(self._node.at("straightDistance"))
    @straightDistance.setter
    def straightDistance(self, val): self.straightDistance.set(val)
    @property
    def visibleInFlight(self):  # type: ()->Bool
        return Bool(self._node.at("visibleInFlight"))
    @visibleInFlight.setter
    def visibleInFlight(self, val): self.visibleInFlight.set(val)
    pass




