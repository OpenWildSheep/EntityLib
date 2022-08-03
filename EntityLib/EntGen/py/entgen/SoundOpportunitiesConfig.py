
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.SmallActorSpawnPointData import *
from entgen.String import *

from EntityLibPy import Node

class SoundOpportunitiesConfig(HelperObject):
    schema_name = "SoundOpportunitiesConfig"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundOpportunitiesConfig
        return SoundOpportunitiesConfig(entlib.load_node_file(sourcefile, entlib.get_schema(SoundOpportunitiesConfig.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundOpportunitiesConfig
        return SoundOpportunitiesConfig(entlib.make_node(SoundOpportunitiesConfig.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SmallActorSpawnRules(self):  # type: ()->Map[str, SmallActorSpawnPointData]
        return (lambda n: Map(str, SmallActorSpawnPointData, n))(self._node.at("SmallActorSpawnRules"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




