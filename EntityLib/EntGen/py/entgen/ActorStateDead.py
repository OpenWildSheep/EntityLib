
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *
from entgen.LastAliveReviveSide import *


class ActorStateDead(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateDead"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateDead.schema_name))
    @property
    def LastAliveReviveSide(self): return LastAliveReviveSide(self._node.at("LastAliveReviveSide"))
    @property
    def ReviveLifeSigned(self): return Float(self._node.at("ReviveLifeSigned"))
    @ReviveLifeSigned.setter
    def ReviveLifeSigned(self, val): self.ReviveLifeSigned.set(val)
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




