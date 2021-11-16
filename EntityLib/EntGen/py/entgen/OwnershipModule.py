
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class OwnershipModule(HelperObject):
    schema_name = "OwnershipModule"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OwnershipModule
        return OwnershipModule(entlib.load_node_file(sourcefile, entlib.get_schema(OwnershipModule.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OwnershipModule
        return OwnershipModule(entlib.make_node(OwnershipModule.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




