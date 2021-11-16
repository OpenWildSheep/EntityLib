
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GameFlyData_Centrifugal import *
from entgen.GameFlyData_Dive import *
from entgen.GameFlyData_Flap import *
from entgen.GameFlyData_FlyDown import *
from entgen.GameFlyData_FlyUp import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameFlyData(HelperObject):
    schema_name = "GameFlyData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFlyData
        return GameFlyData(entlib.load_node_file(sourcefile, entlib.get_schema(GameFlyData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFlyData
        return GameFlyData(entlib.make_node(GameFlyData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Centrifugal(self):  # type: ()->GameFlyData_Centrifugal
        return GameFlyData_Centrifugal(self._node.at("Centrifugal"))
    @property
    def Dive(self):  # type: ()->GameFlyData_Dive
        return GameFlyData_Dive(self._node.at("Dive"))
    @property
    def Flap(self):  # type: ()->GameFlyData_Flap
        return GameFlyData_Flap(self._node.at("Flap"))
    @property
    def FlyBlendIn(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("FlyBlendIn"))
    @property
    def FlyDown(self):  # type: ()->GameFlyData_FlyDown
        return GameFlyData_FlyDown(self._node.at("FlyDown"))
    @property
    def FlyExitBlendIn(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("FlyExitBlendIn"))
    @property
    def FlyPitchCoeffFromSpeedCoeff(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("FlyPitchCoeffFromSpeedCoeff"))
    @property
    def FlyUp(self):  # type: ()->GameFlyData_FlyUp
        return GameFlyData_FlyUp(self._node.at("FlyUp"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




