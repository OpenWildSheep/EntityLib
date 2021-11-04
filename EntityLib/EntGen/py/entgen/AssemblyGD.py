
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class AssemblyGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AssemblyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AssemblyGD
        return AssemblyGD(entlib.load_node_file(sourcefile, entlib.get_schema(AssemblyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AssemblyGD
        return AssemblyGD(entlib.make_node(AssemblyGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




