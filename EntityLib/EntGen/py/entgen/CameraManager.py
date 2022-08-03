
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CameraEditorData import *
from entgen.CameraFreeData import *
from entgen.Float import *
from entgen.Manager import *
from entgen.ScaleConverter import *
from entgen.Vector2 import *

from EntityLibPy import Node

class CameraManager(HelperObject):
    schema_name = "CameraManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraManager
        return CameraManager(entlib.load_node_file(sourcefile, entlib.get_schema(CameraManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraManager
        return CameraManager(entlib.make_node(CameraManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivateDoF(self):  # type: ()->Bool
        return Bool(self._node.at("ActivateDoF"))
    @ActivateDoF.setter
    def ActivateDoF(self, val): self.ActivateDoF.set(val)
    @property
    def AnglesLevels(self):  # type: ()->Vector2
        return Vector2(self._node.at("AnglesLevels"))
    @AnglesLevels.setter
    def AnglesLevels(self, val): self.AnglesLevels.set(val)
    @property
    def CameraControlAxisInvertX(self):  # type: ()->Bool
        return Bool(self._node.at("CameraControlAxisInvertX"))
    @CameraControlAxisInvertX.setter
    def CameraControlAxisInvertX(self, val): self.CameraControlAxisInvertX.set(val)
    @property
    def CameraControlAxisInvertY(self):  # type: ()->Bool
        return Bool(self._node.at("CameraControlAxisInvertY"))
    @CameraControlAxisInvertY.setter
    def CameraControlAxisInvertY(self, val): self.CameraControlAxisInvertY.set(val)
    @property
    def DistanceFromTopPosition(self):  # type: ()->Vector2
        return Vector2(self._node.at("DistanceFromTopPosition"))
    @DistanceFromTopPosition.setter
    def DistanceFromTopPosition(self, val): self.DistanceFromTopPosition.set(val)
    @property
    def Editor(self):  # type: ()->CameraEditorData
        return CameraEditorData(self._node.at("Editor"))
    @property
    def Free(self):  # type: ()->CameraFreeData
        return CameraFreeData(self._node.at("Free"))
    @property
    def HeightLevel(self):  # type: ()->Vector2
        return Vector2(self._node.at("HeightLevel"))
    @HeightLevel.setter
    def HeightLevel(self, val): self.HeightLevel.set(val)
    @property
    def JoyThreshold(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("JoyThreshold"))
    @property
    def RotatePitchIn(self):  # type: ()->Float
        return Float(self._node.at("RotatePitchIn"))
    @RotatePitchIn.setter
    def RotatePitchIn(self, val): self.RotatePitchIn.set(val)
    @property
    def RotatePitchOut(self):  # type: ()->Float
        return Float(self._node.at("RotatePitchOut"))
    @RotatePitchOut.setter
    def RotatePitchOut(self, val): self.RotatePitchOut.set(val)
    @property
    def RotateYawIn(self):  # type: ()->Float
        return Float(self._node.at("RotateYawIn"))
    @RotateYawIn.setter
    def RotateYawIn(self, val): self.RotateYawIn.set(val)
    @property
    def RotateYawOut(self):  # type: ()->Float
        return Float(self._node.at("RotateYawOut"))
    @RotateYawOut.setter
    def RotateYawOut(self, val): self.RotateYawOut.set(val)
    @property
    def SpeedHorizontal(self):  # type: ()->Float
        return Float(self._node.at("SpeedHorizontal"))
    @SpeedHorizontal.setter
    def SpeedHorizontal(self, val): self.SpeedHorizontal.set(val)
    @property
    def SpeedVertical(self):  # type: ()->Float
        return Float(self._node.at("SpeedVertical"))
    @SpeedVertical.setter
    def SpeedVertical(self, val): self.SpeedVertical.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




