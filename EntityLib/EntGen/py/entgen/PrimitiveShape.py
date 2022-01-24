
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class PrimitiveShape(HelperObject):
    schema_name = "PrimitiveShape"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PrimitiveShape
        return PrimitiveShape(entlib.load_node_file(sourcefile, entlib.get_schema(PrimitiveShape.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PrimitiveShape
        return PrimitiveShape(entlib.make_node(PrimitiveShape.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SDFPadding(self):  # type: ()->Float
        return Float(self._node.at("SDFPadding"))
    @SDFPadding.setter
    def SDFPadding(self, val): self.SDFPadding.set(val)
    @property
    def SDFVoxelSize(self):  # type: ()->Float
        return Float(self._node.at("SDFVoxelSize"))
    @SDFVoxelSize.setter
    def SDFVoxelSize(self, val): self.SDFVoxelSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




