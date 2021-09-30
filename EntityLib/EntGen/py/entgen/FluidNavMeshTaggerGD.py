
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Precision import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class FluidNavMeshTaggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidNavMeshTaggerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidNavMeshTaggerGD.schema_name))
    @property
    def MinDepth(self): return Float(self._node.at("MinDepth"))
    @MinDepth.setter
    def MinDepth(self, val): self.MinDepth.set(val)
    @property
    def SamplingPrecision(self): return Precision(self._node.at("SamplingPrecision"))
    @SamplingPrecision.setter
    def SamplingPrecision(self, val): self.SamplingPrecision.set(val)
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




