
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.DetailMaterialVariants import *

from EntityLibPy import Node

class DetailMaterialBank(HelperObject):
    schema_name = "DetailMaterialBank"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DetailMaterialBank
        return DetailMaterialBank(entlib.load_node_file(sourcefile, entlib.get_schema(DetailMaterialBank.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DetailMaterialBank
        return DetailMaterialBank(entlib.make_node(DetailMaterialBank.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Bank(self):  # type: ()->Array[DetailMaterialVariants]
        return (lambda n: Array(DetailMaterialVariants, n))(self._node.at("Bank"))
    @property
    def Filters(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Filters"))
    @Filters.setter
    def Filters(self, val): self.Filters.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




