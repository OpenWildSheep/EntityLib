
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Precision import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class FluidNavMeshTaggerGD(HelperObject):
    schema_name = "FluidNavMeshTaggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidNavMeshTaggerGD
        return FluidNavMeshTaggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidNavMeshTaggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidNavMeshTaggerGD
        return FluidNavMeshTaggerGD(entlib.make_node(FluidNavMeshTaggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MinDepth(self):  # type: ()->Float
        return Float(self._node.at("MinDepth"))
    @MinDepth.setter
    def MinDepth(self, val): self.MinDepth.set(val)
    @property
    def SamplingPrecision(self):  # type: ()->Precision
        return Precision(self._node.at("SamplingPrecision"))
    @SamplingPrecision.setter
    def SamplingPrecision(self, val): self.SamplingPrecision.set(val)
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




