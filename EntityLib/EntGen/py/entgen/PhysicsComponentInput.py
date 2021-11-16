
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *

from EntityLibPy import Node

class PhysicsComponentInput(HelperObject):
    schema_name = "PhysicsComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsComponentInput
        return PhysicsComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsComponentInput
        return PhysicsComponentInput(entlib.make_node(PhysicsComponentInput.schema_name))
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




