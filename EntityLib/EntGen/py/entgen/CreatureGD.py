
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorGD import *
from entgen.BiteData import *
from entgen.Bool import *
from entgen.CreatureDangerousness import *
from entgen.FallData import *
from entgen.Float import *
from entgen.FusionData import *
from entgen.InteractData import *
from entgen.MountData import *
from entgen.RevivedData import *
from entgen.SpeedFastMinDuration import *


class CreatureGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CreatureGD.schema_name))
    @property
    def DisableLookAt(self): return Bool(self._node.at("DisableLookAt"))
    @DisableLookAt.setter
    def DisableLookAt(self, val): self.DisableLookAt.set(val)
    @property
    def DivePitchAngleMax(self): return Float(self._node.at("DivePitchAngleMax"))
    @DivePitchAngleMax.setter
    def DivePitchAngleMax(self, val): self.DivePitchAngleMax.set(val)
    @property
    def DivePitchAngleMin(self): return Float(self._node.at("DivePitchAngleMin"))
    @DivePitchAngleMin.setter
    def DivePitchAngleMin(self, val): self.DivePitchAngleMin.set(val)
    @property
    def FlyPitchAngleMax(self): return Float(self._node.at("FlyPitchAngleMax"))
    @FlyPitchAngleMax.setter
    def FlyPitchAngleMax(self, val): self.FlyPitchAngleMax.set(val)
    @property
    def FlyPitchAngleMin(self): return Float(self._node.at("FlyPitchAngleMin"))
    @FlyPitchAngleMin.setter
    def FlyPitchAngleMin(self, val): self.FlyPitchAngleMin.set(val)
    @property
    def IsBig(self): return Bool(self._node.at("IsBig"))
    @IsBig.setter
    def IsBig(self, val): self.IsBig.set(val)
    @property
    def IsDivinity(self): return Bool(self._node.at("IsDivinity"))
    @IsDivinity.setter
    def IsDivinity(self, val): self.IsDivinity.set(val)
    @property
    def IsGuardian(self): return Bool(self._node.at("IsGuardian"))
    @IsGuardian.setter
    def IsGuardian(self, val): self.IsGuardian.set(val)
    @property
    def IsStaff(self): return Bool(self._node.at("IsStaff"))
    @IsStaff.setter
    def IsStaff(self, val): self.IsStaff.set(val)
    @property
    def SpawnSoulIfNoEnemy(self): return Bool(self._node.at("SpawnSoulIfNoEnemy"))
    @SpawnSoulIfNoEnemy.setter
    def SpawnSoulIfNoEnemy(self, val): self.SpawnSoulIfNoEnemy.set(val)
    @property
    def SpeedFastMinDuration(self): return SpeedFastMinDuration(self._node.at("SpeedFastMinDuration"))
    @property
    def Super(self): return ActorGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def biteData(self): return BiteData(self._node.at("biteData"))
    @property
    def dangerousnessData(self): return CreatureDangerousness(self._node.at("dangerousnessData"))
    @property
    def fallData(self): return FallData(self._node.at("fallData"))
    @property
    def fusionData(self): return FusionData(self._node.at("fusionData"))
    @property
    def interactData(self): return InteractData(self._node.at("interactData"))
    @property
    def mountData(self): return MountData(self._node.at("mountData"))
    @property
    def revivedData(self): return RevivedData(self._node.at("revivedData"))
    pass




