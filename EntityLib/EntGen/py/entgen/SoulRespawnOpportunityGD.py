
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.Specie import *
from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class SoulRespawnOpportunityGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoulRespawnOpportunityGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoulRespawnOpportunityGD
        return SoulRespawnOpportunityGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoulRespawnOpportunityGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoulRespawnOpportunityGD
        return SoulRespawnOpportunityGD(entlib.make_node(SoulRespawnOpportunityGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ForceReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ForceReviveSide"))
    @ForceReviveSide.setter
    def ForceReviveSide(self, val): self.ForceReviveSide.set(val)
    @property
    def MaxDensityCount(self):  # type: ()->Int
        return Int(self._node.at("MaxDensityCount"))
    @MaxDensityCount.setter
    def MaxDensityCount(self, val): self.MaxDensityCount.set(val)
    @property
    def MaxDensityRadius(self):  # type: ()->Float
        return Float(self._node.at("MaxDensityRadius"))
    @MaxDensityRadius.setter
    def MaxDensityRadius(self, val): self.MaxDensityRadius.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def SlotCount(self):  # type: ()->Int
        return Int(self._node.at("SlotCount"))
    @SlotCount.setter
    def SlotCount(self, val): self.SlotCount.set(val)
    @property
    def Specie(self):  # type: ()->Specie
        return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




