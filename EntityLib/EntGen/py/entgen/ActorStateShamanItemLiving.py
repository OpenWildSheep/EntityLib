
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActorStateShamanItemLiving(HelperObject):
    schema_name = "ActorStateShamanItemLiving"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateShamanItemLiving
        return ActorStateShamanItemLiving(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateShamanItemLiving.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateShamanItemLiving
        return ActorStateShamanItemLiving(entlib.make_node(ActorStateShamanItemLiving.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def End(self):  # type: ()->Bool
        return Bool(self._node.at("End"))
    @End.setter
    def End(self, val): self.End.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




