
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class Codec(HelperObject):
    schema_name = "Codec"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Codec
        return Codec(entlib.load_node_file(sourcefile, entlib.get_schema(Codec.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Codec
        return Codec(entlib.make_node(Codec.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




