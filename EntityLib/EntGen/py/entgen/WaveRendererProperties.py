
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Vector3 import *

from EntityLibPy import Node

class WaveRendererProperties(HelperObject):
    schema_name = "WaveRendererProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WaveRendererProperties
        return WaveRendererProperties(entlib.load_node_file(sourcefile, entlib.get_schema(WaveRendererProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WaveRendererProperties
        return WaveRendererProperties(entlib.make_node(WaveRendererProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BonesGridHeight(self):  # type: ()->Int
        return Int(self._node.at("BonesGridHeight"))
    @BonesGridHeight.setter
    def BonesGridHeight(self, val): self.BonesGridHeight.set(val)
    @property
    def BonesGridWidth(self):  # type: ()->Int
        return Int(self._node.at("BonesGridWidth"))
    @BonesGridWidth.setter
    def BonesGridWidth(self, val): self.BonesGridWidth.set(val)
    @property
    def BonesIgnoreOffset(self):  # type: ()->Int
        return Int(self._node.at("BonesIgnoreOffset"))
    @BonesIgnoreOffset.setter
    def BonesIgnoreOffset(self, val): self.BonesIgnoreOffset.set(val)
    @property
    def MaterialPath(self):  # type: ()->String
        return String(self._node.at("MaterialPath"))
    @MaterialPath.setter
    def MaterialPath(self, val): self.MaterialPath.set(val)
    @property
    def MeshPath(self):  # type: ()->String
        return String(self._node.at("MeshPath"))
    @MeshPath.setter
    def MeshPath(self, val): self.MeshPath.set(val)
    @property
    def NbMeshInstances(self):  # type: ()->Int
        return Int(self._node.at("NbMeshInstances"))
    @NbMeshInstances.setter
    def NbMeshInstances(self, val): self.NbMeshInstances.set(val)
    @property
    def NbQuads(self):  # type: ()->Int
        return Int(self._node.at("NbQuads"))
    @NbQuads.setter
    def NbQuads(self, val): self.NbQuads.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def Scale(self):  # type: ()->Vector3
        return Vector3(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




