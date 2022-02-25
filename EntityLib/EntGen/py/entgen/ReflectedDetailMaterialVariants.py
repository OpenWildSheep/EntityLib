
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ReflectedDetailMaterial import *
from entgen.String import *

from EntityLibPy import Node

class ReflectedDetailMaterialVariants(HelperObject):
    schema_name = "ReflectedDetailMaterialVariants"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectedDetailMaterialVariants
        return ReflectedDetailMaterialVariants(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectedDetailMaterialVariants.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectedDetailMaterialVariants
        return ReflectedDetailMaterialVariants(entlib.make_node(ReflectedDetailMaterialVariants.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Variants(self):  # type: ()->Map[str, ReflectedDetailMaterial]
        return (lambda n: Map(str, ReflectedDetailMaterial, n))(self._node.at("Variants"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




