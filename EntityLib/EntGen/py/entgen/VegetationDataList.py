
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.VegetationData import *

from EntityLibPy import Node

class VegetationDataList(HelperObject):
    schema_name = "VegetationDataList"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VegetationDataList
        return VegetationDataList(entlib.load_node_file(sourcefile, entlib.get_schema(VegetationDataList.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VegetationDataList
        return VegetationDataList(entlib.make_node(VegetationDataList.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[VegetationData]
        return (lambda n: Array(VegetationData, n))(self._node.at("Data"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




