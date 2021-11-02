
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class CheatCodeReplication(HelperObject):
    schema_name = "CheatCodeReplication"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CheatCodeReplication
        return CheatCodeReplication(entlib.load_node_file(sourcefile, entlib.get_schema(CheatCodeReplication.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CheatCodeReplication
        return CheatCodeReplication(entlib.make_node(CheatCodeReplication.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




