
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.ForceMultiplier import *

from EntityLibPy import Node

class PhysicsImpactMakerComponentInput(HelperObject):
    schema_name = "PhysicsImpactMakerComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsImpactMakerComponentInput
        return PhysicsImpactMakerComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsImpactMakerComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsImpactMakerComponentInput
        return PhysicsImpactMakerComponentInput(entlib.make_node(PhysicsImpactMakerComponentInput.schema_name))
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




