
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class NetworkNode(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/NetworkNode"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(NetworkNode.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Tag(self): return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def ThumbnailMesh(self): return String(self._node.at("ThumbnailMesh"))
    @ThumbnailMesh.setter
    def ThumbnailMesh(self, val): self.ThumbnailMesh.set(val)
    @property
    def Type_(self): return String(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




