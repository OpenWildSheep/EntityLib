
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ScaleConverter import *
from entgen.Vector3 import *


class MoveCapacityData_OrientationSpeed(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::OrientationSpeed"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_OrientationSpeed.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def factor(self): return Vector3(self._node.at("factor"))
    @factor.setter
    def factor(self, val): self.factor.set(val)
    @property
    def rate(self): return Vector3(self._node.at("rate"))
    @rate.setter
    def rate(self, val): self.rate.set(val)
    @property
    def rotationRollFromAngularSpeed(self): return ScaleConverter(self._node.at("rotationRollFromAngularSpeed"))
    @property
    def speedFactorFromSpeedSlow(self): return ScaleConverter(self._node.at("speedFactorFromSpeedSlow"))
    @property
    def speedMax(self): return Vector3(self._node.at("speedMax"))
    @speedMax.setter
    def speedMax(self, val): self.speedMax.set(val)
    @property
    def steeringAngle(self): return Vector3(self._node.at("steeringAngle"))
    @steeringAngle.setter
    def steeringAngle(self, val): self.steeringAngle.set(val)
    pass




