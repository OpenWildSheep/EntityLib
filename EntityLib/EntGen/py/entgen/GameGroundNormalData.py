
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameGroundNormalData(HelperObject):
    schema_name = "GameGroundNormalData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameGroundNormalData
        return GameGroundNormalData(entlib.load_node_file(sourcefile, entlib.get_schema(GameGroundNormalData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameGroundNormalData
        return GameGroundNormalData(entlib.make_node(GameGroundNormalData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AgainstWallTimeHysteresis(self):  # type: ()->Float
        return Float(self._node.at("AgainstWallTimeHysteresis"))
    @AgainstWallTimeHysteresis.setter
    def AgainstWallTimeHysteresis(self, val): self.AgainstWallTimeHysteresis.set(val)
    @property
    def IsOnStepTimeHysteresis(self):  # type: ()->Float
        return Float(self._node.at("IsOnStepTimeHysteresis"))
    @IsOnStepTimeHysteresis.setter
    def IsOnStepTimeHysteresis(self, val): self.IsOnStepTimeHysteresis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




