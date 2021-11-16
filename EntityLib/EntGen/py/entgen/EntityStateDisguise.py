
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class EntityStateDisguise(HelperObject):
    schema_name = "EntityStateDisguise"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateDisguise
        return EntityStateDisguise(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateDisguise.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateDisguise
        return EntityStateDisguise(entlib.make_node(EntityStateDisguise.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ExitRequired(self):  # type: ()->Bool
        return Bool(self._node.at("ExitRequired"))
    @ExitRequired.setter
    def ExitRequired(self, val): self.ExitRequired.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




