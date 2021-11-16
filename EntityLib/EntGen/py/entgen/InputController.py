
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class InputController(HelperObject):
    schema_name = "InputController"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InputController
        return InputController(entlib.load_node_file(sourcefile, entlib.get_schema(InputController.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InputController
        return InputController(entlib.make_node(InputController.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass



