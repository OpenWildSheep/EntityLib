
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionIdle(HelperObject):
    schema_name = "ActionIdle"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionIdle
        return ActionIdle(entlib.load_node_file(sourcefile, entlib.get_schema(ActionIdle.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionIdle
        return ActionIdle(entlib.make_node(ActionIdle.schema_name))
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




