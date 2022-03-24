
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.RigidBodyUserData import *

from EntityLibPy import Node

class RigidBodyUserDataImpact(HelperObject):
    schema_name = "RigidBodyUserDataImpact"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RigidBodyUserDataImpact
        return RigidBodyUserDataImpact(entlib.load_node_file(sourcefile, entlib.get_schema(RigidBodyUserDataImpact.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RigidBodyUserDataImpact
        return RigidBodyUserDataImpact(entlib.make_node(RigidBodyUserDataImpact.schema_name))
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




