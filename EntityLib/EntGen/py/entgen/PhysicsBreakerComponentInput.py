
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.ForceMultiplier import *

from EntityLibPy import Node

class PhysicsBreakerComponentInput(HelperObject):
    schema_name = "PhysicsBreakerComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsBreakerComponentInput
        return PhysicsBreakerComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsBreakerComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsBreakerComponentInput
        return PhysicsBreakerComponentInput(entlib.make_node(PhysicsBreakerComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ForceMultiplier(self):  # type: ()->ForceMultiplier
        return ForceMultiplier(self._node.at("ForceMultiplier"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




