
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.FluidVolumeComponentGD_FluidVolumeData import *

from EntityLibPy import Node

class FluidVolumeComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD
        return FluidVolumeComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD
        return FluidVolumeComponentGD(entlib.make_node(FluidVolumeComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FluidVolume(self):  # type: ()->FluidVolumeComponentGD_FluidVolumeData
        return FluidVolumeComponentGD_FluidVolumeData(self._node.at("FluidVolume"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




