
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.TestPropertyDefaultValues import *


class TestPropertyDefaultValues2(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestPropertyDefaultValues2"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestPropertyDefaultValues2.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def propertyWithDefault2(self): return TestPropertyDefaultValues(self._node.at("propertyWithDefault2"))
    @property
    def propertyWithDefault3(self): return TestPropertyDefaultValues(self._node.at("propertyWithDefault3"))
    pass




