
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class GameTimeInMs(HelperObject):
    schema_name = "GameTimeInMs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameTimeInMs
        return GameTimeInMs(entlib.load_node_file(sourcefile, entlib.get_schema(GameTimeInMs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameTimeInMs
        return GameTimeInMs(entlib.make_node(GameTimeInMs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




