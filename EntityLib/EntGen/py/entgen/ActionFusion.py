
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionFusion(HelperObject):
    schema_name = "ActionFusion"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionFusion
        return ActionFusion(entlib.load_node_file(sourcefile, entlib.get_schema(ActionFusion.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionFusion
        return ActionFusion(entlib.make_node(ActionFusion.schema_name))
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




