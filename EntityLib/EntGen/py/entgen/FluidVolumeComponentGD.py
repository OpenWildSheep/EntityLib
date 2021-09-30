
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.FluidVolumeComponentGD_FluidVolumeData import *


class FluidVolumeComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD.schema_name))
    @property
    def FluidVolume(self): return FluidVolumeComponentGD_FluidVolumeData(self._node.at("FluidVolume"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




