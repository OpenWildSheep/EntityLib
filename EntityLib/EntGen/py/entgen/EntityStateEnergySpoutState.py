
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EnergySideEvent import *

from EntityLibPy import Node

class EntityStateEnergySpoutState(HelperObject):
    schema_name = "EntityStateEnergySpoutState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnergySpoutState
        return EntityStateEnergySpoutState(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergySpoutState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnergySpoutState
        return EntityStateEnergySpoutState(entlib.make_node(EntityStateEnergySpoutState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergySideEvents(self):  # type: ()->Array[EnergySideEvent]
        return (lambda n: Array(EnergySideEvent, n))(self._node.at("EnergySideEvents"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




