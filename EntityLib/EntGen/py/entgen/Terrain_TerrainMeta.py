
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class Terrain_TerrainMeta(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Terrain::TerrainMeta"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(Terrain_TerrainMeta.schema_name))
    @property
    def DataPath(self): return String(self._node.at("DataPath"))
    @DataPath.setter
    def DataPath(self, val): self.DataPath.set(val)
    @property
    def HeightScaleMeters(self): return Float(self._node.at("HeightScaleMeters"))
    @HeightScaleMeters.setter
    def HeightScaleMeters(self, val): self.HeightScaleMeters.set(val)
    @property
    def Material(self): return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def RegionWidthMeters(self): return Float(self._node.at("RegionWidthMeters"))
    @RegionWidthMeters.setter
    def RegionWidthMeters(self, val): self.RegionWidthMeters.set(val)
    @property
    def SkirtScale(self): return Float(self._node.at("SkirtScale"))
    @SkirtScale.setter
    def SkirtScale(self, val): self.SkirtScale.set(val)
    @property
    def TexelsPerMeter(self): return Float(self._node.at("TexelsPerMeter"))
    @TexelsPerMeter.setter
    def TexelsPerMeter(self, val): self.TexelsPerMeter.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




