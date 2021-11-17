
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameImmersionData(HelperObject):
    schema_name = "GameImmersionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameImmersionData
        return GameImmersionData(entlib.load_node_file(sourcefile, entlib.get_schema(GameImmersionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameImmersionData
        return GameImmersionData(entlib.make_node(GameImmersionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def friction(self):  # type: ()->Float
        return Float(self._node.at("friction"))
    @friction.setter
    def friction(self, val): self.friction.set(val)
    @property
    def immersedFactor(self):  # type: ()->Float
        return Float(self._node.at("immersedFactor"))
    @immersedFactor.setter
    def immersedFactor(self, val): self.immersedFactor.set(val)
    @property
    def immersedFactorMaxToJump(self):  # type: ()->Float
        return Float(self._node.at("immersedFactorMaxToJump"))
    @immersedFactorMaxToJump.setter
    def immersedFactorMaxToJump(self, val): self.immersedFactorMaxToJump.set(val)
    @property
    def pitchMaxAngleToJump(self):  # type: ()->Float
        return Float(self._node.at("pitchMaxAngleToJump"))
    @pitchMaxAngleToJump.setter
    def pitchMaxAngleToJump(self, val): self.pitchMaxAngleToJump.set(val)
    @property
    def pitchMinAngleToJump(self):  # type: ()->Float
        return Float(self._node.at("pitchMinAngleToJump"))
    @pitchMinAngleToJump.setter
    def pitchMinAngleToJump(self, val): self.pitchMinAngleToJump.set(val)
    @property
    def reachSurfaceAcceleration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("reachSurfaceAcceleration"))
    @property
    def speedZMinToJump(self):  # type: ()->Float
        return Float(self._node.at("speedZMinToJump"))
    @speedZMinToJump.setter
    def speedZMinToJump(self, val): self.speedZMinToJump.set(val)
    pass




