
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.SmallActorSpawnRuleData import *

from EntityLibPy import Node

class SmallActorSpawnPointData(HelperObject):
    schema_name = "SmallActorSpawnPointData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmallActorSpawnPointData
        return SmallActorSpawnPointData(entlib.load_node_file(sourcefile, entlib.get_schema(SmallActorSpawnPointData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmallActorSpawnPointData
        return SmallActorSpawnPointData(entlib.make_node(SmallActorSpawnPointData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SelectionProbability(self):  # type: ()->Float
        return Float(self._node.at("SelectionProbability"))
    @SelectionProbability.setter
    def SelectionProbability(self, val): self.SelectionProbability.set(val)
    @property
    def SpawnRules(self):  # type: ()->Array[SmallActorSpawnRuleData]
        return (lambda n: Array(SmallActorSpawnRuleData, n))(self._node.at("SpawnRules"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




