
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ClassMemberRef import *

from EntityLibPy import Node

class ComponentMethodRef(HelperObject):
    schema_name = "ComponentMethodRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentMethodRef
        return ComponentMethodRef(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentMethodRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentMethodRef
        return ComponentMethodRef(entlib.make_node(ComponentMethodRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Method(self):  # type: ()->ClassMemberRef
        return ClassMemberRef(self._node.at("Method"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




