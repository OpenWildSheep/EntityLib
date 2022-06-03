
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Game_VoxelsPile import *

from EntityLibPy import Node

class Game_VoxelsColumn(HelperObject):
    schema_name = "Game::VoxelsColumn"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Game_VoxelsColumn
        return Game_VoxelsColumn(entlib.load_node_file(sourcefile, entlib.get_schema(Game_VoxelsColumn.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Game_VoxelsColumn
        return Game_VoxelsColumn(entlib.make_node(Game_VoxelsColumn.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Piles(self):  # type: ()->Array[Game_VoxelsPile]
        return (lambda n: Array(Game_VoxelsPile, n))(self._node.at("Piles"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




