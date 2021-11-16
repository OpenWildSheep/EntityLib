
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData(HelperObject):
    schema_name = "ReflectionTools::ClassReflectionSchema::ClassReflectionSchemaMetaData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData
        return ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData
        return ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData(entlib.make_node(ReflectionTools_ClassReflectionSchema_ClassReflectionSchemaMetaData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Type_(self):  # type: ()->String
        return String(self._node.at("Type"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




