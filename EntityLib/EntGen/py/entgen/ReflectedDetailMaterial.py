
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector3i import *

from EntityLibPy import Node

class ReflectedDetailMaterial(HelperObject):
    schema_name = "ReflectedDetailMaterial"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectedDetailMaterial
        return ReflectedDetailMaterial(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectedDetailMaterial.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectedDetailMaterial
        return ReflectedDetailMaterial(entlib.make_node(ReflectedDetailMaterial.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlbedoMap(self):  # type: ()->String
        return String(self._node.at("AlbedoMap"))
    @AlbedoMap.setter
    def AlbedoMap(self, val): self.AlbedoMap.set(val)
    @property
    def CavityMap(self):  # type: ()->String
        return String(self._node.at("CavityMap"))
    @CavityMap.setter
    def CavityMap(self, val): self.CavityMap.set(val)
    @property
    def DebugAlbedo(self):  # type: ()->Vector3i
        return Vector3i(self._node.at("DebugAlbedo"))
    @DebugAlbedo.setter
    def DebugAlbedo(self, val): self.DebugAlbedo.set(val)
    @property
    def EmissiveMap(self):  # type: ()->String
        return String(self._node.at("EmissiveMap"))
    @EmissiveMap.setter
    def EmissiveMap(self, val): self.EmissiveMap.set(val)
    @property
    def HeightMap(self):  # type: ()->String
        return String(self._node.at("HeightMap"))
    @HeightMap.setter
    def HeightMap(self, val): self.HeightMap.set(val)
    @property
    def NormalMap(self):  # type: ()->String
        return String(self._node.at("NormalMap"))
    @NormalMap.setter
    def NormalMap(self, val): self.NormalMap.set(val)
    @property
    def RoughMap(self):  # type: ()->String
        return String(self._node.at("RoughMap"))
    @RoughMap.setter
    def RoughMap(self, val): self.RoughMap.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




