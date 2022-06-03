
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateSlope(HelperObject):
    schema_name = "ActorStateSlope"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateSlope
        return ActorStateSlope(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateSlope.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateSlope
        return ActorStateSlope(entlib.make_node(ActorStateSlope.schema_name))
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




