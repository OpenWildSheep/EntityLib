
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.TestPropertyDefaultValues import *

from EntityLibPy import Node

class TestPropertyDefaultValues2(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestPropertyDefaultValues2"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestPropertyDefaultValues2
        return TestPropertyDefaultValues2(entlib.load_node_file(sourcefile, entlib.get_schema(TestPropertyDefaultValues2.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestPropertyDefaultValues2
        return TestPropertyDefaultValues2(entlib.make_node(TestPropertyDefaultValues2.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def propertyWithDefault2(self):  # type: ()->TestPropertyDefaultValues
        return TestPropertyDefaultValues(self._node.at("propertyWithDefault2"))
    @property
    def propertyWithDefault3(self):  # type: ()->TestPropertyDefaultValues
        return TestPropertyDefaultValues(self._node.at("propertyWithDefault3"))
    pass




