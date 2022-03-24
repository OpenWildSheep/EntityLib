
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ReflectionTools_ClassReflectionSchema import *
from entgen.ReflectionTools_EnumSchema import *

from EntityLibPy import Node

class ReflectionTools_ReflectionSchema(HelperObject):
    schema_name = "ReflectionTools::ReflectionSchema"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_ReflectionSchema
        return ReflectionTools_ReflectionSchema(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_ReflectionSchema.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_ReflectionSchema
        return ReflectionTools_ReflectionSchema(entlib.make_node(ReflectionTools_ReflectionSchema.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Enums(self):  # type: ()->Array[ReflectionTools_EnumSchema]
        return (lambda n: Array(ReflectionTools_EnumSchema, n))(self._node.at("Enums"))
    @property
    def Schemas(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema, n))(self._node.at("Schemas"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




