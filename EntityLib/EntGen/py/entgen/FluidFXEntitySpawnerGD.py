
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Precision import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.SpawningParameter import *


class FluidFXEntitySpawnerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidFXEntitySpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidFXEntitySpawnerGD.schema_name))
    @property
    def SamplingPrecision(self): return Precision(self._node.at("SamplingPrecision"))
    @SamplingPrecision.setter
    def SamplingPrecision(self, val): self.SamplingPrecision.set(val)
    @property
    def SpawningParameters(self): return (lambda n: Array(SpawningParameter, n))(self._node.at("SpawningParameters"))
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




