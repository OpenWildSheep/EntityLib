
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class MeshNavigationBehavior(HelperObject):
    schema_name = "MeshNavigationBehavior"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeshNavigationBehavior
        return MeshNavigationBehavior(entlib.load_node_file(sourcefile, entlib.get_schema(MeshNavigationBehavior.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeshNavigationBehavior
        return MeshNavigationBehavior(entlib.make_node(MeshNavigationBehavior.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




