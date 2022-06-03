
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.MoveTo import *

from EntityLibPy import Node

class MoveToAlongSpline(HelperObject):
    schema_name = "MoveToAlongSpline"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveToAlongSpline
        return MoveToAlongSpline(entlib.load_node_file(sourcefile, entlib.get_schema(MoveToAlongSpline.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveToAlongSpline
        return MoveToAlongSpline(entlib.make_node(MoveToAlongSpline.schema_name))
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




