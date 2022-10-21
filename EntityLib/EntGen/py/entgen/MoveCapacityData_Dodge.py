
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class MoveCapacityData_Dodge(HelperObject):
    schema_name = "MoveCapacityData::Dodge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_Dodge
        return MoveCapacityData_Dodge(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_Dodge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_Dodge
        return MoveCapacityData_Dodge(entlib.make_node(MoveCapacityData_Dodge.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def classicDodgeOrientationRate(self):  # type: ()->Float
        return Float(self._node.at("classicDodgeOrientationRate"))
    @classicDodgeOrientationRate.setter
    def classicDodgeOrientationRate(self, val): self.classicDodgeOrientationRate.set(val)
    @property
    def cooldownTime(self):  # type: ()->Float
        return Float(self._node.at("cooldownTime"))
    @cooldownTime.setter
    def cooldownTime(self, val): self.cooldownTime.set(val)
    @property
    def distance(self):  # type: ()->Float
        return Float(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    @property
    def scalePlayRatioFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("scalePlayRatioFactor"))
    pass




