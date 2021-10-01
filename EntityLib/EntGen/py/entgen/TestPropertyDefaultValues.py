
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class TestPropertyDefaultValues(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestPropertyDefaultValues"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestPropertyDefaultValues
        return TestPropertyDefaultValues(entlib.load_node_file(sourcefile, entlib.get_schema(TestPropertyDefaultValues.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestPropertyDefaultValues
        return TestPropertyDefaultValues(entlib.make_node(TestPropertyDefaultValues.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def A(self):  # type: ()->Int
        return Int(self._node.at("A"))
    @A.setter
    def A(self, val): self.A.set(val)
    @property
    def B(self):  # type: ()->Int
        return Int(self._node.at("B"))
    @B.setter
    def B(self, val): self.B.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




