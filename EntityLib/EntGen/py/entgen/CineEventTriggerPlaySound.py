
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *


class CineEventTriggerPlaySound(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerPlaySound"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerPlaySound.schema_name))
    @property
    def SoundEventName(self): return String(self._node.at("SoundEventName"))
    @SoundEventName.setter
    def SoundEventName(self, val): self.SoundEventName.set(val)
    @property
    def Super(self): return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




