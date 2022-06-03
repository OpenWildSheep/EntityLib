
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.Parameters import *
from entgen.ScaleFactor import *

from EntityLibPy import Node

class SmoothScaleComponentInput(HelperObject):
    schema_name = "SmoothScaleComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmoothScaleComponentInput
        return SmoothScaleComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(SmoothScaleComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmoothScaleComponentInput
        return SmoothScaleComponentInput(entlib.make_node(SmoothScaleComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Parameters(self):  # type: ()->Parameters
        return Parameters(self._node.at("Parameters"))
    @property
    def ScaleFactor(self):  # type: ()->ScaleFactor
        return ScaleFactor(self._node.at("ScaleFactor"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




