
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class VoxelSimulationGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VoxelSimulationGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(VoxelSimulationGD.schema_name))
    @property
    def FilePath(self): return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def LossBySecond(self): return Float(self._node.at("LossBySecond"))
    @LossBySecond.setter
    def LossBySecond(self, val): self.LossBySecond.set(val)
    @property
    def LostRatio(self): return Float(self._node.at("LostRatio"))
    @LostRatio.setter
    def LostRatio(self, val): self.LostRatio.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def TransmissionBySecond(self): return Float(self._node.at("TransmissionBySecond"))
    @TransmissionBySecond.setter
    def TransmissionBySecond(self, val): self.TransmissionBySecond.set(val)
    @property
    def TransmittedRatio(self): return Float(self._node.at("TransmittedRatio"))
    @TransmittedRatio.setter
    def TransmittedRatio(self, val): self.TransmittedRatio.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




