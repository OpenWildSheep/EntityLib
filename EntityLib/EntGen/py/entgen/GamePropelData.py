
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Float import *

from EntityLibPy import Node

class GamePropelData(HelperObject):
    schema_name = "GamePropelData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GamePropelData
        return GamePropelData(entlib.load_node_file(sourcefile, entlib.get_schema(GamePropelData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GamePropelData
        return GamePropelData(entlib.make_node(GamePropelData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AttractorFactorFallThreshold(self):  # type: ()->Float
        return Float(self._node.at("AttractorFactorFallThreshold"))
    @AttractorFactorFallThreshold.setter
    def AttractorFactorFallThreshold(self, val): self.AttractorFactorFallThreshold.set(val)
    @property
    def AttractorFactorRaiseThreshold(self):  # type: ()->Float
        return Float(self._node.at("AttractorFactorRaiseThreshold"))
    @AttractorFactorRaiseThreshold.setter
    def AttractorFactorRaiseThreshold(self, val): self.AttractorFactorRaiseThreshold.set(val)
    @property
    def EnterAngleMin(self):  # type: ()->Float
        return Float(self._node.at("EnterAngleMin"))
    @EnterAngleMin.setter
    def EnterAngleMin(self, val): self.EnterAngleMin.set(val)
    @property
    def EnterSpeedMin(self):  # type: ()->Float
        return Float(self._node.at("EnterSpeedMin"))
    @EnterSpeedMin.setter
    def EnterSpeedMin(self, val): self.EnterSpeedMin.set(val)
    @property
    def Speed(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Speed"))
    @Speed.setter
    def Speed(self, val): self.Speed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




