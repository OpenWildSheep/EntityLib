
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *


class CineEventTriggerGameStateChange(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerGameStateChange"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerGameStateChange.schema_name))
    @property
    def GameStateName(self): return String(self._node.at("GameStateName"))
    @GameStateName.setter
    def GameStateName(self, val): self.GameStateName.set(val)
    @property
    def Super(self): return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




