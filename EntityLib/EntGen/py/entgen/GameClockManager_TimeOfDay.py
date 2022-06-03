
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class GameClockManager_TimeOfDay(HelperObject):
    schema_name = "GameClockManager::TimeOfDay"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameClockManager_TimeOfDay
        return GameClockManager_TimeOfDay(entlib.load_node_file(sourcefile, entlib.get_schema(GameClockManager_TimeOfDay.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameClockManager_TimeOfDay
        return GameClockManager_TimeOfDay(entlib.make_node(GameClockManager_TimeOfDay.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Hour(self):  # type: ()->Int
        return Int(self._node.at("Hour"))
    @Hour.setter
    def Hour(self, val): self.Hour.set(val)
    @property
    def Minute(self):  # type: ()->Int
        return Int(self._node.at("Minute"))
    @Minute.setter
    def Minute(self, val): self.Minute.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




