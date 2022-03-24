
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionStateArbiter_CategoryCategoryDecision import *

from EntityLibPy import Node

class ActionStateArbiter_CategoryAllDecisionPass(HelperObject):
    schema_name = "ActionStateArbiter::CategoryAllDecisionPass"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter_CategoryAllDecisionPass
        return ActionStateArbiter_CategoryAllDecisionPass(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter_CategoryAllDecisionPass.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter_CategoryAllDecisionPass
        return ActionStateArbiter_CategoryAllDecisionPass(entlib.make_node(ActionStateArbiter_CategoryAllDecisionPass.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Decisions(self):  # type: ()->Array[ActionStateArbiter_CategoryCategoryDecision]
        return (lambda n: Array(ActionStateArbiter_CategoryCategoryDecision, n))(self._node.at("Decisions"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




