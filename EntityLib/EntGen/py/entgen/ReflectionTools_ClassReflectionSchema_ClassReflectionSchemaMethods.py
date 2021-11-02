
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods(HelperObject):
    schema_name = "ReflectionTools::ClassReflectionSchema::ClassReflectionSchemaMethods"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods
        return ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods
        return ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods(entlib.make_node(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def ParamTypes(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ParamTypes"))
    @ParamTypes.setter
    def ParamTypes(self, val): self.ParamTypes.set(val)
    @property
    def ReturnType(self):  # type: ()->String
        return String(self._node.at("ReturnType"))
    @ReturnType.setter
    def ReturnType(self, val): self.ReturnType.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




