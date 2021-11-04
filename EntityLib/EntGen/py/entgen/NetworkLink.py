
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *

from EntityLibPy import Node

class NetworkLink(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/NetworkLink"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NetworkLink
        return NetworkLink(entlib.load_node_file(sourcefile, entlib.get_schema(NetworkLink.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NetworkLink
        return NetworkLink(entlib.make_node(NetworkLink.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Source(self):  # type: ()->String
        return String(self._node.at("Source"))
    @Source.setter
    def Source(self, val): self.Source.set(val)
    @property
    def SourceEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SourceEntityRef"))
    @SourceEntityRef.setter
    def SourceEntityRef(self, val): self.SourceEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Target(self):  # type: ()->String
        return String(self._node.at("Target"))
    @Target.setter
    def Target(self, val): self.Target.set(val)
    @property
    def TargetEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("TargetEntityRef"))
    @TargetEntityRef.setter
    def TargetEntityRef(self, val): self.TargetEntityRef.set(val)
    @property
    def ThumbnailMesh(self):  # type: ()->String
        return String(self._node.at("ThumbnailMesh"))
    @ThumbnailMesh.setter
    def ThumbnailMesh(self, val): self.ThumbnailMesh.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




