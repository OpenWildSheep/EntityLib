
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GamePadSpeedBehaviorData(HelperObject):
    schema_name = "GamePadSpeedBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GamePadSpeedBehaviorData
        return GamePadSpeedBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(GamePadSpeedBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GamePadSpeedBehaviorData
        return GamePadSpeedBehaviorData(entlib.make_node(GamePadSpeedBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DeadZoneThreshold(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("DeadZoneThreshold"))
    @property
    def JoyAcceleration(self):  # type: ()->Float
        return Float(self._node.at("JoyAcceleration"))
    @JoyAcceleration.setter
    def JoyAcceleration(self, val): self.JoyAcceleration.set(val)
    @property
    def PostponeDelayMax(self):  # type: ()->Float
        return Float(self._node.at("PostponeDelayMax"))
    @PostponeDelayMax.setter
    def PostponeDelayMax(self, val): self.PostponeDelayMax.set(val)
    @property
    def SpeedFastMinDuration(self):  # type: ()->Float
        return Float(self._node.at("SpeedFastMinDuration"))
    @SpeedFastMinDuration.setter
    def SpeedFastMinDuration(self, val): self.SpeedFastMinDuration.set(val)
    @property
    def SpeedMediumThreshold(self):  # type: ()->Float
        return Float(self._node.at("SpeedMediumThreshold"))
    @SpeedMediumThreshold.setter
    def SpeedMediumThreshold(self, val): self.SpeedMediumThreshold.set(val)
    @property
    def SpeedSlowThreshold(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedSlowThreshold"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




