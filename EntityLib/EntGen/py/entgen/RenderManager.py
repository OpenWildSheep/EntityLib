
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *
from entgen.RenderManager_DepthOfFieldConfig import *
from entgen.RenderManager_RenderConfig import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class RenderManager(HelperObject):
    schema_name = "RenderManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RenderManager
        return RenderManager(entlib.load_node_file(sourcefile, entlib.get_schema(RenderManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RenderManager
        return RenderManager(entlib.make_node(RenderManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DecalMeshPath(self):  # type: ()->String
        return String(self._node.at("DecalMeshPath"))
    @DecalMeshPath.setter
    def DecalMeshPath(self, val): self.DecalMeshPath.set(val)
    @property
    def DepthOfField(self):  # type: ()->RenderManager_DepthOfFieldConfig
        return RenderManager_DepthOfFieldConfig(self._node.at("DepthOfField"))
    @property
    def DisableMoveDrawOrigin(self):  # type: ()->Bool
        return Bool(self._node.at("DisableMoveDrawOrigin"))
    @DisableMoveDrawOrigin.setter
    def DisableMoveDrawOrigin(self, val): self.DisableMoveDrawOrigin.set(val)
    @property
    def DoubleSizeIn4K(self):  # type: ()->Bool
        return Bool(self._node.at("DoubleSizeIn4K"))
    @DoubleSizeIn4K.setter
    def DoubleSizeIn4K(self, val): self.DoubleSizeIn4K.set(val)
    @property
    def EnableFade(self):  # type: ()->Bool
        return Bool(self._node.at("EnableFade"))
    @EnableFade.setter
    def EnableFade(self, val): self.EnableFade.set(val)
    @property
    def EnableLODTransitions(self):  # type: ()->Bool
        return Bool(self._node.at("EnableLODTransitions"))
    @EnableLODTransitions.setter
    def EnableLODTransitions(self, val): self.EnableLODTransitions.set(val)
    @property
    def FloatPrecisionThreshold(self):  # type: ()->Float
        return Float(self._node.at("FloatPrecisionThreshold"))
    @FloatPrecisionThreshold.setter
    def FloatPrecisionThreshold(self, val): self.FloatPrecisionThreshold.set(val)
    @property
    def Fullscreen(self):  # type: ()->Bool
        return Bool(self._node.at("Fullscreen"))
    @Fullscreen.setter
    def Fullscreen(self, val): self.Fullscreen.set(val)
    @property
    def Global(self):  # type: ()->RenderManager_RenderConfig
        return RenderManager_RenderConfig(self._node.at("Global"))
    @property
    def ImGuiFontScale(self):  # type: ()->Int
        return Int(self._node.at("ImGuiFontScale"))
    @ImGuiFontScale.setter
    def ImGuiFontScale(self, val): self.ImGuiFontScale.set(val)
    @property
    def LODTransitionDuration(self):  # type: ()->Float
        return Float(self._node.at("LODTransitionDuration"))
    @LODTransitionDuration.setter
    def LODTransitionDuration(self, val): self.LODTransitionDuration.set(val)
    @property
    def MotionBlurHeightFactorFromSpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("MotionBlurHeightFactorFromSpeed"))
    @property
    def PC(self):  # type: ()->RenderManager_RenderConfig
        return RenderManager_RenderConfig(self._node.at("PC"))
    @property
    def PS4(self):  # type: ()->RenderManager_RenderConfig
        return RenderManager_RenderConfig(self._node.at("PS4"))
    @property
    def PS4Neo(self):  # type: ()->RenderManager_RenderConfig
        return RenderManager_RenderConfig(self._node.at("PS4Neo"))
    @property
    def PS5(self):  # type: ()->RenderManager_RenderConfig
        return RenderManager_RenderConfig(self._node.at("PS5"))
    @property
    def RenderToWindow(self):  # type: ()->Bool
        return Bool(self._node.at("RenderToWindow"))
    @RenderToWindow.setter
    def RenderToWindow(self, val): self.RenderToWindow.set(val)
    @property
    def ResolutionX(self):  # type: ()->Int
        return Int(self._node.at("ResolutionX"))
    @ResolutionX.setter
    def ResolutionX(self, val): self.ResolutionX.set(val)
    @property
    def ResolutionY(self):  # type: ()->Int
        return Int(self._node.at("ResolutionY"))
    @ResolutionY.setter
    def ResolutionY(self, val): self.ResolutionY.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def VSync(self):  # type: ()->Int
        return Int(self._node.at("VSync"))
    @VSync.setter
    def VSync(self, val): self.VSync.set(val)
    @property
    def WindowPositionX(self):  # type: ()->Int
        return Int(self._node.at("WindowPositionX"))
    @WindowPositionX.setter
    def WindowPositionX(self, val): self.WindowPositionX.set(val)
    @property
    def WindowPositionY(self):  # type: ()->Int
        return Int(self._node.at("WindowPositionY"))
    @WindowPositionY.setter
    def WindowPositionY(self, val): self.WindowPositionY.set(val)
    @property
    def WindowSizeX(self):  # type: ()->Int
        return Int(self._node.at("WindowSizeX"))
    @WindowSizeX.setter
    def WindowSizeX(self, val): self.WindowSizeX.set(val)
    @property
    def WindowSizeY(self):  # type: ()->Int
        return Int(self._node.at("WindowSizeY"))
    @WindowSizeY.setter
    def WindowSizeY(self, val): self.WindowSizeY.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




