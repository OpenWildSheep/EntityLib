
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ReflectionMethodParameter import *

from EntityLibPy import Node

class ReflectionMethod(HelperObject):
    schema_name = "ReflectionMethod"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionMethod
        return ReflectionMethod(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionMethod.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionMethod
        return ReflectionMethod(entlib.make_node(ReflectionMethod.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def inputs(self):  # type: ()->Array[ReflectionMethodParameter]
        return (lambda n: Array(ReflectionMethodParameter, n))(self._node.at("inputs"))
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def outputs(self):  # type: ()->Array[ReflectionMethodParameter]
        return (lambda n: Array(ReflectionMethodParameter, n))(self._node.at("outputs"))
    @property
    def threadSafe(self):  # type: ()->Bool
        return Bool(self._node.at("threadSafe"))
    @threadSafe.setter
    def threadSafe(self, val): self.threadSafe.set(val)
    pass




