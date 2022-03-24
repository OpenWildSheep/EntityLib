
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class Game_Voxel(HelperObject):
    schema_name = "Game::Voxel"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Game_Voxel
        return Game_Voxel(entlib.load_node_file(sourcefile, entlib.get_schema(Game_Voxel.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Game_Voxel
        return Game_Voxel(entlib.make_node(Game_Voxel.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NeighboursMask(self):  # type: ()->Int
        return Int(self._node.at("NeighboursMask"))
    @NeighboursMask.setter
    def NeighboursMask(self, val): self.NeighboursMask.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




