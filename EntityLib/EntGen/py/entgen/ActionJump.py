
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActionJump(HelperObject):
    schema_name = "ActionJump"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionJump
        return ActionJump(entlib.load_node_file(sourcefile, entlib.get_schema(ActionJump.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionJump
        return ActionJump(entlib.make_node(ActionJump.schema_name))
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
    def jumpAnalog(self):  # type: ()->Bool
        return Bool(self._node.at("jumpAnalog"))
    @jumpAnalog.setter
    def jumpAnalog(self, val): self.jumpAnalog.set(val)
    pass




