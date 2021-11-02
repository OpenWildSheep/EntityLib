
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class FluidManager(HelperObject):
    schema_name = "FluidManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidManager
        return FluidManager(entlib.load_node_file(sourcefile, entlib.get_schema(FluidManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidManager
        return FluidManager(entlib.make_node(FluidManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




