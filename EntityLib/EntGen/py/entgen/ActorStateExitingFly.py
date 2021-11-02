
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateExitingFly(HelperObject):
    schema_name = "ActorStateExitingFly"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateExitingFly
        return ActorStateExitingFly(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateExitingFly.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateExitingFly
        return ActorStateExitingFly(entlib.make_node(ActorStateExitingFly.schema_name))
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




