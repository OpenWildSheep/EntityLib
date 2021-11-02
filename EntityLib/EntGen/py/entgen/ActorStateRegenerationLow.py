
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActorStateRegenerationLow(HelperObject):
    schema_name = "ActorStateRegenerationLow"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateRegenerationLow
        return ActorStateRegenerationLow(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateRegenerationLow.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateRegenerationLow
        return ActorStateRegenerationLow(entlib.make_node(ActorStateRegenerationLow.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NeedToBeFreed(self):  # type: ()->Bool
        return Bool(self._node.at("NeedToBeFreed"))
    @NeedToBeFreed.setter
    def NeedToBeFreed(self, val): self.NeedToBeFreed.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




