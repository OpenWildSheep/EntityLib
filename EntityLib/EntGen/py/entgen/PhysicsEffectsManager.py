
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *
from entgen.PhysicsMaterial import *

from EntityLibPy import Node

class PhysicsEffectsManager(HelperObject):
    schema_name = "PhysicsEffectsManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsEffectsManager
        return PhysicsEffectsManager(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsEffectsManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsEffectsManager
        return PhysicsEffectsManager(entlib.make_node(PhysicsEffectsManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GravityConstant(self):  # type: ()->Float
        return Float(self._node.at("GravityConstant"))
    @GravityConstant.setter
    def GravityConstant(self, val): self.GravityConstant.set(val)
    @property
    def MaterialBank(self):  # type: ()->Array[PhysicsMaterial]
        return (lambda n: Array(PhysicsMaterial, n))(self._node.at("MaterialBank"))
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




