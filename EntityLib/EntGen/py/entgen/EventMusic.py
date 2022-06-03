
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SyncTempoMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class EventMusic(HelperObject):
    schema_name = "EventMusic"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EventMusic
        return EventMusic(entlib.load_node_file(sourcefile, entlib.get_schema(EventMusic.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EventMusic
        return EventMusic(entlib.make_node(EventMusic.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PlayerDeathBank(self):  # type: ()->String
        return String(self._node.at("PlayerDeathBank"))
    @PlayerDeathBank.setter
    def PlayerDeathBank(self, val): self.PlayerDeathBank.set(val)
    @property
    def PlayerDeathEvent(self):  # type: ()->String
        return String(self._node.at("PlayerDeathEvent"))
    @PlayerDeathEvent.setter
    def PlayerDeathEvent(self, val): self.PlayerDeathEvent.set(val)
    @property
    def PlayerDeathMusicPriority(self):  # type: ()->Int
        return Int(self._node.at("PlayerDeathMusicPriority"))
    @PlayerDeathMusicPriority.setter
    def PlayerDeathMusicPriority(self, val): self.PlayerDeathMusicPriority.set(val)
    @property
    def PlayerDeathTimeOnStack(self):  # type: ()->Float
        return Float(self._node.at("PlayerDeathTimeOnStack"))
    @PlayerDeathTimeOnStack.setter
    def PlayerDeathTimeOnStack(self, val): self.PlayerDeathTimeOnStack.set(val)
    @property
    def PlayerVictoryBank(self):  # type: ()->String
        return String(self._node.at("PlayerVictoryBank"))
    @PlayerVictoryBank.setter
    def PlayerVictoryBank(self, val): self.PlayerVictoryBank.set(val)
    @property
    def PlayerVictoryEvent(self):  # type: ()->String
        return String(self._node.at("PlayerVictoryEvent"))
    @PlayerVictoryEvent.setter
    def PlayerVictoryEvent(self, val): self.PlayerVictoryEvent.set(val)
    @property
    def ReleaseCreatureBankPrefix(self):  # type: ()->String
        return String(self._node.at("ReleaseCreatureBankPrefix"))
    @ReleaseCreatureBankPrefix.setter
    def ReleaseCreatureBankPrefix(self, val): self.ReleaseCreatureBankPrefix.set(val)
    @property
    def ReleaseCreatureEventPrefix(self):  # type: ()->String
        return String(self._node.at("ReleaseCreatureEventPrefix"))
    @ReleaseCreatureEventPrefix.setter
    def ReleaseCreatureEventPrefix(self, val): self.ReleaseCreatureEventPrefix.set(val)
    @property
    def ReleaseCreatureMusicPriority(self):  # type: ()->Int
        return Int(self._node.at("ReleaseCreatureMusicPriority"))
    @ReleaseCreatureMusicPriority.setter
    def ReleaseCreatureMusicPriority(self, val): self.ReleaseCreatureMusicPriority.set(val)
    @property
    def ReleaseCreatureTimeOnStack(self):  # type: ()->Float
        return Float(self._node.at("ReleaseCreatureTimeOnStack"))
    @ReleaseCreatureTimeOnStack.setter
    def ReleaseCreatureTimeOnStack(self, val): self.ReleaseCreatureTimeOnStack.set(val)
    @property
    def ReleaseSoulBankPrefix(self):  # type: ()->String
        return String(self._node.at("ReleaseSoulBankPrefix"))
    @ReleaseSoulBankPrefix.setter
    def ReleaseSoulBankPrefix(self, val): self.ReleaseSoulBankPrefix.set(val)
    @property
    def ReleaseSoulEventPrefix(self):  # type: ()->String
        return String(self._node.at("ReleaseSoulEventPrefix"))
    @ReleaseSoulEventPrefix.setter
    def ReleaseSoulEventPrefix(self, val): self.ReleaseSoulEventPrefix.set(val)
    @property
    def ReleaseSoulMusicPriority(self):  # type: ()->Int
        return Int(self._node.at("ReleaseSoulMusicPriority"))
    @ReleaseSoulMusicPriority.setter
    def ReleaseSoulMusicPriority(self, val): self.ReleaseSoulMusicPriority.set(val)
    @property
    def ReleaseSoulTimeOnStack(self):  # type: ()->Float
        return Float(self._node.at("ReleaseSoulTimeOnStack"))
    @ReleaseSoulTimeOnStack.setter
    def ReleaseSoulTimeOnStack(self, val): self.ReleaseSoulTimeOnStack.set(val)
    @property
    def SynchronizationMode(self):  # type: ()->SyncTempoMode
        return SyncTempoMode(self._node.at("SynchronizationMode"))
    @SynchronizationMode.setter
    def SynchronizationMode(self, val): self.SynchronizationMode.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




