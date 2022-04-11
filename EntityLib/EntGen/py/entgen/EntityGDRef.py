
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class EntityGDRef(HelperObject):
    schema_name = "EntityGDRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityGDRef
        return EntityGDRef(entlib.load_node_file(sourcefile, entlib.get_schema(EntityGDRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityGDRef
        return EntityGDRef(entlib.make_node(EntityGDRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def hash(self):  # type: ()->String
        return String(self._node.at("hash"))
    @hash.setter
    def hash(self, val): self.hash.set(val)
    pass




