
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class VelocityObstacleGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VelocityObstacleGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(VelocityObstacleGD.schema_name))
    @property
    def AccelerationAfterAvoidance(self): return Float(self._node.at("AccelerationAfterAvoidance"))
    @AccelerationAfterAvoidance.setter
    def AccelerationAfterAvoidance(self, val): self.AccelerationAfterAvoidance.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




