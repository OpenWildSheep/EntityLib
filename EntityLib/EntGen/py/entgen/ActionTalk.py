
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionTalk(HelperObject):
    schema_name = "ActionTalk"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionTalk
        return ActionTalk(entlib.load_node_file(sourcefile, entlib.get_schema(ActionTalk.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionTalk
        return ActionTalk(entlib.make_node(ActionTalk.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




