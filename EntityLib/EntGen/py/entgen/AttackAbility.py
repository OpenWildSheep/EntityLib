
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CameraShakeData import *
from entgen.Float import *
from entgen.FreezeData import *

from EntityLibPy import Node

class AttackAbility(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackAbility"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackAbility
        return AttackAbility(entlib.load_node_file(sourcefile, entlib.get_schema(AttackAbility.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackAbility
        return AttackAbility(entlib.make_node(AttackAbility.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Damage(self):  # type: ()->Float
        return Float(self._node.at("Damage"))
    @Damage.setter
    def Damage(self, val): self.Damage.set(val)
    @property
    def DistanceMax(self):  # type: ()->Float
        return Float(self._node.at("DistanceMax"))
    @DistanceMax.setter
    def DistanceMax(self, val): self.DistanceMax.set(val)
    @property
    def DistanceMin(self):  # type: ()->Float
        return Float(self._node.at("DistanceMin"))
    @DistanceMin.setter
    def DistanceMin(self, val): self.DistanceMin.set(val)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def EnergyCost(self):  # type: ()->Float
        return Float(self._node.at("EnergyCost"))
    @EnergyCost.setter
    def EnergyCost(self, val): self.EnergyCost.set(val)
    @property
    def FreezeData(self):  # type: ()->FreezeData
        return FreezeData(self._node.at("FreezeData"))
    @property
    def Impact(self):  # type: ()->Float
        return Float(self._node.at("Impact"))
    @Impact.setter
    def Impact(self, val): self.Impact.set(val)
    @property
    def ShakeData(self):  # type: ()->CameraShakeData
        return CameraShakeData(self._node.at("ShakeData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




