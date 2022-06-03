
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ReflectionClass import *
from entgen.ReflectionEnum import *

from EntityLibPy import Node

class ReflectionDb(HelperObject):
    schema_name = "ReflectionDb"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionDb
        return ReflectionDb(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionDb.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionDb
        return ReflectionDb(entlib.make_node(ReflectionDb.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def classes(self):  # type: ()->Array[ReflectionClass]
        return (lambda n: Array(ReflectionClass, n))(self._node.at("classes"))
    @property
    def enums(self):  # type: ()->Array[ReflectionEnum]
        return (lambda n: Array(ReflectionEnum, n))(self._node.at("enums"))
    pass




