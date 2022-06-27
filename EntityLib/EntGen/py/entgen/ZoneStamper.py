
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.CapabilitiesAndTags import *
from entgen.Float import *
from entgen.GeometryStamper import *
from entgen.variant_EntityRef_NavMeshArea_ import *
from entgen.variant_ZoneCylinderShape_ZoneMeshShape_ import *

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
    def CapabilitiesAndTags(self):  # type: ()->CapabilitiesAndTags
        return CapabilitiesAndTags(self._node.at("CapabilitiesAndTags"))
    @property
    def DownwardOffset(self):  # type: ()->Float
        return Float(self._node.at("DownwardOffset"))
    @DownwardOffset.setter
    def DownwardOffset(self, val): self.DownwardOffset.set(val)
    @property
    def NavMeshArea(self):  # type: ()->variant_EntityRef_NavMeshArea_
        return variant_EntityRef_NavMeshArea_(self._node.at("NavMeshArea"))
    @property
    def Priority(self):  # type: ()->Int
        return Int(self._node.at("Priority"))
    @Priority.setter
    def Priority(self, val): self.Priority.set(val)
    @property
    def Shape(self):  # type: ()->variant_ZoneCylinderShape_ZoneMeshShape_
        return variant_ZoneCylinderShape_ZoneMeshShape_(self._node.at("Shape"))
    @property
    def Super(self):  # type: ()->GeometryStamper
        return GeometryStamper(self._node.at("Super"))
    @property
    def UpwardOffset(self):  # type: ()->Float
        return Float(self._node.at("UpwardOffset"))
    @UpwardOffset.setter
    def UpwardOffset(self, val): self.UpwardOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




