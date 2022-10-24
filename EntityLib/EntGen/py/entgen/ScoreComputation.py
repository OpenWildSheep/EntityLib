
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class ScoreComputation(HelperObject):
    schema_name = "ScoreComputation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ScoreComputation
        return ScoreComputation(entlib.load_node_file(sourcefile, entlib.get_schema(ScoreComputation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ScoreComputation
        return ScoreComputation(entlib.make_node(ScoreComputation.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CameraSightPitchAngleScore(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("CameraSightPitchAngleScore"))
    @property
    def CameraSightYawAngleScore(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("CameraSightYawAngleScore"))
    @property
    def DistanceScore(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("DistanceScore"))
    @property
    def InteractorSightAngleScore(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("InteractorSightAngleScore"))
    @property
    def JoystickDirectionAngleScore(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("JoystickDirectionAngleScore"))
    @property
    def MaxDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxDistance"))
    @MaxDistance.setter
    def MaxDistance(self, val): self.MaxDistance.set(val)
    @property
    def MinScore(self):  # type: ()->Float
        return Float(self._node.at("MinScore"))
    @MinScore.setter
    def MinScore(self, val): self.MinScore.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




