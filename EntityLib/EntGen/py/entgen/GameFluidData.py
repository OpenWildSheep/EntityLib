
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.GameFluidData_HeightThreshold import *

from EntityLibPy import Node

class GameFluidData(HelperObject):
    schema_name = "GameFluidData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFluidData
        return GameFluidData(entlib.load_node_file(sourcefile, entlib.get_schema(GameFluidData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFluidData
        return GameFluidData(entlib.make_node(GameFluidData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FlowSpeedInfluences(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("FlowSpeedInfluences"))
    @FlowSpeedInfluences.setter
    def FlowSpeedInfluences(self, val): self.FlowSpeedInfluences.set(val)
    @property
    def HeightThresholds(self):  # type: ()->Array[Array[GameFluidData_HeightThreshold]]
        return (lambda n: Array((lambda n: Array(GameFluidData_HeightThreshold, n)), n))(self._node.at("HeightThresholds"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




