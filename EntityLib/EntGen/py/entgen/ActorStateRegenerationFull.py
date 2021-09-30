
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *


class ActorStateRegenerationFull(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateRegenerationFull"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateRegenerationFull.schema_name))
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




