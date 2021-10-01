
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.FluidVolumeComponentGD_HeightMapData import *
from entgen.FluidVolumeComponentGD_SimulationParameters import *
from entgen.Vector2 import *

from EntityLibPy import Node

class FluidVolumeComponentGD_FluidVolumeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::FluidVolumeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD_FluidVolumeData
        return FluidVolumeComponentGD_FluidVolumeData(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_FluidVolumeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD_FluidVolumeData
        return FluidVolumeComponentGD_FluidVolumeData(entlib.make_node(FluidVolumeComponentGD_FluidVolumeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HeightMap(self):  # type: ()->FluidVolumeComponentGD_HeightMapData
        return FluidVolumeComponentGD_HeightMapData(self._node.at("HeightMap"))
    @property
    def InHeightMapWorldSizeOffset(self):  # type: ()->Vector2
        return Vector2(self._node.at("InHeightMapWorldSizeOffset"))
    @InHeightMapWorldSizeOffset.setter
    def InHeightMapWorldSizeOffset(self, val): self.InHeightMapWorldSizeOffset.set(val)
    @property
    def Material(self):  # type: ()->String
        return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def Simulation(self):  # type: ()->FluidVolumeComponentGD_SimulationParameters
        return FluidVolumeComponentGD_SimulationParameters(self._node.at("Simulation"))
    @property
    def WorldSize(self):  # type: ()->Vector2
        return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




