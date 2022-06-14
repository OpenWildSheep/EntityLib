
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class ZoneMeshShape(HelperObject):
    schema_name = "ZoneMeshShape"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ZoneMeshShape
        return ZoneMeshShape(entlib.load_node_file(sourcefile, entlib.get_schema(ZoneMeshShape.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ZoneMeshShape
        return ZoneMeshShape(entlib.make_node(ZoneMeshShape.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ConvexZoneFilePath(self):  # type: ()->String
        return String(self._node.at("ConvexZoneFilePath"))
    @ConvexZoneFilePath.setter
    def ConvexZoneFilePath(self, val): self.ConvexZoneFilePath.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




