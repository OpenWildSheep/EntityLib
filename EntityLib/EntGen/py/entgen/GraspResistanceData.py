
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GraspResistanceData(HelperObject):
    schema_name = "GraspResistanceData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GraspResistanceData
        return GraspResistanceData(entlib.load_node_file(sourcefile, entlib.get_schema(GraspResistanceData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GraspResistanceData
        return GraspResistanceData(entlib.make_node(GraspResistanceData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def resistanceMax(self):  # type: ()->Float
        return Float(self._node.at("resistanceMax"))
    @resistanceMax.setter
    def resistanceMax(self, val): self.resistanceMax.set(val)
    @property
    def strengthMultiplierCurve(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("strengthMultiplierCurve"))
    pass




