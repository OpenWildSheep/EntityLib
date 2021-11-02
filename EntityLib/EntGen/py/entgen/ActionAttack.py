
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionAttack_AttackOutputs import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionAttack(HelperObject):
    schema_name = "ActionAttack"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionAttack
        return ActionAttack(entlib.load_node_file(sourcefile, entlib.get_schema(ActionAttack.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionAttack
        return ActionAttack(entlib.make_node(ActionAttack.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Outputs(self):  # type: ()->ActionAttack_AttackOutputs
        return ActionAttack_AttackOutputs(self._node.at("Outputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




