
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class SmoothScaleComponentGD(HelperObject):
    schema_name = "SmoothScaleComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmoothScaleComponentGD
        return SmoothScaleComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(SmoothScaleComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmoothScaleComponentGD
        return SmoothScaleComponentGD(entlib.make_node(SmoothScaleComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




