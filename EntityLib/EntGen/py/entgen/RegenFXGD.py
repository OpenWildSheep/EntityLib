
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class RegenFXGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenFXGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenFXGD
        return RegenFXGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenFXGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenFXGD
        return RegenFXGD(entlib.make_node(RegenFXGD.schema_name))
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




