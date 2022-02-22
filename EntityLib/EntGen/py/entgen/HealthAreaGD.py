
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class HealthAreaGD(HelperObject):
    schema_name = "HealthAreaGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealthAreaGD
        return HealthAreaGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealthAreaGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealthAreaGD
        return HealthAreaGD(entlib.make_node(HealthAreaGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyRestorationRate(self):  # type: ()->Float
        return Float(self._node.at("EnergyRestorationRate"))
    @EnergyRestorationRate.setter
    def EnergyRestorationRate(self, val): self.EnergyRestorationRate.set(val)
    @property
    def FactionSide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("FactionSide"))
    @FactionSide.setter
    def FactionSide(self, val): self.FactionSide.set(val)
    @property
    def LifeRestorationRate(self):  # type: ()->Float
        return Float(self._node.at("LifeRestorationRate"))
    @LifeRestorationRate.setter
    def LifeRestorationRate(self, val): self.LifeRestorationRate.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def ReviveRestorationRate(self):  # type: ()->Float
        return Float(self._node.at("ReviveRestorationRate"))
    @ReviveRestorationRate.setter
    def ReviveRestorationRate(self, val): self.ReviveRestorationRate.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




