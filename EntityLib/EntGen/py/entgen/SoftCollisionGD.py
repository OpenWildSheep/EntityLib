
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.SoftCollisionGD_VegetationDetectionParameters import *

from EntityLibPy import Node

class SoftCollisionGD(HelperObject):
    schema_name = "SoftCollisionGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoftCollisionGD
        return SoftCollisionGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoftCollisionGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoftCollisionGD
        return SoftCollisionGD(entlib.make_node(SoftCollisionGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PenetrationCoeffSmoothRate(self):  # type: ()->Float
        return Float(self._node.at("PenetrationCoeffSmoothRate"))
    @PenetrationCoeffSmoothRate.setter
    def PenetrationCoeffSmoothRate(self, val): self.PenetrationCoeffSmoothRate.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VegetationDetectionParam(self):  # type: ()->SoftCollisionGD_VegetationDetectionParameters
        return SoftCollisionGD_VegetationDetectionParameters(self._node.at("VegetationDetectionParam"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




