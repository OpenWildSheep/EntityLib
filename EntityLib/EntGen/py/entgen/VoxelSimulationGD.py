
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class VoxelSimulationGD(HelperObject):
    schema_name = "VoxelSimulationGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VoxelSimulationGD
        return VoxelSimulationGD(entlib.load_node_file(sourcefile, entlib.get_schema(VoxelSimulationGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VoxelSimulationGD
        return VoxelSimulationGD(entlib.make_node(VoxelSimulationGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_voxelSize(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_voxelSize"))
    @EDITOR_voxelSize.setter
    def EDITOR_voxelSize(self, val): self.EDITOR_voxelSize.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




