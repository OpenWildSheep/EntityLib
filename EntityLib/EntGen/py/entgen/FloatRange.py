
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *

from EntityLibPy import Node

class FloatRange(HelperObject):
    schema_name = "FloatRange"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FloatRange
        return FloatRange(entlib.load_node_file(sourcefile, entlib.get_schema(FloatRange.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FloatRange
        return FloatRange(entlib.make_node(FloatRange.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MinMax(self):  # type: ()->Vector2
        return Vector2(self._node.at("MinMax"))
    @MinMax.setter
    def MinMax(self, val): self.MinMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




