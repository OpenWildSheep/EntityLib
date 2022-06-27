
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class RecastNavmeshGenerationParameters(HelperObject):
    schema_name = "RecastNavmeshGenerationParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RecastNavmeshGenerationParameters
        return RecastNavmeshGenerationParameters(entlib.load_node_file(sourcefile, entlib.get_schema(RecastNavmeshGenerationParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RecastNavmeshGenerationParameters
        return RecastNavmeshGenerationParameters(entlib.make_node(RecastNavmeshGenerationParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CreatureHeight(self):  # type: ()->Float
        return Float(self._node.at("CreatureHeight"))
    @CreatureHeight.setter
    def CreatureHeight(self, val): self.CreatureHeight.set(val)
    @property
    def CreatureRadius(self):  # type: ()->Float
        return Float(self._node.at("CreatureRadius"))
    @CreatureRadius.setter
    def CreatureRadius(self, val): self.CreatureRadius.set(val)
    @property
    def CreatureType(self):  # type: ()->String
        return String(self._node.at("CreatureType"))
    @CreatureType.setter
    def CreatureType(self, val): self.CreatureType.set(val)
    @property
    def DeepWaterDepth(self):  # type: ()->Float
        return Float(self._node.at("DeepWaterDepth"))
    @DeepWaterDepth.setter
    def DeepWaterDepth(self, val): self.DeepWaterDepth.set(val)
    @property
    def MarkWaterAreas(self):  # type: ()->Bool
        return Bool(self._node.at("MarkWaterAreas"))
    @MarkWaterAreas.setter
    def MarkWaterAreas(self, val): self.MarkWaterAreas.set(val)
    @property
    def MaxClimbHeight(self):  # type: ()->Float
        return Float(self._node.at("MaxClimbHeight"))
    @MaxClimbHeight.setter
    def MaxClimbHeight(self, val): self.MaxClimbHeight.set(val)
    @property
    def MaxWalkableSlopeAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxWalkableSlopeAngle"))
    @MaxWalkableSlopeAngle.setter
    def MaxWalkableSlopeAngle(self, val): self.MaxWalkableSlopeAngle.set(val)
    @property
    def MinWaterDepth(self):  # type: ()->Float
        return Float(self._node.at("MinWaterDepth"))
    @MinWaterDepth.setter
    def MinWaterDepth(self, val): self.MinWaterDepth.set(val)
    @property
    def VoxelPrecision(self):  # type: ()->Float
        return Float(self._node.at("VoxelPrecision"))
    @VoxelPrecision.setter
    def VoxelPrecision(self, val): self.VoxelPrecision.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




