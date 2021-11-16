
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class GameMasterManager(HelperObject):
    schema_name = "GameMasterManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameMasterManager
        return GameMasterManager(entlib.load_node_file(sourcefile, entlib.get_schema(GameMasterManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameMasterManager
        return GameMasterManager(entlib.make_node(GameMasterManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxTimeBetweenSoulOpportunityRespawn(self):  # type: ()->Float
        return Float(self._node.at("MaxTimeBetweenSoulOpportunityRespawn"))
    @MaxTimeBetweenSoulOpportunityRespawn.setter
    def MaxTimeBetweenSoulOpportunityRespawn(self, val): self.MaxTimeBetweenSoulOpportunityRespawn.set(val)
    @property
    def MinDistBetweenSoulOpportunityRespawn(self):  # type: ()->Float
        return Float(self._node.at("MinDistBetweenSoulOpportunityRespawn"))
    @MinDistBetweenSoulOpportunityRespawn.setter
    def MinDistBetweenSoulOpportunityRespawn(self, val): self.MinDistBetweenSoulOpportunityRespawn.set(val)
    @property
    def RadiusWithoutEnemy(self):  # type: ()->Float
        return Float(self._node.at("RadiusWithoutEnemy"))
    @RadiusWithoutEnemy.setter
    def RadiusWithoutEnemy(self, val): self.RadiusWithoutEnemy.set(val)
    @property
    def SoulOpportunitySpawnRadius(self):  # type: ()->Float
        return Float(self._node.at("SoulOpportunitySpawnRadius"))
    @SoulOpportunitySpawnRadius.setter
    def SoulOpportunitySpawnRadius(self, val): self.SoulOpportunitySpawnRadius.set(val)
    @property
    def SoulOpportunityUnspawnInsideFrustumRadius(self):  # type: ()->Float
        return Float(self._node.at("SoulOpportunityUnspawnInsideFrustumRadius"))
    @SoulOpportunityUnspawnInsideFrustumRadius.setter
    def SoulOpportunityUnspawnInsideFrustumRadius(self, val): self.SoulOpportunityUnspawnInsideFrustumRadius.set(val)
    @property
    def SoulOpportunityUnspawnOutsideFrustumRadius(self):  # type: ()->Float
        return Float(self._node.at("SoulOpportunityUnspawnOutsideFrustumRadius"))
    @SoulOpportunityUnspawnOutsideFrustumRadius.setter
    def SoulOpportunityUnspawnOutsideFrustumRadius(self, val): self.SoulOpportunityUnspawnOutsideFrustumRadius.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




