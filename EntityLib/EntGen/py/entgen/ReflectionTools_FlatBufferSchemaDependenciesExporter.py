
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency import *

from EntityLibPy import Node

class ReflectionTools_FlatBufferSchemaDependenciesExporter(HelperObject):
    schema_name = "ReflectionTools::FlatBufferSchemaDependenciesExporter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_FlatBufferSchemaDependenciesExporter
        return ReflectionTools_FlatBufferSchemaDependenciesExporter(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_FlatBufferSchemaDependenciesExporter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_FlatBufferSchemaDependenciesExporter
        return ReflectionTools_FlatBufferSchemaDependenciesExporter(entlib.make_node(ReflectionTools_FlatBufferSchemaDependenciesExporter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def className(self):  # type: ()->String
        return String(self._node.at("className"))
    @className.setter
    def className(self, val): self.className.set(val)
    @property
    def dependencies(self):  # type: ()->Array[ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency]
        return (lambda n: Array(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaDependency, n))(self._node.at("dependencies"))
    pass




