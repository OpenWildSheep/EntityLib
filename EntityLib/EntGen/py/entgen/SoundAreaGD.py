
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class SoundAreaGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoundAreaGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SoundAreaGD.schema_name))
    @property
    def EventEnter(self): return String(self._node.at("EventEnter"))
    @EventEnter.setter
    def EventEnter(self, val): self.EventEnter.set(val)
    @property
    def EventExit(self): return String(self._node.at("EventExit"))
    @EventExit.setter
    def EventExit(self, val): self.EventExit.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




