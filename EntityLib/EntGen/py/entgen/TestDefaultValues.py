
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Matrix33 import *
from entgen.TestPropertyDefaultValues2 import *


class TestDefaultValues(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestDefaultValues"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestDefaultValues.schema_name))
    @property
    def Matrix(self): return Matrix33(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Matrix2(self): return Matrix33(self._node.at("Matrix2"))
    @Matrix2.setter
    def Matrix2(self, val): self.Matrix2.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def propertyWithDefault(self): return TestPropertyDefaultValues2(self._node.at("propertyWithDefault"))
    pass




