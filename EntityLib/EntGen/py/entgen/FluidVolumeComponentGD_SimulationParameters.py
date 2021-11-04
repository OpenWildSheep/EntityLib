
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class FluidVolumeComponentGD_SimulationParameters(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::SimulationParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD_SimulationParameters
        return FluidVolumeComponentGD_SimulationParameters(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_SimulationParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD_SimulationParameters
        return FluidVolumeComponentGD_SimulationParameters(entlib.make_node(FluidVolumeComponentGD_SimulationParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Evaporation(self):  # type: ()->Float
        return Float(self._node.at("Evaporation"))
    @Evaporation.setter
    def Evaporation(self, val): self.Evaporation.set(val)
    @property
    def Momentum(self):  # type: ()->Float
        return Float(self._node.at("Momentum"))
    @Momentum.setter
    def Momentum(self, val): self.Momentum.set(val)
    @property
    def Precision(self):  # type: ()->Float
        return Float(self._node.at("Precision"))
    @Precision.setter
    def Precision(self, val): self.Precision.set(val)
    @property
    def Viscosity(self):  # type: ()->Float
        return Float(self._node.at("Viscosity"))
    @Viscosity.setter
    def Viscosity(self, val): self.Viscosity.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




