
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


class SoulRespawnOpportunityGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoulRespawnOpportunityGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SoulRespawnOpportunityGD.schema_name))
    @property
    def ForceReviveSide(self): return ReviveSide(self._node.at("ForceReviveSide"))
    @ForceReviveSide.setter
    def ForceReviveSide(self, val): self.ForceReviveSide.set(val)
    @property
    def MaxDensityCount(self): return Int(self._node.at("MaxDensityCount"))
    @MaxDensityCount.setter
    def MaxDensityCount(self, val): self.MaxDensityCount.set(val)
    @property
    def MaxDensityRadius(self): return Float(self._node.at("MaxDensityRadius"))
    @MaxDensityRadius.setter
    def MaxDensityRadius(self, val): self.MaxDensityRadius.set(val)
    @property
    def Offset(self): return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def SlotCount(self): return Int(self._node.at("SlotCount"))
    @SlotCount.setter
    def SlotCount(self, val): self.SlotCount.set(val)
    @property
    def Specie(self): return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




