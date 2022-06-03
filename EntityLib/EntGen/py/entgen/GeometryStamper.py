
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Transform3D import *

from EntityLibPy import Node

class GeometryStamper(HelperObject):
    schema_name = "GeometryStamper"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GeometryStamper
        return GeometryStamper(entlib.load_node_file(sourcefile, entlib.get_schema(GeometryStamper.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GeometryStamper
        return GeometryStamper(entlib.make_node(GeometryStamper.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Transform(self):  # type: ()->Transform3D
        return Transform3D(self._node.at("Transform"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




