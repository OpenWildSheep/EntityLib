
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.FloatRange import *

from EntityLibPy import Node

class SmallActorSpawnRuleData(HelperObject):
    schema_name = "SmallActorSpawnRuleData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmallActorSpawnRuleData
        return SmallActorSpawnRuleData(entlib.load_node_file(sourcefile, entlib.get_schema(SmallActorSpawnRuleData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmallActorSpawnRuleData
        return SmallActorSpawnRuleData(entlib.make_node(SmallActorSpawnRuleData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AudioEventName(self):  # type: ()->String
        return String(self._node.at("AudioEventName"))
    @AudioEventName.setter
    def AudioEventName(self, val): self.AudioEventName.set(val)
    @property
    def AudioEventSoundBank(self):  # type: ()->String
        return String(self._node.at("AudioEventSoundBank"))
    @AudioEventSoundBank.setter
    def AudioEventSoundBank(self, val): self.AudioEventSoundBank.set(val)
    @property
    def DayTimeRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("DayTimeRange"))
    @property
    def DistanceRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("DistanceRange"))
    @property
    def PrecipitationRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("PrecipitationRange"))
    @property
    def RegenRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("RegenRange"))
    @property
    def SpawnProbability(self):  # type: ()->Float
        return Float(self._node.at("SpawnProbability"))
    @SpawnProbability.setter
    def SpawnProbability(self, val): self.SpawnProbability.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




