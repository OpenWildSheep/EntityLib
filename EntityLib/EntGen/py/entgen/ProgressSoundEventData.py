
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *


class ProgressSoundEventData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProgressSoundEventData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ProgressSoundEventData.schema_name))
    @property
    def DecreaseEventName(self): return String(self._node.at("DecreaseEventName"))
    @DecreaseEventName.setter
    def DecreaseEventName(self, val): self.DecreaseEventName.set(val)
    @property
    def DecreaseStartThreshold(self): return Float(self._node.at("DecreaseStartThreshold"))
    @DecreaseStartThreshold.setter
    def DecreaseStartThreshold(self, val): self.DecreaseStartThreshold.set(val)
    @property
    def DecreaseStopThreshold(self): return Float(self._node.at("DecreaseStopThreshold"))
    @DecreaseStopThreshold.setter
    def DecreaseStopThreshold(self, val): self.DecreaseStopThreshold.set(val)
    @property
    def EventBank(self): return String(self._node.at("EventBank"))
    @EventBank.setter
    def EventBank(self, val): self.EventBank.set(val)
    @property
    def EventLooping(self): return Bool(self._node.at("EventLooping"))
    @EventLooping.setter
    def EventLooping(self, val): self.EventLooping.set(val)
    @property
    def IncreaseEventName(self): return String(self._node.at("IncreaseEventName"))
    @IncreaseEventName.setter
    def IncreaseEventName(self, val): self.IncreaseEventName.set(val)
    @property
    def IncreaseStartThreshold(self): return Float(self._node.at("IncreaseStartThreshold"))
    @IncreaseStartThreshold.setter
    def IncreaseStartThreshold(self, val): self.IncreaseStartThreshold.set(val)
    @property
    def IncreaseStopThreshold(self): return Float(self._node.at("IncreaseStopThreshold"))
    @IncreaseStopThreshold.setter
    def IncreaseStopThreshold(self, val): self.IncreaseStopThreshold.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




