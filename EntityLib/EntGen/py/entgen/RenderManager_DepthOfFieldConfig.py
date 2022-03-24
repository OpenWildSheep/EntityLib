
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class RenderManager_DepthOfFieldConfig(HelperObject):
    schema_name = "RenderManager::DepthOfFieldConfig"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RenderManager_DepthOfFieldConfig
        return RenderManager_DepthOfFieldConfig(entlib.load_node_file(sourcefile, entlib.get_schema(RenderManager_DepthOfFieldConfig.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RenderManager_DepthOfFieldConfig
        return RenderManager_DepthOfFieldConfig(entlib.make_node(RenderManager_DepthOfFieldConfig.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FarTransitionDistance(self):  # type: ()->Float
        return Float(self._node.at("FarTransitionDistance"))
    @FarTransitionDistance.setter
    def FarTransitionDistance(self, val): self.FarTransitionDistance.set(val)
    @property
    def Multiplier(self):  # type: ()->Float
        return Float(self._node.at("Multiplier"))
    @Multiplier.setter
    def Multiplier(self, val): self.Multiplier.set(val)
    @property
    def NearTransitionDistance(self):  # type: ()->Float
        return Float(self._node.at("NearTransitionDistance"))
    @NearTransitionDistance.setter
    def NearTransitionDistance(self, val): self.NearTransitionDistance.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




