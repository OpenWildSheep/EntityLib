
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EnergyValue import *
from entgen.String import *
from entgen.VegetationPCloudData import *

from EntityLibPy import Node

class RegenerableVegetationGD(HelperObject):
    schema_name = "RegenerableVegetationGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenerableVegetationGD
        return RegenerableVegetationGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenerableVegetationGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenerableVegetationGD
        return RegenerableVegetationGD(entlib.make_node(RegenerableVegetationGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyValues(self):  # type: ()->PrimArray[EnergyValue]
        return (lambda n: PrimArray(EnergyValue, n))(self._node.at("EnergyValues"))
    @EnergyValues.setter
    def EnergyValues(self, val): self.EnergyValues.set(val)
    @property
    def PCloudPath(self):  # type: ()->String
        return String(self._node.at("PCloudPath"))
    @PCloudPath.setter
    def PCloudPath(self, val): self.PCloudPath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UsedVegetations(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("UsedVegetations"))
    @UsedVegetations.setter
    def UsedVegetations(self, val): self.UsedVegetations.set(val)
    @property
    def VegetationPClouds(self):  # type: ()->Array[VegetationPCloudData]
        return (lambda n: Array(VegetationPCloudData, n))(self._node.at("VegetationPClouds"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




