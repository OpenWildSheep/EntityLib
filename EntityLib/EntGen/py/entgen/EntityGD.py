
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class EntityGD(HelperObject):
    schema_name = "EntityGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityGD
        return EntityGD(entlib.load_node_file(sourcefile, entlib.get_schema(EntityGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityGD
        return EntityGD(entlib.make_node(EntityGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def components(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("components"))
    @components.setter
    def components(self, val): self.components.set(val)
    pass




