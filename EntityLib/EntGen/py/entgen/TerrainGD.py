
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Terrain_TerrainMeta import *


class TerrainGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/TerrainGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TerrainGD.schema_name))
    @property
    def EDITOR_AlbedoType(self): return Int(self._node.at("EDITOR_AlbedoType"))
    @EDITOR_AlbedoType.setter
    def EDITOR_AlbedoType(self, val): self.EDITOR_AlbedoType.set(val)
    @property
    def EDITOR_CavityAlbedoStrength(self): return Float(self._node.at("EDITOR_CavityAlbedoStrength"))
    @EDITOR_CavityAlbedoStrength.setter
    def EDITOR_CavityAlbedoStrength(self, val): self.EDITOR_CavityAlbedoStrength.set(val)
    @property
    def EDITOR_CavityStrength(self): return Float(self._node.at("EDITOR_CavityStrength"))
    @EDITOR_CavityStrength.setter
    def EDITOR_CavityStrength(self, val): self.EDITOR_CavityStrength.set(val)
    @property
    def EDITOR_CollisionDecimateHmm(self): return Float(self._node.at("EDITOR_CollisionDecimateHmm"))
    @EDITOR_CollisionDecimateHmm.setter
    def EDITOR_CollisionDecimateHmm(self, val): self.EDITOR_CollisionDecimateHmm.set(val)
    @property
    def EDITOR_ComputeSurfaceObjectTerrain(self): return Bool(self._node.at("EDITOR_ComputeSurfaceObjectTerrain"))
    @EDITOR_ComputeSurfaceObjectTerrain.setter
    def EDITOR_ComputeSurfaceObjectTerrain(self, val): self.EDITOR_ComputeSurfaceObjectTerrain.set(val)
    @property
    def EDITOR_DebugMode(self): return Bool(self._node.at("EDITOR_DebugMode"))
    @EDITOR_DebugMode.setter
    def EDITOR_DebugMode(self, val): self.EDITOR_DebugMode.set(val)
    @property
    def EDITOR_DetailMapFalloff(self): return Int(self._node.at("EDITOR_DetailMapFalloff"))
    @EDITOR_DetailMapFalloff.setter
    def EDITOR_DetailMapFalloff(self, val): self.EDITOR_DetailMapFalloff.set(val)
    @property
    def EDITOR_DetailScale(self): return Float(self._node.at("EDITOR_DetailScale"))
    @EDITOR_DetailScale.setter
    def EDITOR_DetailScale(self, val): self.EDITOR_DetailScale.set(val)
    @property
    def EDITOR_DisableSeedParams(self): return Bool(self._node.at("EDITOR_DisableSeedParams"))
    @EDITOR_DisableSeedParams.setter
    def EDITOR_DisableSeedParams(self, val): self.EDITOR_DisableSeedParams.set(val)
    @property
    def EDITOR_DisplayAlbedo(self): return Bool(self._node.at("EDITOR_DisplayAlbedo"))
    @EDITOR_DisplayAlbedo.setter
    def EDITOR_DisplayAlbedo(self, val): self.EDITOR_DisplayAlbedo.set(val)
    @property
    def EDITOR_DisplayFinal(self): return Bool(self._node.at("EDITOR_DisplayFinal"))
    @EDITOR_DisplayFinal.setter
    def EDITOR_DisplayFinal(self, val): self.EDITOR_DisplayFinal.set(val)
    @property
    def EDITOR_Distributed(self): return Bool(self._node.at("EDITOR_Distributed"))
    @EDITOR_Distributed.setter
    def EDITOR_Distributed(self, val): self.EDITOR_Distributed.set(val)
    @property
    def EDITOR_Erosion(self): return Bool(self._node.at("EDITOR_Erosion"))
    @EDITOR_Erosion.setter
    def EDITOR_Erosion(self, val): self.EDITOR_Erosion.set(val)
    @property
    def EDITOR_ErosionType(self): return Int(self._node.at("EDITOR_ErosionType"))
    @EDITOR_ErosionType.setter
    def EDITOR_ErosionType(self, val): self.EDITOR_ErosionType.set(val)
    @property
    def EDITOR_ExportCollision(self): return Bool(self._node.at("EDITOR_ExportCollision"))
    @EDITOR_ExportCollision.setter
    def EDITOR_ExportCollision(self, val): self.EDITOR_ExportCollision.set(val)
    @property
    def EDITOR_ExportQuality(self): return Int(self._node.at("EDITOR_ExportQuality"))
    @EDITOR_ExportQuality.setter
    def EDITOR_ExportQuality(self, val): self.EDITOR_ExportQuality.set(val)
    @property
    def EDITOR_LocalSndbs(self): return Bool(self._node.at("EDITOR_LocalSndbs"))
    @EDITOR_LocalSndbs.setter
    def EDITOR_LocalSndbs(self, val): self.EDITOR_LocalSndbs.set(val)
    @property
    def EDITOR_MergeTSOPreview(self): return Bool(self._node.at("EDITOR_MergeTSOPreview"))
    @EDITOR_MergeTSOPreview.setter
    def EDITOR_MergeTSOPreview(self, val): self.EDITOR_MergeTSOPreview.set(val)
    @property
    def EDITOR_MultiLayerHeightmap(self): return Bool(self._node.at("EDITOR_MultiLayerHeightmap"))
    @EDITOR_MultiLayerHeightmap.setter
    def EDITOR_MultiLayerHeightmap(self, val): self.EDITOR_MultiLayerHeightmap.set(val)
    @property
    def EDITOR_Path(self): return String(self._node.at("EDITOR_Path"))
    @EDITOR_Path.setter
    def EDITOR_Path(self, val): self.EDITOR_Path.set(val)
    @property
    def EDITOR_PreviewQuality(self): return Int(self._node.at("EDITOR_PreviewQuality"))
    @EDITOR_PreviewQuality.setter
    def EDITOR_PreviewQuality(self, val): self.EDITOR_PreviewQuality.set(val)
    @property
    def EDITOR_ProcessDetailMap(self): return Bool(self._node.at("EDITOR_ProcessDetailMap"))
    @EDITOR_ProcessDetailMap.setter
    def EDITOR_ProcessDetailMap(self, val): self.EDITOR_ProcessDetailMap.set(val)
    @property
    def EDITOR_SeedTextureSizeReduce(self): return Int(self._node.at("EDITOR_SeedTextureSizeReduce"))
    @EDITOR_SeedTextureSizeReduce.setter
    def EDITOR_SeedTextureSizeReduce(self, val): self.EDITOR_SeedTextureSizeReduce.set(val)
    @property
    def EDITOR_SuperimposeSeeds(self): return Bool(self._node.at("EDITOR_SuperimposeSeeds"))
    @EDITOR_SuperimposeSeeds.setter
    def EDITOR_SuperimposeSeeds(self, val): self.EDITOR_SuperimposeSeeds.set(val)
    @property
    def EDITOR_SurfaceObjectDecimate(self): return Float(self._node.at("EDITOR_SurfaceObjectDecimate"))
    @EDITOR_SurfaceObjectDecimate.setter
    def EDITOR_SurfaceObjectDecimate(self, val): self.EDITOR_SurfaceObjectDecimate.set(val)
    @property
    def EDITOR_SurfaceObjectDecimateHmm(self): return Float(self._node.at("EDITOR_SurfaceObjectDecimateHmm"))
    @EDITOR_SurfaceObjectDecimateHmm.setter
    def EDITOR_SurfaceObjectDecimateHmm(self, val): self.EDITOR_SurfaceObjectDecimateHmm.set(val)
    @property
    def EDITOR_TerrainWildMat(self): return String(self._node.at("EDITOR_TerrainWildMat"))
    @EDITOR_TerrainWildMat.setter
    def EDITOR_TerrainWildMat(self, val): self.EDITOR_TerrainWildMat.set(val)
    @property
    def EDITOR_TriPerMeter(self): return Int(self._node.at("EDITOR_TriPerMeter"))
    @EDITOR_TriPerMeter.setter
    def EDITOR_TriPerMeter(self, val): self.EDITOR_TriPerMeter.set(val)
    @property
    def EDITOR_WMErosionComputeDistant(self): return Bool(self._node.at("EDITOR_WMErosionComputeDistant"))
    @EDITOR_WMErosionComputeDistant.setter
    def EDITOR_WMErosionComputeDistant(self, val): self.EDITOR_WMErosionComputeDistant.set(val)
    @property
    def EDITOR_WMErosionPreview(self): return Bool(self._node.at("EDITOR_WMErosionPreview"))
    @EDITOR_WMErosionPreview.setter
    def EDITOR_WMErosionPreview(self, val): self.EDITOR_WMErosionPreview.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def TerrainMeta(self): return Terrain_TerrainMeta(self._node.at("TerrainMeta"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




