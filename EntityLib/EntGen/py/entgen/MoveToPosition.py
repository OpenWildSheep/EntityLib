
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.MoveTo import *

from EntityLibPy import Node

class MoveToPosition(HelperObject):
    schema_name = "MoveToPosition"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveToPosition
        return MoveToPosition(entlib.load_node_file(sourcefile, entlib.get_schema(MoveToPosition.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveToPosition
        return MoveToPosition(entlib.make_node(MoveToPosition.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->MoveTo
        return MoveTo(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




