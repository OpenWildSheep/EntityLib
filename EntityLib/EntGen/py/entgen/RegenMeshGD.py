
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class RegenMeshGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenMeshGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(RegenMeshGD.schema_name))
    @property
    def FilePath(self): return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def FrontierHeightDetection(self): return Float(self._node.at("FrontierHeightDetection"))
    @FrontierHeightDetection.setter
    def FrontierHeightDetection(self, val): self.FrontierHeightDetection.set(val)
    @property
    def FrontierTolerance(self): return Float(self._node.at("FrontierTolerance"))
    @FrontierTolerance.setter
    def FrontierTolerance(self, val): self.FrontierTolerance.set(val)
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
    def TransmissionPerSecond(self): return Float(self._node.at("TransmissionPerSecond"))
    @TransmissionPerSecond.setter
    def TransmissionPerSecond(self, val): self.TransmissionPerSecond.set(val)
    @property
    def TransmissionRatio(self): return Float(self._node.at("TransmissionRatio"))
    @TransmissionRatio.setter
    def TransmissionRatio(self, val): self.TransmissionRatio.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




