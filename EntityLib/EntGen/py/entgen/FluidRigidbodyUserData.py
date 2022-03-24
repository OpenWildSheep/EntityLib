
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.RigidBodyUserData import *

from EntityLibPy import Node

class FluidRigidbodyUserData(HelperObject):
    schema_name = "FluidRigidbodyUserData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidRigidbodyUserData
        return FluidRigidbodyUserData(entlib.load_node_file(sourcefile, entlib.get_schema(FluidRigidbodyUserData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidRigidbodyUserData
        return FluidRigidbodyUserData(entlib.make_node(FluidRigidbodyUserData.schema_name))
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




