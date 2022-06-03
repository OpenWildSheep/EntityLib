
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateChargeMode_EntityStateChargeModeInputs import *

from EntityLibPy import Node

class EntityStateChargeMode(HelperObject):
    schema_name = "EntityStateChargeMode"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateChargeMode
        return EntityStateChargeMode(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateChargeMode.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateChargeMode
        return EntityStateChargeMode(entlib.make_node(EntityStateChargeMode.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ChargeModeInputs(self):  # type: ()->EntityStateChargeMode_EntityStateChargeModeInputs
        return EntityStateChargeMode_EntityStateChargeModeInputs(self._node.at("ChargeModeInputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




