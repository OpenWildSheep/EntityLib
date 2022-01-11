
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.SeedPatchData import *
from entgen.String import *

from EntityLibPy import Node

class SeedPatchDatas(HelperObject):
    schema_name = "SeedPatchDatas"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatchDatas
        return SeedPatchDatas(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchDatas.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatchDatas
        return SeedPatchDatas(entlib.make_node(SeedPatchDatas.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DataMap(self):  # type: ()->Map[str, SeedPatchData]
        return (lambda n: Map(str, SeedPatchData, n))(self._node.at("DataMap"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




