
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateChargingJump(HelperObject):
    schema_name = "EntityStateChargingJump"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateChargingJump
        return EntityStateChargingJump(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateChargingJump.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateChargingJump
        return EntityStateChargingJump(entlib.make_node(EntityStateChargingJump.schema_name))
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




