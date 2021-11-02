
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.RigidBodyUserData import *

from EntityLibPy import Node

class RigidBodyUserDataDamage(HelperObject):
    schema_name = "RigidBodyUserDataDamage"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RigidBodyUserDataDamage
        return RigidBodyUserDataDamage(entlib.load_node_file(sourcefile, entlib.get_schema(RigidBodyUserDataDamage.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RigidBodyUserDataDamage
        return RigidBodyUserDataDamage(entlib.make_node(RigidBodyUserDataDamage.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->RigidBodyUserData
        return RigidBodyUserData(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




