
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionStateArbiter_StateStateDecision import *

from EntityLibPy import Node

class ActionStateArbiter_StateStateDecisionPass(HelperObject):
    schema_name = "ActionStateArbiter::StateStateDecisionPass"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter_StateStateDecisionPass
        return ActionStateArbiter_StateStateDecisionPass(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter_StateStateDecisionPass.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter_StateStateDecisionPass
        return ActionStateArbiter_StateStateDecisionPass(entlib.make_node(ActionStateArbiter_StateStateDecisionPass.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Decisions(self):  # type: ()->Array[ActionStateArbiter_StateStateDecision]
        return (lambda n: Array(ActionStateArbiter_StateStateDecision, n))(self._node.at("Decisions"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




