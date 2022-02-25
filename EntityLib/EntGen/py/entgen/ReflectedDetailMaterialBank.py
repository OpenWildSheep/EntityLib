
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ReflectedMaterialGroupVector import *
from entgen.String import *
from entgen.ReflectedDetailMaterialVariants import *

from EntityLibPy import Node

class ReflectedDetailMaterialBank(HelperObject):
    schema_name = "ReflectedDetailMaterialBank"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectedDetailMaterialBank
        return ReflectedDetailMaterialBank(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectedDetailMaterialBank.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectedDetailMaterialBank
        return ReflectedDetailMaterialBank(entlib.make_node(ReflectedDetailMaterialBank.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Bank(self):  # type: ()->Array[ReflectedDetailMaterialVariants]
        return (lambda n: Array(ReflectedDetailMaterialVariants, n))(self._node.at("Bank"))
    @property
    def Filters(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Filters"))
    @Filters.setter
    def Filters(self, val): self.Filters.set(val)
    @property
    def Groups(self):  # type: ()->ReflectedMaterialGroupVector
        return ReflectedMaterialGroupVector(self._node.at("Groups"))
    @property
    def NeedMaterialGroupsTable(self):  # type: ()->Bool
        return Bool(self._node.at("NeedMaterialGroupsTable"))
    @NeedMaterialGroupsTable.setter
    def NeedMaterialGroupsTable(self, val): self.NeedMaterialGroupsTable.set(val)
    @property
    def RangeOverride(self):  # type: ()->Bool
        return Bool(self._node.at("RangeOverride"))
    @RangeOverride.setter
    def RangeOverride(self, val): self.RangeOverride.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




