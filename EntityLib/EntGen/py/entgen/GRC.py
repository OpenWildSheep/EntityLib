
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class GRC(HelperObject):
    schema_name = "GRC"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GRC
        return GRC(entlib.load_node_file(sourcefile, entlib.get_schema(GRC.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GRC
        return GRC(entlib.make_node(GRC.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




