
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CameraFreeData(HelperObject):
    schema_name = "CameraFreeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraFreeData
        return CameraFreeData(entlib.load_node_file(sourcefile, entlib.get_schema(CameraFreeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraFreeData
        return CameraFreeData(entlib.make_node(CameraFreeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Acceleration(self):  # type: ()->Float
        return Float(self._node.at("Acceleration"))
    @Acceleration.setter
    def Acceleration(self, val): self.Acceleration.set(val)
    @property
    def Deceleration(self):  # type: ()->Float
        return Float(self._node.at("Deceleration"))
    @Deceleration.setter
    def Deceleration(self, val): self.Deceleration.set(val)
    @property
    def JoyThreshold(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("JoyThreshold"))
    @property
    def MoveBlend(self):  # type: ()->Float
        return Float(self._node.at("MoveBlend"))
    @MoveBlend.setter
    def MoveBlend(self, val): self.MoveBlend.set(val)
    @property
    def MoveSpeed(self):  # type: ()->Float
        return Float(self._node.at("MoveSpeed"))
    @MoveSpeed.setter
    def MoveSpeed(self, val): self.MoveSpeed.set(val)
    @property
    def MoveSpeedZ(self):  # type: ()->Float
        return Float(self._node.at("MoveSpeedZ"))
    @MoveSpeedZ.setter
    def MoveSpeedZ(self, val): self.MoveSpeedZ.set(val)
    @property
    def RotateBlendX(self):  # type: ()->Float
        return Float(self._node.at("RotateBlendX"))
    @RotateBlendX.setter
    def RotateBlendX(self, val): self.RotateBlendX.set(val)
    @property
    def RotateBlendY(self):  # type: ()->Float
        return Float(self._node.at("RotateBlendY"))
    @RotateBlendY.setter
    def RotateBlendY(self, val): self.RotateBlendY.set(val)
    @property
    def RotateSpeedX(self):  # type: ()->Float
        return Float(self._node.at("RotateSpeedX"))
    @RotateSpeedX.setter
    def RotateSpeedX(self, val): self.RotateSpeedX.set(val)
    @property
    def RotateSpeedY(self):  # type: ()->Float
        return Float(self._node.at("RotateSpeedY"))
    @RotateSpeedY.setter
    def RotateSpeedY(self, val): self.RotateSpeedY.set(val)
    @property
    def SpeedMax(self):  # type: ()->Float
        return Float(self._node.at("SpeedMax"))
    @SpeedMax.setter
    def SpeedMax(self, val): self.SpeedMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




