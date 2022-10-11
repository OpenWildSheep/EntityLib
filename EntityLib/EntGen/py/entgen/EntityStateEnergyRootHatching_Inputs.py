
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateEnergyRootHatching_Inputs(HelperObject):
    schema_name = "EntityStateEnergyRootHatching::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnergyRootHatching_Inputs
        return EntityStateEnergyRootHatching_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergyRootHatching_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnergyRootHatching_Inputs
        return EntityStateEnergyRootHatching_Inputs(entlib.make_node(EntityStateEnergyRootHatching_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HatchingDuration(self):  # type: ()->Float
        return Float(self._node.at("HatchingDuration"))
    @HatchingDuration.setter
    def HatchingDuration(self, val): self.HatchingDuration.set(val)
    @property
    def HatchingSide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("HatchingSide"))
    @HatchingSide.setter
    def HatchingSide(self, val): self.HatchingSide.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




