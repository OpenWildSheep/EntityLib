
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateBeingOnSlope(HelperObject):
    schema_name = "EntityStateBeingOnSlope"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBeingOnSlope
        return EntityStateBeingOnSlope(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBeingOnSlope.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBeingOnSlope
        return EntityStateBeingOnSlope(entlib.make_node(EntityStateBeingOnSlope.schema_name))
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



