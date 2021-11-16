
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateHintNone(HelperObject):
    schema_name = "EntityStateHintNone"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateHintNone
        return EntityStateHintNone(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateHintNone.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateHintNone
        return EntityStateHintNone(entlib.make_node(EntityStateHintNone.schema_name))
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




