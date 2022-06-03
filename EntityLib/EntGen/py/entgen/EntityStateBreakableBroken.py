
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateBreakableBroken(HelperObject):
    schema_name = "EntityStateBreakableBroken"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBreakableBroken
        return EntityStateBreakableBroken(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBreakableBroken.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBreakableBroken
        return EntityStateBreakableBroken(entlib.make_node(EntityStateBreakableBroken.schema_name))
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




