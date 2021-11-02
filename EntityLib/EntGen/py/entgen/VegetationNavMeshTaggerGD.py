
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class VegetationNavMeshTaggerGD(HelperObject):
    schema_name = "VegetationNavMeshTaggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VegetationNavMeshTaggerGD
        return VegetationNavMeshTaggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(VegetationNavMeshTaggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VegetationNavMeshTaggerGD
        return VegetationNavMeshTaggerGD(entlib.make_node(VegetationNavMeshTaggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
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




