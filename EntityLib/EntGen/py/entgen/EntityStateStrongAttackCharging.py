
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateStrongAttackCharging(HelperObject):
    schema_name = "EntityStateStrongAttackCharging"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateStrongAttackCharging
        return EntityStateStrongAttackCharging(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateStrongAttackCharging.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateStrongAttackCharging
        return EntityStateStrongAttackCharging(entlib.make_node(EntityStateStrongAttackCharging.schema_name))
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




