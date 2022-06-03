
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionStateArbiter_CategoryStateDecision import *

from EntityLibPy import Node

class ActionStateArbiter_AllStateDecisionPass(HelperObject):
    schema_name = "ActionStateArbiter::AllStateDecisionPass"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter_AllStateDecisionPass
        return ActionStateArbiter_AllStateDecisionPass(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter_AllStateDecisionPass.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter_AllStateDecisionPass
        return ActionStateArbiter_AllStateDecisionPass(entlib.make_node(ActionStateArbiter_AllStateDecisionPass.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Decisions(self):  # type: ()->Array[ActionStateArbiter_CategoryStateDecision]
        return (lambda n: Array(ActionStateArbiter_CategoryStateDecision, n))(self._node.at("Decisions"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




