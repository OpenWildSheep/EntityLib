
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActorStateArbiterDecision import *
from entgen.String import *

from EntityLibPy import Node

class ActionStateArbiter_StateStateDecision(HelperObject):
    schema_name = "ActionStateArbiter::StateStateDecision"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter_StateStateDecision
        return ActionStateArbiter_StateStateDecision(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter_StateStateDecision.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter_StateStateDecision
        return ActionStateArbiter_StateStateDecision(entlib.make_node(ActionStateArbiter_StateStateDecision.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Current(self):  # type: ()->String
        return String(self._node.at("Current"))
    @Current.setter
    def Current(self, val): self.Current.set(val)
    @property
    def Decision(self):  # type: ()->ActorStateArbiterDecision
        return ActorStateArbiterDecision(self._node.at("Decision"))
    @Decision.setter
    def Decision(self, val): self.Decision.set(val)
    @property
    def New(self):  # type: ()->String
        return String(self._node.at("New"))
    @New.setter
    def New(self, val): self.New.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




