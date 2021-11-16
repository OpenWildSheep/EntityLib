
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class SeedPatchData(HelperObject):
    schema_name = "SeedPatchData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatchData
        return SeedPatchData(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatchData
        return SeedPatchData(entlib.make_node(SeedPatchData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NoiseBlur(self):  # type: ()->Float
        return Float(self._node.at("NoiseBlur"))
    @NoiseBlur.setter
    def NoiseBlur(self, val): self.NoiseBlur.set(val)
    @property
    def NoiseContrast(self):  # type: ()->Float
        return Float(self._node.at("NoiseContrast"))
    @NoiseContrast.setter
    def NoiseContrast(self, val): self.NoiseContrast.set(val)
    @property
    def NoiseInvert(self):  # type: ()->Bool
        return Bool(self._node.at("NoiseInvert"))
    @NoiseInvert.setter
    def NoiseInvert(self, val): self.NoiseInvert.set(val)
    @property
    def NoiseName(self):  # type: ()->String
        return String(self._node.at("NoiseName"))
    @NoiseName.setter
    def NoiseName(self, val): self.NoiseName.set(val)
    @property
    def NoiseOffsetX(self):  # type: ()->Float
        return Float(self._node.at("NoiseOffsetX"))
    @NoiseOffsetX.setter
    def NoiseOffsetX(self, val): self.NoiseOffsetX.set(val)
    @property
    def NoiseOffsetY(self):  # type: ()->Float
        return Float(self._node.at("NoiseOffsetY"))
    @NoiseOffsetY.setter
    def NoiseOffsetY(self, val): self.NoiseOffsetY.set(val)
    @property
    def NoiseOpacity(self):  # type: ()->Float
        return Float(self._node.at("NoiseOpacity"))
    @NoiseOpacity.setter
    def NoiseOpacity(self, val): self.NoiseOpacity.set(val)
    @property
    def NoisePosition(self):  # type: ()->Float
        return Float(self._node.at("NoisePosition"))
    @NoisePosition.setter
    def NoisePosition(self, val): self.NoisePosition.set(val)
    @property
    def NoiseSizeX(self):  # type: ()->Float
        return Float(self._node.at("NoiseSizeX"))
    @NoiseSizeX.setter
    def NoiseSizeX(self, val): self.NoiseSizeX.set(val)
    @property
    def NoiseSizeY(self):  # type: ()->Float
        return Float(self._node.at("NoiseSizeY"))
    @NoiseSizeY.setter
    def NoiseSizeY(self, val): self.NoiseSizeY.set(val)
    @property
    def SeedName(self):  # type: ()->String
        return String(self._node.at("SeedName"))
    @SeedName.setter
    def SeedName(self, val): self.SeedName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




