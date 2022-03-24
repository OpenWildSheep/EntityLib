
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ReflectionMethod import *

from EntityLibPy import Node

class ReflectionClass(HelperObject):
    schema_name = "ReflectionClass"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionClass
        return ReflectionClass(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionClass.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionClass
        return ReflectionClass(entlib.make_node(ReflectionClass.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def methods(self):  # type: ()->Array[ReflectionMethod]
        return (lambda n: Array(ReflectionMethod, n))(self._node.at("methods"))
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass




