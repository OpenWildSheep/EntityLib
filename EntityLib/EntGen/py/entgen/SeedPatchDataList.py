
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.SeedPatchData import *


class SeedPatchDataList(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SeedPatchDataList"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchDataList.schema_name))
    @property
    def Data(self): return (lambda n: Array(SeedPatchData, n))(self._node.at("Data"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




