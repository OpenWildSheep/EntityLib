
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateConversionTransitionTo(HelperObject):
    schema_name = "EntityStateConversionTransitionTo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateConversionTransitionTo
        return EntityStateConversionTransitionTo(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateConversionTransitionTo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateConversionTransitionTo
        return EntityStateConversionTransitionTo(entlib.make_node(EntityStateConversionTransitionTo.schema_name))
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




