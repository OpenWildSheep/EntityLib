
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.FluidType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class FluidGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidGD.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def type(self): return FluidType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    @property
    def useHalfShape(self): return Bool(self._node.at("useHalfShape"))
    @useHalfShape.setter
    def useHalfShape(self, val): self.useHalfShape.set(val)
    pass




