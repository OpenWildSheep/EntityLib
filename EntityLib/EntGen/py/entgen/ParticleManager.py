
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Manager import *

from EntityLibPy import Node

class ParticleManager(HelperObject):
    schema_name = "ParticleManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ParticleManager
        return ParticleManager(entlib.load_node_file(sourcefile, entlib.get_schema(ParticleManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ParticleManager
        return ParticleManager(entlib.make_node(ParticleManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PoolSize(self):  # type: ()->Int
        return Int(self._node.at("PoolSize"))
    @PoolSize.setter
    def PoolSize(self, val): self.PoolSize.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




