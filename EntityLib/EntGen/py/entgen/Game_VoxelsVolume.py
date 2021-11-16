
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.Game_VoxelsColumn import *

from EntityLibPy import Node

class Game_VoxelsVolume(HelperObject):
    schema_name = "Game::VoxelsVolume"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Game_VoxelsVolume
        return Game_VoxelsVolume(entlib.load_node_file(sourcefile, entlib.get_schema(Game_VoxelsVolume.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Game_VoxelsVolume
        return Game_VoxelsVolume(entlib.make_node(Game_VoxelsVolume.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnchorToCorner(self):  # type: ()->Vector3
        return Vector3(self._node.at("AnchorToCorner"))
    @AnchorToCorner.setter
    def AnchorToCorner(self, val): self.AnchorToCorner.set(val)
    @property
    def BoundingBox(self):  # type: ()->Vector3
        return Vector3(self._node.at("BoundingBox"))
    @BoundingBox.setter
    def BoundingBox(self, val): self.BoundingBox.set(val)
    @property
    def Columns(self):  # type: ()->Array[Game_VoxelsColumn]
        return (lambda n: Array(Game_VoxelsColumn, n))(self._node.at("Columns"))
    @property
    def Height(self):  # type: ()->Int
        return Int(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def VoxelSize(self):  # type: ()->Float
        return Float(self._node.at("VoxelSize"))
    @VoxelSize.setter
    def VoxelSize(self, val): self.VoxelSize.set(val)
    @property
    def Width(self):  # type: ()->Int
        return Int(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




