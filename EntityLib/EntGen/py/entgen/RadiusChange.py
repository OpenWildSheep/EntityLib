
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Pasta_Easing_Curve import *
from entgen.String import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class RadiusChange(HelperObject):
    schema_name = "RadiusChange"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RadiusChange
        return RadiusChange(entlib.load_node_file(sourcefile, entlib.get_schema(RadiusChange.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RadiusChange
        return RadiusChange(entlib.make_node(RadiusChange.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Entry(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Entry"))
    @property
    def Exit(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Exit"))
    @property
    def InBetweenEasing(self):  # type: ()->Pasta_Easing_Curve
        return Pasta_Easing_Curve(self._node.at("InBetweenEasing"))
    @InBetweenEasing.setter
    def InBetweenEasing(self, val): self.InBetweenEasing.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




