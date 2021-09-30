
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *


class ShootData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShootData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ShootData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def ammoName(self): return String(self._node.at("ammoName"))
    @ammoName.setter
    def ammoName(self, val): self.ammoName.set(val)
    @property
    def anticipationImprecision(self): return Float(self._node.at("anticipationImprecision"))
    @anticipationImprecision.setter
    def anticipationImprecision(self, val): self.anticipationImprecision.set(val)
    @property
    def canShoot(self): return Bool(self._node.at("canShoot"))
    @canShoot.setter
    def canShoot(self, val): self.canShoot.set(val)
    @property
    def chargeTierCount(self): return Int(self._node.at("chargeTierCount"))
    @chargeTierCount.setter
    def chargeTierCount(self, val): self.chargeTierCount.set(val)
    @property
    def gravity(self): return Float(self._node.at("gravity"))
    @gravity.setter
    def gravity(self, val): self.gravity.set(val)
    @property
    def lifeCost(self): return Float(self._node.at("lifeCost"))
    @lifeCost.setter
    def lifeCost(self, val): self.lifeCost.set(val)
    @property
    def lifeCostCharged(self): return Float(self._node.at("lifeCostCharged"))
    @lifeCostCharged.setter
    def lifeCostCharged(self, val): self.lifeCostCharged.set(val)
    @property
    def maxChargeDuration(self): return Float(self._node.at("maxChargeDuration"))
    @maxChargeDuration.setter
    def maxChargeDuration(self, val): self.maxChargeDuration.set(val)
    @property
    def maxShootDistance(self): return Float(self._node.at("maxShootDistance"))
    @maxShootDistance.setter
    def maxShootDistance(self, val): self.maxShootDistance.set(val)
    @property
    def minDelayBetweenShots(self): return Float(self._node.at("minDelayBetweenShots"))
    @minDelayBetweenShots.setter
    def minDelayBetweenShots(self, val): self.minDelayBetweenShots.set(val)
    @property
    def randomAngleShoot(self): return Bool(self._node.at("randomAngleShoot"))
    @randomAngleShoot.setter
    def randomAngleShoot(self, val): self.randomAngleShoot.set(val)
    @property
    def shootMaxAngle(self): return Float(self._node.at("shootMaxAngle"))
    @shootMaxAngle.setter
    def shootMaxAngle(self, val): self.shootMaxAngle.set(val)
    @property
    def shootSpeed(self): return Float(self._node.at("shootSpeed"))
    @shootSpeed.setter
    def shootSpeed(self, val): self.shootSpeed.set(val)
    @property
    def zoneImprecision(self): return Float(self._node.at("zoneImprecision"))
    @zoneImprecision.setter
    def zoneImprecision(self, val): self.zoneImprecision.set(val)
    pass




