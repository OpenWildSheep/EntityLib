
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateForceAgainstSlope(HelperObject):
    schema_name = "ActorStateForceAgainstSlope"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateForceAgainstSlope
        return ActorStateForceAgainstSlope(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateForceAgainstSlope.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateForceAgainstSlope
        return ActorStateForceAgainstSlope(entlib.make_node(ActorStateForceAgainstSlope.schema_name))
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




