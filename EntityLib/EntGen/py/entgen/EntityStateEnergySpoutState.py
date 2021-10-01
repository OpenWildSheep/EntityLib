
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ActorState import *
from entgen.ReviveSideEvent import *

from EntityLibPy import Node

class EntityStateEnergySpoutState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateEnergySpoutState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnergySpoutState
        return EntityStateEnergySpoutState(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergySpoutState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnergySpoutState
        return EntityStateEnergySpoutState(entlib.make_node(EntityStateEnergySpoutState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def ReviveSideEvents(self):  # type: ()->Array[ReviveSideEvent]
        return (lambda n: Array(ReviveSideEvent, n))(self._node.at("ReviveSideEvents"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




