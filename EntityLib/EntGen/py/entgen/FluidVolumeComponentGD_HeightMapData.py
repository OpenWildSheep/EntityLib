
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *

from EntityLibPy import Node

class FluidVolumeComponentGD_HeightMapData(HelperObject):
    schema_name = "FluidVolumeComponentGD::HeightMapData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD_HeightMapData
        return FluidVolumeComponentGD_HeightMapData(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_HeightMapData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD_HeightMapData
        return FluidVolumeComponentGD_HeightMapData(entlib.make_node(FluidVolumeComponentGD_HeightMapData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Path(self):  # type: ()->String
        return String(self._node.at("Path"))
    @Path.setter
    def Path(self, val): self.Path.set(val)
    @property
    def TerrainName(self):  # type: ()->String
        return String(self._node.at("TerrainName"))
    @TerrainName.setter
    def TerrainName(self, val): self.TerrainName.set(val)
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




