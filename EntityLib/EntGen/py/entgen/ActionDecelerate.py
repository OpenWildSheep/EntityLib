
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionDecelerate(HelperObject):
    schema_name = "ActionDecelerate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionDecelerate
        return ActionDecelerate(entlib.load_node_file(sourcefile, entlib.get_schema(ActionDecelerate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionDecelerate
        return ActionDecelerate(entlib.make_node(ActionDecelerate.schema_name))
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




