
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class ReviveEnergyGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveEnergyGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ReviveEnergyGD.schema_name))
    @property
    def EnergyMinNeutral(self): return Float(self._node.at("EnergyMinNeutral"))
    @EnergyMinNeutral.setter
    def EnergyMinNeutral(self, val): self.EnergyMinNeutral.set(val)
    @property
    def HatchingEnergyMinHysteresis(self): return Float(self._node.at("HatchingEnergyMinHysteresis"))
    @HatchingEnergyMinHysteresis.setter
    def HatchingEnergyMinHysteresis(self, val): self.HatchingEnergyMinHysteresis.set(val)
    @property
    def HatchingFightBackSpeedModifier(self): return Float(self._node.at("HatchingFightBackSpeedModifier"))
    @HatchingFightBackSpeedModifier.setter
    def HatchingFightBackSpeedModifier(self, val): self.HatchingFightBackSpeedModifier.set(val)
    @property
    def HatchingMaxDuration(self): return Float(self._node.at("HatchingMaxDuration"))
    @HatchingMaxDuration.setter
    def HatchingMaxDuration(self, val): self.HatchingMaxDuration.set(val)
    @property
    def HatchingMinDuration(self): return Float(self._node.at("HatchingMinDuration"))
    @HatchingMinDuration.setter
    def HatchingMinDuration(self, val): self.HatchingMinDuration.set(val)
    @property
    def InitEnergy(self): return Float(self._node.at("InitEnergy"))
    @InitEnergy.setter
    def InitEnergy(self, val): self.InitEnergy.set(val)
    @property
    def InitReviveSide(self): return ReviveSide(self._node.at("InitReviveSide"))
    @InitReviveSide.setter
    def InitReviveSide(self, val): self.InitReviveSide.set(val)
    @property
    def MaxEnergy(self): return Float(self._node.at("MaxEnergy"))
    @MaxEnergy.setter
    def MaxEnergy(self, val): self.MaxEnergy.set(val)
    @property
    def MaxWaitingTime(self): return Float(self._node.at("MaxWaitingTime"))
    @MaxWaitingTime.setter
    def MaxWaitingTime(self, val): self.MaxWaitingTime.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




