
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class ConstrainedMoveContextInput(HelperObject):
    schema_name = "ConstrainedMoveContextInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConstrainedMoveContextInput
        return ConstrainedMoveContextInput(entlib.load_node_file(sourcefile, entlib.get_schema(ConstrainedMoveContextInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConstrainedMoveContextInput
        return ConstrainedMoveContextInput(entlib.make_node(ConstrainedMoveContextInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CurvatureNormalizationRadius(self):  # type: ()->Float
        return Float(self._node.at("CurvatureNormalizationRadius"))
    @CurvatureNormalizationRadius.setter
    def CurvatureNormalizationRadius(self, val): self.CurvatureNormalizationRadius.set(val)
    @property
    def PowerMethodIterationMaxCount(self):  # type: ()->Int
        return Int(self._node.at("PowerMethodIterationMaxCount"))
    @PowerMethodIterationMaxCount.setter
    def PowerMethodIterationMaxCount(self, val): self.PowerMethodIterationMaxCount.set(val)
    @property
    def PowerMethodIterationThreshold(self):  # type: ()->Float
        return Float(self._node.at("PowerMethodIterationThreshold"))
    @PowerMethodIterationThreshold.setter
    def PowerMethodIterationThreshold(self, val): self.PowerMethodIterationThreshold.set(val)
    @property
    def RaycastAngleThreshold(self):  # type: ()->Float
        return Float(self._node.at("RaycastAngleThreshold"))
    @RaycastAngleThreshold.setter
    def RaycastAngleThreshold(self, val): self.RaycastAngleThreshold.set(val)
    @property
    def RaycastCount(self):  # type: ()->Int
        return Int(self._node.at("RaycastCount"))
    @RaycastCount.setter
    def RaycastCount(self, val): self.RaycastCount.set(val)
    @property
    def RaycastLength(self):  # type: ()->Float
        return Float(self._node.at("RaycastLength"))
    @RaycastLength.setter
    def RaycastLength(self, val): self.RaycastLength.set(val)
    @property
    def RaycastStep(self):  # type: ()->Float
        return Float(self._node.at("RaycastStep"))
    @RaycastStep.setter
    def RaycastStep(self, val): self.RaycastStep.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




