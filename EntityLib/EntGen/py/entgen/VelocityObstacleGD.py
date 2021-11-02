
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class VelocityObstacleGD(HelperObject):
    schema_name = "VelocityObstacleGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VelocityObstacleGD
        return VelocityObstacleGD(entlib.load_node_file(sourcefile, entlib.get_schema(VelocityObstacleGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VelocityObstacleGD
        return VelocityObstacleGD(entlib.make_node(VelocityObstacleGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AccelerationAfterAvoidance(self):  # type: ()->Float
        return Float(self._node.at("AccelerationAfterAvoidance"))
    @AccelerationAfterAvoidance.setter
    def AccelerationAfterAvoidance(self, val): self.AccelerationAfterAvoidance.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




