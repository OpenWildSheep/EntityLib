
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.PointCloudInstanceDataResource import *

from EntityLibPy import Node

class PointCloudChunk(HelperObject):
    schema_name = "PointCloudChunk"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PointCloudChunk
        return PointCloudChunk(entlib.load_node_file(sourcefile, entlib.get_schema(PointCloudChunk.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PointCloudChunk
        return PointCloudChunk(entlib.make_node(PointCloudChunk.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def chunkPosX(self):  # type: ()->Int
        return Int(self._node.at("chunkPosX"))
    @chunkPosX.setter
    def chunkPosX(self, val): self.chunkPosX.set(val)
    @property
    def chunkPosY(self):  # type: ()->Int
        return Int(self._node.at("chunkPosY"))
    @chunkPosY.setter
    def chunkPosY(self, val): self.chunkPosY.set(val)
    @property
    def chunkPosZ(self):  # type: ()->Int
        return Int(self._node.at("chunkPosZ"))
    @chunkPosZ.setter
    def chunkPosZ(self, val): self.chunkPosZ.set(val)
    @property
    def instances(self):  # type: ()->Array[PointCloudInstanceDataResource]
        return (lambda n: Array(PointCloudInstanceDataResource, n))(self._node.at("instances"))
    pass




