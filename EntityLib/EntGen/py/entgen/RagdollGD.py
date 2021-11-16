
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class RagdollGD(HelperObject):
    schema_name = "RagdollGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RagdollGD
        return RagdollGD(entlib.load_node_file(sourcefile, entlib.get_schema(RagdollGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RagdollGD
        return RagdollGD(entlib.make_node(RagdollGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RagdollType(self):  # type: ()->String
        return String(self._node.at("RagdollType"))
    @RagdollType.setter
    def RagdollType(self, val): self.RagdollType.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




