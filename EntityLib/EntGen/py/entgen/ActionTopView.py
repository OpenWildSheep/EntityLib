
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionTopView(HelperObject):
    schema_name = "ActionTopView"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionTopView
        return ActionTopView(entlib.load_node_file(sourcefile, entlib.get_schema(ActionTopView.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionTopView
        return ActionTopView(entlib.make_node(ActionTopView.schema_name))
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




