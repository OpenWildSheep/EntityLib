
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.PrimitiveShape import *

from EntityLibPy import Node

class ShapeSphere(HelperObject):
    schema_name = "ShapeSphere"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShapeSphere
        return ShapeSphere(entlib.load_node_file(sourcefile, entlib.get_schema(ShapeSphere.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShapeSphere
        return ShapeSphere(entlib.make_node(ShapeSphere.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->PrimitiveShape
        return PrimitiveShape(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




