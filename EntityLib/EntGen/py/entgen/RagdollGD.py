
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class RagdollGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RagdollGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(RagdollGD.schema_name))
    @property
    def RagdollType(self): return String(self._node.at("RagdollType"))
    @RagdollType.setter
    def RagdollType(self, val): self.RagdollType.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




