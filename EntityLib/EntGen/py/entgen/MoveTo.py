
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class MoveTo(HelperObject):
    schema_name = "MoveTo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveTo
        return MoveTo(entlib.load_node_file(sourcefile, entlib.get_schema(MoveTo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveTo
        return MoveTo(entlib.make_node(MoveTo.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




