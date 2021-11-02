
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class RigidBodyUserData(HelperObject):
    schema_name = "RigidBodyUserData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RigidBodyUserData
        return RigidBodyUserData(entlib.load_node_file(sourcefile, entlib.get_schema(RigidBodyUserData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RigidBodyUserData
        return RigidBodyUserData(entlib.make_node(RigidBodyUserData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




