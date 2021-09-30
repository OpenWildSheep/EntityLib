
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class FluidVolumeComponentGD_SimulationParameters(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::SimulationParameters"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_SimulationParameters.schema_name))
    @property
    def Evaporation(self): return Float(self._node.at("Evaporation"))
    @Evaporation.setter
    def Evaporation(self, val): self.Evaporation.set(val)
    @property
    def Momentum(self): return Float(self._node.at("Momentum"))
    @Momentum.setter
    def Momentum(self, val): self.Momentum.set(val)
    @property
    def Precision(self): return Float(self._node.at("Precision"))
    @Precision.setter
    def Precision(self, val): self.Precision.set(val)
    @property
    def Viscosity(self): return Float(self._node.at("Viscosity"))
    @Viscosity.setter
    def Viscosity(self, val): self.Viscosity.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




