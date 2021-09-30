
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.String import *


class NavmeshGenerationParameters(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/NavmeshGenerationParameters"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(NavmeshGenerationParameters.schema_name))
    @property
    def CreatureHeight(self): return Float(self._node.at("CreatureHeight"))
    @CreatureHeight.setter
    def CreatureHeight(self, val): self.CreatureHeight.set(val)
    @property
    def CreatureRadius(self): return Float(self._node.at("CreatureRadius"))
    @CreatureRadius.setter
    def CreatureRadius(self, val): self.CreatureRadius.set(val)
    @property
    def MarkWaterAreas(self): return Bool(self._node.at("MarkWaterAreas"))
    @MarkWaterAreas.setter
    def MarkWaterAreas(self, val): self.MarkWaterAreas.set(val)
    @property
    def MaxClimbHeight(self): return Float(self._node.at("MaxClimbHeight"))
    @MaxClimbHeight.setter
    def MaxClimbHeight(self, val): self.MaxClimbHeight.set(val)
    @property
    def MaxWalkableSlopeAngle(self): return Float(self._node.at("MaxWalkableSlopeAngle"))
    @MaxWalkableSlopeAngle.setter
    def MaxWalkableSlopeAngle(self, val): self.MaxWalkableSlopeAngle.set(val)
    @property
    def MinWaterDepth(self): return Float(self._node.at("MinWaterDepth"))
    @MinWaterDepth.setter
    def MinWaterDepth(self, val): self.MinWaterDepth.set(val)
    @property
    def SizeLayerMask(self): return (lambda n: PrimArray(String, n))(self._node.at("SizeLayerMask"))
    @SizeLayerMask.setter
    def SizeLayerMask(self, val): self.SizeLayerMask.set(val)
    @property
    def TileWorldSize(self): return Float(self._node.at("TileWorldSize"))
    @TileWorldSize.setter
    def TileWorldSize(self, val): self.TileWorldSize.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




