
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.FluidType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class FluidGD(HelperObject):
    schema_name = "FluidGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidGD
        return FluidGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidGD
        return FluidGD(entlib.make_node(FluidGD.schema_name))
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
    @property
    def type(self):  # type: ()->FluidType
        return FluidType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    @property
    def useHalfShape(self):  # type: ()->Bool
        return Bool(self._node.at("useHalfShape"))
    @useHalfShape.setter
    def useHalfShape(self, val): self.useHalfShape.set(val)
    pass




