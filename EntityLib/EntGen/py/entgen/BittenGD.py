
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class BittenGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BittenGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BittenGD
        return BittenGD(entlib.load_node_file(sourcefile, entlib.get_schema(BittenGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BittenGD
        return BittenGD(entlib.make_node(BittenGD.schema_name))
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




