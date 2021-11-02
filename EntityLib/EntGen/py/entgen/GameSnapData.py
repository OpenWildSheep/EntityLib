
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameSnapData(HelperObject):
    schema_name = "GameSnapData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameSnapData
        return GameSnapData(entlib.load_node_file(sourcefile, entlib.get_schema(GameSnapData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameSnapData
        return GameSnapData(entlib.make_node(GameSnapData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def creatureSizeCoeff(self):  # type: ()->Float
        return Float(self._node.at("creatureSizeCoeff"))
    @creatureSizeCoeff.setter
    def creatureSizeCoeff(self, val): self.creatureSizeCoeff.set(val)
    @property
    def dirCoeff(self):  # type: ()->Float
        return Float(self._node.at("dirCoeff"))
    @dirCoeff.setter
    def dirCoeff(self, val): self.dirCoeff.set(val)
    @property
    def distCoeff(self):  # type: ()->Float
        return Float(self._node.at("distCoeff"))
    @distCoeff.setter
    def distCoeff(self, val): self.distCoeff.set(val)
    @property
    def maxAngle(self):  # type: ()->Float
        return Float(self._node.at("maxAngle"))
    @maxAngle.setter
    def maxAngle(self, val): self.maxAngle.set(val)
    @property
    def maxDist(self):  # type: ()->Float
        return Float(self._node.at("maxDist"))
    @maxDist.setter
    def maxDist(self, val): self.maxDist.set(val)
    pass




