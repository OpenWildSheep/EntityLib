
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentGD
        return ComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentGD
        return ComponentGD(entlib.make_node(ComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




