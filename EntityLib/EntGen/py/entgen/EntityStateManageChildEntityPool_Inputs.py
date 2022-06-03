
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateManageChildEntityPool_Inputs(HelperObject):
    schema_name = "EntityStateManageChildEntityPool::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateManageChildEntityPool_Inputs
        return EntityStateManageChildEntityPool_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateManageChildEntityPool_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateManageChildEntityPool_Inputs
        return EntityStateManageChildEntityPool_Inputs(entlib.make_node(EntityStateManageChildEntityPool_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DistanceMaxFromCamera(self):  # type: ()->Float
        return Float(self._node.at("DistanceMaxFromCamera"))
    @DistanceMaxFromCamera.setter
    def DistanceMaxFromCamera(self, val): self.DistanceMaxFromCamera.set(val)
    @property
    def DistanceMaxFromSpawner(self):  # type: ()->Float
        return Float(self._node.at("DistanceMaxFromSpawner"))
    @DistanceMaxFromSpawner.setter
    def DistanceMaxFromSpawner(self, val): self.DistanceMaxFromSpawner.set(val)
    @property
    def SafeDistanceAroundPlayer(self):  # type: ()->Float
        return Float(self._node.at("SafeDistanceAroundPlayer"))
    @SafeDistanceAroundPlayer.setter
    def SafeDistanceAroundPlayer(self, val): self.SafeDistanceAroundPlayer.set(val)
    @property
    def SpawnerEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SpawnerEntityRef"))
    @SpawnerEntityRef.setter
    def SpawnerEntityRef(self, val): self.SpawnerEntityRef.set(val)
    @property
    def UnspawnDelay(self):  # type: ()->Float
        return Float(self._node.at("UnspawnDelay"))
    @UnspawnDelay.setter
    def UnspawnDelay(self, val): self.UnspawnDelay.set(val)
    @property
    def UnspawnRadius(self):  # type: ()->Float
        return Float(self._node.at("UnspawnRadius"))
    @UnspawnRadius.setter
    def UnspawnRadius(self, val): self.UnspawnRadius.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




