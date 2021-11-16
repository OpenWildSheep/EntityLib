
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameSlopeData(HelperObject):
    schema_name = "GameSlopeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameSlopeData
        return GameSlopeData(entlib.load_node_file(sourcefile, entlib.get_schema(GameSlopeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameSlopeData
        return GameSlopeData(entlib.make_node(GameSlopeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngleMin(self):  # type: ()->Float
        return Float(self._node.at("AngleMin"))
    @AngleMin.setter
    def AngleMin(self, val): self.AngleMin.set(val)
    @property
    def AngleMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("AngleMinHysteresis"))
    @AngleMinHysteresis.setter
    def AngleMinHysteresis(self, val): self.AngleMinHysteresis.set(val)
    @property
    def ForceAgainstSlopeAdherenceMin(self):  # type: ()->Float
        return Float(self._node.at("ForceAgainstSlopeAdherenceMin"))
    @ForceAgainstSlopeAdherenceMin.setter
    def ForceAgainstSlopeAdherenceMin(self, val): self.ForceAgainstSlopeAdherenceMin.set(val)
    @property
    def ForceAgainstSlopeAdherenceMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("ForceAgainstSlopeAdherenceMinHysteresis"))
    @ForceAgainstSlopeAdherenceMinHysteresis.setter
    def ForceAgainstSlopeAdherenceMinHysteresis(self, val): self.ForceAgainstSlopeAdherenceMinHysteresis.set(val)
    @property
    def OrientationDotMin(self):  # type: ()->Float
        return Float(self._node.at("OrientationDotMin"))
    @OrientationDotMin.setter
    def OrientationDotMin(self, val): self.OrientationDotMin.set(val)
    @property
    def OrientationDotMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("OrientationDotMinHysteresis"))
    @OrientationDotMinHysteresis.setter
    def OrientationDotMinHysteresis(self, val): self.OrientationDotMinHysteresis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




