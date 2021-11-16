
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActionStun(HelperObject):
    schema_name = "ActionStun"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStun
        return ActionStun(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStun.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStun
        return ActionStun(entlib.make_node(ActionStun.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def StunMax(self):  # type: ()->Bool
        return Bool(self._node.at("StunMax"))
    @StunMax.setter
    def StunMax(self, val): self.StunMax.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




