
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class IMatchMakerApi(HelperObject):
    schema_name = "IMatchMakerApi"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->IMatchMakerApi
        return IMatchMakerApi(entlib.load_node_file(sourcefile, entlib.get_schema(IMatchMakerApi.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->IMatchMakerApi
        return IMatchMakerApi(entlib.make_node(IMatchMakerApi.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




