
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.String import *

from EntityLibPy import Node

class SoftCollisionGD_VegetationDetectionParameters(HelperObject):
    schema_name = "SoftCollisionGD::VegetationDetectionParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoftCollisionGD_VegetationDetectionParameters
        return SoftCollisionGD_VegetationDetectionParameters(entlib.load_node_file(sourcefile, entlib.get_schema(SoftCollisionGD_VegetationDetectionParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoftCollisionGD_VegetationDetectionParameters
        return SoftCollisionGD_VegetationDetectionParameters(entlib.make_node(SoftCollisionGD_VegetationDetectionParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def BoneOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("BoneOffset"))
    @BoneOffset.setter
    def BoneOffset(self, val): self.BoneOffset.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def VegetationTagList(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("VegetationTagList"))
    @VegetationTagList.setter
    def VegetationTagList(self, val): self.VegetationTagList.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




