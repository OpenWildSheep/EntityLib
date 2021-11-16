
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class SmoothScaleComponentInput_Parameters(HelperObject):
    schema_name = "SmoothScaleComponentInput::Parameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmoothScaleComponentInput_Parameters
        return SmoothScaleComponentInput_Parameters(entlib.load_node_file(sourcefile, entlib.get_schema(SmoothScaleComponentInput_Parameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmoothScaleComponentInput_Parameters
        return SmoothScaleComponentInput_Parameters(entlib.make_node(SmoothScaleComponentInput_Parameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Scale(self):  # type: ()->Float
        return Float(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def Time(self):  # type: ()->Float
        return Float(self._node.at("Time"))
    @Time.setter
    def Time(self, val): self.Time.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




