
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class ProtoComponentGD(HelperObject):
    schema_name = "ProtoComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProtoComponentGD
        return ProtoComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ProtoComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProtoComponentGD
        return ProtoComponentGD(entlib.make_node(ProtoComponentGD.schema_name))
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




