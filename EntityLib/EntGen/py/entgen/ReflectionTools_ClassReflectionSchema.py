
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency import *
from entgen.ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMember import *
from entgen.ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData import *
from entgen.ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods import *

from EntityLibPy import Node

class ReflectionTools_ClassReflectionSchema(HelperObject):
    schema_name = "ReflectionTools::ClassReflectionSchema"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_ClassReflectionSchema
        return ReflectionTools_ClassReflectionSchema(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_ClassReflectionSchema.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_ClassReflectionSchema
        return ReflectionTools_ClassReflectionSchema(entlib.make_node(ReflectionTools_ClassReflectionSchema.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BaseRecursive(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BaseRecursive"))
    @BaseRecursive.setter
    def BaseRecursive(self, val): self.BaseRecursive.set(val)
    @property
    def Dependencies(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency, n))(self._node.at("Dependencies"))
    @property
    def Members(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMember]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMember, n))(self._node.at("Members"))
    @property
    def Metadata(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData, n))(self._node.at("Metadata"))
    @property
    def Methods(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods, n))(self._node.at("Methods"))
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def RPCMethods(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods, n))(self._node.at("RPCMethods"))
    @property
    def Signals(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMethods, n))(self._node.at("Signals"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




