
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityRef import *

from EntityLibPy import Node

class EntityStateRespawnability(HelperObject):
    schema_name = "EntityStateRespawnability"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateRespawnability
        return EntityStateRespawnability(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateRespawnability.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateRespawnability
        return EntityStateRespawnability(entlib.make_node(EntityStateRespawnability.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RespawnPlaceEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("RespawnPlaceEntityRef"))
    @RespawnPlaceEntityRef.setter
    def RespawnPlaceEntityRef(self, val): self.RespawnPlaceEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




