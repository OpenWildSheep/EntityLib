
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameFlyData_FlyUp(HelperObject):
    schema_name = "GameFlyData::FlyUp"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFlyData_FlyUp
        return GameFlyData_FlyUp(entlib.load_node_file(sourcefile, entlib.get_schema(GameFlyData_FlyUp.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFlyData_FlyUp
        return GameFlyData_FlyUp(entlib.make_node(GameFlyData_FlyUp.schema_name))
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
    def SpeedFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedFactor"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




