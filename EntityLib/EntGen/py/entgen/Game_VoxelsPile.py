
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class Game_VoxelsPile(HelperObject):
    schema_name = "Game::VoxelsPile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Game_VoxelsPile
        return Game_VoxelsPile(entlib.load_node_file(sourcefile, entlib.get_schema(Game_VoxelsPile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Game_VoxelsPile
        return Game_VoxelsPile(entlib.make_node(Game_VoxelsPile.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NbEmptyVoxels(self):  # type: ()->Int
        return Int(self._node.at("NbEmptyVoxels"))
    @NbEmptyVoxels.setter
    def NbEmptyVoxels(self, val): self.NbEmptyVoxels.set(val)
    @property
    def NbUsedVoxels(self):  # type: ()->Int
        return Int(self._node.at("NbUsedVoxels"))
    @NbUsedVoxels.setter
    def NbUsedVoxels(self, val): self.NbUsedVoxels.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




