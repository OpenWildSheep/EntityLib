
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class FluidToRegenInjectorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidToRegenInjectorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidToRegenInjectorGD
        return FluidToRegenInjectorGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidToRegenInjectorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidToRegenInjectorGD
        return FluidToRegenInjectorGD(entlib.make_node(FluidToRegenInjectorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyPerSecond(self):  # type: ()->Float
        return Float(self._node.at("EnergyPerSecond"))
    @EnergyPerSecond.setter
    def EnergyPerSecond(self, val): self.EnergyPerSecond.set(val)
    @property
    def MinDepth(self):  # type: ()->Float
        return Float(self._node.at("MinDepth"))
    @MinDepth.setter
    def MinDepth(self, val): self.MinDepth.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UpdatePeriod(self):  # type: ()->Float
        return Float(self._node.at("UpdatePeriod"))
    @UpdatePeriod.setter
    def UpdatePeriod(self, val): self.UpdatePeriod.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




