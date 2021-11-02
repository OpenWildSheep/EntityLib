
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class Terrain_TerrainMeta(HelperObject):
    schema_name = "Terrain::TerrainMeta"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Terrain_TerrainMeta
        return Terrain_TerrainMeta(entlib.load_node_file(sourcefile, entlib.get_schema(Terrain_TerrainMeta.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Terrain_TerrainMeta
        return Terrain_TerrainMeta(entlib.make_node(Terrain_TerrainMeta.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DataPath(self):  # type: ()->String
        return String(self._node.at("DataPath"))
    @DataPath.setter
    def DataPath(self, val): self.DataPath.set(val)
    @property
    def HeightScaleMeters(self):  # type: ()->Float
        return Float(self._node.at("HeightScaleMeters"))
    @HeightScaleMeters.setter
    def HeightScaleMeters(self, val): self.HeightScaleMeters.set(val)
    @property
    def Material(self):  # type: ()->String
        return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def RegionWidthMeters(self):  # type: ()->Float
        return Float(self._node.at("RegionWidthMeters"))
    @RegionWidthMeters.setter
    def RegionWidthMeters(self, val): self.RegionWidthMeters.set(val)
    @property
    def RimTerrain(self):  # type: ()->Bool
        return Bool(self._node.at("RimTerrain"))
    @RimTerrain.setter
    def RimTerrain(self, val): self.RimTerrain.set(val)
    @property
    def SkirtScale(self):  # type: ()->Float
        return Float(self._node.at("SkirtScale"))
    @SkirtScale.setter
    def SkirtScale(self, val): self.SkirtScale.set(val)
    @property
    def TexelsPerMeter(self):  # type: ()->Float
        return Float(self._node.at("TexelsPerMeter"))
    @TexelsPerMeter.setter
    def TexelsPerMeter(self, val): self.TexelsPerMeter.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




