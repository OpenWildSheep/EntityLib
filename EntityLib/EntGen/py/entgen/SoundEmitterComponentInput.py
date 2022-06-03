
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.computePitchAngle import *

from EntityLibPy import Node

class SoundEmitterComponentInput(HelperObject):
    schema_name = "SoundEmitterComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundEmitterComponentInput
        return SoundEmitterComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(SoundEmitterComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundEmitterComponentInput
        return SoundEmitterComponentInput(entlib.make_node(SoundEmitterComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def computePitchAngle(self):  # type: ()->computePitchAngle
        return computePitchAngle(self._node.at("computePitchAngle"))
    pass




