
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Color import *
from entgen.Float import *

from EntityLibPy import Node

class GradientColor(HelperObject):
    schema_name = "GradientColor"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GradientColor
        return GradientColor(entlib.load_node_file(sourcefile, entlib.get_schema(GradientColor.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GradientColor
        return GradientColor(entlib.make_node(GradientColor.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def color(self):  # type: ()->Color
        return Color(self._node.at("color"))
    @color.setter
    def color(self, val): self.color.set(val)
    @property
    def percent(self):  # type: ()->Float
        return Float(self._node.at("percent"))
    @percent.setter
    def percent(self, val): self.percent.set(val)
    pass




