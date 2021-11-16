
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ReplicaReplay(HelperObject):
    schema_name = "ReplicaReplay"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReplicaReplay
        return ReplicaReplay(entlib.load_node_file(sourcefile, entlib.get_schema(ReplicaReplay.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReplicaReplay
        return ReplicaReplay(entlib.make_node(ReplicaReplay.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




