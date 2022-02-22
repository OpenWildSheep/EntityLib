
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *
from entgen.AttackDamageData import *
from entgen.String import *
from entgen.AttackImpactData import *
from entgen.String import *
from entgen.CameraShakeData import *
from entgen.String import *

from EntityLibPy import Node

class GameAttackData(HelperObject):
    schema_name = "GameAttackData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameAttackData
        return GameAttackData(entlib.load_node_file(sourcefile, entlib.get_schema(GameAttackData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameAttackData
        return GameAttackData(entlib.make_node(GameAttackData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AggressiveDuration(self):  # type: ()->Float
        return Float(self._node.at("AggressiveDuration"))
    @AggressiveDuration.setter
    def AggressiveDuration(self, val): self.AggressiveDuration.set(val)
    @property
    def AttackCameraShakeData(self):  # type: ()->Map[str, CameraShakeData]
        return (lambda n: Map(str, CameraShakeData, n))(self._node.at("AttackCameraShakeData"))
    @property
    def AttackDamageData(self):  # type: ()->Map[str, AttackDamageData]
        return (lambda n: Map(str, AttackDamageData, n))(self._node.at("AttackDamageData"))
    @property
    def AttackImpactData(self):  # type: ()->Map[str, AttackImpactData]
        return (lambda n: Map(str, AttackImpactData, n))(self._node.at("AttackImpactData"))
    @property
    def DashTargetImpulse(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("DashTargetImpulse"))
    @property
    def ShapeAfterGlowTime(self):  # type: ()->Float
        return Float(self._node.at("ShapeAfterGlowTime"))
    @ShapeAfterGlowTime.setter
    def ShapeAfterGlowTime(self, val): self.ShapeAfterGlowTime.set(val)
    @property
    def ShapeAnticipationTime(self):  # type: ()->Float
        return Float(self._node.at("ShapeAnticipationTime"))
    @ShapeAnticipationTime.setter
    def ShapeAnticipationTime(self, val): self.ShapeAnticipationTime.set(val)
    @property
    def ShapePassivedAnticipationTime(self):  # type: ()->Float
        return Float(self._node.at("ShapePassivedAnticipationTime"))
    @ShapePassivedAnticipationTime.setter
    def ShapePassivedAnticipationTime(self, val): self.ShapePassivedAnticipationTime.set(val)
    @property
    def ShapeRadiusScale(self):  # type: ()->Float
        return Float(self._node.at("ShapeRadiusScale"))
    @ShapeRadiusScale.setter
    def ShapeRadiusScale(self, val): self.ShapeRadiusScale.set(val)
    @property
    def SpeedLockedDelayAfterDodge(self):  # type: ()->Float
        return Float(self._node.at("SpeedLockedDelayAfterDodge"))
    @SpeedLockedDelayAfterDodge.setter
    def SpeedLockedDelayAfterDodge(self, val): self.SpeedLockedDelayAfterDodge.set(val)
    @property
    def UseMountAttack(self):  # type: ()->Bool
        return Bool(self._node.at("UseMountAttack"))
    @UseMountAttack.setter
    def UseMountAttack(self, val): self.UseMountAttack.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




