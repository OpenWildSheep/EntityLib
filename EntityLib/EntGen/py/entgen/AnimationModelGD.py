
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class AnimationModelGD(HelperObject):
    schema_name = "AnimationModelGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationModelGD
        return AnimationModelGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationModelGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationModelGD
        return AnimationModelGD(entlib.make_node(AnimationModelGD.schema_name))
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
    def isLandAnimDriven(self):  # type: ()->Bool
        return Bool(self._node.at("isLandAnimDriven"))
    @isLandAnimDriven.setter
    def isLandAnimDriven(self, val): self.isLandAnimDriven.set(val)
    @property
    def isTurnAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("isTurnAllowed"))
    @isTurnAllowed.setter
    def isTurnAllowed(self, val): self.isTurnAllowed.set(val)
    @property
    def playRatioFactor(self):  # type: ()->Float
        return Float(self._node.at("playRatioFactor"))
    @playRatioFactor.setter
    def playRatioFactor(self, val): self.playRatioFactor.set(val)
    @property
    def scalePlayRatioCoeffInfluence(self):  # type: ()->Float
        return Float(self._node.at("scalePlayRatioCoeffInfluence"))
    @scalePlayRatioCoeffInfluence.setter
    def scalePlayRatioCoeffInfluence(self, val): self.scalePlayRatioCoeffInfluence.set(val)
    @property
    def startRunPlayRatioFactor(self):  # type: ()->Float
        return Float(self._node.at("startRunPlayRatioFactor"))
    @startRunPlayRatioFactor.setter
    def startRunPlayRatioFactor(self, val): self.startRunPlayRatioFactor.set(val)
    @property
    def turnPlayRatioFactor(self):  # type: ()->Float
        return Float(self._node.at("turnPlayRatioFactor"))
    @turnPlayRatioFactor.setter
    def turnPlayRatioFactor(self, val): self.turnPlayRatioFactor.set(val)
    pass




