
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.PrimitiveShape import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ShapeBox(HelperObject):
    schema_name = "ShapeBox"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShapeBox
        return ShapeBox(entlib.load_node_file(sourcefile, entlib.get_schema(ShapeBox.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShapeBox
        return ShapeBox(entlib.make_node(ShapeBox.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Size(self):  # type: ()->Vector3
        return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Super(self):  # type: ()->PrimitiveShape
        return PrimitiveShape(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




