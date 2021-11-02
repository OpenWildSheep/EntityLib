
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.RigidBodyUserData import *

from EntityLibPy import Node

class RigidBodyMeshNavigation(HelperObject):
    schema_name = "RigidBodyMeshNavigation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RigidBodyMeshNavigation
        return RigidBodyMeshNavigation(entlib.load_node_file(sourcefile, entlib.get_schema(RigidBodyMeshNavigation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RigidBodyMeshNavigation
        return RigidBodyMeshNavigation(entlib.make_node(RigidBodyMeshNavigation.schema_name))
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




