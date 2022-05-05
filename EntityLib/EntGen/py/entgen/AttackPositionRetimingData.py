
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.AttackPositionRetimingData_SpecieRetimingCoeff import *
from entgen.Specie import *

from EntityLibPy import Node

class AttackPositionRetimingData(HelperObject):
    schema_name = "AttackPositionRetimingData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackPositionRetimingData
        return AttackPositionRetimingData(entlib.load_node_file(sourcefile, entlib.get_schema(AttackPositionRetimingData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackPositionRetimingData
        return AttackPositionRetimingData(entlib.make_node(AttackPositionRetimingData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animTranslationCoeff(self):  # type: ()->Float
        return Float(self._node.at("animTranslationCoeff"))
    @animTranslationCoeff.setter
    def animTranslationCoeff(self, val): self.animTranslationCoeff.set(val)
    @property
    def backwardRetimingCoeffBySpecie(self):  # type: ()->Map[SpecieEnum, AttackPositionRetimingData_SpecieRetimingCoeff]
        return (lambda n: Map(SpecieEnum, AttackPositionRetimingData_SpecieRetimingCoeff, n))(self._node.at("backwardRetimingCoeffBySpecie"))
    @property
    def lengthMax(self):  # type: ()->Float
        return Float(self._node.at("lengthMax"))
    @lengthMax.setter
    def lengthMax(self, val): self.lengthMax.set(val)
    @property
    def lengthMin(self):  # type: ()->Float
        return Float(self._node.at("lengthMin"))
    @lengthMin.setter
    def lengthMin(self, val): self.lengthMin.set(val)
    @property
    def spherecastRadiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("spherecastRadiusCoeff"))
    @spherecastRadiusCoeff.setter
    def spherecastRadiusCoeff(self, val): self.spherecastRadiusCoeff.set(val)
    pass




