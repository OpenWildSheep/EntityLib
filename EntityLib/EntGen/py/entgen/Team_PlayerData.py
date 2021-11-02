
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class Team_PlayerData(HelperObject):
    schema_name = "Team::PlayerData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Team_PlayerData
        return Team_PlayerData(entlib.load_node_file(sourcefile, entlib.get_schema(Team_PlayerData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Team_PlayerData
        return Team_PlayerData(entlib.make_node(Team_PlayerData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PlayerID(self):  # type: ()->Int
        return Int(self._node.at("PlayerID"))
    @PlayerID.setter
    def PlayerID(self, val): self.PlayerID.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




