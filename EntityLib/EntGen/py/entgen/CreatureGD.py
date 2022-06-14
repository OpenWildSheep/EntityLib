
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorGD import *
from entgen.BiteData import *
from entgen.Bool import *
from entgen.CreatureDangerousness import *
from entgen.Float import *
from entgen.RevivedData import *
from entgen.SpeedFastMinDuration import *

from EntityLibPy import Node

class CreatureGD(HelperObject):
    schema_name = "CreatureGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureGD
        return CreatureGD(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureGD
        return CreatureGD(entlib.make_node(CreatureGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DisableLookAt(self):  # type: ()->Bool
        return Bool(self._node.at("DisableLookAt"))
    @DisableLookAt.setter
    def DisableLookAt(self, val): self.DisableLookAt.set(val)
    @property
    def FlyPitchAngleMax(self):  # type: ()->Float
        return Float(self._node.at("FlyPitchAngleMax"))
    @FlyPitchAngleMax.setter
    def FlyPitchAngleMax(self, val): self.FlyPitchAngleMax.set(val)
    @property
    def FlyPitchAngleMin(self):  # type: ()->Float
        return Float(self._node.at("FlyPitchAngleMin"))
    @FlyPitchAngleMin.setter
    def FlyPitchAngleMin(self, val): self.FlyPitchAngleMin.set(val)
    @property
    def IsBig(self):  # type: ()->Bool
        return Bool(self._node.at("IsBig"))
    @IsBig.setter
    def IsBig(self, val): self.IsBig.set(val)
    @property
    def IsDivinity(self):  # type: ()->Bool
        return Bool(self._node.at("IsDivinity"))
    @IsDivinity.setter
    def IsDivinity(self, val): self.IsDivinity.set(val)
    @property
    def IsGuardian(self):  # type: ()->Bool
        return Bool(self._node.at("IsGuardian"))
    @IsGuardian.setter
    def IsGuardian(self, val): self.IsGuardian.set(val)
    @property
    def IsStaff(self):  # type: ()->Bool
        return Bool(self._node.at("IsStaff"))
    @IsStaff.setter
    def IsStaff(self, val): self.IsStaff.set(val)
    @property
    def SpawnSoulIfNoEnemy(self):  # type: ()->Bool
        return Bool(self._node.at("SpawnSoulIfNoEnemy"))
    @SpawnSoulIfNoEnemy.setter
    def SpawnSoulIfNoEnemy(self, val): self.SpawnSoulIfNoEnemy.set(val)
    @property
    def SpeedFastMinDuration(self):  # type: ()->SpeedFastMinDuration
        return SpeedFastMinDuration(self._node.at("SpeedFastMinDuration"))
    @property
    def Super(self):  # type: ()->ActorGD
        return ActorGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def biteData(self):  # type: ()->BiteData
        return BiteData(self._node.at("biteData"))
    @property
    def dangerousnessData(self):  # type: ()->CreatureDangerousness
        return CreatureDangerousness(self._node.at("dangerousnessData"))
    @property
    def revivedData(self):  # type: ()->RevivedData
        return RevivedData(self._node.at("revivedData"))
    pass




