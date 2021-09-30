
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class HealthAreaGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealthAreaGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(HealthAreaGD.schema_name))
    @property
    def EnergyRestorationRate(self): return Float(self._node.at("EnergyRestorationRate"))
    @EnergyRestorationRate.setter
    def EnergyRestorationRate(self, val): self.EnergyRestorationRate.set(val)
    @property
    def FactionSide(self): return ReviveSide(self._node.at("FactionSide"))
    @FactionSide.setter
    def FactionSide(self, val): self.FactionSide.set(val)
    @property
    def LifeRestorationRate(self): return Float(self._node.at("LifeRestorationRate"))
    @LifeRestorationRate.setter
    def LifeRestorationRate(self, val): self.LifeRestorationRate.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def ReviveRestorationRate(self): return Float(self._node.at("ReviveRestorationRate"))
    @ReviveRestorationRate.setter
    def ReviveRestorationRate(self, val): self.ReviveRestorationRate.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




