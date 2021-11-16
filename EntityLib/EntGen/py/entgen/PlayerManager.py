
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class PlayerManager(HelperObject):
    schema_name = "PlayerManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PlayerManager
        return PlayerManager(entlib.load_node_file(sourcefile, entlib.get_schema(PlayerManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PlayerManager
        return PlayerManager(entlib.make_node(PlayerManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SaveGame(self):  # type: ()->String
        return String(self._node.at("SaveGame"))
    @SaveGame.setter
    def SaveGame(self, val): self.SaveGame.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




