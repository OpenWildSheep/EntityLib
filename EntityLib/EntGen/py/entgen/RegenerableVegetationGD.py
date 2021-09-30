
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.FloatRange import *
from entgen.String import *
from entgen.VegetationPCloudData import *


class RegenerableVegetationGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenerableVegetationGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(RegenerableVegetationGD.schema_name))
    @property
    def PCloudPath(self): return String(self._node.at("PCloudPath"))
    @PCloudPath.setter
    def PCloudPath(self, val): self.PCloudPath.set(val)
    @property
    def RegenRange(self): return FloatRange(self._node.at("RegenRange"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def UsedVegetations(self): return (lambda n: PrimArray(String, n))(self._node.at("UsedVegetations"))
    @UsedVegetations.setter
    def UsedVegetations(self, val): self.UsedVegetations.set(val)
    @property
    def VegetationPClouds(self): return (lambda n: Array(VegetationPCloudData, n))(self._node.at("VegetationPClouds"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




