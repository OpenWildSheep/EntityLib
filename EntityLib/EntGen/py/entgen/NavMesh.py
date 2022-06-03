
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Vector3 import *
from entgen.Int import *
from entgen.NavMeshTile import *

from EntityLibPy import Node

class NavMesh(HelperObject):
    schema_name = "NavMesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMesh
        return NavMesh(entlib.load_node_file(sourcefile, entlib.get_schema(NavMesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMesh
        return NavMesh(entlib.make_node(NavMesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoundingBox(self):  # type: ()->Vector3
        return Vector3(self._node.at("BoundingBox"))
    @BoundingBox.setter
    def BoundingBox(self, val): self.BoundingBox.set(val)
    @property
    def CenterToCorner(self):  # type: ()->Vector3
        return Vector3(self._node.at("CenterToCorner"))
    @CenterToCorner.setter
    def CenterToCorner(self, val): self.CenterToCorner.set(val)
    @property
    def LayerSizeMask(self):  # type: ()->Int
        return Int(self._node.at("LayerSizeMask"))
    @LayerSizeMask.setter
    def LayerSizeMask(self, val): self.LayerSizeMask.set(val)
    @property
    def NumTiles(self):  # type: ()->Int
        return Int(self._node.at("NumTiles"))
    @NumTiles.setter
    def NumTiles(self, val): self.NumTiles.set(val)
    @property
    def Params(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("Params"))
    @Params.setter
    def Params(self, val): self.Params.set(val)
    @property
    def Tiles(self):  # type: ()->Array[NavMeshTile]
        return (lambda n: Array(NavMeshTile, n))(self._node.at("Tiles"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




