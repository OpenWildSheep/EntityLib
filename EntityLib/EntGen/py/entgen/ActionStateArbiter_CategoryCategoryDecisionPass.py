
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionStateArbiter_CategoryCategoryDecision import *

from EntityLibPy import Node

class ActionStateArbiter_CategoryCategoryDecisionPass(HelperObject):
    schema_name = "ActionStateArbiter::CategoryCategoryDecisionPass"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter_CategoryCategoryDecisionPass
        return ActionStateArbiter_CategoryCategoryDecisionPass(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter_CategoryCategoryDecisionPass.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter_CategoryCategoryDecisionPass
        return ActionStateArbiter_CategoryCategoryDecisionPass(entlib.make_node(ActionStateArbiter_CategoryCategoryDecisionPass.schema_name))
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




