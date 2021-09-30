
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *


class PhysicsTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PhysicsTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsTriggerGD.schema_name))
    @property
    def RequiredComponents(self): return (lambda n: PrimArray(String, n))(self._node.at("RequiredComponents"))
    @RequiredComponents.setter
    def RequiredComponents(self, val): self.RequiredComponents.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




