
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.GameClockManager_GameDate import *
from entgen.Manager import *

from EntityLibPy import Node

class GameClockManager(HelperObject):
    schema_name = "GameClockManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameClockManager
        return GameClockManager(entlib.load_node_file(sourcefile, entlib.get_schema(GameClockManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameClockManager
        return GameClockManager(entlib.make_node(GameClockManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DayDurationInMin(self):  # type: ()->Int
        return Int(self._node.at("DayDurationInMin"))
    @DayDurationInMin.setter
    def DayDurationInMin(self, val): self.DayDurationInMin.set(val)
    @property
    def DayDurationInMs(self):  # type: ()->Int
        return Int(self._node.at("DayDurationInMs"))
    @DayDurationInMs.setter
    def DayDurationInMs(self, val): self.DayDurationInMs.set(val)
    @property
    def FallDurationInDay(self):  # type: ()->Int
        return Int(self._node.at("FallDurationInDay"))
    @FallDurationInDay.setter
    def FallDurationInDay(self, val): self.FallDurationInDay.set(val)
    @property
    def FreezeTime(self):  # type: ()->Bool
        return Bool(self._node.at("FreezeTime"))
    @FreezeTime.setter
    def FreezeTime(self, val): self.FreezeTime.set(val)
    @property
    def SpringDurationInDay(self):  # type: ()->Int
        return Int(self._node.at("SpringDurationInDay"))
    @SpringDurationInDay.setter
    def SpringDurationInDay(self, val): self.SpringDurationInDay.set(val)
    @property
    def StartTime(self):  # type: ()->GameClockManager_GameDate
        return GameClockManager_GameDate(self._node.at("StartTime"))
    @property
    def SummerDurationInDay(self):  # type: ()->Int
        return Int(self._node.at("SummerDurationInDay"))
    @SummerDurationInDay.setter
    def SummerDurationInDay(self, val): self.SummerDurationInDay.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def WinterDurationInDay(self):  # type: ()->Int
        return Int(self._node.at("WinterDurationInDay"))
    @WinterDurationInDay.setter
    def WinterDurationInDay(self, val): self.WinterDurationInDay.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




