
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class Edge(HelperObject):
    schema_name = "Edge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Edge
        return Edge(entlib.load_node_file(sourcefile, entlib.get_schema(Edge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Edge
        return Edge(entlib.make_node(Edge.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




