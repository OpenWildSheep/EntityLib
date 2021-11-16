
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Color import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class EditorManager(HelperObject):
    schema_name = "EditorManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EditorManager
        return EditorManager(entlib.load_node_file(sourcefile, entlib.get_schema(EditorManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EditorManager
        return EditorManager(entlib.make_node(EditorManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivateMouseControl(self):  # type: ()->Bool
        return Bool(self._node.at("ActivateMouseControl"))
    @ActivateMouseControl.setter
    def ActivateMouseControl(self, val): self.ActivateMouseControl.set(val)
    @property
    def DisableDisplayDebugEntityInfo(self):  # type: ()->Bool
        return Bool(self._node.at("DisableDisplayDebugEntityInfo"))
    @DisableDisplayDebugEntityInfo.setter
    def DisableDisplayDebugEntityInfo(self, val): self.DisableDisplayDebugEntityInfo.set(val)
    @property
    def GameBlockedWhenActive(self):  # type: ()->Bool
        return Bool(self._node.at("GameBlockedWhenActive"))
    @GameBlockedWhenActive.setter
    def GameBlockedWhenActive(self, val): self.GameBlockedWhenActive.set(val)
    @property
    def MoveZ_Blend(self):  # type: ()->Float
        return Float(self._node.at("MoveZ_Blend"))
    @MoveZ_Blend.setter
    def MoveZ_Blend(self, val): self.MoveZ_Blend.set(val)
    @property
    def MoveZ_BlendJoy(self):  # type: ()->Float
        return Float(self._node.at("MoveZ_BlendJoy"))
    @MoveZ_BlendJoy.setter
    def MoveZ_BlendJoy(self, val): self.MoveZ_BlendJoy.set(val)
    @property
    def MoveZ_SpeedAtScreenWidthMax(self):  # type: ()->Float
        return Float(self._node.at("MoveZ_SpeedAtScreenWidthMax"))
    @MoveZ_SpeedAtScreenWidthMax.setter
    def MoveZ_SpeedAtScreenWidthMax(self, val): self.MoveZ_SpeedAtScreenWidthMax.set(val)
    @property
    def MoveZ_SpeedAtScreenWidthMin(self):  # type: ()->Float
        return Float(self._node.at("MoveZ_SpeedAtScreenWidthMin"))
    @MoveZ_SpeedAtScreenWidthMin.setter
    def MoveZ_SpeedAtScreenWidthMin(self, val): self.MoveZ_SpeedAtScreenWidthMin.set(val)
    @property
    def Rotate_AccelerationTime(self):  # type: ()->Float
        return Float(self._node.at("Rotate_AccelerationTime"))
    @Rotate_AccelerationTime.setter
    def Rotate_AccelerationTime(self, val): self.Rotate_AccelerationTime.set(val)
    @property
    def Rotate_Blend(self):  # type: ()->Float
        return Float(self._node.at("Rotate_Blend"))
    @Rotate_Blend.setter
    def Rotate_Blend(self, val): self.Rotate_Blend.set(val)
    @property
    def Rotate_Speed(self):  # type: ()->Float
        return Float(self._node.at("Rotate_Speed"))
    @Rotate_Speed.setter
    def Rotate_Speed(self, val): self.Rotate_Speed.set(val)
    @property
    def Scale_AccelerationTime(self):  # type: ()->Float
        return Float(self._node.at("Scale_AccelerationTime"))
    @Scale_AccelerationTime.setter
    def Scale_AccelerationTime(self, val): self.Scale_AccelerationTime.set(val)
    @property
    def Scale_Blend(self):  # type: ()->Float
        return Float(self._node.at("Scale_Blend"))
    @Scale_Blend.setter
    def Scale_Blend(self, val): self.Scale_Blend.set(val)
    @property
    def Scale_Speed(self):  # type: ()->Float
        return Float(self._node.at("Scale_Speed"))
    @Scale_Speed.setter
    def Scale_Speed(self, val): self.Scale_Speed.set(val)
    @property
    def Selection_DistanceMax(self):  # type: ()->Float
        return Float(self._node.at("Selection_DistanceMax"))
    @Selection_DistanceMax.setter
    def Selection_DistanceMax(self, val): self.Selection_DistanceMax.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def Text_BackgroundColor(self):  # type: ()->Color
        return Color(self._node.at("Text_BackgroundColor"))
    @Text_BackgroundColor.setter
    def Text_BackgroundColor(self, val): self.Text_BackgroundColor.set(val)
    @property
    def Text_DefaultColor(self):  # type: ()->Color
        return Color(self._node.at("Text_DefaultColor"))
    @Text_DefaultColor.setter
    def Text_DefaultColor(self, val): self.Text_DefaultColor.set(val)
    @property
    def Text_Scale(self):  # type: ()->Float
        return Float(self._node.at("Text_Scale"))
    @Text_Scale.setter
    def Text_Scale(self, val): self.Text_Scale.set(val)
    @property
    def Text_SelectedColor(self):  # type: ()->Color
        return Color(self._node.at("Text_SelectedColor"))
    @Text_SelectedColor.setter
    def Text_SelectedColor(self, val): self.Text_SelectedColor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




