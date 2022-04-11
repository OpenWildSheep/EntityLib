
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *

from EntityLibPy import Node

class CineEventTriggerPlaySound(HelperObject):
    schema_name = "CineEventTriggerPlaySound"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerPlaySound
        return CineEventTriggerPlaySound(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerPlaySound.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerPlaySound
        return CineEventTriggerPlaySound(entlib.make_node(CineEventTriggerPlaySound.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SoundEventName(self):  # type: ()->String
        return String(self._node.at("SoundEventName"))
    @SoundEventName.setter
    def SoundEventName(self, val): self.SoundEventName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




