
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AttackType import *
from entgen.String import *

from EntityLibPy import Node

class AttackData(HelperObject):
    schema_name = "AttackData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackData
        return AttackData(entlib.load_node_file(sourcefile, entlib.get_schema(AttackData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackData
        return AttackData(entlib.make_node(AttackData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DefaultAttackType(self):  # type: ()->AttackType
        return AttackType(self._node.at("DefaultAttackType"))
    @DefaultAttackType.setter
    def DefaultAttackType(self, val): self.DefaultAttackType.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




