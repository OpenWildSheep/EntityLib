
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateMovingProne(HelperObject):
    schema_name = "ActorStateMovingProne"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateMovingProne
        return ActorStateMovingProne(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateMovingProne.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateMovingProne
        return ActorStateMovingProne(entlib.make_node(ActorStateMovingProne.schema_name))
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




