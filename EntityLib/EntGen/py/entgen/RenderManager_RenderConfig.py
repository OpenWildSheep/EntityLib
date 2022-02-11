
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AaMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class RenderManager_RenderConfig(HelperObject):
    schema_name = "RenderManager::RenderConfig"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RenderManager_RenderConfig
        return RenderManager_RenderConfig(entlib.load_node_file(sourcefile, entlib.get_schema(RenderManager_RenderConfig.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RenderManager_RenderConfig
        return RenderManager_RenderConfig(entlib.make_node(RenderManager_RenderConfig.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AaMode(self):  # type: ()->AaMode
        return AaMode(self._node.at("AaMode"))
    @AaMode.setter
    def AaMode(self, val): self.AaMode.set(val)
    @property
    def ClusteredLighting(self):  # type: ()->Int
        return Int(self._node.at("ClusteredLighting"))
    @ClusteredLighting.setter
    def ClusteredLighting(self, val): self.ClusteredLighting.set(val)
    @property
    def DisplacementMapSize(self):  # type: ()->Int
        return Int(self._node.at("DisplacementMapSize"))
    @DisplacementMapSize.setter
    def DisplacementMapSize(self, val): self.DisplacementMapSize.set(val)
    @property
    def EnableAsyncPipelineCreation(self):  # type: ()->Int
        return Int(self._node.at("EnableAsyncPipelineCreation"))
    @EnableAsyncPipelineCreation.setter
    def EnableAsyncPipelineCreation(self, val): self.EnableAsyncPipelineCreation.set(val)
    @property
    def EnableColorCorrection(self):  # type: ()->Int
        return Int(self._node.at("EnableColorCorrection"))
    @EnableColorCorrection.setter
    def EnableColorCorrection(self, val): self.EnableColorCorrection.set(val)
    @property
    def EnableComputeForDeferredLighting(self):  # type: ()->Int
        return Int(self._node.at("EnableComputeForDeferredLighting"))
    @EnableComputeForDeferredLighting.setter
    def EnableComputeForDeferredLighting(self, val): self.EnableComputeForDeferredLighting.set(val)
    @property
    def EnableComputeForUnderWater(self):  # type: ()->Int
        return Int(self._node.at("EnableComputeForUnderWater"))
    @EnableComputeForUnderWater.setter
    def EnableComputeForUnderWater(self, val): self.EnableComputeForUnderWater.set(val)
    @property
    def EnableDepthOfField(self):  # type: ()->Int
        return Int(self._node.at("EnableDepthOfField"))
    @EnableDepthOfField.setter
    def EnableDepthOfField(self, val): self.EnableDepthOfField.set(val)
    @property
    def EnableLensFlare(self):  # type: ()->Int
        return Int(self._node.at("EnableLensFlare"))
    @EnableLensFlare.setter
    def EnableLensFlare(self, val): self.EnableLensFlare.set(val)
    @property
    def EnableMTR(self):  # type: ()->Int
        return Int(self._node.at("EnableMTR"))
    @EnableMTR.setter
    def EnableMTR(self, val): self.EnableMTR.set(val)
    @property
    def EnableMotionBlur(self):  # type: ()->Int
        return Int(self._node.at("EnableMotionBlur"))
    @EnableMotionBlur.setter
    def EnableMotionBlur(self, val): self.EnableMotionBlur.set(val)
    @property
    def EnableNonBlockingDrawUpdates(self):  # type: ()->Int
        return Int(self._node.at("EnableNonBlockingDrawUpdates"))
    @EnableNonBlockingDrawUpdates.setter
    def EnableNonBlockingDrawUpdates(self, val): self.EnableNonBlockingDrawUpdates.set(val)
    @property
    def EnableSSAO(self):  # type: ()->Int
        return Int(self._node.at("EnableSSAO"))
    @EnableSSAO.setter
    def EnableSSAO(self, val): self.EnableSSAO.set(val)
    @property
    def EnableSSR(self):  # type: ()->Int
        return Int(self._node.at("EnableSSR"))
    @EnableSSR.setter
    def EnableSSR(self, val): self.EnableSSR.set(val)
    @property
    def EnableSSSS(self):  # type: ()->Int
        return Int(self._node.at("EnableSSSS"))
    @EnableSSSS.setter
    def EnableSSSS(self, val): self.EnableSSSS.set(val)
    @property
    def EnableTonemapping(self):  # type: ()->Int
        return Int(self._node.at("EnableTonemapping"))
    @EnableTonemapping.setter
    def EnableTonemapping(self, val): self.EnableTonemapping.set(val)
    @property
    def EnableUnderwaterPostEffect(self):  # type: ()->Int
        return Int(self._node.at("EnableUnderwaterPostEffect"))
    @EnableUnderwaterPostEffect.setter
    def EnableUnderwaterPostEffect(self, val): self.EnableUnderwaterPostEffect.set(val)
    @property
    def GlobalLODBias(self):  # type: ()->Float
        return Float(self._node.at("GlobalLODBias"))
    @GlobalLODBias.setter
    def GlobalLODBias(self, val): self.GlobalLODBias.set(val)
    @property
    def GlobalLODScale(self):  # type: ()->Float
        return Float(self._node.at("GlobalLODScale"))
    @GlobalLODScale.setter
    def GlobalLODScale(self, val): self.GlobalLODScale.set(val)
    @property
    def LODDecimationFactor(self):  # type: ()->Float
        return Float(self._node.at("LODDecimationFactor"))
    @LODDecimationFactor.setter
    def LODDecimationFactor(self, val): self.LODDecimationFactor.set(val)
    @property
    def MaterialBank(self):  # type: ()->String
        return String(self._node.at("MaterialBank"))
    @MaterialBank.setter
    def MaterialBank(self, val): self.MaterialBank.set(val)
    @property
    def MaxActiveShadowLights(self):  # type: ()->Int
        return Int(self._node.at("MaxActiveShadowLights"))
    @MaxActiveShadowLights.setter
    def MaxActiveShadowLights(self, val): self.MaxActiveShadowLights.set(val)
    @property
    def MinTriangleSize(self):  # type: ()->Float
        return Float(self._node.at("MinTriangleSize"))
    @MinTriangleSize.setter
    def MinTriangleSize(self, val): self.MinTriangleSize.set(val)
    @property
    def ParticleLigthingAtlasSize(self):  # type: ()->Int
        return Int(self._node.at("ParticleLigthingAtlasSize"))
    @ParticleLigthingAtlasSize.setter
    def ParticleLigthingAtlasSize(self, val): self.ParticleLigthingAtlasSize.set(val)
    @property
    def PlanarReflectionsDownsample(self):  # type: ()->Int
        return Int(self._node.at("PlanarReflectionsDownsample"))
    @PlanarReflectionsDownsample.setter
    def PlanarReflectionsDownsample(self, val): self.PlanarReflectionsDownsample.set(val)
    @property
    def Quality(self):  # type: ()->Int
        return Int(self._node.at("Quality"))
    @Quality.setter
    def Quality(self, val): self.Quality.set(val)
    @property
    def QualityDepthOfField(self):  # type: ()->Int
        return Int(self._node.at("QualityDepthOfField"))
    @QualityDepthOfField.setter
    def QualityDepthOfField(self, val): self.QualityDepthOfField.set(val)
    @property
    def RippleMapSize(self):  # type: ()->Int
        return Int(self._node.at("RippleMapSize"))
    @RippleMapSize.setter
    def RippleMapSize(self, val): self.RippleMapSize.set(val)
    @property
    def SamplesSSAO(self):  # type: ()->Int
        return Int(self._node.at("SamplesSSAO"))
    @SamplesSSAO.setter
    def SamplesSSAO(self, val): self.SamplesSSAO.set(val)
    @property
    def SamplesSSSS(self):  # type: ()->Int
        return Int(self._node.at("SamplesSSSS"))
    @SamplesSSSS.setter
    def SamplesSSSS(self, val): self.SamplesSSSS.set(val)
    @property
    def ShadowLODScale(self):  # type: ()->Float
        return Float(self._node.at("ShadowLODScale"))
    @ShadowLODScale.setter
    def ShadowLODScale(self, val): self.ShadowLODScale.set(val)
    @property
    def ShadowMapSize(self):  # type: ()->Int
        return Int(self._node.at("ShadowMapSize"))
    @ShadowMapSize.setter
    def ShadowMapSize(self, val): self.ShadowMapSize.set(val)
    @property
    def TerrainAlbedoMapBlendAreaRatio(self):  # type: ()->Float
        return Float(self._node.at("TerrainAlbedoMapBlendAreaRatio"))
    @TerrainAlbedoMapBlendAreaRatio.setter
    def TerrainAlbedoMapBlendAreaRatio(self, val): self.TerrainAlbedoMapBlendAreaRatio.set(val)
    @property
    def TerrainAlbedoMapExtent(self):  # type: ()->Float
        return Float(self._node.at("TerrainAlbedoMapExtent"))
    @TerrainAlbedoMapExtent.setter
    def TerrainAlbedoMapExtent(self, val): self.TerrainAlbedoMapExtent.set(val)
    @property
    def UseHiZBufferForClusteredLighting(self):  # type: ()->Int
        return Int(self._node.at("UseHiZBufferForClusteredLighting"))
    @UseHiZBufferForClusteredLighting.setter
    def UseHiZBufferForClusteredLighting(self, val): self.UseHiZBufferForClusteredLighting.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




