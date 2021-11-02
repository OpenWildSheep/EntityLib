
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameFlyData_FlyDown(HelperObject):
    schema_name = "GameFlyData::FlyDown"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFlyData_FlyDown
        return GameFlyData_FlyDown(entlib.load_node_file(sourcefile, entlib.get_schema(GameFlyData_FlyDown.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFlyData_FlyDown
        return GameFlyData_FlyDown(entlib.make_node(GameFlyData_FlyDown.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Acceleration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Acceleration"))
    @property
    def Deceleration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Deceleration"))
    @property
    def ExitDeceleration(self):  # type: ()->Float
        return Float(self._node.at("ExitDeceleration"))
    @ExitDeceleration.setter
    def ExitDeceleration(self, val): self.ExitDeceleration.set(val)
    @property
    def PitchStart(self):  # type: ()->Float
        return Float(self._node.at("PitchStart"))
    @PitchStart.setter
    def PitchStart(self, val): self.PitchStart.set(val)
    @property
    def SpeedSlowFactor(self):  # type: ()->Float
        return Float(self._node.at("SpeedSlowFactor"))
    @SpeedSlowFactor.setter
    def SpeedSlowFactor(self, val): self.SpeedSlowFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




