
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionStackFilter import *

from EntityLibPy import Node

class ActionStackFilterRide(HelperObject):
    schema_name = "ActionStackFilterRide"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStackFilterRide
        return ActionStackFilterRide(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStackFilterRide.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStackFilterRide
        return ActionStackFilterRide(entlib.make_node(ActionStackFilterRide.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActionStackFilter
        return ActionStackFilter(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




