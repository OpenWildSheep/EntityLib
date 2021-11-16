
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Precision import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.SpawningParameter import *

from EntityLibPy import Node

class FluidFXEntitySpawnerGD(HelperObject):
    schema_name = "FluidFXEntitySpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidFXEntitySpawnerGD
        return FluidFXEntitySpawnerGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidFXEntitySpawnerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidFXEntitySpawnerGD
        return FluidFXEntitySpawnerGD(entlib.make_node(FluidFXEntitySpawnerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SamplingPrecision(self):  # type: ()->Precision
        return Precision(self._node.at("SamplingPrecision"))
    @SamplingPrecision.setter
    def SamplingPrecision(self, val): self.SamplingPrecision.set(val)
    @property
    def SpawningParameters(self):  # type: ()->Array[SpawningParameter]
        return (lambda n: Array(SpawningParameter, n))(self._node.at("SpawningParameters"))
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




