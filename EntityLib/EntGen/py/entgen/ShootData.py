
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ShootData(HelperObject):
    schema_name = "ShootData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShootData
        return ShootData(entlib.load_node_file(sourcefile, entlib.get_schema(ShootData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShootData
        return ShootData(entlib.make_node(ShootData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def ammoName(self):  # type: ()->String
        return String(self._node.at("ammoName"))
    @ammoName.setter
    def ammoName(self, val): self.ammoName.set(val)
    @property
    def anticipationImprecision(self):  # type: ()->Float
        return Float(self._node.at("anticipationImprecision"))
    @anticipationImprecision.setter
    def anticipationImprecision(self, val): self.anticipationImprecision.set(val)
    @property
    def canShoot(self):  # type: ()->Bool
        return Bool(self._node.at("canShoot"))
    @canShoot.setter
    def canShoot(self, val): self.canShoot.set(val)
    @property
    def chargeTierCount(self):  # type: ()->Int
        return Int(self._node.at("chargeTierCount"))
    @chargeTierCount.setter
    def chargeTierCount(self, val): self.chargeTierCount.set(val)
    @property
    def gravity(self):  # type: ()->Float
        return Float(self._node.at("gravity"))
    @gravity.setter
    def gravity(self, val): self.gravity.set(val)
    @property
    def lifeCost(self):  # type: ()->Float
        return Float(self._node.at("lifeCost"))
    @lifeCost.setter
    def lifeCost(self, val): self.lifeCost.set(val)
    @property
    def lifeCostCharged(self):  # type: ()->Float
        return Float(self._node.at("lifeCostCharged"))
    @lifeCostCharged.setter
    def lifeCostCharged(self, val): self.lifeCostCharged.set(val)
    @property
    def maxChargeDuration(self):  # type: ()->Float
        return Float(self._node.at("maxChargeDuration"))
    @maxChargeDuration.setter
    def maxChargeDuration(self, val): self.maxChargeDuration.set(val)
    @property
    def maxShootDistance(self):  # type: ()->Float
        return Float(self._node.at("maxShootDistance"))
    @maxShootDistance.setter
    def maxShootDistance(self, val): self.maxShootDistance.set(val)
    @property
    def minDelayBetweenShots(self):  # type: ()->Float
        return Float(self._node.at("minDelayBetweenShots"))
    @minDelayBetweenShots.setter
    def minDelayBetweenShots(self, val): self.minDelayBetweenShots.set(val)
    @property
    def randomAngleShoot(self):  # type: ()->Bool
        return Bool(self._node.at("randomAngleShoot"))
    @randomAngleShoot.setter
    def randomAngleShoot(self, val): self.randomAngleShoot.set(val)
    @property
    def shootMaxAngle(self):  # type: ()->Float
        return Float(self._node.at("shootMaxAngle"))
    @shootMaxAngle.setter
    def shootMaxAngle(self, val): self.shootMaxAngle.set(val)
    @property
    def shootSpeed(self):  # type: ()->Float
        return Float(self._node.at("shootSpeed"))
    @shootSpeed.setter
    def shootSpeed(self, val): self.shootSpeed.set(val)
    @property
    def zoneImprecision(self):  # type: ()->Float
        return Float(self._node.at("zoneImprecision"))
    @zoneImprecision.setter
    def zoneImprecision(self, val): self.zoneImprecision.set(val)
    pass




