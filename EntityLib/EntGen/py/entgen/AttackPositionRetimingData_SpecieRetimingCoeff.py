
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class AttackPositionRetimingData_SpecieRetimingCoeff(HelperObject):
    schema_name = "AttackPositionRetimingData::SpecieRetimingCoeff"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackPositionRetimingData_SpecieRetimingCoeff
        return AttackPositionRetimingData_SpecieRetimingCoeff(entlib.load_node_file(sourcefile, entlib.get_schema(AttackPositionRetimingData_SpecieRetimingCoeff.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackPositionRetimingData_SpecieRetimingCoeff
        return AttackPositionRetimingData_SpecieRetimingCoeff(entlib.make_node(AttackPositionRetimingData_SpecieRetimingCoeff.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def defaultCoeff(self):  # type: ()->Float
        return Float(self._node.at("defaultCoeff"))
    @defaultCoeff.setter
    def defaultCoeff(self, val): self.defaultCoeff.set(val)
    @property
    def masterCoeff(self):  # type: ()->Float
        return Float(self._node.at("masterCoeff"))
    @masterCoeff.setter
    def masterCoeff(self, val): self.masterCoeff.set(val)
    pass




