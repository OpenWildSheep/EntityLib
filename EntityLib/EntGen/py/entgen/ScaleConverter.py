
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.variant_Pasta_Easing_Curve_string_ import *

from EntityLibPy import Node

class ScaleConverter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScaleConverter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ScaleConverter
        return ScaleConverter(entlib.load_node_file(sourcefile, entlib.get_schema(ScaleConverter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ScaleConverter
        return ScaleConverter(entlib.make_node(ScaleConverter.schema_name))
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
    @property
    def in_(self):  # type: ()->Vector2
        return Vector2(self._node.at("in"))
    @in_.setter
    def in_(self, val): self.in_.set(val)
    @property
    def inText(self):  # type: ()->String
        return String(self._node.at("inText"))
    @inText.setter
    def inText(self, val): self.inText.set(val)
    @property
    def out(self):  # type: ()->Vector2
        return Vector2(self._node.at("out"))
    @out.setter
    def out(self, val): self.out.set(val)
    @property
    def outText(self):  # type: ()->String
        return String(self._node.at("outText"))
    @outText.setter
    def outText(self, val): self.outText.set(val)
    pass




