
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class RegenMeshGD(HelperObject):
    schema_name = "RegenMeshGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenMeshGD
        return RegenMeshGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenMeshGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenMeshGD
        return RegenMeshGD(entlib.make_node(RegenMeshGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FilePath(self):  # type: ()->String
        return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def FrontierHeightDetection(self):  # type: ()->Float
        return Float(self._node.at("FrontierHeightDetection"))
    @FrontierHeightDetection.setter
    def FrontierHeightDetection(self, val): self.FrontierHeightDetection.set(val)
    @property
    def FrontierTolerance(self):  # type: ()->Float
        return Float(self._node.at("FrontierTolerance"))
    @FrontierTolerance.setter
    def FrontierTolerance(self, val): self.FrontierTolerance.set(val)
    @property
    def LossBySecond(self):  # type: ()->Float
        return Float(self._node.at("LossBySecond"))
    @LossBySecond.setter
    def LossBySecond(self, val): self.LossBySecond.set(val)
    @property
    def LostRatio(self):  # type: ()->Float
        return Float(self._node.at("LostRatio"))
    @LostRatio.setter
    def LostRatio(self, val): self.LostRatio.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TransmissionPerSecond(self):  # type: ()->Float
        return Float(self._node.at("TransmissionPerSecond"))
    @TransmissionPerSecond.setter
    def TransmissionPerSecond(self, val): self.TransmissionPerSecond.set(val)
    @property
    def TransmissionRatio(self):  # type: ()->Float
        return Float(self._node.at("TransmissionRatio"))
    @TransmissionRatio.setter
    def TransmissionRatio(self, val): self.TransmissionRatio.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




