
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class PhysicsMeshProviderGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PhysicsMeshProviderGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsMeshProviderGD.schema_name))
    @property
    def EdgeTransitionConstraintAllowed(self): return Bool(self._node.at("EdgeTransitionConstraintAllowed"))
    @EdgeTransitionConstraintAllowed.setter
    def EdgeTransitionConstraintAllowed(self, val): self.EdgeTransitionConstraintAllowed.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




