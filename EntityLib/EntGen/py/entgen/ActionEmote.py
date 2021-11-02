
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActionMode import *
from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionEmote(HelperObject):
    schema_name = "ActionEmote"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionEmote
        return ActionEmote(entlib.load_node_file(sourcefile, entlib.get_schema(ActionEmote.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionEmote
        return ActionEmote(entlib.make_node(ActionEmote.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnimAction(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("AnimAction"))
    @AnimAction.setter
    def AnimAction(self, val): self.AnimAction.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




