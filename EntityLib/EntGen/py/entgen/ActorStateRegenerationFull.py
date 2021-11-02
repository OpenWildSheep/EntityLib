
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateRegenerationFull(HelperObject):
    schema_name = "ActorStateRegenerationFull"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateRegenerationFull
        return ActorStateRegenerationFull(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateRegenerationFull.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateRegenerationFull
        return ActorStateRegenerationFull(entlib.make_node(ActorStateRegenerationFull.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




