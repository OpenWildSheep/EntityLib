
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *

from EntityLibPy import Node

class ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency(HelperObject):
    schema_name = "ReflectionTools::ClassReflectionSchema::ClassReflectionSchemaDependency"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency
        return ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency
        return ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency(entlib.make_node(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Optional(self):  # type: ()->Bool
        return Bool(self._node.at("Optional"))
    @Optional.setter
    def Optional(self, val): self.Optional.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




