
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.FluidVolumeComponentGD_HeightMapData import *
from entgen.FluidVolumeComponentGD_SimulationParameters import *
from entgen.Vector2 import *


class FluidVolumeComponentGD_FluidVolumeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::FluidVolumeData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_FluidVolumeData.schema_name))
    @property
    def HeightMap(self): return FluidVolumeComponentGD_HeightMapData(self._node.at("HeightMap"))
    @property
    def InHeightMapWorldSizeOffset(self): return Vector2(self._node.at("InHeightMapWorldSizeOffset"))
    @InHeightMapWorldSizeOffset.setter
    def InHeightMapWorldSizeOffset(self, val): self.InHeightMapWorldSizeOffset.set(val)
    @property
    def Material(self): return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def Simulation(self): return FluidVolumeComponentGD_SimulationParameters(self._node.at("Simulation"))
    @property
    def WorldSize(self): return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




