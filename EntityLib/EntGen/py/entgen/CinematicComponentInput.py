
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *

from EntityLibPy import Node

class CinematicComponentInput(HelperObject):
    schema_name = "CinematicComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CinematicComponentInput
        return CinematicComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(CinematicComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CinematicComponentInput
        return CinematicComponentInput(entlib.make_node(CinematicComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass



