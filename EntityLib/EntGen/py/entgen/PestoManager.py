
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class PestoManager(HelperObject):
    schema_name = "PestoManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PestoManager
        return PestoManager(entlib.load_node_file(sourcefile, entlib.get_schema(PestoManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PestoManager
        return PestoManager(entlib.make_node(PestoManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




