
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *


class FloatRange(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FloatRange"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FloatRange.schema_name))
    @property
    def MinMax(self): return Vector2(self._node.at("MinMax"))
    @MinMax.setter
    def MinMax(self, val): self.MinMax.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




