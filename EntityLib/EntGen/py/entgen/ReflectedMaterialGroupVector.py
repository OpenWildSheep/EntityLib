
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ReflectedMaterialGroup import *
from entgen.String import *

from EntityLibPy import Node

class ReflectedMaterialGroupVector(HelperObject):
    schema_name = "ReflectedMaterialGroupVector"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectedMaterialGroupVector
        return ReflectedMaterialGroupVector(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectedMaterialGroupVector.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectedMaterialGroupVector
        return ReflectedMaterialGroupVector(entlib.make_node(ReflectedMaterialGroupVector.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Groups(self):  # type: ()->Map[str, ReflectedMaterialGroup]
        return (lambda n: Map(str, ReflectedMaterialGroup, n))(self._node.at("Groups"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




