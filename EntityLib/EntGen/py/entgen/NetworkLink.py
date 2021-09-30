
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class NetworkLink(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/NetworkLink"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(NetworkLink.schema_name))
    @property
    def Source(self): return String(self._node.at("Source"))
    @Source.setter
    def Source(self, val): self.Source.set(val)
    @property
    def SourceEntityRef(self): return EntityRef(self._node.at("SourceEntityRef"))
    @SourceEntityRef.setter
    def SourceEntityRef(self, val): self.SourceEntityRef.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Target(self): return String(self._node.at("Target"))
    @Target.setter
    def Target(self, val): self.Target.set(val)
    @property
    def TargetEntityRef(self): return EntityRef(self._node.at("TargetEntityRef"))
    @TargetEntityRef.setter
    def TargetEntityRef(self, val): self.TargetEntityRef.set(val)
    @property
    def ThumbnailMesh(self): return String(self._node.at("ThumbnailMesh"))
    @ThumbnailMesh.setter
    def ThumbnailMesh(self, val): self.ThumbnailMesh.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




