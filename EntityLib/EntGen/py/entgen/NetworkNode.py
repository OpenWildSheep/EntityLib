
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class NetworkNode(HelperObject):
    schema_name = "NetworkNode"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NetworkNode
        return NetworkNode(entlib.load_node_file(sourcefile, entlib.get_schema(NetworkNode.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NetworkNode
        return NetworkNode(entlib.make_node(NetworkNode.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tag(self):  # type: ()->String
        return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def ThumbnailMesh(self):  # type: ()->String
        return String(self._node.at("ThumbnailMesh"))
    @ThumbnailMesh.setter
    def ThumbnailMesh(self, val): self.ThumbnailMesh.set(val)
    @property
    def Type_(self):  # type: ()->String
        return String(self._node.at("Type"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




