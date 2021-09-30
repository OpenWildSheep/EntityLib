
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *


class SeedPatchData(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SeedPatchData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchData.schema_name))
    @property
    def NoiseBlur(self): return Float(self._node.at("NoiseBlur"))
    @NoiseBlur.setter
    def NoiseBlur(self, val): self.NoiseBlur.set(val)
    @property
    def NoiseContrast(self): return Float(self._node.at("NoiseContrast"))
    @NoiseContrast.setter
    def NoiseContrast(self, val): self.NoiseContrast.set(val)
    @property
    def NoiseInvert(self): return Bool(self._node.at("NoiseInvert"))
    @NoiseInvert.setter
    def NoiseInvert(self, val): self.NoiseInvert.set(val)
    @property
    def NoiseName(self): return String(self._node.at("NoiseName"))
    @NoiseName.setter
    def NoiseName(self, val): self.NoiseName.set(val)
    @property
    def NoiseOffsetX(self): return Float(self._node.at("NoiseOffsetX"))
    @NoiseOffsetX.setter
    def NoiseOffsetX(self, val): self.NoiseOffsetX.set(val)
    @property
    def NoiseOffsetY(self): return Float(self._node.at("NoiseOffsetY"))
    @NoiseOffsetY.setter
    def NoiseOffsetY(self, val): self.NoiseOffsetY.set(val)
    @property
    def NoiseOpacity(self): return Float(self._node.at("NoiseOpacity"))
    @NoiseOpacity.setter
    def NoiseOpacity(self, val): self.NoiseOpacity.set(val)
    @property
    def NoisePosition(self): return Float(self._node.at("NoisePosition"))
    @NoisePosition.setter
    def NoisePosition(self, val): self.NoisePosition.set(val)
    @property
    def NoiseSizeX(self): return Float(self._node.at("NoiseSizeX"))
    @NoiseSizeX.setter
    def NoiseSizeX(self, val): self.NoiseSizeX.set(val)
    @property
    def NoiseSizeY(self): return Float(self._node.at("NoiseSizeY"))
    @NoiseSizeY.setter
    def NoiseSizeY(self, val): self.NoiseSizeY.set(val)
    @property
    def SeedName(self): return String(self._node.at("SeedName"))
    @SeedName.setter
    def SeedName(self, val): self.SeedName.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




