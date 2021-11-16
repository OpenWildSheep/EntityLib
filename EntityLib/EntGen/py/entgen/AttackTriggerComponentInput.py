
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *

from EntityLibPy import Node

class AttackTriggerComponentInput(HelperObject):
    schema_name = "AttackTriggerComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackTriggerComponentInput
        return AttackTriggerComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(AttackTriggerComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackTriggerComponentInput
        return AttackTriggerComponentInput(entlib.make_node(AttackTriggerComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




