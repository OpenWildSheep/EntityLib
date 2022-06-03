
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.DisableFluid import *

from EntityLibPy import Node

class FluidComponentInput(HelperObject):
    schema_name = "FluidComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidComponentInput
        return FluidComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(FluidComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidComponentInput
        return FluidComponentInput(entlib.make_node(FluidComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DisableFluid(self):  # type: ()->DisableFluid
        return DisableFluid(self._node.at("DisableFluid"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




