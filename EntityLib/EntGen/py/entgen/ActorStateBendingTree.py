
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActorStateBendingTree(HelperObject):
    schema_name = "ActorStateBendingTree"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBendingTree
        return ActorStateBendingTree(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBendingTree.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBendingTree
        return ActorStateBendingTree(entlib.make_node(ActorStateBendingTree.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AttackInput(self):  # type: ()->Bool
        return Bool(self._node.at("AttackInput"))
    @AttackInput.setter
    def AttackInput(self, val): self.AttackInput.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




