
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameBeamSnapData(HelperObject):
    schema_name = "GameBeamSnapData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameBeamSnapData
        return GameBeamSnapData(entlib.load_node_file(sourcefile, entlib.get_schema(GameBeamSnapData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameBeamSnapData
        return GameBeamSnapData(entlib.make_node(GameBeamSnapData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Max2DDist(self):  # type: ()->Float
        return Float(self._node.at("Max2DDist"))
    @Max2DDist.setter
    def Max2DDist(self, val): self.Max2DDist.set(val)
    @property
    def Max2DDistScoreCoeff(self):  # type: ()->Float
        return Float(self._node.at("Max2DDistScoreCoeff"))
    @Max2DDistScoreCoeff.setter
    def Max2DDistScoreCoeff(self, val): self.Max2DDistScoreCoeff.set(val)
    @property
    def Max3DDistScoreCoeff(self):  # type: ()->Float
        return Float(self._node.at("Max3DDistScoreCoeff"))
    @Max3DDistScoreCoeff.setter
    def Max3DDistScoreCoeff(self, val): self.Max3DDistScoreCoeff.set(val)
    @property
    def MinCameraDepth(self):  # type: ()->Float
        return Float(self._node.at("MinCameraDepth"))
    @MinCameraDepth.setter
    def MinCameraDepth(self, val): self.MinCameraDepth.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




