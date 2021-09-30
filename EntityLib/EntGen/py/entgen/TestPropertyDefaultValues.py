
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *


class TestPropertyDefaultValues(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestPropertyDefaultValues"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestPropertyDefaultValues.schema_name))
    @property
    def A(self): return Int(self._node.at("A"))
    @A.setter
    def A(self, val): self.A.set(val)
    @property
    def B(self): return Int(self._node.at("B"))
    @B.setter
    def B(self, val): self.B.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




