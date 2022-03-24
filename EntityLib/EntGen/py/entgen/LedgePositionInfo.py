
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class LedgePositionInfo(HelperObject):
    schema_name = "LedgePositionInfo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LedgePositionInfo
        return LedgePositionInfo(entlib.load_node_file(sourcefile, entlib.get_schema(LedgePositionInfo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LedgePositionInfo
        return LedgePositionInfo(entlib.make_node(LedgePositionInfo.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




