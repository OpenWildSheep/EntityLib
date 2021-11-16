
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *

from EntityLibPy import Node

class SmallActorSpawnRuleExchangeData(HelperObject):
    schema_name = "SmallActorSpawnRuleExchangeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmallActorSpawnRuleExchangeData
        return SmallActorSpawnRuleExchangeData(entlib.load_node_file(sourcefile, entlib.get_schema(SmallActorSpawnRuleExchangeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmallActorSpawnRuleExchangeData
        return SmallActorSpawnRuleExchangeData(entlib.make_node(SmallActorSpawnRuleExchangeData.schema_name))
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
    def IsValid(self):  # type: ()->Bool
        return Bool(self._node.at("IsValid"))
    @IsValid.setter
    def IsValid(self, val): self.IsValid.set(val)
    @property
    def RuleIndex(self):  # type: ()->Int
        return Int(self._node.at("RuleIndex"))
    @RuleIndex.setter
    def RuleIndex(self, val): self.RuleIndex.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




