
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameReviveData(HelperObject):
    schema_name = "GameReviveData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameReviveData
        return GameReviveData(entlib.load_node_file(sourcefile, entlib.get_schema(GameReviveData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameReviveData
        return GameReviveData(entlib.make_node(GameReviveData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnimPlayRatioSpeedIn(self):  # type: ()->Float
        return Float(self._node.at("AnimPlayRatioSpeedIn"))
    @AnimPlayRatioSpeedIn.setter
    def AnimPlayRatioSpeedIn(self, val): self.AnimPlayRatioSpeedIn.set(val)
    @property
    def AnimPlayRatioSpeedOut(self):  # type: ()->Float
        return Float(self._node.at("AnimPlayRatioSpeedOut"))
    @AnimPlayRatioSpeedOut.setter
    def AnimPlayRatioSpeedOut(self, val): self.AnimPlayRatioSpeedOut.set(val)
    @property
    def AnimPlayRatioSpeedRate(self):  # type: ()->Float
        return Float(self._node.at("AnimPlayRatioSpeedRate"))
    @AnimPlayRatioSpeedRate.setter
    def AnimPlayRatioSpeedRate(self, val): self.AnimPlayRatioSpeedRate.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




