
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateClassicLand(HelperObject):
    schema_name = "EntityStateClassicLand"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateClassicLand
        return EntityStateClassicLand(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateClassicLand.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateClassicLand
        return EntityStateClassicLand(entlib.make_node(EntityStateClassicLand.schema_name))
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




