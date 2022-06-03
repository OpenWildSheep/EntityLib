
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateFall(HelperObject):
    schema_name = "EntityStateFall"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateFall
        return EntityStateFall(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateFall.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateFall
        return EntityStateFall(entlib.make_node(EntityStateFall.schema_name))
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




