
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class ReflectionTools_EnumSchema(HelperObject):
    schema_name = "ReflectionTools::EnumSchema"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_EnumSchema
        return ReflectionTools_EnumSchema(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_EnumSchema.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_EnumSchema
        return ReflectionTools_EnumSchema(entlib.make_node(ReflectionTools_EnumSchema.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Values(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Values"))
    @Values.setter
    def Values(self, val): self.Values.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




