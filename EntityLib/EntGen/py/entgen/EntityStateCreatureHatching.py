
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateCreatureHatching_Inputs import *

from EntityLibPy import Node

class EntityStateCreatureHatching(HelperObject):
    schema_name = "EntityStateCreatureHatching"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateCreatureHatching
        return EntityStateCreatureHatching(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateCreatureHatching.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateCreatureHatching
        return EntityStateCreatureHatching(entlib.make_node(EntityStateCreatureHatching.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStateCreatureHatching_Inputs
        return EntityStateCreatureHatching_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




