
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateJumpHeightMultiplier(HelperObject):
    schema_name = "EntityStateJumpHeightMultiplier"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateJumpHeightMultiplier
        return EntityStateJumpHeightMultiplier(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateJumpHeightMultiplier.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateJumpHeightMultiplier
        return EntityStateJumpHeightMultiplier(entlib.make_node(EntityStateJumpHeightMultiplier.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def JumpHeightMultiplier(self):  # type: ()->Float
        return Float(self._node.at("JumpHeightMultiplier"))
    @JumpHeightMultiplier.setter
    def JumpHeightMultiplier(self, val): self.JumpHeightMultiplier.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




