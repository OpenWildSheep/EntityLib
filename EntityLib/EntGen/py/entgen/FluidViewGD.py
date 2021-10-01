
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class FluidViewGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidViewGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidViewGD
        return FluidViewGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidViewGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidViewGD
        return FluidViewGD(entlib.make_node(FluidViewGD.schema_name))
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




