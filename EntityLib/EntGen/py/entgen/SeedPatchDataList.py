
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.SeedPatchData import *

from EntityLibPy import Node

class SeedPatchDataList(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SeedPatchDataList"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatchDataList
        return SeedPatchDataList(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchDataList.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatchDataList
        return SeedPatchDataList(entlib.make_node(SeedPatchDataList.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[SeedPatchData]
        return (lambda n: Array(SeedPatchData, n))(self._node.at("Data"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




