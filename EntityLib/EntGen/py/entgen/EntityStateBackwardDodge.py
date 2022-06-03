
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateBackwardDodge(HelperObject):
    schema_name = "EntityStateBackwardDodge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBackwardDodge
        return EntityStateBackwardDodge(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBackwardDodge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBackwardDodge
        return EntityStateBackwardDodge(entlib.make_node(EntityStateBackwardDodge.schema_name))
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




