
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class ReviveEnergyGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveEnergyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveEnergyGD
        return ReviveEnergyGD(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveEnergyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveEnergyGD
        return ReviveEnergyGD(entlib.make_node(ReviveEnergyGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyMinNeutral(self):  # type: ()->Float
        return Float(self._node.at("EnergyMinNeutral"))
    @EnergyMinNeutral.setter
    def EnergyMinNeutral(self, val): self.EnergyMinNeutral.set(val)
    @property
    def HatchingCostsEnergy(self):  # type: ()->Bool
        return Bool(self._node.at("HatchingCostsEnergy"))
    @HatchingCostsEnergy.setter
    def HatchingCostsEnergy(self, val): self.HatchingCostsEnergy.set(val)
    @property
    def HatchingEnergyMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("HatchingEnergyMinHysteresis"))
    @HatchingEnergyMinHysteresis.setter
    def HatchingEnergyMinHysteresis(self, val): self.HatchingEnergyMinHysteresis.set(val)
    @property
    def HatchingMaxDuration(self):  # type: ()->Float
        return Float(self._node.at("HatchingMaxDuration"))
    @HatchingMaxDuration.setter
    def HatchingMaxDuration(self, val): self.HatchingMaxDuration.set(val)
    @property
    def InitEnergy(self):  # type: ()->Float
        return Float(self._node.at("InitEnergy"))
    @InitEnergy.setter
    def InitEnergy(self, val): self.InitEnergy.set(val)
    @property
    def InitReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("InitReviveSide"))
    @InitReviveSide.setter
    def InitReviveSide(self, val): self.InitReviveSide.set(val)
    @property
    def MaxEnergy(self):  # type: ()->Float
        return Float(self._node.at("MaxEnergy"))
    @MaxEnergy.setter
    def MaxEnergy(self, val): self.MaxEnergy.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TimeBetweenShot(self):  # type: ()->Float
        return Float(self._node.at("TimeBetweenShot"))
    @TimeBetweenShot.setter
    def TimeBetweenShot(self, val): self.TimeBetweenShot.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




