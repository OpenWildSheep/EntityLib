
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityRef import *

from EntityLibPy import Node

class EntityStateBeingBlockedByVine(HelperObject):
    schema_name = "EntityStateBeingBlockedByVine"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBeingBlockedByVine
        return EntityStateBeingBlockedByVine(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBeingBlockedByVine.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBeingBlockedByVine
        return EntityStateBeingBlockedByVine(entlib.make_node(EntityStateBeingBlockedByVine.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Blocker(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("Blocker"))
    @Blocker.setter
    def Blocker(self, val): self.Blocker.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




