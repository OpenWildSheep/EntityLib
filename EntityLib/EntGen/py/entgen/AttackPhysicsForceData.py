
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class AttackPhysicsForceData(HelperObject):
    schema_name = "AttackPhysicsForceData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackPhysicsForceData
        return AttackPhysicsForceData(entlib.load_node_file(sourcefile, entlib.get_schema(AttackPhysicsForceData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackPhysicsForceData
        return AttackPhysicsForceData(entlib.make_node(AttackPhysicsForceData.schema_name))
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




