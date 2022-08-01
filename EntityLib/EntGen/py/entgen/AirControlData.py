
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class AirControlData(HelperObject):
    schema_name = "AirControlData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AirControlData
        return AirControlData(entlib.load_node_file(sourcefile, entlib.get_schema(AirControlData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AirControlData
        return AirControlData(entlib.make_node(AirControlData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AirControlBrake(self):  # type: ()->Float
        return Float(self._node.at("AirControlBrake"))
    @AirControlBrake.setter
    def AirControlBrake(self, val): self.AirControlBrake.set(val)
    @property
    def AirControlBrakeAngleMin(self):  # type: ()->Float
        return Float(self._node.at("AirControlBrakeAngleMin"))
    @AirControlBrakeAngleMin.setter
    def AirControlBrakeAngleMin(self, val): self.AirControlBrakeAngleMin.set(val)
    @property
    def AirControlDirection(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("AirControlDirection"))
    @property
    def AirControlSmooth(self):  # type: ()->Float
        return Float(self._node.at("AirControlSmooth"))
    @AirControlSmooth.setter
    def AirControlSmooth(self, val): self.AirControlSmooth.set(val)
    @property
    def AirControlSpeed(self):  # type: ()->Float
        return Float(self._node.at("AirControlSpeed"))
    @AirControlSpeed.setter
    def AirControlSpeed(self, val): self.AirControlSpeed.set(val)
    @property
    def AirControlSpeedAngleMax(self):  # type: ()->Float
        return Float(self._node.at("AirControlSpeedAngleMax"))
    @AirControlSpeedAngleMax.setter
    def AirControlSpeedAngleMax(self, val): self.AirControlSpeedAngleMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




