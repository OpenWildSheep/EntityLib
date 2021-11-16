
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *

from EntityLibPy import Node

class ConditionalRigidityAttribute_Range(HelperObject):
    schema_name = "ConditionalRigidityAttribute::Range"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_Range
        return ConditionalRigidityAttribute_Range(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Range.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_Range
        return ConditionalRigidityAttribute_Range(entlib.make_node(ConditionalRigidityAttribute_Range.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Range(self):  # type: ()->Vector2
        return Vector2(self._node.at("Range"))
    @Range.setter
    def Range(self, val): self.Range.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




