
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Matrix44 import *
from entgen.TransitionNeighborData import *
from entgen.Vector3 import *
from entgen.String import *


class VolumeConstraintDataGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VolumeConstraintDataGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(VolumeConstraintDataGD.schema_name))
    @property
    def Matrix(self): return Matrix44(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Neighbors(self): return TransitionNeighborData(self._node.at("Neighbors"))
    @property
    def Size(self): return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Tags(self): return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




