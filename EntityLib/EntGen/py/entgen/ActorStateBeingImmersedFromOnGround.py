
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateBeingImmersedFromOnGround(HelperObject):
    schema_name = "ActorStateBeingImmersedFromOnGround"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBeingImmersedFromOnGround
        return ActorStateBeingImmersedFromOnGround(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBeingImmersedFromOnGround.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBeingImmersedFromOnGround
        return ActorStateBeingImmersedFromOnGround(entlib.make_node(ActorStateBeingImmersedFromOnGround.schema_name))
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




