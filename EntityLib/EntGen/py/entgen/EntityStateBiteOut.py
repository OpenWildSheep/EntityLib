
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateBiteOut(HelperObject):
    schema_name = "EntityStateBiteOut"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBiteOut
        return EntityStateBiteOut(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBiteOut.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBiteOut
        return EntityStateBiteOut(entlib.make_node(EntityStateBiteOut.schema_name))
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




