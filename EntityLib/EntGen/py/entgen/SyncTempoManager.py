
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Manager import *

from EntityLibPy import Node

class SyncTempoManager(HelperObject):
    schema_name = "SyncTempoManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SyncTempoManager
        return SyncTempoManager(entlib.load_node_file(sourcefile, entlib.get_schema(SyncTempoManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SyncTempoManager
        return SyncTempoManager(entlib.make_node(SyncTempoManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DefaultTempo(self):  # type: ()->Int
        return Int(self._node.at("DefaultTempo"))
    @DefaultTempo.setter
    def DefaultTempo(self, val): self.DefaultTempo.set(val)
    @property
    def RTPC_Tempo(self):  # type: ()->String
        return String(self._node.at("RTPC_Tempo"))
    @RTPC_Tempo.setter
    def RTPC_Tempo(self, val): self.RTPC_Tempo.set(val)
    @property
    def StartSyncClickEvent(self):  # type: ()->String
        return String(self._node.at("StartSyncClickEvent"))
    @StartSyncClickEvent.setter
    def StartSyncClickEvent(self, val): self.StartSyncClickEvent.set(val)
    @property
    def StartSyncEvent(self):  # type: ()->String
        return String(self._node.at("StartSyncEvent"))
    @StartSyncEvent.setter
    def StartSyncEvent(self, val): self.StartSyncEvent.set(val)
    @property
    def StopSyncClickEvent(self):  # type: ()->String
        return String(self._node.at("StopSyncClickEvent"))
    @StopSyncClickEvent.setter
    def StopSyncClickEvent(self, val): self.StopSyncClickEvent.set(val)
    @property
    def StopSyncEvent(self):  # type: ()->String
        return String(self._node.at("StopSyncEvent"))
    @StopSyncEvent.setter
    def StopSyncEvent(self, val): self.StopSyncEvent.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




