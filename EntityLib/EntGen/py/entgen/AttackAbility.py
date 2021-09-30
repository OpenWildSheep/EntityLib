
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CameraShakeData import *
from entgen.Float import *
from entgen.FreezeData import *


class AttackAbility(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackAbility"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AttackAbility.schema_name))
    @property
    def Damage(self): return Float(self._node.at("Damage"))
    @Damage.setter
    def Damage(self, val): self.Damage.set(val)
    @property
    def DistanceMax(self): return Float(self._node.at("DistanceMax"))
    @DistanceMax.setter
    def DistanceMax(self, val): self.DistanceMax.set(val)
    @property
    def DistanceMin(self): return Float(self._node.at("DistanceMin"))
    @DistanceMin.setter
    def DistanceMin(self, val): self.DistanceMin.set(val)
    @property
    def Duration(self): return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def EnergyCost(self): return Float(self._node.at("EnergyCost"))
    @EnergyCost.setter
    def EnergyCost(self, val): self.EnergyCost.set(val)
    @property
    def FreezeData(self): return FreezeData(self._node.at("FreezeData"))
    @property
    def Impact(self): return Float(self._node.at("Impact"))
    @Impact.setter
    def Impact(self, val): self.Impact.set(val)
    @property
    def ShakeData(self): return CameraShakeData(self._node.at("ShakeData"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




