
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.variant_Pasta_Easing_Curve_string_ import *

from EntityLibPy import Node

class SimpleCurve1D(HelperObject):
    schema_name = "SimpleCurve1D"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SimpleCurve1D
        return SimpleCurve1D(entlib.load_node_file(sourcefile, entlib.get_schema(SimpleCurve1D.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SimpleCurve1D
        return SimpleCurve1D(entlib.make_node(SimpleCurve1D.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def easing(self):  # type: ()->variant_Pasta_Easing_Curve_string_
        return variant_Pasta_Easing_Curve_string_(self._node.at("easing"))
    pass




