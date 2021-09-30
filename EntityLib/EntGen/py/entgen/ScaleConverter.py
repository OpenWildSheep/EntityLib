
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.variant_Pasta_Easing_Curve_string_ import *


class ScaleConverter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScaleConverter"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ScaleConverter.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def easing(self): return variant_Pasta_Easing_Curve_string_(self._node.at("easing"))
    @property
    def in_(self): return Vector2(self._node.at("in_"))
    @in_.setter
    def in_(self, val): self.in_.set(val)
    @property
    def inText(self): return String(self._node.at("inText"))
    @inText.setter
    def inText(self, val): self.inText.set(val)
    @property
    def out(self): return Vector2(self._node.at("out"))
    @out.setter
    def out(self, val): self.out.set(val)
    @property
    def outText(self): return String(self._node.at("outText"))
    @outText.setter
    def outText(self, val): self.outText.set(val)
    pass




