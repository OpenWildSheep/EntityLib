
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ActionStackFilter(HelperObject):
    schema_name = "ActionStackFilter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStackFilter
        return ActionStackFilter(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStackFilter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStackFilter
        return ActionStackFilter(entlib.make_node(ActionStackFilter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




