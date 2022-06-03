
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameDeathData(HelperObject):
    schema_name = "GameDeathData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameDeathData
        return GameDeathData(entlib.load_node_file(sourcefile, entlib.get_schema(GameDeathData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameDeathData
        return GameDeathData(entlib.make_node(GameDeathData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def defaultFreedDelay(self):  # type: ()->Float
        return Float(self._node.at("defaultFreedDelay"))
    @defaultFreedDelay.setter
    def defaultFreedDelay(self, val): self.defaultFreedDelay.set(val)
    @property
    def immersedFreedDelay(self):  # type: ()->Float
        return Float(self._node.at("immersedFreedDelay"))
    @immersedFreedDelay.setter
    def immersedFreedDelay(self, val): self.immersedFreedDelay.set(val)
    @property
    def leavingLavaDelay(self):  # type: ()->Float
        return Float(self._node.at("leavingLavaDelay"))
    @leavingLavaDelay.setter
    def leavingLavaDelay(self, val): self.leavingLavaDelay.set(val)
    @property
    def meetingLavaDelay(self):  # type: ()->Float
        return Float(self._node.at("meetingLavaDelay"))
    @meetingLavaDelay.setter
    def meetingLavaDelay(self, val): self.meetingLavaDelay.set(val)
    pass




