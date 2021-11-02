
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.TravelParams import *

from EntityLibPy import Node

class GameRespawnData(HelperObject):
    schema_name = "GameRespawnData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameRespawnData
        return GameRespawnData(entlib.load_node_file(sourcefile, entlib.get_schema(GameRespawnData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameRespawnData
        return GameRespawnData(entlib.make_node(GameRespawnData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GuardianTravelParams(self):  # type: ()->TravelParams
        return TravelParams(self._node.at("GuardianTravelParams"))
    @property
    def IdleTimeBeforeRespawn(self):  # type: ()->Float
        return Float(self._node.at("IdleTimeBeforeRespawn"))
    @IdleTimeBeforeRespawn.setter
    def IdleTimeBeforeRespawn(self, val): self.IdleTimeBeforeRespawn.set(val)
    @property
    def NonGuardianTravelParams(self):  # type: ()->TravelParams
        return TravelParams(self._node.at("NonGuardianTravelParams"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




