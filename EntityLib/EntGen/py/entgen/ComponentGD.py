
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy



class ComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ComponentGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ComponentGD.schema_name))
    pass




