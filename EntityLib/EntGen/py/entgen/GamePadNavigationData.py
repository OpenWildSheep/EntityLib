
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GamePadNavigationData(HelperObject):
    schema_name = "GamePadNavigationData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GamePadNavigationData
        return GamePadNavigationData(entlib.load_node_file(sourcefile, entlib.get_schema(GamePadNavigationData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GamePadNavigationData
        return GamePadNavigationData(entlib.make_node(GamePadNavigationData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def clamberDirectionDeltaAngle(self):  # type: ()->Float
        return Float(self._node.at("clamberDirectionDeltaAngle"))
    @clamberDirectionDeltaAngle.setter
    def clamberDirectionDeltaAngle(self, val): self.clamberDirectionDeltaAngle.set(val)
    @property
    def invertInputFactor(self):  # type: ()->Float
        return Float(self._node.at("invertInputFactor"))
    @invertInputFactor.setter
    def invertInputFactor(self, val): self.invertInputFactor.set(val)
    @property
    def joyLockedAngularSpeedMax(self):  # type: ()->Float
        return Float(self._node.at("joyLockedAngularSpeedMax"))
    @joyLockedAngularSpeedMax.setter
    def joyLockedAngularSpeedMax(self, val): self.joyLockedAngularSpeedMax.set(val)
    @property
    def meshNavigationMaxDeltaAngleToKeepInputLock(self):  # type: ()->Float
        return Float(self._node.at("meshNavigationMaxDeltaAngleToKeepInputLock"))
    @meshNavigationMaxDeltaAngleToKeepInputLock.setter
    def meshNavigationMaxDeltaAngleToKeepInputLock(self, val): self.meshNavigationMaxDeltaAngleToKeepInputLock.set(val)
    @property
    def normalAlignmentToKeepTrajectory(self):  # type: ()->Float
        return Float(self._node.at("normalAlignmentToKeepTrajectory"))
    @normalAlignmentToKeepTrajectory.setter
    def normalAlignmentToKeepTrajectory(self, val): self.normalAlignmentToKeepTrajectory.set(val)
    pass




