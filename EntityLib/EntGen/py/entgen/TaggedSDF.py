
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.variant_MeshShape_ShapeSphere_ShapeBox_ import *

from EntityLibPy import Node

class TaggedSDF(HelperObject):
    schema_name = "TaggedSDF"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TaggedSDF
        return TaggedSDF(entlib.load_node_file(sourcefile, entlib.get_schema(TaggedSDF.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TaggedSDF
        return TaggedSDF(entlib.make_node(TaggedSDF.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxTagDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxTagDistance"))
    @MaxTagDistance.setter
    def MaxTagDistance(self, val): self.MaxTagDistance.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def Shape(self):  # type: ()->variant_MeshShape_ShapeSphere_ShapeBox_
        return variant_MeshShape_ShapeSphere_ShapeBox_(self._node.at("Shape"))
    @property
    def Tag(self):  # type: ()->String
        return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




