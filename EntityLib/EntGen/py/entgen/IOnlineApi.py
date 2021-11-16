
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class IOnlineApi(HelperObject):
    schema_name = "IOnlineApi"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->IOnlineApi
        return IOnlineApi(entlib.load_node_file(sourcefile, entlib.get_schema(IOnlineApi.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->IOnlineApi
        return IOnlineApi(entlib.make_node(IOnlineApi.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




