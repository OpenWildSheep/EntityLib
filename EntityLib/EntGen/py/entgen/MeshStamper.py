
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GeometryStamper import *

from EntityLibPy import Node

class MeshStamper(HelperObject):
    schema_name = "MeshStamper"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeshStamper
        return MeshStamper(entlib.load_node_file(sourcefile, entlib.get_schema(MeshStamper.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeshStamper
        return MeshStamper(entlib.make_node(MeshStamper.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MeshFilePath(self):  # type: ()->String
        return String(self._node.at("MeshFilePath"))
    @MeshFilePath.setter
    def MeshFilePath(self, val): self.MeshFilePath.set(val)
    @property
    def Super(self):  # type: ()->GeometryStamper
        return GeometryStamper(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




