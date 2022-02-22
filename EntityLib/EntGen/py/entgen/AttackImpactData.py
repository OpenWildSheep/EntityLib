
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class AttackImpactData(HelperObject):
    schema_name = "AttackImpactData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackImpactData
        return AttackImpactData(entlib.load_node_file(sourcefile, entlib.get_schema(AttackImpactData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackImpactData
        return AttackImpactData(entlib.make_node(AttackImpactData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def amount(self):  # type: ()->Float
        return Float(self._node.at("amount"))
    @amount.setter
    def amount(self, val): self.amount.set(val)
    pass




