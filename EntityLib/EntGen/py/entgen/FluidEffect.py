
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.GameEffect import *

from EntityLibPy import Node

class FluidEffect(HelperObject):
    schema_name = "FluidEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidEffect
        return FluidEffect(entlib.load_node_file(sourcefile, entlib.get_schema(FluidEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidEffect
        return FluidEffect(entlib.make_node(FluidEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DisplayFX(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayFX"))
    @DisplayFX.setter
    def DisplayFX(self, val): self.DisplayFX.set(val)
    @property
    def EnergySide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("EnergySide"))
    @EnergySide.setter
    def EnergySide(self, val): self.EnergySide.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def VolumePerSecond(self):  # type: ()->Float
        return Float(self._node.at("VolumePerSecond"))
    @VolumePerSecond.setter
    def VolumePerSecond(self, val): self.VolumePerSecond.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




