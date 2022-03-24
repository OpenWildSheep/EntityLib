
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GeometryStamper import *

from EntityLibPy import Node

class ZoneStamper(HelperObject):
    schema_name = "ZoneStamper"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ZoneStamper
        return ZoneStamper(entlib.load_node_file(sourcefile, entlib.get_schema(ZoneStamper.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ZoneStamper
        return ZoneStamper(entlib.make_node(ZoneStamper.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ConvexZoneFilePath(self):  # type: ()->String
        return String(self._node.at("ConvexZoneFilePath"))
    @ConvexZoneFilePath.setter
    def ConvexZoneFilePath(self, val): self.ConvexZoneFilePath.set(val)
    @property
    def Super(self):  # type: ()->GeometryStamper
        return GeometryStamper(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




