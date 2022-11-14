
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateEnergyRootHatching_Inputs import *

from EntityLibPy import Node

class EntityStateEnergyRootHatching(HelperObject):
    schema_name = "EntityStateEnergyRootHatching"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnergyRootHatching
        return EntityStateEnergyRootHatching(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergyRootHatching.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnergyRootHatching
        return EntityStateEnergyRootHatching(entlib.make_node(EntityStateEnergyRootHatching.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStateEnergyRootHatching_Inputs
        return EntityStateEnergyRootHatching_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




