
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *


class FluidVolumeComponentGD_HeightMapData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::HeightMapData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_HeightMapData.schema_name))
    @property
    def Path(self): return String(self._node.at("Path"))
    @Path.setter
    def Path(self, val): self.Path.set(val)
    @property
    def TerrainName(self): return String(self._node.at("TerrainName"))
    @TerrainName.setter
    def TerrainName(self, val): self.TerrainName.set(val)
    @property
    def WorldSize(self): return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




