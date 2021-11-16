
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionCinematic(HelperObject):
    schema_name = "ActionCinematic"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionCinematic
        return ActionCinematic(entlib.load_node_file(sourcefile, entlib.get_schema(ActionCinematic.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionCinematic
        return ActionCinematic(entlib.make_node(ActionCinematic.schema_name))
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




