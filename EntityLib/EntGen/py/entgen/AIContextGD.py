
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.AIContextSlot import *

from EntityLibPy import Node

class AIContextGD(HelperObject):
    schema_name = "AIContextGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIContextGD
        return AIContextGD(entlib.load_node_file(sourcefile, entlib.get_schema(AIContextGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIContextGD
        return AIContextGD(entlib.make_node(AIContextGD.schema_name))
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
    def attackCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("attackCircleRadius"))
    @attackCircleRadius.setter
    def attackCircleRadius(self, val): self.attackCircleRadius.set(val)
    @property
    def distanceBetweenCreatures(self):  # type: ()->Float
        return Float(self._node.at("distanceBetweenCreatures"))
    @distanceBetweenCreatures.setter
    def distanceBetweenCreatures(self, val): self.distanceBetweenCreatures.set(val)
    @property
    def distantReachCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("distantReachCircleRadius"))
    @distantReachCircleRadius.setter
    def distantReachCircleRadius(self, val): self.distantReachCircleRadius.set(val)
    @property
    def followCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("followCircleRadius"))
    @followCircleRadius.setter
    def followCircleRadius(self, val): self.followCircleRadius.set(val)
    @property
    def lockTargetCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("lockTargetCircleRadius"))
    @lockTargetCircleRadius.setter
    def lockTargetCircleRadius(self, val): self.lockTargetCircleRadius.set(val)
    @property
    def slots(self):  # type: ()->Array[AIContextSlot]
        return (lambda n: Array(AIContextSlot, n))(self._node.at("slots"))
    pass




