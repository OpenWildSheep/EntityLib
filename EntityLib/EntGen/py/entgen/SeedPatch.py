
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Matrix33 import *
from entgen.SeedPatchDataList import *

from EntityLibPy import Node

class SeedPatch(HelperObject):
    schema_name = "SeedPatch"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatch
        return SeedPatch(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatch.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatch
        return SeedPatch(entlib.make_node(SeedPatch.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AddVertexColor(self):  # type: ()->Bool
        return Bool(self._node.at("AddVertexColor"))
    @AddVertexColor.setter
    def AddVertexColor(self, val): self.AddVertexColor.set(val)
    @property
    def LocalMatrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("LocalMatrix"))
    @LocalMatrix.setter
    def LocalMatrix(self, val): self.LocalMatrix.set(val)
    @property
    def MeshFile(self):  # type: ()->String
        return String(self._node.at("MeshFile"))
    @MeshFile.setter
    def MeshFile(self, val): self.MeshFile.set(val)
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
    def SeedOverride(self):  # type: ()->Bool
        return Bool(self._node.at("SeedOverride"))
    @SeedOverride.setter
    def SeedOverride(self, val): self.SeedOverride.set(val)
    @property
    def SeedPatchDataList(self):  # type: ()->SeedPatchDataList
        return SeedPatchDataList(self._node.at("SeedPatchDataList"))
    @property
    def Subdivision(self):  # type: ()->Int
        return Int(self._node.at("Subdivision"))
    @Subdivision.setter
    def Subdivision(self, val): self.Subdivision.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




