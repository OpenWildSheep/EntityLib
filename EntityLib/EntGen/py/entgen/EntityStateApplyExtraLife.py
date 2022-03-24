
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateApplyExtraLife(HelperObject):
    schema_name = "EntityStateApplyExtraLife"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateApplyExtraLife
        return EntityStateApplyExtraLife(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateApplyExtraLife.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateApplyExtraLife
        return EntityStateApplyExtraLife(entlib.make_node(EntityStateApplyExtraLife.schema_name))
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




