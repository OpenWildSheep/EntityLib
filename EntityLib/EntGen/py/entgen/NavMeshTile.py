
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class NavMeshTile(HelperObject):
    schema_name = "NavMeshTile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMeshTile
        return NavMeshTile(entlib.load_node_file(sourcefile, entlib.get_schema(NavMeshTile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMeshTile
        return NavMeshTile(entlib.make_node(NavMeshTile.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("Data"))
    @Data.setter
    def Data(self, val): self.Data.set(val)
    @property
    def TileRef(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("TileRef"))
    @TileRef.setter
    def TileRef(self, val): self.TileRef.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




