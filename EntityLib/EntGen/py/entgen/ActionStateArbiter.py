
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionStateArbiter_AllAllDecisionPass import *
from entgen.ActionStateArbiter_AllCategoryDecisionPass import *
from entgen.ActionStateArbiter_AllStateDecisionPass import *
from entgen.ActionStateArbiter_CategoryAllDecisionPass import *
from entgen.ActionStateArbiter_CategoryCategoryDecisionPass import *
from entgen.ActionStateArbiter_CategoryOrderPass import *
from entgen.ActionStateArbiter_CategoryStateDecisionPass import *
from entgen.ActionStateArbiter_PairDecisionPass import *
from entgen.ActionStateArbiter_StateAllDecisionPass import *
from entgen.ActionStateArbiter_StateCategoryDecisionPass import *
from entgen.ActionStateArbiter_StateOrderPass import *
from entgen.ActionStateArbiter_StateStateDecisionPass import *

from EntityLibPy import Node

class ActionStateArbiter(HelperObject):
    schema_name = "ActionStateArbiter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter
        return ActionStateArbiter(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter
        return ActionStateArbiter(entlib.make_node(ActionStateArbiter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllAll(self):  # type: ()->ActionStateArbiter_AllAllDecisionPass
        return ActionStateArbiter_AllAllDecisionPass(self._node.at("AllAll"))
    @property
    def AllCategory(self):  # type: ()->ActionStateArbiter_AllCategoryDecisionPass
        return ActionStateArbiter_AllCategoryDecisionPass(self._node.at("AllCategory"))
    @property
    def AllState(self):  # type: ()->ActionStateArbiter_AllStateDecisionPass
        return ActionStateArbiter_AllStateDecisionPass(self._node.at("AllState"))
    @property
    def CategoryAll(self):  # type: ()->ActionStateArbiter_CategoryAllDecisionPass
        return ActionStateArbiter_CategoryAllDecisionPass(self._node.at("CategoryAll"))
    @property
    def CategoryCategory(self):  # type: ()->ActionStateArbiter_CategoryCategoryDecisionPass
        return ActionStateArbiter_CategoryCategoryDecisionPass(self._node.at("CategoryCategory"))
    @property
    def CategoryOrder(self):  # type: ()->ActionStateArbiter_CategoryOrderPass
        return ActionStateArbiter_CategoryOrderPass(self._node.at("CategoryOrder"))
    @property
    def CategoryState(self):  # type: ()->ActionStateArbiter_CategoryStateDecisionPass
        return ActionStateArbiter_CategoryStateDecisionPass(self._node.at("CategoryState"))
    @property
    def Pair(self):  # type: ()->ActionStateArbiter_PairDecisionPass
        return ActionStateArbiter_PairDecisionPass(self._node.at("Pair"))
    @property
    def StateAll(self):  # type: ()->ActionStateArbiter_StateAllDecisionPass
        return ActionStateArbiter_StateAllDecisionPass(self._node.at("StateAll"))
    @property
    def StateCategory(self):  # type: ()->ActionStateArbiter_StateCategoryDecisionPass
        return ActionStateArbiter_StateCategoryDecisionPass(self._node.at("StateCategory"))
    @property
    def StateOrder(self):  # type: ()->ActionStateArbiter_StateOrderPass
        return ActionStateArbiter_StateOrderPass(self._node.at("StateOrder"))
    @property
    def StateState(self):  # type: ()->ActionStateArbiter_StateStateDecisionPass
        return ActionStateArbiter_StateStateDecisionPass(self._node.at("StateState"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




