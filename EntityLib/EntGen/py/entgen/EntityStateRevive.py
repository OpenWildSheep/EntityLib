
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateRevive_Inputs import *

from EntityLibPy import Node

class EntityStateRevive(HelperObject):
    schema_name = "EntityStateRevive"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateRevive
        return EntityStateRevive(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateRevive.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateRevive
        return EntityStateRevive(entlib.make_node(EntityStateRevive.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStateRevive_Inputs
        return EntityStateRevive_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




