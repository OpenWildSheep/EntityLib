
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ComponentInputBase(HelperObject):
    schema_name = "ComponentInputBase"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentInputBase
        return ComponentInputBase(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentInputBase.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentInputBase
        return ComponentInputBase(entlib.make_node(ComponentInputBase.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




