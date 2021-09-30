
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class FallData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FallData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FallData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def deadDelayDuringFreeFall(self): return Float(self._node.at("deadDelayDuringFreeFall"))
    @deadDelayDuringFreeFall.setter
    def deadDelayDuringFreeFall(self, val): self.deadDelayDuringFreeFall.set(val)
    @property
    def fallToFreeFallDelay(self): return Float(self._node.at("fallToFreeFallDelay"))
    @fallToFreeFallDelay.setter
    def fallToFreeFallDelay(self, val): self.fallToFreeFallDelay.set(val)
    @property
    def injuredDelayDuringFall(self): return Float(self._node.at("injuredDelayDuringFall"))
    @injuredDelayDuringFall.setter
    def injuredDelayDuringFall(self, val): self.injuredDelayDuringFall.set(val)
    pass




