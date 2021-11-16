
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class ClassMemberRef(HelperObject):
    schema_name = "ClassMemberRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClassMemberRef
        return ClassMemberRef(entlib.load_node_file(sourcefile, entlib.get_schema(ClassMemberRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClassMemberRef
        return ClassMemberRef(entlib.make_node(ClassMemberRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def class_(self):  # type: ()->String
        return String(self._node.at("class"))
    @class_.setter
    def class_(self, val): self.class_.set(val)
    @property
    def member(self):  # type: ()->String
        return String(self._node.at("member"))
    @member.setter
    def member(self, val): self.member.set(val)
    pass




