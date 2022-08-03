
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateJumpOriented(HelperObject):
    schema_name = "EntityStateJumpOriented"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateJumpOriented
        return EntityStateJumpOriented(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateJumpOriented.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateJumpOriented
        return EntityStateJumpOriented(entlib.make_node(EntityStateJumpOriented.schema_name))
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




