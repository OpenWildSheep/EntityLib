
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class Timer(HelperObject):
    schema_name = "Timer"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Timer
        return Timer(entlib.load_node_file(sourcefile, entlib.get_schema(Timer.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Timer
        return Timer(entlib.make_node(Timer.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




