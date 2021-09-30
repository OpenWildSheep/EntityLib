
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class FluidToRegenInjectorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidToRegenInjectorGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidToRegenInjectorGD.schema_name))
    @property
    def EnergyPerSecond(self): return Float(self._node.at("EnergyPerSecond"))
    @EnergyPerSecond.setter
    def EnergyPerSecond(self, val): self.EnergyPerSecond.set(val)
    @property
    def MinDepth(self): return Float(self._node.at("MinDepth"))
    @MinDepth.setter
    def MinDepth(self, val): self.MinDepth.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def UpdatePeriod(self): return Float(self._node.at("UpdatePeriod"))
    @UpdatePeriod.setter
    def UpdatePeriod(self, val): self.UpdatePeriod.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




