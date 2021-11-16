
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameFlyData_Dive(HelperObject):
    schema_name = "GameFlyData::Dive"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFlyData_Dive
        return GameFlyData_Dive(entlib.load_node_file(sourcefile, entlib.get_schema(GameFlyData_Dive.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFlyData_Dive
        return GameFlyData_Dive(entlib.make_node(GameFlyData_Dive.schema_name))
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
    def SpeedFastFactor(self):  # type: ()->Float
        return Float(self._node.at("SpeedFastFactor"))
    @SpeedFastFactor.setter
    def SpeedFastFactor(self, val): self.SpeedFastFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




