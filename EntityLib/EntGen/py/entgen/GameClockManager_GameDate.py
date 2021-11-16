
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.GameClockManager_TimeOfDay import *

from EntityLibPy import Node

class GameClockManager_GameDate(HelperObject):
    schema_name = "GameClockManager::GameDate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameClockManager_GameDate
        return GameClockManager_GameDate(entlib.load_node_file(sourcefile, entlib.get_schema(GameClockManager_GameDate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameClockManager_GameDate
        return GameClockManager_GameDate(entlib.make_node(GameClockManager_GameDate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DayOfYear(self):  # type: ()->Int
        return Int(self._node.at("DayOfYear"))
    @DayOfYear.setter
    def DayOfYear(self, val): self.DayOfYear.set(val)
    @property
    def Season(self):  # type: ()->String
        return String(self._node.at("Season"))
    @Season.setter
    def Season(self, val): self.Season.set(val)
    @property
    def TimeOfDay(self):  # type: ()->GameClockManager_TimeOfDay
        return GameClockManager_TimeOfDay(self._node.at("TimeOfDay"))
    @property
    def Year(self):  # type: ()->Int
        return Int(self._node.at("Year"))
    @Year.setter
    def Year(self, val): self.Year.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




