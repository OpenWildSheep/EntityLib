
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ActorState import *
from entgen.ReviveSideEvent import *


class EntityStateEnergySpoutState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateEnergySpoutState"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergySpoutState.schema_name))
    @property
    def ReviveSide(self): return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def ReviveSideEvents(self): return (lambda n: Array(ReviveSideEvent, n))(self._node.at("ReviveSideEvents"))
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




