
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateBeingOnGroundFromImmersed(HelperObject):
    schema_name = "ActorStateBeingOnGroundFromImmersed"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBeingOnGroundFromImmersed
        return ActorStateBeingOnGroundFromImmersed(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBeingOnGroundFromImmersed.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBeingOnGroundFromImmersed
        return ActorStateBeingOnGroundFromImmersed(entlib.make_node(ActorStateBeingOnGroundFromImmersed.schema_name))
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




