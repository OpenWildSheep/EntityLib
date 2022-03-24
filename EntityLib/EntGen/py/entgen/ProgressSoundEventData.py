
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ProgressSoundEventData(HelperObject):
    schema_name = "ProgressSoundEventData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProgressSoundEventData
        return ProgressSoundEventData(entlib.load_node_file(sourcefile, entlib.get_schema(ProgressSoundEventData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProgressSoundEventData
        return ProgressSoundEventData(entlib.make_node(ProgressSoundEventData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DecreaseEventName(self):  # type: ()->String
        return String(self._node.at("DecreaseEventName"))
    @DecreaseEventName.setter
    def DecreaseEventName(self, val): self.DecreaseEventName.set(val)
    @property
    def DecreaseStartThreshold(self):  # type: ()->Float
        return Float(self._node.at("DecreaseStartThreshold"))
    @DecreaseStartThreshold.setter
    def DecreaseStartThreshold(self, val): self.DecreaseStartThreshold.set(val)
    @property
    def DecreaseStopThreshold(self):  # type: ()->Float
        return Float(self._node.at("DecreaseStopThreshold"))
    @DecreaseStopThreshold.setter
    def DecreaseStopThreshold(self, val): self.DecreaseStopThreshold.set(val)
    @property
    def EventBank(self):  # type: ()->String
        return String(self._node.at("EventBank"))
    @EventBank.setter
    def EventBank(self, val): self.EventBank.set(val)
    @property
    def EventLooping(self):  # type: ()->Bool
        return Bool(self._node.at("EventLooping"))
    @EventLooping.setter
    def EventLooping(self, val): self.EventLooping.set(val)
    @property
    def IncreaseEventName(self):  # type: ()->String
        return String(self._node.at("IncreaseEventName"))
    @IncreaseEventName.setter
    def IncreaseEventName(self, val): self.IncreaseEventName.set(val)
    @property
    def IncreaseStartThreshold(self):  # type: ()->Float
        return Float(self._node.at("IncreaseStartThreshold"))
    @IncreaseStartThreshold.setter
    def IncreaseStartThreshold(self, val): self.IncreaseStartThreshold.set(val)
    @property
    def IncreaseStopThreshold(self):  # type: ()->Float
        return Float(self._node.at("IncreaseStopThreshold"))
    @IncreaseStopThreshold.setter
    def IncreaseStopThreshold(self, val): self.IncreaseStopThreshold.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




