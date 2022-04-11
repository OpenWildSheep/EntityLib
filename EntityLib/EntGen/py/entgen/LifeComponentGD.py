
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class LifeComponentGD(HelperObject):
    schema_name = "LifeComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LifeComponentGD
        return LifeComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(LifeComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LifeComponentGD
        return LifeComponentGD(entlib.make_node(LifeComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AttackCancelDamagesThreshold(self):  # type: ()->Float
        return Float(self._node.at("AttackCancelDamagesThreshold"))
    @AttackCancelDamagesThreshold.setter
    def AttackCancelDamagesThreshold(self, val): self.AttackCancelDamagesThreshold.set(val)
    @property
    def ClearDamagesWhenNoCombatAfterTime(self):  # type: ()->Float
        return Float(self._node.at("ClearDamagesWhenNoCombatAfterTime"))
    @ClearDamagesWhenNoCombatAfterTime.setter
    def ClearDamagesWhenNoCombatAfterTime(self, val): self.ClearDamagesWhenNoCombatAfterTime.set(val)
    @property
    def DamagesRecoverSpeed(self):  # type: ()->Float
        return Float(self._node.at("DamagesRecoverSpeed"))
    @DamagesRecoverSpeed.setter
    def DamagesRecoverSpeed(self, val): self.DamagesRecoverSpeed.set(val)
    @property
    def DamagesShield(self):  # type: ()->Float
        return Float(self._node.at("DamagesShield"))
    @DamagesShield.setter
    def DamagesShield(self, val): self.DamagesShield.set(val)
    @property
    def DeathThreshold(self):  # type: ()->Float
        return Float(self._node.at("DeathThreshold"))
    @DeathThreshold.setter
    def DeathThreshold(self, val): self.DeathThreshold.set(val)
    @property
    def InjuredDamagesRatio(self):  # type: ()->Float
        return Float(self._node.at("InjuredDamagesRatio"))
    @InjuredDamagesRatio.setter
    def InjuredDamagesRatio(self, val): self.InjuredDamagesRatio.set(val)
    @property
    def MinLifeWhenSpending(self):  # type: ()->Float
        return Float(self._node.at("MinLifeWhenSpending"))
    @MinLifeWhenSpending.setter
    def MinLifeWhenSpending(self, val): self.MinLifeWhenSpending.set(val)
    @property
    def ShouldCrashWhenFlyingInjured(self):  # type: ()->Bool
        return Bool(self._node.at("ShouldCrashWhenFlyingInjured"))
    @ShouldCrashWhenFlyingInjured.setter
    def ShouldCrashWhenFlyingInjured(self, val): self.ShouldCrashWhenFlyingInjured.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VelocityDamagesMax(self):  # type: ()->Float
        return Float(self._node.at("VelocityDamagesMax"))
    @VelocityDamagesMax.setter
    def VelocityDamagesMax(self, val): self.VelocityDamagesMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




