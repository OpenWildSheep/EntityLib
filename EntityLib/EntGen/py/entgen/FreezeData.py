
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.eventStringHash import *


class FreezeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FreezeData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FreezeData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def deltaTimeFactor(self): return Float(self._node.at("deltaTimeFactor"))
    @deltaTimeFactor.setter
    def deltaTimeFactor(self, val): self.deltaTimeFactor.set(val)
    @property
    def eventStringHash(self): return eventStringHash(self._node.at("eventStringHash"))
    @property
    def stateDuration(self): return Float(self._node.at("stateDuration"))
    @stateDuration.setter
    def stateDuration(self, val): self.stateDuration.set(val)
    @property
    def transitionInDuration(self): return Float(self._node.at("transitionInDuration"))
    @transitionInDuration.setter
    def transitionInDuration(self, val): self.transitionInDuration.set(val)
    @property
    def transitionOutDuration(self): return Float(self._node.at("transitionOutDuration"))
    @transitionOutDuration.setter
    def transitionOutDuration(self, val): self.transitionOutDuration.set(val)
    pass




