
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class ReflectionMethodParameter(HelperObject):
    schema_name = "ReflectionMethodParameter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectionMethodParameter
        return ReflectionMethodParameter(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectionMethodParameter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectionMethodParameter
        return ReflectionMethodParameter(entlib.make_node(ReflectionMethodParameter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def containerType(self):  # type: ()->Int
        return Int(self._node.at("containerType"))
    @containerType.setter
    def containerType(self, val): self.containerType.set(val)
    @property
    def elementType(self):  # type: ()->Int
        return Int(self._node.at("elementType"))
    @elementType.setter
    def elementType(self, val): self.elementType.set(val)
    @property
    def elementTypeName(self):  # type: ()->String
        return String(self._node.at("elementTypeName"))
    @elementTypeName.setter
    def elementTypeName(self, val): self.elementTypeName.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def typeName(self):  # type: ()->String
        return String(self._node.at("typeName"))
    @typeName.setter
    def typeName(self, val): self.typeName.set(val)
    pass




