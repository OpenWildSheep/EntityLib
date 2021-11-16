
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateBiteEntityLiving(HelperObject):
    schema_name = "ActorStateBiteEntityLiving"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBiteEntityLiving
        return ActorStateBiteEntityLiving(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBiteEntityLiving.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBiteEntityLiving
        return ActorStateBiteEntityLiving(entlib.make_node(ActorStateBiteEntityLiving.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def State(self):  # type: ()->Int
        return Int(self._node.at("State"))
    @State.setter
    def State(self, val): self.State.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




