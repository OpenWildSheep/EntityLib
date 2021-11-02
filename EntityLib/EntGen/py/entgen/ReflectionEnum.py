
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class ReflectionEnum(HelperObject):
    schema_name = "ReflectionEnum"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionEnum
        return ReflectionEnum(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionEnum.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionEnum
        return ReflectionEnum(entlib.make_node(ReflectionEnum.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def names(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("names"))
    @names.setter
    def names(self, val): self.names.set(val)
    @property
    def values(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("values"))
    @values.setter
    def values(self, val): self.values.set(val)
    pass




