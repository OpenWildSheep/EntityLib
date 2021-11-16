
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class NetRoot(HelperObject):
    schema_name = "NetRoot"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NetRoot
        return NetRoot(entlib.load_node_file(sourcefile, entlib.get_schema(NetRoot.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NetRoot
        return NetRoot(entlib.make_node(NetRoot.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




