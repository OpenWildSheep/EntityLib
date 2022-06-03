
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.CreatureProfile import *

from EntityLibPy import Node

class EntityStateCreatureProfile(HelperObject):
    schema_name = "EntityStateCreatureProfile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateCreatureProfile
        return EntityStateCreatureProfile(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateCreatureProfile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateCreatureProfile
        return EntityStateCreatureProfile(entlib.make_node(EntityStateCreatureProfile.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Profile(self):  # type: ()->CreatureProfile
        return CreatureProfile(self._node.at("Profile"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




