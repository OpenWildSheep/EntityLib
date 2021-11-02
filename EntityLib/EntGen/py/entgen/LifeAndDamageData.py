
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Float import *

from EntityLibPy import Node

class LifeAndDamageData(HelperObject):
    schema_name = "LifeAndDamageData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LifeAndDamageData
        return LifeAndDamageData(entlib.load_node_file(sourcefile, entlib.get_schema(LifeAndDamageData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LifeAndDamageData
        return LifeAndDamageData(entlib.make_node(LifeAndDamageData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackCancelThreshold(self):  # type: ()->Float
        return Float(self._node.at("attackCancelThreshold"))
    @attackCancelThreshold.setter
    def attackCancelThreshold(self, val): self.attackCancelThreshold.set(val)
    @property
    def damageThreshold(self):  # type: ()->Float
        return Float(self._node.at("damageThreshold"))
    @damageThreshold.setter
    def damageThreshold(self, val): self.damageThreshold.set(val)
    @property
    def dyingSolidity(self):  # type: ()->Float
        return Float(self._node.at("dyingSolidity"))
    @dyingSolidity.setter
    def dyingSolidity(self, val): self.dyingSolidity.set(val)
    @property
    def energyMax(self):  # type: ()->Float
        return Float(self._node.at("energyMax"))
    @energyMax.setter
    def energyMax(self, val): self.energyMax.set(val)
    @property
    def energyRecoverSpeed(self):  # type: ()->Float
        return Float(self._node.at("energyRecoverSpeed"))
    @energyRecoverSpeed.setter
    def energyRecoverSpeed(self, val): self.energyRecoverSpeed.set(val)
    @property
    def impactPercent(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("impactPercent"))
    @impactPercent.setter
    def impactPercent(self, val): self.impactPercent.set(val)
    @property
    def lifeInjuredCoeff(self):  # type: ()->Float
        return Float(self._node.at("lifeInjuredCoeff"))
    @lifeInjuredCoeff.setter
    def lifeInjuredCoeff(self, val): self.lifeInjuredCoeff.set(val)
    @property
    def lifeMax(self):  # type: ()->Float
        return Float(self._node.at("lifeMax"))
    @lifeMax.setter
    def lifeMax(self, val): self.lifeMax.set(val)
    @property
    def lifeRecoverSpeed(self):  # type: ()->Float
        return Float(self._node.at("lifeRecoverSpeed"))
    @lifeRecoverSpeed.setter
    def lifeRecoverSpeed(self, val): self.lifeRecoverSpeed.set(val)
    @property
    def lifeStunCoeff(self):  # type: ()->Float
        return Float(self._node.at("lifeStunCoeff"))
    @lifeStunCoeff.setter
    def lifeStunCoeff(self, val): self.lifeStunCoeff.set(val)
    @property
    def minLifeWhenSpending(self):  # type: ()->Float
        return Float(self._node.at("minLifeWhenSpending"))
    @minLifeWhenSpending.setter
    def minLifeWhenSpending(self, val): self.minLifeWhenSpending.set(val)
    @property
    def shouldCrashWhenFlyingInjured(self):  # type: ()->Bool
        return Bool(self._node.at("shouldCrashWhenFlyingInjured"))
    @shouldCrashWhenFlyingInjured.setter
    def shouldCrashWhenFlyingInjured(self, val): self.shouldCrashWhenFlyingInjured.set(val)
    @property
    def solidity(self):  # type: ()->Float
        return Float(self._node.at("solidity"))
    @solidity.setter
    def solidity(self, val): self.solidity.set(val)
    @property
    def unbreakable(self):  # type: ()->Bool
        return Bool(self._node.at("unbreakable"))
    @unbreakable.setter
    def unbreakable(self, val): self.unbreakable.set(val)
    @property
    def velocityDamageMax(self):  # type: ()->Float
        return Float(self._node.at("velocityDamageMax"))
    @velocityDamageMax.setter
    def velocityDamageMax(self, val): self.velocityDamageMax.set(val)
    @property
    def velocityImpactMax(self):  # type: ()->Float
        return Float(self._node.at("velocityImpactMax"))
    @velocityImpactMax.setter
    def velocityImpactMax(self, val): self.velocityImpactMax.set(val)
    pass




