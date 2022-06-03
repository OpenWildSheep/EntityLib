
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Matrix43 import *

from EntityLibPy import Node

class PointCloudInstanceDataResource(HelperObject):
    schema_name = "PointCloudInstanceDataResource"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PointCloudInstanceDataResource
        return PointCloudInstanceDataResource(entlib.load_node_file(sourcefile, entlib.get_schema(PointCloudInstanceDataResource.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PointCloudInstanceDataResource
        return PointCloudInstanceDataResource(entlib.make_node(PointCloudInstanceDataResource.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def index(self):  # type: ()->Int
        return Int(self._node.at("index"))
    @index.setter
    def index(self, val): self.index.set(val)
    @property
    def matrix(self):  # type: ()->Matrix43
        return Matrix43(self._node.at("matrix"))
    @matrix.setter
    def matrix(self, val): self.matrix.set(val)
    pass




