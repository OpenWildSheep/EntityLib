
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Matrix44 import *
from entgen.TransitionNeighborData import *
from entgen.Vector3 import *
from entgen.String import *

from EntityLibPy import Node

class VolumeConstraintDataGD(HelperObject):
    schema_name = "VolumeConstraintDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VolumeConstraintDataGD
        return VolumeConstraintDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(VolumeConstraintDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VolumeConstraintDataGD
        return VolumeConstraintDataGD(entlib.make_node(VolumeConstraintDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CameraConstraintLocalAxis(self):  # type: ()->Vector3
        return Vector3(self._node.at("CameraConstraintLocalAxis"))
    @CameraConstraintLocalAxis.setter
    def CameraConstraintLocalAxis(self, val): self.CameraConstraintLocalAxis.set(val)
    @property
    def Matrix(self):  # type: ()->Matrix44
        return Matrix44(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Neighbors(self):  # type: ()->TransitionNeighborData
        return TransitionNeighborData(self._node.at("Neighbors"))
    @property
    def Size(self):  # type: ()->Vector3
        return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




