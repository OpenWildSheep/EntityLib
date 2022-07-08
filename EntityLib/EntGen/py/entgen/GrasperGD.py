
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.GrasperInteractionData import *
from entgen.GraspType import *

from EntityLibPy import Node

class GrasperGD(HelperObject):
    schema_name = "GrasperGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GrasperGD
        return GrasperGD(entlib.load_node_file(sourcefile, entlib.get_schema(GrasperGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GrasperGD
        return GrasperGD(entlib.make_node(GrasperGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def bestInteractionDeltaAngleCoeff(self):  # type: ()->Float
        return Float(self._node.at("bestInteractionDeltaAngleCoeff"))
    @bestInteractionDeltaAngleCoeff.setter
    def bestInteractionDeltaAngleCoeff(self, val): self.bestInteractionDeltaAngleCoeff.set(val)
    @property
    def bestInteractionDistanceCoeff(self):  # type: ()->Float
        return Float(self._node.at("bestInteractionDistanceCoeff"))
    @bestInteractionDistanceCoeff.setter
    def bestInteractionDistanceCoeff(self, val): self.bestInteractionDistanceCoeff.set(val)
    @property
    def interactionDatas(self):  # type: ()->Map[GraspTypeEnum, GrasperInteractionData]
        return (lambda n: Map(GraspTypeEnum, GrasperInteractionData, n))(self._node.at("interactionDatas"))
    @property
    def jumpRiseMinCoeffToEnter(self):  # type: ()->Float
        return Float(self._node.at("jumpRiseMinCoeffToEnter"))
    @jumpRiseMinCoeffToEnter.setter
    def jumpRiseMinCoeffToEnter(self, val): self.jumpRiseMinCoeffToEnter.set(val)
    @property
    def sensorHotspotName(self):  # type: ()->String
        return String(self._node.at("sensorHotspotName"))
    @sensorHotspotName.setter
    def sensorHotspotName(self, val): self.sensorHotspotName.set(val)
    pass




