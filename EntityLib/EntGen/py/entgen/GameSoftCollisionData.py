
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameSoftCollisionData(HelperObject):
    schema_name = "GameSoftCollisionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameSoftCollisionData
        return GameSoftCollisionData(entlib.load_node_file(sourcefile, entlib.get_schema(GameSoftCollisionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameSoftCollisionData
        return GameSoftCollisionData(entlib.make_node(GameSoftCollisionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DecelerationFactor(self):  # type: ()->Float
        return Float(self._node.at("DecelerationFactor"))
    @DecelerationFactor.setter
    def DecelerationFactor(self, val): self.DecelerationFactor.set(val)
    @property
    def InsidePenetrationCoeff(self):  # type: ()->Float
        return Float(self._node.at("InsidePenetrationCoeff"))
    @InsidePenetrationCoeff.setter
    def InsidePenetrationCoeff(self, val): self.InsidePenetrationCoeff.set(val)
    @property
    def MaxSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("MaxSpeedFactor"))
    @MaxSpeedFactor.setter
    def MaxSpeedFactor(self, val): self.MaxSpeedFactor.set(val)
    @property
    def MinSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("MinSpeedFactor"))
    @MinSpeedFactor.setter
    def MinSpeedFactor(self, val): self.MinSpeedFactor.set(val)
    @property
    def MinSpeedMode(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("MinSpeedMode"))
    @MinSpeedMode.setter
    def MinSpeedMode(self, val): self.MinSpeedMode.set(val)
    @property
    def StuckDuration(self):  # type: ()->Float
        return Float(self._node.at("StuckDuration"))
    @StuckDuration.setter
    def StuckDuration(self, val): self.StuckDuration.set(val)
    @property
    def StuckPenetrationCoeff(self):  # type: ()->Float
        return Float(self._node.at("StuckPenetrationCoeff"))
    @StuckPenetrationCoeff.setter
    def StuckPenetrationCoeff(self, val): self.StuckPenetrationCoeff.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




