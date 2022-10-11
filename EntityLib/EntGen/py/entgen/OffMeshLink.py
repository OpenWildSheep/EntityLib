
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.Bool import *
from entgen.CapabilitiesAndTags import *
from entgen.Float import *
from entgen.WallRunData import *

from EntityLibPy import Node

class OffMeshLink(HelperObject):
    schema_name = "OffMeshLink"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OffMeshLink
        return OffMeshLink(entlib.load_node_file(sourcefile, entlib.get_schema(OffMeshLink.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OffMeshLink
        return OffMeshLink(entlib.make_node(OffMeshLink.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def bidirectional(self):  # type: ()->Bool
        return Bool(self._node.at("bidirectional"))
    @bidirectional.setter
    def bidirectional(self, val): self.bidirectional.set(val)
    @property
    def capabilitiesAndTags(self):  # type: ()->CapabilitiesAndTags
        return CapabilitiesAndTags(self._node.at("capabilitiesAndTags"))
    @property
    def destination(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("destination"))
    @destination.setter
    def destination(self, val): self.destination.set(val)
    @property
    def offMeshLinkData(self):  # type: ()->WallRunData
        return WallRunData(self._node.at("offMeshLinkData"))
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    @property
    def shouldBeAddedToMinModif(self):  # type: ()->Bool
        return Bool(self._node.at("shouldBeAddedToMinModif"))
    @shouldBeAddedToMinModif.setter
    def shouldBeAddedToMinModif(self, val): self.shouldBeAddedToMinModif.set(val)
    pass




