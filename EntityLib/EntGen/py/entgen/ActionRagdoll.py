
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionRagdoll(HelperObject):
    schema_name = "ActionRagdoll"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionRagdoll
        return ActionRagdoll(entlib.load_node_file(sourcefile, entlib.get_schema(ActionRagdoll.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionRagdoll
        return ActionRagdoll(entlib.make_node(ActionRagdoll.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def State(self):  # type: ()->Int
        return Int(self._node.at("State"))
    @State.setter
    def State(self, val): self.State.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




