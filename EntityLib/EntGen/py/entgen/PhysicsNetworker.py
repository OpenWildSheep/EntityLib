
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class PhysicsNetworker(HelperObject):
    schema_name = "PhysicsNetworker"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsNetworker
        return PhysicsNetworker(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsNetworker.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsNetworker
        return PhysicsNetworker(entlib.make_node(PhysicsNetworker.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




