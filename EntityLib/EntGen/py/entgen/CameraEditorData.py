
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CameraEditorData(HelperObject):
    schema_name = "CameraEditorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraEditorData
        return CameraEditorData(entlib.load_node_file(sourcefile, entlib.get_schema(CameraEditorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraEditorData
        return CameraEditorData(entlib.make_node(CameraEditorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DistanceMax(self):  # type: ()->Float
        return Float(self._node.at("DistanceMax"))
    @DistanceMax.setter
    def DistanceMax(self, val): self.DistanceMax.set(val)
    @property
    def DistanceMin(self):  # type: ()->Float
        return Float(self._node.at("DistanceMin"))
    @DistanceMin.setter
    def DistanceMin(self, val): self.DistanceMin.set(val)
    @property
    def JoyThreshold(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("JoyThreshold"))
    @property
    def MoveBlend(self):  # type: ()->Float
        return Float(self._node.at("MoveBlend"))
    @MoveBlend.setter
    def MoveBlend(self, val): self.MoveBlend.set(val)
    @property
    def MoveSpeedAtScreenWidthMax(self):  # type: ()->Float
        return Float(self._node.at("MoveSpeedAtScreenWidthMax"))
    @MoveSpeedAtScreenWidthMax.setter
    def MoveSpeedAtScreenWidthMax(self, val): self.MoveSpeedAtScreenWidthMax.set(val)
    @property
    def MoveSpeedAtScreenWidthMin(self):  # type: ()->Float
        return Float(self._node.at("MoveSpeedAtScreenWidthMin"))
    @MoveSpeedAtScreenWidthMin.setter
    def MoveSpeedAtScreenWidthMin(self, val): self.MoveSpeedAtScreenWidthMin.set(val)
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
    def ScreenWidthMax(self):  # type: ()->Float
        return Float(self._node.at("ScreenWidthMax"))
    @ScreenWidthMax.setter
    def ScreenWidthMax(self, val): self.ScreenWidthMax.set(val)
    @property
    def ScreenWidthMin(self):  # type: ()->Float
        return Float(self._node.at("ScreenWidthMin"))
    @ScreenWidthMin.setter
    def ScreenWidthMin(self, val): self.ScreenWidthMin.set(val)
    @property
    def ZoomBlend(self):  # type: ()->Float
        return Float(self._node.at("ZoomBlend"))
    @ZoomBlend.setter
    def ZoomBlend(self, val): self.ZoomBlend.set(val)
    @property
    def ZoomSpeedAtScreenWidthMax(self):  # type: ()->Float
        return Float(self._node.at("ZoomSpeedAtScreenWidthMax"))
    @ZoomSpeedAtScreenWidthMax.setter
    def ZoomSpeedAtScreenWidthMax(self, val): self.ZoomSpeedAtScreenWidthMax.set(val)
    @property
    def ZoomSpeedAtScreenWidthMin(self):  # type: ()->Float
        return Float(self._node.at("ZoomSpeedAtScreenWidthMin"))
    @ZoomSpeedAtScreenWidthMin.setter
    def ZoomSpeedAtScreenWidthMin(self, val): self.ZoomSpeedAtScreenWidthMin.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




