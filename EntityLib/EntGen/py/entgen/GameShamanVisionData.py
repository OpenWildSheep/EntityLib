
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameShamanVisionData(HelperObject):
    schema_name = "GameShamanVisionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameShamanVisionData
        return GameShamanVisionData(entlib.load_node_file(sourcefile, entlib.get_schema(GameShamanVisionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameShamanVisionData
        return GameShamanVisionData(entlib.make_node(GameShamanVisionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AudioAngle(self):  # type: ()->Float
        return Float(self._node.at("AudioAngle"))
    @AudioAngle.setter
    def AudioAngle(self, val): self.AudioAngle.set(val)
    @property
    def IconDisableDisplayDuration(self):  # type: ()->Float
        return Float(self._node.at("IconDisableDisplayDuration"))
    @IconDisableDisplayDuration.setter
    def IconDisableDisplayDuration(self, val): self.IconDisableDisplayDuration.set(val)
    @property
    def IconDisplayDuration(self):  # type: ()->Float
        return Float(self._node.at("IconDisplayDuration"))
    @IconDisplayDuration.setter
    def IconDisplayDuration(self, val): self.IconDisplayDuration.set(val)
    @property
    def IconEnableDisplayDuration(self):  # type: ()->Float
        return Float(self._node.at("IconEnableDisplayDuration"))
    @IconEnableDisplayDuration.setter
    def IconEnableDisplayDuration(self, val): self.IconEnableDisplayDuration.set(val)
    @property
    def IntensityGoddess(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("IntensityGoddess"))
    @property
    def IntensityPlayer(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("IntensityPlayer"))
    @property
    def IntensitySpecie(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("IntensitySpecie"))
    @property
    def PerceptionGoddess(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("PerceptionGoddess"))
    @property
    def PerceptionPlayer(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("PerceptionPlayer"))
    @property
    def PerceptionSpecie(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("PerceptionSpecie"))
    @property
    def Sound_Locate_HeartBeat(self):  # type: ()->String
        return String(self._node.at("Sound_Locate_HeartBeat"))
    @Sound_Locate_HeartBeat.setter
    def Sound_Locate_HeartBeat(self, val): self.Sound_Locate_HeartBeat.set(val)
    @property
    def Sound_UI_Locate_HeartBeat_Stop(self):  # type: ()->String
        return String(self._node.at("Sound_UI_Locate_HeartBeat_Stop"))
    @Sound_UI_Locate_HeartBeat_Stop.setter
    def Sound_UI_Locate_HeartBeat_Stop(self, val): self.Sound_UI_Locate_HeartBeat_Stop.set(val)
    @property
    def Sound_UI_Locate_In(self):  # type: ()->String
        return String(self._node.at("Sound_UI_Locate_In"))
    @Sound_UI_Locate_In.setter
    def Sound_UI_Locate_In(self, val): self.Sound_UI_Locate_In.set(val)
    @property
    def Sound_UI_Locate_Out(self):  # type: ()->String
        return String(self._node.at("Sound_UI_Locate_Out"))
    @Sound_UI_Locate_Out.setter
    def Sound_UI_Locate_Out(self, val): self.Sound_UI_Locate_Out.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




