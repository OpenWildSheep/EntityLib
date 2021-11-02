
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class PhysicsMeshProviderGD(HelperObject):
    schema_name = "PhysicsMeshProviderGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsMeshProviderGD
        return PhysicsMeshProviderGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsMeshProviderGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsMeshProviderGD
        return PhysicsMeshProviderGD(entlib.make_node(PhysicsMeshProviderGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EdgeTransitionConstraintAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("EdgeTransitionConstraintAllowed"))
    @EdgeTransitionConstraintAllowed.setter
    def EdgeTransitionConstraintAllowed(self, val): self.EdgeTransitionConstraintAllowed.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




