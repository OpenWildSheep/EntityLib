
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class BehaviorPesto(HelperObject):
    schema_name = "BehaviorPesto"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BehaviorPesto
        return BehaviorPesto(entlib.load_node_file(sourcefile, entlib.get_schema(BehaviorPesto.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BehaviorPesto
        return BehaviorPesto(entlib.make_node(BehaviorPesto.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




