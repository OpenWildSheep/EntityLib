
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActionMode import *
from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionAimProjectile(HelperObject):
    schema_name = "ActionAimProjectile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionAimProjectile
        return ActionAimProjectile(entlib.load_node_file(sourcefile, entlib.get_schema(ActionAimProjectile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionAimProjectile
        return ActionAimProjectile(entlib.make_node(ActionAimProjectile.schema_name))
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
    @property
    def actionMode(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("actionMode"))
    @actionMode.setter
    def actionMode(self, val): self.actionMode.set(val)
    pass




